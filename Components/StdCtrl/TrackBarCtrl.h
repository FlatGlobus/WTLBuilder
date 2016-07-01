// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TRACKBARCTRL_H
#define __TRACKBARCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CTrackBarCtrl:public CWindowImpl<StdCtrl::CTrackBarCtrl,WTL::CTrackBarCtrl>,public ControlComponent<StdCtrl::CTrackBarCtrl>
	{
	public:
		CTrackBarCtrl(LPTSTR _name=NULL);
		~CTrackBarCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CTrackBarCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CTrackBarCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
