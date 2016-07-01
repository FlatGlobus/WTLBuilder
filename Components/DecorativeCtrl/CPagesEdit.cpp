// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "Panel.h"
#include "CPagesEdit.h"
#include "_util.h"

#define MAX_PAGENAME_LEN 128
///////////////////////////////////////////////////////////////////////////////
CPagesEdit::CPagesEdit(PropertyBase *p):prop(p)
{
}

LRESULT CPagesEdit::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(476,401);
	SetWindowText(_TEXT("Pages Edit"));

	m_panel2.Create(m_hWnd,CRect(0,0,476,357),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT,IDC_CPAGEHOSTEDIT_PANEL2);
	m_panel2.SetFont((HFONT)m_formFont);
	m_panel2.SetInnerBorder(BDR_SUNKENINNER);
	m_panel2.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel2.SetEdgeType(BF_BOTTOM);
	m_panel2.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel2.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel2.SetHorizTextAlign(DT_LEFT);
	m_panel2.SetVertTextAlign(DT_TOP);
	m_panel2.SetSingleLine(true);
	m_panel2.SetCaption(_TEXT(""));

	m_static12.Create(m_panel2,CRect(16,11,47,25),_TEXT("Pages:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CPAGESEDIT_STATIC12);
	m_static12.SetFont((HFONT)m_formFont);

	m_panel14.Create(m_hWnd,CRect(0,357,476,401),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CPAGESEDIT_PANEL14);
	m_panel14.SetFont((HFONT)m_formFont);
	m_panel14.SetInnerBorder(BDR_RAISEDINNER);
	m_panel14.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel14.SetEdgeType(BF_RECT);
	m_panel14.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel14.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel14.SetHorizTextAlign(DT_CENTER);
	m_panel14.SetVertTextAlign(DT_VCENTER);
	m_panel14.SetSingleLine(true);
	m_panel14.SetCaption(_TEXT(""));

	m_ok.Create(m_panel14,CRect(300,13,374,35),_TEXT("&OK"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_cancel.Create(m_panel14,CRect(386,13,460,35),_TEXT("&Cancel"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_pagesedit.Create(m_panel2,CRect(16,40,460,338),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP,0,IDC_PAGESEDIT);
	m_pagesedit.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
	m_pagesedit.SetFocus();
//}}WTLBUILDER_POST_CREATION
	CenterWindow(GetDesktopWindow());
	DecorativeCtrl::CPanelHostComp * panelHost=(DecorativeCtrl::CPanelHostComp *)prop->Self();
	for(long i=0;i < panelHost->GetCount();i++)
	{
		int idx=m_pagesedit.InsertItem(-1,((DecorativeCtrl::CPanelComp*)panelHost->GetAt(i))->get_Name());
		m_pagesedit.SetItemData(idx,panelHost->GetAt(i));
	}
	m_pagesedit.SelectItem(0);
	return TRUE;
}

LRESULT CPagesEdit::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDOK)
	{
        _TCHAR buff[256];
		for(int idx=0; idx < m_pagesedit.GetItemCount();idx++)
		{
            memset(buff,0,256*sizeof(_TCHAR));
			m_pagesedit.GetItemText(idx,buff,255);
			void *item=m_pagesedit.GetItemData(idx);
            pageInfoArray.Add(CPageInfo(buff,item));
		}
        DecorativeCtrl::CPanelHostComp * panelHost=(DecorativeCtrl::CPanelHostComp *)prop->Self();
        panelHost->EndEditPages(pageInfoArray);
        SendEvent(evAddUndo,NULL);
	}
	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

LRESULT CPagesEdit::OnAcceptChanges(int, LPNMHDR _hdr, BOOL& )
{
    HWND editWindow = m_pagesedit.GetEditCtrl();
    CString text;
    if(::IsWindow(editWindow))
    {
        CEdit edit(editWindow);
        edit.GetWindowText(text);
        //название должно быть уникальным и быть идентификатором
        return m_pagesedit.FindItemExact(text)==LB_ERR? !IsIdentifier(text):TRUE;
    }
    return TRUE;
}

void PagesEdit(HWND parent,PropertyBase *prop,LPARAM)
{
	if(prop)
	{
		CPagesEdit Dlg(prop);
		Dlg.DoModal(parent);
	}
}

