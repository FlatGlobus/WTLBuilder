// [!output WTL_FRAME_FILE].cpp : implmentation of the [!output WTL_FRAME_CLASS] class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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
	if(_baseClass::PreTranslateMessage(pMsg))
		return TRUE;

	HWND hWnd = MDIGetActive();
	if(hWnd != NULL)
		return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);

	return FALSE;
[!else]
[!if WTL_USE_VIEW]
	if(_baseClass::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
[!else]
	return _baseClass::PreTranslateMessage(pMsg);
[!endif]
[!endif]
}

BOOL [!output WTL_FRAME_CLASS]::OnIdle()
{
	return FALSE;
}

LRESULT [!output WTL_FRAME_CLASS]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
[!if WTL_APPTYPE_MDI]

	CreateMDIClient();
[!endif]

//{{WTLBUILDER_MEMBER_CREATION
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	InitLayout();
	return 0;
}

[!if WTL_COM_SERVER]
LRESULT [!output WTL_FRAME_CLASS]::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

[!if WTL_APPTYPE_MDI]
[!endif]
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
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

	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
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

void [!output WTL_FRAME_CLASS]::DoPaint(CDCHandle /*dc*/)
{

}
