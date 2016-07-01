// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "updownctrl.h"
#include "resource.h"
#include "ComponentList.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	REGISTER_COMPONENT(CUpDownCtrl,StdCtl,IDB_UPDOWNCTRL)
    typedef long AlignStyle;
    typedef long BaseStyle;
    static void RegisterUpDownCtrlStyles();
	CUpDownCtrl::CUpDownCtrl(LPTSTR _name):ControlComponent<StdCtrl::CUpDownCtrl>(_name),
    lover(0),upper(100),buddy(_T("NULL"))
	{
        RegisterUpDownCtrlStyles();
		SetDefaultSize(16,20);
		enableTabIndex=FALSE;
	}

	CUpDownCtrl::~CUpDownCtrl(void)
	{
	}

	BOOL CUpDownCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CUpDownCtrl,WTL::CUpDownCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CUpDownCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CUpDownCtrl>::InitProperty();
        DEFINE_PROPERTY(Base,BaseStyle,CUpDownCtrl,10)
        DEFINE_PROPERTY(Buddy,ComponentName,CUpDownCtrl,_T("NULL"))
        DEFINE_PROPERTY(Pos,int,CUpDownCtrl,0)
        DEFINE_PROPERTY(Lover,int,CUpDownCtrl,lover)
        DEFINE_PROPERTY(Upper,int,CUpDownCtrl,upper)
        DEFINE_PROPERTY(Align,AlignStyle,CUpDownCtrl,UDS_ALIGNRIGHT)
        DEFINE_PROPERTY(ArrowKeys,BOOL,CUpDownCtrl,TRUE)
        DEFINE_PROPERTY(AutoBuddy,BOOL,CUpDownCtrl,FALSE)
        DEFINE_PROPERTY(Horz,BOOL,CUpDownCtrl,FALSE)
        DEFINE_PROPERTY(HotTrack,BOOL,CUpDownCtrl,FALSE)
        DEFINE_PROPERTY(NoThousands,BOOL,CUpDownCtrl,FALSE)
        DEFINE_PROPERTY(SetBuddyInt,BOOL,CUpDownCtrl,TRUE)
        DEFINE_PROPERTY(Wrap,BOOL,CUpDownCtrl,FALSE)
	}

    IMPLEMENT_WINSTYLE_PROPERTY(CUpDownCtrl,Align,(UDS_ALIGNLEFT|UDS_ALIGNRIGHT))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,ArrowKeys,(UDS_ARROWKEYS))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,AutoBuddy,(UDS_AUTOBUDDY))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,Horz,(UDS_HORZ))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,HotTrack,(UDS_HOTTRACK))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,NoThousands,(UDS_NOTHOUSANDS))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,SetBuddyInt,(UDS_SETBUDDYINT))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CUpDownCtrl,Wrap,(UDS_WRAP))

    void CUpDownCtrl::set_Base(int val)
    {
        if(GetBase()!=val)
        {
            SetBase(val);
            SetModified();
        }
    }

    int CUpDownCtrl::get_Base(void)
    {
        return GetBase();
    }

    void CUpDownCtrl::set_Pos(int val)
    {
        if(GetPos()!=val)
        {
            SetPos(val);
            SetModified();
        }
    }

    int CUpDownCtrl::get_Pos(void)
    {
        return GetPos();
    }

    void CUpDownCtrl::set_Lover(int val)
    {
        if(lover!=val)
        {
            lover=val;
            SetRange(lover,upper);
            SetModified();
        }
    }

    int CUpDownCtrl::get_Lover(void)
    {
        return lover;
    }

    void CUpDownCtrl::set_Upper(int val)
    {
        if(upper!=val)
        {
            upper=val;
            SetRange(lover, upper);
            SetModified();
        }
    }

    int CUpDownCtrl::get_Upper(void)
    {
        return upper;
    }

    void CUpDownCtrl::set_Buddy(CString val)
    {
        if(buddy!=val)
        {
            SetModified();
            Component * temp=Find(val);
            if(temp!=NULL)
            {
                buddy=val;
                //SetBuddy((HWND)temp->GetHandle());
            }
            else
            {
                buddy=CComponentListEdit::GetNoneStr();
                //SetBuddy(NULL);
                return;
            }
        }
    }

    CString CUpDownCtrl::get_Buddy(void)
    {
        CComponentListEdit::SetComponentKind(_T(""));
        return buddy;
    }

    BEGIN_LIST_PROPERTY(AlignStyle)
        LIST_ITEM_DECORATE(UDS_ALIGNLEFT ,UDS_ALIGNLEFT ,Left)
        LIST_ITEM_DECORATE(UDS_ALIGNRIGHT ,UDS_ALIGNRIGHT ,Right)
    END_LIST_ITEM(AlignStyle)

    BEGIN_LIST_PROPERTY(BaseStyle)
        LIST_ITEM_DECORATE(10 ,10 ,Decimal)
        LIST_ITEM_DECORATE(16 ,16 ,Hexadecimal)
    END_LIST_ITEM(BaseStyle)

    void RegisterUpDownCtrlStyles()
    {
        static BOOL IsInited=FALSE;
        if(IsInited==TRUE)
            return;

        REGISTER_LIST_PROPERTY(AlignStyle)
        REGISTER_LIST_PROPERTY(BaseStyle)

        IsInited=TRUE;
    }
}
//////////////////////////////////////////////////////////////////////////
