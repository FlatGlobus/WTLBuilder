// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "TabCtrl.h"
#include "CPagesEdit.h"
///////////////////////////////////////////////////////////////////////////////
CPagesEdit::CPagesEdit(PropertyBase *p):prop(p)
{

}

LRESULT CPagesEdit::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(368,271);
	SetWindowText(_T(""));

	m_ok.Create(m_hWnd,CRect(208,240,282,262),_TEXT("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_cancel.Create(m_hWnd,CRect(288,240,362,262),_TEXT("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_pagesList.Create(m_hWnd,CRect(7,6,362,231),_TEXT(""),WS_CHILD|WS_VISIBLE,0,IDC_PAGES_LIST);
	m_pagesList.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
	CenterWindow(GetDesktopWindow());
	CString str=*(CString *)prop->GetValue(true);
	int idx=-1;
	while((idx=str.Find(_T("\n")))!=-1)
	{
		m_pagesList.InsertItem(-1,str.Left(idx));
		str.Delete(0,idx+1);
	}
	return TRUE;
}

LRESULT CPagesEdit::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==IDOK)
	{
        CString str;
        _TCHAR buff[256];
        for(int idx=0; idx < m_pagesList.GetItemCount();idx++)
        {
            memset(buff,0,256);
            m_pagesList.GetItemText(idx,buff,255);
            str+=buff;
            str+=_T('\n');
        }
		prop->SetValue(&str, true);
        SendEvent(evAddUndo,NULL);
	}
	EndDialog(wID);
	return 0;
}

//LRESULT CPagesEdit::OnAdd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
/*{
	if(m_pagename.GetWindowTextLength())
	{
		CString pageName;
		int len=m_pagename.LineLength(0);
		m_pagename.GetLine(0,pageName.GetBuffer(len),len);
		pageName.ReleaseBuffer(len);
		if(m_pagelist.FindStringExact(0,pageName)==LB_ERR)
		{
			int idx=m_pagelist.GetCurSel();
			if(idx==LB_ERR)
				idx=m_pagelist.GetCount();
			else
				idx+=1;
			idx=m_pagelist.InsertString(idx,pageName);
			m_pagelist.SetCurSel(idx);
		}
	}
	return 0;
}
*/

void PagesEdit(HWND parent,PropertyBase *prop,LPARAM)
{
	if(prop)
	{
		CPagesEdit Dlg(prop);
		if(Dlg.DoModal(parent)==IDOK)
		{
		}
	}
}
