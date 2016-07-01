// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "shellcomboctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "ShellPropMacro.h"

//////////////////////////////////////////////////////////////////////////
static void RegisterComboBoxStyles();
typedef long ComboBoxStyle;
namespace ViksoeCtrl
{
    REGISTER_COMPONENT_EX(CShellComboCtrl,CShellComboCtrlComp,ViksoeCtrl,IDB_SHELLCOMBOBOX)

    CShellComboCtrlComp::CShellComboCtrlComp(LPTSTR _name):ControlComponent<CShellComboCtrlComp>(_name)
    {
        SetDefaultSize(108,74);
        RegisterComboBoxStyles();
    }

    CShellComboCtrlComp::~CShellComboCtrlComp(void)
    {
    }

    BOOL CShellComboCtrlComp::CreateComponent(Component * _Parent)
    {
		ADD_WIN_STYLE(CBS_DROPDOWN)
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Name(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
        //SetShellStyle(SCT_EX_NOFILES|SCT_EX_NOROOT);
        return ::IsWindow(m_hWnd);
    }

    void CShellComboCtrlComp::InitProperty(void)
    {
        ControlComponent<CShellComboCtrlComp>::InitProperty();
        DEFINE_PROPERTY(DisableNoScroll,BOOL,CShellComboCtrlComp,FALSE)
        DEFINE_PROPERTY(AutoScroll,BOOL,CShellComboCtrlComp,TRUE)
        DEFINE_PROPERTY(Style,ComboBoxStyle,CShellComboCtrlComp,CBS_DROPDOWN)
        DEFINE_PROPERTY(NoIntegralHeight,BOOL,CShellComboCtrlComp,FALSE)
        DEFINE_PROPERTY(Sort,BOOL,CShellComboCtrlComp,TRUE)
        PUBLIC_PROPERTY(VScroll,TRUE)
        DEFINE_PROPERTY(DroppedWidth,long,CShellComboCtrlComp,0)
        DEFINE_PROPERTY(HorizontalExtent,long,CShellComboCtrlComp,bounds.Width())
        DEFINE_PROPERTY(ShowDropDown,BOOL,CShellComboCtrlComp,FALSE)
        DEFINE_PROPERTY(CurSel,long,CShellComboCtrlComp,-1)

        DEFINE_PROPERTY(Path,CString,CShellComboCtrlComp,_T(""))
        BEGIN_SUB_PROPERTY(_T("ShellStyle"),_T(""))
            DEFINE_SUB_PROPERTY(NoFolders,BOOL,CShellComboCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(NoFiles,BOOL,CShellComboCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(ShowHidden,BOOL,CShellComboCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(NoReadOnly,BOOL,CShellComboCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(LocalComputer,BOOL,CShellComboCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(FileSysytemOnly,BOOL,CShellComboCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(NoRoot,BOOL,CShellComboCtrlComp,FALSE)
        END_SUB_PROPERTY
    }

    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellComboCtrlComp,DisableNoScroll,(CBS_DISABLENOSCROLL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellComboCtrlComp,AutoScroll,(CBS_AUTOHSCROLL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellComboCtrlComp,Sort,(CBS_SORT))
    IMPLEMENT_WINSTYLE_PROPERTY(CShellComboCtrlComp,Style,(CBS_SIMPLE|CBS_DROPDOWN|CBS_DROPDOWNLIST))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CShellComboCtrlComp,NoIntegralHeight,(CBS_NOINTEGRALHEIGHT))

    CRect CShellComboCtrlComp::GetBoundsRect(void)
    {
        CRect rc;
        if(::IsWindow((HWND)GetHandle()) && designer)	
            rc=bounds;
        else
            rc=Component::GetBoundsRect();
        return rc;
    }

    void CShellComboCtrlComp::set_ItemHeight(long val)
    {
        SetItemHeight(0,val);
        SetModified();
    }

    long CShellComboCtrlComp::get_ItemHeight()
    {
        return GetItemHeight(0);
    }

    void CShellComboCtrlComp::set_EditHeight(long val)
    {
        SetItemHeight(-1,val);
        SetModified();
    }

    long CShellComboCtrlComp::get_EditHeight()
    {
        return GetItemHeight(-1);
    }

    void CShellComboCtrlComp::set_DroppedWidth(long val)
    {
        SetDroppedWidth(val);
        SetModified();
    }

    long CShellComboCtrlComp::get_DroppedWidth()
    {
        return GetDroppedWidth();
    }

    void CShellComboCtrlComp::set_HorizontalExtent(long val)
    {
        SetHorizontalExtent(val);
        SetModified();
    }

    long CShellComboCtrlComp::get_HorizontalExtent()
    {
        return GetHorizontalExtent();
    }

    void CShellComboCtrlComp::set_ShowDropDown(BOOL val)
    {
        ShowDropDown(val);
    }

    BOOL CShellComboCtrlComp::get_ShowDropDown()
    {
        return GetDroppedState();
    }

    void CShellComboCtrlComp::set_CurSel(long val)
    {
        SetCurSel(val);
        SetModified();
    }

    long CShellComboCtrlComp::get_CurSel()
    {
        return GetCurSel();
    }

    void CShellComboCtrlComp::set_Path(CString val)
    {
        path = val;
        Populate(path);
        SetModified();
    }

    CString CShellComboCtrlComp::get_Path()
    {
        return path;
    }

    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,NoFolders,SCT_EX_NOFOLDERS)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,NoFiles,SCT_EX_NOFILES)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,ShowHidden,SCT_EX_SHOWHIDDEN)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,NoReadOnly,SCT_EX_NOREADONLY)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,LocalComputer,SCT_EX_LOCALCOMPUTER)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,FileSysytemOnly,SCT_EX_FILESYSTEMONLY)
    IMPLEMENT_SHELL_BOOL_PROPERTY(CShellComboCtrlComp,NoRoot,SCT_EX_NOROOT)

 //////////////////////////////////////////////////////////////////////////
}

BEGIN_LIST_PROPERTY(ComboBoxStyle)
LIST_ITEM_DECORATE(CBS_SIMPLE,CBS_SIMPLE,Simple)
LIST_ITEM_DECORATE(CBS_DROPDOWN,CBS_DROPDOWN,DropDown)
LIST_ITEM_DECORATE(CBS_DROPDOWNLIST,CBS_DROPDOWNLIST,DropDownList)
END_LIST_ITEM(ComboBoxStyle)

static void RegisterComboBoxStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;
    REGISTER_LIST_PROPERTY(ComboBoxStyle)
    IsInited=TRUE;
}