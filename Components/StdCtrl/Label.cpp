// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "label.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterStaticStyles();

typedef long StaticAlignText;
namespace StdCtrl
{
REGISTER_COMPONENT(CStatic,StdCtl,IDB_STATIC)
StdCtrl::CStatic::CStatic(LPTSTR _name):ControlComponent<StdCtrl::CStatic>(_name)
{
	SetDefaultSize(60,14);
	RegisterStaticStyles();
	enableTabIndex=FALSE;
}

CStatic::~CStatic(void)
{
}

BOOL CStatic::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CStatic,WTL::CStatic>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Caption(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CStatic::InitProperty(void)
{
	ControlComponent<StdCtrl::CStatic>::InitProperty();
	DEFINE_PROPERTY(Caption,CString,CStatic,(LPCTSTR)get_Name())
	DEFINE_PROPERTY(Notify,BOOL,CStatic,FALSE)
	DEFINE_PROPERTY(TextAlign,StaticAlignText,CStatic,SS_LEFT)
 	DEFINE_PROPERTY(Simple,BOOL,CStatic,FALSE)
	DEFINE_PROPERTY(Etched,BOOL,CStatic,FALSE)
	DEFINE_PROPERTY(WordWrap,BOOL,CStatic,FALSE)
	DEFINE_PROPERTY(NoPrefix,BOOL,CStatic,TRUE)
}

void CStatic::set_Caption(CString str)
{
	caption.Empty();
	caption=(LPCTSTR)str;
	if(IsWindow())
		SetWindowText((LPCTSTR)caption);
	SetModified();
}

CString CStatic::get_Caption(void)
{
	if(state.GetBit(csLoading))
	{
		caption= GET_PROP_VALUE(CString, Caption)
	}
	return caption;
}

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatic,Notify,(SS_NOTIFY))
IMPLEMENT_WINSTYLE_PROPERTY(CStatic,TextAlign,(SS_LEFT|SS_CENTER|SS_RIGHT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatic,Simple,(SS_SIMPLE))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatic,Etched,(SS_ETCHEDFRAME))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CStatic,WordWrap,(SS_LEFTNOWORDWRAP))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY_NOT(CStatic,NoPrefix,(SS_NOPREFIX))
//////////////////////////////////////////////////////////////////////////

REGISTER_COMPONENT(CPicture,StdCtl,IDB_PICTURE)
StdCtrl::CPicture::CPicture(LPTSTR _name):ControlComponent<StdCtrl::CPicture>(_name)
{
	SetDefaultSize(25,25);
	RegisterStaticStyles();
}

CPicture::~CPicture(void)
{
}

BOOL CPicture::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CPicture,WTL::CStatic>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
    image.Change.SetObject(this);
    image.Change.SetMethod(&CPicture::OnImageChange);
	return ::IsWindow(m_hWnd);
}

void CPicture::InitProperty(void)
{
	ControlComponent<StdCtrl::CPicture>::InitProperty();
	DEFINE_PROPERTY(Notify,BOOL,CPicture,FALSE)
	DEFINE_PROPERTY(Etched,BOOL,CPicture,FALSE)
    DEFINE_PROPERTY(CenterImage,BOOL,CPicture,FALSE)
    image.AddProperty(_T("Image"),objprop);
}

void CPicture::OnImageChange(CImage *)
{
    if((HBITMAP)image)
    {
        ModifyStyle(SS_ICON,SS_BITMAP);
        SetBitmap((HBITMAP)image);
    }
    else
        if((HICON)image)
        {
            ModifyStyle(SS_BITMAP,SS_ICON);
            SetIcon((HICON)image);

        }
		else
		{
			ModifyStyle(SS_BITMAP | SS_ICON, 0);
		}

		set_InternalWindowStyle(GetWindowLong(GWL_STYLE));
        SetModified();
        ::InvalidateRect(GetParent(),NULL,FALSE);
}

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CPicture,Notify,(SS_NOTIFY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CPicture,Etched,(SS_ETCHEDFRAME))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY_NOT(CPicture,CenterImage,(SS_CENTERIMAGE))
/////////////////////////////////////////////////////////////////////////////////////////

}
BEGIN_LIST_PROPERTY(StaticAlignText)
	LIST_ITEM_DECORATE(SS_LEFT,SS_LEFT,Left)
	LIST_ITEM_DECORATE(SS_CENTER,SS_CENTER,Center)
	LIST_ITEM_DECORATE(SS_RIGHT,SS_RIGHT,Right)
END_LIST_ITEM(StaticAlignText)

//BEGIN_LIST_PROPERTY(StaticStyles)
//    LIST_ITEM_DECORATE(TEXT_STYLE,TEXT_STYLE,Text)
//	LIST_ITEM_DECORATE(SS_BITMAP,SS_BITMAP,Bitmap)
//	LIST_ITEM_DECORATE(SS_BLACKFRAME,SS_BLACKFRAME,BlackFrame)
//	LIST_ITEM_DECORATE(SS_ENHMETAFILE,SS_ENHMETAFILE,EnMetafile)
//	LIST_ITEM_DECORATE(SS_GRAYFRAME,SS_GRAYFRAME,GrayFrame)
//	LIST_ITEM_DECORATE(SS_GRAYRECT,SS_GRAYRECT,GrayRect)
//	LIST_ITEM_DECORATE(SS_ICON,SS_ICON,Icon)
//	LIST_ITEM_DECORATE(SS_WHITEFRAME,SS_WHITEFRAME,WhiteFrame)
//	LIST_ITEM_DECORATE(SS_WHITERECT,SS_WHITERECT,WhiteRect)
//END_LIST_ITEM(StaticStyles)

static void RegisterStaticStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(StaticAlignText)
//    REGISTER_LIST_PROPERTY(StaticStyles)
	
	IsInited=TRUE;
}
