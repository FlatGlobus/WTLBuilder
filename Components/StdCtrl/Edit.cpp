// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "edit.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterEditStyles();

typedef long EditAlignText;

namespace StdCtrl
{
REGISTER_COMPONENT(CEdit,StdCtl,IDB_EDIT)
CEdit::CEdit(LPTSTR _name):ControlComponent<StdCtrl::CEdit>(_name)
{
	SetDefaultSize(85,22);
	RegisterEditStyles();
}

CEdit::~CEdit(void)
{
}

BOOL CEdit::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CEdit,WTL::CEdit>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Text(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CEdit::InitProperty(void)
{
	ControlComponent<StdCtrl::CEdit>::InitProperty();
	DEFINE_PROPERTY(AutoHScroll,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(AutoVScroll,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(MultiLine,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(LowerCase,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(NoHideSel,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(Number,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(OemConvert,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(Password,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(ReadOnly,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(UpperCase,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(WantReturn,BOOL,CEdit,FALSE)
	DEFINE_PROPERTY(Text,CString,CEdit,_T(""))
    DEFINE_PROPERTY(CueBannerText, CString, CEdit, _T(""))
	DEFINE_PROPERTY(TextAlign,EditAlignText,CEdit,ES_LEFT)
	//DEFINE_PROPERTY(LimitText,long,CEdit,-1)
	PUBLIC_PROPERTY(VScroll,TRUE)
	PUBLIC_PROPERTY(HScroll,TRUE)
    

} 

void CEdit::set_Text(CString str)
{
	text.Empty();
	text=(LPCTSTR)str;
	if(IsWindow())
		SetWindowText((LPCTSTR)text);
	SetModified();
}

CString CEdit::get_Text(void)
{
	if(state.GetBit(csLoading))
	{
		text= GET_PROP_VALUE(CString, Text)
	}
	return text;
}

void CEdit::set_CueBannerText(CString str)
{
    cueBannerText.Empty();
    cueBannerText = (LPCTSTR)str;
    //if (IsWindow())
    //    SetCueBannerText((LPCWSTR)cueBannerText);
    SetModified();
}

CString CEdit::get_CueBannerText(void)
{
    if (state.GetBit(csLoading))
    {
        cueBannerText = GET_PROP_VALUE(CString, CueBannerText)
    }
    return cueBannerText;
}


//void CEdit::SetLimitText(long)
//{
//}

//long CEdit::GetLimitText(void)
//{
//}


IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,AutoHScroll,(ES_AUTOHSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,AutoVScroll,(ES_AUTOVSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,MultiLine,(ES_MULTILINE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,LowerCase,(ES_LOWERCASE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,NoHideSel,(ES_NOHIDESEL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,Number,(ES_NUMBER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,OemConvert,(ES_OEMCONVERT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,Password,(ES_PASSWORD))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,ReadOnly,(ES_READONLY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,UpperCase,(ES_UPPERCASE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CEdit,WantReturn,(ES_WANTRETURN))
IMPLEMENT_WINSTYLE_PROPERTY(CEdit,TextAlign,(ES_LEFT|ES_CENTER|ES_RIGHT))
//////////////////////////////////////////////////////////////////////////
}
BEGIN_LIST_PROPERTY(EditAlignText)
	LIST_ITEM_DECORATE(ES_LEFT,ES_LEFT,Left)
	LIST_ITEM_DECORATE(ES_CENTER,ES_CENTER,Center)
	LIST_ITEM_DECORATE(ES_RIGHT,ES_RIGHT,Right)
END_LIST_ITEM(EditAlignText)

static void RegisterEditStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(EditAlignText)
	
	IsInited=TRUE;
}
