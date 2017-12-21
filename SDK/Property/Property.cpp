// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "PropertyList.h"

CAppModule _Module;

void InitProperty(void);

BOOL APIENTRY DllMain( HANDLE hInstance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			_Module.Init(NULL, (HINSTANCE)hInstance);
			InitProperty();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			_Module.Term();
			break;
    }
    return TRUE;
}


static CPropertyList propertyList;

void RegisterThemes();

extern "C" PROPERTY_API CPropertyList * CreatePropertyList(HWND Parent, CRect &rc,UINT id)
{
    RegisterThemes();
	if(::IsWindow(propertyList.m_hWnd)==NULL)
		propertyList.Create(Parent,rc,id);

	return 	&propertyList;
}

extern "C" PROPERTY_API void RemoveProperties(void)
{
	if(::IsWindow(propertyList.m_hWnd))
	{
		propertyList.ResetContent();
	}
}

extern "C" PROPERTY_API void ShowProperties(CProperties * p)
{
	if(::IsWindow(propertyList.m_hWnd))
	{
		propertyList.InsertProperty(p);
	}
}

extern "C" PROPERTY_API void UpdateProperty(const CString & p)
{
	if(::IsWindow(propertyList.m_hWnd))
	{
		propertyList.UpdateProperty(p);
	}
}
