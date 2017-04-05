// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include <Path.h>
#include <CFile.h>
#include "Component.h"
#include "Codegen.h"
#include "_util.h"
//////////////////////////////////////////////////////////////////////////////////////////////
CCodeGenerator::CCodeGenerator():templateName(""),header(""),source(""),localize("")
{
}

CCodeGenerator::~CCodeGenerator()
{
    variables.RemoveAll();
}

BOOL CCodeGenerator::LoadSource(const CString & str)
{
    CPath fileName(str);
    fileName.SetExt(_T("cpp"));

    if(fileName.IsFilePath()==FALSE || str.IsEmpty())
    {
        MessageBox(NULL,MakeString(_T("File %s not found."),(LPCTSTR)fileName),_T("Error"),MB_OK);
        return FALSE;
    }
    source=LoadString((LPCTSTR)fileName);
    return source.IsEmpty()==FALSE;
}

BOOL CCodeGenerator::LoadHeader(const CString & str)
{
    CPath fileName(str);
    fileName.SetExt(_T("h"));

    if(fileName.IsFilePath()==FALSE || str.IsEmpty())
    {
        MessageBox(NULL,MakeString(_T("File %s not found."),(LPCTSTR)fileName),_T("Error"),MB_OK);
        return FALSE;
    }

    header=LoadString((LPCTSTR)fileName);
    return header.IsEmpty()==FALSE;
}

BOOL CCodeGenerator::SaveSource(const CString & str)
{
    if(source.IsEmpty())
        return FALSE;

    Untabify(source);
    CPath fileName(str);
    fileName.SetExt(_T("cpp"));
    return SaveString((LPCTSTR)fileName,source);
}

BOOL CCodeGenerator::SaveHeader(const CString & str)
{
    if(header.IsEmpty())
        return FALSE;

    Untabify(header);
    CPath fileName(str);
    fileName.SetExt(_T("h"));
    return SaveString((LPCTSTR)fileName,header);
}

BOOL CCodeGenerator::SaveLocalize(const CString & str)
{
    if(localize.IsEmpty())
        return FALSE;

    CPath fileName(str);
    fileName.SetExt(_T("lng"));
    return SaveString((LPCTSTR)fileName,localize);
}

BSTR __stdcall CCodeGenerator::get_Header()
{
    return header.AllocSysString();
}

void __stdcall CCodeGenerator::put_Header(BSTR str)
{
    header=str;
}

BSTR __stdcall CCodeGenerator::get_Source()
{
    return source.AllocSysString();
}

void __stdcall CCodeGenerator::put_Source(BSTR str)
{
    source=str;
}

BSTR __stdcall CCodeGenerator::get_Localize()
{
    return localize.AllocSysString();
}

void __stdcall CCodeGenerator::put_Localize(BSTR str)
{
    localize=str;
}

void __stdcall CCodeGenerator::Insert(BSTR brace,BSTR str)
{
    CString pattern(brace);
    CString s(str);
    int pos=header.Find(pattern);
    if(pos!=-1)
        header.Insert(pos,s);
    
    pos=source.Find(pattern);
    if(pos!=-1)
        source.Insert(pos,s);
}

BOOL __stdcall CCodeGenerator::IsEmptyHeader(BSTR _Begin,BSTR _End)
{
    CString Begin(_Begin);
    CString End(_End);

    if(Begin.IsEmpty() || End.IsEmpty())
        return TRUE;
    int pos1=header.Find(Begin);
    int pos2=header.Find(End);
    if(pos1!=-1 && pos2!=-1 && pos2 > pos1)
    {
        pos1+=Begin.GetLength();
        for(int i=pos1; i <=pos2; i++)
            if(_istalnum(header[i])!=0)
                return FALSE;
    }
    return TRUE;
}

BOOL __stdcall CCodeGenerator::IsEmptySource(BSTR _Begin,BSTR _End)
{
    CString Begin(_Begin);
    CString End(_End);
    
    if(Begin.IsEmpty() || End.IsEmpty())
        return TRUE;
    
    int pos1=source.Find(Begin);
    int pos2=source.Find(End);
    
    if(pos1!=-1 && pos2!=-1 && pos2 > pos1)
    {
        pos1+=Begin.GetLength();
        for(int i=pos1; i <=pos2;i++)
            if(_istalnum(source[i])!=0)
                return FALSE;
    }
    return TRUE;
}

void __stdcall CCodeGenerator::ClearBetween(BSTR Begin,BSTR End)
{
    EmptyHeader(CString(Begin),CString(End));
    EmptySource(CString(Begin),CString(End));
}

void __stdcall CCodeGenerator::AddInclude(BSTR brace,BSTR str)
{
    CString pattern(brace);
    CString s(str);
    int pos=header.Find(pattern);
    if(pos!=-1 && header.Find(s)==-1)
    {
        CString includeStr;
        includeStr+=_T("#include \"");
        includeStr+=s;
        includeStr+=_T("\"\n");
        header.Insert(pos,includeStr);
    }
}

void CCodeGenerator::EmptyHeader(CString & Begin,CString & End)
{
    if(Begin.IsEmpty() || End.IsEmpty())
        return;
    int pos1=header.Find(Begin);
    int pos2=header.Find(End);
    if(pos1!=-1 && pos2!=-1 && pos2 > pos1)
    {
        pos1+=Begin.GetLength();
        header.Delete(pos1+1,pos2-pos1-1);
    }
}

void CCodeGenerator::EmptySource(CString & Begin,CString & End)
{
    if(Begin.IsEmpty() || End.IsEmpty())
        return;

    int pos1=source.Find(Begin);
    int pos2=source.Find(End);
        
    if(pos1!=-1 && pos2!=-1 && pos2 > pos1)
    {
        pos1+=Begin.GetLength();
        source.Delete(pos1+1,pos2-pos1-1);
    }
}

void CCodeGenerator::SetTemplateName(const CString &str)
{
    CPath fn(CPath::GetAppPath(),TRUE);
    templateName=(LPCTSTR)fn;
    templateName+=_T("Template\\");
    templateName+=str;
}

void CCodeGenerator::FormatForm(void)
{
    header=FormatString(NULL,header);
    source=FormatString(NULL,source);
}

BSTR __stdcall CCodeGenerator::Format(Component * component,BSTR formatStr)
{
    CString fs(formatStr);
    CString str=FormatString(component,fs);
    return str.AllocSysString();
}

CString CCodeGenerator::FormatString(Component *component,LPCTSTR str)
{
    enum State{stAdd,stKeyword};

    State state=stAdd;
    
    CString result;
    CString expression;
    if(str!=NULL)
    {
        _TCHAR ch=0,ch1=0;
        int i = 0;
        while((ch = *(str + i)) != 0)
        {
            if(ch=='[' && state!=stKeyword)
            {
                ch1 = *(str + i + 1);
                if ( ch1 == '!')
                {
                    state = stKeyword;
                    expression.Empty();
                    i += 2; //skip [!
                    continue;
                }
            }

            if(ch == ']' && state==stKeyword)
            {
                expression.TrimLeft();
                expression.TrimRight();
                result+=Name2Val(component,expression);
                state=stAdd;
                i += 1;
                continue;
            }
            
            if(state==stKeyword)
            {
                expression+=ch;
                i += 1;
                continue;
            }

            if(state==stAdd)
            {
                result+=ch;
                i += 1;
            }
            
        }
    }
    return result;
}

CString CCodeGenerator::Name2Val(Component *component,LPCTSTR str) 
{
    CString val;

    Variable *var=variables.Find(str);
    if(var)
        val=variables.GetValue(str);
    else
        val=MakeString(_T("The name \"%s\" is incorrect."),str);

    if(component && str && var==NULL)
    {
        CProperties * prop=component->GetProperty();
        val=prop->GetPropValueStr(str);
    }

    return val;
}

void CCodeGenerator::AddVar(const CString & name,const CString & val)
{
    variables.Add(name,val);
}

CString CCodeGenerator::GetVar(const CString & name)
{
    return variables.GetValue(name);
}
//TODO option - num of spaces 
void CCodeGenerator::Untabify(CString& str)
{
    str.Replace(_T("\t"),_T("    "));
}

void CCodeGenerator::RemoveFormName(CString& str)
{
    header.Replace(str, _T("[!CLASSNAME]"));
    source.Replace(str, _T("[!CLASSNAME]"));
}

//////////////////////////////////////////////////////////////////////////
Variable::Variable(void)
{
}

Variable::Variable(const CString & n,const CString & val):name(n),value(val)
{
}

Variable::~Variable(void)
{
}

void Variable::Reset()
{
    name.Empty();
    value.Empty();
}

void Variable::AddValue(const CString & val)
{
    value=val;
}

const CString & Variable::GetValue(void)
{
    return value;
}

const CString & Variable::GetName(void)
{
    return name;
}

int Variable::operator == (const CString & n)
{
    return name==n;
}

int Variable::operator != (const CString & n)
{
    return name!=n;
}
//////////////////////////////////////////////////////////////////////////////////////////////
VarArray::VarArray(void)
{
}

VarArray::~VarArray(void)
{
    RemoveAll();
}

void VarArray::Add(const CString & name,const CString & val)
{
    Variable *var;
    if((var=Find(name))==NULL)
    {
      var=new Variable(name,val);
        vararray.Add(var);
    }
    else
    {
        var->AddValue(val);
    }
}

CString VarArray::GetValue(const CString & name)
{
    Variable *var=Find(name);
    if(var)
        return var->GetValue();
    
    return _T("");
}

void VarArray::RemoveAll(void)
{
    for(int i=0; i < vararray.GetSize();i++)
        delete vararray[i];
    
    vararray.RemoveAll();
}

Variable * VarArray::Find(const CString & n)
{
    for(int i=0; i < vararray.GetSize(); i++)
        if(vararray[i]->GetName()==n)
            return vararray[i];
        
    return NULL;
}

