// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

//////////////////////////////////////////////////////////////////////////
#pragma once 

#include<LayoutMgr.h>
#include <atlscrl.h>
#include "ScriptError.h"

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_EDIT	1000
#define	IDC_CSCRIPTEDITOR_STATUSBARCTRL1	1001
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef CWinTraits<WS_OVERLAPPED|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_GROUP|WS_TABSTOP|WS_BORDER|WS_DLGFRAME|WS_THICKFRAME,WS_EX_WINDOWEDGE>	CScriptEditorWinTraits;
//}}WTLBUILDER_WINDOW_STYLE
class CScriptEditor:public CFrameWindowImpl<CScriptEditor,CWindow,CScriptEditorWinTraits>,
	public CScrollImpl<CScriptEditor>,public LayoutMgr<CScriptEditor>
{
	CToolTipCtrl	m_toolTip;
//	CBrush		m_bkColor;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CEdit	m_edit;
	CStatusBarCtrl	m_statusbarctrl1;
	CMenu	Menu2;
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();

	CScriptError *scriptError;
public:
	virtual void GetDialogRect(LPRECT r);
	virtual void GetOffset(LPPOINT offset);
	virtual void DoPaint(CDCHandle /*dc*/);
	static const UINT _controlsToClip[];
	typedef CFrameWindowImpl<CScriptEditor, CWindow, CScriptEditorWinTraits>	thisClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
//}}WTLBUILDER_WINCLASS_DECLARATION
	
	DECLARE_FRAME_WND_CLASS("WTLBUILDER_SCRIPT_EDITOR", IDR_SCRIPT_EDITOR_MENU)

	virtual BOOL PreTranslateMessage(MSG* pMsg);	

	BEGIN_MSG_MAP(CScriptEditor)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<CScriptEditor>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<CScriptEditor>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_CLOSE,OnClose)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, OnFileSave)
		COMMAND_ID_HANDLER(ID_FILE_SAVEAS, OnFileSaveAs)
		COMMAND_ID_HANDLER(ID_FILE_CLOSE, OnFileExit)
		CHAIN_MSG_MAP(thisClass)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	CScriptEditor(void);
	~CScriptEditor(void);
    BOOL Create(HWND,CScriptError *);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
