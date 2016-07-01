// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#include "StdAfx.h"
#include "button.h"
#include "resource.h"
#include "PropertyListEdit.h"

//////////////////////////////////////////////////////////////////////////
static void RegisterButtonStyles();
typedef long VertAlignButtonStyle;
typedef long HorizAlignButtonStyle;
typedef long ButtonStyle;
typedef long ButtonCheck;
typedef CString Bitmap;
typedef long CheckBoxStyle;
typedef long RadioButtonStyle;
namespace StdCtrl
{
REGISTER_COMPONENT(CButton,StdCtl,IDB_BUTTON)
REGISTER_COMPONENT(CBitmapButton,StdCtl,IDB_BITMAP_BUTTON)
REGISTER_COMPONENT(CCheckBox,StdCtl,IDB_CHECKBOX)
REGISTER_COMPONENT(CRadioButton,StdCtl,IDB_RADIOBUTTON)
REGISTER_COMPONENT(CGroupBox,StdCtl,IDB_GROUPBOX)

CButton::CButton(LPTSTR _name):ControlComponent<StdCtrl::CButton>(_name)
{
	SetDefaultSize(85,22);
	RegisterButtonStyles();
}

CButton::~CButton(void)
{
}

BOOL CButton::CreateComponent(Component * _Parent)
{
	ADD_WIN_STYLE(BS_CENTER| BS_VCENTER)
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CButton,WTL::CButton>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Caption(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
	bitmap.Change.SetObject(this);
	bitmap.Change.SetMethod(&CButton::OnImageChange);
	return ::IsWindow(m_hWnd);
}

void CButton::OnImageChange(CImage * image)
{
	if(image)
	{
		if((HBITMAP)*image)
			CButton::SetBitmap(*image);
		
		else
			if((HICON)*image)
				CButton::SetIcon(*image);
	}
	SetModified();
}

void CButton::InitProperty(void)
{
	ControlComponent<StdCtrl::CButton>::InitProperty();
	DEFINE_PROPERTY(Caption,CString,CButton,(LPCTSTR)get_Name())
	DEFINE_PROPERTY(VertAlign,VertAlignButtonStyle,CButton,BS_VCENTER)
	DEFINE_PROPERTY(HorizAlign,HorizAlignButtonStyle,CButton,BS_CENTER)
	DEFINE_PROPERTY(Flat,BOOL,CButton,FALSE)
	DEFINE_PROPERTY(DefPushButton,BOOL,CButton,FALSE)
	DEFINE_PROPERTY(MultiLine,BOOL,CButton,FALSE)
	DEFINE_PROPERTY(Notify,BOOL,CButton,FALSE)
	DEFINE_PROPERTY(PushButton,BOOL,CButton,FALSE)
	DEFINE_PROPERTY(LeftText,BOOL,CButton,FALSE)
	PUBLIC_PROPERTY(LeftText,FALSE)
	bitmap.AddProperty(_T("Image"),objprop);	
	DEFINE_PROPERTY(Style,ButtonStyle,CButton,BS_TEXT)
	DEFINE_PROPERTY(Check,ButtonCheck,CButton,BST_UNCHECKED)
	PUBLIC_PROPERTY(Check,FALSE)
}
   
void CButton::set_Caption(CString str)
{
	caption.Empty();
	caption=(LPCTSTR)str;
	if(IsWindow())
		SetWindowText((LPCTSTR)caption);
	SetModified();
}

CString CButton::get_Caption(void)
{
	if(state.GetBit(csLoading))
	{
		caption= GET_PROP_VALUE(CString, Caption)
	}
	return caption;
}

void CButton::set_Check(long val)
{
	SetCheck(val);
	SetModified();
}

long CButton::get_Check(void)
{
	return GetCheck();
}

//LRESULT CButton::OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//{
	//bkBrush.Color=bkColor;
	//bHandled=TRUE;
//	return (LRESULT)(HBRUSH)bkBrush;
//}

IMPLEMENT_WINSTYLE_PROPERTY(CButton,VertAlign,(BS_TOP|BS_VCENTER|BS_BOTTOM))
IMPLEMENT_WINSTYLE_PROPERTY(CButton,HorizAlign,(BS_LEFT|BS_CENTER|BS_RIGHT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CButton,Flat,(BS_FLAT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CButton,DefPushButton,(BS_DEFPUSHBUTTON))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CButton,MultiLine,(BS_MULTILINE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CButton,Notify,(BS_NOTIFY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CButton,PushButton,(BS_PUSHBUTTON))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CButton,LeftText,(BS_LEFTTEXT))

void CButton::set_Style(long val)
{
	DWORD windowStyle = get_InternalWindowStyle();
	windowStyle&=~(BS_BITMAP|BS_ICON|BS_TEXT);
	windowStyle|=val;
	set_InternalWindowStyle(windowStyle);
	if(val!=BS_TEXT)
		OnImageChange(&bitmap);
}

long CButton::get_Style(void)
{
	return get_InternalWindowStyle() & (BS_BITMAP|BS_ICON|BS_TEXT);
}

//////////////////////////////////////////////////////////////////////////
CBitmapButton::CBitmapButton(LPTSTR _name):ControlComponent<StdCtrl::CBitmapButton>(_name)
{
    SetDefaultSize(85,22);
    RegisterButtonStyles();
}

CBitmapButton::~CBitmapButton(void)
{
}

BOOL CBitmapButton::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
    Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Caption(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
    bitmap.Change.SetObject(this);
    bitmap.Change.SetMethod(&CBitmapButton::OnImageChange);
    return ::IsWindow(m_hWnd);
}

void CBitmapButton::OnImageChange(CImage * image)
{
    if(image)
    {
        if((HBITMAP)*image)
            CBitmapButton::SetBitmap(*image);

        else
            if((HICON)*image)
                CBitmapButton::SetIcon(*image);
    }
    SetModified();
}

void CBitmapButton::InitProperty(void)
{
    ControlComponent<StdCtrl::CBitmapButton>::InitProperty();
    DEFINE_PROPERTY(Caption,CString,CBitmapButton,(LPCTSTR)get_Name())
        DEFINE_PROPERTY(VertAlign,VertAlignButtonStyle,CBitmapButton,BS_VCENTER)
        DEFINE_PROPERTY(HorizAlign,HorizAlignButtonStyle,CBitmapButton,BS_CENTER)
        DEFINE_PROPERTY(Flat,BOOL,CBitmapButton,FALSE)
        DEFINE_PROPERTY(DefPushButton,BOOL,CBitmapButton,FALSE)
        DEFINE_PROPERTY(MultiLine,BOOL,CBitmapButton,FALSE)
        DEFINE_PROPERTY(Notify,BOOL,CBitmapButton,FALSE)
        DEFINE_PROPERTY(PushButton,BOOL,CBitmapButton,FALSE)
        DEFINE_PROPERTY(LeftText,BOOL,CBitmapButton,FALSE)
        PUBLIC_PROPERTY(LeftText,FALSE)
        bitmap.AddProperty(_T("Image"),objprop);	
        DEFINE_PROPERTY(Style,ButtonStyle,CBitmapButton,BS_TEXT)
        DEFINE_PROPERTY(Check,ButtonCheck,CBitmapButton,BST_UNCHECKED)
        PUBLIC_PROPERTY(Check,FALSE)
}

void CBitmapButton::set_Caption(CString str)
{
    caption.Empty();
    caption=(LPCTSTR)str;
    if(IsWindow())
        SetWindowText((LPCTSTR)caption);
    SetModified();
}

CString CBitmapButton::get_Caption(void)
{
    if(state.GetBit(csLoading))
    {
        caption= GET_PROP_VALUE(CString, Caption)
    }
    return caption;
}

void CBitmapButton::set_Check(long val)
{
    SetCheck(val);
    SetModified();
}

long CBitmapButton::get_Check(void)
{
    return GetCheck();
}


IMPLEMENT_WINSTYLE_PROPERTY(CBitmapButton,VertAlign,(BS_TOP|BS_VCENTER|BS_BOTTOM))
IMPLEMENT_WINSTYLE_PROPERTY(CBitmapButton,HorizAlign,(BS_LEFT|BS_CENTER|BS_RIGHT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CBitmapButton,Flat,(BS_FLAT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CBitmapButton,DefPushButton,(BS_DEFPUSHBUTTON))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CBitmapButton,MultiLine,(BS_MULTILINE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CBitmapButton,Notify,(BS_NOTIFY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CBitmapButton,PushButton,(BS_PUSHBUTTON))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CBitmapButton,LeftText,(BS_LEFTTEXT))

void CBitmapButton::set_Style(long val)
{
	DWORD windowStyle = get_InternalWindowStyle();
    windowStyle&=~(BS_BITMAP|BS_ICON|BS_TEXT);
    windowStyle|=val;
    set_InternalWindowStyle(windowStyle);
    if(val!=BS_TEXT)
        OnImageChange(&bitmap);
}

long CBitmapButton::get_Style(void)
{
    return get_InternalWindowStyle() & (BS_BITMAP|BS_ICON|BS_TEXT);
}
//////////////////////////////////////////////////////////////////////////
StdCtrl::CCheckBox::CCheckBox(LPTSTR _name):StdCtrl::CButton(_name),checked(FALSE)
{
	SetDefaultSize(100,16);
	RegisterButtonStyles();
}

StdCtrl::CCheckBox::~CCheckBox(void)
{
}

void CCheckBox::InitProperty(void)
{
	CButton::InitProperty();
	ADD_WIN_STYLE(BS_CHECKBOX)
	PUBLIC_PROPERTY(Check,TRUE)
	objprop.Remove(_T("DefPushButton"));
	objprop.Remove(_T("PushButton"));
	PUBLIC_PROPERTY(LeftText,TRUE)
	DEFINE_PROPERTY(CheckBoxStyle,CheckBoxStyle,CCheckBox,BS_CHECKBOX)
	long val=BS_LEFT;
	SET_PROP_VALUE(HorizAlign,val)
}
IMPLEMENT_WINSTYLE_PROPERTY(CCheckBox,CheckBoxStyle,(BS_CHECKBOX|BS_3STATE|BS_AUTO3STATE|BS_AUTOCHECKBOX))
//////////////////////////////////////////////////////////////////////////
CGroupBox::CGroupBox(LPTSTR _name):StdCtrl::CButton(_name)
{
	SetDefaultSize(152,94);
    //windowStyleEx|=WS_EX_TRANSPARENT;
	RegisterButtonStyles();
}

CGroupBox::~CGroupBox(void)
{
}

void CGroupBox::InitProperty(void)
{
	CButton::InitProperty();
	ADD_WIN_STYLE(BS_GROUPBOX)
	objprop.Remove(_T("DefPushButton"));
	objprop.Remove(_T("PushButton"));
	PUBLIC_PROPERTY(LeftText,FALSE)
	SET_PROP_VALUE(HorizAlign, BS_LEFT)
	SET_PROP_VALUE(VertAlign, BS_TOP)
}
//////////////////////////////////////////////////////////////////////////
CRadioButton::CRadioButton(LPTSTR _name):StdCtrl::CButton(_name),checked(FALSE)
{
	SetDefaultSize(100,16);
	RegisterButtonStyles();
}

CRadioButton::~CRadioButton(void)
{
}

void CRadioButton::InitProperty(void)
{
	CButton::InitProperty();
	ADD_WIN_STYLE(BS_RADIOBUTTON)
	objprop.Remove(_T("DefPushButton"));
	objprop.Remove(_T("PushButton"));
	PUBLIC_PROPERTY(LeftText,TRUE)
	PUBLIC_PROPERTY(Check,TRUE)
	long val=BS_LEFT;
	
	SET_PROP_VALUE(HorizAlign,val);
	DEFINE_PROPERTY(RadioButtonStyle,RadioButtonStyle,CRadioButton,BS_RADIOBUTTON)
}
IMPLEMENT_WINSTYLE_PROPERTY(CRadioButton,RadioButtonStyle,(BS_RADIOBUTTON|BS_AUTORADIOBUTTON))
//////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////
BEGIN_LIST_PROPERTY(HorizAlignButtonStyle)
	LIST_ITEM_DECORATE(BS_LEFT,BS_LEFT,Left)
	LIST_ITEM_DECORATE(BS_CENTER,BS_CENTER,Center)
	LIST_ITEM_DECORATE(BS_RIGHT,BS_RIGHT,Right)
END_LIST_ITEM(HorizAlignButtonStyle)

BEGIN_LIST_PROPERTY(VertAlignButtonStyle)
	LIST_ITEM_DECORATE(BS_TOP,BS_TOP,Top)
	LIST_ITEM_DECORATE(BS_VCENTER,BS_VCENTER,Center)
	LIST_ITEM_DECORATE(BS_BOTTOM,BS_BOTTOM,Bottom)
END_LIST_ITEM(VertAlignButtonStyle)

BEGIN_LIST_PROPERTY(ButtonStyle)
	LIST_ITEM_DECORATE(BS_TEXT,BS_TEXT,Text)
	LIST_ITEM_DECORATE(BS_BITMAP,BS_BITMAP,Bitmap)
	LIST_ITEM_DECORATE(BS_ICON,BS_ICON,Icon)
END_LIST_ITEM(ButtonStyle)

BEGIN_LIST_PROPERTY(ButtonCheck)
	LIST_ITEM(BST_UNCHECKED,UnChecked)
	LIST_ITEM(BST_CHECKED,Checked)
	LIST_ITEM(BST_INDETERMINATE,Inderterminate)
END_LIST_ITEM(ButtonCheck)

BEGIN_LIST_PROPERTY(CheckBoxStyle)
	LIST_ITEM(BS_CHECKBOX,CheckBox)
	LIST_ITEM(BS_AUTOCHECKBOX,AutoCheckBox)
	LIST_ITEM(BS_3STATE,3State)
	LIST_ITEM(BS_AUTO3STATE,Auto3State)
END_LIST_ITEM(CheckBoxStyle)

BEGIN_LIST_PROPERTY(RadioButtonStyle)
LIST_ITEM(BS_RADIOBUTTON,RadioButton)
LIST_ITEM(BS_AUTORADIOBUTTON,AutoRadioButton)
END_LIST_ITEM(RadioButtonStyle)

static void RegisterButtonStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(HorizAlignButtonStyle)
	REGISTER_LIST_PROPERTY(VertAlignButtonStyle)
	REGISTER_LIST_PROPERTY(ButtonStyle)
	REGISTER_LIST_PROPERTY(ButtonCheck)
	REGISTER_LIST_PROPERTY(CheckBoxStyle)
	REGISTER_LIST_PROPERTY(RadioButtonStyle)
	IsInited=TRUE;
}
