// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "hotkeyctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterStatusBarCtrlStyles();
//typedef long ListViewStyle;
//typedef long ListAlignStyle;
//typedef long ListSortStyle;

namespace StdCtrl
{
    REGISTER_COMPONENT(CHotKeyCtrl,StdCtl,IDB_HOTKEYCTRL)

CHotKeyCtrl::CHotKeyCtrl(LPTSTR _name):ControlComponent<StdCtrl::CHotKeyCtrl>(_name)
{
    SetDefaultSize(80,14);
    RegisterStatusBarCtrlStyles();
}

    CHotKeyCtrl::~CHotKeyCtrl(void)
    {
    }

    BOOL CHotKeyCtrl::CreateComponent(Component * _Parent)
    {
        SetComponentParent(_Parent);
        CWindowImpl<StdCtrl::CHotKeyCtrl,WTL::CHotKeyCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
        return ::IsWindow(m_hWnd);
    }

    void CHotKeyCtrl::InitProperty(void)
    {
        ControlComponent<StdCtrl::CHotKeyCtrl>::InitProperty();
    }
}
//////////////////////////////////////////////////////////////////////////
static void RegisterStatusBarCtrlStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;


    IsInited=TRUE;
}
