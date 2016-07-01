// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "propertybox.h"
#include "..\Property\Register.h"
#include "resource.h"
#include "..\Property\PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
namespace WTLBuilderCtrl
{
	REGISTER_COMPONENT(CPropertyList,WTLBuilderCtrl,IDB_PROPERTYBOX)
	CPropertyList::CPropertyList(LPTSTR _name):ControlComponent<CPropertyList>(_name)
	{
		m_bkgBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	}

	CPropertyList::~CPropertyList(void)
	{
	}

	BOOL CPropertyList::CreateComponent(Component * _Parent)
	{
		ADD_WIN_STYLE(LBS_SORT | LBS_OWNERDRAWFIXED | WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT)
        SetComponentParent(_Parent);
		CWindowImpl<CPropertyList,WTL::CListBox>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Name(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CPropertyList::InitProperty(void)
	{
		ControlComponent<CPropertyList>::InitProperty();
	}

	LRESULT CPropertyList::OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& handled)
	{
		handled=TRUE;
		SetBkColor((HDC)wParam,::GetSysColor(COLOR_BTNFACE));
		SetTextColor((HDC)wParam,RGB(0,0,0));
		return (LRESULT)(HBRUSH)m_bkgBrush;
	}

	//////////////////////////////////////////////////////////////////////////
}
