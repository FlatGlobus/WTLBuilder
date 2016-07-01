// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SPLITTER_H
#define __SPLITTER_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
    class CSplitterWindow:public WTL::CSplitterWindow,public ControlComponent<StdCtrl::CSplitterWindow>
    {
        CString leftPane,rightPane;
        Component *leftPaneParent,*rightPaneParent;
        long activePane;
        BOOL CheckPaneName(CString);
        void LeftPaneChanged(Component* comp);
        void RightPaneChanged(Component* comp);
    public:
        typedef WTL::CSplitterWindow baseClass;
        CSplitterWindow(LPTSTR _name=NULL);
        ~CSplitterWindow(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(StdCtrl::CSplitterWindow)
            CHAIN_MSG_MAP(ControlComponent<StdCtrl::CSplitterWindow>)
            CHAIN_MSG_MAP(baseClass)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()

        virtual void InitProperty(void);
        virtual void SetBoundsRect(CRect);

        DECLARE_PROPERTY(LeftPane,CString)
        DECLARE_PROPERTY(RightPane,CString)
        DECLARE_PROPERTY(Proportional,BOOL)
        DECLARE_PROPERTY(NonInteractive,BOOL)
        DECLARE_PROPERTY(RightAligned,BOOL)
        DECLARE_PROPERTY(Pos,long)
        DECLARE_PROPERTY(SinglePaneMode,long)
        DECLARE_PROPERTY(ActivePane,long)
    };

    class CHorSplitterWindow:public WTL::CHorSplitterWindow,public ControlComponent<StdCtrl::CHorSplitterWindow>
    {
        CString topPane,bottomPane;
        Component *topPaneParent,*bottomPaneParent;
        long activePane;
        BOOL CheckPaneName(CString);
        void TopPaneChanged(Component* comp);
        void BottomPaneChanged(Component* comp);
    public:
        typedef WTL::CHorSplitterWindow baseClass;
        CHorSplitterWindow(LPTSTR _name=NULL);
        ~CHorSplitterWindow(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(StdCtrl::CHorSplitterWindow)
            CHAIN_MSG_MAP(ControlComponent<StdCtrl::CHorSplitterWindow>)
            CHAIN_MSG_MAP(baseClass)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()
            
        virtual void InitProperty(void);
        virtual void SetBoundsRect(CRect);
        
        DECLARE_PROPERTY(TopPane,CString)
        DECLARE_PROPERTY(BottomPane,CString)
        DECLARE_PROPERTY(Proportional,BOOL)
        DECLARE_PROPERTY(NonInteractive,BOOL)
        DECLARE_PROPERTY(BottomAligned,BOOL)
        DECLARE_PROPERTY(Pos,long)
        DECLARE_PROPERTY(SinglePaneMode,long)
        DECLARE_PROPERTY(ActivePane,long)
    };

}
//////////////////////////////////////////////////////////////////////////
#endif