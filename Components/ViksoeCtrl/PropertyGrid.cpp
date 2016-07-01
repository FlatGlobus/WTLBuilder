// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "PropertyGrid.h"
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
    REGISTER_COMPONENT_EX(CPropertyGridCtrl,CPropertyGridCtrlComp,ViksoeCtrl,IDB_PROPERTYGRID)
        
    CPropertyGridCtrlComp::CPropertyGridCtrlComp(LPTSTR _name):ControlComponent<CPropertyGridCtrlComp>(_name)
    {
        SetDefaultSize(40,40);
    }
    
    
    CPropertyGridCtrlComp::~CPropertyGridCtrlComp(void)
    {
    }
    
    BOOL CPropertyGridCtrlComp::CreateComponent(Component * _Parent)
    {
		ADD_WIN_STYLE(LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS)
        SetComponentParent(_Parent);
        CPropertyGridCtrl::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
        InsertColumn(0, _T("Name"), LVCFMT_LEFT,100,0);
        SetExtendedGridStyle(PGS_EX_SINGLECLICKEDIT | PGS_EX_ADDITEMATEND);
        return ::IsWindow(m_hWnd);
    }
    
    void CPropertyGridCtrlComp::InitProperty(void)
    {
        ControlComponent<CPropertyGridCtrlComp>::InitProperty();
		DEFINE_PROPERTY(FirstColor,CColorref,CPropertyGridCtrlComp,RGB(200,200,255))
		DEFINE_PROPERTY(SecondColor,CColorref,CPropertyGridCtrlComp,RGB(255,255,255))
        /*BEGIN_SUB_PROPERTY(_T("ExGridStyles"),CPropertyGridCtrlComp)
            DEFINE_SUB_PROPERTY(SingleClickEdit,BOOL,CPropertyGridCtrlComp,TRUE)
            DEFINE_SUB_PROPERTY(NoGrid,BOOL,CPropertyGridCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(TabNav,BOOL,CPropertyGridCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(NoSheetNav,BOOL,CPropertyGridCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(FullRowSel,BOOL,CPropertyGridCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(InvertSel,BOOL,CPropertyGridCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(AddItemAtend,BOOL,CPropertyGridCtrlComp,FALSE)
            DEFINE_SUB_PROPERTY(DrawFocus,BOOL,CPropertyGridCtrlComp,FALSE)
        END_SUB_PROPERTY*/

    }
	void CPropertyGridCtrlComp::set_FirstColor(CColorref val)
	{
		SetFirstColor(val);
		SetModified();
	}

	CColorref CPropertyGridCtrlComp::get_FirstColor(void)
	{
		return GetFirstColor();
	}

	void CPropertyGridCtrlComp::set_SecondColor(CColorref val)
	{
		SetSecondColor(val);
		SetModified();
	}

	CColorref CPropertyGridCtrlComp::get_SecondColor(void)
	{
		return GetSecondColor();
	}

};
#endif
