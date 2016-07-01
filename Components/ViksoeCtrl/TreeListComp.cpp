// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "TreeListComp.h"
#include "resource.h"
#include "PropertyListEdit.h"
#ifdef __WTLBUILDER__
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeListViewCtrlStyles();
namespace ViksoeCtrl
{
    REGISTER_COMPONENT_EX(CTreeListView,CTreeListViewComp,ViksoeCtrl,IDB_TREELISTVIEW)

    CTreeListViewComp::CTreeListViewComp(LPTSTR _name):ControlComponent<ViksoeCtrl::CTreeListViewComp>(_name)
    {
        SetDefaultSize(120,128);
        RegisterTreeListViewCtrlStyles();
    }

    CTreeListViewComp::~CTreeListViewComp(void)
    {
    }

    BOOL CTreeListViewComp::CreateComponent(Component * _Parent)
    {
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
        return ::IsWindow(m_hWnd);
    }

    void CTreeListViewComp::InitProperty(void)
    {
        ControlComponent<ViksoeCtrl::CTreeListViewComp>::InitProperty();
    }
}
//////////////////////////////////////////////////////////////////////////
static void RegisterTreeListViewCtrlStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;
        IsInited=TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
#endif
