// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROGRESSBARCTRL_H
#define __PROGRESSBARCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CProgressBarCtrl:public CWindowImpl<StdCtrl::CProgressBarCtrl,WTL::CProgressBarCtrl>,public ControlComponent<StdCtrl::CProgressBarCtrl>
	{
		CColorref m_bkColor,m_barColor;
		long m_minRange,m_maxRange;
		long m_pos,m_step,m_offsetPos;
	public:
		CProgressBarCtrl(LPTSTR _name=NULL);
		~CProgressBarCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CProgressBarCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CProgressBarCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
	
		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(Vertical)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Smooth)
		DECLARE_PROPERTY(BkColor,CColorref)
		DECLARE_PROPERTY(BarColor,CColorref)
		DECLARE_PROPERTY(Min,long)
		DECLARE_PROPERTY(Max,long)
		DECLARE_PROPERTY(Pos,long)
		DECLARE_PROPERTY(Step,long)
		DECLARE_PROPERTY(OffsetPos,long)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
