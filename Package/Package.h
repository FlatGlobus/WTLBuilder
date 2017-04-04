// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PACKAGE_H
#define __PACKAGE_H
//////////////////////////////////////////////////////////////////////////
#include "EventLib.h"
#include "PackageApi.h"
#pragma warning( disable:4251)  
//////////////////////////////////////////////////////////////////////////
class CPackageItem
{
public:
    CPackageItem(void);
    CPackageItem(const CString &);
    ~CPackageItem(void);
    BOOL            Load(void);
    void            Free(void);
    void            SetName(const CString &);
    const CString & GetName(void);
    BOOL            IsLoaded(void);
protected:
    CString          DllName;
    HINSTANCE        Handle;
};

//////////////////////////////////////////////////////////////////////////
typedef CSimpleArray<CPackageItem> CPackages;
class PACKAGE_API CPackage
{
public:
    CPackage(void);
    ~CPackage(void);
    
    void * CreateByName(LPCTSTR);
    void LoadPackages(void);
    void FreePackages(void);
    void StartingUp(void);
    void OnCommand(UINT);
    void ScanFolder(LPCTSTR folder,LPCTSTR ext);
    HBITMAP GetDefaulBitmap();
protected:
    CBitmap defBitmap;
    CPackages packages;
};

extern PACKAGE_API CPackage * Package;
//////////////////////////////////////////////////////////////////////////
#endif
