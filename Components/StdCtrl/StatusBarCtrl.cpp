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
namespace StdCtrl
{
	typedef long CCPosition;
	static void RegisterStatusBarCtrlStyles();

	REGISTER_COMPONENT(CStatusBarCtrl, StdCtl, IDB_STATUSBARCTRL)

	CStatusBarCtrl::CStatusBarCtrl(LPTSTR _name) :ControlComponent<StdCtrl::CStatusBarCtrl>(_name)
	{
		RegisterStatusBarCtrlStyles();
		enableTabIndex = FALSE;
	}

	CStatusBarCtrl::~CStatusBarCtrl(void)
	{
	}

	BOOL CStatusBarCtrl::CreateComponent(Component * _Parent)
	{
		SetComponentParent(_Parent->GetParentForm());
		CWindowImpl<StdCtrl::CStatusBarCtrl, WTL::CStatusBarCtrl>::Create((HWND)Parent->GetHandle(), GetBoundsRect(), NULL, get_InternalWindowStyle()| CCS_TOP, get_InternalWindowStyleEx(), ATL_IDW_STATUS_BAR);
		
		return ::IsWindow(m_hWnd);
	}

	void CStatusBarCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CStatusBarCtrl>::InitProperty();

		BEGIN_SUB_PROPERTY(_T("CommonStyle"), _T(""))
			DEFINE_SUB_PROPERTY(NoDivider, BOOL, CStatusBarCtrl, FALSE)
			DEFINE_SUB_PROPERTY(NoMoveY, BOOL, CStatusBarCtrl, FALSE)
			DEFINE_SUB_PROPERTY(NoMoveX, BOOL, CStatusBarCtrl, FALSE)
			DEFINE_SUB_PROPERTY(NoParentAlign, BOOL, CStatusBarCtrl, FALSE)
			DEFINE_SUB_PROPERTY(NoResize, BOOL, CStatusBarCtrl, FALSE)
			DEFINE_SUB_PROPERTY(Adjustable, BOOL, CStatusBarCtrl, FALSE)
			DEFINE_SUB_PROPERTY(Position, CCPosition, CStatusBarCtrl, CCS_BOTTOM)
		END_SUB_PROPERTY
	}

	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatusBarCtrl, NoDivider, (CCS_NODIVIDER));
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatusBarCtrl, NoMoveY, (CCS_NOMOVEY));
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatusBarCtrl, NoMoveX, (CCS_NOMOVEX));
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatusBarCtrl, NoParentAlign, (CCS_NOPARENTALIGN));
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatusBarCtrl, NoResize, (CCS_NORESIZE));
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatusBarCtrl, Adjustable, (CCS_ADJUSTABLE))

	//	IMPLEMENT_WINSTYLE_PROPERTY(CStatusBarCtrl, Position, (CCS_LEFT| CCS_TOP| CCS_RIGHT| CCS_BOTTOM))
	void CStatusBarCtrl::set_Position(long val)
	{
		DWORD windowStyle = get_InternalWindowStyle();
		windowStyle &= ~(CCS_LEFT | CCS_TOP | CCS_RIGHT | CCS_BOTTOM);
		windowStyle |= val;
		GetComponents()->Invalidate(TRUE);

//////////set_InternalWindowStyle(windowStyle);////////////////////////////
		ModifyWndStyle((HWND)GetHandle(), 0xFFFFFFFFL, windowStyle | WS_VISIBLE, SWP_NOOWNERZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOCOPYBITS);

		SET_PROP_VALUE(InternalWindowStyle, windowStyle)
		SetModified();
//////////////////////////////////////////////////////////////////////////
	}

	long CStatusBarCtrl::get_Position(void)
	{
		return get_InternalWindowStyle() & (CCS_LEFT | CCS_TOP | CCS_RIGHT | CCS_BOTTOM);
	}


	BEGIN_LIST_PROPERTY(CCPosition)
		LIST_ITEM(CCS_LEFT, Left)
		LIST_ITEM(CCS_TOP, Top)
		LIST_ITEM(CCS_RIGHT, Right)
		LIST_ITEM(CCS_BOTTOM, Bottom)
	END_LIST_ITEM(CCPosition)

	static void RegisterStatusBarCtrlStyles()
	{
		static BOOL IsInited = FALSE;
		if (IsInited == TRUE)
			return;
		REGISTER_LIST_PROPERTY(CCPosition)
		IsInited = TRUE;
	}
}
