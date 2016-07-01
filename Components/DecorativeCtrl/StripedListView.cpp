// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "StripedListView.h"
#include "resource.h"
#include "PropertyListEdit.h"
#ifdef __WTLBUILDER__
//////////////////////////////////////////////////////////////////////////
static void RegisterListViewCtrlStyles();
typedef long ListViewStyle;
typedef long ListAlignStyle;
typedef long ListSortStyle;

namespace DecorativeCtrl
{
REGISTER_COMPONENT_EX(CStripedListView,CStripedListViewComp,DecorativeCtrl,IDB_STRIPEDLISTVIEW)

CStripedListViewComp::CStripedListViewComp(LPTSTR _name):ControlComponent<DecorativeCtrl::CStripedListViewComp>(_name)
{
	SetDefaultSize(120,128);
	RegisterListViewCtrlStyles();
}

CStripedListViewComp::~CStripedListViewComp(void)
{
}

BOOL CStripedListViewComp::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CStripedListViewComp::InitProperty(void)
{
	ControlComponent<DecorativeCtrl::CStripedListViewComp>::InitProperty();
	DEFINE_PROPERTY(AutoArrange,BOOL,CStripedListViewComp,FALSE)
	DEFINE_PROPERTY(EditLabels,BOOL,CStripedListViewComp,FALSE)
	DEFINE_PROPERTY(NoColumnHeader,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(NoLabelWrap,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(NoScroll,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(NoSortHeader,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(OwnerData,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(OwnerDrawFixed,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(ShareImageLists,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(ShowSelAlways,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(SingleSel,BOOL,CStripedListViewComp,FALSE)	
	DEFINE_PROPERTY(ListStyle,ListViewStyle,CStripedListViewComp,LVS_LIST)
	DEFINE_PROPERTY(Alignment,ListAlignStyle,CStripedListViewComp,LVS_ALIGNTOP)
	DEFINE_PROPERTY(Sort,ListSortStyle,CStripedListViewComp,0)
		///common styles
	DEFINE_PROPERTY(NoDivider,BOOL,CStripedListViewComp,FALSE)
	DEFINE_PROPERTY(NoMoveY,BOOL,CStripedListViewComp,FALSE)
	DEFINE_PROPERTY(NoParentAlign,BOOL,CStripedListViewComp,FALSE)
	DEFINE_PROPERTY(NoResize,BOOL,CStripedListViewComp,FALSE)
	PUBLIC_PROPERTY(VScroll,TRUE)
	PUBLIC_PROPERTY(HScroll,TRUE)

    DEFINE_PROPERTY(CheckBoxes,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(GridLines,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(SubItemImages,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(TrackSelect,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(HeaderDragAndDrop,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(FullRowSelect,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(OneClickActivate,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(TwoClickActivate,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(FlatSB,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(Regional,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(InfoTip,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(UnderLineHot,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(UnderLineCold,BOOL,CStripedListViewComp,FALSE)
    DEFINE_PROPERTY(MultiWorkAreas,BOOL,CStripedListViewComp,FALSE)

    DEFINE_PROPERTY(FirstColor,CColorref,CStripedListViewComp,RGB(200,200,255))
    DEFINE_PROPERTY(SecondColor,CColorref,CStripedListViewComp,RGB(255,255,255))

}

   void CStripedListViewComp::set_FirstColor(CColorref val)
   {
        SetFirstColor(val);
        SetModified();
   }
   
   CColorref CStripedListViewComp::get_FirstColor(void)
   {
      return GetFirstColor();
   }

   void CStripedListViewComp::set_SecondColor(CColorref val)
   {
        SetSecondColor(val);
        SetModified();
   }
   
   CColorref CStripedListViewComp::get_SecondColor(void)
   {
      return GetSecondColor();
   }


IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,AutoArrange,(LVS_AUTOARRANGE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,EditLabels,(LVS_EDITLABELS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoColumnHeader,(LVS_NOCOLUMNHEADER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoLabelWrap,(LVS_NOLABELWRAP))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoScroll,(LVS_NOSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoSortHeader,(LVS_NOSORTHEADER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,OwnerData,(LVS_OWNERDATA))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,OwnerDrawFixed,(LVS_OWNERDRAWFIXED))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,ShareImageLists,(LVS_SHAREIMAGELISTS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,ShowSelAlways,(LVS_SHOWSELALWAYS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,SingleSel,(LVS_SINGLESEL))

IMPLEMENT_WINSTYLE_PROPERTY(CStripedListViewComp,ListStyle,(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST))
IMPLEMENT_WINSTYLE_PROPERTY(CStripedListViewComp,Alignment,(LVS_ALIGNTOP|LVS_ALIGNLEFT))
IMPLEMENT_WINSTYLE_PROPERTY(CStripedListViewComp,Sort,(LVS_SORTASCENDING|LVS_SORTDESCENDING|0))
///common styles
//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListView,Bottom,(CCS_BOTTOM))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListViewComp,NoResize,(CCS_NORESIZE))


IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,CheckBoxes,(LVS_EX_CHECKBOXES))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,GridLines,(LVS_EX_GRIDLINES))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,SubItemImages,(LVS_EX_SUBITEMIMAGES))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,TrackSelect,(LVS_EX_TRACKSELECT))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,HeaderDragAndDrop,(LVS_EX_HEADERDRAGDROP))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,FullRowSelect,(LVS_EX_FULLROWSELECT))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,OneClickActivate,(LVS_EX_ONECLICKACTIVATE))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,TwoClickActivate,(LVS_EX_TWOCLICKACTIVATE))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,FlatSB,(LVS_EX_FLATSB))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,Regional,(LVS_EX_REGIONAL))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,InfoTip,(LVS_EX_INFOTIP))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,UnderLineHot,(LVS_EX_UNDERLINEHOT))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,UnderLineCold,(LVS_EX_UNDERLINECOLD))
IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CStripedListViewComp,MultiWorkAreas,(LVS_EX_MULTIWORKAREAS))
//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStripedListView,Top,(CCS_TOP))
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
////////////////////////////////////////////////////////////////////////////////////////////////
#endif