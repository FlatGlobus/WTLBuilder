// [!output WTL_CHILD_FRAME_FILE].cpp : implementation of the [!output WTL_CHILD_FRAME_CLASS] class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

[!if WTL_USE_VIEW]
#include "[!output WTL_VIEW_FILE].h"
[!endif]
#include "[!output WTL_CHILD_FRAME_FILE].h"

const UINT [!output WTL_CHILD_FRAME_CLASS]::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};

[!output WTL_CHILD_FRAME_CLASS]::[!output WTL_CHILD_FRAME_CLASS](void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

void [!output WTL_CHILD_FRAME_CLASS]::OnFinalMessage(HWND /*hWnd*/)
{
	delete this;
}

[!if WTL_USE_VIEW]
LRESULT [!output WTL_CHILD_FRAME_CLASS]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_toolTip.Create(m_hWnd);

//{{WTLBUILDER_MEMBER_CREATION
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP

	InitLayout();
	bHandled = FALSE;
	return 1;
}

[!endif]
LRESULT [!output WTL_CHILD_FRAME_CLASS]::OnForwardMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	LPMSG pMsg = (LPMSG)lParam;
	m_toolTip.RelayEvent(pMsg);
[!if WTL_USE_VIEW]
	if(baseClass::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
[!else]
	return baseClass::PreTranslateMessage(pMsg);
[!endif]
}

LRESULT [!output WTL_CHILD_FRAME_CLASS]::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
	bHandled = FALSE;
	return 1;
}

void [!output WTL_CHILD_FRAME_CLASS]::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void [!output WTL_CHILD_FRAME_CLASS]::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

void [!output WTL_CHILD_FRAME_CLASS]::GetDialogRect(LPRECT r)
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

void [!output WTL_CHILD_FRAME_CLASS]::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void [!output WTL_CHILD_FRAME_CLASS]::DoPaint(CDCHandle /*dc*/)
{

}
