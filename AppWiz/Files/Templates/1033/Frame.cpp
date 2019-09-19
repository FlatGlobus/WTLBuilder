// [!output WTL_FRAME_FILE].cpp : implmentation of the [!output WTL_FRAME_CLASS] class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
[!if WTL_USE_RIBBON]
#include "Ribbon.h"
[!endif]
#include "resource.h"

#include "aboutdlg.h"
[!if WTL_USE_VIEW]
#include "[!output WTL_VIEW_FILE].h"
[!endif]
[!if WTL_APPTYPE_MDI]
#include "[!output WTL_CHILD_FRAME_FILE].h"
[!endif]
#include "[!output WTL_FRAME_FILE].h"

const UINT [!output WTL_FRAME_CLASS]::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

[!output WTL_FRAME_CLASS]::[!output WTL_FRAME_CLASS](void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

BOOL [!output WTL_FRAME_CLASS]::PreTranslateMessage(MSG* pMsg)
{
	m_toolTip.RelayEvent(pMsg);
[!if WTL_APPTYPE_MDI]
	if([!output WTL_FRAME_BASE_CLASS]<[!output WTL_FRAME_CLASS]>::PreTranslateMessage(pMsg))
		return TRUE;

	HWND hWnd = MDIGetActive();
	if(hWnd != NULL)
		return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);

	return FALSE;
[!else]
[!if WTL_USE_VIEW]
	if([!output WTL_FRAME_BASE_CLASS]<[!output WTL_FRAME_CLASS]>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
[!else]
	return [!output WTL_FRAME_BASE_CLASS]<[!output WTL_FRAME_CLASS]>::PreTranslateMessage(pMsg);
[!endif]
[!endif]
}

BOOL [!output WTL_FRAME_CLASS]::OnIdle()
{
[!if WTL_USE_TOOLBAR]
	UIUpdateToolBar();
[!endif]
	return FALSE;
}

LRESULT [!output WTL_FRAME_CLASS]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
[!if WTL_RIBBON_DUAL_UI]
	bool bRibbonUI = [!output WTL_NS]RunTimeHelper::IsRibbonUIAvailable();
	if (bRibbonUI)
		UIAddMenu(GetMenu(), true);
	else
		[!output WTL_NS]CMenuHandle(GetMenu()).DeleteMenu(ID_VIEW_RIBBON, MF_BYCOMMAND);

[!else]
[!if WTL_RIBBON_SINGLE_UI]
	UIAddMenu(GetMenu(), true);
[!endif]
[!endif]
[!if WTL_USE_RIBBON && !WTL_USE_CMDBAR]
	m_CmdBar.Create(m_hWnd, rcDefault, NULL, WS_CHILD);
	m_CmdBar.AttachMenu(GetMenu());
	m_CmdBar.LoadImages(IDR_MAINFRAME);

[!endif]
[!if WTL_USE_TOOLBAR]
[!if WTL_USE_REBAR]
[!if WTL_USE_CMDBAR]
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

[!endif]
	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
[!if WTL_USE_CMDBAR]
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);
[!else]
	AddSimpleReBarBand(hWndToolBar);
[!endif]
[!else]
	CreateSimpleToolBar();
[!endif]
[!endif]
[!if WTL_USE_STATUSBAR]

	CreateSimpleStatusBar();
[!endif]
[!if WTL_APPTYPE_MDI]

	CreateMDIClient();
[!if WTL_USE_CMDBAR]
	m_CmdBar.SetMDIClient(m_hWndMDIClient);
[!endif]
[!endif]
[!if WTL_APPTYPE_SDI || WTL_APPTYPE_MTSDI ]
[!if WTL_USE_VIEW]
	m_hWndClient = m_view.Create(m_hWnd);
[!endif]
[!endif]
[!if WTL_USE_TOOLBAR]
[!if WTL_USE_REBAR]

	UIAddToolBar(hWndToolBar);
[!else]

	UIAddToolBar(m_hWndToolBar);
[!endif]
	UISetCheck(ID_VIEW_TOOLBAR, 1);
[!endif]
[!if WTL_USE_STATUSBAR]
	UISetCheck(ID_VIEW_STATUS_BAR, 1);
[!endif]

//{{WTLBUILDER_MEMBER_CREATION
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP

	// register object for message filtering and idle updates
	[!output WTL_NS]CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

[!if WTL_USE_RIBBON]
[!if WTL_RIBBON_SINGLE_UI]
		ShowRibbonUI(true);

[!else]
		ShowRibbonUI(bRibbonUI);
		UISetCheck(ID_VIEW_RIBBON, bRibbonUI);

[!endif]
[!endif]
	InitLayout();
	return 0;
}

[!if WTL_COM_SERVER]
LRESULT [!output WTL_FRAME_CLASS]::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

[!if WTL_APPTYPE_MDI]
[!if WTL_USE_CMDBAR]
		m_CmdBar.AttachMenu(NULL);

[!endif]
[!endif]
	// unregister message filtering and idle updates
	[!output WTL_NS]CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	// if UI is the last thread, no need to wait
	if(_Module.GetLockCount() == 1)
	{
		_Module.m_dwTimeOut = 0L;
		_Module.m_dwPause = 0L;
	}
	_Module.Unlock();

[!if WTL_APPTYPE_MTSDI]
	::PostQuitMessage(1);

[!endif]
	return 0;
}

[!else]
LRESULT [!output WTL_FRAME_CLASS]::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

[!if WTL_APPTYPE_MDI]
[!if WTL_USE_CMDBAR]
		m_CmdBar.AttachMenu(NULL);

[!endif]
[!endif]
	// unregister message filtering and idle updates
	[!output WTL_NS]CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

[!endif]
LRESULT [!output WTL_FRAME_CLASS]::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT [!output WTL_FRAME_CLASS]::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
[!if WTL_APPTYPE_MDI]
	[!output WTL_CHILD_FRAME_CLASS]* pChild = new [!output WTL_CHILD_FRAME_CLASS];
	pChild->CreateEx(m_hWndClient);

[!endif]
	// TODO: add code to initialize document

	return 0;
}

[!if WTL_APPTYPE_MTSDI]
LRESULT [!output WTL_FRAME_CLASS]::OnFileNewWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	::PostThreadMessage(_Module.m_dwMainThreadID, WM_USER, 0, 0L);
	return 0;
}

[!endif]
[!if WTL_USE_TOOLBAR]
LRESULT [!output WTL_FRAME_CLASS]::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
[!if WTL_USE_REBAR]
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	[!output WTL_NS]CReBarCtrl rebar = m_hWndToolBar;
[!if WTL_USE_CMDBAR]
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
[!else]
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST);	// toolbar is first 1st band
[!endif]
	rebar.ShowBand(nBandIndex, bVisible);
[!else]
	BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
	::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
[!endif]
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

[!endif]
[!if WTL_USE_STATUSBAR]
LRESULT [!output WTL_FRAME_CLASS]::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

[!endif]
[!if WTL_RIBBON_DUAL_UI]
LRESULT [!output WTL_FRAME_CLASS]::OnViewRibbon(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowRibbonUI(!IsRibbonUI());
	UISetCheck(ID_VIEW_RIBBON, IsRibbonUI());
[!if !WTL_USE_CMDBAR]
	if (!IsRibbonUI())
		SetMenu([!output WTL_NS]AtlLoadMenu(IDR_MAINFRAME));
[!endif]
	return 0;
}

[!endif]
LRESULT [!output WTL_FRAME_CLASS]::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}
[!if WTL_APPTYPE_MDI]

LRESULT [!output WTL_FRAME_CLASS]::OnWindowCascade(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MDICascade();
	return 0;
}

LRESULT [!output WTL_FRAME_CLASS]::OnWindowTile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MDITile();
	return 0;
}

LRESULT [!output WTL_FRAME_CLASS]::OnWindowArrangeIcons(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MDIIconArrange();
	return 0;
}
[!endif]

void [!output WTL_FRAME_CLASS]::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void [!output WTL_FRAME_CLASS]::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

void [!output WTL_FRAME_CLASS]::GetDialogRect(LPRECT r)
{
	GetClientRect(r);	
	if (r->right < m_sizeAll.cx)
	{
		r->right = m_sizeAll.cx;
	}
	if (r->bottom < m_sizeAll.cy)
	{
		r->bottom = m_sizeAll.cy;
	}
}

void [!output WTL_FRAME_CLASS]::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void [!output WTL_FRAME_CLASS]::DoPaint([!output WTL_NS]CDCHandle /*dc*/)
{
}