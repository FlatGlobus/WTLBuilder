// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
#include "Package\Package.h"
#include "SDK\Property\register.h"
#include "SDK\Property\Component.h"
#include "ToolPanel.h"  
#include "CToolBoxWnd.h"
#include "Project.h"
#include "ScriptHandler.h"
#include "OutputWindow.h"
#include "atldispa.h"
#include "ValueListHelper.h"

#include<LayoutMgr.h>
#include <atlscrl.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
#include "resource.h"
#include "ButtonST.h"
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_PANEL	1001
#define	IDC_PANEL1	1041
#define	IDC_TOOLTAB	1000
#define	IDC_ALIGN_LEFT	1003
#define	IDC_ALIGN_RIGHT	1004
#define	IDC_ALIGN_TOP	1005
#define	IDC_ALIGN_BOTTOM	1006
#define	IDC_CMAINFRAME_PANEL7	1007
#define	IDC_SAME_WIDTH	1008
#define	IDC_CMAINFRAME_EDIT10	1010
#define	IDC_CMAINFRAME_UPDOWNCTRL11	1011
#define	IDC_SAME_HEIGHT	1012
#define	IDC_CMAINFRAME_PANEL13	1013
#define	IDC_SAME_SIZE	1014
#define	IDC_GS_HORIZ	1015
#define	IDC_GS_VERT	1016
#define	IDC_CMAINFRAME_PANEL17	1017
#define	IDC_CENTER_HORIZ	1018
#define	IDC_CENTER_VERT	1019
#define	IDC_HORIZ_ORDER	1021
#define	IDC_VERT_ORDER	1022
#define	IDC_CMAINFRAME_PANEL28	1028
#define	IDC_TOPARENT	1029
#define	IDC_CMAINFRAME_PANEL30	1030
#define	IDC_CREATION_ORDER	1033
#define	IDC_CENTER_GROUP_HORIZ	1037
#define	IDC_CENTER_GROUP_VERT	1038
#define	IDC_SHOW_GRID	1048
#define	IDC_CMAINFRAME_STATIC49	1049
#define	IDC_XEDIT	1050
#define	IDC_CMAINFRAME_UPDOWNCTRL51	1051
#define	IDC_CMAINFRAME_STATIC52	1052
#define	IDC_YEDIT	1053
#define	IDC_CMAINFRAME_PANEL55	1055
#define	IDC_SHOW_GSGRID	1056
#define	IDC_CMAINFRAME_UPDOWNCTRL57	1057
#define	IDC_CHANGEPARENT	1058
#define	IDC_TABORDER	1059
#define	IDC_HORIZ_ORDER_RIGHT	1060
#define	IDC_VERT_ORDER_BOTTOM	1061
#define	IDC_CMAINFRAME_STATIC62	1062
#define	IDC_XCURSOR	1063
#define	IDC_STATICY	1064
#define	IDC_YCURSOR	1065
//}}WTLBUILDER_CONTROL_ID_DECLARATION


#define MIN_USER_MENU_ID 5000U
#define MAX_USER_MENU_ID 6000U
typedef CAtlMap<UINT, CString> CUserMenuMap;

//{{WTLBUILDER_WINDOW_STYLE
typedef CWinTraits<WS_OVERLAPPED|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,WS_EX_WINDOWEDGE>	CMainFrameWinTraits;
//}}WTLBUILDER_WINDOW_STYLE

class CMainFrame : public CFrameWindowImpl<CMainFrame, CWindow, CMainFrameWinTraits>,
	public CScrollImpl<CMainFrame>,
	public LayoutMgr<CMainFrame>,
	public CUpdateUI<CMainFrame>,
	public CMessageFilter,
	public CIdleHandler,
	protected Component,
	public IDispDynImpl<CMainFrame>
{
	CToolTipCtrl	m_toolTip;
	//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	Panel::CPanel	m_panel;
	Panel::CPanel	m_panel1;
	CToolTab	m_toolTab;
	CButtonST	m_buttonst3;
	CButtonST	m_buttonst4;
	CButtonST	m_buttonst5;
	CButtonST	m_buttonst6;
	Panel::CPanel	m_panel7;
	CButtonST	m_buttonst8;
	CEdit	m_edit;
	CUpDownCtrl	m_updownctrl11;
	CButtonST	m_buttonst12;
	Panel::CPanel	m_panel13;
	CButtonST	m_buttonst14;
	CButtonST	m_buttonst15;
	CButtonST	m_buttonst16;
	Panel::CPanel	m_panel17;
	CButtonST	m_buttonst18;
	CButtonST	m_buttonst19;
	CButtonST	m_buttonst21;
	CButtonST	m_buttonst22;
	CButtonST	m_new;
	CButtonST	m_open;
	CButtonST	m_buttonst26;
	CButtonST	m_saveAll;
	Panel::CPanel	m_panel28;
	CButtonST	m_buttonst29;
	Panel::CPanel	m_panel30;
	CButtonST	m_buttonst33;
	CButtonST	m_buttonst37;
	CButtonST	m_buttonst38;
	CButtonST	m_showgrid;
	CStatic	m_static49;
	CFont	m_static49Font;
	CEdit	m_xedit;
	CUpDownCtrl	m_updownctrl51;
	CStatic	m_static52;
	CFont	m_static52Font;
	CEdit	m_yedit;
	Panel::CPanel	m_panel55;
	CButtonST	m_buttonst56;
	CUpDownCtrl	m_updownctrl57;
	CButtonST	m_buttonst58;
	CButtonST	m_tabOrder;
	CButtonST	m_buttonst60;
	CButtonST	m_buttonst61;
	CStatic	m_static62;
	CFont	m_static62Font;
	CStatic	m_XCursor;
	CStatic	m_static64;
	CFont	m_static64Font;
	CStatic	m_YCursor;
//}}WTLBUILDER_MEMBER_DECLARATION

	CUserMenuMap userMenuMap;
	UINT         userMenuCount;

	CComObjectGlobal<CScriptHandler> m_ScriptHost;
	long windowHeight;
	BOOL enableUndo;
	COutputWindow outputWindow;
	CValueListHelper valueListHelper;
	void FormSavedLoaded(Component *, LPCTSTR);
	void InitLayout(void);
	virtual void DefineLayout();
	void SetGridButton(void *, BOOL);
	void SetGridWidth(void *obj, long val);
	void SetGridHeight(void *obj, long val);
	void EnableUndo(BOOL);
	void OnEditCommand(WORD wID, Component *comp, CPoint *);
	void SetActiveForm(Component *form);
	void LoadScriptFromFile(LPCSTR);
public:
	virtual void GetDialogRect(LPRECT r);
	virtual void GetOffset(LPPOINT offset);
	virtual void DoPaint(CDCHandle /*dc*/);
	static const UINT _controlsToClip[];
	typedef CFrameWindowImpl<CMainFrame, CWindow, CMainFrameWinTraits>	baseClass;

	//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
//}}WTLBUILDER_WINCLASS_DECLARATION

	//CToolTipCtrl	m_toolTip;
	//CToolTab toolTab;
	CToolBoxWnd toolBox;
	CProject	project;

	//CCommandBarCtrl m_CmdBar;
	//HWND hWndToolBar;
	//HWND hWndAlignToolBar;
	CRecentDocumentList mru;

	CMainFrame(void);
	~CMainFrame(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_EDIT_UNDO, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CUT, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_COPY, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_PASTE, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_SELECT_ALL, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_EDIT_CLEAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP_EX(CMainFrame)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<CMainFrame>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<CMainFrame>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNewForm)
		COMMAND_ID_HANDLER(ID_FILE_NEW_CONTROL, OnFileNewControl)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, OnFileSave)
		COMMAND_ID_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)
		COMMAND_ID_HANDLER(ID_FILE_SAVEALL, OnFileSaveAll)
		COMMAND_ID_HANDLER(ID_FILE_CLOSE, OnFileClose)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_FILE_SAVEAS_TEMPLATE, OnSaveAsTemplate)
		COMMAND_ID_HANDLER(ID_FILE_GENERATE_LOC_FILE, OnGenerateLocFile)
		COMMAND_ID_HANDLER(ID_OPTIONS_OPTIONS, OnOptions)
		COMMAND_ID_HANDLER(IDC_ALIGN_LEFT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_ALIGN_RIGHT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_ALIGN_TOP, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_ALIGN_BOTTOM, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_SAME_WIDTH, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_SAME_HEIGHT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_SAME_SIZE, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_GS_HORIZ, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_GS_VERT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_CENTER_HORIZ, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_CENTER_VERT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_HORIZ_ORDER, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_VERT_ORDER, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_HORIZ_ORDER_RIGHT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_VERT_ORDER_BOTTOM, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_TOPARENT, OnAlignCommand)
		//COMMAND_ID_HANDLER(IDC_TOBACKGROUND,OnAlignCommand)
		//COMMAND_ID_HANDLER(IDC_TOFOREGROUND,OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_CENTER_GROUP_HORIZ, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_CENTER_GROUP_VERT, OnAlignCommand)
		COMMAND_ID_HANDLER(IDC_CHANGEPARENT, OnAlignCommand)

		COMMAND_ID_HANDLER(ID_EDIT_UNDO, OnEdit)
		COMMAND_ID_HANDLER(ID_EDIT_CUT, OnEdit)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, OnEdit)
		COMMAND_ID_HANDLER(ID_EDIT_PASTE, OnEdit)
		COMMAND_ID_HANDLER(ID_EDIT_SELECT_ALL, OnEdit)
		COMMAND_ID_HANDLER(ID_EDIT_CLEAR, OnEdit)

		COMMAND_ID_HANDLER(ID_VIEW_PROPERTY, OnView)
		COMMAND_ID_HANDLER(ID_VIEW_OUTPUT, OnView)

		COMMAND_ID_HANDLER(IDC_SHOW_GRID, OnShowGrid)
		COMMAND_ID_HANDLER(IDC_TABORDER, OnTabOrder)
		COMMAND_ID_HANDLER(ID_CTRL_BUILDER, OnCtrlBuilder)
		COMMAND_RANGE_HANDLER(ID_FILE_MRU_FIRST, ID_FILE_MRU_LAST, OnFileRecent)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_INITMENUPOPUP, OnMenuSelect)
		MESSAGE_HANDLER(WM_MENUSELECT, OnMenuSelect)
		MESSAGE_HANDLER(WM_MENUSELECT, OnMenuSelect)
		MESSAGE_HANDLER(WM_SELCHANGE, OnSelectComponent)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		MESSAGE_HANDLER(WM_WININICHANGE, OnWinIniChange)
		COMMAND_HANDLER(IDC_XEDIT, EN_CHANGE, OnXEditChange)
		COMMAND_HANDLER(IDC_YEDIT, EN_CHANGE, OnYEditChange)
		//for user menu
		COMMAND_RANGE_HANDLER(MIN_USER_MENU_ID, MAX_USER_MENU_ID, OnUserMenu)
		//
		REFLECT_NOTIFICATIONS_EX()
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(baseClass)
		END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNewForm(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNewControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCommonCommand(WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnMenuSelect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	LRESULT OnFileSaveAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	LRESULT OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	LRESULT OnFileClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	//LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSaveAsTemplate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	LRESULT OnGenerateLocFile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled);
	LRESULT OnAlignCommand(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnWinIniChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnFileRecent(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnView(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnShowGrid(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnXEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnYEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTabOrder(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCtrlBuilder(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUserMenu(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void AddMenu(const CMenuHandle * pMenuAdd, bool bTopLevel);
	void FillToolPanel(LPCTSTR _name, LPCTSTR _page, HBITMAP _bitmap, int type);
	LRESULT OnSelectComponent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void ResetSelectedComponent(void);
	virtual HANDLE GetHandle(void);
	long CalcWindowSize();
	void LoadFormFromFile(LPCSTR);
	void XYCursor(CPoint);
	////////////////////////////////
	BEGIN_DISPATCH_MAP(CMainFrame)
		DISP_METHOD(InsertPopupItem, VT_EMPTY, 2, VTS_BSTR VTS_BSTR)
		DISP_METHOD(AppendItem, VT_EMPTY, 3, VTS_BSTR VTS_BSTR VTS_BSTR)
	END_DISPATCH_MAP()

	void __stdcall InsertPopupItem(BSTR after, BSTR popitem);
	void __stdcall AppendItem(BSTR popup, BSTR item, BSTR scriptName);
};
