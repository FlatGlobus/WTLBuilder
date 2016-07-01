//////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
//{{WTLBUILDER_INCLUDE_DECLARATION
#include "Panel.h"
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_CFORMTYPE_PANEL0	1000
#define	IDC_CFORMTYPE_PANEL1	1001
#define	IDC_CFORMTYPE_PANEL8	1008
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CDialogTemplate:public CDialogImpl<CDialogTemplate>
//{{WTLBUILDER_BASE_CLASS
//}}WTLBUILDER_BASE_CLASS
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel0;
	Panel::CPanel	m_panel1;
	Panel::CPanel	m_panel8;
	CButton	m_button9;
	CButton	m_button10;
//}}WTLBUILDER_MEMBER_DECLARATION
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CDialogTemplate)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	CDialogTemplate(void);
	~CDialogTemplate(void);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
