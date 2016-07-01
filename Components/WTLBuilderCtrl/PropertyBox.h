// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __LISTBOX_H
#define __LISTBOX_H
//////////////////////////////////////////////////////////////////////////

#include <..\Property\component.h>

namespace WTLBuilderCtrl
{
	class CPropertyList:public CWindowImpl<CPropertyList,WTL::CListBox>,public ControlComponent<CPropertyList>
	{
		CBrush	m_bkgBrush;
	public:
		CPropertyList(LPTSTR _name=NULL);
		~CPropertyList(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(CPropertyList)
			CHAIN_MSG_MAP(ControlComponent<CPropertyList>)
			MESSAGE_HANDLER(OCM_CTLCOLORLISTBOX,OnCtlColor)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
		virtual void InitProperty(void);
		LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& handled);
	};
}
//////////////////////////////////////////////////////////////////////////
#endif