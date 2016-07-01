// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TABCTRL_H
#define __TABCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	typedef CSimpleArray<CString> CStringArray;
	class CTabCtrl:public CWindowImpl<StdCtrl::CTabCtrl,WTL::CTabCtrl>,public ControlComponent<StdCtrl::CTabCtrl>
	{
		CString current;
		CStringArray	pages;
		CString imageList;
		
		void FillPagesArray(CString);
		void Reset();
		int FindPage(CString val);
		void ImageListChanged(Component* comp);
	public:
		CTabCtrl(LPTSTR _name=NULL);
		~CTabCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CTabCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CTabCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		
		DECLARE_PROPERTY(Pages,CString)
		DECLARE_PROPERTY(CurSel,CString)
        DECLARE_PROPERTY(ImageList,CString)
        
		DECLARE_WINSTYLE_BOOL_PROPERTY(Bottom)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Buttons)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Right)
		DECLARE_WINSTYLE_BOOL_PROPERTY(FlatButtons)
		DECLARE_WINSTYLE_BOOL_PROPERTY(FocusNever)
		DECLARE_WINSTYLE_BOOL_PROPERTY(FocusOnButtonDown)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ForceIconLeft)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ForceLabelLeft)
		DECLARE_WINSTYLE_BOOL_PROPERTY(HotTrack)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiLine)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiSelect)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OwnerDrawFixed)
		DECLARE_WINSTYLE_PROPERTY(Style)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ScrollOpposite)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Tabs)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Vertical)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
