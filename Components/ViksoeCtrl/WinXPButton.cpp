// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "imagehelpers.h"
#include "FadeStateButton.h"
#include "MiscControls.h"
#include "WinXPButton.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
   REGISTER_COMPONENT_EX(CWinXPButton,CWinXPButtonComp,ViksoeCtrl,IDB_EDITLISTBOXCOM)
      
   CWinXPButtonComp::CWinXPButtonComp(LPTSTR _name):ControlComponent<CWinXPButtonComp>(_name)
   {
      SetDefaultSize(40,60);
   }
   
   
   CWinXPButtonComp::~CWinXPButtonComp(void)
   {
   }
   
   BOOL CWinXPButtonComp::CreateComponent(Component * _Parent)
   {
        SetComponentParent(_Parent);
        CWinXPButton::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_CtrlWindowStyle(),get_CtrlWindowStyleEx());
        SetBkColor(RGB(238,243,250));
        GenerateImages(_T(""), IDB_PROPERTYGRID, TRUE);
        return ::IsWindow(m_hWnd);
   }
   
   void CWinXPButtonComp::InitProperty(void)
   {
      ControlComponent<CWinXPButtonComp>::InitProperty();
   }
  
};
#endif