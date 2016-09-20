// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __STATUSBARCTRL_H
#define __STATUSBARCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CStatusBarCtrl:public CWindowImpl<StdCtrl::CStatusBarCtrl,WTL::CStatusBarCtrl>,public ControlComponent<StdCtrl::CStatusBarCtrl>
	{
	public:
		CStatusBarCtrl(LPTSTR _name=NULL);
		~CStatusBarCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CStatusBarCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CStatusBarCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
        virtual CString     GetComponetKind(){return _T("STATUSBAR");}
		virtual void InitProperty(void);

		DECLARE_WINSTYLE_BOOL_PROPERTY(NoDivider)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoMoveY)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoMoveX)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoParentAlign)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoResize)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Adjustable)
		DECLARE_PROPERTY(Position, long)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
