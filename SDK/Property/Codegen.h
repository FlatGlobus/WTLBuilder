// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TEMPLATER_H
#define __TEMPLATER_H
//////////////////////////////////////////////////////////////////////////////////////////////
class Variable
{
public:
	Variable(void);
	Variable(const CString & name,const CString & val);
	~Variable(void);
	void AddValue(const CString &);
	const CString & GetValue(void);
	const CString & GetName(void);
	void Reset();
	int operator == (const CString &);
	int operator != (const CString &);
protected:
	CString name;
	CString value;
};

typedef CSimpleArray<Variable *> VarArrayType;

class VarArray
{
public:
	VarArray(void);
	~VarArray(void);
	void Add(const CString & name,const CString & val);
	void RemoveAll(void);
	Variable * Find(const CString &);
	CString GetValue(const CString & name);
protected:
	VarArrayType vararray;
};

class  PROPERTY_API CCodeGenerator:public IDispDynImpl<CCodeGenerator>
{
public:
	CCodeGenerator(void);
	virtual ~CCodeGenerator(void);

	BEGIN_DISPATCH_MAP(CCodeGenerator)
          DISP_PROP(Header,VT_BSTR)
          DISP_PROP(Source,VT_BSTR)
          DISP_PROP(Localize,VT_BSTR)
		DISP_METHOD(Insert,VT_EMPTY, 2, VTS_BSTR VTS_BSTR)
                DISP_METHOD(IsEmptyHeader,VT_BOOL, 2, VTS_BSTR VTS_BSTR)
                DISP_METHOD(IsEmptySource,VT_BOOL, 2, VTS_BSTR VTS_BSTR)
		DISP_METHOD(ClearBetween,VT_EMPTY, 2, VTS_BSTR VTS_BSTR)
		DISP_METHOD(Format,VT_BSTR, 2, VTS_DISPATCH VTS_BSTR)
        DISP_METHOD(AddInclude,VT_EMPTY, 2, VTS_BSTR VTS_BSTR)
	END_DISPATCH_MAP()

	BSTR __stdcall get_Header();
	void __stdcall put_Header(BSTR);

	BSTR __stdcall get_Source();
	void __stdcall put_Source(BSTR);

   	BSTR __stdcall get_Localize();
	void __stdcall put_Localize(BSTR);

	void __stdcall Insert(BSTR,BSTR);//вставляет текст между скобками
	void __stdcall ClearBetween(BSTR,BSTR);//удаляет содержимое между скобками
	BSTR __stdcall Format(Component *,BSTR);//форматирует строку
    BOOL __stdcall IsEmptyHeader(BSTR,BSTR);
    BOOL __stdcall IsEmptySource(BSTR,BSTR);
    void __stdcall AddInclude(BSTR,BSTR);//добавляет include

	BOOL LoadSource(const CString &);
	BOOL LoadHeader(const CString &);

	BOOL SaveSource(const CString &);
	BOOL SaveHeader(const CString &);
    BOOL SaveLocalize(const CString &);

	void SetTemplateName(const CString &);
	void AddVar(const CString & name,const CString & val);
	CString GetVar(const CString & name);
	void FormatTemplate(void);
protected:
	void EmptyHeader(CString & Begin,CString & End);
	void EmptySource(CString & Begin,CString & End);
   
	CString Name2Val(Component *component,LPCTSTR str);
	CString FormatString(Component *component,LPCTSTR str);
		
	CString templateName;
	CString header;
	CString source;
    CString localize;
	VarArray variables;
};
//////////////////////////////////////////////////////////////////////////////////////////////
#endif