// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __COMBOBOX_H
#define __COMBOBOX_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	typedef CSimpleArray<CString> CStringArray;

	class CComboBox:public CWindowImpl<StdCtrl::CComboBox,WTL::CComboBox>,public ControlComponent<StdCtrl::CComboBox>
	{
		CStringArray	strings;
		long limitText;

		void FillStringsArray(CString);
		void Reset();
	public:
		CComboBox(LPTSTR _name=NULL);
		~CComboBox(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CComboBox)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CComboBox>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(DisableNoScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(HasStrings)
		DECLARE_WINSTYLE_PROPERTY(Style)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LowerCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OemConvert)
		DECLARE_WINSTYLE_BOOL_PROPERTY(UpperCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoIntegralHeight)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Sort)
		DECLARE_PROPERTY(LimitText,long)
		DECLARE_PROPERTY(ItemHeight,long)
		DECLARE_PROPERTY(EditHeight,long)
		DECLARE_PROPERTY(DroppedWidth,long)
		DECLARE_PROPERTY(HorizontalExtent,long)
		DECLARE_PROPERTY(ShowDropDown,BOOL)
		DECLARE_PROPERTY(Strings,CString)
		DECLARE_PROPERTY(CurSel,long)
		
		virtual CRect GetBoundsRect(void);

	};
}
//////////////////////////////////////////////////////////////////////////
#endif