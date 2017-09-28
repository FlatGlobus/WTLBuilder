// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "FormComponent.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
#define FORM_PRORITY 64

static ComponentArray * clipboard = NULL;
static void FreeClipboard()
{
    if (clipboard)
    {
        for (; clipboard->size();)
        {
            delete (*clipboard)[0];
            clipboard->erase(clipboard->begin());
        }
        delete clipboard;
        clipboard = NULL;
    }
}
PROPERTY_API BOOL IsPasteEnabled()
{
    return clipboard != NULL;
}
size_t Undo::max_undos = MAX_UNDOS;
//////////////////////////////////////////////////////////////////////////
Undo::Undo() :changed(FALSE), fixChanges(FALSE)
{

}

Undo::~Undo()
{
    undo.RemoveAll();
}

void Undo::Add(const CString & str)
{
    CMsgPump pump;
    undo.Add(str);
    if (undo.GetCount() > 1 || fixChanges == TRUE)
        changed = TRUE;

    if (undo.GetCount() > max_undos)
    {
        undo.RemoveAt(0, 1);
        fixChanges = TRUE;
    }
    EnableUndo();
}

CString Undo::Get()
{
    CMsgPump pump;
    CString ret;
    if (undo.GetCount() - 2)
    {
        ret = undo.GetAt(undo.GetCount() - 2);
        undo.RemoveAt(undo.GetCount() - 2, 1);
    }
    else
    {
        ret = undo.GetAt(0);
        undo.RemoveAt(1, 1);
    }

    if (undo.GetCount() - 1 == 0)
        changed = fixChanges;

    EnableUndo();
    return ret;
}

void Undo::EnableUndo()
{
    PostEvent(evEnableUndo, (BOOL)((int)undo.GetCount() - 1 > 0));
}

BOOL Undo::IsModified()
{
    return undo.GetCount() != 1 && changed == TRUE;
}

void Undo::Reset()
{
    changed = FALSE;
    fixChanges = FALSE;
    undo.RemoveAll();
    EnableUndo();
}
//////////////////////////////////////////////////////////////////////////
CFormComponent::CFormComponent(LPTSTR _name) :Component(_name), enableClose(FALSE), showWindow(TRUE),
visible(TRUE), bkColor(COLOR_WINDOW), _controlsToClip(NULL), enableLayout(FALSE), nPositions(1),
formIcon(ICON_TYPE), classStyle(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW), fromTemplate(TRUE), idBase(0),
caption(_T("")), sizeChanged(FALSE), showHandle(FALSE)
{
    RegisterEvent(evSaveForm, this, &CFormComponent::SaveForm, FORM_PRORITY);
    RegisterEvent(evSaveAsForm, this, &CFormComponent::SaveAsForm, FORM_PRORITY);
    RegisterEvent(evSaveFormAsTemplate, this, &CFormComponent::SaveAsTemplate, FORM_PRORITY);
    RegisterEvent(evLoadForm, this, &CFormComponent::LoadForm);
    RegisterEvent(evCloseForm, this, &CFormComponent::CloseForm, 32);
    RegisterEvent(evGetFormFileName, this, &CFormComponent::GetFormFileName);
    RegisterEvent(evSetFormFileName, this, &CFormComponent::SetFormFileName);

    RegisterEvent(evGoldenSectionWidth, this, &CFormComponent::MakeGoldenSectionWidht);
    RegisterEvent(evGoldenSectionHeight, this, &CFormComponent::MakeGoldenSectionHeight);
    RegisterEvent(evGenerateLocFile, this, &CFormComponent::GenerateLocFile);
    RegisterEvent(evShowGrid, this, &CFormComponent::ShowGrid);
    RegisterEvent(evSetGridSizeX, this, &CFormComponent::SetGridWidth);
    RegisterEvent(evSetGridSizeY, this, &CFormComponent::SetGridHeight);

    RegisterEvent(evAddUndo, this, &CFormComponent::AddUndo, FORM_PRORITY);
    RegisterEvent(evUndo, this, &CFormComponent::UndoChanges, FORM_PRORITY);
    RegisterEvent(evCopy, this, &CFormComponent::EditCopy, FORM_PRORITY);
    RegisterEvent(evPaste, this, &CFormComponent::EditPaste, FORM_PRORITY);
    RegisterEvent(evCut, this, &CFormComponent::EditCut, FORM_PRORITY);
    RegisterEvent(evDelete, this, &CFormComponent::EditDelete, FORM_PRORITY);

    RegisterEvent(evTabIndex, this, &CFormComponent::TabIndex);

    RegisterEvent(evIsFormChanged, this, &CFormComponent::IsFormChanged);

    designer = new CDesignerCtrl;
    SetModified();
}

CFormComponent::~CFormComponent()
{
    UnRegisterEvent(this);
    if (designer)
        delete designer;
}

BOOL CFormComponent::PreTranslateMessage(MSG* pMsg)
{
    if (CFrameWindowImpl<CFormComponent, CWindow>::PreTranslateMessage(pMsg))
        return TRUE;
    return 0;
}

IDispatch* __stdcall CFormComponent::get_Code()
{
    return &codeGen;
}

LRESULT CFormComponent::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
    designer->Create(this, &components);
    components.SetDesigner(designer);
    Parent = this;
    SetFormFont(NULL);
    formFont.Change.SetObject(this);
    formFont.Change.SetMethod(&CFormComponent::SetFormFont);
    SetFont((HFONT)formFont, TRUE);
    SetState(csCreating, FALSE);
    formIcon.Change.SetObject(this);
    formIcon.Change.SetMethod(&CFormComponent::OnImageChange);
    return lRes;
}

LRESULT CFormComponent::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
    bHandled = TRUE;
    return 0;
}

LRESULT CFormComponent::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (LOWORD(wParam) != WA_INACTIVE)
    {
        BringWindowToTop();
        if (GetState(csLoading) == FALSE)
        {
            PostEvent(evShowGrid, NULL, get_Grid());
            PostEvent(evSetGridSizeX, NULL, get_GridWidth());
            PostEvent(evSetGridSizeY, NULL, get_GridHeight());
        }
        undo.EnableUndo();
        GetDesigner()->SetFocus();
        fileName.SetCurDir();
    }
    return 0;
}

LRESULT CFormComponent::OnEndSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (sizeChanged == TRUE)
        AddUndo(this);
    sizeChanged = FALSE;
    return 0;
}

LRESULT CFormComponent::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (GetState(csLoading) == FALSE && GetState(csCreating) == FALSE)
    {
        CRect clientRC;
        GetClientRect(&clientRC);
        CRect wndRc;
        GetWindowRect(&wndRc);
        CPoint delta;
        minRC = GetMinRect();
        if (minRC.IsRectNull() == FALSE)
        {
            delta.x = wndRc.Width() - clientRC.Width();
            delta.y = wndRc.Height() - clientRC.Height();
            if (GetDesigner() != NULL)
                delta = GetDesigner()->SnapToGrid(delta);
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = minRC.Width() + delta.x;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = minRC.Height() + delta.y;
            return FALSE;
        }
    }
    return TRUE;
}

LRESULT CFormComponent::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam != SIZE_MINIMIZED && IsWindow())
    {
        //if(enableLayout==TRUE)
        //	LayoutMgr<CFormComponent>::OnSize(uMsg,wParam,lParam,bHandled);
        clientWidth = LOWORD(lParam);
        clientHeight = HIWORD(lParam);
        UpdateBoundsProp(GetBoundsRect());
        UpdateProperty(_T("ClientWidth"));
        UpdateProperty(_T("ClientHeight"));
        UpdateLayout();
        if (GetState(csLoading) == FALSE && GetState(csCreating) == FALSE)
            sizeChanged = TRUE;

        designer->SetWindowPos(HWND_TOP, 0, 0, clientWidth, clientHeight, SWP_NOCOPYBITS | SWP_SHOWWINDOW | SWP_SHOWWINDOW);
        RedrawWindow(NULL, NULL, RDW_NOERASE | RDW_INTERNALPAINT | RDW_ALLCHILDREN | RDW_UPDATENOW | RDW_INVALIDATE);
    }
    return TRUE;
}

void CFormComponent::DoPaint(CDCHandle dc)
{
}

LRESULT CFormComponent::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
    CPaintDC dc((HWND)GetHandle());
    designer->PaintGrid(dc, bkColor);
    return 0;
}

LRESULT CFormComponent::OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
    return TRUE;
}

LRESULT CFormComponent::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
    if (IsWindow())
        UpdateBoundsProp(GetBoundsRect());

    bHandled = TRUE;
    return lRes;
}

LRESULT CFormComponent::OnButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
    GetComponents()->UnselectAll();
    ShowProperties();
    PostEvent(evSetActiveForm, (Component *)this);
    BringWindowToTop();
    fileName.SetCurDir();
    return lRes;
}

LRESULT CFormComponent::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    RemoveProperties();
    if (enableClose == FALSE)
    {
        bHandled = TRUE;
        ShowWindow(SW_HIDE);
        return TRUE;
    }
    else
        bHandled = FALSE;
    return 0;
}

void CFormComponent::SetFormFont(CFontEx *)
{
    SetFont((HFONT)formFont, TRUE);
    for (int i = 0; i < components.GetCount(); i++)
    {
        if (components.GetAt(i)->IsControl()/* && components.GetAt(i)->GetComponentParent()==this*/)
        {
            HWND ctrl = (HWND)components.GetAt(i)->GetHandle();
            if (::IsWindow(ctrl))
                ::SendMessage(ctrl, WM_SETCTRLFONT, 0, (LPARAM)&formFont);
        }
    }
    SetModified();
}

LRESULT CFormComponent::OnGetFormFont(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
    bHandled = TRUE;
    return (LRESULT)&formFont;
}

typedef DWORD WindowBorderStyle;
typedef DWORD WindowStyle;

void CFormComponent::InitProperty(void)
{
    Component::InitProperty();
    PUBLIC_PROPERTY(Generate, FALSE)
        DEFINE_PROPERTY(InternalWindowStyle, DWORD, CFormComponent, CControlWinTraits::GetWndStyle(0))
        PUBLIC_PROPERTY(InternalWindowStyle, FALSE)
        DEFINE_PROPERTY(InternalWindowStyleEx, DWORD, CFormComponent, CControlWinTraits::GetWndExStyle(0))
        PUBLIC_PROPERTY(InternalWindowStyleEx, FALSE)
        DEFINE_PROPERTY(ShowWindow, BOOL, CFormComponent, TRUE)
        PUBLIC_PROPERTY(ShowWindow, FALSE)
        formFont.AddProperty(_T("Font"), objprop);
    DEFINE_PROPERTY(Caption, CString, CFormComponent, "")
        DEFINE_PROPERTY(Visible, BOOL, CFormComponent, TRUE)
        DEFINE_WIN_PROPERTY(ClientEdge, CFormComponent)
        DEFINE_WIN_PROPERTY(HScroll, CFormComponent)
        DEFINE_WIN_PROPERTY(VScroll, CFormComponent)
        DEFINE_WIN_PROPERTY(MinimizeBox, CFormComponent)
        DEFINE_WIN_PROPERTY(MaximizeBox, CFormComponent)
        DEFINE_WIN_PROPERTY(SysMenu, CFormComponent)
        DEFINE_PROPERTY(CaptionBar, BOOL, CFormComponent, TRUE)
        DEFINE_WIN_PROPERTY(ModalFrame, CFormComponent)
        DEFINE_WIN_PROPERTY(TopMost, CFormComponent)
        DEFINE_WIN_PROPERTY(Transparent, CFormComponent)
        DEFINE_WIN_PROPERTY(MDIChild, CFormComponent)
        DEFINE_WIN_PROPERTY(ToolWindow, CFormComponent)
        DEFINE_WIN_PROPERTY(ContextHelp, CFormComponent)
        DEFINE_WIN_PROPERTY(ClipSiblings, CFormComponent)
        DEFINE_WIN_PROPERTY(ClipChildren, CFormComponent)
        DEFINE_WIN_PROPERTY(AcceptFiles, CFormComponent)
        DEFINE_WIN_PROPERTY(WindowEdge, CFormComponent)
        DEFINE_WIN_PROPERTY(ControlParent, CFormComponent)
        DEFINE_WIN_PROPERTY(StaticEdge, CFormComponent)
        DEFINE_WIN_PROPERTY(AppWindow, CFormComponent)
        //DEFINE_WIN_PROPERTY(Child, CFormComponent)
        DEFINE_PROPERTY(BorderStyle, WindowBorderStyle, CFormComponent, 0)

        DEFINE_PROPERTY(EnableLayout, BOOL, CFormComponent, FALSE)
        BEGIN_SUB_PROPERTY(_T("EnableLayout"), CFormComponent)
        DEFINE_SUB_PROPERTY(ShowHandle, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(NPositions, long, CFormComponent, 1)
        END_SUB_PROPERTY

        DEFINE_PROPERTY(Color, SystemColor, CFormComponent, bkColor)
        DEFINE_PROPERTY(ClientHeight, long, CFormComponent, 0)
        DEFINE_PROPERTY(ClientWidth, long, CFormComponent, 0)
        formIcon.AddProperty(_T("Icon"), objprop);
    DEFINE_PROPERTY_2(WindowClassStyle, DWORD, CFormComponent, classStyle)
        PUBLIC_PROPERTY(WindowClassStyle, FALSE)
        DEFINE_PROPERTY_2(WindowClass, BOOL, CFormComponent, FALSE)
        BEGIN_SUB_PROPERTY(_T("WindowClass"), CFormComponent)
        DEFINE_SUB_PROPERTY_2(ClassName, CString, CFormComponent, _T("NULL"))
        DEFINE_SUB_PROPERTY_2(CommonResID, CString, CFormComponent, _T(""))
        DEFINE_SUB_PROPERTY(CS_BYTEALIGNCLIENT, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_BYTEALIGNWINDOW, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_CLASSDC, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_DBLCLKS, BOOL, CFormComponent, TRUE)
        DEFINE_SUB_PROPERTY(CS_GLOBALCLASS, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_HREDRAW, BOOL, CFormComponent, TRUE)
        DEFINE_SUB_PROPERTY(CS_NOCLOSE, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_OWNDC, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_PARENTDC, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_SAVEBITS, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_VREDRAW, BOOL, CFormComponent, TRUE)
        DEFINE_SUB_PROPERTY(CS_IME, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(CS_DROPSHADOW, BOOL, CFormComponent, FALSE)
        END_SUB_PROPERTY

        //set window style WS_OVERLAPPED or WS_POPUP or WS_CHILD
        DEFINE_PROPERTY(WindowStyle, WindowStyle, CFormComponent, WS_OVERLAPPED)

        DEFINE_PROPERTY(Grid, BOOL, CFormComponent, TRUE)
        BEGIN_SUB_PROPERTY(_T("Grid"), CFormComponent)
        DEFINE_SUB_PROPERTY(GridWidth, long, CFormComponent, 8)
        DEFINE_SUB_PROPERTY(GridHeight, long, CFormComponent, 8)
        END_SUB_PROPERTY
        PUBLIC_PROPERTY(Grid, FALSE)
        PUBLIC_PROPERTY(Grid.GridWidth, FALSE)
        PUBLIC_PROPERTY(Grid.GridHeight, FALSE)

        DEFINE_PROPERTY(GSGuides, BOOL, CFormComponent, FALSE)
        BEGIN_SUB_PROPERTY(_T("GSGuides"), CFormComponent)
        DEFINE_SUB_PROPERTY(FromLeftToRight, BOOL, CFormComponent, TRUE)
        DEFINE_SUB_PROPERTY(FromTopToBottom, BOOL, CFormComponent, TRUE)
        DEFINE_SUB_PROPERTY(Moveable, BOOL, CFormComponent, FALSE)
        DEFINE_SUB_PROPERTY(OffsetX, long, CFormComponent, 0)
        DEFINE_SUB_PROPERTY(OffsetY, long, CFormComponent, 0)
        END_SUB_PROPERTY

        PUBLIC_PROPERTY(GSGuides, FALSE)
        PUBLIC_PROPERTY(FromLeftToRight, FALSE)
        PUBLIC_PROPERTY(FromTopToBottom, FALSE)
        PUBLIC_PROPERTY(Moveable, FALSE)
        PUBLIC_PROPERTY(OffsetX, FALSE)
        PUBLIC_PROPERTY(OffsetY, FALSE)


        DEFINE_PROPERTY_2(Localize, BOOL, CFormComponent, FALSE)
        BEGIN_SUB_PROPERTY(_T("Localize"), CFormComponent)
        DEFINE_SUB_PROPERTY(LocalizeName, CString, CFormComponent, name)
        DEFINE_SUB_PROPERTY(LangID, LangID, CFormComponent, GetUserDefaultLangID() & 0x3FF)
        END_SUB_PROPERTY

        DEFINE_PROPERTY(BaseCtrlID, long, CFormComponent, 1000)
        //DEFINE_PROPERTY(WndClient,ComponentName,CFormComponent,_T("NULL"))
//		DEFINE_PROPERTY(WndToolBar,ComponentName,CFormComponent,_T("NULL"))
//		DEFINE_PROPERTY(WndStatusBar,ComponentName,CFormComponent,_T("NULL"))
        //DEFINE_PROPERTY(Menu,ComponentName,CFormComponent,_T("NULL"))
}

//set window style WS_OVERLAPPED or WS_POPUP or WS_CHILD
void CFormComponent::set_WindowStyle(DWORD val)
{
    DWORD windowStyle = get_InternalWindowStyle();
    windowStyle = (windowStyle & ~(WS_CHILD | WS_POPUP)) | val;
    set_InternalWindowStyle(windowStyle);
    //AddUndo(this);
}

DWORD CFormComponent::get_WindowStyle()
{
    DWORD windowStyle = get_InternalWindowStyle();
    if ((windowStyle & WS_CHILD) == WS_CHILD)
        return WS_CHILD;

    if ((windowStyle & WS_POPUP) == WS_POPUP)
        return WS_POPUP;

    return WS_OVERLAPPED;
}

void CFormComponent::set_LangID(DWORD val)
{
    SET_PROP_VALUE(Localize.LangID, val)
        //AddUndo(this);
}

DWORD CFormComponent::get_LangID()
{
    return GET_PROP_VALUE(DWORD, Localize.LangID)
}

void CFormComponent::set_LocalizeName(CString val)
{
    SET_PROP_VALUE(Localize.LocalizeName, val)
        //AddUndo(this);
}

CString CFormComponent::get_LocalizeName()
{
    return GET_PROP_VALUE(LPCTSTR, Localize.LocalizeName)
}

void CFormComponent::set_EnableLayout(BOOL val)
{
    enableLayout = val;
    if (enableLayout == TRUE)
        InitLayout();
    //AddUndo(this);
}

BOOL CFormComponent::get_EnableLayout()
{
    return enableLayout;
}

void CFormComponent::set_ShowHandle(BOOL val)
{
    showHandle = val;
}

BOOL CFormComponent::get_ShowHandle()
{
    return showHandle;
}

void CFormComponent::set_NPositions(long val)
{
    if (val < 1)
        val = 1;
    nPositions = val;
    //SetNPositions(nPositions);
    ::UpdateProperty(_T("NPositions"));
}

long CFormComponent::get_NPositions()
{
    return nPositions;
}

void CFormComponent::set_ClientHeight(long val)
{
    if (val > 0 && val != clientHeight && GetState(csLoading) == 0)
    {
        clientHeight = val;
        ResizeClient(clientWidth, clientHeight);
        UpdateBoundsProp(GetBoundsRect());
    }
}

long CFormComponent::get_ClientHeight()
{
    return clientHeight;
}

void CFormComponent::set_ClientWidth(long val)
{
    if (val > 0 && clientWidth != val && GetState(csLoading) == 0)
    {
        clientWidth = val;
        ResizeClient(clientWidth, clientHeight);
        UpdateBoundsProp(GetBoundsRect());
    }
}

long CFormComponent::get_ClientWidth()
{
    return clientWidth;
}

void CFormComponent::set_BorderStyle(DWORD val)
{
    DWORD windowStyle = get_InternalWindowStyle();

    windowStyle = (windowStyle & ~((windowStyle & (WS_CAPTION == WS_CAPTION ? 0 : WS_BORDER)) | WS_THICKFRAME | WS_DLGFRAME)) | val;
    set_InternalWindowStyle(windowStyle);
    if (state.GetBit(csLoading) != TRUE)
    {
        UpdateProperty(_T("CaptionBar"));
    }
    SET_PROP_VALUE(BorderStyle, val)
}

DWORD CFormComponent::get_BorderStyle(void)
{
    return GET_PROP_VALUE(DWORD, BorderStyle)
}

void CFormComponent::set_CaptionBar(BOOL val)
{
    DWORD windowStyle = get_InternalWindowStyle();
    windowStyle = (windowStyle & ~(WS_CAPTION)) | (val == TRUE ? WS_CAPTION : 0);
    set_InternalWindowStyle(windowStyle);
    if (state.GetBit(csLoading) != TRUE)
    {
        UpdateProperty(_T("BorderStyle"));
    }
    SET_PROP_VALUE(CaptionBar, val)
}

BOOL CFormComponent::get_CaptionBar(void)
{
    return GET_PROP_VALUE(BOOL, CaptionBar)
}

void CFormComponent::set_Caption(CString str)
{
    caption = str;
    if (IsWindow())
        SetWindowText((LPCTSTR)caption);
}

CString CFormComponent::get_Caption(void)
{
    if (state.GetBit(csLoading))
    {
        caption = GET_PROP_VALUE(LPCTSTR, Caption)
    }
    return caption;
}

void CFormComponent::set_ShowWindow(BOOL val)
{
    if (::IsWindow((HWND)GetHandle()))
    {
        if (::IsWindowVisible((HWND)GetHandle()) != val)
        {
            ShowWindow(val == TRUE ? SW_SHOW : SW_HIDE);
            if (val == TRUE)
            {
                ShowProperties();
                PostEvent(evSetActiveForm, (Component*)this);
                fileName.SetCurDir();
                undo.EnableUndo();
            }
        }
    }
    showWindow = val;
    //AddUndo(this);
}

BOOL CFormComponent::get_ShowWindow(void)
{
    return showWindow;
}

BOOL CFormComponent::IsForm()
{
    return TRUE;
}

void CFormComponent::SetBoundsRect(CRect rc)
{
    Component::SetBoundsRect(rc);
    if (IsWindow() && IsIconic() == 0)
    {
        SetWindowPos(NULL, bounds.left, bounds.top, bounds.Width(), bounds.Height(),
            SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOCOPYBITS);
    }
}

CRect CFormComponent::GetBoundsRect(void)
{
    if (IsWindow() && GetState(csLoading) == FALSE && IsIconic() == 0)
        GetWindowRect(&bounds);
    else
        bounds = Component::GetBoundsRect();

    return bounds;
}

void CFormComponent::SaveAsTemplate(Component * frm, CString* templatePath)
{
    if (frm == this && templatePath)
    {
        templateFileName = *templatePath;
        SaveForm(this, soSaveAsTemplate);
        StopEvent(evSaveFormAsTemplate);
        templateFileName.Empty();
    }
}

void CFormComponent::SaveAsForm(Component * frm)
{
    if (frm == this)
    {
        fileName.Empty();
        SaveForm(this, soSaveAs);
        StopEvent(evSaveFormAsTemplate);
    }
}

void CFormComponent::SaveForm(Component * frm, SaveOperation operation)
{
    if (frm == this)
    {
        try
        {
            if (operation == soSave && undo.IsModified() == FALSE)
                return;

            if (fileName.GetPath().IsEmpty() || fileName.GetTitle().IsEmpty() || operation == soSaveAs)
            {
                static _TCHAR Filter[] = _T("Form Files (*.wff)\0*.wff\0");
                CPath fn((LPCTSTR)get_Name());
                fn.SetExt(_T("wff"));
                CFileDialog filedlg(FALSE, _T("*.wff"), (LPCTSTR)fn, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, Filter);
                if (filedlg.DoModal(GetDesktopWindow()) != IDOK)
                    return;

                fileName = filedlg.m_szFileName;
            }

            {
                CXMLDOMDocument2	Doc;
                GenerateXML(Doc);

                if (GenerateCode(operation) == FALSE)
                    return;
                if (operation != soSaveAsTemplate)
                {
                    fileName.SetExt(_T("wff"));
                    fileName.SetCurDir();
                    Doc.Save((LPCTSTR)fileName);
                    codeGen.SaveHeader((LPCTSTR)fileName);
                    codeGen.SaveSource((LPCTSTR)fileName);
                    undo.Reset();
                    AddUndo(this);
                    SendEvent(evFormSaved, static_cast<Component *>(this), (LPCTSTR)fileName);
                }
                else
                {
                    templateFileName.SetExt(_T("wff"));
                    Doc.Save((LPCTSTR)templateFileName);
                    codeGen.SaveHeader((LPCTSTR)templateFileName);
                    codeGen.SaveSource((LPCTSTR)templateFileName);

                }
            }

        }
        catch (CComException *pE)
        {
            pE->ReportError();
            pE->Delete();
        }
        catch (...)
        {
        }
    }
}

BOOL CFormComponent::GenerateXML(CXMLDOMDocument2 & Doc)
{
    //Doc = CDOMDocument40Class::CreateXMLDOMDocument2();
    Doc = CDOMDocument30Class::CreateXMLDOMDocument2();
    CXMLDOMNode formNode(Doc.CreateNode((long)NODE_ELEMENT, _T("Form"), NULL));
    Doc.AppendChild(formNode);
    CXMLDOMProcessingInstruction ProcessingInstruction(Doc.CreateProcessingInstruction(_T("xml"), _T("version='1.0'")));
    Doc.InsertBefore(ProcessingInstruction, (IXMLDOMNode*)formNode);
    objprop.Save(formNode);
    CXMLDOMNode controls(Doc.CreateNode((long)NODE_ELEMENT, _T("Controls"), NULL));
    formNode.AppendChild(controls);
    designer->GetComponents()->Save(controls);
    return TRUE;
}

void CFormComponent::LoadForm(Component *mainForm, Component ** formPtr, LPCTSTR formFileName, BOOL _fromTemplate)
{
    //try
    //{
        if (*formPtr != this)
            return;
        fromTemplate = _fromTemplate;
        ATLASSERT(formFileName);

        fileName = formFileName;
        fileName.SetExt(_T("wff"));
        fileName.SetCurDir();
        CXMLDOMDocument2	Doc;
        Doc = CDOMDocument30Class::CreateXMLDOMDocument2();
        if (Doc.Load((LPCTSTR)fileName) != FALSE)
        {
            CXMLDOMNode formNode(Doc.SelectSingleNode(_T("Form")));
            CXMLDOMNode controlNode(formNode.SelectSingleNode(_T("Controls")));
            SetState(csLoading, TRUE);
            objprop.Load(formNode);
            CreateComponent(mainForm);
            if (controlNode != NULL)
                designer->GetComponents()->Load(controlNode);
            ComponentCreated();
            SetState(csLoading, FALSE);

            if (codeGen.LoadHeader((LPCTSTR)fileName) == TRUE)
                codeGen.LoadSource((LPCTSTR)fileName);

            designer->MoveWindow(0, 0, clientWidth, clientHeight);
            AddUndo(this);

            PostEvent(evShowGrid, NULL, get_Grid());
            PostEvent(evSetGridSizeX, NULL, get_GridWidth());
            PostEvent(evSetGridSizeY, NULL, get_GridHeight());
        }
        else
        {
            ::MessageBox(NULL, _T("Error opening form"), _T("WTLBuilder"), MB_OK);
            enableClose = TRUE;
            if (IsWindow() != 0)
                DestroyWindow();
            else
                delete this;
            *formPtr = NULL;

        }
    //}
    //catch (CComException *pE)
    //{
    //    pE->ReportError();
    //    pE->Delete();
    //    enableClose=TRUE;
    //    if(IsWindow()!=0)
    //        DestroyWindow();	
    //    else
    //        delete this;
    //    *formPtr=NULL;
    //}
    //catch(...)
    //{
    //    ::MessageBox(NULL,_T("Error opening form"),_T("WTLBuilder"),MB_OK);
    //    enableClose=TRUE;
    //    if(IsWindow()!=0)
    //        DestroyWindow();	
    //    else
    //        delete this;
    //    *formPtr=NULL;
    //}
}

BOOL CFormComponent::LoadFromString(const CString &str, BOOL loadForm)
{
    CXMLDOMDocument2	Doc;
    //Doc = CDOMDocument40Class::CreateXMLDOMDocument2();
    Doc = CDOMDocument30Class::CreateXMLDOMDocument2();
    if (Doc.LoadXML((LPCTSTR)str) == FALSE)
        return FALSE;
    CXMLDOMNode formNode(Doc.SelectSingleNode(_T("Form")));
    CXMLDOMNode controlNode(formNode.SelectSingleNode(_T("Controls")));
    if (loadForm == TRUE)
    {
        SetState(csLoading, TRUE);
        objprop.Load(formNode);
    }

    if (controlNode != NULL)
        designer->GetComponents()->Load(controlNode);

    if (loadForm == TRUE)
    {
        SetState(csCreating, FALSE);
        ComponentCreated();
        SetState(csLoading, FALSE);
    }

    designer->BringToTop();

    return TRUE;
}

void CFormComponent::CloseForm(Component * cmp, BOOL * remove)
{
    if (cmp == this)
    {

        if (undo.IsModified() == TRUE)
        {
            CString msg;
            CPath fn((fileName.GetPath().IsEmpty() ? (LPCTSTR)get_Name() : (LPCTSTR)fileName));
            fn.SetExt(_T("wff"));

            msg.Format(_T("Save changes to %s ?"), (LPCTSTR)fn);
            int ret = AtlMessageBox((HWND)GetHandle(), (LPCTSTR)msg, _T("WTLBuilder"), MB_YESNOCANCEL | MB_ICONQUESTION);
            if (ret == IDYES)
            {
                SaveForm(this, soSave);
            }
            else
                if (ret == IDCANCEL)
                {
                    *remove = FALSE;
                    StopEvent(evCloseForm);
                    return;
                }
        }

        enableClose = TRUE;
        if (IsWindow())
        {
            DestroyWindow();
            delete this;
        }
    }
}

CString CFormComponent::GetFileName()
{
    return (LPCTSTR)fileName;
}

void CFormComponent::GetFormFileName(Component * cmp, CString* formFileName)
{
    if (cmp == this && formFileName)
    {
        *formFileName = (LPCTSTR)fileName;
        StopEvent(evGetFormFileName);
    }
}

BOOL CFormComponent::GenerateCode(SaveOperation operation)
{
    CMsgPump pump;

    if (fileName.IsFilePath() && operation == soSave)//load last source code changes
    {
        codeGen.LoadHeader((LPCTSTR)fileName);
        codeGen.LoadSource((LPCTSTR)fileName);
    }

    BOOL retFlag;
    codeGen.AddVar(_T("FILENAME"), fileName.GetTitle());
    codeGen.AddVar(_T("CLASSNAME"), get_Name());
    codeGen.FormatForm();
    VARIANT params[2];
    VARIANT retVal;
    params[1].vt = VT_DISPATCH;
    params[1].pdispVal = (IDispDynImpl<Component> *)this;
    CString cmpName;
    CString cmpPage;
    CString funcName;
    ExtractName(GetClassName(), cmpPage, cmpName);
    cmpPage = cmpPage.Trim();
    cmpName = cmpName.Trim();
    funcName.Format(_T("%s_%s"), (LPCTSTR)cmpPage, (LPCTSTR)cmpName);
    params[0].vt = VT_DISPATCH;
    params[0].pdispVal = (IDispDynImpl<Component> *)this;//params[1].pdispVal;
    SendEvent(evInvokeFunc, (BSTR)CComBSTR((LPCTSTR)funcName), &params[0], 1, &retVal, &retFlag);
    if (retFlag == FALSE)
    {
        CString errMsg;
        errMsg.Format("Error while generating form code. See %s script function.", (LPCTSTR)funcName);
        PostEvent(evOutput, ErrorMsg, (LPCTSTR)errMsg);
        return FALSE;
    }

    for (int i = 0; i < components.GetCount(); i++)
    {
        BOOL generate = components.GetAt(i)->GetProperty()->GetPropValue<BOOL>(_T("Generate"));
        if (generate == FALSE)
            continue;
        ExtractName(components.GetAt(i)->GetClassName(), cmpPage, cmpName);
        funcName.Format(_T("%s_%s"), (LPCTSTR)cmpPage, (LPCTSTR)cmpName);
        params[0].vt = VT_DISPATCH;
        params[0].pdispVal = (IDispDynImpl<Component> *)components.GetAt(i);
        params[1].vt = VT_DISPATCH;
        params[1].pdispVal = (IDispDynImpl<Component> *)this;
        SendEvent(evInvokeFunc, (BSTR)CComBSTR((LPCTSTR)funcName), &params[0], 2, &retVal, &retFlag);
        if (retFlag == FALSE)
        {
            CString errMsg;
            errMsg.Format("Error while generating control code. See %s script function.", (LPCTSTR)funcName);
            PostEvent(evOutput, ErrorMsg, (LPCTSTR)errMsg);
            return FALSE;
        }
    }

    if (operation == soSaveAsTemplate)
        codeGen.RemoveFormName(get_Name());
    return TRUE;
}

void CFormComponent::GenerateLocFile(LPCTSTR fileName)
{
    CString localizeName = get_LocalizeName();
    if (localizeName.IsEmpty() == TRUE)
    {
        MessageBox("Error creating localization file.\nSpecify LocalizeName form property first.", "WTLBuilder", MB_OK | MB_ICONERROR);
        return;
    }
    BOOL retFlag;
    VARIANT params[2];
    VARIANT retVal;
    params[1].vt = VT_DISPATCH;
    params[1].pdispVal = this;
    CString cmpName;
    CString cmpPage;
    CString funcName;
    ExtractName(GetClassName(), cmpPage, cmpName);
    funcName.Format(_T("%s_%sLocalize"), (LPCTSTR)cmpPage, (LPCTSTR)cmpName);
    params[0].vt = VT_DISPATCH;
    params[0].pdispVal = params[1].pdispVal;
    SendEvent(evInvokeFunc, (BSTR)CComBSTR((LPCTSTR)funcName), &params[0], 1, &retVal, &retFlag);
    if (retFlag == FALSE)
        return;

    for (int i = 0; i < components.GetCount(); i++)
    {
        BOOL generate = components.GetAt(i)->GetProperty()->GetPropValue<BOOL>(_T("Generate"));
        if (generate == FALSE)
            continue;

        BOOL  localize = components.GetAt(i)->GetProperty()->GetPropValue<BOOL>(_T("Localize"));
        if (localize == FALSE)
            continue;

        ExtractName(components.GetAt(i)->GetClassName(), cmpPage, cmpName);
        funcName.Format(_T("%s_%sLocalize"), (LPCTSTR)cmpPage, (LPCTSTR)cmpName);
        params[0].vt = VT_DISPATCH;
        params[0].pdispVal = (IDispDynImpl<Component> *)components.GetAt(i);
        SendEvent(evInvokeFunc, (BSTR)CComBSTR((LPCTSTR)funcName), &params[0], 2, &retVal, &retFlag);
        if (retFlag == FALSE)
            return;
    }
    codeGen.SaveLocalize(fileName);
}

DWORD CFormComponent::get_InternalWindowStyle()
{
    return GET_PROP_VALUE(DWORD, InternalWindowStyle)
}

void CFormComponent::set_InternalWindowStyle(DWORD s)
{
    SET_PROP_VALUE(InternalWindowStyle, s)
        AddUndo(this);
}

DWORD CFormComponent::get_InternalWindowStyleEx()
{
    return GET_PROP_VALUE(DWORD, InternalWindowStyleEx)
}

void CFormComponent::set_InternalWindowStyleEx(DWORD s)
{
    SET_PROP_VALUE(InternalWindowStyleEx, s)
        AddUndo(this);
}

void CFormComponent::set_Visible(BOOL val)
{
    visible = val;
    AddUndo(this);
}

BOOL CFormComponent::get_Visible()
{
    return visible;
}

void CFormComponent::set_Color(COLORREF val)
{
    bkColor = val;
    if (IsWindow())
        RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

COLORREF CFormComponent::get_Color()
{
    return bkColor;
}

void CFormComponent::GetDialogRect(LPRECT r)
{
    GetClientRect(r);
    //if (r->right < m_sizeAll.cx)
    //{
    //	r->right = m_sizeAll.cx;
    //}
    //if (r->bottom < m_sizeAll.cy)
    //{
    //	r->bottom = m_sizeAll.cy;
    //}
}

void CFormComponent::GetOffset(LPPOINT offset)
{
    //	*offset = m_ptOffset;
}

/*#define DOLAYOUT(side)\
    if(layout->get_AttachForm())\
    AttachForm(component->GetHandle(),side);\
    if(layout->get_AttachOppositeForm())\
    AttachOppositeForm(component->GetHandle(),side);\
    if(layout->get_AttachChild())\
{\
    temp=GetComponents()->Find(layout->get_Child());\
    if(temp)\
    AttachWidget(component->GetHandle(),side,temp->GetHandle());\
}\
    if(layout->get_AttachOppositeChild())\
{\
    temp=GetComponents()->Find(layout->get_Child());\
    if(temp)\
    AttachOppositeWidget(component->GetHandle(),side,temp->GetHandle());\
}\
    if(layout->get_AttachPosition())\
    AttachPosition(component->GetHandle(),side,layout->get_Position());\
    if(layout->get_AttachSelf())\
    AttachSelf(component->GetHandle(),side);\
    if(layout->get_AttachNone())\
    AttachNone(component->GetHandle(),side);
*/
void CFormComponent::DefineLayout()
{
    /*	UINT _id;
        _controls.RemoveAll();

        for(int i=0; i < GetComponents()->GetCount();i++)
        {
            Component *temp=NULL;
            Component * component=GetComponents()->GetAt(i);

            if(component->IsControl()==FALSE)
                continue;

            _id=component->get_UniqueID();
            _controls.Add(_id);
            HWND wnd=component->GetHandle();
            Unattach(wnd);
            if(component->get_Layout()==FALSE)
                continue;

            CLayout * layout=component->get_leftLayout();
            DOLAYOUT(ATTACH_LEFT)

                layout=component->get_topLayout();
            DOLAYOUT(ATTACH_TOP)

                layout=component->get_rightLayout();
            DOLAYOUT(ATTACH_RIGHT)

                layout=component->get_bottomLayout();
            DOLAYOUT(ATTACH_BOTTOM)

                layout=component->get_hCenterLayout();
            DOLAYOUT(ATTACH_HCENTER)

                layout=component->get_vCenterLayout();
            DOLAYOUT(ATTACH_VCENTER)
        }
        _id=0;
        _controls.Add(_id);
        _controlsToClip=_controls.GetData();
        if(enableLayout==TRUE)
            DoLayout();
    */
}

LRESULT CFormComponent::OnUpdateLayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    //	if(GetState(csLoading)==FALSE && GetState(csCreating)==FALSE)
    //		DefineLayout();
    return 0;
}

void CFormComponent::InitLayout()
{
    //	RECT r;
    //	GetClientRect(&r);
    //	_minClientSize.cx = (r.right-r.left);
    //	_minClientSize.cy = (r.bottom-r.top);
    //	_prevClientSize = _minClientSize;
    //	GetWindowRect(&r);
    //	_minWindowSize.cx = (r.right-r.left);
    //	_minWindowSize.cy = (r.bottom-r.top);
    //	DefineLayout();
}

void CFormComponent::UnAttach(Component * component)
{
    //	if(component->IsControl() && IsWindow())
    //		Unattach(component->GetHandle());
}

void CFormComponent::set_GSGuides(BOOL val)
{
    designer->ShowGSGuides(val);
    RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
    //AddUndo(this);
}

BOOL CFormComponent::get_GSGuides()
{
    return designer->IsShowGSGuides();
}

void CFormComponent::set_FromLeftToRight(BOOL val)
{
    designer->SetFromLeftToRight(val);
    RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
    //AddUndo(this);
}

BOOL CFormComponent::get_FromLeftToRight()
{
    return designer->GetFromLeftToRight();
}

void CFormComponent::set_FromTopToBottom(BOOL val)
{
    designer->SetFromTopToBottom(val);
    RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
}

BOOL CFormComponent::get_FromTopToBottom()
{
    return designer->GetFromTopToBottom();
}

void CFormComponent::ShowGrid(Component * form, BOOL val)
{
    if (form == this)
    {
        StopEvent(evShowGrid);
        set_Grid(val);
    }
}

void CFormComponent::set_Grid(BOOL val)
{
    designer->ShowGrid(val);
    RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
}

BOOL CFormComponent::get_Grid()
{
    return designer->IsShowGrid();
}

void CFormComponent::SetGridWidth(Component * form, long val)
{
    if (form == this)
    {
        StopEvent(evSetGridSizeX);
        set_GridWidth(val);
    }
}

void CFormComponent::set_GridWidth(long cx)
{
    if (designer->GetGridSize().cx != cx)
    {
        //if (GetState(csLoading))
        //{
        //	SendEvent(evSetGridSizeX, NULL, cx);
        //}

        designer->GetGridSize().cx = cx;
        RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
    }
}

long CFormComponent::get_GridWidth()
{
    return designer->GetGridSize().cx;
}

void CFormComponent::SetGridHeight(Component * form, long val)
{
    if (form == this)
    {
        StopEvent(evSetGridSizeY);
        set_GridHeight(val);
    }
}

void CFormComponent::set_GridHeight(long cy)
{
    if (designer->GetGridSize().cy != cy)
    {
        designer->GetGridSize().cy = cy;
        RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
    }
}

long CFormComponent::get_GridHeight()
{
    return designer->GetGridSize().cy;
}

void CFormComponent::set_OffsetX(long val)
{
    CPoint offset = designer->GetOffset();
    if (offset.x != val)
    {
        offset.x = val;
        designer->SetOffset(offset);
        RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
    }
}

long CFormComponent::get_OffsetX()
{
    return designer->GetOffset().x;
}

void CFormComponent::set_OffsetY(long val)
{
    CPoint offset = designer->GetOffset();
    if (offset.y != val)
    {
        offset.y = val;
        designer->SetOffset(offset);
        RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
    }
}

long CFormComponent::get_OffsetY()
{
    return designer->GetOffset().y;
}

void CFormComponent::set_Moveable(BOOL val)
{
    designer->SetMoveableGSGuides(val);
}

BOOL CFormComponent::get_Moveable()
{
    return designer->IsMoveableGSGuides();
}

void CFormComponent::MakeGoldenSectionWidht(Component *from)
{
    if (from != this)
        return;
    StopEvent(evGoldenSectionWidth);

    if (designer->GetComponents()->GetSelCount())
    {
        designer->GetComponents()->MakeGoldenSectionWidht();
        return;
    }

    double delta = get_ClientHeight();
    delta = (delta / 0.382)*0.618;
    set_ClientWidth(_round(delta));
}

void CFormComponent::MakeGoldenSectionHeight(Component *from)
{
    if (from != this)
        return;
    StopEvent(evGoldenSectionHeight);
    if (designer->GetComponents()->GetSelCount())
    {
        designer->GetComponents()->MakeGoldenSectionHeight();
        return;
    }
    double delta = get_ClientWidth();
    delta = (delta / 0.382)*0.618;
    set_ClientHeight(_round(delta));
}

void CFormComponent::OnImageChange(CImage * image)
{
    if (image)
    {
        if ((HICON)*image)
            ::SendMessage((HWND)GetHandle(), WM_SETICON, ICON_SMALL, (LPARAM)(HICON)*image);
    }
    //AddUndo(this);
    //SetModified();
}

void CFormComponent::set_BaseCtrlID(long val)
{
    if (idBase != val)
    {
        idBase = val;
        //  SetModified();
        //AddUndo(this);
    }
}

long CFormComponent::get_BaseCtrlID(void)
{
    return idBase;
}

void CFormComponent::AddUndo(Component * form)
{
    if (form == this && GetState(csLoading) == FALSE && GetState(csCreating) == FALSE)
    {
        //StopEvent(evAddUndo);

        CXMLDOMDocument2 Doc;
        GenerateXML(Doc);
        undo.Add(Doc.GetXml());
        SetModified();
    }
}

void CFormComponent::UndoChanges(Component * form)
{
    if (form == this)
    {
        //StopEvent(evUndo);
        CMsgPump pump;
        CString undodata = undo.Get();
        if (undodata.GetLength())
        {
            designer->GetComponents()->RemoveAll();
            LoadFromString(undodata, TRUE);
            RedrawWindow(NULL, NULL, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
        }
    }
}

void CFormComponent::EditCopy(Component * form, Component *comp)
{
    if (form == this)
    {
        CMsgPump pump;
        StopEvent(evCopy);
        FreeClipboard();
        if (comp == NULL || designer->GetComponents()->GetSelCount())
            clipboard = designer->GetComponents()->Clone(TRUE);
        else
            clipboard = designer->GetComponents()->Clone(comp);
        AddUndo(this);
    }
}

void CFormComponent::EditCut(Component * form, Component *comp)
{
    if (form == this)
    {
        CMsgPump pump;
        StopEvent(evCut);
        FreeClipboard();
        if (comp == NULL || designer->GetComponents()->GetSelCount())
            clipboard = designer->GetComponents()->Clone(TRUE);
        else
        {
            clipboard = designer->GetComponents()->Clone(comp);
            comp->Selected = TRUE;
            comp->FirstSelected = TRUE;
        }
        designer->GetComponents()->Delete();
        AddUndo(this);
    }
}

void CFormComponent::EditPaste(Component * form, Component *comp, CPoint * downPoint)
{
    if (form == this)
    {
        StopEvent(evPaste);
        if (clipboard)
        {
            CMsgPump pump;
            designer->GetComponents()->Paste(clipboard, comp, downPoint);
            AddUndo(this);
        }
    }
}

void CFormComponent::EditDelete(Component * form)
{
    if (form == this)
    {
        StopEvent(evDelete);
        if (designer->GetComponents()->GetSelCount())
        {
            CMsgPump pump;
            designer->GetComponents()->Delete();
            AddUndo(this);
            ::RedrawWindow((HWND)GetHandle(), NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
        }
    }
}

HANDLE CFormComponent::GetHandle(void)
{
    return m_hWnd;
}

void CFormComponent::TabIndex(Component * form, BOOL val)
{
    if (form == this)
    {
        StopEvent(evTabIndex);
        GetDesigner()->SetTabIndexMode(val);
    }
}

void CFormComponent::set_WndClient(CString val)
{
    if (viewCtrl != val)
    {
        if (viewCtrl != CComponentListEdit::GetNoneStr())
        {
            Component * oldComp = Find(viewCtrl);
            if (oldComp)
                oldComp->Changed.Reset();
        }

        Component * temp = Find(val);
        if (temp != NULL)
        {
            ::SetParent((HWND)temp->GetHandle(), (HWND)GetHandle());
            temp->set_ParentName(get_Name());
            temp->SetComponentParent(this);
            m_hWndClient = (HWND)temp->GetHandle();
            temp->Changed.SetObject(this);
            temp->Changed.SetMethod(&CFormComponent::ViewCtrlChanged);
            UpdateLayout();
            designer->SetWindowPos(HWND_TOP, 0, 0, clientWidth, clientHeight, SWP_FRAMECHANGED | SWP_NOCOPYBITS | SWP_SHOWWINDOW);
        }
        else
        {
            viewCtrl = CComponentListEdit::GetNoneStr();
            m_hWndClient = NULL;
            return;
        }
        viewCtrl = val;
    }
}

void CFormComponent::ViewCtrlChanged(Component* comp)
{
    if (comp->GetState(csDeleting))
    {
        viewCtrl = CComponentListEdit::GetNoneStr();
        m_hWndClient = NULL;
    }
    else
        viewCtrl = comp->get_Name();
}

CString CFormComponent::get_WndClient()
{
    CComponentListEdit::SetComponentKind(_T(""));
    return viewCtrl;
}

/*void CFormComponent::set_WndToolBar(CString val)
{
    if(toolBarCtrl!=val)
    {
        if(toolBarCtrl!=CComponentListEdit::GetNoneStr())
        {
            Component * oldComp=Find(toolBarCtrl);
            if(oldComp)
                oldComp->Changed.Reset();
        }

        Component * temp=Find(val);
        if(temp!=NULL && temp->GetComponetKind()==_T("TOOLBAR"))
        {
            ::SetParent((HWND)temp->GetHandle(),(HWND)GetHandle());
            temp->set_ParentName(get_Name());
            temp->SetComponentParent(this);
            temp->Changed.SetObject(this);
            temp->Changed.SetMethod(&CFormComponent::ToolBarChanged);
            m_hWndToolBar=(HWND)temp->GetHandle();
            UpdateLayout();
        }
        else
        {
            toolBarCtrl=CComponentListEdit::GetNoneStr();
            m_hWndToolBar=NULL;
            return;
        }
        toolBarCtrl=val;
    }
}*/

void CFormComponent::ToolBarChanged(Component* comp)
{
    //	if(comp->GetState(csDeleting))
    //	{
    //		toolBarCtrl=CComponentListEdit::GetNoneStr();
    //		m_hWndToolBar=NULL;
    //	}
    //	else
    //		toolBarCtrl=comp->get_Name();
}

//CString CFormComponent::get_WndToolBar()
//{
//	CComponentListEdit::SetComponentKind(_T("TOOLBAR"));
//	return toolBarCtrl;
//}

/*void CFormComponent::set_WndStatusBar(CString val)
{
    if(statusBarCtrl!=val)
    {
        if(statusBarCtrl!=CComponentListEdit::GetNoneStr())
        {
            Component * oldComp=Find(statusBarCtrl);
            if(oldComp)
                oldComp->Changed.Reset();
        }

        Component * temp=Find(val);
        if(temp!=NULL && temp->GetComponetKind()==_T("STATUSBAR"))
        {
            ::SetParent((HWND)temp->GetHandle(),(HWND)GetHandle());
            temp->set_ParentName(get_Name());
            temp->SetComponentParent(this);
            temp->Changed.SetObject(this);
            temp->Changed.SetMethod(&CFormComponent::StatusBarChanged);
            m_hWndStatusBar=(HWND)temp->GetHandle();
            UpdateLayout();
        }
        else
        {
            statusBarCtrl=CComponentListEdit::GetNoneStr();
            m_hWndStatusBar=NULL;
            return;
        }
        statusBarCtrl=val;
        //AddUndo(this);
    }
}*/

void CFormComponent::StatusBarChanged(Component* comp)
{
    //	if(comp->GetState(csDeleting))
    //	{
    //		statusBarCtrl=CComponentListEdit::GetNoneStr();
    //		m_hWndStatusBar=NULL;
    //	}
    //	else
    //		statusBarCtrl=comp->get_Name();
}

//CString CFormComponent::get_WndStatusBar()
//{
//	CComponentListEdit::SetComponentKind(_T("STATUSBAR"));
///	return statusBarCtrl;
//}

/*void CFormComponent::set_Menu(CString val)
{
    if(menu!=val)
    {
        Component * temp = NULL;
        if(menu!=CComponentListEdit::GetNoneStr())
        {
            Component * oldComp=Find(menu);
            if(oldComp)
                oldComp->Changed.Reset();
        }

        temp=Find(val);

        if(temp!=NULL && temp->GetComponetKind()==_T("MENU"))
        {
            temp->set_ParentName(get_Name());
            temp->SetComponentParent(this);
            SetMenu((HMENU)temp->GetHandle());
            DrawMenuBar();
            UpdateLayout();
            temp->Changed.SetObject(this);
            temp->Changed.SetMethod(&CFormComponent::MenuChanged);
        }
        else
        {
            menu=CComponentListEdit::GetNoneStr();
            SetMenu(NULL);
            return;
        }
        menu=val;
    }
}*/

void CFormComponent::MenuChanged(Component* comp)
{
    //if(comp->GetState(csDeleting))
    //{
    //	menu=CComponentListEdit::GetNoneStr();
    //	SetMenu(NULL);		
    //	comp->Changed.Reset();
    //}
    //else
    //	menu=comp->get_Name();
}

/*CString CFormComponent::get_Menu()
{
    CComponentListEdit::SetComponentKind(_T("MENU"));
    return menu;
}*/

void CFormComponent::SetFormFileName(Component* comp, LPTSTR val)
{
    if (comp == this)
    {
        fileName = val;
        StopEvent(evSetFormFileName);
    }
}

void CFormComponent::IsFormChanged(Component* comp, BOOL * val)
{
    if (comp == this)
    {
        *val = undo.IsModified();
        StopEvent(evIsFormChanged);
    }
}