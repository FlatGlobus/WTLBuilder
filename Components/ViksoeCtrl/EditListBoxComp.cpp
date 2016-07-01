// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "EditListBoxComp.h"
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
   REGISTER_COMPONENT_EX(CEditListBox,CEditListBoxComp,ViksoeCtrl,IDB_EDITLISTBOXCOM)
      
   CEditListBoxComp::CEditListBoxComp(LPTSTR _name):ControlComponent<CEditListBoxComp>(_name)
   {
      SetDefaultSize(40,60);
   }
   
   
   CEditListBoxComp::~CEditListBoxComp(void)
   {
   }
   
   BOOL CEditListBoxComp::CreateComponent(Component * _Parent)
   {
        SetComponentParent(_Parent);
        CEditListBox::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle()|EDLS_BROWSE,get_InternalWindowStyleEx());
        //_Init();
        return ::IsWindow(m_hWnd);
   }
   
   void CEditListBoxComp::InitProperty(void)
   {
      ControlComponent<CEditListBoxComp>::InitProperty();
      DEFINE_PROPERTY_2(Browse,BOOL,CEditListBoxComp,FALSE)
      DEFINE_PROPERTY_2(MoveButtons,BOOL,CEditListBoxComp,TRUE)
      DEFINE_PROPERTY(Caption,CString,CEditListBoxComp,_T(""))
   }

   void CEditListBoxComp::set_Caption(CString str)
   {
      caption.Empty();
      caption=(LPCTSTR)str;
      if(IsWindow())
      {
         SetWindowText((LPCTSTR)caption);
         Invalidate();
      }
      SetModified();
   }
   
   CString CEditListBoxComp::get_Caption(void)
   {
      if(state.GetBit(csLoading))
      {
         caption= GET_PROP_VALUE(CString, Caption)
      }
      return caption;
   }
   
};
#endif
