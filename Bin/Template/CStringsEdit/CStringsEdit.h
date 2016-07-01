#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

#undef __WTLBUILDER__
#include "editlistbox.h"

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_STRINGS_LIST	1015
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CStringsEdit:public CDialogImpl<CStringsEdit>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CButton	m_ok;
	CButton	m_cancel;
	CEditListBox	m_stringsList;
//}}WTLBUILDER_MEMBER_DECLARATION
	PropertyBase * prop;
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP(CStringsEdit)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	CStringsEdit(PropertyBase *);	

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
void StringsEdit(HWND parent,PropertyBase *prop);
//////////////////////////////////////////////////////////////////////////
