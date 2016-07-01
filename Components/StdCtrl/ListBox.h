// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __LISTBOX_H
#define __LISTBOX_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	typedef CSimpleArray<CString> CStringArray;
	class CListBox:public CWindowImpl<StdCtrl::CListBox,WTL::CListBox>,public ControlComponent<StdCtrl::CListBox>
	{
		CStringArray	strings;
		long columnWidth;
		void FillStringsArray(CString);
		void Reset();

	public:
		CListBox(LPTSTR _name=NULL);
		~CListBox(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CListBox)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CListBox>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(DisableNoScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ExtendedSelect)
		DECLARE_WINSTYLE_BOOL_PROPERTY(HasStrings)
		DECLARE_WINSTYLE_PROPERTY(Style)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiColumn)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiSelect)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoData)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoRedraw)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoSelect)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Notify)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Sort)
		DECLARE_WINSTYLE_BOOL_PROPERTY(UseTabStops)
		DECLARE_WINSTYLE_BOOL_PROPERTY(WantKeyboardInput)
		DECLARE_PROPERTY(HorizontalExtent,long)
		DECLARE_PROPERTY(Strings,CString)
		DECLARE_PROPERTY(CurSel,long)
		DECLARE_PROPERTY(ItemHeight,long)
		DECLARE_PROPERTY(ColumnWidth,long)
		
	};
}
//////////////////////////////////////////////////////////////////////////
#endif