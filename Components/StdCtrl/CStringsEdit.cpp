// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "Panel.h"
#include "CStringsEdit.h"
///////////////////////////////////////////////////////////////////////////////
CStringsEdit::CStringsEdit(PropertyBase *p):prop(p)
{

}

LRESULT CStringsEdit::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(476,401);
	SetWindowText(_TEXT("ListBox items edit"));

	m_panel17.Create(m_hWnd,CRect(0,0,476,357),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CSTRINGSEDIT_PANEL17);
	m_panel17.SetFont((HFONT)m_formFont);
	m_panel17.SetInnerBorder(0);
	m_panel17.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel17.SetEdgeType(BF_RECT);
	m_panel17.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel17.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel17.SetHorizTextAlign(DT_CENTER);
	m_panel17.SetVertTextAlign(DT_VCENTER);
	m_panel17.SetSingleLine(true);
	m_panel17.SetCaption(_TEXT(""));

	m_stringsList.Create(m_panel17,CRect(16,40,460,338),_TEXT(""),WS_CHILD|WS_VISIBLE,0,IDC_STRINGS_LIST);
	m_stringsList.SetFont((HFONT)m_formFont);

	m_panel18.Create(m_hWnd,CRect(0,358,476,401),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CSTRINGSEDIT_PANEL18);
	m_panel18.SetFont((HFONT)m_formFont);
	m_panel18.SetInnerBorder(BDR_RAISEDINNER);
	m_panel18.SetOuterBorder(0);
	m_panel18.SetEdgeType(BF_RECT);
	m_panel18.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel18.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel18.SetHorizTextAlign(DT_CENTER);
	m_panel18.SetVertTextAlign(DT_VCENTER);
	m_panel18.SetSingleLine(true);
	m_panel18.SetCaption(_TEXT(""));

	m_ok.Create(m_panel18,CRect(300,13,374,35),_TEXT("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_cancel.Create(m_panel18,CRect(386,13,460,35),_TEXT("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_static19.Create(m_panel17,CRect(16,11,82,25),_TEXT("ListBox items:"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_LEFT,0,IDC_CSTRINGSEDIT_STATIC19);
	m_static19.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
	m_stringsList.SetFocus();
//}}WTLBUILDER_POST_CREATION

	CenterWindow(GetDesktopWindow());
	CString str=*(CString *)prop->GetValue(true);
	int idx=-1;
	while((idx=str.Find(_T("\n")))!=-1)
	{
        m_stringsList.InsertItem(-1,str.Left(idx));
		str.Delete(0,idx+1);
	}
    //m_stringsList.SetMaxText(255);
	m_stringsList.SelectItem(0);
	return TRUE;
}

LRESULT CStringsEdit::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDOK)
	{
		CString str;
        _TCHAR buff[256];
		for(int idx=0; idx < m_stringsList.GetItemCount();idx++)
		{
            memset(buff,0,256);
			m_stringsList.GetItemText(idx,buff,255);
			str+=buff;
			str+=_T('\n');
		}
		prop->SetValue(&str, true);
        SendEvent(evAddUndo,NULL);
	}

	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

void StringsEdit(HWND parent,PropertyBase *prop,LPARAM  )
{
	if(prop)
	{
		CStringsEdit Dlg(prop);
		Dlg.DoModal(parent);
	}
}
