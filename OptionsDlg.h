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
#include "Panel.h"
//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_OPTIONSDLG_PANEL	1001
#define	IDC_OPTIONSDLG_OPTIONSTREE	1002
#define	IDC_OPTIONSDLG_PANELHOST	1005
#define	IDC_COPTIONSDLG_PANEL6	1006
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class COptionsDlg:public CResizableDialogImpl<COptionsDlg>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel;
	CTreeViewCtrl	m_optionsTree;
	CButton	m_ok;
	CButton	m_cancel;
	Panel::CPanelHost	m_pages;
	Panel::CPanel	m_panel6;
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
public:
	virtual void DefineLayout();
	enum { IDD = IDD_NULL };
	static const UINT _controlsToClip[];

	typedef CResizableDialogImpl<COptionsDlg> thisClass;

	BEGIN_MSG_MAP(COptionsDlg)
		CHAIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		NOTIFY_HANDLER(IDC_OPTIONSDLG_OPTIONSTREE,TVN_SELCHANGED, OnSelchangedOptionsTree)
		NOTIFY_HANDLER(IDC_OPTIONSDLG_OPTIONSTREE,TVN_SELCHANGING, OnSelchangingOptionsTree)
		
	END_MSG_MAP()

	COptionsDlg();

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSelchangedOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnSelchangingOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};
//////////////////////////////////////////////////////////////////////////
