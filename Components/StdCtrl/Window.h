// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __WINDOW_H
#define __WINDOW_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CWindow:public CWindowImpl<StdCtrl::CWindow>,public ControlComponent<StdCtrl::CWindow>
	{
	public:
		DECLARE_WND_CLASS(NULL)
		CWindow(LPTSTR _name=NULL);
		~CWindow(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CWindow)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CWindow>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
