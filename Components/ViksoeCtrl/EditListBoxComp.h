// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#if !defined(__EDITLISTBOXCOMP_H_)
#define __EDITLISTBOXCOMP_H_

#ifdef __WTLBUILDER__

#include "EditListBox.h"

namespace ViksoeCtrl
{
   class CEditListBoxComp:public CEditListBox,public ControlComponent<CEditListBoxComp>
   {
      CString caption;
   public:
      CEditListBoxComp(char * _name);
      ~CEditListBoxComp(void);
   
      BEGIN_MSG_MAP(CEditListBoxComp)
         CHAIN_MSG_MAP(ControlComponent<CEditListBoxComp>)
         CHAIN_MSG_MAP(CEditListBox)
      END_MSG_MAP()
      
      BOOL CreateComponent(Component * _Parent);
      void InitProperty(void);
      DECLARE_PROPERTY(Caption,CString)
   };
};

#endif

#endif // !defined(__EDITLISTBOX_H_)
