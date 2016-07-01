// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "ScanfEdit.h"
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
	REGISTER_COMPONENT_EX(CScanfEditCtrlComp,CScanfEditCtrlComp,ViksoeCtrl,IDB_SCANFEDITCTRL)
		
	CScanfEditCtrlComp::CScanfEditCtrlComp(LPTSTR _name):ControlComponent<CScanfEditCtrlComp>(_name)
	{
		SetDefaultSize(40,20);
	}
	
	
	CScanfEditCtrlComp::~CScanfEditCtrlComp(void)
	{
	}
	
	BOOL CScanfEditCtrlComp::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CScanfEditCtrl::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		_Init();
		return ::IsWindow(m_hWnd);
	}
	
	void CScanfEditCtrlComp::InitProperty(void)
	{
		ControlComponent<CScanfEditCtrlComp>::InitProperty();
		DEFINE_PROPERTY(Caption,CString,CScanfEditCtrlComp,_T(""))
		DEFINE_PROPERTY(Mask,CString,CScanfEditCtrlComp,_T(""))
	}
	
	void CScanfEditCtrlComp::set_Caption(CString str)
	{
		caption.Empty();
		caption=(LPCTSTR)str;
		if(IsWindow())
		{
			SetWindowText(caption);
			SetModified();			
		}
	}
	
	CString CScanfEditCtrlComp::get_Caption(void)
	{
		if(state.GetBit(csLoading))
		{
			caption= GET_PROP_VALUE(CString, Caption)
		}
		return caption;
	}
	

	void CScanfEditCtrlComp::set_Mask(CString str)
	{
		mask.Empty();
		mask=(LPCTSTR)str;
		if(IsWindow())
		{
			SetFormat(mask);
			ActivateItem(0, TRUE);
			SetModified();			
		}
	}
	
	CString CScanfEditCtrlComp::get_Mask(void)
	{
		if(state.GetBit(csLoading))
		{
			mask= GET_PROP_VALUE(CString, Mask)
		}
		return mask;
	}
	
};
#endif
