// [!output WTL_MAINDLG_FILE].h : interface of the [!output WTL_MAINDLG_CLASS] class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"
#include "LayoutMgr.h"

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION


//{{WTLBUILDER_CONTROL_ID_DECLARATION
//}}WTLBUILDER_CONTROL_ID_DECLARATION

[!if WTL_APPTYPE_DLG && !WTL_APPTYPE_DLG_MODAL]
class [!output WTL_MAINDLG_CLASS] : public [!output WTL_MAINDLG_BASE_CLASS]<[!output WTL_MAINDLG_CLASS]>, public CUpdateUI<[!output WTL_MAINDLG_CLASS]>,
		public CMessageFilter, public CIdleHandler
//{{WTLBUILDER_BASE_CLASS
//}}WTLBUILDER_BASE_CLASS
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();
	static const UINT _controlsToClip[];
public:
	enum { IDD = IDD_NULL };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP([!output WTL_MAINDLG_CLASS])
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP([!output WTL_MAINDLG_CLASS])
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	[!output WTL_MAINDLG_CLASS](void);
	~[!output WTL_MAINDLG_CLASS](void);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
};
[!endif]
[!if WTL_APPTYPE_DLG && WTL_APPTYPE_DLG_MODAL]
class [!output WTL_MAINDLG_CLASS] : public [!output WTL_MAINDLG_BASE_CLASS]<[!output WTL_MAINDLG_CLASS]>
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();
	static const UINT _controlsToClip[];
public:
	enum { IDD = IDD_NULL };

	BEGIN_MSG_MAP([!output WTL_MAINDLG_CLASS])
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
[!if WTL_COM_SERVER]
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
[!endif]
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	[!output WTL_MAINDLG_CLASS](void);
	~[!output WTL_MAINDLG_CLASS](void);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
[!if WTL_COM_SERVER]
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
[!endif]
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
[!endif]
