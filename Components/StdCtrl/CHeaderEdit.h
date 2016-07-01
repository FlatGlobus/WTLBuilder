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

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_STRINGSEDIT_PANEL	1002
#define	IDC_STRINGS	1003
#define	IDC_STRINGSEDIT_STATIC2	1005
#define	IDC_STRINGEDIT	1006
#define	IDC_ADD	1007
#define	IDC_REMOVE	1008
#define	IDC_UP	1009
#define	IDC_DOWN	1010
#define	IDC_STRINGSEDIT_STATIC1	1012
#define	IDC_UPDATE	1013
#define	IDC_CSTRINGSEDIT_STATIC14	1014
#define	IDC_CSTRINGSEDIT_COMBOBOX15	1015
#define	IDC_CSTRINGSEDIT_STATIC16	1016
#define	IDC_CSTRINGSEDIT_EDIT17	1017
#define	IDC_CSTRINGSEDIT_CHECKBOX18	1018
#define	IDC_CSTRINGSEDIT_CHECKBOX19	1019
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CStringsEdit:public CDialogImpl<CStringsEdit>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CButton	m_ok;
	Panel::CPanel	m_panel;
	CListBox	m_strings;
	CStatic	m_static2;
	CEdit	m_stringEdit;
	CButton	m_add;
	HICON	m_addIcon;
	CButton	m_remove;
	HICON	m_removeIcon;
	CButton	m_up;
	HICON	m_upIcon;
	CButton	m_down;
	HICON	m_downIcon;
	CButton	m_cancel;
	CStatic	m_static1;
	CButton	m_update;
	HICON	m_updateIcon;
	CStatic	m_static14;
	CComboBox	m_combobox15;
	CStatic	m_static16;
	CEdit	m_edit17;
	CButton	m_checkbox18;
	CButton	m_checkbox19;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase * prop;
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CStringsEdit)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_REMOVE,OnRemove)
		COMMAND_ID_HANDLER(IDC_ADD,OnAdd)
		COMMAND_ID_HANDLER(IDC_UP,OnUp)
		COMMAND_ID_HANDLER(IDC_DOWN,OnDown)
		COMMAND_ID_HANDLER(IDC_UPDATE,OnUpdate)
		COMMAND_CODE_HANDLER(LBN_SELCHANGE,OnSelChange)
		COMMAND_CODE_HANDLER(EN_UPDATE,OnEditChange)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	CStringsEdit(PropertyBase *);	

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnRemove(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAdd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUp(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDown(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUpdate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSelChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
void StringsEdit(HWND parent,PropertyBase *prop,LPARAM);
//////////////////////////////////////////////////////////////////////////
