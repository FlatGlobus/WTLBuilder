// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "listbox.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "CStringsEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterListBoxStyles();
typedef long ListBoxStyle;
typedef CString Strings;
namespace StdCtrl
{
    REGISTER_COMPONENT(CListBox,StdCtl,IDB_LISTBOX)
    StdCtrl::CListBox::CListBox(LPTSTR _name):ControlComponent<StdCtrl::CListBox>(_name)
    {
        SetDefaultSize(96,117);
        RegisterListBoxStyles();
    }

    CListBox::~CListBox(void)
    {
    }

    BOOL CListBox::CreateComponent(Component * _Parent)
    {
        ADD_WIN_STYLE(LBS_NOINTEGRALHEIGHT)
        SetComponentParent(_Parent);
        CWindowImpl<StdCtrl::CListBox,WTL::CListBox>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Name(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
        return ::IsWindow(m_hWnd);
    }

    void CListBox::InitProperty(void)
    {
        ControlComponent<StdCtrl::CListBox>::InitProperty();
        DEFINE_PROPERTY(DisableNoScroll,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(ExtendedSelect,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(HasStrings,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(Style,ListBoxStyle,CListBox,0)
        DEFINE_PROPERTY(MultiColumn,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(MultiSelect,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(NoData,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY_2(NoIntegralHeight,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(NoRedraw,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(NoSelect,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(Notify,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(Sort,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(UseTabStops,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(WantKeyboardInput,BOOL,CListBox,FALSE)
        DEFINE_PROPERTY(HorizontalExtent,long,CListBox,bounds.Width())
        DEFINE_PROPERTY(Strings,Strings,CListBox,_T("Item\n"))
        DEFINE_PROPERTY(CurSel,long,CListBox,-1)
        DEFINE_PROPERTY(ItemHeight,long,CListBox,0)
        DEFINE_PROPERTY(ColumnWidth,long,CListBox,-1)
        PUBLIC_PROPERTY(VScroll,TRUE)
        PUBLIC_PROPERTY(HScroll,TRUE)
        
    }

IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,DisableNoScroll,(LBS_DISABLENOSCROLL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,ExtendedSelect,(LBS_EXTENDEDSEL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,HasStrings,(LBS_HASSTRINGS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,MultiColumn,(LBS_MULTICOLUMN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,MultiSelect,(LBS_MULTIPLESEL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,NoData,(LBS_NODATA))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,NoRedraw,(LBS_NOREDRAW))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,NoSelect,(LBS_NOSEL))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,Notify,(LBS_NOTIFY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,Sort,(LBS_SORT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,UseTabStops,(LBS_USETABSTOPS))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CListBox,WantKeyboardInput,(LBS_WANTKEYBOARDINPUT))
IMPLEMENT_WINSTYLE_PROPERTY(CListBox,Style,(LBS_MULTIPLESEL|LBS_EXTENDEDSEL|LBS_NOSEL))

void CListBox::set_HorizontalExtent(long val)
{
    SetHorizontalExtent(val);
    SetModified();
}

long CListBox::get_HorizontalExtent()
{
    return GetHorizontalExtent();
}

void CListBox::set_CurSel(long val)
{
    if((GetStyle() & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL))==0)
        SetCurSel(val);
    SetModified();
}

long CListBox::get_CurSel()
{
    if((GetStyle() & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL))==0)
        return GetCurSel();
    return -1;
}

void CListBox::set_ItemHeight(long val)
{
    SetItemHeight(-1,val);
    SetModified();
}

long CListBox::get_ItemHeight()
{
    return GetItemHeight(-1);
}

void CListBox::set_ColumnWidth(long val)
{
    if(val > 0)
    {
        SetColumnWidth(val);
        columnWidth=val;
        SetModified();
    }
}

long CListBox::get_ColumnWidth()
{
    return columnWidth;
}

void CListBox::set_Strings(CString val)
{
    Reset();
    FillStringsArray(val);
    for(int i=0; i < strings.GetSize();i++)
        AddString(strings[i]);
    SetModified();
}

CString CListBox::get_Strings()
{
    CString ret;
    for(int i=0; i < strings.GetSize();i++)
    {
        ret+=strings[i];
        ret+=_T('\n');
    }
    return ret;
}

void CListBox::Reset()
{
    strings.RemoveAll();
    ResetContent();
}

void CListBox::FillStringsArray(CString str)
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

BEGIN_LIST_PROPERTY(ListBoxStyle)
    LIST_ITEM_DECORATE(0,0,Single) 
    LIST_ITEM_DECORATE(LBS_MULTIPLESEL,LBS_MULTIPLESEL,Multiple)
    LIST_ITEM_DECORATE(LBS_EXTENDEDSEL,LBS_EXTENDEDSEL,Extended)
    LIST_ITEM_DECORATE(LBS_NOSEL,LBS_NOSEL,NoSel)
END_LIST_ITEM(ListBoxStyle)

static void RegisterListBoxStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;

    RegisterConversion(_T("Strings"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
    RegisterEdit(_T("Strings"),NULL,StringsEdit);
    RegisterDrawProperty(_T("Strings"),NULL);

    REGISTER_LIST_PROPERTY(ListBoxStyle)

    IsInited=TRUE;
}