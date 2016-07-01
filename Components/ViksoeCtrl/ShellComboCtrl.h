// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SHELLCOMBOCTRL_H
#define __SHELLCOMBOCTRL_H
//////////////////////////////////////////////////////////////////////////
#include "atlshellext.h"
#include "ShellCtrls.h"

namespace ViksoeCtrl
{
    class CShellComboCtrlComp:public CShellComboCtrl,public ControlComponent<CShellComboCtrlComp>
    {
        CString path;
    public:
        CShellComboCtrlComp(LPTSTR _name=NULL);
        ~CShellComboCtrlComp(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(CShellComboCtrlComp)
            CHAIN_MSG_MAP(ControlComponent<CShellComboCtrlComp>)
            CHAIN_MSG_MAP(CShellComboCtrl)
        END_MSG_MAP()

        virtual void InitProperty(void);
        DECLARE_WINSTYLE_BOOL_PROPERTY(AutoScroll)
        DECLARE_WINSTYLE_BOOL_PROPERTY(DisableNoScroll)
        DECLARE_WINSTYLE_PROPERTY(Style)
        DECLARE_WINSTYLE_BOOL_PROPERTY(NoIntegralHeight)
        DECLARE_WINSTYLE_BOOL_PROPERTY(Sort)
        DECLARE_PROPERTY(ItemHeight,long)
        DECLARE_PROPERTY(EditHeight,long)
        DECLARE_PROPERTY(DroppedWidth,long)
        DECLARE_PROPERTY(HorizontalExtent,long)
        DECLARE_PROPERTY(ShowDropDown,BOOL)
        DECLARE_PROPERTY(CurSel,long)
        virtual CRect GetBoundsRect(void);

        DECLARE_PROPERTY(NoFolders,BOOL)      
        DECLARE_PROPERTY(NoFiles,BOOL)
        DECLARE_PROPERTY(ShowHidden,BOOL)
        DECLARE_PROPERTY(NoReadOnly,BOOL)
        DECLARE_PROPERTY(LocalComputer,BOOL)
        DECLARE_PROPERTY(FileSysytemOnly,BOOL)
        DECLARE_PROPERTY(NoRoot,BOOL)
        DECLARE_PROPERTY(Path,CString)
    };
}
//////////////////////////////////////////////////////////////////////////
#endif
