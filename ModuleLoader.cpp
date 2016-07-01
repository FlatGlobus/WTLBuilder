// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "ModuleLoader.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModuleLoader::CModuleLoader()
{
	Add(_T("Package.dll"));
}

CModuleLoader::~CModuleLoader()
{
	Free();
}

void CModuleLoader::Load(void)
{
	for(int i=0; i < modules.GetSize();i++)
	{
		modules[i].Load();
	}
}

void CModuleLoader::Free(void)
{
	for(int i=0; i < modules.GetSize();i++)
	{
		modules[i].Free();
	}
}

void CModuleLoader::Add(const CString & name,BOOL DoLoad)
{
	modules.Add(CModuleItem(name));
	if(DoLoad==TRUE)
		Load();

}
//////////////////////////////////////////////////////////////////////////
CModuleItem::CModuleItem(void):Handle(NULL), DllName(_T(""))
{
	
}

CModuleItem::CModuleItem(const CString & n):Handle(NULL), DllName(n)
{
}

CModuleItem::~CModuleItem(void)
{
    Free();
}

BOOL CModuleItem::Load(void)
{
    if (Handle)
		return TRUE;
	if(DllName.IsEmpty())
        return FALSE;
    Handle = ::LoadLibrary(DllName);
    return IsLoaded();
}

void CModuleItem::Free(void)
{
    if (IsLoaded())
        ::FreeLibrary(Handle);
    Handle =    NULL;
}

void CModuleItem::SetName(const CString & n)
{
    DllName = n;
}

const CString & CModuleItem::GetName(void)
{
    return DllName;
}

BOOL CModuleItem::IsLoaded(void)
{
    return Handle != NULL;
}
