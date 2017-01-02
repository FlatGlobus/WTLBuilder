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

	DEFINE_PROPERTY(CheckBoxes, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(DisableDragAndDrop, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(EditLabels, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(FullRowSelect, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(HasButtons, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(HasLines, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(InfoTip, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(LinesAtRoot, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(NoHScroll, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(NoNevenHeight, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(NoScroll, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(NoToolTips, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(RTLReading, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(ShowSelAlways, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(SingleExpand, BOOL, CTreeViewCtrl, FALSE)
	DEFINE_PROPERTY(TrackSelect, BOOL, CTreeViewCtrl, FALSE)
}
///common styles
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl,NoResize,(CCS_NORESIZE))

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, CheckBoxes, (TVS_CHECKBOXES))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, DisableDragAndDrop, (TVS_DISABLEDRAGDROP))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, EditLabels, (TVS_EDITLABELS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, FullRowSelect, (TVS_FULLROWSELECT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, HasButtons, (TVS_HASBUTTONS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, HasLines, (TVS_HASLINES))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, InfoTip, (TVS_INFOTIP))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, LinesAtRoot, (TVS_LINESATROOT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, NoHScroll, (TVS_NOHSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, NoNevenHeight, (TVS_NONEVENHEIGHT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, NoScroll, (TVS_NOSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, NoToolTips, (TVS_NOTOOLTIPS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, RTLReading, (TVS_RTLREADING))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, ShowSelAlways, (TVS_SHOWSELALWAYS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, SingleExpand, (TVS_SINGLEEXPAND))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTreeViewCtrl, TrackSelect, (TVS_TRACKSELECT))



}
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeViewCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;


	IsInited=TRUE;
}
