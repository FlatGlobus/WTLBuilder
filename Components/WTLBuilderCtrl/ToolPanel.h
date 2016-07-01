// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TOOLPANEL_H
#define __TOOLPANEL_H
//////////////////////////////////////////////////////////////////////////



namespace WTLBuilderCtrl
{
    class CToolTab:public CWindowImpl<CToolTab,CTabCtrl>,public ControlComponent<CToolTab>
    {
    public:
        CToolTab(LPTSTR _name=NULL);
        ~CToolTab(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(CToolTab)
            CHAIN_MSG_MAP(ControlComponent<CToolTab>)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()
        virtual void InitProperty(void);
    };
}
//////////////////////////////////////////////////////////////////////////
#endif