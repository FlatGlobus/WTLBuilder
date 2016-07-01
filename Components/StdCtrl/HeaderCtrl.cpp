// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "HeaderCtrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
typedef long CommonCtrlAlign;
static void RegisterHeaderCtrlStyles();
namespace StdCtrl
{
	REGISTER_COMPONENT(CHeaderCtrl,StdCtl,IDB_HEADERCTRL)

CHeaderCtrl::CHeaderCtrl(LPTSTR _name):ControlComponent<StdCtrl::CHeaderCtrl>(_name),items(0)
{
	SetDefaultSize(200,20);
	RegisterHeaderCtrlStyles();
	enableTabIndex=FALSE;
}

CHeaderCtrl::~CHeaderCtrl(void)
{
}

BOOL CHeaderCtrl::CreateComponent(Component * _Parent)
{
	SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CHeaderCtrl,WTL::CHeaderCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CHeaderCtrl::InitProperty(void)
{
	ControlComponent<StdCtrl::CHeaderCtrl>::InitProperty();
	DEFINE_PROPERTY(Buttons,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(DragDrop,BOOL,CHeaderCtrl,FALSE)
#if (_WIN32_IE >= 0x0500)
	DEFINE_PROPERTY(FilterBar,BOOL,CHeaderCtrl,FALSE)
#endif
#if (_WIN32_WINNT >= 0x501)
	DEFINE_PROPERTY(Flat,BOOL,CHeaderCtrl,FALSE)
#endif
	DEFINE_PROPERTY(FullDrag,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(Hidden,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(Horiz,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(HotTrack,BOOL,CHeaderCtrl,FALSE)
///common styles
	DEFINE_PROPERTY(NoDivider,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(NoMoveY,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(NoParentAlign,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(NoResize,BOOL,CHeaderCtrl,FALSE)
	//DEFINE_PROPERTY(,BOOL,CHeaderCtrl,FALSE)
	DEFINE_PROPERTY(CtrlAlign,CommonCtrlAlign,CHeaderCtrl,CCS_TOP)
    DEFINE_PROPERTY(Items,long,CHeaderCtrl,0)
}

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,Buttons,(HDS_BUTTONS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,DragDrop,(HDS_DRAGDROP))
#if (_WIN32_IE >= 0x0500)
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,FilterBar,(HDS_FILTERBAR))
#endif
#if (_WIN32_WINNT >= 0x501)
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,Flat,(HDS_FLAT))
#endif
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,FullDrag,(HDS_FULLDRAG))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,Hidden,(HDS_HIDDEN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,Horiz,(HDS_HORZ))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,HotTrack,(HDS_HOTTRACK))
///common styles
IMPLEMENT_WINSTYLE_PROPERTY(CHeaderCtrl,CtrlAlign,(CCS_BOTTOM|CCS_TOP|CCS_LEFT|CCS_RIGHT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CHeaderCtrl,NoResize,(CCS_NORESIZE))

void CHeaderCtrl::set_Items(long val)
{
    if(items!=val)
    {
        

        HDITEM item;

        item.mask=HDI_TEXT|HDI_WIDTH|HDI_FORMAT;
        item.fmt=HDF_CENTER;
        item.cxy=50;
        item.pszText=_T("Item");
        InsertItem(0,&item);
    }
}

long CHeaderCtrl::get_Items()
{
    return items;
}
}
//////////////////////////////////////////////////////////////////////////
static void RegisterHeaderCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;
		IsInited=TRUE;
}
