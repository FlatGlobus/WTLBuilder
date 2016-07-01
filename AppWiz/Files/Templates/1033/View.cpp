// [!output WTL_VIEW_FILE].cpp : implementation of the [!output WTL_VIEW_CLASS] class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
[!if WTL_USE_RIBBON]
#include "Ribbon.h"
[!endif]
#include "resource.h"

#include "[!output WTL_VIEW_FILE].h"

const UINT [!output WTL_VIEW_CLASS]::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

[!output WTL_VIEW_CLASS]::[!output WTL_VIEW_CLASS](void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

BOOL [!output WTL_VIEW_CLASS]::PreTranslateMessage(MSG* pMsg)
{
	if(m_toolTip.IsWindow())
		m_toolTip.RelayEvent(pMsg);
[!if WTL_HOST_AX]
	if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
	   (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
		return FALSE;

	HWND hWndCtl = ::GetFocus();
	if(IsChild(hWndCtl))
	{
		// find a direct child of the dialog from the window that has focus
		while(::GetParent(hWndCtl) != m_hWnd)
			hWndCtl = ::GetParent(hWndCtl);

		// give control a chance to translate this message
		if(::SendMessage(hWndCtl, WM_FORWARDMSG, 0, (LPARAM)pMsg) != 0)
			return TRUE;
	}

[!endif]
[!if WTL_VIEWTYPE_HTML]
	if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
	   (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
		return FALSE;

	// give HTML page a chance to translate this message
	return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
[!else]
[!if WTL_VIEWTYPE_FORM]
	return CWindow::IsDialogMessage(pMsg);
[!else]
	return FALSE;
[!endif]
[!endif]
}

LRESULT [!output WTL_VIEW_CLASS]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);

//{{WTLBUILDER_MEMBER_CREATION
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP

	InitLayout();

	return 0;
}

LRESULT [!output WTL_VIEW_CLASS]::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

	return 0;
}
[!if WTL_VIEWTYPE_GENERIC]

LRESULT [!output WTL_VIEW_CLASS]::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);

	//TODO: Add your drawing code here

	return 0;
}
[!endif]


[!if WTL_APPTYPE_TABVIEW]

void [!output WTL_VIEW_CLASS]::OnFinalMessage(HWND /*hWnd*/)
{
	delete this;
}
[!endif]

void [!output WTL_VIEW_CLASS]::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void [!output WTL_VIEW_CLASS]::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

void [!output WTL_VIEW_CLASS]::GetDialogRect(LPRECT r)
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

void [!output WTL_VIEW_CLASS]::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void [!output WTL_VIEW_CLASS]::DoPaint(CDCHandle /*dc*/)
{
}