// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "SplashWnd.h"
#include "Register.h"
#include "GDIUtil.h"
//////////////////////////////////////////////////////////////////////////
namespace Form
{
    REGISTER_FORM(CSplashWnd,Form)
    CSplashWnd::CSplashWnd(LPTSTR _name):CFormComponent(_name)
    {
        int xScreen=::GetSystemMetrics(SM_CXSCREEN);
        int yScreen=::GetSystemMetrics(SM_CYSCREEN);
        bounds.left=_round(xScreen/3.5);
        bounds.right=xScreen/2;
        bounds.top=yScreen/3;
        bounds.bottom=_round(bounds.right*0.75);
        SetBoundsRect(bounds);

        m_hWndClient=NULL;
        bkColor=COLOR_WINDOW;
    }

    CSplashWnd::~CSplashWnd(void)
    {
    }

    BOOL CSplashWnd::CreateComponent(Component * Parent)
    {
		if (::IsWindow(Create((HWND)Parent->GetHandle(), GetBoundsRect())))
            return TRUE;
        return FALSE;
    }

    void CSplashWnd::OnFinalMessage(HWND /*hWnd*/)
    {
        //RemoveProperties();
        //delete this;
    }

    void CSplashWnd::InitProperty(void)
    {
        CFormComponent::InitProperty();
		SET_WIN_STYLE(WS_POPUP | WS_VISIBLE)
		SET_WIN_STYLE_EX(WS_EX_TOOLWINDOW)
        HIDE_PROPERTY(Caption)
            HIDE_PROPERTY(Visible)
            HIDE_PROPERTY(MinimizeBox)
            HIDE_PROPERTY(MaximizeBox)
            HIDE_PROPERTY(SysMenu)
            HIDE_PROPERTY(CaptionBar)
            HIDE_PROPERTY(Border)
            HIDE_PROPERTY(ModalFrame)
            HIDE_PROPERTY(Ctrl3d)
            HIDE_PROPERTY(TopMost)
            HIDE_PROPERTY(Transparent)
            HIDE_PROPERTY(MDIChild)
            HIDE_PROPERTY(ToolWindow)
            HIDE_PROPERTY(ContextHelp)
            HIDE_PROPERTY(EnableLayout)
            HIDE_PROPERTY(NPositions)
            HIDE_PROPERTY(ClipSiblings)
            HIDE_PROPERTY(ClipChildren)
            HIDE_PROPERTY(AcceptFiles)
            HIDE_PROPERTY(WindowEdge)
            HIDE_PROPERTY(ClientEdge)
            HIDE_PROPERTY(ControlParent)
            HIDE_PROPERTY(StaticEdge)
            HIDE_PROPERTY(AppWindow)
            HIDE_PROPERTY(WndClient)
            HIDE_PROPERTY(WndToolBar)
            HIDE_PROPERTY(WndStatusBar)
            HIDE_PROPERTY(Menu)
            HIDE_PROPERTY(HScroll)
            HIDE_PROPERTY(VScroll)
            HIDE_PROPERTY(WindowClass)
            HIDE_PROPERTY(Color)

    }
    //////////////////////////////////////////////////////////////////////////
}