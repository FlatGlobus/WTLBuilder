// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"

#undef __WTLBUILDER__

#include <panel.h>
#include <atlctrlx.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
#include "EditListBox.h"
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_CPAGEHOSTEDIT_PANEL2	1002
#define	IDC_CPAGESEDIT_STATIC12	1012
#define	IDC_CPAGESEDIT_PANEL14	1014
#define	IDC_PAGESEDIT	1017
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CPageInfo
{
public:
    CPageInfo(CString _name, void * _ptr = NULL):name(_name),ptr(_ptr){}
    CString name;
    void * ptr;
    friend int operator == (const CPageInfo pi1,const CPageInfo pi2) {return pi1.name == pi2.name;}
};

typedef CSimpleArray<CPageInfo> CPageInfoArray;

class CPagesEdit:public CDialogImpl<CPagesEdit>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel2;
	CStatic	m_static12;
	Panel::CPanel	m_panel14;
	CButton	m_ok;
	CButton	m_cancel;
	CEditListBox	m_pagesedit;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase * prop;
    CPageInfoArray pageInfoArray;
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CPagesEdit)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        NOTIFY_HANDLER(IDC_PAGESEDIT,EDLN_ITEMCHANGING,OnAcceptChanges)
	END_MSG_MAP()

	CPagesEdit(PropertyBase *);	

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnAcceptChanges(int, LPNMHDR, BOOL& );
};
#define __WTLBUILDER__
//////////////////////////////////////////////////////////////////////////
