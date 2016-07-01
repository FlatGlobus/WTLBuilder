// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "treeviewctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeViewCtrlStyles();
//typedef long ListViewStyle;
//typedef long ListAlignStyle;
//typedef long ListSortStyle;

namespace StdCtrl
{
	REGISTER_COMPONENT(CTreeViewCtrl,StdCtl,IDB_TREEVIEWCTRL)

CTreeViewCtrl::CTreeViewCtrl(LPTSTR _name):ControlComponent<StdCtrl::CTreeViewCtrl>(_name)
{
	SetDefaultSize(138,162);
	RegisterTreeViewCtrlStyles();
}

CTreeViewCtrl::~CTreeViewCtrl(void)
{
}

BOOL CTreeViewCtrl::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CTreeViewCtrl,WTL::CTreeViewCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CTreeViewCtrl::InitProperty(void)
{
	ControlComponent<StdCtrl::CTreeViewCtrl>::InitProperty();
			///common styles
	DEFINE_PROPERTY(NoDivider,BOOL,CTreeViewCtrl,FALSE)
	DEFINE_PROPERTY(NoMoveY,BOOL,CTreeViewCtrl,FALSE)
	DEFINE_PROPERTY(NoParentAlign,BOOL,CTreeViewCtrl,FALSE)
	DEFINE_PROPERTY(NoResize,BOOL,CTreeViewCtrl,FALSE)
	PUBLIC_PROPERTY(VScroll,TRUE)
	PUBLIC_PROPERTY(HScroll,TRUE)
}
///common styles
//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListViewCtrl,Bottom,(CCS_BOTTOM))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoResize,(CCS_NORESIZE))
	//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListViewCtrl,Top,(CCS_TOP))
}
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeViewCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;


	IsInited=TRUE;
}
