#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

#undef __WTLBUILDER__
#include <panel.h>

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_CPAGEHOSTEDIT_PANEL2	1002
#define	IDC_PAGELIST	1003
#define	IDC_CPAGEHOSTEDIT_STATIC5	1005
#define	IDC_PAGENAME	1006
#define	IDC_ADD	1007
#define	IDC_REMOVE	1008
#define	IDC_UP	1009
#define	IDC_DOWN	1010
#define	IDC_CPAGESEDIT_STATIC12	1012
#define	IDC_UPDATE	1013
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CPagesEdit:public CDialogImpl<CPagesEdit>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CButton	m_ok;
	CPanel	m_panel2;
	CListBox	m_pagelist;
	CStatic	m_static5;
	CEdit	m_pagename;
	CButton	m_add;
	HICON	m_addIcon;
	CButton	m_remove;
	HICON	m_removeIcon;
	CButton	m_up;
	HICON	m_upIcon;
	CButton	m_down;
	HICON	m_downIcon;
	CButton	m_cancel;
	CStatic	m_static12;
	CButton	m_update;
	HICON	m_updateIcon;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase * prop;
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CPagesEdit)
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
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	CPagesEdit(PropertyBase *);	

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
//////////////////////////////////////////////////////////////////////////
