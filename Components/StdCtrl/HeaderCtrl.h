// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __HEADERCTRL_H
#define __HEADERCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CHeaderCtrl:public CWindowImpl<StdCtrl::CHeaderCtrl,WTL::CHeaderCtrl>,public ControlComponent<StdCtrl::CHeaderCtrl>
	{
        long items;
	public:
		CHeaderCtrl(LPTSTR _name=NULL);
		~CHeaderCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CHeaderCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CHeaderCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

        virtual CString     GetComponetKind() {return _T("HEADER");}

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(Buttons)
		DECLARE_WINSTYLE_BOOL_PROPERTY(DragDrop)
#if (_WIN32_IE >= 0x0500)
		DECLARE_WINSTYLE_BOOL_PROPERTY(FilterBar)
#endif
#if (_WIN32_WINNT >= 0x501)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Flat)
#endif
		DECLARE_WINSTYLE_BOOL_PROPERTY(FullDrag)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Hidden)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Horiz)
		DECLARE_WINSTYLE_BOOL_PROPERTY(HotTrack)
///common styles
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoDivider)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoMoveY)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoParentAlign)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoResize)
		//DECLARE_WINSTYLE_BOOL_PROPERTY(HotTrack)
		DECLARE_WINSTYLE_PROPERTY(CtrlAlign)
        DECLARE_PROPERTY(Items,long)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
