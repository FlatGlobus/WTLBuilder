// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once 

#include<LayoutMgr.h>
#include <atlscrl.h>
#include "atldispa.h"
#include "ScriptError.h"

//{{WTLBUILDER_INCLUDE_DECLARATION
#include "Panel.h"
#include "resource.h"
#include "ButtonST.h"
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_LISTVIEW	1001
#define	IDC_COUTPUTWINDOW_PANEL3	1003
#define	IDC_CLEAR_LIST	1005
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef CWinTraits<WS_OVERLAPPED|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,WS_EX_WINDOWEDGE>	COutputWindowWinTraits;
//}}WTLBUILDER_WINDOW_STYLE
class COutputWindow:public CFrameWindowImpl<COutputWindow,CWindow,COutputWindowWinTraits>,
	public CScrollImpl<COutputWindow>,public LayoutMgr<COutputWindow>,public IDispDynImpl<COutputWindow>
{
	CToolTipCtrl	m_toolTip;
//	CBrush		m_bkColor;
//{{WTLBUILDER_MEMBER_DECLARATION
	CFont	m_formFont;
	CListViewCtrl	m_listviewctrl;
	CImageList	imageList;
	Panel::CPanel	m_panel3;
	CButtonST	m_clear_list;
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();
public:
	virtual void GetDialogRect(LPRECT r);
	virtual void GetOffset(LPPOINT offset);
	virtual void DoPaint(CDCHandle /*dc*/);
	static const UINT _controlsToClip[];
	typedef CFrameWindowImpl<COutputWindow, CWindow, COutputWindowWinTraits>	thisClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_FRAME_WND_CLASS(NULL, )
//}}WTLBUILDER_WINCLASS_DECLARATION
	
	//DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg);	

	BEGIN_MSG_MAP(COutputWindow)
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<COutputWindow>::OnSize)
		//MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<COutputWindow>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
        //MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_CLOSE,OnClose)
		COMMAND_ID_HANDLER(IDC_CLEAR_LIST,OnClearList)
        NOTIFY_HANDLER(IDC_LISTVIEW,NM_DBLCLK,OnDblClick)
		CHAIN_MSG_MAP(thisClass)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    BEGIN_DISPATCH_MAP(COutputWindow)
        DISP_METHOD(Show,VT_EMPTY,0,VTS_EMPTY)
        DISP_METHOD(Hide,VT_EMPTY,0,VTS_EMPTY)
        DISP_METHOD(Clear,VT_EMPTY,0,VTS_EMPTY)
        DISP_PROPPUT(Info,VT_BSTR)
		DISP_PROPPUT(Warn,VT_BSTR)
		DISP_PROPPUT(Err,VT_BSTR)
    END_DISPATCH_MAP()

	COutputWindow(void);
	~COutputWindow(void);

    HWND Create(HWND);

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDblClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnClearList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);


    void __stdcall Show(void);
    void __stdcall Hide(void);
    void __stdcall Clear(void);
    void __stdcall put_Info(BSTR);
	void __stdcall put_Warn(BSTR);
	void __stdcall put_Err(BSTR);
    void OutputStr(int msgType,LPCTSTR msg);
    void OutputScriptError(CScriptError *);
	void ClearList();
};
//////////////////////////////////////////////////////////////////////////
