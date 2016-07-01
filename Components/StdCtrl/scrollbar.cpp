// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "scrollbar.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterScrollBarStyles();

typedef long ScrollBarHorizAlign;
typedef long ScrollBarVertAlign;
namespace StdCtrl
{
REGISTER_COMPONENT(CHScrollBar,StdCtl,IDB_HSCROLLBAR)
REGISTER_COMPONENT(CVScrollBar,StdCtl,IDB_VSCROLLBAR)

CHScrollBar::CHScrollBar(LPTSTR _name):ControlComponent<StdCtrl::CHScrollBar>(_name)
{
	SetDefaultSize(154,17);
	RegisterScrollBarStyles();
	enableTabIndex=FALSE;
}

CHScrollBar::~CHScrollBar(void)
{
}

BOOL CHScrollBar::CreateComponent(Component * _Parent)
{
	ADD_WIN_STYLE(SBS_HORZ)
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CHScrollBar,WTL::CScrollBar>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CHScrollBar::InitProperty(void)
{
	ControlComponent<StdCtrl::CHScrollBar>::InitProperty();
	DEFINE_PROPERTY(Alignment,ScrollBarHorizAlign,CHScrollBar,0)
}

IMPLEMENT_WINSTYLE_PROPERTY(CHScrollBar,Alignment,(SBS_BOTTOMALIGN|SBS_TOPALIGN))
//////////////////////////////////////////////////////////////////////////
CVScrollBar::CVScrollBar(LPTSTR _name):ControlComponent<StdCtrl::CVScrollBar>(_name)
{
	SetDefaultSize(17,154);
	RegisterScrollBarStyles();
}

CVScrollBar::~CVScrollBar(void)
{
}

BOOL CVScrollBar::CreateComponent(Component * _Parent)
{
	ADD_WIN_STYLE(SBS_VERT)
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CVScrollBar,WTL::CScrollBar>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CVScrollBar::InitProperty(void)
{
	ControlComponent<StdCtrl::CVScrollBar>::InitProperty();
	DEFINE_PROPERTY(Alignment,ScrollBarVertAlign,CVScrollBar,0)
}

IMPLEMENT_WINSTYLE_PROPERTY(CVScrollBar,Alignment,(SBS_LEFTALIGN|SBS_RIGHTALIGN))

//////////////////////////////////////////////////////////////////////////
}
BEGIN_LIST_PROPERTY(ScrollBarHorizAlign)
	LIST_ITEM_DECORATE(0,0,None)
	LIST_ITEM_DECORATE(SBS_BOTTOMALIGN,SBS_BOTTOMALIGN,Bottom)
	LIST_ITEM_DECORATE(SBS_TOPALIGN,SBS_TOPALIGN,Top)
END_LIST_ITEM(ScrollBarHorizAlign)

BEGIN_LIST_PROPERTY(ScrollBarVertAlign)
	LIST_ITEM_DECORATE(0,0,None)
	LIST_ITEM_DECORATE(SBS_LEFTALIGN,SBS_LEFTALIGN,Left)
	LIST_ITEM_DECORATE(SBS_RIGHTALIGN,SBS_RIGHTALIGN,Top)
END_LIST_ITEM(ScrollBarVertAlign)

static void RegisterScrollBarStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(ScrollBarHorizAlign)
	REGISTER_LIST_PROPERTY(ScrollBarVertAlign)

	IsInited=TRUE;
}
