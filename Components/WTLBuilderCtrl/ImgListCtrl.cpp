// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "ImgListCtrl.h"
#include "..\Property\Register.h"
#include "resource.h"

namespace WTLBuilderCtrl
{
REGISTER_COMPONENT_EX(CImgListCtrl,CImgListCtrlComp,WTLBuilderCtrl,IDB_PROPERTYBOX)
//////////////////////////////////////////////////////////////////////////
CImgListCtrlComp::CImgListCtrlComp(LPTSTR _name):CImgListCtrl(16,16),ControlComponent<CImgListCtrlComp>(_name)
{
}

CImgListCtrlComp::~CImgListCtrlComp(void)
{
}
//////////////////////////////////////////////////////////////////////////
BOOL CImgListCtrlComp::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
    Create((HWND)_Parent->GetHandle(),GetBoundsRect(),0);
    //CWindowImpl<CImgListCtrl,CWindow>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),(LPCTSTR)get_Name(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
    AddImage(ATL::_U_STRINGorID(IDB_PROPERTYBOX));
    return ::IsWindow(m_hWnd);
}

void CImgListCtrlComp::InitProperty(void)
{
    ControlComponent<CImgListCtrlComp>::InitProperty();
    DEFINE_PROPERTY(ImageWidth,long,CImgListCtrlComp,16)
}

void CImgListCtrlComp::set_ImageWidth(long n)
{
    SetColWidth(n);
    SetModified();
}

long CImgListCtrlComp::get_ImageWidth()
{
    return GetColWidth();
}

}