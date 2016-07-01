// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TREEVIEWCTRL_H
#define __TREEVIEWCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CTreeViewCtrl:public CWindowImpl<StdCtrl::CTreeViewCtrl,WTL::CTreeViewCtrl>,public ControlComponent<StdCtrl::CTreeViewCtrl>
	{
	public:
		CTreeViewCtrl(LPTSTR _name=NULL);
		~CTreeViewCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CTreeViewCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CTreeViewCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		///common styles
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoDivider)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoMoveY)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoParentAlign)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoResize)
		//DECLARE_WINSTYLE_BOOL_PROPERTY(HotTrack)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
