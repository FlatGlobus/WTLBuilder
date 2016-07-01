// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#include "StdAfx.h"
#include "animatectrl.h"
#include "resource.h"
#include "PropertyTextEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterAnimateCtrlStyles();
typedef CString AviImageFileNameType;

namespace StdCtrl
{
	REGISTER_COMPONENT(CAnimateCtrl,StdCtl,IDB_ANIMATECTRL)

		CAnimateCtrl::CAnimateCtrl(LPTSTR _name):ControlComponent<StdCtrl::CAnimateCtrl>(_name)
	{
		RegisterAnimateCtrlStyles();
	}

	CAnimateCtrl::~CAnimateCtrl(void)
	{
	}

	BOOL CAnimateCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CAnimateCtrl,WTL::CAnimateCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		image.Change.SetObject(this);
		image.Change.SetMethod(&CAnimateCtrl::OnImageChange);
		return ::IsWindow(m_hWnd);
	}

	void CAnimateCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CAnimateCtrl>::InitProperty();
        REMOVE_PROPERTY(Transparent)
		DEFINE_PROPERTY(AutoPlay,BOOL,CAnimateCtrl,FALSE)
		DEFINE_PROPERTY(Center,BOOL,CAnimateCtrl,FALSE)
		DEFINE_PROPERTY(Timer,BOOL,CAnimateCtrl,FALSE)
		DEFINE_PROPERTY(Transparent,BOOL,CAnimateCtrl,FALSE)
		image.AddProperty(_T("Image"),objprop);
		DEFINE_PROPERTY(Play,BOOL,CAnimateCtrl,FALSE)
	}

	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CAnimateCtrl,AutoPlay,(ACS_AUTOPLAY))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CAnimateCtrl,Center,(ACS_CENTER))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CAnimateCtrl,Timer,(ACS_TIMER))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CAnimateCtrl,Transparent,(ACS_TRANSPARENT))

void CAnimateCtrl::OnImageChange(CAviImage * image)
{
	if(image)
	{
		GetComponents()->Invalidate(TRUE);
		if(image->get_FileName().IsEmpty()==FALSE)
			Open((LPCTSTR)image->get_FileName());
		
		SetBoundsRect(GetBoundsRect());
		SetModified();
	}
}

void CAnimateCtrl::set_Play(BOOL val)
{
	play=val;
	if(play==TRUE)
		Play(0,-1,-1);
	else
		Stop();
}

BOOL CAnimateCtrl::get_Play()
{
	return play;
}

//////////////////////////////////////////////////////////////////////////
CAviImage::CAviImage()
{
}

CAviImage::~CAviImage()
{
}

void CAviImage::set_FileName(CString val)
{
	fileName=val;
	change(this);
}

CString CAviImage::get_FileName()
{
	return fileName;
}

void CAviImage::set_ID(CString val)
{
	id=val;
	change(this);
}

CString CAviImage::get_ID(void)
{
	return id;
}

void CAviImage::AddProperty(LPCTSTR Name,CProperties & objprop)
{
	BEGIN_SUB_PROPERTY(Name,CAviImage)
	DEFINE_SUB_PROPERTY(FileName,AviImageFileNameType,CAviImage,fileName)
	DEFINE_SUB_PROPERTY(ID,CString,CAviImage,_T(""))
	END_SUB_PROPERTY
}

}
//////////////////////////////////////////////////////////////////////////
void ExAviImageEdit(HWND parent,PropertyBase *prop)
{
    static _TCHAR FileFilter[] = _T("AVI Files (*.avi)\0*.avi\0");
	if(prop)
	{
		CFileDialog dlg(TRUE,_T("*.avi"),*(CString *)prop->GetValue(true),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,FileFilter);
		if(dlg.DoModal(::GetDesktopWindow())==IDOK)
		{
			CString str(dlg.m_szFileName);
			prop->SetValue(&str, true);
			UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
		}
	}
}

static void RegisterAnimateCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;
	RegisterConversion(_T("AviImageFileNameType"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("AviImageFileNameType"),CInplaceTextEdit::CreateEdit,(ExPropEdit)ExAviImageEdit);
	RegisterDrawProperty(_T("AviImageFileNameType"),DrawPropertyValueText);

	IsInited=TRUE;
}
