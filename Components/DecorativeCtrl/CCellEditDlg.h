// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "LayoutMgr.h"

//{{WTLBUILDER_INCLUDE_DECLARATION
#include "Panel.h"
#include "GridCtrl.h"
//}}WTLBUILDER_INCLUDE_DECLARATION


//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_CCELLEDITDLG_PANEL1	1001
#define	IDC_CCELLEDITDLG_GRIDCTRL2	1002
#define	IDAPPLY	1005
#define	IDC_CCELLEDITDLG_GROUPBOX9	1009
#define	IDC_CCELLEDITDLG_STATIC10	1010
#define	IDC_CCELLEDITDLG_EDIT11	1011
#define	IDC_CCELLEDITDLG_STATIC12	1012
#define	IDC_CCELLEDITDLG_COMBOBOX13	1013
#define	IDC_ADD	1014
#define	IDC_DELETE	1015
#define	IDC_UP	1016
#define	IDC_DOWN	1017
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CCellEditDlg:public CResizableDialogImpl<CCellEditDlg>,public CGridCtrl::CListener
{
    PropertyBase * prop;
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel1;
	CGridCtrl	m_grid;
	CFont	m_gridHeaderFont;
	CFont	m_gridCellFont;
	CButton	m_ok;
	CButton	m_cancel;
	CButton	m_apply;
	CButton	m_groupbox9;
	CStatic	m_static10;
	CEdit	m_edit11;
	CStatic	m_static12;
	CComboBox	m_combobox13;
	CButton	m_add;
	CButton	m_button15;
	CButton	m_button16;
	CButton	m_button17;
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
public:
	virtual void DefineLayout();
	enum { IDD = IDD_NULL };
	static const UINT _controlsToClip[];

	typedef CResizableDialogImpl<CCellEditDlg> thisClass;

	BEGIN_MSG_MAP(CCellEditDlg)
		CHAIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        COMMAND_ID_HANDLER(IDC_ADD, OnAdd)
        COMMAND_ID_HANDLER(IDC_DELETE, OnDelete)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	CCellEditDlg(PropertyBase *);
	~CCellEditDlg(void);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnAdd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnDelete(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    virtual void OnRowActivate(UINT uID,long nRow);
};
//////////////////////////////////////////////////////////////////////////
