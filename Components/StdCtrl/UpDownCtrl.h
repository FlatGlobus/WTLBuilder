// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __UPDOWNCTRL_H
#define __UPDOWNCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CUpDownCtrl:public CWindowImpl<StdCtrl::CUpDownCtrl,WTL::CUpDownCtrl>,public ControlComponent<StdCtrl::CUpDownCtrl>
	{
        int lover,upper;
        CString buddy;
	public:
		CUpDownCtrl(LPTSTR _name=NULL);
		~CUpDownCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CUpDownCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CUpDownCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
        DECLARE_PROPERTY(Base,int)
        DECLARE_PROPERTY(Buddy,CString)
        DECLARE_PROPERTY(Pos,int)
        DECLARE_PROPERTY(Lover,int)
        DECLARE_PROPERTY(Upper,int)
        DECLARE_WINSTYLE_PROPERTY(Align)
        DECLARE_WINSTYLE_BOOL_PROPERTY(ArrowKeys)
        DECLARE_WINSTYLE_BOOL_PROPERTY(AutoBuddy)
        DECLARE_WINSTYLE_BOOL_PROPERTY(Horz)
        DECLARE_WINSTYLE_BOOL_PROPERTY(HotTrack)
        DECLARE_WINSTYLE_BOOL_PROPERTY(NoThousands)
        DECLARE_WINSTYLE_BOOL_PROPERTY(SetBuddyInt)
        DECLARE_WINSTYLE_BOOL_PROPERTY(Wrap)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
