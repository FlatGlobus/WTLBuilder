// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include "resource.h"

#include "Package.h"
#include "Command.h"
#include "File.h"
#include "Register.h"

CAppModule _Module;

PACKAGE_API CPackage *Package=NULL;
LPCTSTR DEF_PACKAGE_EXT = _T("*.dll");
LPCTSTR DEF_PACKAGE_DIR = _T("package\\");
LPCTSTR DEF_MODULE_DIR = _T("");

BOOL APIENTRY DllMain( HANDLE hInstance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            _Module.Init(NULL, (HINSTANCE)hInstance);
            Package=new CPackage;
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            _Module.Term();
            if(Package)
                delete Package;
            break;
   }
    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
CPackageItem::CPackageItem(void):Handle(NULL), DllName(_T(""))
{
}

CPackageItem::CPackageItem(const CString & n):Handle(NULL), DllName(n)
{
}

CPackageItem::~CPackageItem(void)
{
    Free();
}

BOOL CPackageItem::Load(void)
{
    if (Handle)
        return TRUE;

    if(DllName.IsEmpty())
        return FALSE;

    Handle = ::LoadLibrary(DllName);
    return IsLoaded();
}

void CPackageItem::Free(void)
{
    if (IsLoaded())
        ::FreeLibrary(Handle);
    Handle =    NULL;
}

void CPackageItem::SetName(const CString & n)
{
    DllName = n;
}

const CString & CPackageItem::GetName(void)
{
    return DllName;
}

BOOL CPackageItem::IsLoaded(void)
{
    return Handle != NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////		
CPackage::CPackage()
{ 
    RegisterEvent(evLoadPackages,this,&CPackage::LoadPackages,0);
    RegisterEvent(evStartingUp,this,&CPackage::StartingUp);
    defBitmap.LoadBitmap(IDB_DEFAULT);	
}

CPackage::~CPackage(void)
{
    FreePackages();	
    UnRegisterEvent(this);
}

HBITMAP CPackage::GetDefaulBitmap()
{
    return defBitmap;
}

void CPackage::ScanFolder(LPCTSTR folder,LPCTSTR ext)
{
    CString appPath=CPath::GetAppPath();
    appPath=appPath+folder;
    CStringArray packageNames;
    CPath::GetAllFilesFromFolder(appPath,TRUE,packageNames,ext);
    for(int i= 0; i < (int)packageNames.GetSize();i++)
        packages.Add(CPackageItem(packageNames[i]));
}

void * CPackage::CreateByName(LPCTSTR name)
{
    return NULL;
}

void CPackage::LoadPackages(void)
{
    ScanFolder(DEF_PACKAGE_DIR,DEF_PACKAGE_EXT);
    for(int i=0; i < packages.GetSize();i++)
    {
        packages[i].Load();
    }
}

void CPackage::FreePackages(void)
{
    for(int i=0; i < packages.GetSize();i++)
    {
        packages[i].Free();
    }
    packages.RemoveAll();
}

void CPackage::StartingUp(void)
{
    //CMenuHandle pMenuAdd;
    //if(pMenuAdd.LoadMenu(IDR_PACKAGE_MENU))
    //	SendEvent(evAddMenu,&pMenuAdd,true);
}

void CPackage::OnCommand(UINT id)
{
}