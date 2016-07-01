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
	SetWindowText(_T(""));

	m_ok.Create(m_hWnd,CRect(210,247,284,269),_TEXT("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_ok.SetFont((HFONT)m_formFont);

	m_cancel.Create(m_hWnd,CRect(290,247,364,269),_TEXT("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_cancel.SetFont((HFONT)m_formFont);

	m_stringsList.Create(m_hWnd,CRect(3,6,363,241),_TEXT(""),WS_CHILD|WS_VISIBLE,0,IDC_STRINGS_LIST);
	m_stringsList.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
	m_stringsList.SetFocus();
//}}WTLBUILDER_POST_CREATION

	CenterWindow(GetDesktopWindow());
	CString str=*(CString *)prop->GetValue();
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
		prop->SetValue(&str);
        SendEvent(evAddUndo,NULL);
	}

	EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
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
