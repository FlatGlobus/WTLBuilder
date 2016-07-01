// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROJECT_H
#define __PROJECT_H
//////////////////////////////////////////////////////////////////////////
#include "atldispa.h"
#include "SDK\Property\Component.h"
#include <vector>

typedef std::vector<Component *> CFormArray;

class CForms:public IDispDynImpl<CForms>
{
	CFormArray forms;
	Component * active;
	void SetActiveForm(Component *);
	void GetActiveForm(Component **);
	void CloseForm(Component *,BOOL *);
    void AddUndo(Component *);

public:
	CForms(void);
	~CForms(void);
	BEGIN_DISPATCH_MAP(CForms)
		DISP_METHOD_ID(Item,DISPID_VALUE,VT_DISPATCH,1,VTS_I4 )
		DISP_PROPGET_ID(_NewEnum,DISPID_NEWENUM,VT_UNKNOWN)
		DISP_PROPGET(Count,VT_I4)
		DISP_METHOD1(Add,VT_EMPTY,VT_DISPATCH)
		DISP_METHOD1(Remove,VT_EMPTY,VT_I4)
		DISP_PROPGET(Active,VT_DISPATCH)
	END_DISPATCH_MAP()
	Component * __stdcall Item(long Index);
	long __stdcall get_Count(void);
	__declspec(property(get=get_Count)) long Count;

	LPUNKNOWN __stdcall get__NewEnum();
	void __stdcall Add(Component *);
	BOOL __stdcall Remove(long Index);

	Component * __stdcall get_Active(void);
	void __stdcall set_Active(Component *);
	__declspec(property(get=get_Active, put=set_Active)) Component *Active;
	BOOL RemoveAll();
};
//////////////////////////////////////////////////////////////////////////

class CProject:public IDispDynImpl<CProject>
{
	Component * mainForm;
	CForms      forms;
	CString projectName;
public:

	CProject(Component * );
	~CProject(void);
	CString GetTemplatesPath();

	BEGIN_DISPATCH_MAP(CProject)
		DISP_PROPGET(Name,VT_BSTR)
		DISP_PROPGET(Path,VT_BSTR)
		DISP_PROPGET(Forms,VT_DISPATCH)
		DISP_METHOD(New,VT_EMPTY,0,VTS_EMPTY)
		DISP_METHOD1(Open,VT_BOOL,VT_BSTR)
		DISP_METHOD1(CloseAll,VT_BOOL,VT_EMPTY)
		DISP_METHOD1(CloseActive,VT_BOOL,VT_EMPTY)
		DISP_METHOD(Save,VT_EMPTY,0,VTS_EMPTY)
	END_DISPATCH_MAP()

	BSTR __stdcall get_Name(void);
	BSTR __stdcall get_Path(void);
	CForms * __stdcall get_Forms(void);
	__declspec(property(get=get_Forms)) CForms * Forms;

	void __stdcall New(void);
	BOOL __stdcall Open(BSTR fileName=NULL);
	BOOL __stdcall CloseAll(void);
	BOOL __stdcall CloseActive(void);
	void __stdcall Save(void);

    void SaveAs();
    void SaveAll();
	void SaveAsTemplate(void);
    void GenerateLocFile(void);
	Component * CreateForm(const CString & formFileName);
};

//////////////////////////////////////////////////////////////////////////
#endif