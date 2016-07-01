// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __WINXPBUTTON_H
#define __WINXPBUTTON_H


#ifdef __WTLBUILDER__

namespace ViksoeCtrl
{
   class CWinXPButtonComp:public CWinXPButton,public ControlComponent<CWinXPButtonComp>
   {
   public:
      CWinXPButtonComp(char * _name);
      ~CWinXPButtonComp(void);
   
      BEGIN_MSG_MAP(CWinXPButtonComp)
         CHAIN_MSG_MAP(ControlComponent<CWinXPButtonComp>)
         CHAIN_MSG_MAP(CWinXPButton)
      END_MSG_MAP()
      
      BOOL CreateComponent(Component * _Parent);
      void InitProperty(void);
   };
};

#endif

#endif