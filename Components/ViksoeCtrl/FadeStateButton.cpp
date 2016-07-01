// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "imagehelpers.h"
#include "FadeStateButton.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
   REGISTER_COMPONENT_EX(CFadeStateButtonCtrl,CFadeStateButtonCtrlComp,ViksoeCtrl,IDB_EDITLISTBOXCOM)
      
   CFadeStateButtonCtrlComp::CFadeStateButtonCtrlComp(LPTSTR _name):ControlComponent<CFadeStateButtonCtrlComp>(_name)
   {
      SetDefaultSize(40,60);
   }
   
   
   CFadeStateButtonCtrlComp::~CFadeStateButtonCtrlComp(void)
   {
   }
   
   BOOL CFadeStateButtonCtrlComp::CreateComponent(Component * _Parent)
   {
        SetComponentParent(_Parent);
        CFadeStateButtonCtrl::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_CtrlWindowStyle(),get_CtrlWindowStyleEx());
        HBITMAP bmp=AtlLoadBitmap(IDB_PROPERTYGRID);
        SetBitmap(bmp);
        return ::IsWindow(m_hWnd);
   }
   
   void CFadeStateButtonCtrlComp::InitProperty(void)
   {
      ControlComponent<CFadeStateButtonCtrlComp>::InitProperty();
   }
  
};
#endif
