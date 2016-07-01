// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "toolbarctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterToolBarCtrlStyles();
typedef long CommonCtrlAlign;
namespace StdCtrl
{
REGISTER_COMPONENT(CToolBarCtrl,StdCtl,IDB_TOOLBARCTRL)

CToolBarCtrl::CToolBarCtrl(LPTSTR _name):ControlComponent<StdCtrl::CToolBarCtrl>(_name)
{
	RegisterToolBarCtrlStyles();
	enableTabIndex=FALSE;
}

CToolBarCtrl::~CToolBarCtrl(void)
{
}

BOOL CToolBarCtrl::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
	CWindowImpl<StdCtrl::CToolBarCtrl,WTL::CToolBarCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

LRESULT CToolBarCtrl::OnParentNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch(LOWORD(wParam))
	{
	case WM_CREATE:		//HIWORD(wParam) childID
		{				//lParam HWND
			/*TBBUTTON tb;
			tb.iBitmap=I_IMAGENONE;
			tb.idCommand=HIWORD(wParam);
			tb.fsState=0;
			tb.fsStyle=TBSTYLE_SEP;
			tb.dwData=NULL;
			tb.iString=NULL;
			//HitTest()
			int index=GetButtonCount()+1;
			InsertButton(index,&tb);

			TBBUTTONINFO tbi;
			tbi.cbSize = sizeof TBBUTTONINFO;		
			tbi.dwMask = TBIF_STYLE | TBIF_SIZE;
			tbi.fsStyle = TBSTYLE_SEP;
			tbi.cx = (unsigned short)40;

			CSize sz(cx,cy);
			
			SetButtonInfo(index,&tbi); 						
			GetItemRect(0, &rc); 
			*/
		}
		break;
	case WM_DESTROY:
		break;
	};
	return 0;
}

void CToolBarCtrl::InitProperty(void)
{
	ControlComponent<StdCtrl::CToolBarCtrl>::InitProperty();
	///common styles
	DEFINE_PROPERTY(NoDivider,BOOL,CToolBarCtrl,FALSE)
	DEFINE_PROPERTY(NoMoveY,BOOL,CToolBarCtrl,FALSE)
	DEFINE_PROPERTY(NoParentAlign,BOOL,CToolBarCtrl,FALSE)
	DEFINE_PROPERTY(NoResize,BOOL,CToolBarCtrl,FALSE)
	DEFINE_PROPERTY(CtrlAlign,CommonCtrlAlign,CToolBarCtrl,CCS_TOP)
}
///common styles
IMPLEMENT_WINSTYLE_PROPERTY(CToolBarCtrl,CtrlAlign,(CCS_BOTTOM|CCS_TOP|CCS_LEFT|CCS_RIGHT))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CToolBarCtrl,NoDivider,(CCS_NODIVIDER))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CToolBarCtrl,NoMoveY,(CCS_NOMOVEY))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CToolBarCtrl,NoParentAlign,(CCS_NOPARENTALIGN))
IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CToolBarCtrl,NoResize,(CCS_NORESIZE))

}
//////////////////////////////////////////////////////////////////////////

static void RegisterToolBarCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	IsInited=TRUE;
}
