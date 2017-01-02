// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TOOLBARCTRL_H
#define __TOOLBARCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CToolBarCtrl:public CWindowImpl<StdCtrl::CToolBarCtrl,WTL::CToolBarCtrl>,public ControlComponent<StdCtrl::CToolBarCtrl>
	{
	public:
		CToolBarCtrl(LPTSTR _name=NULL);
		~CToolBarCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CToolBarCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CToolBarCtrl>)
			MESSAGE_HANDLER(WM_PARENTNOTIFY ,OnParentNotify)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		LRESULT OnParentNotify(UINT,WPARAM,LPARAM, BOOL& bHandled);
        virtual CString     GetComponetKind(){return _T("TOOLBAR");}
		virtual void InitProperty(void);
		///common styles

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
