// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "Command.h"
#include "component.h"
#include "FormComponent.h"
#include <GDIUtil.h>
#include <_util.h>

typedef CSimpleArray<CString> CStringArray;
#define CTRL_ID_BASE 1000
#define DEF_PARENT_NAME _T("m_hWnd")

#define NONCONTROLW 29
#define NONCONTROLH 29

class CFreeze
{
    BOOL &f;
public:
    CFreeze(BOOL &_f) :f(_f) { f = TRUE; }
    ~CFreeze() { f = FALSE; }
};
//////////////////////////////////////////////////////////////////////////
static void DrawBox(CDC & dc, CPoint at, COLORREF color = RGB(0x7F, 0x7F, 0x7F))
{
    CPenEx Pen(PS_INSIDEFRAME, 1, RGB(0, 0, 0));
    CSel _Pen(dc, Pen);

    CBrushEx Brush(color);
    CSel _Brush(dc, Brush);

    dc.Rectangle(at.x - BOX_SIDE, at.y + BOX_SIDE, at.x + BOX_SIDE, at.y - BOX_SIDE);
}

static void DrawEmptiBox(CDC & dc, CRect rc, COLORREF color = RGB(0, 0, 0x7F))
{
    CPenEx Pen(PS_INSIDEFRAME, 1, color);
    CSel _Pen(dc, Pen);
    CSel _Brush(dc, NULL_BRUSH);
    dc.Rectangle(rc.left, rc.top, rc.right, rc.bottom);
}
//////////////////////////////////////////////////////////////////////////
BOOL PtInBox(CPoint &at, CPoint & pt)
{
    CRect rc(at.x - BOX_SIDE, at.y - BOX_SIDE, at.x + BOX_SIDE, at.y + BOX_SIDE);
    return PtInRect(rc, pt);
}
//////////////////////////////////////////////////////////////////////////
class CUniqueID
{
    long uniqueID;
public:
    CUniqueID():uniqueID(-2)
    {
    }

    long Get()
    {
        return ++uniqueID;
    }

    operator long() { return Get(); }
};

static CUniqueID UniqueID;
//////////////////////////////////////////////////////////////////////////
Component::Component(LPCTSTR _className) :state(1), pressed(FALSE),
className(_className), designer(NULL), Parent(NULL), objprop(_className, this), parentName(DEF_PARENT_NAME),
defaultSize(DEF_SIZE_W, DEF_SIZE_H), bounds(0, 0, 40, 40), minRC(0, 0, 0, 0), tabIndex(-1), enableTabIndex(TRUE), uniqueID(UniqueID)
{
    SetState(csCreating);
}

Component::Component(const Component & comp) :
    objprop(comp.objprop),
    pressed(comp.pressed),
    deltaPoint(comp.deltaPoint),
    name(comp.name),
    designer(comp.designer),
    Parent(comp.Parent),
    state(comp.state),
    className(comp.className),
    bounds(comp.bounds),
    parentName(comp.parentName),
    uniqueID(comp.uniqueID),
    defaultSize(comp.defaultSize),
    tabIndex(comp.tabIndex),
    enableTabIndex(comp.enableTabIndex)

{

}

Component::~Component(void)
{
    UnRegisterEvent(this);
}

void Component::SetDefaultSize(int cx, int cy)
{
    defaultSize.cx = cx;
    defaultSize.cy = cy;
}

BOOL Component::CreateComponent(Component *_Parent)
{
    SetComponentParent(_Parent);
    if (_Parent)
        designer = Parent->GetDesigner();

    if (IsControl() == FALSE && IsForm() == FALSE)
    {
        SetDefaultSize(NONCONTROLW, NONCONTROLH);
        bounds.right = bounds.left + NONCONTROLW;
        bounds.bottom = bounds.top + NONCONTROLH;
        return TRUE;
    }
    return FALSE;
}

void Component::DeleteComponent()
{
    SetState(csDeleting);
    RemoveProperties();
    if (IsControl())
    {
        GetParentForm()->SetModified();
        GetParentForm()->UnAttach(this);
    }
    //changed(this);
    delete this;
}

CProperties * Component::GetProperty()
{
    return &objprop;
}

Components *  Component::GetComponents()
{
    if (designer)
        return designer->GetComponents();
    return NULL;
}

void Component::InitProperty(void)
{
    DEFINE_PROPERTY(Name, CString, Component, name)
        DEFINE_PROPERTY(ParentName, CString, Component, DEF_PARENT_NAME)
        PUBLIC_PROPERTY(ParentName, FALSE)

        DEFINE_PROPERTY(UniqueID, long, Component, uniqueID)
        PUBLIC_PROPERTY(UniqueID, FALSE)

        DEFINE_PROPERTY(Left, long, Component, bounds.left)
        DEFINE_PROPERTY(Width, long, Component, bounds.right)
        DEFINE_PROPERTY(Top, long, Component, bounds.top)
        DEFINE_PROPERTY(Height, long, Component, bounds.bottom)
        DEFINE_PROPERTY_2(Generate, BOOL, Component, TRUE)

        if (IsForm() == FALSE)
            DEFINE_PROPERTY_2(IncludePath, CString, Component, _T(""))

            if (IsControl())
            {
                DEFINE_PROPERTY(TabIndex, long, Component, -1)
                PUBLIC_PROPERTY(TabIndex, FALSE)
                DEFINE_PROPERTY(Selected, BOOL, Component, FALSE)
                PUBLIC_PROPERTY(Selected, FALSE)
                DEFINE_PROPERTY(FirstSelected, BOOL, Component, FALSE)
                PUBLIC_PROPERTY(FirstSelected, FALSE)
            }
}

void Component::ShowProperties(void)
{
    ::ShowProperties(&objprop);
}

void Component::ComponentCreated()
{
    objprop.Update();
}

void Component::set_Name(CString n)
{
    if (n != name)
    {
        if (IsControl() == TRUE && Find(n) != NULL)
            return;
        name = n;
        if (n.IsEmpty())
            name = MakeDefaultName();

        CCodeGenerator * code = (CCodeGenerator *)get_Code();
        if (code)
            code->AddVar(_T("CLASSNAME"), name);
        SetModified();
        if (state.GetBit(csCreating) || state.GetBit(csLoading))
            return;
        ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
    }
}

CString Component::get_Name(void)
{
    if (state.GetBit(csLoading) && state.GetBit(csCloning) == FALSE)
    {
        name = GET_PROP_VALUE(CString, Name)
    }

    if (name.IsEmpty())
    {
        name = MakeDefaultName();
        SET_PROP_VALUE(Name, name)
        if (state.GetBit(csCreating) == FALSE)
            SetModified();
    }
    return name;
}

void Component::set_ParentName(CString str)
{
    parentName = str;
    if (state.GetBit(csLoading))
    {
        if (str.IsEmpty() || str.Compare(DEF_PARENT_NAME) == 0)
            Parent = designer->GetParentForm();
        else
        {
            Parent = designer->GetComponents()->Find(CString(str));
            if (Parent == NULL)
            {
                Parent = designer->GetParentForm();
                parentName = Parent->get_Name();
            }
        }
    }
    else
    {
        SetModified();
    }
}

CString Component::get_ParentName()
{
    if (designer && Parent != designer->GetParentForm())
        return parentName = Parent->get_Name();
    return parentName = DEF_PARENT_NAME;
}

void Component::set_Left(long val)
{
    CRect rc(GetBoundsRect());
    if (rc.left != val || state.GetBit(csLoading))
    {
        int width = rc.Width();
        rc.left = val;
        rc.right = rc.left + width;
        if (CheckBounds(rc))
        {
            if (IsControl() == TRUE && GetState(csLoading) == FALSE && GetState(csCreating) == FALSE &&
                FirstSelected == TRUE)
                GetComponents()->Invalidate(TRUE);
            SetBoundsRect(rc);
        }
    }
}

long Component::get_Left(void)
{
    if (GetState(csMoving))
        return bounds.left;
    return GetBoundsRect().left;
}

void Component::set_Top(long val)
{
    CRect rc(GetBoundsRect());
    if (rc.top != val || state.GetBit(csLoading))
    {
        int height = rc.Height();
        rc.top = val;
        rc.bottom = rc.top + height;
        if (CheckBounds(rc))
        {
            if (IsControl() == TRUE && GetState(csLoading) == FALSE && GetState(csCreating) == FALSE &&
                FirstSelected == TRUE)
                GetComponents()->Invalidate(TRUE);

            SetBoundsRect(rc);
        }
    }
}

long Component::get_Top(void)
{
    if (GetState(csMoving))
        return bounds.top;
    return GetBoundsRect().top;
}

void Component::set_Width(long val)
{
    CRect rc(GetBoundsRect());
    if (val != 0 || state.GetBit(csLoading))
    {
        rc.right = rc.left + val;
        if (CheckBounds(rc))
        {
            if (IsControl() == TRUE && GetState(csLoading) == FALSE && GetState(csCreating) == FALSE &&
                FirstSelected == TRUE)
                GetComponents()->Invalidate(TRUE);
            SetBoundsRect(rc);
        }
    }
}

long Component::get_Width(void)
{
    if (GetState(csMoving))
        return bounds.Width();
    return GetBoundsRect().Width();
}

void Component::set_Height(long val)
{
    CRect rc(GetBoundsRect());
    if (val != 0 || state.GetBit(csLoading))
    {
        rc.bottom = rc.top + val;
        if (CheckBounds(rc))
        {
            if (IsControl() == TRUE && GetState(csLoading) == FALSE && GetState(csCreating) == FALSE &&
                FirstSelected == TRUE)
                GetComponents()->Invalidate(TRUE);
            SetBoundsRect(rc);
        }
    }
}

long Component::get_Height(void)
{
    if (GetState(csMoving))
        return bounds.Height();
    return GetBoundsRect().Height();
}

void Component::set_UniqueID(long val)
{
    uniqueID = val;
    if (IsControl() && ::IsWindow((HWND)GetHandle()))
        ::SetWindowLong((HWND)GetHandle(), GWL_ID, uniqueID);
}

long Component::get_UniqueID(void)
{
    return uniqueID;
}

void Component::set_Selected(BOOL val)
{
    SET_PROP_VALUE(Selected, val)
    if (val == FALSE)
        FirstSelected = FALSE;
}

BOOL Component::get_Selected(void)
{
    return GET_PROP_VALUE(BOOL, Selected)
}

void Component::set_FirstSelected(BOOL val)
{
    SET_PROP_VALUE(FirstSelected, val)
        if (val == TRUE)
        {
            ShowProperties();
            if (IsForm() == FALSE)
                PostEvent(evSetActiveForm, GetParentForm());
        }
}

BOOL Component::get_FirstSelected(void)
{
    return GET_PROP_VALUE(BOOL, FirstSelected)
}

BOOL Component::CheckBounds(CRect rc)
{
    if (Parent && IsControl() == TRUE)
    {
        CRect RC;
        ::GetClientRect((HWND)Parent->GetHandle(), &RC);
        BOOL dimFlag = rc.left >= RC.left && rc.top >= RC.top && rc.right <= RC.right && rc.bottom <= RC.bottom;

        BOOL minRCFlag = TRUE;
        if (minRC.IsRectNull() == FALSE)
            minRCFlag = rc.Width() >= minRC.Width() && rc.Height() >= minRC.Height();

        return dimFlag && minRCFlag;
    }
    return TRUE;
}

BOOL Component::MouseDown(CDC *dc, CPoint at, HintItem h)
{
    deltaPoint = at;
    pressed = TRUE;
    designer->GetComponents()->Invalidate(TRUE);
    minRC = GetMinRect();
    return TRUE;
}

BOOL Component::MouseMove(CDC *dc, CPoint at, HintItem h)
{
    if (pressed == TRUE && ((deltaPoint - at) != CSize(0, 0)))
    {
        if (GetState(csMoving))
        {
            CRect rc(bounds);
            ComponentToDesigner(rc);
            dc->DrawFocusRect(&rc);

            bounds = Move(CPoint(at - deltaPoint), h);
        }
        else
            if (CPoint(at - deltaPoint) != CPoint(0, 0))
                SetState(csMoving, TRUE);

        if (GetState(csMoving))
        {
            CRect rc(bounds);
            ComponentToDesigner(rc);
            dc->DrawFocusRect(&rc);
        }
        deltaPoint = at;
    }
    return TRUE;
}

BOOL Component::MouseUp(CDC *dc, CPoint at, HintItem h)
{
    if (pressed == TRUE)
    {
        pressed = FALSE;
        if (GetState(csCreating))
        {
            bounds = Move(CPoint(at - deltaPoint), h);
            SetState(csCreating, FALSE);
            NormalizeRect(bounds);
            SetBoundsRect(bounds);
            SetState(csMoving, FALSE);
        }

        if (GetState(csMoving))
        {
            CRect rc(bounds);
            ComponentToDesigner(rc);
            dc->DrawFocusRect(&rc);
            bounds = Move(CPoint(at - deltaPoint), h);
            SetBoundsRect(bounds);
            SetState(csMoving, FALSE);
        }

        if (IsControl() == FALSE && IsForm() == FALSE)
        {
            ::RedrawWindow((HWND)designer->GetParentForm()->GetHandle(), NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);
        }
    }
    return TRUE;
}

CRect Component::Move(CPoint &at, HintItem hint)
{
    if (at.x == 0 && at.y == 0)
        return bounds;

    BOOL modFlag = TRUE;

    CRect maxRC;
    ::GetClientRect((HWND)Parent->GetHandle(), &maxRC);
    CWindow _w((HWND)Parent->GetHandle());
    _w.ClientToScreen(&maxRC);
    GetDesigner()->ScreenToClient(&maxRC);

    CRect rc = bounds;
    ComponentToDesigner(rc);

    if (IsControl() == FALSE && IsForm() == FALSE && hint != hiAll)
    {
        rc.right = rc.left + NONCONTROLW;
        rc.bottom = rc.top + NONCONTROLH;
    }
    else
        switch (hint)
        {
        case hiLeftTop:
            if (rc.top + at.y >= maxRC.top)
                rc.top += at.y;
            else
                rc.top = maxRC.top;

            if (rc.left + at.x >= maxRC.left)
                rc.left += at.x;
            else
                rc.left = maxRC.left;
            break;
        case hiTopMedium:
            if (rc.top + at.y >= maxRC.top)
                rc.top += at.y;
            else
                rc.top = maxRC.top;
            break;
        case hiRightTop:
            if (rc.top + at.y >= maxRC.top)
                rc.top += at.y;
            else
                rc.top = maxRC.top;

            if (rc.right + at.x <= maxRC.right)
                rc.right += at.x;
            else
                rc.right = maxRC.right;
            break;
        case hiRightMedium:
            if (rc.right + at.x <= maxRC.right)
                rc.right += at.x;
            else
                rc.right = maxRC.right;
            break;
        case hiRightBottom:
            if (rc.bottom + at.y <= maxRC.bottom)
                rc.bottom += at.y;
            else
                rc.bottom = maxRC.bottom;

            if (rc.right + at.x <= maxRC.right)
                rc.right += at.x;
            else
                rc.right = maxRC.right;
            break;
        case hiBottomMedium:
            if (rc.bottom + at.y <= maxRC.bottom)
                rc.bottom += at.y;
            else
                rc.bottom = maxRC.bottom;
            break;
        case hiLeftBottom:
            if (rc.bottom + at.y <= maxRC.bottom)
                rc.bottom += at.y;
            else
                rc.bottom = maxRC.bottom;

            if (rc.left + at.x >= maxRC.left)
                rc.left += at.x;
            else
                rc.left = maxRC.left;
            break;
        case hiLeftMedium:
            if (rc.left + at.x >= maxRC.left)
                rc.left += at.x;
            else
                rc.left = maxRC.left;
            break;
        case hiAll:
            if (rc.left + at.x >= maxRC.left && rc.bottom + at.y <= maxRC.bottom && rc.top + at.y >= maxRC.top && rc.right + at.x <= maxRC.right)
                rc += at;
            else
                modFlag = FALSE;
            break;
        }

    DesignerToComponent(rc);
    if (modFlag == TRUE && CheckBounds(rc))
    {
        bounds = rc;
        //UpdateBoundsProp(bounds);
    }
    return bounds;
}

void Component::Paint(CDC & dc)
{
    if (IsControl() == FALSE && IsForm() == FALSE && GetState(csMoving) == FALSE)
    {
        HBITMAP bitmap = NULL;
        CString cmpName;
        CString cmpPage;
        if (ExtractName(className, cmpPage, cmpName))
        {
            CRect rc(bounds);
            ComponentToDesigner(rc);
            SendEvent(evGetComponentBitmap, (LPCTSTR)cmpName, (LPCTSTR)cmpPage, &bitmap);
            {
                CPenEx pen(PS_SOLID, 1, RGB(0, 0, 0));
                CSel selPen(dc, pen);
                dc.Rectangle(&rc);
            }
            rc.DeflateRect(1, 1);
            dc.DrawFrameControl(&rc, DFC_BUTTON, DFCS_BUTTONPUSH);
            rc.DeflateRect(1, 1);
            if (bitmap)
                DrawTransparentBitmap(dc, bitmap, rc.left, rc.top, RGB(192, 192, 192));
        }
    }

    if (Selected == TRUE)
        PaintSelect(dc);
}

void Component::PaintSelect(CDC & dc)
{
    if (pressed == FALSE && GetComponents()->hideall == FALSE)
    {
        COLORREF color = FirstSelected == TRUE ? RGB(0x7F, 0x7F, 0x7F) : RGB(0xFF, 0xFF, 0xFF);
        CPoint at;
        CRect rc(bounds);
        ComponentToDesigner(rc);

        at.x = rc.left - BOX_SIDE;
        at.y = rc.top - BOX_SIDE;
        DrawBox(dc, at, color);

        at.x = (rc.left + rc.right) / 2;
        DrawBox(dc, at, color);

        at.x = rc.right + BOX_SIDE;
        DrawBox(dc, at, color);

        at.y = (rc.top + rc.bottom) / 2;
        DrawBox(dc, at, color);

        at.y = rc.bottom + BOX_SIDE;
        DrawBox(dc, at, color);

        at.x = (rc.left + rc.right) / 2;
        DrawBox(dc, at, color);

        at.x = rc.left - BOX_SIDE;
        DrawBox(dc, at, color);

        at.y = (rc.top + rc.bottom) / 2;
        DrawBox(dc, at, color);
    }
}

HintItem Component::GetHint(CPoint & pt)
{
    CPoint at;
    CRect rc(bounds);
    ComponentToDesigner(rc);

    at.x = rc.left - BOX_SIDE;
    at.y = rc.top - BOX_SIDE;
    if (PtInBox(at, pt))
        return hiLeftTop;

    at.x = (rc.left + rc.right) / 2;
    if (PtInBox(at, pt))
        return hiTopMedium;

    at.x = rc.right + BOX_SIDE;
    if (PtInBox(at, pt))
        return hiRightTop;

    at.y = (rc.top + rc.bottom) / 2;
    if (PtInBox(at, pt))
        return hiRightMedium;

    at.y = rc.bottom + BOX_SIDE;
    if (PtInBox(at, pt))
        return hiRightBottom;

    at.x = (rc.left + rc.right) / 2;
    if (PtInBox(at, pt))
        return hiBottomMedium;

    at.x = rc.left - BOX_SIDE;
    if (PtInBox(at, pt))
        return hiLeftBottom;

    at.y = (rc.top + rc.bottom) / 2;
    if (PtInBox(at, pt))
        return hiLeftMedium;

    return PtInRect(rc, pt) ? hiAll : hiNone;
}

CRect  Component::GetBoundsRect(void)
{
    if (state.GetBit(csLoading))
    {
        bounds.left = GET_PROP_VALUE(long, Left)
            bounds.top = GET_PROP_VALUE(long, Top)
            bounds.right = bounds.left + GET_PROP_VALUE(long, Width)
            bounds.bottom = bounds.top + GET_PROP_VALUE(long, Height)
    }
    return bounds;
}

void Component::UpdateBoundsProp(CRect & rc)
{
    bounds = rc;
    SET_PROP_VALUE(Left, bounds.left)
        SET_PROP_VALUE(Top, bounds.top)
        long temp = bounds.Width();
    SET_PROP_VALUE(Width, temp)
        temp = bounds.Height();
    SET_PROP_VALUE(Height, temp)

        ::UpdateProperty(_T("Left"));
    ::UpdateProperty(_T("Top"));
    ::UpdateProperty(_T("Width"));
    ::UpdateProperty(_T("Height"));

    if (IsForm() == TRUE)
    {
        ::UpdateProperty(_T("ClientWidth"));
        ::UpdateProperty(_T("ClientHeight"));
    }

    SetModified();
}

void Component::SetBoundsRect(CRect rc)
{
    UpdateBoundsProp(rc);
    if (get_Layout() == TRUE && GetState(csLoading) == FALSE && GetState(csCreating) == FALSE)
        ::PostMessage((HWND)GetParentForm()->GetHandle(), WM_UPDATELAYOUT, 0, 0);
}

void Component::Load(CXMLDOMNode & Node)
{
    objprop.Load(Node);
}

void Component::Save(CXMLDOMNode & Node)
{
    objprop.Save(Node);
}

void Component::DesignerToComponent(CRect & rc)
{
    if (IsControl())
    {
        designer->ClientToScreen(&rc);
        CWindow((HWND)Parent->GetHandle()).ScreenToClient(&rc);
    }
}

void Component::ComponentToDesigner(CRect & rc)
{
    if (IsControl())
    {
        CWindow((HWND)Parent->GetHandle()).ClientToScreen(&rc);
        designer->ScreenToClient(&rc);
    }
}

void Component::DesignerToComponent(CPoint & pt)
{
    if (IsControl())
    {
        designer->ClientToScreen(&pt);
        CWindow((HWND)Parent->GetHandle()).ScreenToClient(&pt);
    }
}

void Component::ComponentToDesigner(CPoint & pt)
{
    if (IsControl())
    {
        CWindow((HWND)Parent->GetHandle()).ClientToScreen(&pt);
        designer->ScreenToClient(&pt);
    }
}

long Component::DesignerToComponentX(long val)
{
    CPoint pt(val, 0);
    DesignerToComponent(pt);
    return pt.x;
}

long Component::ComponentToDesignerX(long val)
{
    CPoint pt(val, 0);
    ComponentToDesigner(pt);
    return pt.x;
}

long Component::DesignerToComponentY(long val)
{
    CPoint pt(0, val);
    DesignerToComponent(pt);
    return pt.y;
}

long Component::ComponentToDesignerY(long val)
{
    CPoint pt(0, val);
    ComponentToDesigner(pt);
    return pt.y;
}

void Component::SetState(ComponentState cs, BOOL flag)
{
    state.SetBit(cs, flag);
}

BOOL Component::GetState(ComponentState cs)
{
    return state.GetBit(cs);
}

void Component::ResetState(void)
{
    state.Reset();
}

BOOL Component::IsControl()
{
    return FALSE;
}

BOOL Component::IsForm()
{
    return FALSE;
}

HANDLE Component::GetHandle(void)
{
    return NULL;
}

Component	*Component::GetComponentParent()
{
    if (state.GetBit(csLoading))
    {
        CString str = GET_PROP_VALUE(CString, ParentName)
            if (str.IsEmpty() || str == DEF_PARENT_NAME)
                Parent = designer->GetParentForm();
            else
            {
                Parent = designer->GetComponents()->Find(str);
                if (Parent == NULL)
                    Parent = designer->GetParentForm();
            }
    }
    return Parent;
}

void Component::SetComponentParent(Component* newParent)
{
    if (newParent == NULL || newParent == Parent)
        return;

    Component * oldParent = Parent;
    Parent = newParent;
    if (state.GetBit(csLoading) == FALSE && IsForm() == FALSE && IsControl() == TRUE &&
        ::IsWindow((HWND)GetHandle()) && ::IsWindow((HWND)newParent->GetHandle()))
        ::SetParent((HWND)GetHandle(), (HWND)newParent->GetHandle());

    CString str = newParent->get_Name();
    if (GetState(csCreating) == FALSE &&
        IsForm() == FALSE &&
        str == GetParentForm()->get_Name())
        str = DEF_PARENT_NAME;

    SET_PROP_VALUE(ParentName, str)
        parentName = str;
    if (oldParent != NULL && ::IsWindow((HWND)oldParent->GetHandle()))
    {
        ::SetWindowPos((HWND)GetHandle(), (HWND)oldParent->GetHandle(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        GetDesigner()->BringToTop();
    }
}

Component* Component::GetParentForm()
{
    if (GetDesigner())
        return GetDesigner()->GetParentForm();
    return NULL;
}

CDesignerCtrl * Component::GetDesigner()
{
    return designer;
}

void Component::SetDesigner(CDesignerCtrl * d)
{
    designer = d;
}

CString Component::MakeDefaultName(void)
{
    CString str;
    if (className.IsEmpty() == FALSE)
    {
        CString cmpName;
        CString cmpPage;
        if (ExtractName(className, cmpPage, cmpName))
        {
            if (cmpName[0] == 'c' || cmpName[0] == 'C')
                cmpName.Delete(0);

            if (IsControl() == TRUE)
            {
                cmpName.MakeLower();
                str.Format(_T("m_%s%d"), (LPCTSTR)cmpName, uniqueID);
            }
            else
            {
                str.Format(_T("%s%d"), (LPCTSTR)cmpName, uniqueID);
            }
        }
    }
    return str;
}

CString Component::GetClassName()
{
    return className;
}

void Component::set_Layout(BOOL val)
{

}

BOOL Component::get_Layout(void)
{
    return FALSE;
}

CLayout *	Component::get_leftLayout()
{
    return NULL;
}

CLayout	*	Component::get_topLayout()
{
    return NULL;
}

CLayout	*	Component::get_rightLayout()
{
    return NULL;
}

CLayout	*	Component::get_bottomLayout()
{
    return NULL;
}

CLayout	*	Component::get_hCenterLayout()
{
    return NULL;
}

CLayout	*	Component::get_vCenterLayout()
{
    return NULL;
}

void Component::UnAttach(Component *)
{
}

void Component::set_Focus(BOOL)
{
}

BOOL Component::get_Focus()
{
    return FALSE;
}

_variant_t __stdcall Component::Item(BSTR propName)
{
    USES_CONVERSION;
    CString str = objprop.GetPropValueStr(CString(propName));

    if (str == _T("true"))
    {
        return true;
    }

    if (str == _T("false"))
    {
        return false;
    }

    if (str == _T(""))
    {
        str = _T("");
    }

    ATLTRACE(CString(propName) + "=" + CString(str) + "\n");
    return str.AllocSysString();
}

long __stdcall Component::get_Count(void)
{
    return objprop.Count();
}

BSTR __stdcall Component::get_Class(void)
{
    //CString cmpName;
    //CString cmpPage;
    //ExtractName(className,cmpPage,cmpName);

    //return cmpName.AllocSysString();
    return className.AllocSysString();
}

IDispatch * __stdcall Component::get_Components()
{
    return dynamic_cast<Components *>(designer->GetComponents());
}

IDispatch* __stdcall Component::get_Code()
{
    return NULL;
}

IDispatch * __stdcall Component::get_Form()
{
    return dynamic_cast<Component *>(GetParentForm());
}

BOOL __stdcall Component::get_IsControl()
{
    return IsControl();
}

BOOL __stdcall Component::get_IsForm()
{
    return IsForm();
}

Component * Component::Find(const CString & val)
{
    Components * cmps = static_cast<Components *>(designer->GetComponents());
    for (int i = 0; i < cmps->GetCount(); i++)
    {
        if (cmps->GetAt(i)->get_Name() == val)
            return static_cast<Component *>(cmps->GetAt(i));
    }
    return NULL;
}

CString Component::GetComponetKind()
{
    return _T("COMPONENT");
}

void Component::SetModified(CRect * rc)
{
    if (GetState(csLoading) || GetState(csCreating))
        return;

    if (IsForm() == TRUE)
    {
        if (designer->IsShowGSGuides())
            ::RedrawWindow((HWND)GetHandle(), rc, NULL, RDW_NOERASE | RDW_UPDATENOW | RDW_INVALIDATE | RDW_INTERNALPAINT/*|RDW_ALLCHILDREN*/);
    }
    else
    {
        CRect rect = GetBoundsRect();
        ComponentToDesigner(rect);
        GetParentForm()->SetModified(&rect);
    }
}

Component * Component::Clone(CDesignerCtrl * d)
{
    Component * ctrl = NULL;
    CString cmpPage;
    CString cmpName;
    SetDesigner(d);
    ExtractName(className, cmpPage, cmpName);
    SendEvent(evCreateComponent, (LPCTSTR)cmpName, (LPCTSTR)cmpPage, &ctrl);
    if (ctrl != NULL)
    {
        ctrl->SetState(csCreating, TRUE);
        ctrl->SetState(csCloning, TRUE);
        ctrl->SetState(csLoading, TRUE);
        ctrl->InitProperty();
        ctrl->objprop = objprop;

        ctrl->set_UniqueID(UniqueID);
        ctrl->SET_PROP_VALUE(UniqueID, ctrl->get_UniqueID())
        ctrl->SET_PROP_VALUE(ID, CString(_T("")))
        name = ctrl->MakeDefaultName();
        ctrl->SET_PROP_VALUE(Name, name)

        if (ctrl->EnableTabIndex() == TRUE)
        {
            int tab = GetComponents()->FindMaxTabIndex() + 1;
            ctrl->SET_PROP_VALUE(TabIndex, tab)
        }
        ctrl->SetState(csCloning, FALSE);
    }
    return ctrl;
}

CRect Component::GetMinRect()
{
    CRect minRc;
    Components * components = GetComponents();
    if (components == NULL)
        return minRc;
    Component *  comp;
    minRc.left = 0;
    minRc.top = 0;
    minRc.right = 0;
    minRc.bottom = 0;

    BOOL flag = FALSE;
    for (size_t i = 0; i < (size_t)components->GetCount(); i++)
    {
        comp = components->GetAt((int)i);
        if (comp->IsControl() && this == comp->GetComponentParent())
        {
            Component *comp = components->GetAt((int)i);
            CRect rc = comp->GetBoundsRect();
            minRc.right = max(minRc.right, rc.right);
            minRc.bottom = max(minRc.bottom, rc.bottom);
            flag = TRUE;
        }
    }

    if (flag == FALSE)
        minRc.SetRectEmpty();
    else
    {
        minRc.left = 0;
        minRc.top = 0;
    }

    return minRc;
}

void Component::set_TabIndex(long val)
{
    if (tabIndex != val)
    {
        if (enableTabIndex == TRUE)
            tabIndex = val;
        else
            tabIndex = -1;
        SetModified();
    }
}

long Component::get_TabIndex()
{
    return tabIndex;
}

BOOL Component::EnableTabIndex()
{
    return enableTabIndex;
}
//////////////////////////////////////////////////////////////////////////
Components::Components(void) :designer(NULL), currMode(cmSelect),
id(1000), hideall(FALSE), pressed(FALSE), freeze(FALSE)
{
    RegisterEvent(evSelectComponent, this, &Components::SelectComponent);
    RegisterEvent(evAlignComponentsLeft, this, &Components::AlignLeft);
    RegisterEvent(evAlignComponentsTop, this, &Components::AlignTop);
    RegisterEvent(evAlignComponentsRight, this, &Components::AlignRight);
    RegisterEvent(evAlignComponentsBottom, this, &Components::AlignBottom);
    RegisterEvent(evAlignComponentsHoriz, this, &Components::AlignHoriz);
    RegisterEvent(evAlignComponentsVert, this, &Components::AlignVert);
    RegisterEvent(evMakeSameWidth, this, &Components::MakeSameWidth);
    RegisterEvent(evMakeSameHeight, this, &Components::MakeSameHeight);
    RegisterEvent(evMakeSameSize, this, &Components::MakeSameSize);
    RegisterEvent(evToParent, this, &Components::ToParent);
    RegisterEvent(evHorizOrder, this, &Components::HorizOrder);
    RegisterEvent(evVertOrder, this, &Components::VertOrder);
    RegisterEvent(evHorizOrderRight, this, &Components::HorizOrderRight);
    RegisterEvent(evVertOrderBottom, this, &Components::VertOrderBottom);
    //RegisterEvent(evToBackground,this,&Components::ToBackGround);
    //RegisterEvent(evToForeground,this,&Components::ToForeGround);
    RegisterEvent(evCenterGroupHoriz, this, &Components::CenterGroupHoriz);
    RegisterEvent(evCenterGroupVert, this, &Components::CenterGroupVert);
    RegisterEvent(evChangeParent, this, &Components::ChangeComponentsParent);
    RegisterEvent(evSelectAll, this, &Components::SelectAll);
}

Components::~Components(void)
{
    UnRegisterEvent(this);
    for (unsigned int i = 0; i < components.size(); i++)
        delete components[i];

    components.clear();
}

void Components::SetDesigner(CDesignerCtrl *p)
{
    designer = p;
}

CDesignerCtrl *	Components::GetDesigner(void)
{
    return designer;
}

Component*Components::GetParentForm()
{
    return GetDesigner()->GetParentForm();
}

void Components::SetSelectMode(BOOL m)
{
    if (m == TRUE)
        currMode = cmSelect;
    else
        currMode = cmCreate;
}

BOOL Components::IsSelectMode()
{
    return currMode == cmSelect;
}

void Components::Paint(CDC & dc)
{
    if (freeze == TRUE)
        return;

    if (hideall == FALSE)
        for (unsigned int i = 0; i < components.size(); i++)
            components[i]->Paint(dc);
}

Component * Components::ComponentFromPt(CPoint & at, BOOL realBounds)
{
    if (freeze == TRUE)
        return NULL;
    CRect rc;
    for (int i = (int)components.size() - 1; i >= 0; i--)
    {
        if (components[i]->IsControl() && ::IsWindowVisible((HWND)components[i]->GetHandle()) == FALSE)
            continue;
        if (realBounds == FALSE)
        {
            rc = components[i]->GetBoundsRect();
            components[i]->ComponentToDesigner(rc);
        }
        else
        {
            ::GetWindowRect((HWND)components[i]->GetHandle(), &rc);
            designer->ScreenToClient(&rc);
        }
        if (rc.PtInRect(at))
            return components[i];
    }
    return NULL;
}

Component * Components::SelectComponentFromPt(CPoint & at, BOOL selected)
{
    CRect rc;
    Component * comp = NULL;
    HintItem hint;

    if (freeze == TRUE)
        return NULL;

    for (int i = (int)components.size() - 1; i >= 0; i--)
    {
        if ((hint = components[i]->GetHint(at)) != hiNone)
        {
            if (components[i]->IsControl() == FALSE && components[i]->IsForm() == FALSE)
                return components[i];
            if (::IsWindow((HWND)components[i]->GetHandle()) && ::IsWindowVisible((HWND)components[i]->GetHandle()) == FALSE)
                continue;
            if (selected == TRUE && components[i]->get_Selected() == FALSE)
                continue;
            if (selected == TRUE && hint == hiAll)
                continue;
            //if(comp==NULL)
            comp = components[i];
            break;
        }
    }

    return comp;
}

void Components::UnselectAll(void)
{
    Invalidate(TRUE);
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
            components[i]->set_Selected(FALSE);
    }
}

void Components::MouseDown(CPoint point)
{
    Component * temp = NULL;
    ShowCursorPos(point);
    if (freeze == TRUE)
        return;

    CClientDC dc(designer->m_hWnd);

    BOOL shiftPressed = ((GetKeyState(VK_LSHIFT) & 0x100) || (GetKeyState(VK_RSHIFT) & 0x100)) ? TRUE : FALSE;

    if (currMode == cmCreate)
    {
        UnselectAll();
        point = SnapToGrid(point);
        CSize grid = GetDesigner()->IsShowGrid() == TRUE ? GetDesigner()->GetGridSize() : CSize(0, 0);
        CRect rc(point.x, point.y, point.x + grid.cx, point.y + grid.cy);
        temp = Create(rc, shiftPressed);
        if (temp)
        {
            //SetStateAll(csFirstSelected, FALSE);
            components.push_back(temp);
            temp->Selected = TRUE;
            temp->FirstSelected = TRUE;
            hint = hiRightBottom;
            temp->DesignerToComponent(point);
            temp->MouseDown(&dc, point, hint);
            temp->SetModified();
            GetDesigner()->SetComponentCreated();
            if(temp->EnableTabIndex() == TRUE)
                temp->set_TabIndex(FindMaxTabIndex() + 1);
            else
                temp->set_TabIndex(-1);
            pressed = TRUE;
        }
        PostEvent(evSetActiveForm, temp->GetParentForm());
        return;
    }

    if (currMode == cmSelect)
    {
        temp = SelectComponentFromPt(point, TRUE);
        if (temp == NULL)
            temp = SelectComponentFromPt(point);

        if (temp)
        {
            if (shiftPressed == TRUE)
            {
                temp->set_Selected(TRUE);
                if (GetSelCount() == 1)
                {
                    temp->FirstSelected = TRUE;
                    RemoveProperties();
                }
                
                hint = hiAll;
                point = SnapToGrid(point);
                MouseDownAll(&dc, point);
            }
            else
            {
                UnselectAll();
                temp->Selected = TRUE;
                temp->FirstSelected = TRUE;
                hint = temp->GetHint(point);
                if (hint != hiNone)
                {
                    pressed = TRUE;
                    ShowCursor(hint);
                    point = SnapToGrid(point);
                    MouseDownAll(&dc, point);
                }
            }
            pressed = TRUE;
            return;
        }
        else
        {
            if (shiftPressed == FALSE)
                UnselectAll();
            ::SendMessage((HWND)designer->GetParentForm()->GetHandle(), WM_LBUTTONDOWN, 0, MAKELONG(point.x, point.y));
        }
    }

    PostEvent(evSetActiveForm, designer->GetParentForm());
}

void Components::MouseUp(CPoint point)
{
    ShowCursorPos(point);
    if (freeze == TRUE)
        return;

    if (currMode == cmCreate && (GetKeyState(VK_LSHIFT) & 0x100 || GetKeyState(VK_RSHIFT) & 0x100) == FALSE)
        PostEvent(evResetSelectedComponent);

    Component * temp = NULL;
    if (pressed == TRUE)
    {
        point = SnapToGrid(point);
        CClientDC dc(designer->m_hWnd);
        if ((temp = GetSingleSel()) != NULL)
        {
            temp->MouseUp(&dc, point, hint);
        }
        else
            MouseUpAll(&dc, point);
    }
    else
    {
        temp = SelectComponentFromPt(point, TRUE);
        if (temp && temp->get_Selected())
        {
            ShowCursor(temp->GetHint(point));
        }
    }
    hint = hiNone;
    pressed = FALSE;

    ::PostMessage((HWND)GetParentForm()->GetHandle(), WM_UPDATELAYOUT, 0, 0);
    Invalidate();
}

void Components::MouseMove(CPoint point)
{
    ShowCursorPos(point);
    if (freeze == TRUE)
        return;

    Component * temp = NULL;

    if (pressed)
    {
        point = SnapToGrid(point);
        CClientDC dc(designer->m_hWnd);
        if ((temp = GetSingleSel()) != NULL)
        {
            temp->MouseMove(&dc, point, hint);
            if (currMode != cmCreate)
                ShowCursor(hint);
            return;
        }
        else
        {
            MouseMoveAll(&dc, point);
            return;
        }
    }
    else
    {
        temp = SelectComponentFromPt(point, TRUE);
        if (temp)
        {
            ShowCursor(temp->GetHint(point));
        }
    }
}

void Components::ShowCursorPos(const CPoint& pt)
{
    CPoint point(pt);
    Component *temp = ComponentFromPt(point, FALSE);
    if (temp)
    {
        if (temp->IsControl())
        {
            designer->ClientToScreen(&point);
            CWindow((HWND)temp->GetHandle()).ScreenToClient(&point);
        }
    }
    PostEvent(evXYCursor, point);
}

int	Components::GetSelCount(void)
{
    int selcount = 0;
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected())
        {
            selcount += 1;
        }
    }

    return selcount;
}

Component * Components::GetSingleSel(void)
{
    Component * temp = NULL;
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected())
        {
            if (temp == NULL)
                temp = components[i];
            else
                return NULL;
        }
    }
    return temp;
}

Component * Components::GetFirstSel(void)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->FirstSelected)
            return components[i];
    }
    return NULL;
}

int Components::GetFirstSelIdx(void)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->FirstSelected)
            return i;
    }
    return -1;
}

void Components::MouseDownAll(CDC *dc, CPoint at)
{
    if (freeze == TRUE)
        return;

    for (unsigned int i = 0; i < components.size(); ++i)
        if (components[i]->get_Selected())
            components[i]->MouseDown(dc, at, hint);
}

void Components::MouseMoveAll(CDC *dc, CPoint at)
{
    if (freeze == TRUE)
        return;

    for (unsigned int i = 0; i < components.size(); ++i)
        if (components[i]->get_Selected())
            components[i]->MouseMove(dc, at, hint);
}

void Components::MouseUpAll(CDC *dc, CPoint at)
{
    if (freeze == TRUE)
        return;

    for (unsigned int i = 0; i < components.size(); ++i)
        if (GetAt(i)->get_Selected())
            GetAt(i)->MouseUp(dc, at, hint);
}

void Components::ShowCursor(HintItem h)
{
    if (currMode != cmCreate)
    {
        HCURSOR Cursor = NULL;
        switch (h)
        {
        case hiLeftTop:
        case hiRightBottom:
            Cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE));
            break;
        case hiRightTop:
        case hiLeftBottom:
            Cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW));
            break;
        case hiRightMedium:
        case hiLeftMedium:
            Cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE));
            break;
        case hiTopMedium:
        case hiBottomMedium:
            Cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS));
            break;
        case hiCaption:
Cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEALL));
break;
        }

        if (Cursor)
            SetCursor(Cursor);
    }
}

void Components::Load(CXMLDOMNode & controlNode)
{
    CXMLDOMNodeList controls(controlNode.GetChildNodes());
    if (controls == NULL)
        return;

    CXMLDOMNode LastId = controlNode.GetAttributes().GetNamedItem(_T("LastCtrlId"));
    if (LastId != NULL)
    {
        _variant_t val = LastId.GetNodeValue();
        id = val;
    }

    long Count = controls.GetLength();
    for (long i = 0; i < Count; i++)
    {
        CString cmpName = controls.GetItem(i).GetAttributes().GetNamedItem(_T("Class")).GetText();
        CString cmpPage = controls.GetItem(i).GetAttributes().GetNamedItem(_T("Page")).GetText();
        if (cmpName.IsEmpty() == FALSE && cmpPage.IsEmpty() == FALSE)
        {
            Component * ctrl = NULL;
            SendEvent(evCreateComponent, (LPCTSTR)cmpName, (LPCTSTR)cmpPage, &ctrl);
            if (ctrl == NULL)
            {
                SendEvent(evOutput, ErrorMsg, (LPCSTR)MakeString(_T("Component Page = %s, Name = %s not found."), (LPCTSTR)cmpPage, (LPCTSTR)cmpName));
                return;
            }
            ctrl->SetState(csLoading, TRUE);
            CRect rc(0, 0, 0, 0);

            ctrl->InitProperty();
            ctrl->SetDesigner(designer);
            ctrl->Load(controls.GetItem(i));
            rc = ctrl->GetBoundsRect();
            ctrl->SetBoundsRect(rc);
            ctrl->CreateComponent(ctrl->GetComponentParent());
            components.push_back(ctrl);
            ctrl->SetState(csCreating, FALSE);
        }
    }

    for (size_t j = 0; j < components.size(); j++)
    {
        components[j]->ComponentCreated();
        components[j]->SetState(csLoading, FALSE);
    }
    designer->BringWindowToTop();
}

static CPoint findTopLeftCorner(ComponentArray * comps)
{
    CPoint pt(0xFFFF, 0xFFFF);
    for (int i = 0; i < (int)comps->size(); i++)
    {
        if ((*comps)[i]->IsControl() == FALSE)
            continue;
        pt.x = min(pt.x, (*comps)[i]->get_Left());
        pt.y = min(pt.y, (*comps)[i]->get_Top());
    }
    return pt;
}

void Components::Paste(ComponentArray * comps, Component * comp, CPoint * downPoint)
{
    CFreeze fr(freeze);
    Component * ctrl = NULL;
    CPoint pt(0, 0);

    if (downPoint)
        pt = findTopLeftCorner(comps);

    for (unsigned int i = 0; i < comps->size(); i++)
    {
        ctrl = (*comps)[i]->Clone(designer);
        ctrl->SetState(csLoading, TRUE);
        Component * par = comp;
        if (par == NULL)
            par = GetParentForm();

        ctrl->CreateComponent(par);
        UnselectAll();
        components.push_back(ctrl);
        CPoint at(0, 0);
        if (downPoint)
        {
            at = *downPoint;
            ctrl->DesignerToComponent(at);
        }

        ctrl->set_Left(at.x + ctrl->get_Left() - pt.x);
        ctrl->set_Top(at.y + ctrl->get_Top() - pt.y);
        ctrl->SetState(csCreating, FALSE);
        ctrl->ComponentCreated();
        ctrl->SetState(csLoading, FALSE);
    }
}

void Components::Save(CXMLDOMNode &controls, BOOL onlySelected)
{
    CFreeze fr(freeze);
    CXMLDOMAttribute LastId(controls.GetOwnerDocument().CreateAttribute(_T("LastCtrlId")));
    LastId.SetValue(id);
    controls.GetAttributes().SetNamedItem(LastId);

    long count = 0;
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (onlySelected == TRUE && components[i]->get_Selected() == FALSE)
            continue;

        CXMLDOMNode Item(controls.GetOwnerDocument().CreateNode((long)NODE_ELEMENT, components[i]->get_Name(), NULL));
        controls.AppendChild(Item);

        components[i]->SetState(csSaving, TRUE);
        components[i]->Save(Item);
        components[i]->SetState(csSaving, FALSE);
    }
}

Component * Components::Create(CRect & rc, BOOL multiCreate)
{
    CString cmpName;
    CString cmpPage;
    if (ExtractName(newComponentName, cmpPage, cmpName) == FALSE)
        return NULL;
    Component * newCtrl = NULL;
    SendEvent(evCreateComponent, (LPCTSTR)cmpName, (LPCTSTR)cmpPage, &newCtrl);
    if (newCtrl)
    {
        Component * curParent = NULL;
        if (newCtrl->IsControl() == FALSE)
            curParent = designer->GetParentForm();
        else
            curParent = GetCurrentParent(rc.TopLeft());

        designer->ClientToScreen(&rc);
        CWindow((HWND)curParent->GetHandle()).ScreenToClient(&rc);
        newCtrl->InitProperty();
        newCtrl->SetBoundsRect(rc);
        newCtrl->CreateComponent(curParent);
        newCtrl->ComponentCreated();
    }
    else
    {
        SendEvent(evOutput, ErrorMsg, (LPCSTR)MakeString(_T("Component Page = %s, Name = %s not found."), (LPCTSTR)cmpPage, (LPCTSTR)cmpName));
    }
    return newCtrl;
}

Component * Components::Create(Component *Parent, LPCTSTR newCmpName, CRect & rc)
{
    CString cmpName;
    CString cmpPage;
    if (ExtractName(CString(newCmpName), cmpPage, cmpName) == FALSE)
        return NULL;
    Component * newCtrl = NULL;
    SendEvent(evCreateComponent, (LPCTSTR)cmpName, (LPCTSTR)cmpPage, &newCtrl);
    if (newCtrl)
    {
        newCtrl->InitProperty();
        newCtrl->SetBoundsRect(rc);
        newCtrl->CreateComponent(Parent);
        newCtrl->ComponentCreated();
        Add(newCtrl);
    }
    return newCtrl;
}

Component * Components::GetCurrentParent(CPoint & point)
{
    Component * temp = ComponentFromPt(point, TRUE);

    if (temp)
    {
        if (::IsWindow((HWND)temp->GetHandle()) && ::IsWindowVisible((HWND)temp->GetHandle()))
            return temp;
        else
        {
            while (temp = temp->GetComponentParent())
            {
                if (::IsWindow((HWND)temp->GetHandle()) && ::IsWindowVisible((HWND)temp->GetHandle()))
                    return temp;
            }
        }
    }
    return designer->GetParentForm();
}

void Components::IncrementMove(long x, long y)
{
    BOOL flag = FALSE;
    Invalidate(TRUE);
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected())
        {
            //	CRect rc=components[i]->GetBoundsRect();
            //	rc.left-=x;
            //	rc.top-=y;
            //	components[i]->set_Left(rc.left);
            //	components[i]->set_Top(rc.top);
            components[i]->SetBoundsRect(components[i]->Move(CPoint(x, y), hiAll));
            //if(components[i]->IsControl()==FALSE && components[i]->IsForm()==FALSE)
            //    flag=TRUE;
        }
    }

    //if(flag==TRUE)
    //        ::RedrawWindow((HWND)GetParentForm()->GetHandle(),NULL,NULL,RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_ALLCHILDREN);
    //  else    
    Invalidate();
    ::PostMessage((HWND)GetParentForm()->GetHandle(), WM_UPDATELAYOUT, 0, 0);
}

void Components::IncrementSize(long x, long y, BOOL rightBottom)
{
    Invalidate(TRUE);
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected() && (components[i]->IsControl() == TRUE || components[i]->IsForm() == TRUE))
        {
            if (rightBottom == TRUE)
                components[i]->SetBoundsRect(components[i]->Move(CPoint(x, y), hiRightBottom));
            else
                components[i]->SetBoundsRect(components[i]->Move(CPoint(x, y), hiLeftTop));
        }
    }
    Invalidate();
    ::PostMessage((HWND)GetParentForm()->GetHandle(), WM_UPDATELAYOUT, 0, 0);
}

void Components::Delete()
{
    CFreeze fr(freeze);

    Invalidate(TRUE);
    BOOL flag = FALSE;
    for (int i = 0; i < (int)components.size();)
    {
        if (components[i]->get_Selected())
        {
            Component * tempComp = components[i];
            components.erase(components.begin() + i);
            Delete(tempComp, FALSE);
            i = 0;
            tempComp->DeleteComponent();
            flag = TRUE;
        }
        else
            i++;
    }

    if (flag)
    {
        ReSetTabIndex();
    }
}

BOOL Components::Delete(Component * comp, BOOL deleteSelf)
{
    CFreeze fr(freeze);
    BOOL flag = FALSE;
    if (comp == NULL)
        return flag;

    while (components.size() != 0)
    {
        Component * temp = FindByParent(comp);
        if (temp)
        {
            Delete(temp, FALSE);
            components.erase(components.begin() + FindIndex(temp));
            temp->DeleteComponent();
            flag = TRUE;
            GetParentForm()->SetModified();
            continue;
        }
        else
            break;
    }

    if (deleteSelf)
    {
        int index = FindIndex(comp);
        if (index != -1)
            components.erase(components.begin() + index);
        comp->DeleteComponent();
    }

    if (flag)
        ReSetTabIndex();

    return flag;
}

void Components::RemoveAll(void)
{
    CFreeze fr(freeze);
    for (; components.size();)
    {
        components[0]->DeleteComponent();
        components.erase(components.begin());
    }
    components.clear();
    GetParentForm()->SetModified();
    Invalidate();
}

Component * Components::Find(const CString & str)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Name() == str)
        {
            return components[i];
        }
    }
    return NULL;
}

void Components::SetStateAll(ComponentState cs, BOOL flag, BOOL SelectedOnly)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (SelectedOnly == TRUE)
        {
            if (components[i]->get_Selected() == TRUE)
                components[i]->SetState(cs, flag);
        }
        else
            components[i]->SetState(cs, flag);
    }
}

CPoint Components::SnapToGrid(CPoint xy)
{
    return designer->SnapToGrid(xy);
}

void Components::HorizOrder(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evHorizOrder);

    CPoint pt(0, 0);
    int right = 0;
    Component * firstSelected = GetFirstSel();

    if (firstSelected == NULL)
        return;

    if (firstSelected->IsControl() == FALSE)
        return;

    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;

    if (GetSelCount() > 1)
    {
        pt.y = 0;
        pt.x = firstSelected->get_Left();
        firstSelected->ComponentToDesigner(pt);
        right = pt.x + firstSelected->get_Width() + intend;
    }

    Invalidate(TRUE);

    int rx = 0;

    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE && components[i] != firstSelected)
        {
            int currIdx = FindLeftestIdx(0);
            if (currIdx == -1)
                continue;

            if (components[currIdx] == firstSelected)
            {
                i = 0;
                continue;
            }

            if (components[currIdx]->IsControl() == FALSE)
                continue;

            if (shiftPressed == TRUE)
                rx = components[currIdx]->GetBoundsRect().right;

            pt.y = 0;
            pt.x = right;
            components[currIdx]->DesignerToComponent(pt);
            components[currIdx]->set_Left(pt.x);
            pt.x = components[currIdx]->get_Left();
            pt.y = 0;
            components[currIdx]->ComponentToDesigner(pt);
            right = pt.x + components[currIdx]->get_Width() + intend;
            if (shiftPressed == TRUE)
            {
                CRect r = components[currIdx]->GetBoundsRect();
                r.right = rx;
                components[currIdx]->SetBoundsRect(r);
            }
            i = 0;
        }
    }

    Invalidate();
    SetStateAll(csReserved1, FALSE, FALSE);
}

void Components::HorizOrderRight(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evHorizOrder);

    CPoint pt(0, 0);
    int left = 0;
    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;

    if (firstSelected->IsControl() == FALSE)
        return;

    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;

    if (GetSelCount() > 1)
    {
        pt.y = 0;
        pt.x = firstSelected->get_Left();
        firstSelected->ComponentToDesigner(pt);
        left = pt.x - intend;
    }

    Invalidate(TRUE);
    int rx = 0;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE && components[i] != firstSelected)
        {
            int currIdx = FindRightestIdx(0);
            if (currIdx == -1)
                continue;
            if (components[currIdx]->IsControl() == FALSE)
                continue;
            if (components[currIdx] == firstSelected)
            {
                i = 0;
                continue;
            }

            if (shiftPressed == TRUE)
                rx = components[currIdx]->GetBoundsRect().left;

            pt.y = 0;
            pt.x = left;
            components[currIdx]->DesignerToComponent(pt);
            components[currIdx]->set_Left(pt.x - components[currIdx]->get_Width());
            pt.x = components[currIdx]->get_Left();
            pt.y = 0;
            components[currIdx]->ComponentToDesigner(pt);
            left = pt.x - intend;

            if (shiftPressed == TRUE)
            {
                CRect r = components[i]->GetBoundsRect();
                r.left = rx;
                components[i]->SetBoundsRect(r);
            }
            i = 0;
        }
    }

    Invalidate();
    SetStateAll(csReserved1, FALSE, FALSE);
}

void Components::VertOrder(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evVertOrder);

    CPoint pt(0, 0);
    int bottom = 0;
    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;
    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;
    if (GetSelCount() > 1)
    {
        pt.x = 0;
        pt.y = firstSelected->get_Top();
        firstSelected->ComponentToDesigner(pt);
        bottom = pt.y + firstSelected->get_Height() + intend;
    }

    Invalidate(TRUE);
    int ry = 0;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;

            int currIdx = FindTopestIdx(0);
            if (currIdx == -1)
                continue;

            if (components[currIdx] == firstSelected)
            {
                i = 0;
                continue;
            }

            if (shiftPressed == TRUE)
                ry = components[currIdx]->GetBoundsRect().bottom;

            pt.y = bottom;
            pt.x = 0;
            components[currIdx]->DesignerToComponent(pt);
            components[currIdx]->set_Top(pt.y);
            pt.y = components[currIdx]->get_Top();
            pt.x = 0;
            components[currIdx]->ComponentToDesigner(pt);
            bottom = pt.y + components[currIdx]->get_Height() + intend;

            if (shiftPressed == TRUE)
            {
                CRect r = components[currIdx]->GetBoundsRect();
                r.bottom = ry;
                components[currIdx]->SetBoundsRect(r);
            }
            i = 0;
        }
    }

    Invalidate();
    SetStateAll(csReserved1, FALSE, FALSE);
}

void Components::VertOrderBottom(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evVertOrderBottom);

    CPoint pt(0, 0);
    int bottom = 0;
    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;
    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;
    if (GetSelCount() > 1)
    {
        pt.x = 0;
        pt.y = firstSelected->get_Top();
        firstSelected->ComponentToDesigner(pt);
        bottom = pt.y - intend;
    }

    Invalidate(TRUE);
    int ry = 0;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            int currIdx = FindBottomestIdx(0);
            if (currIdx == -1)
                continue;
            if (components[currIdx]->IsControl() == FALSE)
                continue;
            if (components[currIdx] == firstSelected)
            {
                i = 0;
                continue;
            }

            if (shiftPressed == TRUE)
                ry = components[currIdx]->GetBoundsRect().top;

            pt.y = bottom;
            pt.x = 0;
            components[currIdx]->DesignerToComponent(pt);
            components[currIdx]->set_Top(pt.y - components[currIdx]->get_Height());
            pt.y = components[currIdx]->get_Top();
            pt.x = 0;
            components[currIdx]->ComponentToDesigner(pt);
            bottom = pt.y - intend;
            if (shiftPressed == TRUE)
            {
                CRect r = components[currIdx]->GetBoundsRect();
                r.top = ry;
                components[currIdx]->SetBoundsRect(r);
            }
            i = 0;
        }
    }

    Invalidate();
    SetStateAll(csReserved1, FALSE, FALSE);
}

Component * Components::GetAt(int idx)
{
    return components[idx];
}

int Components::GetCount(void)
{
    return (int)components.size();
}

Component * Components::FindByParent(Component * parentComp)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->GetComponentParent() == parentComp)
            return components[i];
    }
    return NULL;
}

int Components::FindIndex(Component * comp)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i] == comp)
            return i;
    }
    return -1;
}

int Components::FindParentIndex(Component * comp)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Name() == comp->get_ParentName())
            return i;
    }
    return -1;
}
int Components::FindByHandle(HWND wnd)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        if ((HWND)components[i]->GetHandle() == wnd)
            return i;
    }
    return -1;
}

void Components::SelectComponent(LPCTSTR str)
{
    newComponentName = str;
    if (newComponentName.IsEmpty())
        currMode = cmSelect;
    else
        currMode = cmCreate;
}

IDispatch* __stdcall Components::Item(long Index)//Component * 
{
    if (Index < (long)components.size())
        return components[Index];

    return NULL;
}

long __stdcall Components::get_Count(void)
{
    return (long)components.size();
}

LPUNKNOWN __stdcall Components::get__NewEnum()
{
    long count = (long)components.size();

    VARIANT * pVar = new VARIANT[count];
    for (int i = 0; i < count; i++)
    {
        pVar[i].vt = VT_DISPATCH;
        pVar[i].pdispVal = components[i];
    }

    typedef CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT,
        _Copy<VARIANT> > VarArrEnum;
    typedef CComObject<VarArrEnum> enumVar;

    enumVar * pEnumVar = new enumVar;
    pEnumVar->Init(&pVar[0], &pVar[count], NULL, AtlFlagCopy);
    delete[] pVar;
    LPUNKNOWN pVal = NULL;
    pEnumVar->QueryInterface(IID_IUnknown, (void**)pVal);
    return pVal;
}

void __stdcall Components::Add(Component * cmp)
{
    if (cmp)
    {
        components.push_back(cmp);
        GetParentForm()->SetModified();
    }
}

void __stdcall Components::Remove(long Index)
{
}
//////////////////////////////////////////////////////////////////////////
CRgnHandle MakeRgn(Component * component)
{
    CRect rc(component->GetBoundsRect());
    component->ComponentToDesigner(rc);

    POINT at[] = {
        rc.left - BOX_SIDE - BOX_SIDE,rc.top + BOX_SIDE - BOX_SIDE,
        rc.left + BOX_SIDE - BOX_SIDE,rc.top + BOX_SIDE - BOX_SIDE,
        rc.left + BOX_SIDE - BOX_SIDE,rc.top - BOX_SIDE - BOX_SIDE,
        rc.left - BOX_SIDE - BOX_SIDE,rc.top - BOX_SIDE - BOX_SIDE,

        (rc.left + rc.right) / 2 - BOX_SIDE,rc.top + BOX_SIDE - BOX_SIDE,
        (rc.left + rc.right) / 2 + BOX_SIDE,rc.top + BOX_SIDE - BOX_SIDE,
        (rc.left + rc.right) / 2 + BOX_SIDE,rc.top - BOX_SIDE - BOX_SIDE,
        (rc.left + rc.right) / 2 - BOX_SIDE,rc.top - BOX_SIDE - BOX_SIDE,

        rc.right - BOX_SIDE + BOX_SIDE,rc.top + BOX_SIDE - BOX_SIDE,
        rc.right + BOX_SIDE + BOX_SIDE,rc.top + BOX_SIDE - BOX_SIDE,
        rc.right + BOX_SIDE + BOX_SIDE,rc.top - BOX_SIDE - BOX_SIDE,
        rc.right - BOX_SIDE + BOX_SIDE,rc.top - BOX_SIDE - BOX_SIDE,

        rc.right - BOX_SIDE + BOX_SIDE,(rc.top + rc.bottom) / 2 + BOX_SIDE,
        rc.right + BOX_SIDE + BOX_SIDE,(rc.top + rc.bottom) / 2 + BOX_SIDE,
        rc.right + BOX_SIDE + BOX_SIDE,(rc.top + rc.bottom) / 2 - BOX_SIDE,
        rc.right - BOX_SIDE + BOX_SIDE,(rc.top + rc.bottom) / 2 - BOX_SIDE,

        rc.right - BOX_SIDE + BOX_SIDE,rc.bottom + BOX_SIDE + BOX_SIDE,
        rc.right + BOX_SIDE + BOX_SIDE,rc.bottom + BOX_SIDE + BOX_SIDE,
        rc.right + BOX_SIDE + BOX_SIDE,rc.bottom - BOX_SIDE + BOX_SIDE,
        rc.right - BOX_SIDE + BOX_SIDE,rc.bottom - BOX_SIDE + BOX_SIDE,

        (rc.left + rc.right) / 2 - BOX_SIDE,rc.bottom + BOX_SIDE + BOX_SIDE,
        (rc.left + rc.right) / 2 + BOX_SIDE,rc.bottom + BOX_SIDE + BOX_SIDE,
        (rc.left + rc.right) / 2 + BOX_SIDE,rc.bottom - BOX_SIDE + BOX_SIDE,
        (rc.left + rc.right) / 2 - BOX_SIDE,rc.bottom - BOX_SIDE + BOX_SIDE,


        rc.left - BOX_SIDE - BOX_SIDE,rc.bottom + BOX_SIDE + BOX_SIDE,
        rc.left + BOX_SIDE - BOX_SIDE,rc.bottom + BOX_SIDE + BOX_SIDE,
        rc.left + BOX_SIDE - BOX_SIDE,rc.bottom - BOX_SIDE + BOX_SIDE,
        rc.left - BOX_SIDE - BOX_SIDE,rc.bottom - BOX_SIDE + BOX_SIDE,

        rc.left - BOX_SIDE - BOX_SIDE,(rc.top + rc.bottom) / 2 + BOX_SIDE,
        rc.left + BOX_SIDE - BOX_SIDE,(rc.top + rc.bottom) / 2 + BOX_SIDE,
        rc.left + BOX_SIDE - BOX_SIDE,(rc.top + rc.bottom) / 2 - BOX_SIDE,
        rc.left - BOX_SIDE - BOX_SIDE,(rc.top + rc.bottom) / 2 - BOX_SIDE,
    };

    int counts[] = { 4,4,4,4,4,4,4,4 };

    CRgnHandle result;
    return result.CreatePolyPolygonRgn(at, counts, 8, WINDING);
}

void Components::Invalidate(BOOL hideSelMarks)
{
    CRgn rgn;
    hideall = hideSelMarks;
    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            CRgnHandle cmpRgn = MakeRgn(components[i]);
            if (rgn.IsNull())
            {
                rgn = cmpRgn;
            }
            else
            {
                rgn.CombineRgn(rgn, cmpRgn, RGN_OR);
                cmpRgn.DeleteObject();
            }
        }
    }

    if (rgn.IsNull() == FALSE)
        ::RedrawWindow((HWND)designer->GetParentForm()->GetHandle(), NULL, rgn, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_INTERNALPAINT);

    hideall = FALSE;
}

void Components::SelectControl(int idx, Component * active)
{
    if (active == designer->GetParentForm())
    {
        //SetStateAll(csFirstSelected, FALSE);
        UnselectAll();
        if (idx == -1)
            designer->GetParentForm()->ShowProperties();
        else
        {
            if ((size_t)idx < components.size())
            {
                components[idx]->Selected = TRUE;
                components[idx]->FirstSelected = TRUE;
                Invalidate();
            }
        }
    }
}

void Components::MoveAfter(Component *comp, Component *after, BOOL childrenToo)
{
    UINT compIdx = FindIndex(comp);
    if (compIdx == -1)
        return;

    UINT afterIdx;

    if (after == NULL)
        afterIdx = GetCount() - 1;
    else
        afterIdx = FindIndex(after);

    if ((int)afterIdx == -1)
        return;

    if (compIdx > afterIdx)
        return;

    components.erase(components.begin() + compIdx);
    //InsertAt(afterIdx+1,comp);
    InsertAt(afterIdx, comp);
    //if(comp->IsControl() && after->IsControl())
    //    ::SetWindowPos((HWND)comp->GetHandle(),(HWND)after->GetHandle(),0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

    if (childrenToo == TRUE)
    {
        for (size_t i = 0; i < components.size(); i++)
        {
            Component * temp = components[i];
            compIdx = FindIndex(comp);
            UINT tempIdx = FindIndex(temp);
            if (temp->GetComponentParent() == comp && tempIdx < compIdx)
            {
                MoveAfter(temp, comp);
                i = 0;
            }
        }
    }
}

void Components::InsertAt(int idx, Component * comp)
{
    components.insert(components.begin() + idx, 1, comp);
}

int Components::FindLeftestIdx(int fromPos)
{
    size_t idx = -1;
    CPoint pt(0, 0);

    CRect rc;
    ::GetClientRect((HWND)GetParentForm()->GetHandle(), &rc);
    int left = rc.right;

    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->Selected &&
            components[i]->FirstSelected == FALSE &&
            components[i]->GetState(csReserved1) == FALSE &&
            components[i]->IsControl() == TRUE)
        {
            pt.x = components[i]->get_Left();
            components[i]->ComponentToDesigner(pt);
            if (pt.x < left && pt.x >= fromPos)
            {
                idx = i;
                left = pt.x;
            }
        }
    }
    if (idx != -1)
        components[idx]->SetState(csReserved1, TRUE);

    return (int)idx;
}

int Components::FindRightestIdx(int fromPos)
{
    size_t idx = -1;
    CPoint pt(0, 0);

    int right = 0;

    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->Selected &&
            components[i]->FirstSelected == FALSE &&
            components[i]->GetState(csReserved1) == FALSE &&
            components[i]->IsControl() == TRUE)
        {
            pt.x = components[i]->get_Left() + components[i]->get_Width();
            components[i]->ComponentToDesigner(pt);
            if (pt.x > right && pt.x >= fromPos)
            {
                idx = i;
                right = pt.x;
            }
        }
    }
    if (idx != -1)
        components[idx]->SetState(csReserved1, TRUE);

    return (int)idx;
}

int Components::FindTopestIdx(int fromPos)
{
    int idx = -1;
    CPoint pt(0, 0);

    CRect rc;
    ::GetClientRect((HWND)GetParentForm()->GetHandle(), &rc);
    int top = rc.bottom;

    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->Selected &&
            components[i]->FirstSelected == FALSE &&
            components[i]->GetState(csReserved1) == FALSE &&
            components[i]->IsControl() == TRUE)
        {
            pt.y = components[i]->get_Top();
            components[i]->ComponentToDesigner(pt);
            if (pt.y < top && pt.y >= fromPos)
            {
                idx = (int)i;
                top = pt.y;
            }
        }
    }
    if (idx != -1)
        components[idx]->SetState(csReserved1, TRUE);

    return idx;
}

int Components::FindBottomestIdx(int fromPos)
{
    int idx = -1;
    CPoint pt(0, 0);

    int bottom = 0;

    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->Selected &&
            components[i]->FirstSelected == FALSE &&
            components[i]->GetState(csReserved1) == FALSE &&
            components[i]->IsControl() == TRUE)
        {
            pt.y = components[i]->get_Top() + components[i]->get_Height();
            components[i]->ComponentToDesigner(pt);
            if (pt.y > bottom && pt.y >= fromPos)
            {
                idx = (int)i;
                bottom = pt.y;
            }
        }
    }
    if (idx != -1)
        components[idx]->SetState(csReserved1, TRUE);

    return idx;
}

//////////////////////////////////////////////////////////////////////////
void Components::AlignLeft(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evAlignComponentsLeft);
    CPoint pt(0, 0);
    int left = 0;
    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;

    if (GetSelCount() > 1)
    {
        pt.y = 0;
        pt.x = firstSelected->get_Left();
        firstSelected->ComponentToDesigner(pt);
        left = pt.x;
    }

    Invalidate(TRUE);
    int rx = 0;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE && components[i] != firstSelected)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            components[i]->DesignerToComponent(pt);

            if (shiftPressed == TRUE)
                rx = components[i]->GetBoundsRect().right;

            components[i]->set_Left(pt.x + intend);

            if (shiftPressed == TRUE)
            {
                CRect r = components[i]->GetBoundsRect();
                r.right = rx;
                components[i]->SetBoundsRect(r);
            }

            pt.x = left;
        }
    }

    if (firstSelected && GetSelCount() == 1)
    {
        if (shiftPressed == TRUE)
            rx = firstSelected->GetBoundsRect().right;

        firstSelected->set_Left(pt.x + intend);

        if (shiftPressed == TRUE)
        {
            CRect r = firstSelected->GetBoundsRect();
            r.right = rx;
            firstSelected->SetBoundsRect(r);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::AlignTop(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evAlignComponentsTop);
    CPoint pt(0, 0);
    int top = 0;

    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;

    if (GetSelCount() > 1)
    {
        pt.x = 0;
        pt.y = firstSelected->get_Top();
        firstSelected->ComponentToDesigner(pt);
        top = pt.y;
    }

    int ry = 0;

    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        pt.y = top;
        pt.x = 0;
        if (components[i]->get_Selected() == TRUE && components[i] != firstSelected)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            components[i]->DesignerToComponent(pt);

            if (shiftPressed == TRUE)
                ry = components[i]->GetBoundsRect().bottom;

            components[i]->set_Top(pt.y + intend);

            if (shiftPressed == TRUE)
            {
                CRect r = components[i]->GetBoundsRect();
                r.bottom = ry;
                components[i]->SetBoundsRect(r);
            }
        }
    }

    if (firstSelected && GetSelCount() == 1)
    {
        if (shiftPressed == TRUE)
            ry = firstSelected->GetBoundsRect().bottom;

        pt.y = top;
        pt.x = 0;
        firstSelected->set_Top(pt.y + intend);

        if (shiftPressed == TRUE)
        {
            CRect r = firstSelected->GetBoundsRect();
            r.bottom = ry;
            firstSelected->SetBoundsRect(r);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::AlignRight(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evAlignComponentsRight);

    CPoint pt(0, 0);
    int  right = 0;
    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;

    if (GetSelCount() > 1)
    {
        pt.y = 0;
        pt.x = firstSelected->get_Left();
        firstSelected->ComponentToDesigner(pt);
        right = pt.x + firstSelected->get_Width();
    }
    else
    {
        if (firstSelected == NULL)
            return;

        if (firstSelected->GetComponentParent()->IsControl())
            right = firstSelected->GetComponentParent()->get_Width();

        if (firstSelected->GetComponentParent()->IsForm())
        {
            CRect rc;
            ::GetClientRect((HWND)firstSelected->GetComponentParent()->GetHandle(), &rc);
            right = rc.Width();
        }
    }

    Invalidate(TRUE);
    int rx = 0;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() && components[i] != firstSelected)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            pt.x = components[i]->get_Left();
            components[i]->DesignerToComponent(pt);

            if (shiftPressed == TRUE)
                rx = components[i]->GetBoundsRect().left;

            components[i]->set_Left(right - components[i]->get_Width() - intend);

            if (shiftPressed == TRUE)
            {
                CRect r = components[i]->GetBoundsRect();
                r.left = rx;
                components[i]->SetBoundsRect(r);
            }
            pt.y = 0;
        }
    }

    if (firstSelected && GetSelCount() == 1)
    {
        if (shiftPressed == TRUE)
            rx = firstSelected->GetBoundsRect().left;

        pt.x = firstSelected->get_Left();
        firstSelected->set_Left(right - firstSelected->get_Width() - intend);

        if (shiftPressed == TRUE)
        {
            CRect r = firstSelected->GetBoundsRect();
            r.left = rx;
            firstSelected->SetBoundsRect(r);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::AlignBottom(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evAlignComponentsBottom);

    CPoint pt(0, 0);
    int  bottom = 0;
    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    BOOL shiftPressed = GetKeyState(VK_SHIFT) < 0;

    if (GetSelCount() > 1)
    {
        pt.x = 0;
        pt.y = firstSelected->get_Top();
        firstSelected->ComponentToDesigner(pt);
        bottom = pt.y + firstSelected->get_Height();
    }
    else
    {
        if (firstSelected == NULL)
            return;

        if (firstSelected->GetComponentParent()->IsControl())
            bottom = firstSelected->GetComponentParent()->get_Height();

        if (firstSelected->GetComponentParent()->IsForm())
        {
            CRect rc;
            ::GetClientRect((HWND)firstSelected->GetComponentParent()->GetHandle(), &rc);
            bottom = rc.Height();
        }
    }

    Invalidate(TRUE);
    int ry = 0;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() && components[i] != firstSelected)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            if ((components[i] == firstSelected && GetSelCount() > 1))
                continue;

            pt.y = components[i]->get_Top();
            components[i]->DesignerToComponent(pt);

            if (shiftPressed == TRUE)
                ry = components[i]->GetBoundsRect().top;

            components[i]->set_Top(bottom - components[i]->get_Height() - intend);

            if (shiftPressed == TRUE)
            {
                CRect r = components[i]->GetBoundsRect();
                r.top = ry;
                components[i]->SetBoundsRect(r);
            }
            pt.x = 0;
        }
    }

    if (firstSelected && GetSelCount() == 1)
    {
        if (shiftPressed == TRUE)
            ry = firstSelected->GetBoundsRect().top;

        pt.y = firstSelected->get_Top();
        firstSelected->set_Top(bottom - firstSelected->get_Height() - intend);

        if (shiftPressed == TRUE)
        {
            CRect r = firstSelected->GetBoundsRect();
            r.top = ry;
            firstSelected->SetBoundsRect(r);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::AlignHoriz(Component *from)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evAlignComponentsHoriz);

    if (GetSelCount() == 1)
    {
        CenterHoriz();
        return;
    }

    Component * temp = GetFirstSel();
    if (temp == NULL)
        return;
    if (temp->IsControl() == FALSE)
        return;

    CPoint pt;
    pt.y = 0;
    pt.x = temp->get_Left();
    temp->ComponentToDesigner(pt);
    int  middle = (pt.x + temp->get_Width() + pt.x) / 2;
    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->Selected == TRUE && components[i]->FirstSelected == FALSE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            pt.x = components[i]->get_Left();
            components[i]->DesignerToComponent(pt);
            components[i]->set_Left(pt.x + (middle - (pt.x + pt.x + components[i]->get_Width()) / 2));
            pt.y = 0;
        }
    }
    pt.x = temp->get_Left();
    temp->DesignerToComponent(pt);
    temp->set_Left(pt.x + (middle - (pt.x + pt.x + temp->get_Width()) / 2));
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::AlignVert(Component *from)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evAlignComponentsVert);

    if (GetSelCount() == 1)
    {
        CenterVert();
        return;
    }

    Component * temp = GetFirstSel();
    if (temp == NULL)
        return;
    if (temp->IsControl() == FALSE)
        return;
    CPoint pt;
    pt.x = 0;
    pt.y = temp->get_Top();
    temp->ComponentToDesigner(pt);
    int  middle = (pt.y + temp->get_Height() + pt.y) / 2;
    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->Selected == TRUE && components[i]->FirstSelected == FALSE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            pt.y = components[i]->get_Top();
            components[i]->DesignerToComponent(pt);

            components[i]->set_Top(pt.y + (middle - (pt.y + pt.y + components[i]->get_Height()) / 2));
        }
    }
    pt.y = temp->get_Top();
    temp->DesignerToComponent(pt);

    temp->set_Top(pt.y + (middle - (pt.y + pt.y + temp->get_Height()) / 2));
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::MakeSameWidth(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evMakeSameWidth);

    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;
    int  width = 0;
    int selCount = GetSelCount();
    if (selCount > 1)
        width = firstSelected->get_Width();
    else
    {
        CRect rc;
        ::GetClientRect((HWND)firstSelected->GetComponentParent()->GetHandle(), &rc);
        width = rc.Width();
    }

    Invalidate(TRUE);

    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected())
        {
            if (components[i]->IsControl() == FALSE)
                continue;

            if ((components[i] == firstSelected && selCount > 1))
                continue;

            if (selCount == 1)
                components[i]->set_Left(intend);

            components[i]->set_Width(width - intend * 2);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::MakeSameHeight(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evMakeSameHeight);

    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    int selCount = GetSelCount();
    int  height = 0;
    if (selCount > 1)
        height = firstSelected->get_Height();
    else
    {
        CRect rc;
        ::GetClientRect((HWND)firstSelected->GetComponentParent()->GetHandle(), &rc);
        height = rc.Height();
    }

    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            if ((components[i] == firstSelected && selCount > 1))
                continue;

            if (selCount == 1)
                components[i]->set_Top(intend);
            components[i]->set_Height(height - intend * 2);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::MakeSameSize(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evMakeSameSize);

    Component * temp = GetFirstSel();
    if (temp == NULL)
        return;
    if (temp->IsControl() == FALSE)
        return;

    int  width = temp->get_Width() + intend;
    int  height = temp->get_Height() + intend;
    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->Selected == TRUE && components[i]->FirstSelected == FALSE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            components[i]->set_Height(height);
            components[i]->set_Width(width);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::MakeGoldenSectionWidht()
{
    Invalidate(TRUE);
    double delta;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            delta = components[i]->get_Height();
            delta = _round((delta / 0.382)*0.618);
            components[i]->set_Width(_round(delta));
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::MakeGoldenSectionHeight()
{
    Invalidate(TRUE);
    double delta;
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            delta = components[i]->get_Width();
            delta = (delta / 0.382)*0.618;
            components[i]->set_Height(_round(delta));
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::CenterHoriz()
{
    CRect rc;
    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            ::GetClientRect((HWND)components[i]->GetComponentParent()->GetHandle(), &rc);
            int centerX = rc.Width() / 2;
            components[i]->set_Left(centerX - (components[i]->get_Width() / 2));
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::CenterVert()
{
    CRect rc;
    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            ::GetClientRect((HWND)components[i]->GetComponentParent()->GetHandle(), &rc);
            int centerY = rc.Height() / 2;
            components[i]->set_Top(centerY - (components[i]->get_Height() / 2));
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::ToParent(Component *from, long intend)
{
    if (from != designer->GetParentForm())
        return;
    StopEvent(evToParent);
    Component * temp = GetFirstSel();
    if (temp == NULL)
        return;
    if (temp->IsControl() == FALSE)
        return;

    Invalidate(TRUE);
    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->get_Selected() == TRUE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            CRect rc;
            ::GetClientRect((HWND)components[i]->GetComponentParent()->GetHandle(), rc);
            components[i]->set_Left(intend);
            components[i]->set_Top(intend);
            components[i]->set_Height(rc.Height() - intend * 2);
            components[i]->set_Width(rc.Width() - intend * 2);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::CenterGroupHoriz(Component *form, long val)
{
    if (form != designer->GetParentForm())
        return;
    StopEvent(evCenterGroupHoriz);

    if (GetSelCount() == 1)
    {
        CenterHoriz();
        return;
    }

    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;

    if (firstSelected->IsControl() == FALSE)
        return;

    CPoint pt;
    pt.y = 0;
    pt.x = firstSelected->get_Left();
    firstSelected->ComponentToDesigner(pt);
    int  middle = (pt.x + firstSelected->get_Width() + pt.x) / 2;
    Invalidate(TRUE);

    double commonWidth = 0;
    for (int count = 0; count < GetCount(); count++)
    {
        if (components[count]->Selected == TRUE && components[count]->FirstSelected == FALSE &&
            components[count]->IsControl() == TRUE)
            commonWidth += (double)components[count]->get_Width() + (double)val / 2;
    }

    CRect rc;
    ::GetClientRect((HWND)GetParentForm()->GetHandle(), &rc);
    if (_round(commonWidth) > rc.Width())
        return;

    int left = middle - _round(commonWidth / 2);
    if (left < 0)
        return;

    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->Selected == TRUE && components[i]->FirstSelected == FALSE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;

            int currIdx = FindLeftestIdx(0);
            if (currIdx == -1)
                continue;

            if (components[currIdx] == firstSelected)
            {
                i = 0;
                continue;
            }

            pt.x = left;
            components[currIdx]->DesignerToComponent(pt);
            components[currIdx]->set_Left(pt.x);
            left += components[currIdx]->get_Width() + val;
            i = 0;
        }
    }
    SetStateAll(csReserved1, FALSE, FALSE);
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::CenterGroupVert(Component *form, long val)
{
    if (form != designer->GetParentForm())
        return;
    StopEvent(evCenterGroupVert);

    if (GetSelCount() == 1)
    {
        CenterVert();
        return;
    }

    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    CPoint pt;
    pt.x = 0;
    pt.y = firstSelected->get_Top();
    firstSelected->ComponentToDesigner(pt);
    int  middle = (pt.y + firstSelected->get_Height() + pt.y) / 2;
    Invalidate(TRUE);

    double commonHeight = 0;
    for (int count = 0; count < GetCount(); count++)
    {
        if (components[count]->Selected == TRUE && components[count]->FirstSelected == FALSE &&
            components[count]->IsControl() == TRUE)
            commonHeight += (double)components[count]->get_Height() + (double)val / 2;
    }

    CRect rc;
    ::GetClientRect((HWND)GetParentForm()->GetHandle(), &rc);
    if (_round(commonHeight) > rc.Height())
        return;

    int top = middle - _round(commonHeight / 2);
    if (top < 0)
        return;

    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->Selected == TRUE && components[i]->FirstSelected == FALSE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;

            int currIdx = FindTopestIdx(0);
            if (currIdx == -1)
                continue;

            if (components[currIdx] == firstSelected)
            {
                i = 0;
                continue;
            }
            pt.y = top;
            components[currIdx]->DesignerToComponent(pt);
            components[currIdx]->set_Top(pt.y);
            top += components[currIdx]->get_Height() + val;
            i = 0;
        }
    }
    Invalidate();
    SetStateAll(csReserved1, FALSE, FALSE);
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}

void Components::ChangeComponentsParent(Component *form)
{
    if (form != designer->GetParentForm())
        return;
    StopEvent(evChangeParent);

    Component * firstSelected = GetFirstSel();
    if (firstSelected == NULL)
        return;
    if (firstSelected->IsControl() == FALSE)
        return;

    if (GetSelCount() == 1)
    {
        ChangeParent(GetParentForm());
        return;
    }

    int idx = FindParentIndex(firstSelected);
    if (idx != -1)
    {
        if (components[idx]->get_Selected())
            return;
    }

    Invalidate(TRUE);

    for (int i = 0; i < GetCount(); i++)
    {
        if (components[i]->Selected == TRUE && components[i]->FirstSelected == FALSE)
        {
            if (components[i]->IsControl() == FALSE)
                continue;

            Component * parent = firstSelected;
            if (components[i]->GetComponentParent() == parent)
                parent = firstSelected->GetComponentParent();

            CRect bounds = components[i]->GetBoundsRect();
            if (components[i]->GetComponentParent() != GetParentForm())
                components[i]->ComponentToDesigner(bounds);
            components[i]->SetComponentParent(parent);
            components[i]->DesignerToComponent(bounds);
            components[i]->SetBoundsRect(bounds);
        }
    }
    Invalidate();
    ((CFormComponent *)GetParentForm())->AddUndo(GetParentForm());
}
//////////////////////////////////////////////////////////////////////////
ComponentArray * Components::Clone(BOOL onlySelected)
{
    CRect rc;
    Component *comp;
    ComponentArray * comps = new ComponentArray;
    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected() == FALSE &&  onlySelected == TRUE)
            continue;
        comp = components[i]->Clone(GetDesigner());
        rc = components[i]->GetBoundsRect();
        components[i]->ComponentToDesigner(rc);
        comp->SetBoundsRect(rc);
        comps->push_back(comp);
    }
    return comps;
}

ComponentArray * Components::Clone(Component * comp)
{
    ComponentArray * comps = new ComponentArray;
    comps->push_back(comp->Clone(GetDesigner()));
    return comps;
}

void Components::ChangeParent(Component *parent)
{
    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i]->get_Selected())
        {
            if (components[i]->IsControl() == FALSE)
                continue;
            if (components[i]->GetComponentParent() == parent)
                continue;

            CRect bounds = components[i]->GetBoundsRect();
            if (components[i]->GetComponentParent() != GetParentForm())
                components[i]->ComponentToDesigner(bounds);
            components[i]->SetComponentParent(parent);
            components[i]->DesignerToComponent(bounds);
            components[i]->SetBoundsRect(bounds);
        }
    }
}

int Components::ControlsCount()
{
    int count = 0;
    for (size_t i = 0; i < components.size(); i++)
        if (components[i]->IsControl())
            count++;
    return count;
}

BOOL Components::SetTabIndex(CPoint & pt, long & val)
{
    Component * comp = ComponentFromPt(pt);
    return SetTabIndex(comp, val);
}

BOOL Components::SetTabIndex(Component *comp, long &val)
{
    if (comp)
    {
        if (comp->IsControl() == FALSE || comp->EnableTabIndex() == FALSE)
            return FALSE;
        long count = FindMaxTabIndex();
        val++;
        if (val > count)
            val = FindMinTabIndex();
        long tempNum = comp->get_TabIndex();
        for (int i = 0; i < GetCount(); i++)
        {
            if (GetAt(i)->get_TabIndex() == val && GetAt(i)->EnableTabIndex() == TRUE)
            {
                GetAt(i)->set_TabIndex(tempNum);
                break;
            }
        }
        comp->set_TabIndex(val);
        return TRUE;
    }
    return FALSE;
}

void Components::ReSetTabIndex()
{
    CAtlArray<int> tabOrder;
    int maxIdx = FindMaxTabIndex();
    for(int idx = FindMinTabIndex(); idx <= maxIdx; idx++)
    {
        int pos = FindByTabIndex(idx);
        if(pos != -1)
        {
            tabOrder.Add(pos);
        }
    }

    for(int i=0; i < tabOrder.GetCount(); i++)
    {
        GetAt(tabOrder.GetAt(i))->set_TabIndex(i+1);
    }
}

long Components::FindMaxTabIndex()
{
    long maxTab = 0;
    for (long i = 0; i < GetCount(); i++)
    {
        int tab = GetAt(i)->get_TabIndex();
        if (maxTab < tab && tab != -1)
            maxTab = GetAt(i)->get_TabIndex();
    }
    return maxTab;
}

long Components::FindNextTabIndex(long index)
{
    if (index != -1)
    {
        long maxTab = FindMaxTabIndex();
        long nextTab = index + 1;
        if (nextTab > maxTab)
            return FindMinTabIndex();
        for (; nextTab <= maxTab; nextTab++)
        {
            for (long j = 0; j < GetCount(); j++)
            {
                if (nextTab == GetAt(j)->get_TabIndex())
                    return nextTab;
            }
        }
    }
    return -1;
}

long Components::FindMinTabIndex()
{
    long minTab = 0xFFFF;
    for (long i = 0; i < GetCount(); i++)
    {
        int tab = GetAt(i)->get_TabIndex();
        if (minTab > tab && tab != -1)
            minTab = GetAt(i)->get_TabIndex();
    }
    return minTab;
}

int Components::FindByTabIndex(long tab)
{
    for (int i = 0; i < GetCount(); i++)
    {
        if (GetAt(i)->get_TabIndex() == tab)
            return i;
    }
    return -1;
}

void Components::SelectAll(Component* form)
{
    if (form != designer->GetParentForm())
        return;
    StopEvent(evSelectAll);
    BOOL firstSelectedFlag = FALSE;
    Invalidate(TRUE);
    for (int count = 0; count < GetCount(); count++)
    {
        firstSelectedFlag |= components[count]->FirstSelected;
        components[count]->Selected = TRUE;
    }

    if (firstSelectedFlag == FALSE && GetCount() != 0)
    {
        components[0]->FirstSelected = TRUE;
    }
    Invalidate();
    PostEvent(evSetActiveForm, GetParentForm());
}
//////////////////////////////////////////////////////////////////////////
