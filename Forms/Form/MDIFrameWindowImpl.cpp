// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "MDIFrameWindowImpl.h"
#include "Register.h"
#include "GDIUtil.h"
//////////////////////////////////////////////////////////////////////////
namespace Form
{
    REGISTER_FORM(CMDIFrameWindowImpl,Form)
//////////////////////////////////////////////////////////////////////////
    CMDIFrameWindowImpl::CMDIFrameWindowImpl(LPTSTR _name):CFormComponent(_name) 
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

    CMDIFrameWindowImpl::~CMDIFrameWindowImpl(void)
    {
    }

    BOOL CMDIFrameWindowImpl::CreateComponent(Component * Parent)
    {
		if (::IsWindow(Create((HWND)Parent->GetHandle(), GetBoundsRect(), get_Caption())))
            return TRUE;
        return FALSE;
    }

    void CMDIFrameWindowImpl::OnFinalMessage(HWND /*hWnd*/)
    {
    }

    void CMDIFrameWindowImpl::InitProperty(void)
    {
        CFormComponent::InitProperty();
		
		SET_PROP_VALUE(InternalWindowStyle, CFrameWinTraits::GetWndStyle(0))
		SET_PROP_VALUE(InternalWindowStyleEx, CFrameWinTraits::GetWndExStyle(0))
		SET_PROP_VALUE(WindowStyle, WS_OVERLAPPED)
		SET_PROP_VALUE(BorderStyle, WS_THICKFRAME)
		REMOVE_PROPERTY(MDIChild)
    }

    CRect CMDIFrameWindowImpl::GetMinRect()
    {
        if(::IsWindow(m_hWndClient))
        {
            int idx=GetComponents()->FindByHandle(m_hWndClient);
            if(idx!=-1)
                minRC=GetComponents()->GetAt(idx)->GetMinRect();
            else
                return minRC=CRect(0,0,0,0);
        }
        else
            minRC=Component::GetMinRect();

        if(::IsWindow(m_hWndStatusBar))
        {
            CRect statusBarRc;
            ::GetWindowRect(m_hWndStatusBar,statusBarRc);
            minRC.bottom+=statusBarRc.Height();
        }

        return minRC;
    }
    //////////////////////////////////////////////////////////////////////////
}