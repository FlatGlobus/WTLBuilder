// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include <atldlgs.h>
#include <Path.h>
#include "SDK\Property\Component.h"
#include "project.h"
#include "FormType.h"
#include <_util.h>
#include <direct.h>
#include "FormComponent.h"

//////////////////////////////////////////////////////////////////////////
BOOL PROPERTY_API PreReadForm(const CString &fn,CString &page,CString &cmpName);
BOOL PROPERTY_API ExtractName(CString &str,CString &cmpPage,CString &cmpName);
//static _TCHAR Filter[] = "Project Files (*.vcproj)\0*.vcproj\0Form Files (*.wff)\0*.wff\0";
//static _TCHAR Filter[] = _T("Form Files (*.wff)\0*.wff\0Project Files (*.vcproj)\0*.vcproj\0");
static _TCHAR FormFilter[] = _T("Form Files (*.wff)\0*.wff\0");
static _TCHAR LocFilter[] = _T("Localization Files (*.lng)\0*.lng\0");
//////////////////////////////////////////////////////////////////////////
CProject::CProject(Component * _mainForm):mainForm(_mainForm)
{
}

CProject::~CProject(void)
{
	UnRegisterEvent(this);
}

void __stdcall CProject::New()
{
	Component * newForm=CreateForm(_T(""));
	if(newForm)
	{
		forms.Add(newForm);
		newForm->ShowProperties();
		SendEvent(evSetActiveForm,newForm);
	}
}

BOOL __stdcall CProject::Open(BSTR fn)
{
    USES_CONVERSION;
    CString _fn(fn);
    CString page(_T("Form"));
    CString cmpName(_T("CFrameWindowImpl"));
    CPath fileName(_fn);

	if(fileName.IsFilePath()==FALSE)
	{
		CFileDialog filedlg(TRUE,_T("*.wff"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,FormFilter);
		if(filedlg.DoModal(::GetDesktopWindow())!=IDOK)
			return FALSE;
		fileName=filedlg.m_szFileName;
	}

    CWaitCursor wc;

    if(fileName.GetExt()==_T("wff"))
    {
		Component *tmp = NULL;
		if ((tmp=forms.Find((LPCSTR)fileName)) != NULL)
		{
			::ShowWindow((HWND)tmp->GetHandle(), SW_SHOWNORMAL);
			SendEvent(evSetActiveForm, tmp);
			return TRUE;
		}

        if(PreReadForm(fileName.GetPath(),page,cmpName)==FALSE)
        {	
            ::MessageBox(NULL,MakeString(_T("Error loading form file %s."),(LPCTSTR)fileName),_T("WTLBuilder"),MB_OK);
            return NULL;
        }

        Component * form=NULL;
        SendEvent(evCreateComponent,(LPCTSTR)cmpName,(LPCTSTR)page,&form);
        if(form)
        {
            //form->set_UniqueID(forms.get_Count());
            form->InitProperty();
            SendEvent(evLoadForm,mainForm,&form,(LPCTSTR)fileName,FALSE);
            if(form==NULL)
            {
                ::MessageBox(NULL,MakeString(_T("Error loading form file %s."),(LPCTSTR)fileName),_T("WTLBuilder"),MB_OK);
                return FALSE;
            }
        }
		else
		{
			SendEvent(evOutput, ErrorMsg, (LPCSTR)MakeString(_T("Component Page = %s, Name = %s not found."), page, cmpName));
		}

        forms.Add(form);
        SendEvent(evFormLoaded,form,(LPCTSTR)fileName);
    }

	return TRUE;
}

BOOL __stdcall CProject::CloseAll()
{
	if(forms.RemoveAll()==FALSE)
        return FALSE;
    return TRUE;
}

BOOL __stdcall CProject::CloseActive()
{
	BOOL remove = TRUE;
	Component * activeForm = forms.Active;
	if(activeForm!=NULL)
	{
		SendEvent(evCloseForm,activeForm,&remove);
		return TRUE;
	}
	return FALSE;
}

Component * CProject::CreateForm(const CString & _formFileName)
{
	CString formFileName=_formFileName;
	CString page(_T("Form"));
	CString cmpName(_T("CFrameWindowImpl"));
	BOOL	makeFromTemplate=formFileName.IsEmpty();
	CString className;
	CString formfilename;

    CString location;
    CString formName;
	if(makeFromTemplate)
	{
		CFormType formType;
		if(formType.DoModal()==IDOK)
        {
			formFileName=formType.GetComponentType();
            location = formType.GetLocation();
            formName = formType.GetFormName();
			formfilename = formType.GetFileName();
        }
		else
			return NULL;
	}
	
	if(PreReadForm(formFileName,page,cmpName)==FALSE)
	{	
		::MessageBox(NULL,MakeString(_T("Error loading form file %s."),(LPCTSTR)formFileName),_T("WTLBuilder"),MB_OK);
		return NULL;
	}
    
    CWaitCursor wc;

	Component * form=NULL;
	SendEvent(evCreateComponent,(LPCTSTR)cmpName,(LPCTSTR)page,&form);
	if(form)
	{
        form->set_UniqueID(forms.get_Count());
		form->InitProperty();
		SendEvent(evLoadForm,mainForm,&form,(LPCTSTR)formFileName,makeFromTemplate);
        form->set_Name(formName);
        if(location[location.GetLength()-1] != _T('\\'))
            location += _T('\\');
        _mkdir(location);
        CString resLocation(location);
        resLocation+=_T("res");
        _mkdir(resLocation);
        location = location+formfilename+_T(".wff");
        SendEvent(evSetFormFileName,form,(LPCTSTR)location);

		CPath templateFile(formFileName);
		templateFile.SetExt("js");
		SendEvent(evLoadScriptFromFile, (LPCSTR)templateFile);
		SendEvent(evSaveForm, form, FALSE);
	}
	else
	{
		SendEvent(evOutput, ErrorMsg, (LPCSTR)MakeString(_T("Component Page = %s, Name = %s not found."), (LPCTSTR)page, (LPCTSTR)cmpName));
	}

	return form;
}

void __stdcall CProject::Save()
{
    CWaitCursor wc;
    BOOL asTemplate=FALSE;
    CMsgPump pump;
	SendEvent(evSaveForm,forms.Active,asTemplate);
    EnableMsgPump(TRUE);
}

void CProject::SaveAs()
{
    SendEvent(evSaveAsForm,forms.Active);
}

void CProject::SaveAll()
{
    BOOL asTemplate=FALSE;
    for(long i = 0; i < forms.get_Count(); i++)
        SendEvent(evSaveForm,forms.Item(i),asTemplate);
}

BSTR __stdcall CProject::get_Name(void)
{
	return projectName.AllocSysString();
}

BSTR __stdcall CProject::get_Path(void)
{
	return projectName.AllocSysString();
}

CForms * __stdcall CProject::get_Forms(void)
{
	return &forms;
}

CString CProject::GetTemplatesPath()
{
	CString templatesPath=CPath::GetAppPath();
	templatesPath+=_T("Template\\");
	return templatesPath;
}

void CProject::SaveAsTemplate(void)
{
	if(forms.Active==NULL)
		return;
	CString formName=((CCodeGenerator *)forms.Active->get_Code())->GetVar(_T("CLASSNAME"));
	CString templatesPath=GetTemplatesPath();
	CString formFileName;
	SendEvent(evGetFormFileName,forms.Active,&formFileName);
	if(formName.IsEmpty()==FALSE)
	{
		formFileName=formName;
	}
	else
		if(formFileName.IsEmpty())
		{
			CFileDialog filedlg(FALSE,_T("*.wff"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,FormFilter);
			filedlg.m_ofn.lpstrInitialDir=(LPCTSTR)templatesPath;
			if(filedlg.DoModal(GetDesktopWindow())!=IDOK)
				return;
			formFileName=filedlg.m_szFileName;
		}

    CWaitCursor wc;
    CPath temp(formFileName);
	templatesPath+=temp.GetTitle();
	templatesPath+=_T("\\");
    _mkdir(templatesPath);
	templatesPath+=temp.GetFileName();
	SendEvent(evSaveFormAsTemplate,forms.Active,&templatesPath);
}

void CProject::GenerateLocFile(void)
{
    if(forms.Active==NULL)
        return;

   	CString formFileName=_T(" ");
	SendEvent(evGetFormFileName,forms.Active,&formFileName);
    CPath temp(formFileName);
    
    CFileDialog filedlg(FALSE,_T("*.lng"),temp.GetTitle(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,LocFilter);
    if(filedlg.DoModal(GetDesktopWindow())!=IDOK)
        return;

    CWaitCursor wc;
    SendEvent(evGenerateLocFile,filedlg.m_szFileName);
        
}
//////////////////////////////////////////////////////////////////////////
CForms::CForms(void):active(NULL)
{
	RegisterEvent(evSetActiveForm,this,&CForms::SetActiveForm);
	RegisterEvent(evGetActiveForm,this,&CForms::GetActiveForm);
	RegisterEvent(evCloseForm,this,&CForms::CloseForm);
    RegisterEvent(evAddUndo,this,&CForms::AddUndo,64);
}

CForms::~CForms(void)
{
	forms.clear();
	UnRegisterEvent(this);
}

Component * __stdcall CForms::Item(long Index)
{
	if(Index < (long)forms.size())
	{
		return forms[Index];
	}
	return NULL;
}

long __stdcall CForms::get_Count(void)
{
	return (long)forms.size();
}

LPUNKNOWN __stdcall CForms::get__NewEnum()
{
	long formCount=(long)forms.size();

	VARIANT * pVar=new VARIANT[formCount];
	for(int i=0; i < formCount; i++)
	{
		pVar[i].vt=VT_DISPATCH;
		pVar[i].pdispVal=forms[i];
	}

	typedef CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT,
		_Copy<VARIANT> > VarArrEnum;
	typedef CComObject<VarArrEnum> enumVar;

	enumVar * pEnumVar=new enumVar;
	pEnumVar->Init(&pVar[0],&pVar[formCount],NULL,AtlFlagCopy);
	delete pVar;
	LPUNKNOWN pVal=NULL;
	pEnumVar->QueryInterface(IID_IUnknown,(void**)pVal);
	return pVal;
}

void __stdcall CForms::Add(Component * form)
{
	if(form)
	{
		forms.push_back(form);
		active=form;
		SendEvent(evAddForm,form);
	}
}

void CForms::CloseForm(Component * form,BOOL * remove)
{
    if(*remove==FALSE)
        return;
	for(long i=0; i < (long)forms.size(); i++)
		if(forms[i]==form)
		{
			if(forms[i]==active)
			{
				active=NULL;
				RemoveProperties();
			}
			forms.erase(forms.begin()+i);
			//::DestroyWindow(form->GetHandle());//delete form;
			break;
		}
}

BOOL __stdcall CForms::Remove(long Index)
{
    BOOL remove=TRUE;
	if(Index < (long)forms.size())
		SendEvent(evCloseForm,forms[Index],&remove);
    return remove;
}

BOOL CForms::RemoveAll()
{
	for(;forms.size()!=0;)
		if(Remove(0)==FALSE)
            return FALSE;

	SendEvent(evCloseAllForms);
	active=NULL;
    return TRUE;
}

Component * __stdcall CForms::get_Active(void)
{
	return static_cast<Component *>(active);
}

void __stdcall CForms::set_Active(Component * form)
{
	::ShowWindow((HWND)form->GetHandle(),SW_SHOWMINNOACTIVE);
	active=form;
}

void CForms::SetActiveForm(Component *form)
{
	active=form;
}

void CForms::GetActiveForm(Component **form)
{
	if(form)
		*form=active;
    StopEvent(evGetActiveForm);//?????
}

void CForms::AddUndo(Component *form)
{
    //if(form==NULL)
    //{
    //    SendEvent(evAddUndo,active);
    //    StopEvent(evAddUndo);
   // }
}

Component * CForms::Find(const CString & str)
{
	for (long i = 0; i < (long)forms.size(); i++)
	{
		if (str.CompareNoCase(((CFormComponent *)forms.at(i))->GetFileName()) == 0)
			return forms.at(i);
	}
	return NULL;
}