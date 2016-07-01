// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PAGESLISTEDIT_H
#define __PAGESLISTEDIT_H
////////////////////////////////////////////////////////////////////////////////////////////
#include "Component.h"
#include "TabCtrl.h"

typedef CWinTraits<WS_BORDER|WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_NOTIFY|LBS_HASSTRINGS,0> PagesListEditTraits;
class CPagesListEdit : 
	public CWindowImpl<CPagesListEdit, CListBox, PagesListEditTraits>//,
{
	bool m_fCancel;
	PropertyBase * prop;
public:
	CPagesListEdit(PropertyBase * p):m_fCancel(false),prop(p)
	{
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	BEGIN_MSG_MAP(CPagesListEdit)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		SetFont( (HFONT)::SendMessage(GetParent(), WM_GETFONT, 0, 0) );

		CRect rect;
		GetWindowRect(&rect);

		::ScreenToClient(GetParent(),&rect.TopLeft());
		::ScreenToClient(GetParent(),&rect.BottomRight());
		
		StdCtrl::CTabCtrl * tabCtrl=(StdCtrl::CTabCtrl *)prop->Self();

		CString str=tabCtrl->get_Pages();
		int idx=-1;
		while((idx=str.Find(_T("\n")))!=-1)
		{
			AddString(str.Left(idx));
			str.Delete(0,idx+1);
		}

		int itemcount=GetCount()+1;
		int m_nNumLines = min(itemcount,5);

		int nHeight = rect.Height();
		rect.bottom = rect.bottom + m_nNumLines*nHeight;

		SetItemHeight(-1,nHeight);
		MoveWindow(rect);

		CString val=*(CString *)prop->GetValue(true);

		if(SelectString(-1,val) == LB_ERR) 
			SetWindowText(val);	
		SetFocus();
		return lRes;
	}

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{

		switch( wParam )
		{
		case VK_ESCAPE:
			m_fCancel = true;
			::SetFocus(GetParent());
			break;
		case VK_RETURN:
			::SetFocus(GetParent());
			break;
			return 0;
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		UpdateProperty();
		PostMessage(WM_CLOSE);
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		::SetFocus(GetParent());
		bHandled=TRUE;
		return 0;
	}

	void UpdateProperty(void)
	{
		if( !m_fCancel )
		{
			int curr = GetCurSel();
			if(curr!=-1)
			{
				CString v;
				GetText(curr,v);
				prop->SetValue(&v, true);
			}
		}

	}

	LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return DefWindowProc(uMsg, wParam, lParam) | DLGC_WANTALLKEYS;
	}

	static HWND CreateInplaceEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint&  ,LPARAM)
	{
		CPagesListEdit * temp= new CPagesListEdit(prop);
		return temp->Create(Parent,Rect);
	}	

};
////////////////////////////////////////////////////////////////////////////////////////////
#endif