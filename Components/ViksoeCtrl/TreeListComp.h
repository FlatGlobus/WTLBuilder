// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
//#include "TreeListView.h"
#include <atlwinx.h>
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
    class CTreeListViewComp:public CWindowImpl<CTreeListViewComp,WTL::CListViewCtrl>/*CTreeListViewCtrl*/,public ControlComponent<CTreeListViewComp>
    {
    public:
        CTreeListViewComp(LPTSTR _name=NULL);
        ~CTreeListViewComp(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(CTreeListViewComp)
            CHAIN_MSG_MAP(ControlComponent<CTreeListViewComp>)
//            CHAIN_MSG_MAP(CListViewCtrl)/*CTreeListViewCtrl*/
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()

        virtual void InitProperty(void);
    };
};
#endif   
//////////////////////////////////////////////////////////////////////////