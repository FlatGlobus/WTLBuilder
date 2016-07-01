// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "EventLib.h"
#include "DialogImpl.h"
#include "Register.h"
#include "GDIUtil.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
namespace Form
{
REGISTER_FORM(CDialogImpl,Form)
CDialogImpl::CDialogImpl(LPTSTR _name):CFormComponent(_name)
{
    int xScreen=::GetSystemMetrics(SM_CXSCREEN);
    int yScreen=::GetSystemMetrics(SM_CYSCREEN);
    bounds.left=_round(xScreen/3.5);
    bounds.right=xScreen/2;
    bounds.top=yScreen/3;
    bounds.bottom=_round(bounds.right*0.75);
    SetBoundsRect(bounds);
	
	m_hWndClient=NULL;
	bkColor=COLOR_BTNFACE;
}
	
CDialogImpl::~CDialogImpl(void)
{
}

BOOL CDialogImpl::CreateComponent(Component * Parent)
{
	if (::IsWindow(Create((HWND)Parent->GetHandle(), GetBoundsRect(), get_Caption())))
		return TRUE;
	return FALSE;
}

void CDialogImpl::OnFinalMessage(HWND /*hWnd*/)
{
	
}

void CDialogImpl::InitProperty(void)
{
    CFormComponent::InitProperty();

	SET_PROP_VALUE(InternalWindowStyle,WS_POPUP | WS_CAPTION | WS_SYSMENU)
	SET_PROP_VALUE(InternalWindowStyleEx,0)
	SET_PROP_VALUE(WindowStyle, WS_POPUP)
	SET_PROP_VALUE(BorderStyle, WS_DLGFRAME)
	SET_PROP_VALUE(Visible, FALSE)
	PUBLIC_PROPERTY(Visible,FALSE)
	
	REMOVE_PROPERTY(Child)
	REMOVE_PROPERTY(WindowClass)
	REMOVE_PROPERTY(WndClient)
	REMOVE_PROPERTY(WndToolBar)
	REMOVE_PROPERTY(WndStatusBar)
	REMOVE_PROPERTY(Menu)
	REMOVE_PROPERTY(MDIChild)
}

CRect CDialogImpl::GetMinRect()
{
    minRC=Component::GetMinRect();
    return minRC;
}
//////////////////////////////////////////////////////////////////////////
}