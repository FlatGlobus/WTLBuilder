// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "FrameWindowImpl.h"
#include "Register.h"
#include "GDIUtil.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
namespace Form
{
    REGISTER_FORM(CFrameWindowImpl,Form)
	CFrameWindowImpl::CFrameWindowImpl(LPTSTR _name):CFormComponent(_name)
    {
        m_hWndClient=NULL;
        bkColor=COLOR_WINDOW;

        int xScreen=::GetSystemMetrics(SM_CXSCREEN);
        int yScreen=::GetSystemMetrics(SM_CYSCREEN);
        bounds.left=_round(xScreen/3.5);
        bounds.right=xScreen/2;
        bounds.top=yScreen/3;
        bounds.bottom=_round(bounds.right*0.75);
        SetBoundsRect(bounds);        
    }

	CFrameWindowImpl::~CFrameWindowImpl(void)
    {
    }

    BOOL CFrameWindowImpl::CreateComponent(Component * Parent)
    {
		if (::IsWindow(Create((HWND)Parent->GetHandle(), GetBoundsRect(), get_Caption())))
            return TRUE;
        return FALSE;
    }

    void CFrameWindowImpl::OnFinalMessage(HWND /*hWnd*/)
    {
    }

    void CFrameWindowImpl::InitProperty(void)
    {
        CFormComponent::InitProperty();
		
		SET_PROP_VALUE(InternalWindowStyle, CFrameWinTraits::GetWndStyle(0))
		SET_PROP_VALUE(InternalWindowStyleEx, CFrameWinTraits::GetWndExStyle(0))
		SET_PROP_VALUE(WindowStyle, WS_OVERLAPPED)
		SET_PROP_VALUE(BorderStyle, WS_THICKFRAME)
		//SET_PROP_VALUE(Visible, TRUE)
		REMOVE_PROPERTY(MDIChild)
	}

    CRect CFrameWindowImpl::GetMinRect()
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

        //if(::IsWindow(m_hWndToolBar))
        //{
        //    CRect toolBarRc;
        //    ::GetWindowRect(m_hWndToolBar,toolBarRc);
        //    minRC.bottom+=toolBarRc.Height();
        //}

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