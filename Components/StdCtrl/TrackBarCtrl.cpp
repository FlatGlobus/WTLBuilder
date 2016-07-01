// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "trackbarctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterStatusBarCtrlStyles();
//typedef long ListViewStyle;
//typedef long ListAlignStyle;
//typedef long ListSortStyle;

namespace StdCtrl
{
	REGISTER_COMPONENT(CTrackBarCtrl,StdCtl,IDB_TRACKBARCTRL)

		CTrackBarCtrl::CTrackBarCtrl(LPTSTR _name):ControlComponent<StdCtrl::CTrackBarCtrl>(_name)
	{
		SetDefaultSize(130,27);
		RegisterStatusBarCtrlStyles();
	}

	CTrackBarCtrl::~CTrackBarCtrl(void)
	{
	}

	BOOL CTrackBarCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CTrackBarCtrl,WTL::CTrackBarCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CTrackBarCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CTrackBarCtrl>::InitProperty();
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
