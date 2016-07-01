// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "toolpanel.h"
#include "..\Property\Register.h"
#include "resource.h"
//#include "..\Property\PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
namespace WTLBuilderCtrl
{
    REGISTER_COMPONENT(CToolTab,WTLBuilderCtrl,IDB_TOOLTAB)
    CToolTab::CToolTab(LPTSTR _name):ControlComponent<CToolTab>(_name)
    {
    }

    CToolTab::~CToolTab(void)
    {
    }

    BOOL CToolTab::CreateComponent(Component * _Parent)
    {
		ADD_WIN_STYLE(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | TCS_TABS | TCS_FOCUSNEVER)
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),GetBoundsRect(),0,get_InternalWindowStyle());
        if(::IsWindow(m_hWnd))
            InsertItem(0,_T("StdCtrl"));
        return ::IsWindow(m_hWnd);
    }

    void CToolTab::InitProperty(void)
    {
        ControlComponent<CToolTab>::InitProperty();
    }
    //////////////////////////////////////////////////////////////////////////
}
