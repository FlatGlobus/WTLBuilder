//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
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
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
}

BOOL [!CLASSNAME]::PreTranslateMessage(MSG* pMsg)
{
	m_toolTip.RelayEvent(pMsg);
	return thisClass::PreTranslateMessage(pMsg);
}

LRESULT [!CLASSNAME]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);

//{{WTLBUILDER_MEMBER_CREATION
//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

	InitLayout();

	return 0;
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
