// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "tabctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "CPagesEdit.h"
#include "PagesList.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterTabCtrlStyles();
typedef long TabCtrlStyle;
typedef CString CTabCtrlPages;
typedef CString CTabCtrlCurSel;
namespace StdCtrl
{
	REGISTER_COMPONENT(CTabCtrl,StdCtl,IDB_TABCTRL)

CTabCtrl::CTabCtrl(LPTSTR _name):ControlComponent<StdCtrl::CTabCtrl>(_name),imageList(CComponentListEdit::GetNoneStr())
	{
		SetDefaultSize(164,132);
		RegisterTabCtrlStyles();
	}

	CTabCtrl::~CTabCtrl(void)
	{
	}

	BOOL CTabCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CTabCtrl,WTL::CTabCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CTabCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CTabCtrl>::InitProperty();
				
		DEFINE_PROPERTY(Bottom,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(Buttons,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(Right,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(FlatButtons,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(FocusNever,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(FocusOnButtonDown,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(ForceIconLeft,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(ForceLabelLeft,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(HotTrack,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(MultiLine,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(MultiSelect,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(OwnerDrawFixed,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(Style,TabCtrlStyle,CTabCtrl,TCS_RIGHTJUSTIFY)
		DEFINE_PROPERTY(ScrollOpposite,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(Tabs,BOOL,CTabCtrl,FALSE)
		DEFINE_PROPERTY(Vertical,BOOL,CTabCtrl,FALSE)

		DEFINE_PROPERTY(Pages,CTabCtrlPages,CTabCtrl,_T("Page 0\n"))
		DEFINE_PROPERTY(CurSel,CTabCtrlCurSel,CTabCtrl,_T(""))
		
		DEFINE_PROPERTY(ImageList,ComponentName,CTabCtrl,_T(""))
	}

	void CTabCtrl::set_Pages(CString val)
	{
		Reset();
		FillPagesArray(val);
		BOOL hasImages = imageList!=CComponentListEdit::GetNoneStr();
		for(int i=0; i < pages.GetSize();i++)
		{
			TCITEM tab = { 0 };
			tab.mask = TCIF_TEXT | hasImages ? TCIF_IMAGE : 0;   
			tab.pszText = (LPTSTR)(LPCTSTR)pages[i];
			tab.cchTextMax = pages[i].GetLength();
			tab.iImage = hasImages ? -1 :-1;//wow!!
			InsertItem(i, &tab);
		}
	}

	CString CTabCtrl::get_Pages()
	{
		CString ret;
		for(int i=0; i < pages.GetSize();i++)
		{
			ret+=pages[i];
			ret+=_T('\n');
		}
		return ret;
	}

	void CTabCtrl::Reset()
	{
		pages.RemoveAll();
		DeleteAllItems();
	}

	void CTabCtrl::FillPagesArray(CString str)
	{
		pages.RemoveAll();
		if(str.IsEmpty())
			return;
		int idx=-1;
		while((idx=str.Find(_T("\n")))!=-1)
		{
			pages.Add(str.Left(idx));
			str.Delete(0,idx+1);
		}
	}
	
	int CTabCtrl::FindPage(CString val)
	{
		for(int i=0; i < pages.GetSize();i++)
		{
			if(val==pages[i])
				return i;
		}
		return 0;
	}

	void CTabCtrl::set_CurSel(CString val)
	{
		current=val;
		SetCurSel(FindPage(current));
	}

	CString CTabCtrl::get_CurSel()
	{
		return current;
	}

	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,Bottom,TCS_BOTTOM)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,Buttons,TCS_BUTTONS)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,Right,TCS_RIGHT)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,FlatButtons,TCS_FLATBUTTONS)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,FocusNever,TCS_FOCUSNEVER)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,FocusOnButtonDown,TCS_FOCUSONBUTTONDOWN)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,ForceIconLeft,TCS_FORCEICONLEFT)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,ForceLabelLeft,TCS_FORCELABELLEFT)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,HotTrack,TCS_HOTTRACK)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,MultiLine,TCS_MULTILINE)//TCS_SINGLELINE выставить
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,MultiSelect,TCS_MULTISELECT)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,OwnerDrawFixed,TCS_OWNERDRAWFIXED)
	IMPLEMENT_WINSTYLE_PROPERTY(CTabCtrl,Style,(TCS_RAGGEDRIGHT|TCS_FIXEDWIDTH|TCS_RIGHTJUSTIFY))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,ScrollOpposite,TCS_SCROLLOPPOSITE)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,Tabs,TCS_TABS)
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CTabCtrl,Vertical,TCS_VERTICAL)
	
	void CTabCtrl::set_ImageList(CString val)
	{
        if(imageList!=val)
        {
            if(imageList!=CComponentListEdit::GetNoneStr())
            {
                Component * oldComp=Find(imageList);
                if(oldComp)
                    oldComp->Changed.Reset();
            }

            Component * temp=Find(val);
            if(temp!=NULL && temp->GetComponetKind()==_T("IMAGELIST"))
            {
                temp->Changed.SetObject(this);
                temp->Changed.SetMethod(&CTabCtrl::ImageListChanged);
                SetImageList((HIMAGELIST)temp->GetHandle());
            }
            else
            {
                imageList=CComponentListEdit::GetNoneStr();
                SetImageList(NULL);
                return;
            }
            imageList=val;
        }
	
	}
	
    void CTabCtrl::ImageListChanged(Component* comp)
    {
        if(comp->GetState(csDeleting))
            imageList=CComponentListEdit::GetNoneStr();
        else
            imageList=comp->get_Name();
    }
	
	CString CTabCtrl::get_ImageList()
	{
		CComponentListEdit::SetComponentKind(_T("IMAGELIST"));
	    return imageList;
	}
}
//////////////////////////////////////////////////////////////////////////
BEGIN_LIST_PROPERTY(TabCtrlStyle)
LIST_ITEM_DECORATE(TCS_RIGHTJUSTIFY,TCS_RIGHTJUSTIFY,RightJustify)
LIST_ITEM_DECORATE(TCS_FIXEDWIDTH,TCS_FIXEDWIDTH,FixedWidth)
LIST_ITEM_DECORATE(TCS_RAGGEDRIGHT,TCS_RAGGEDRIGHT,RaggedRight)
END_LIST_ITEM(TabCtrlStyle)

static void RegisterTabCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(TabCtrlStyle)
	RegisterConversion(_T("CTabCtrlPages"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("CTabCtrlPages"),NULL,PagesEdit);
	RegisterDrawProperty(_T("CTabCtrlPages"),NULL);

	RegisterEdit(_T("CTabCtrlCurSel"),CPagesListEdit::CreateInplaceEdit,NULL);
	RegisterConversion(_T("CTabCtrlCurSel"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterDrawProperty(_T("CTabCtrlCurSel"),DrawPropertyValueText);

	IsInited=TRUE;
}
