//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <atlframe.h>
#include <atlctrls.h>

#include "[!FILENAME].h"
//////////////////////////////////////////////////////////////////////////
const UINT [!CLASSNAME]::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};
//////////////////////////////////////////////////////////////////////////
[!CLASSNAME]::[!CLASSNAME](void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

[!CLASSNAME]::~[!CLASSNAME](void)
{
}

BOOL [!CLASSNAME]::PreTranslateMessage(MSG* pMsg)
{
	m_toolTip.RelayEvent(pMsg);
	return baseClass::PreTranslateMessage(pMsg);
}

LRESULT [!CLASSNAME]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);

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

LRESULT [!CLASSNAME]::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
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

void [!CLASSNAME]::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void [!CLASSNAME]::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

void [!CLASSNAME]::GetDialogRect(LPRECT r)
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

void [!CLASSNAME]::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void [!CLASSNAME]::DoPaint(CDCHandle /*dc*/)
{

}
