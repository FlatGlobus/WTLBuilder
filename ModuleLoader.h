// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
class CModuleItem
{
public:
    CModuleItem(void);
    CModuleItem(const CString &);
    ~CModuleItem(void);
    BOOL            Load(void);
    void            Free(void);
    void            SetName(const CString &);
    const CString & GetName(void);
    BOOL            IsLoaded(void);
protected:
    CString          DllName;
    HINSTANCE        Handle;
};

typedef CSimpleArray<CModuleItem> CModuleItems;

class CModuleLoader  
{
public:
	CModuleLoader();
	virtual ~CModuleLoader();
	void Load(void);
	void Free(void);
	void Add(const CString &,BOOL DoLoad=FALSE);
protected:
	CModuleItems modules;
};
//////////////////////////////////////////////////////////////////////////
