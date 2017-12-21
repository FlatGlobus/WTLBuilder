// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "WindowImpl.h"
#include "Register.h"
#include "GDIUtil.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
namespace Form
{
REGISTER_FORM(CWindowImpl,Form)
CWindowImpl::CWindowImpl(LPTSTR _name):CFormComponent(_name)
{
	bkColor=COLOR_WINDOW;
    int xScreen=::GetSystemMetrics(SM_CXSCREEN);
    int yScreen=::GetSystemMetrics(SM_CYSCREEN);
    bounds.left=_round(xScreen/3.5);
    bounds.right=xScreen/2;
    bounds.top=yScreen/3;
    bounds.bottom=_round(bounds.right*0.75);
    SetBoundsRect(bounds);
}
	
CWindowImpl::~CWindowImpl(void)
{
}

BOOL CWindowImpl::CreateComponent(Component * Parent)
{
	return ::IsWindow(Create((HWND)Parent->GetHandle(), GetBoundsRect(), get_Caption()));
}

void CWindowImpl::OnFinalMessage(HWND /*hWnd*/)
{
}

void CWindowImpl::InitProperty(void)
{
	CFormComponent::InitProperty();
	
	SET_WIN_STYLE(CControlWinTraits::GetWndStyle(0))
	SET_WIN_STYLE_EX(CControlWinTraits::GetWndExStyle(0))
	SET_PROP_VALUE(WindowStyle, WS_CHILD)

    DEFINE_PROPERTY(Border,BOOL,CWindowImpl,FALSE)
    DEFINE_PROPERTY(Enabled,BOOL,CWindowImpl,TRUE)
    DEFINE_PROPERTY(TabStop,BOOL,CWindowImpl,FALSE)
    DEFINE_PROPERTY(Group,BOOL,CWindowImpl,FALSE)
	
    PUBLIC_PROPERTY_STR(_T("WindowClass.CommonResID"),FALSE)
    REMOVE_PROPERTY(WndClient)
    REMOVE_PROPERTY(WndToolBar)
    REMOVE_PROPERTY(WndStatusBar)
    REMOVE_PROPERTY(Menu)
	PUBLIC_PROPERTY(Caption, FALSE)
	REMOVE_PROPERTY(MinimizeBox)
	REMOVE_PROPERTY(MaximizeBox)
	REMOVE_PROPERTY(SysMenu)
	REMOVE_PROPERTY(CaptionBar)
	REMOVE_PROPERTY(ModalFrame)
	REMOVE_PROPERTY(MDIChild)
	REMOVE_PROPERTY(AppWindow)
	REMOVE_PROPERTY(Icon)
	REMOVE_PROPERTY(ToolWindow)
	PUBLIC_PROPERTY(WindowStyle,FALSE)
    PUBLIC_PROPERTY(BorderStyle,FALSE)
}

BOOL __stdcall CWindowImpl::get_IsControl()
{
	return TRUE;
}

BOOL __stdcall CWindowImpl::get_IsForm()
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
}