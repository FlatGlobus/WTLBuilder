// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "shelltreectrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "ShellPropMacro.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeViewCtrlStyles();

namespace ViksoeCtrl
{
	REGISTER_COMPONENT_EX(CShellTreeCtrl,CShellTreeCtrlComp,ViksoeCtrl,IDB_SHELLTREECTRL)

        CShellTreeCtrlComp::CShellTreeCtrlComp(LPTSTR _name):ControlComponent<CShellTreeCtrlComp>(_name)
{
	SetDefaultSize(138,162);
	RegisterTreeViewCtrlStyles();
}

CShellTreeCtrlComp::~CShellTreeCtrlComp(void)
{
}

BOOL CShellTreeCtrlComp::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
    CShellTreeCtrl::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
    SetShellStyle(0);
    //Populate();
    
	return ::IsWindow(m_hWnd);
}

void CShellTreeCtrlComp::InitProperty(void)
{
	ControlComponent<CShellTreeCtrlComp>::InitProperty();
			///common styles
	DEFINE_PROPERTY(NoDivider,BOOL,CShellTreeCtrlComp,FALSE)
	DEFINE_PROPERTY(NoMoveY,BOOL,CShellTreeCtrlComp,FALSE)
	DEFINE_PROPERTY(NoParentAlign,BOOL,CShellTreeCtrlComp,FALSE)
	DEFINE_PROPERTY(NoResize,BOOL,CShellTreeCtrlComp,FALSE)
	PUBLIC_PROPERTY(VScroll,TRUE)
	PUBLIC_PROPERTY(HScroll,TRUE)
    DEFINE_PROPERTY(Path,CString,CShellTreeCtrlComp,_T(""))
    BEGIN_SUB_PROPERTY(_T("ShellStyle"),_T(""))
        DEFINE_SUB_PROPERTY(NoFolders,BOOL,CShellTreeCtrlComp,FALSE)
        DEFINE_SUB_PROPERTY(NoFiles,BOOL,CShellTreeCtrlComp,FALSE)
        DEFINE_SUB_PROPERTY(ShowHidden,BOOL,CShellTreeCtrlComp,FALSE)
        DEFINE_SUB_PROPERTY(NoReadOnly,BOOL,CShellTreeCtrlComp,FALSE)
        DEFINE_SUB_PROPERTY(LocalComputer,BOOL,CShellTreeCtrlComp,FALSE)
        DEFINE_SUB_PROPERTY(FileSysytemOnly,BOOL,CShellTreeCtrlComp,FALSE)
        DEFINE_SUB_PROPERTY(NoRoot,BOOL,CShellTreeCtrlComp,FALSE)
    END_SUB_PROPERTY


		DEFINE_PROPERTY(CheckBoxes, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(DisableDragAndDrop, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(EditLabels, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(FullRowSelect, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(HasButtons, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(HasLines, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(InfoTip, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(LinesAtRoot, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(NoHScroll, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(NoNevenHeight, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(NoScroll, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(NoToolTips, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(RTLReading, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(ShowSelAlways, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(SingleExpand, BOOL, CShellTreeCtrlComp, FALSE)
		DEFINE_PROPERTY(TrackSelect, BOOL, CShellTreeCtrlComp, FALSE)


}
///common styles
//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListViewCtrl,Bottom,(CCS_BOTTOM))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp,NoResize,(CCS_NORESIZE))
	//IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListViewCtrl,Top,(CCS_TOP))


	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, CheckBoxes, (TVS_CHECKBOXES))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, DisableDragAndDrop, (TVS_DISABLEDRAGDROP))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, EditLabels, (TVS_EDITLABELS))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, FullRowSelect, (TVS_FULLROWSELECT))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, HasButtons, (TVS_HASBUTTONS))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, HasLines, (TVS_HASLINES))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, InfoTip, (TVS_INFOTIP))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, LinesAtRoot, (TVS_LINESATROOT))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, NoHScroll, (TVS_NOHSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, NoNevenHeight, (TVS_NONEVENHEIGHT))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, NoScroll, (TVS_NOSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, NoToolTips, (TVS_NOTOOLTIPS))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, RTLReading, (TVS_RTLREADING))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, ShowSelAlways, (TVS_SHOWSELALWAYS))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, SingleExpand, (TVS_SINGLEEXPAND))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellTreeCtrlComp, TrackSelect, (TVS_TRACKSELECT))



void CShellTreeCtrlComp::set_Path(CString val)
{
    path = val;
    Populate(path);
    SetModified();
}

CString CShellTreeCtrlComp::get_Path()
{
    return path;
}

IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,NoFolders,SCT_EX_NOFOLDERS)
IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,NoFiles,SCT_EX_NOFILES)
IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,ShowHidden,SCT_EX_SHOWHIDDEN)
IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,NoReadOnly,SCT_EX_NOREADONLY)
IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,LocalComputer,SCT_EX_LOCALCOMPUTER)
IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,FileSysytemOnly,SCT_EX_FILESYSTEMONLY)
IMPLEMENT_SHELL_BOOL_PROPERTY(CShellTreeCtrlComp,NoRoot,SCT_EX_NOROOT)
}
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeViewCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;


	IsInited=TRUE;
}
