// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "menu.h"
#include "resource.h"

namespace StdCtrl
{
//пока полностью не реализовано, убрать, чтоб не мешалось
//    REGISTER_COMPONENT(CMenu,StdCtl,IDB_MENU)

    CMenu::CMenu(LPTSTR _name):Component(_name)
    {
		enableTabIndex=FALSE;
    }

    CMenu::~CMenu(void)
    {
    }

    BOOL CMenu::CreateComponent(Component *_Parent)
    {
        return Component::CreateComponent(_Parent);
    }

	void CMenu::DeleteComponent()
	{
		Component::DeleteComponent();
	}

    void CMenu::InitProperty(void)
    {
        Component::InitProperty();
		DEFINE_PROPERTY(ID,CString,CMenu,"")
    }

	void CMenu::set_ID(CString str)
	{
		menuID=str;
		SetModified();
	}

	CString CMenu::get_ID(void)
	{
		if(state.GetBit(csLoading))
		{
			menuID= GET_PROP_VALUE(CString, ID)
		}
		return menuID;
	}

	void CMenu::CreateSampleMenu()
	{
		if(hMenu.IsMenu() == FALSE)
		{
			hMenu.LoadMenu(_U_STRINGorID(IDR_SAMPLE_MENU));
		}
	}

	HANDLE CMenu::GetHandle()
	{
		CreateSampleMenu();
		return (HANDLE)hMenu.Detach();
	}
}