// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "combobox.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "CStringsEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterComboBoxStyles();
typedef long ComboBoxStyle;
typedef CString Strings;
namespace StdCtrl
{
	REGISTER_COMPONENT(CComboBox,StdCtl,IDB_COMBOBOX)
    StdCtrl::CComboBox::CComboBox(LPTSTR _name):ControlComponent<StdCtrl::CComboBox>(_name),
		limitText(0)
	{
		SetDefaultSize(108,74);
		RegisterComboBoxStyles();
	}

	CComboBox::~CComboBox(void)
	{
	}

	BOOL CComboBox::CreateComponent(Component * _Parent)
	{
		ADD_WIN_STYLE(CBS_DROPDOWN)
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CComboBox,WTL::CComboBox>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Name(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CComboBox::InitProperty(void)
	{
		ControlComponent<StdCtrl::CComboBox>::InitProperty();
		DEFINE_PROPERTY(DisableNoScroll,BOOL,CComboBox,FALSE)
		DEFINE_PROPERTY(AutoScroll,BOOL,CComboBox,TRUE)
		DEFINE_PROPERTY(HasStrings,BOOL,CComboBox,TRUE)
		DEFINE_PROPERTY(Style,ComboBoxStyle,CComboBox,CBS_DROPDOWN)
		DEFINE_PROPERTY(LowerCase,BOOL,CComboBox,FALSE)
		DEFINE_PROPERTY(OemConvert,BOOL,CComboBox,FALSE)
		DEFINE_PROPERTY(UpperCase,BOOL,CComboBox,FALSE)
		DEFINE_PROPERTY(NoIntegralHeight,BOOL,CComboBox,FALSE)
		DEFINE_PROPERTY(Sort,BOOL,CComboBox,TRUE)
		PUBLIC_PROPERTY(VScroll,TRUE)
		DEFINE_PROPERTY(LimitText,long,CComboBox,0)
		DEFINE_PROPERTY(ItemHeight,long,CComboBox,0)
		DEFINE_PROPERTY(EditHeight,long,CComboBox,0)
		DEFINE_PROPERTY(DroppedWidth,long,CComboBox,0)
		DEFINE_PROPERTY(HorizontalExtent,long,CComboBox,bounds.Width())
		DEFINE_PROPERTY(ShowDropDown,BOOL,CComboBox,FALSE)
		DEFINE_PROPERTY(Strings,Strings,CComboBox,_T("Item\n"))
		DEFINE_PROPERTY(CurSel,long,CComboBox,-1)
	}

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,DisableNoScroll,(CBS_DISABLENOSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,AutoScroll,(CBS_AUTOHSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,HasStrings,(CBS_HASSTRINGS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,LowerCase,(CBS_LOWERCASE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,UpperCase,(CBS_UPPERCASE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,OemConvert,(CBS_OEMCONVERT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,Sort,(CBS_SORT))
IMPLEMENT_WINSTYLE_PROPERTY(CComboBox,Style,(CBS_SIMPLE|CBS_DROPDOWN|CBS_DROPDOWNLIST))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CComboBox,NoIntegralHeight,(CBS_NOINTEGRALHEIGHT))

CRect CComboBox::GetBoundsRect(void)
{
	CRect rc;
	if(::IsWindow((HWND)GetHandle()) && designer)	
		rc=bounds;
	else
		rc=Component::GetBoundsRect();
	return rc;
}

void CComboBox::set_LimitText(long val)
{
	limitText=val;
	LimitText(limitText);
	SetModified();
}

long CComboBox::get_LimitText()
{
	return limitText;
}

void CComboBox::set_ItemHeight(long val)
{
	SetItemHeight(0,val);
	SetModified();
}

long CComboBox::get_ItemHeight()
{
	return GetItemHeight(0);
}

void CComboBox::set_EditHeight(long val)
{
	SetItemHeight(-1,val);
	SetModified();
}

long CComboBox::get_EditHeight()
{
	return GetItemHeight(-1);
}

void CComboBox::set_DroppedWidth(long val)
{
	SetDroppedWidth(val);
	SetModified();
}

long CComboBox::get_DroppedWidth()
{
	return GetDroppedWidth();
}

void CComboBox::set_HorizontalExtent(long val)
{
	SetHorizontalExtent(val);
	SetModified();
}

long CComboBox::get_HorizontalExtent()
{
	return GetHorizontalExtent();
}

void CComboBox::set_ShowDropDown(BOOL val)
{
	ShowDropDown(val);
}

BOOL CComboBox::get_ShowDropDown()
{
	return GetDroppedState();
}

void CComboBox::set_CurSel(long val)
{
	SetCurSel(val);
	SetModified();
}

long CComboBox::get_CurSel()
{
	return GetCurSel();
}

void CComboBox::set_Strings(CString val)
{
	Reset();
	FillStringsArray(val);
	for(int i=0; i < strings.GetSize();i++)
		AddString(strings[i]);
	SetModified();
}

CString CComboBox::get_Strings()
{
	CString ret;
	for(int i=0; i < strings.GetSize();i++)
	{
		ret+=strings[i];
		ret+=_T('\n');
	}
	return ret;
}

void CComboBox::Reset()
{
	strings.RemoveAll();
	ResetContent();
}

void CComboBox::FillStringsArray(CString str)
{
	strings.RemoveAll();
	if(str.IsEmpty())
		return;
	int idx=-1;
	while((idx=str.Find(_T("\n")))!=-1)
	{
		strings.Add(str.Left(idx));
		str.Delete(0,idx+1);
	}
}

//////////////////////////////////////////////////////////////////////////
}

BEGIN_LIST_PROPERTY(ComboBoxStyle)
	LIST_ITEM_DECORATE(CBS_SIMPLE,CBS_SIMPLE,Simple)
	LIST_ITEM_DECORATE(CBS_DROPDOWN,CBS_DROPDOWN,DropDown)
	LIST_ITEM_DECORATE(CBS_DROPDOWNLIST,CBS_DROPDOWNLIST,DropDownList)
END_LIST_ITEM(ComboBoxStyle)

static void RegisterComboBoxStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	RegisterConversion(_T("Strings"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("Strings"),NULL,StringsEdit);
	RegisterDrawProperty(_T("Strings"),NULL);

	REGISTER_LIST_PROPERTY(ComboBoxStyle)
	IsInited=TRUE;
}