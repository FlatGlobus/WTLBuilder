// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "window.h"
#include "..\Component\Register.h"
#include "resource.h"
#include "..\Property\PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	REGISTER_COMPONENT(CWindow,StdCtl,IDB_WINDOWIMPL)

CWindow::CWindow(char * _name):ControlComponent<StdCtrl::CWindow>(_name)
{
	SetDefDim(50,14);
}

CWindow::~CWindow(void)
{
}

BOOL CWindow::CreateComponent(Component * _Parent)
{
	Parent=_Parent;
	CWindowImpl<StdCtrl::CWindow>::Create(GetComponentParent()->GetHandle(),GetBoundsRect(),NULL,get_CtrlWindowStyle(),get_CtrlWindowStyleEx());
	return ::IsWindow(m_hWnd);
}

void CWindow::InitProperty(void)
{
	ControlComponent<StdCtrl::CWindow>::InitProperty();
}
}
//////////////////////////////////////////////////////////////////////////
