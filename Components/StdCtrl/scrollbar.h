// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SCROLLBAR_H
#define __SCROLLBAR_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CHScrollBar:public CWindowImpl<StdCtrl::CHScrollBar,WTL::CScrollBar>,public ControlComponent<StdCtrl::CHScrollBar>
	{
	public:
		CHScrollBar(LPTSTR _name=NULL);
		~CHScrollBar(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CHScrollBar)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CHScrollBar>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_PROPERTY(Alignment)
	};

	class CVScrollBar:public CWindowImpl<StdCtrl::CVScrollBar,WTL::CScrollBar>,public ControlComponent<StdCtrl::CVScrollBar>
	{
	public:
		CVScrollBar(LPTSTR _name=NULL);
		~CVScrollBar(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CVScrollBar)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CVScrollBar>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_PROPERTY(Alignment)
	};

}
//////////////////////////////////////////////////////////////////////////
#endif
