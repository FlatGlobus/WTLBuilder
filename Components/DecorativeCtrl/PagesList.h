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
#include "CtrlComponent.h"
#include "Panel.h"

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
		
		DecorativeCtrl::CPanelHostComp * panelHost=(DecorativeCtrl::CPanelHostComp *)prop->Self();

		int itemcount=panelHost->GetCount()+1;
		int m_nNumLines = min(itemcount,5);

		int nHeight = rect.Height();
		rect.bottom = rect.bottom + m_nNumLines*nHeight;

		CString val=*((CString *)prop->GetValue(true));		

		for (int i = 0; i < panelHost->GetCount(); i++) 
		{
			int idx=AddString(((DecorativeCtrl::CPanelComp*)panelHost->GetAt(i))->get_Name());
			SetItemDataPtr(idx,panelHost->GetAt(i));
		}
		SetItemHeight(-1,nHeight);
		MoveWindow(rect);

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

	static HWND CreateInplaceEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint&,LPARAM)
	{
		CPagesListEdit * temp= new CPagesListEdit(prop);
		return temp->Create(Parent,Rect);
	}	

};
////////////////////////////////////////////////////////////////////////////////////////////
#endif