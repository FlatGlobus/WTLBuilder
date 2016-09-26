// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SHELLTREECTRL_H
#define __SHELLTREECTRL_H

#include "atlshellext.h"
#include "ShellCtrls.h"
//////////////////////////////////////////////////////////////////////////
namespace ViksoeCtrl
{
    class CShellTreeCtrlComp:public CShellTreeCtrl,public ControlComponent<CShellTreeCtrlComp>
	{
        CString path;
	public:
		CShellTreeCtrlComp(LPTSTR _name=NULL);
		~CShellTreeCtrlComp(void);

		virtual BOOL CreateComponent(Component *);

		BEGIN_MSG_MAP(CShellTreeCtrlComp)
			CHAIN_MSG_MAP(ControlComponent<CShellTreeCtrlComp>)
            CHAIN_MSG_MAP(CShellTreeCtrl)
			//REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		///common styles
		
        DECLARE_PROPERTY(NoFolders,BOOL)      
        DECLARE_PROPERTY(NoFiles,BOOL)
        DECLARE_PROPERTY(ShowHidden,BOOL)
        DECLARE_PROPERTY(NoReadOnly,BOOL)
        DECLARE_PROPERTY(LocalComputer,BOOL)
        DECLARE_PROPERTY(FileSysytemOnly,BOOL)
        DECLARE_PROPERTY(NoRoot,BOOL)
        
        DECLARE_PROPERTY(Path,CString)


		DECLARE_WINSTYLE_BOOL_PROPERTY(CheckBoxes)
		DECLARE_WINSTYLE_BOOL_PROPERTY(DisableDragAndDrop)
		DECLARE_WINSTYLE_BOOL_PROPERTY(EditLabels)
		DECLARE_WINSTYLE_BOOL_PROPERTY(FullRowSelect)
		DECLARE_WINSTYLE_BOOL_PROPERTY(HasButtons)
		DECLARE_WINSTYLE_BOOL_PROPERTY(HasLines)
		DECLARE_WINSTYLE_BOOL_PROPERTY(InfoTip)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LinesAtRoot)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoHScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoNevenHeight)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoToolTips)
		DECLARE_WINSTYLE_BOOL_PROPERTY(RTLReading)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ShowSelAlways)
		DECLARE_WINSTYLE_BOOL_PROPERTY(SingleExpand)
		DECLARE_WINSTYLE_BOOL_PROPERTY(TrackSelect)

	};
}
//////////////////////////////////////////////////////////////////////////
#endif
