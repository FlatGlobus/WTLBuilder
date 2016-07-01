// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "shelllistctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "ShellPropMacro.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterListViewCtrlStyles();
typedef long ListViewStyle;
typedef long ListAlignStyle;
typedef long ListSortStyle;

namespace ViksoeCtrl
{
    REGISTER_COMPONENT_EX(CShellListCtrl,CShellListCtrlComp,ViksoeCtrl,IDB_SHELLLISTCTRL)

    CShellListCtrlComp::CShellListCtrlComp(LPTSTR _name):ControlComponent<CShellListCtrlComp>(_name)
    {
        SetDefaultSize(120,128);
        RegisterListViewCtrlStyles();
    }

    CShellListCtrlComp::~CShellListCtrlComp(void)
    {
    }

    BOOL CShellListCtrlComp::CreateComponent(Component * _Parent)
    {
        SetComponentParent(_Parent);
        CShellListCtrl::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
        SetShellStyle(0);
        //Populate();
        return ::IsWindow(m_hWnd);
    }

    void CShellListCtrlComp::InitProperty(void)
    {
        ControlComponent<CShellListCtrlComp>::InitProperty();
        DEFINE_PROPERTY(AutoArrange,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(EditLabels,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(NoColumnHeader,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(NoLabelWrap,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(NoScroll,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(NoSortHeader,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(OwnerData,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(OwnerDrawFixed,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(ShareImageLists,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(ShowSelAlways,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(SingleSel,BOOL,CShellListCtrlComp,FALSE)	
            DEFINE_PROPERTY(ListStyle,ListViewStyle,CShellListCtrlComp,LVS_ICON)
            DEFINE_PROPERTY(Alignment,ListAlignStyle,CShellListCtrlComp,LVS_ALIGNTOP)
            DEFINE_PROPERTY(Sort,ListSortStyle,CShellListCtrlComp,0)
            ///common styles
            DEFINE_PROPERTY(NoDivider,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(NoMoveY,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(NoParentAlign,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(NoResize,BOOL,CShellListCtrlComp,FALSE)
            PUBLIC_PROPERTY(VScroll,TRUE)
            PUBLIC_PROPERTY(HScroll,TRUE)

            DEFINE_PROPERTY(CheckBoxes,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(GridLines,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(SubItemImages,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(TrackSelect,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(HeaderDragAndDrop,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(FullRowSelect,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(OneClickActivate,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(TwoClickActivate,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(FlatSB,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(Regional,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(InfoTip,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(UnderLineHot,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(UnderLineCold,BOOL,CShellListCtrlComp,FALSE)
            DEFINE_PROPERTY(MultiWorkAreas,BOOL,CShellListCtrlComp,FALSE)

            DEFINE_PROPERTY(Path,CString,CShellListCtrlComp,_T(""))
            BEGIN_SUB_PROPERTY(_T("ShellStyle"),_T(""))
                DEFINE_SUB_PROPERTY(NoFolders,BOOL,CShellListCtrlComp,FALSE)
                DEFINE_SUB_PROPERTY(NoFiles,BOOL,CShellListCtrlComp,FALSE)
                DEFINE_SUB_PROPERTY(ShowHidden,BOOL,CShellListCtrlComp,FALSE)
                DEFINE_SUB_PROPERTY(NoReadOnly,BOOL,CShellListCtrlComp,FALSE)
                DEFINE_SUB_PROPERTY(LocalComputer,BOOL,CShellListCtrlComp,FALSE)
                DEFINE_SUB_PROPERTY(FileSysytemOnly,BOOL,CShellListCtrlComp,FALSE)
                DEFINE_SUB_PROPERTY(NoRoot,BOOL,CShellListCtrlComp,FALSE)
            END_SUB_PROPERTY
    }

    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,AutoArrange,(LVS_AUTOARRANGE))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,EditLabels,(LVS_EDITLABELS))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoColumnHeader,(LVS_NOCOLUMNHEADER))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoLabelWrap,(LVS_NOLABELWRAP))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoScroll,(LVS_NOSCROLL))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoSortHeader,(LVS_NOSORTHEADER))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,OwnerData,(LVS_OWNERDATA))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,OwnerDrawFixed,(LVS_OWNERDRAWFIXED))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,ShareImageLists,(LVS_SHAREIMAGELISTS))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,ShowSelAlways,(LVS_SHOWSELALWAYS))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,SingleSel,(LVS_SINGLESEL))

        IMPLEMENT_WINSTYLE_PROPERTY(CShellListCtrlComp,ListStyle,(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST))
        IMPLEMENT_WINSTYLE_PROPERTY(CShellListCtrlComp,Alignment,(LVS_ALIGNTOP|LVS_ALIGNLEFT))
        IMPLEMENT_WINSTYLE_PROPERTY(CShellListCtrlComp,Sort,(LVS_SORTASCENDING|LVS_SORTDESCENDING|0))
        ///common styles
        //IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,Bottom,(CCS_BOTTOM))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoDivider,(CCS_NODIVIDER))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoMoveY,(CCS_NOMOVEY))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoParentAlign,(CCS_NOPARENTALIGN))
        IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,NoResize,(CCS_NORESIZE))


        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,CheckBoxes,(LVS_EX_CHECKBOXES))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,GridLines,(LVS_EX_GRIDLINES))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,SubItemImages,(LVS_EX_SUBITEMIMAGES))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,TrackSelect,(LVS_EX_TRACKSELECT))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,HeaderDragAndDrop,(LVS_EX_HEADERDRAGDROP))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,FullRowSelect,(LVS_EX_FULLROWSELECT))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,OneClickActivate,(LVS_EX_ONECLICKACTIVATE))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,TwoClickActivate,(LVS_EX_TWOCLICKACTIVATE))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,FlatSB,(LVS_EX_FLATSB))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,Regional,(LVS_EX_REGIONAL))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,InfoTip,(LVS_EX_INFOTIP))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,UnderLineHot,(LVS_EX_UNDERLINEHOT))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,UnderLineCold,(LVS_EX_UNDERLINECOLD))
        IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(CShellListCtrlComp,MultiWorkAreas,(LVS_EX_MULTIWORKAREAS))
        //IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellListCtrlComp,Top,(CCS_TOP))


    void CShellListCtrlComp::set_Path(CString val)
    {
        path = val;
        Populate(path);
        SetModified();
    }

    CString CShellListCtrlComp::get_Path()
    {
        return path;
    }

    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,NoFolders,SCT_EX_NOFOLDERS)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,NoFiles,SCT_EX_NOFILES)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,ShowHidden,SCT_EX_SHOWHIDDEN)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,NoReadOnly,SCT_EX_NOREADONLY)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,LocalComputer,SCT_EX_LOCALCOMPUTER)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,FileSysytemOnly,SCT_EX_FILESYSTEMONLY)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellListCtrlComp,NoRoot,SCT_EX_NOROOT)
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
