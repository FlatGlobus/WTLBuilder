// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __EDIT_H
#define __EDIT_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CEdit:public CWindowImpl<StdCtrl::CEdit,WTL::CEdit>,public ControlComponent<StdCtrl::CEdit>
	{
		CString text;
        CString cueBannerText;
        CString ddxVar;
		long limitText;
		//long leftMargin;
		//long rightMargin;
	public:
		CEdit(LPTSTR _name=NULL);
		~CEdit(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CEdit)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CEdit>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		//void SetLimitText(long);
		//long GetLimitText(void);
		DECLARE_PROPERTY(Text,CString)	
        DECLARE_PROPERTY(CueBannerText, CString)
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoHScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoVScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiLine)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LowerCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoHideSel)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Number)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OemConvert)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Password)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ReadOnly)
		DECLARE_WINSTYLE_BOOL_PROPERTY(UpperCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(WantReturn)
		DECLARE_WINSTYLE_PROPERTY(TextAlign)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif