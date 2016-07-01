// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include <atlctrlx.h>
#include "panecontainer.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterPaneContainerStyles();
namespace StdCtrl
{
    REGISTER_COMPONENT(CPaneContainer,StdCtl,IDB_PANECONTAINER)

    CPaneContainer::CPaneContainer(LPTSTR _name):ControlComponent<StdCtrl::CPaneContainer>(_name)
    {
        SetDefaultSize(100,100);
        RegisterPaneContainerStyles();
		enableTabIndex=FALSE;
    }

    CPaneContainer::~CPaneContainer(void)
    {
    }

    BOOL CPaneContainer::CreateComponent(Component * _Parent)
    {
		ADD_WIN_STYLE(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),(LPCTSTR)get_Title(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
        if(::IsWindow(m_hWnd))
        {
            CRect rc=GetBoundsRect();
            UpdateLayout(rc.Width(),rc.Height());
            
            return TRUE;
        }
        return FALSE;
    }

    void CPaneContainer::InitProperty(void)
    {
        ControlComponent<StdCtrl::CPaneContainer>::InitProperty();
        DEFINE_PROPERTY(CloseButton,BOOL,StdCtrl::CPaneContainer,TRUE)
        DEFINE_PROPERTY(EnableCloseButton,BOOL,StdCtrl::CPaneContainer,TRUE)
        DEFINE_PROPERTY(Title,CString,StdCtrl::CPaneContainer,(LPCTSTR)get_Name())
        DEFINE_PROPERTY(Vertical,BOOL,StdCtrl::CPaneContainer,FALSE)

        PUBLIC_PROPERTY(Left,FALSE)
        PUBLIC_PROPERTY(Top,FALSE)
        REMOVE_PROPERTY(EnableToolTip)
        REMOVE_PROPERTY(ToolTip)
        REMOVE_PROPERTY(Focus)
        REMOVE_PROPERTY(Font)
        REMOVE_PROPERTY(Group)
        REMOVE_PROPERTY(TabStop)
        REMOVE_PROPERTY(TabIndex)
        REMOVE_PROPERTY(Enabled)
    }

    CRect CPaneContainer::GetBoundsRect(void)
    {
        CRect rc=ControlComponentBase::GetBoundsRect();
        rc.left=0;
        rc.top=0;
        return rc;
    }

    void CPaneContainer::SetBoundsRect(CRect rc)
    {
        rc.left=rc.top=0;
        ControlComponentBase::SetBoundsRect(rc);
        if(::IsWindow((HWND)GetHandle()) && designer)	
            UpdateLayout(rc.right,rc.bottom);
    }

    void CPaneContainer::set_Title(CString _title)
    {
        if(_title != title)
        {
            title=_title;
            SetTitle(title);
            SetModified();
        }
    }
    
    CString CPaneContainer::get_Title()
    {
        return title;
    }

    void CPaneContainer::set_CloseButton(BOOL val)
    {
        if(val != closeButton)
        {
            closeButton=val;
            DWORD extStyle=GetPaneContainerExtendedStyle();
            extStyle = closeButton == FALSE ? (extStyle | (PANECNT_NOCLOSEBUTTON)): (extStyle & ~(PANECNT_NOCLOSEBUTTON));
            SetPaneContainerExtendedStyle(extStyle,0);
            SetModified();
        }
    }

    BOOL CPaneContainer::get_CloseButton()
    {
        return (GetPaneContainerExtendedStyle() & PANECNT_NOCLOSEBUTTON)==FALSE;
    }

    void CPaneContainer::set_EnableCloseButton(BOOL val)
    {
        if(val != enableCloseButton)
        {
            enableCloseButton=val;
            EnableCloseButton(enableCloseButton);
            SetModified();
        }
    }

    BOOL CPaneContainer::get_EnableCloseButton()
    {
        return enableCloseButton;
    }

    void CPaneContainer::set_Vertical(BOOL val)
    {
        if(val != vertical)
        {
            vertical=val;
            DWORD extStyle=GetPaneContainerExtendedStyle();
            extStyle = vertical == TRUE ? (extStyle | (PANECNT_VERTICAL)): (extStyle & ~(PANECNT_VERTICAL));
            SetPaneContainerExtendedStyle(extStyle,0);
            SetModified();
        }
    }

    BOOL CPaneContainer::get_Vertical()
    {
        return GetPaneContainerExtendedStyle() & PANECNT_VERTICAL;
    }


    //BOOL CPaneContainerComp::MouseMove(CDC * dc,CPoint pt,HintItem h)
    //{
    //    Component::MouseMove(dc,pt,h);
    //}

}
//////////////////////////////////////////////////////////////////////////
static void RegisterPaneContainerStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;
    IsInited=TRUE;
}
