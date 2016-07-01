// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once

namespace StdCtrl
{
    class CPaneContainer:public WTL::CPaneContainer,public ControlComponent<StdCtrl::CPaneContainer>
    {
        CString title;
        BOOL    closeButton;
        BOOL    enableCloseButton;
        BOOL    vertical;
    public:
        CPaneContainer(LPTSTR _name=NULL);
        ~CPaneContainer(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(StdCtrl::CPaneContainer)
            CHAIN_MSG_MAP(ControlComponent<StdCtrl::CPaneContainer>)
            CHAIN_MSG_MAP(CPaneContainerImpl<WTL::CPaneContainer>)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()
        virtual void InitProperty(void);
        virtual CRect GetBoundsRect(void);
        virtual void SetBoundsRect(CRect rc);
        DECLARE_PROPERTY(Title,CString)
        DECLARE_PROPERTY(CloseButton,BOOL)
        DECLARE_PROPERTY(EnableCloseButton,BOOL)
        DECLARE_PROPERTY(Vertical,BOOL)

        //virtual BOOL MouseMove(CDC *,CPoint,HintItem);
    };
}
