// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "csortlistviewctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterListViewCtrlStyles();
typedef long ListViewStyle;
typedef long ListAlignStyle;
typedef long ListSortStyle;

namespace DecorativeCtrl
{
REGISTER_COMPONENT(CSortListViewCtrl,DecorativeCtrl,IDB_LISTVIEWCTRL)

CSortListViewCtrl::CSortListViewCtrl(LPTSTR _name):ControlComponent<CSortListViewCtrl>(_name)
{
	SetDefaultSize(120,120);
	RegisterListViewCtrlStyles();
}

CSortListViewCtrl::~CSortListViewCtrl(void)
{
}

BOOL CSortListViewCtrl::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	CWindowImpl<CSortListViewCtrl,WTL::CListViewCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CSortListViewCtrl::InitProperty(void)
{
	ControlComponent<CSortListViewCtrl>::InitProperty();

	///common styles
	BEGIN_SUB_PROPERTY(_T("CommonStyle"), _T(""))
		DEFINE_SUB_PROPERTY(NoDivider, BOOL, CSortListViewCtrl, FALSE)
		DEFINE_SUB_PROPERTY(NoMoveY, BOOL, CSortListViewCtrl, FALSE)
		DEFINE_SUB_PROPERTY(NoParentAlign, BOOL, CSortListViewCtrl, FALSE)
		DEFINE_SUB_PROPERTY(NoResize, BOOL, CSortListViewCtrl, FALSE)
	END_SUB_PROPERTY

	PUBLIC_PROPERTY(VScroll, TRUE)
	PUBLIC_PROPERTY(HScroll, TRUE)

	BEGIN_SUB_PROPERTY(_T("ControlStyle"), _T(""))
		DEFINE_SUB_PROPERTY(AutoArrange,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(EditLabels,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(NoColumnHeader,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(NoLabelWrap,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(NoScroll,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(NoSortHeader,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(OwnerData,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(OwnerDrawFixed,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(ShareImageLists,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(ShowSelAlways,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(SingleSel,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(ListStyle,ListViewStyle,CSortListViewCtrl,LVS_LIST)
		DEFINE_SUB_PROPERTY(Alignment,ListAlignStyle,CSortListViewCtrl,LVS_ALIGNTOP)
		DEFINE_SUB_PROPERTY(Sort,ListSortStyle,CSortListViewCtrl,0)

		DEFINE_SUB_PROPERTY(CheckBoxes,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(GridLines,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(SubItemImages,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(TrackSelect,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(HeaderDragAndDrop,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(FullRowSelect,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(OneClickActivate,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(TwoClickActivate,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(FlatSB,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(Regional,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(InfoTip,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(UnderLineHot,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(UnderLineCold,BOOL,CSortListViewCtrl,FALSE)
		DEFINE_SUB_PROPERTY(MultiWorkAreas,BOOL,CSortListViewCtrl,FALSE)
	END_SUB_PROPERTY
    DEFINE_PROPERTY(ItemClass,CString,CSortListViewCtrl,_T("CSortListViewItem"))
}

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,AutoArrange,(LVS_AUTOARRANGE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,EditLabels,(LVS_EDITLABELS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoColumnHeader,(LVS_NOCOLUMNHEADER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoLabelWrap,(LVS_NOLABELWRAP))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoScroll,(LVS_NOSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoSortHeader,(LVS_NOSORTHEADER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,OwnerData,(LVS_OWNERDATA))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,OwnerDrawFixed,(LVS_OWNERDRAWFIXED))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,ShareImageLists,(LVS_SHAREIMAGELISTS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,ShowSelAlways,(LVS_SHOWSELALWAYS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,SingleSel,(LVS_SINGLESEL))

IMPLEMENT_WINSTYLE_PROPERTY(CSortListViewCtrl,ListStyle,(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST))
IMPLEMENT_WINSTYLE_PROPERTY(CSortListViewCtrl,Alignment,(LVS_ALIGNTOP|LVS_ALIGNLEFT))
IMPLEMENT_WINSTYLE_PROPERTY(CSortListViewCtrl,Sort,(LVS_SORTASCENDING|LVS_SORTDESCENDING|0))
///common styles
//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,Bottom,(CCS_BOTTOM))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,NoResize,(CCS_NORESIZE))


IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,CheckBoxes,(LVS_EX_CHECKBOXES))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,GridLines,(LVS_EX_GRIDLINES))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,SubItemImages,(LVS_EX_SUBITEMIMAGES))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,TrackSelect,(LVS_EX_TRACKSELECT))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,HeaderDragAndDrop,(LVS_EX_HEADERDRAGDROP))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,FullRowSelect,(LVS_EX_FULLROWSELECT))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,OneClickActivate,(LVS_EX_ONECLICKACTIVATE))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,TwoClickActivate,(LVS_EX_TWOCLICKACTIVATE))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,FlatSB,(LVS_EX_FLATSB))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,Regional,(LVS_EX_REGIONAL))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,InfoTip,(LVS_EX_INFOTIP))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,UnderLineHot,(LVS_EX_UNDERLINEHOT))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,UnderLineCold,(LVS_EX_UNDERLINECOLD))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CSortListViewCtrl,MultiWorkAreas,(LVS_EX_MULTIWORKAREAS))
//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CSortListViewCtrl,Top,(CCS_TOP))

void CSortListViewCtrl::set_ItemClass(CString str)
{
    listItemClass=str;
    SetModified();
}

CString CSortListViewCtrl::get_ItemClass(void)
{
	if(state.GetBit(csLoading))
	{
		listItemClass.Empty();
		listItemClass= GET_PROP_VALUE(CString, ItemClass)
	}
	return listItemClass;
}

}
//////////////////////////////////////////////////////////////////////////
BEGIN_LIST_PROPERTY(ListViewStyle)
LIST_ITEM_DECORATE(LVS_ICON,LVS_ICON,Icon)
LIST_ITEM_DECORATE(LVS_REPORT,LVS_REPORT,Report)         
LIST_ITEM_DECORATE(LVS_SMALLICON,LVS_SMALLICON,SmallIcon)
LIST_ITEM_DECORATE(LVS_LIST,LVS_LIST,List)
END_LIST_ITEM(ListViewStyle)

BEGIN_LIST_PROPERTY(ListAlignStyle)
LIST_ITEM_DECORATE(LVS_ALIGNTOP,LVS_ALIGNTOP,Top)
LIST_ITEM_DECORATE(LVS_ALIGNLEFT,LVS_ALIGNLEFT,Left)
END_LIST_ITEM(ListAlignStyle)

BEGIN_LIST_PROPERTY(ListSortStyle)
LIST_ITEM_DECORATE(LVS_SORTASCENDING,LVS_SORTASCENDING,Ascending)
LIST_ITEM_DECORATE(LVS_SORTDESCENDING,LVS_SORTDESCENDING,Descending)
LIST_ITEM_DECORATE(0,0,None)
END_LIST_ITEM(ListSortStyle)

//LIST_ITEM_DECORATE(LVS_EX_MULTIWORKAREAS   

static void RegisterListViewCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(ListViewStyle)
	REGISTER_LIST_PROPERTY(ListAlignStyle)
	REGISTER_LIST_PROPERTY(ListSortStyle)

	IsInited=TRUE;
}
