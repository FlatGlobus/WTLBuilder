// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "progressbarctrl.h"
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
static void RegisterProgressBarCtrlStyles();

namespace StdCtrl
{
	REGISTER_COMPONENT(CProgressBarCtrl,StdCtl,IDB_PROGRESSBARCTRL)

		CProgressBarCtrl::CProgressBarCtrl(LPTSTR _name):ControlComponent<StdCtrl::CProgressBarCtrl>(_name),
		m_minRange(0),m_maxRange(100),m_pos(50),m_step(1),m_offsetPos(0)
	{
		SetDefaultSize(146,20);
		enableTabIndex=FALSE;
	}

	CProgressBarCtrl::~CProgressBarCtrl(void)
	{
	}

	BOOL CProgressBarCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CProgressBarCtrl,WTL::CProgressBarCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CProgressBarCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CProgressBarCtrl>::InitProperty();
		DEFINE_PROPERTY(Vertical,BOOL,CProgressBarCtrl,FALSE)
		DEFINE_PROPERTY(Smooth,BOOL,CProgressBarCtrl,FALSE)
		DEFINE_PROPERTY(BkColor,CColorref,CProgressBarCtrl,(int)CLR_DEFAULT)
		DEFINE_PROPERTY(BarColor,CColorref,CProgressBarCtrl,(int)CLR_DEFAULT)
		DEFINE_PROPERTY(Max,long,CProgressBarCtrl,100)
		DEFINE_PROPERTY(Min,long,CProgressBarCtrl,0)
		DEFINE_PROPERTY(Step,long,CProgressBarCtrl,10)
		DEFINE_PROPERTY(Pos,long,CProgressBarCtrl,0)
		DEFINE_PROPERTY(OffsetPos,long,CProgressBarCtrl,0)
	}

	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CProgressBarCtrl,Vertical,(PBS_VERTICAL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CProgressBarCtrl,Smooth,(PBS_SMOOTH))

	void CProgressBarCtrl::set_BkColor(CColorref val)
	{
		if(val!=(COLORREF)-1)
		{
			m_bkColor=val;
			SetBkColor(m_bkColor);
		}
		SetModified();
	}

	CColorref CProgressBarCtrl::get_BkColor()
	{
		return m_bkColor;
	}

	void CProgressBarCtrl::set_BarColor(CColorref val)
	{
		if(val!=(COLORREF)-1)
		{
			m_barColor=val;
			SetBarColor(m_barColor);
		}
		SetModified();
	}

	CColorref CProgressBarCtrl::get_BarColor()
	{
		return m_barColor;
	}

	void CProgressBarCtrl::set_Min(long val)
	{
		m_minRange=val;
		SetRange32(m_minRange,m_maxRange);
		SetModified();
	}

	long CProgressBarCtrl::get_Min()
	{
		return m_minRange;
	}

	void CProgressBarCtrl::set_Max(long val)
	{
		m_maxRange=val;
		SetRange32(m_minRange,m_maxRange);
		SetModified();
	}

	long CProgressBarCtrl::get_Max()
	{
		return m_maxRange;
	}

	void CProgressBarCtrl::set_Pos(long val)
	{
		m_pos=val;
		SetPos(m_pos);
		SetModified();
	}

	long CProgressBarCtrl::get_Pos()
	{
		return m_pos;
	}

	void CProgressBarCtrl::set_Step(long val)
	{
		m_step=val;
		SetStep(m_step);
		SetModified();
	}

	long CProgressBarCtrl::get_Step()
	{
		return m_step;
	}

	void CProgressBarCtrl::set_OffsetPos(long val)
	{
		m_offsetPos=val;
		OffsetPos(m_offsetPos);
		SetModified();
	}

	long CProgressBarCtrl::get_OffsetPos()
	{
		return m_offsetPos;
	}

}
//////////////////////////////////////////////////////////////////////////
