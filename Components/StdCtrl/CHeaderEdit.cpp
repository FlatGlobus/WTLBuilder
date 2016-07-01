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
	m_formFont.CreateFont(8,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(369,275);
	SetWindowText("");

	m_ok.Create(m_hWnd,CRect(211,246,285,268),_TEXT("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_panel.Create(m_hWnd,CRect(0,0,369,240),NULL,WS_CHILD|WS_VISIBLE,0,IDC_STRINGSEDIT_PANEL);
	m_panel.SetFont((HFONT)m_formFont);
	m_panel.SetInnerBorder(BDR_SUNKENINNER);
	m_panel.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel.SetEdgeType(BF_BOTTOM);
	m_panel.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel.SetHorizTextAlign(DT_LEFT);
	m_panel.SetVertTextAlign(DT_TOP);
	m_panel.SetSingleLine(true);
	m_panel.SetCaption(_TEXT(""));

	m_strings.Create(m_panel,CRect(3,19,198,205),NULL,WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY|LBS_SORT|LBS_NOINTEGRALHEIGHT,WS_EX_CLIENTEDGE,IDC_STRINGS);
	m_strings.SetFont((HFONT)m_formFont);
	m_strings.AddString(_TEXT("Item"));
	m_strings.SetItemHeight(0,13);

	m_static2.Create(m_panel,CRect(3,214,34,230),_TEXT("Name:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_STRINGSEDIT_STATIC2);
	m_static2.SetFont((HFONT)m_formFont);

	m_stringEdit.Create(m_panel,CRect(40,212,238,232),_TEXT(""),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_STRINGEDIT);
	m_stringEdit.SetFont((HFONT)m_formFont);

	m_add.Create(m_panel,CRect(269,212,289,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_ADD);
	m_add.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_add,_TEXT("Add new page"));
	m_addIcon=AtlLoadIcon(IDI_PLUS);
	m_add.SetIcon(m_addIcon);

	m_remove.Create(m_panel,CRect(294,212,314,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_REMOVE);
	m_remove.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_remove,_TEXT("Remove page"));
	m_removeIcon=AtlLoadIcon(IDI_MINUS);
	m_remove.SetIcon(m_removeIcon);

	m_up.Create(m_panel,CRect(319,212,339,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_UP);
	m_up.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_up,_TEXT("Move up"));
	m_upIcon=AtlLoadIcon(IDI_ARROWU);
	m_up.SetIcon(m_upIcon);

	m_down.Create(m_panel,CRect(344,212,364,232),_TEXT(""),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_DOWN);
	m_down.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_down,_TEXT("Move down"));
	m_downIcon=AtlLoadIcon(IDI_ARROWD);
	m_down.SetIcon(m_downIcon);

	m_cancel.Create(m_hWnd,CRect(290,246,364,268),_TEXT("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_static1.Create(m_panel,CRect(3,2,34,16),_TEXT("Items"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_STRINGSEDIT_STATIC1);
	m_static1.SetFont((HFONT)m_formFont);

	m_update.Create(m_panel,CRect(244,212,264,232),_TEXT("m_button13"),WS_CHILD|WS_VISIBLE|BS_ICON|BS_CENTER|BS_VCENTER,0,IDC_UPDATE);
	m_update.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_update,_TEXT("Update"));
	m_updateIcon=AtlLoadIcon(IDI_UPDATE);
	m_update.SetIcon(m_updateIcon);

	m_static14.Create(m_panel,CRect(210,22,258,36),_TEXT("Alignment"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CSTRINGSEDIT_STATIC14);
	m_static14.SetFont((HFONT)m_formFont);

	m_combobox15.Create(m_panel,CRect(264,19,363,81),NULL,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL|CBS_HASSTRINGS,0,IDC_CSTRINGSEDIT_COMBOBOX15);
	m_combobox15.SetFont((HFONT)m_formFont);
	m_combobox15.AddString(_TEXT("Left"));
	m_combobox15.AddString(_TEXT("Center"));
	m_combobox15.AddString(_TEXT("Right"));
	m_combobox15.LimitText(0);
	m_combobox15.SetItemHeight(-1,15);
	m_combobox15.SetCurSel(0);
	m_combobox15.SetItemHeight(0,13);
	m_combobox15.SetDroppedWidth(99);
	m_combobox15.SetHorizontalExtent(40);

	m_static16.Create(m_panel,CRect(210,53,246,67),_TEXT("Width"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CSTRINGSEDIT_STATIC16);
	m_static16.SetFont((HFONT)m_formFont);

	m_edit17.Create(m_panel,CRect(264,48,362,70),_TEXT(""),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_CSTRINGSEDIT_EDIT17);
	m_edit17.SetFont((HFONT)m_formFont);

	m_checkbox18.Create(m_panel,CRect(210,78,285,94),_TEXT("Sort Down"),WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_TEXT|BS_LEFT|BS_VCENTER,0,IDC_CSTRINGSEDIT_CHECKBOX18);
	m_checkbox18.SetFont((HFONT)m_formFont);

	m_checkbox19.Create(m_panel,CRect(210,104,285,120),_TEXT("Sort Up"),WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_TEXT|BS_LEFT|BS_VCENTER,0,IDC_CSTRINGSEDIT_CHECKBOX19);
	m_checkbox19.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
	CenterWindow(GetDesktopWindow());

	CString str=*(CString *)prop->GetValue();
	int idx=-1;
	while((idx=str.Find("\n"))!=-1)
	{
		m_strings.AddString(str.Left(idx));
		str.Delete(0,idx+1);
	}

	m_strings.SetCurSel(0);
	m_down.EnableWindow(m_strings.GetCount() > 1);
	m_up.EnableWindow(m_strings.GetCount() > 1);
	m_remove.EnableWindow(m_strings.GetCount() > 1);
	
	m_strings.GetText(0,str);
	m_stringEdit.SetWindowText(str);

	return TRUE;
}

LRESULT CStringsEdit::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDOK)
	{
		CString str;
		for(int idx=0; idx < m_strings.GetCount();idx++)
		{
			CString item;
			m_strings.GetText(idx,item);
			str+=item;
			str+='\n';
		}
		prop->SetValue(&str);
	}

	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
	if(m_addIcon!=NULL)
		::DeleteObject(m_addIcon);
	if(m_removeIcon!=NULL)
		::DeleteObject(m_removeIcon);
	if(m_upIcon!=NULL)
		::DeleteObject(m_upIcon);
	if(m_downIcon!=NULL)
		::DeleteObject(m_downIcon);
	if(m_updateIcon!=NULL)
		::DeleteObject(m_updateIcon);
//}}WTLBUILDER_MEMBER_DESTRUCTION
	return 0;
}

LRESULT CStringsEdit::OnRemove(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_strings.GetCurSel();
	if(idx!=LB_ERR)
	{
		m_strings.DeleteString(idx);
		int count=m_strings.GetCount();
		if(idx >= count)
			idx=count-1;
		m_strings.SetCurSel(idx);
		BOOL bHandled;
		OnSelChange(0,0,0,bHandled);
	}

	m_down.EnableWindow(m_strings.GetCount() > 1);
	m_up.EnableWindow(m_strings.GetCount() > 1);
	m_remove.EnableWindow(m_strings.GetCount() > 1);

	return 0;
}

LRESULT CStringsEdit::OnAdd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_stringEdit.GetWindowTextLength())
	{
		CString str;
		int len=m_stringEdit.LineLength(0);
		m_stringEdit.GetLine(0,str.GetBuffer(len),len);
		str.ReleaseBuffer(len);
		if(m_strings.FindStringExact(0,str)==LB_ERR)
		{
			int idx=m_strings.GetCurSel();
			if(idx==LB_ERR)
				idx=m_strings.GetCount();
			else
				idx+=1;
			idx=m_strings.InsertString(idx,str);
			m_strings.SetCurSel(idx);
		}
	}

	m_down.EnableWindow(m_strings.GetCount() > 1);
	m_up.EnableWindow(m_strings.GetCount() > 1);
	m_remove.EnableWindow(m_strings.GetCount() > 1);

	return 0;
}

LRESULT CStringsEdit::OnUp(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_strings.GetCurSel();
	if(idx!=LB_ERR && idx!=0)
	{
		CString str;
		m_strings.GetText(idx,str);
		m_strings.DeleteString(idx);
		idx-=1;
		idx=m_strings.InsertString(idx,str);
		m_strings.SetCurSel(idx);
	}
	return 0;
}

LRESULT CStringsEdit::OnDown(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_strings.GetCurSel();
	if(idx!=LB_ERR && idx<m_strings.GetCount()-1)
	{
		CString str;
		m_strings.GetText(idx,str);
		m_strings.DeleteString(idx);
		idx+=1;
		idx=m_strings.InsertString(idx,str);
		m_strings.SetCurSel(idx);
	}
	return 0;
}

LRESULT CStringsEdit::OnUpdate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_strings.GetCurSel();
	if(idx!=LB_ERR)
	{
		CString str;
		int len=m_stringEdit.LineLength(0);
		if(len!=0)
		{
			m_stringEdit.GetLine(0,str.GetBuffer(len),len);
			str.ReleaseBuffer(len);
			if(m_strings.FindStringExact(0,str)==LB_ERR)
			{
				m_strings.DeleteString(idx);
				idx=m_strings.InsertString(idx,str);
				m_strings.SetCurSel(idx);
			}
		}
	}
	return 0;
}

LRESULT CStringsEdit::OnSelChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_strings.GetCurSel();
	if(idx!=LB_ERR)
	{
		CString str;
		m_strings.GetText(idx,str);
		m_stringEdit.SetWindowText(str);
	}

	return 0;
}

LRESULT CStringsEdit::OnEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_update.EnableWindow(m_strings.GetCurSel()!=LB_ERR && m_stringEdit.LineLength(0)!=0);

	CString pageName;
	int len=m_stringEdit.LineLength(0);
	m_stringEdit.GetLine(0,pageName.GetBuffer(len),len);
	pageName.ReleaseBuffer(len);

	if(m_strings.FindStringExact(0,pageName)==LB_ERR)
		m_add.EnableWindow(m_strings.GetCurSel()!=LB_ERR && m_stringEdit.LineLength(0)!=0);
	else
		m_add.EnableWindow(FALSE);

	return 0;
}

void StringsEdit(HWND parent,PropertyBase *prop)
{
	if(prop)
	{
		CStringsEdit Dlg(prop);
		Dlg.DoModal(parent);
	}
}
