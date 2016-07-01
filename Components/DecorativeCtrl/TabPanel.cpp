// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "TabPanel.h"
//////////////////////////////////////////////////////////////////////////
//static void RegisterTabCtrlStyles();
namespace StdCtrl
{
	REGISTER_COMPONENT_EX(CTabPanel,CTabPanelComp,DecorativeCtrl,IDB_TABCTRL)

CTabPanelComp::CTabPanelComp(LPTSTR _name):ControlComponent<CTabPanelComp>(_name)
{
	SetDefaultSize(50,50);
}

CTabPanelComp::~CTabPanelComp(void)
{
}

BOOL CTabPanelComp::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
    TCITEM tab = { 0 };
    tab.mask = TCIF_TEXT;   
    tab.pszText = _T("Page 0");
    tab.cchTextMax = 7;
    m_tab.InsertItem(0, &tab);
    
	//AddPage();
	return ::IsWindow(m_hWnd);
}

void CTabPanelComp::InitProperty(void)
{
	ControlComponent<CTabPanelComp>::InitProperty();
	//DEFINE_PROPERTY(Current,long,CTabCtrl,0)
}
}
//////////////////////////////////////////////////////////////////////////
//static void RegisterTabCtrlStyles()
//{
//	static IsInited=FALSE;
//	if(IsInited==TRUE)
//		return;


//	IsInited=TRUE;
//}
