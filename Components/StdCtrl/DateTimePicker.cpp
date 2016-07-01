// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "DateTimePicker.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "PropertyTextEdit.h"
static void RegisterDateTimePickerStyles();
typedef long DateTimePickerStyle;
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	REGISTER_COMPONENT(CDateTimePickerCtrl,StdCtl,IDB_DATETIME)

	CDateTimePickerCtrl::CDateTimePickerCtrl(LPTSTR _name):ControlComponent<StdCtrl::CDateTimePickerCtrl>(_name),
    format(DTS_SHORTDATEFORMAT),showNone(FALSE)
	{
        RegisterDateTimePickerStyles();
		SetDefaultSize(85,22);
	}

	CDateTimePickerCtrl::~CDateTimePickerCtrl(void)
	{
	}

	BOOL CDateTimePickerCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CDateTimePickerCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CDateTimePickerCtrl>::InitProperty();
        DEFINE_PROPERTY(Format,DateTimePickerStyle,CDateTimePickerCtrl,DTS_SHORTDATEFORMAT)
        DEFINE_PROPERTY(AppCanParse,BOOL,CDateTimePickerCtrl,FALSE)
        DEFINE_PROPERTY(RightAlign,BOOL,CDateTimePickerCtrl,FALSE)
        DEFINE_PROPERTY(ShowNone,BOOL,CDateTimePickerCtrl,FALSE)
        DEFINE_PROPERTY(UpDown,BOOL,CDateTimePickerCtrl,FALSE)
	}
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateTimePickerCtrl,AppCanParse,(DTS_APPCANPARSE ))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateTimePickerCtrl,RightAlign,(DTS_RIGHTALIGN))
    //IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateTimePickerCtrl,ShowNone,(DTS_SHOWNONE))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateTimePickerCtrl,UpDown,(DTS_UPDOWN))

    void CDateTimePickerCtrl::set_Format(long val)
    {
		DWORD windowStyle = get_InternalWindowStyle();
        windowStyle&=~(DTS_SHORTDATEFORMAT|DTS_LONGDATEFORMAT|DTS_TIMEFORMAT);
        windowStyle|=val;
        format=val;
        set_InternalWindowStyle(windowStyle);
    }

    long CDateTimePickerCtrl::get_Format(void)
    {
        return format; 
    }
    
    void CDateTimePickerCtrl::set_ShowNone(BOOL val)
    {
        showNone = val;
        SetModified();
    }

    BOOL CDateTimePickerCtrl::get_ShowNone(void)
    {
        return showNone; 
    }

}

BEGIN_LIST_PROPERTY(DateTimePickerStyle)
    LIST_ITEM_DECORATE(DTS_SHORTDATEFORMAT,DTS_SHORTDATEFORMAT,ShortDateFormat)
    LIST_ITEM_DECORATE(DTS_LONGDATEFORMAT,DTS_LONGDATEFORMAT,LongDateFormat)
    LIST_ITEM_DECORATE(DTS_TIMEFORMAT,DTS_TIMEFORMAT,TimeFormat)
END_LIST_ITEM(DateTimePickerStyle)

static void RegisterDateTimePickerStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;
    REGISTER_LIST_PROPERTY(DateTimePickerStyle)

    IsInited=TRUE;
}