// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "CtrlComponent.h"
//////////////////////////////////////////////////////////////////////////
long CorrectControlID(LPCTSTR ID);
//////////////////////////////////////////////////////////////////////////
BOOL ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0)
{
    DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
    DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
    if(dwStyle == dwNewStyle)
        return FALSE;

    ::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
    if(nFlags != 0)
    {
        ::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
            SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
    }
    return TRUE;
}

BOOL ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0)
{
    DWORD dwStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
    DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
    if(dwStyle == dwNewStyle)
        return FALSE;

    ::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewStyle);
    if(nFlags != 0)
    {
        ::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
            SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
ControlComponentBase::ControlComponentBase(LPCTSTR _name):Component(_name),
visible(TRUE),enabletoolTip(FALSE),useControlFont(FALSE),layout(FALSE),
leftLayout(this),topLayout(this),rightLayout(this),bottomLayout(this),hCenterLayout(this),
vCenterLayout(this),focus(FALSE)
{
}

ControlComponentBase::~ControlComponentBase()
{
}

LRESULT ControlComponentBase::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    Component::CreateComponent(Parent);
    if(::IsWindow((HWND)GetHandle()))
    {
        designer=Parent->GetDesigner();
        ::ShowWindow((HWND)GetHandle(),SW_SHOW);
        ctrlFont.Change.SetObject(this);
        ctrlFont.Change.SetMethod(&ControlComponentBase::SetControlFont);
    }
    bHandled=FALSE;
    SetMsgHandled(FALSE);
    return 0;
}

LRESULT ControlComponentBase::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if(::IsWindow((HWND)GetHandle()))	
    {
        bounds=GetBoundsRect();
        UpdateBoundsProp(bounds);
    }
    bHandled=FALSE;
    SetMsgHandled(FALSE);
    return FALSE;
}

LRESULT ControlComponentBase::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (selected)
	{
		CClientDC dc(designer->m_hWnd);
		Paint(dc);
	}
	bHandled = FALSE;
	SetMsgHandled(FALSE);
	return FALSE;
}

LRESULT ControlComponentBase::OnSetCtrlFont(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    CFontEx * parentFont=(CFontEx *)lParam;
    if(useControlFont==FALSE && parentFont!=NULL)
    {
        LOGFONT lf;
        parentFont->get_LogFont(lf);
        ctrlFont.set_LogFont(lf);
        ::SendMessage((HWND)GetHandle(),WM_SETFONT,(WPARAM)(HFONT)ctrlFont,TRUE);
        SetModified();
    }
    bHandled=TRUE;
    return TRUE;
}

LRESULT ControlComponentBase::OnGetCtrlFont(UINT,WPARAM,LPARAM, BOOL& bHandled)
{
    bHandled=TRUE;
    return (LRESULT)&ctrlFont;
}
 
typedef DWORD WindowStyle;
void ControlComponentBase::InitProperty(void)
{
	CControlWinTraits tr;
    Component::InitProperty();
    DEFINE_PROPERTY(InternalWindowStyle,DWORD,ControlComponentBase, tr.GetWndStyle(0))
    PUBLIC_PROPERTY(InternalWindowStyle,FALSE)
    DEFINE_PROPERTY(InternalWindowStyleEx,DWORD,ControlComponentBase, tr.GetWndExStyle(0))
    PUBLIC_PROPERTY(InternalWindowStyleEx,FALSE)
	DEFINE_WIN_PROPERTY(Border,ControlComponentBase)
	DEFINE_WIN_PROPERTY(Enabled,ControlComponentBase)
    DEFINE_PROPERTY(Visible,BOOL,ControlComponentBase,TRUE)
	DEFINE_WIN_PROPERTY(ClientEdge,ControlComponentBase)
    DEFINE_PROPERTY(ToolTip,CString,ControlComponentBase,_T(""))
    DEFINE_PROPERTY(EnableToolTip,BOOL,ControlComponentBase,FALSE)
    DEFINE_PROPERTY(ID,CString,ControlComponentBase,_T(""))
    DEFINE_PROPERTY(TabStop,BOOL,ControlComponentBase,enableTabIndex)
    DEFINE_PROPERTY(Group,BOOL,ControlComponentBase,FALSE)
    DEFINE_PROPERTY(HScroll,BOOL,ControlComponentBase,FALSE)
    PUBLIC_PROPERTY(HScroll,FALSE)
    DEFINE_PROPERTY(VScroll,BOOL,ControlComponentBase,FALSE)
    PUBLIC_PROPERTY(VScroll,FALSE)

    DEFINE_PROPERTY(Font,BOOL,ControlComponentBase,useControlFont)
    ctrlFont.AddProperty(_T("Font"),objprop);			

    DEFINE_PROPERTY(Layout,BOOL,ControlComponentBase,FALSE)
        leftLayout.AddProperty(_T("Layout"),_T("Left"),objprop);
        topLayout.AddProperty(_T("Layout"),_T("Top"),objprop);
        rightLayout.AddProperty(_T("Layout"),_T("Right"),objprop);
        bottomLayout.AddProperty(_T("Layout"),_T("Bottom"),objprop);
        hCenterLayout.AddProperty(_T("Layout"),_T("HCenter"),objprop);
        vCenterLayout.AddProperty(_T("Layout"),_T("VCenter"),objprop);
    DEFINE_PROPERTY(Focus,BOOL,ControlComponentBase,FALSE)			

    DEFINE_WIN_PROPERTY(Transparent,ControlComponentBase)
    DEFINE_WIN_PROPERTY(ClipSiblings,ControlComponentBase)
    DEFINE_WIN_PROPERTY(ClipChildren,ControlComponentBase)
    DEFINE_WIN_PROPERTY(AcceptFiles,ControlComponentBase)
        //DEFINE_PROPERTY(WindowEdge,BOOL,ControlComponentBase<T>,FALSE)
        //DEFINE_PROPERTY(ClientEdge,BOOL,ControlComponentBase<T>,FALSE)
    DEFINE_PROPERTY(ControlParent,BOOL,ControlComponentBase,FALSE)
        //DEFINE_PROPERTY(StaticEdge,BOOL,ControlComponentBase<T>,FALSE)

    DEFINE_PROPERTY_2(DoContained,BOOL,ControlComponentBase,FALSE)
    BEGIN_SUB_PROPERTY(_T("DoContained"),ControlComponentBase)
        DEFINE_SUB_PROPERTY_2(MessageMapID,long,ControlComponentBase,0)
    END_SUB_PROPERTY    

    DEFINE_PROPERTY_2(Localize,BOOL,ControlComponentBase,TRUE)
	//DEFINE_PROPERTY_2(WindowStyle,WindowStyle,ControlComponentBase,WS_CHILD)
	//PUBLIC_PROPERTY(WindowStyle,FALSE)
}

void ControlComponentBase::SetControlFont(CFontEx *font) 
{
    if(useControlFont==TRUE)
    {
        ::SendMessage((HWND)GetHandle(),WM_SETFONT,(WPARAM)(HFONT)*font,TRUE);
        SetModified();
    }
}

void ControlComponentBase::set_Font(BOOL val)
{
    useControlFont=val;
    if(val==FALSE)
    {
        CFontEx * pf=(CFontEx *)::SendMessage((HWND)GetParentForm()->GetHandle(),WM_GETCTRLFONT,0,0);
        if(pf)
            ::SendMessage((HWND)GetHandle(),WM_SETFONT,(WPARAM)(HFONT)*pf,TRUE);
    }
    else
    {
        ::SendMessage((HWND)GetHandle(),WM_SETFONT,(WPARAM)(HFONT)ctrlFont,TRUE);
    }
    SetModified();
}

BOOL ControlComponentBase::get_Font()
{
    return useControlFont;
}

void ControlComponentBase::set_Focus(BOOL val)
{
    if(val==TRUE)
    {
        Components * components=GetComponents();
        Component * component;
        for(int i=0; i < components->GetCount();i++)
        {
            component=components->GetAt(i);
            if(component->IsControl()==TRUE)
                component->set_Focus(FALSE);
        }
    }
    SetModified();
    focus=val;
}

BOOL ControlComponentBase::get_Focus()
{
    return focus;
}

void ControlComponentBase::set_Visible(BOOL val)
{
    visible=val;
    SetModified();
}

BOOL ControlComponentBase::get_Visible()
{
    return visible;
}

void ControlComponentBase::set_ToolTip(CString val)
{
    toolTip=val;
	SET_PROP_VALUE(ToolTip,toolTip)
    SetModified();
}

CString ControlComponentBase::get_ToolTip()
{
    return toolTip;
}

void ControlComponentBase::set_EnableToolTip(BOOL val)
{
    enabletoolTip=val;
	SET_PROP_VALUE(EnableToolTip,enabletoolTip)
    SetModified();
}

BOOL ControlComponentBase::get_EnableToolTip()
{
    return enabletoolTip;
}

void ControlComponentBase::set_ID(CString val)
{
    strID=val;
	//long id = CorrectControlID(val);
	//if(id != -1)
	//	set_UniqueID(id);
    SetModified();
}

CString ControlComponentBase::get_ID(void)
{
    if(strID.IsEmpty())
    {
        CString cmpName=get_Name();
        if(cmpName.Find(_T("m_"))==0)
            cmpName.Delete(0,2);
        strID.Format(_T("IDC_%s_%s"),(LPCTSTR)designer->GetParentForm()->get_Name(),(LPCTSTR)cmpName);
        strID.MakeUpper();
    }

    return strID;
}

BOOL ControlComponentBase::IsControl()
{
    return TRUE;
}

void ControlComponentBase::SetBoundsRect(CRect rc)
{
    Component::SetBoundsRect(rc);
    if(::IsWindow((HWND)GetHandle()))
    {
        //::SetWindowPos((HWND)GetHandle(),NULL,rc.left,rc.top,rc.Width(),rc.Height(),
        //    SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOCOPYBITS);
		::MoveWindow((HWND)GetHandle(), rc.left, rc.top, rc.Width(), rc.Height(),TRUE);
    }
}

CRect ControlComponentBase::GetBoundsRect(void)
{
    CRect rc;
    if(::IsWindow((HWND)GetHandle()) && designer && GetState(csLoading)==FALSE && 
        GetState(csCreating)==FALSE)	
    {
        ::GetWindowRect((HWND)GetHandle(),&rc);
        designer->ScreenToClient(&rc);
        DesignerToComponent(rc);
    }
    else
        rc=Component::GetBoundsRect();
    return rc;
}

DWORD ControlComponentBase::get_InternalWindowStyle()
{
    return GET_PROP_VALUE(DWORD,InternalWindowStyle)
}

void ControlComponentBase::set_InternalWindowStyle(DWORD s)
{
    if(::IsWindow((HWND)GetHandle()))	
        ModifyStyle((HWND)GetHandle(),0xFFFFFFFFL,s|WS_VISIBLE,SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_SHOWWINDOW|SWP_FRAMECHANGED|SWP_NOACTIVATE|SWP_NOCOPYBITS);
	
    SET_PROP_VALUE(InternalWindowStyle,s)
    SetModified();
}

DWORD ControlComponentBase::get_InternalWindowStyleEx()
{
	return GET_PROP_VALUE(DWORD, InternalWindowStyleEx)
}

void ControlComponentBase::set_InternalWindowStyleEx(DWORD s)
{
    if(::IsWindow((HWND)GetHandle()))	
        ModifyStyleEx((HWND)GetHandle(),0xFFFFFFFFL,s,SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_SHOWWINDOW|SWP_FRAMECHANGED|SWP_NOACTIVATE|SWP_NOCOPYBITS);
	SET_PROP_VALUE(InternalWindowStyleEx, s)
    SetModified();
}

//void ControlComponentBase::set_Color(CColorref val)
//{
//    if(val!=-1)
//    {
//        bkColor=val;
//        bkBrush.Color=bkColor;
//        ::InvalidateRect((HWND)GetHandle(),NULL,TRUE);
//    }
//    SetModified();
//}
//
//CColorref ControlComponentBase::get_Color()
//{
//    return bkColor;
//}

void ControlComponentBase::set_Layout(BOOL val)
{
    layout=val;
    SetModified();
    ::SendMessage((HWND)GetParentForm()->GetHandle(),WM_UPDATELAYOUT,0,0);
}

BOOL ControlComponentBase::get_Layout(void)
{
    return layout;
}

CLayout *	ControlComponentBase::get_leftLayout()
{
    return &leftLayout;
}

CLayout	*	ControlComponentBase::get_topLayout()
{
    return &topLayout;
}

CLayout	*	ControlComponentBase::get_rightLayout()
{
    return &rightLayout;
}

CLayout	*	ControlComponentBase::get_bottomLayout()
{
    return &bottomLayout;
}

CLayout	*	ControlComponentBase::get_hCenterLayout()
{
    return &hCenterLayout;
}

CLayout	*	ControlComponentBase::get_vCenterLayout()
{
    return &vCenterLayout;
}
