// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __HOTKEYCTRL_H
#define __HOTKEYCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CHotKeyCtrl:public CWindowImpl<StdCtrl::CHotKeyCtrl,WTL::CHotKeyCtrl>,public ControlComponent<StdCtrl::CHotKeyCtrl>
	{
	public:
		CHotKeyCtrl(LPTSTR _name=NULL);
		~CHotKeyCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CHotKeyCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CHotKeyCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
