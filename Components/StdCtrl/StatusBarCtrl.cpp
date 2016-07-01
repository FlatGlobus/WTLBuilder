// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "statusbarctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterStatusBarCtrlStyles();
//typedef long ListViewStyle;
//typedef long ListAlignStyle;
//typedef long ListSortStyle;

namespace StdCtrl
{
	REGISTER_COMPONENT(CStatusBarCtrl,StdCtl,IDB_STATUSBARCTRL)

		CStatusBarCtrl::CStatusBarCtrl(LPTSTR _name):ControlComponent<StdCtrl::CStatusBarCtrl>(_name)
	{
		RegisterStatusBarCtrlStyles();
		enableTabIndex=FALSE;
	}

	CStatusBarCtrl::~CStatusBarCtrl(void)
	{
	}

	BOOL CStatusBarCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CStatusBarCtrl,WTL::CStatusBarCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx(),ATL_IDW_STATUS_BAR);
		return ::IsWindow(m_hWnd);
	}

	void CStatusBarCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CStatusBarCtrl>::InitProperty();
	}
}
//////////////////////////////////////////////////////////////////////////
static void RegisterStatusBarCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;


	IsInited=TRUE;
}
