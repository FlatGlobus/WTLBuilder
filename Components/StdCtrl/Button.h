// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#ifndef __BUTTON_H
#define __BUTTON_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CButton:public CWindowImpl<StdCtrl::CButton,WTL::CButton>,public ControlComponent<StdCtrl::CButton>
	{
		CString caption;
		CImage bitmap;
		void OnImageChange(CImage *);
	public:
		CButton(LPTSTR _name=NULL);
		~CButton(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(CButton)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CButton>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
		virtual void InitProperty(void);
		LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		DECLARE_PROPERTY(Caption,CString)	
		DECLARE_WINSTYLE_PROPERTY(HorizAlign)
		DECLARE_WINSTYLE_PROPERTY(VertAlign)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Flat)
		DECLARE_WINSTYLE_BOOL_PROPERTY(DefPushButton)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiLine)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Notify)
		DECLARE_WINSTYLE_BOOL_PROPERTY(PushButton)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LeftText)
		DECLARE_WINSTYLE_PROPERTY(Style)
		DECLARE_PROPERTY(Check,long)
	};

    class CBitmapButton:public WTL::CBitmapButton,public ControlComponent<StdCtrl::CBitmapButton>
    {
        CString caption;
        CImage bitmap;
        void OnImageChange(CImage *);
    public:
        CBitmapButton(LPTSTR _name=NULL);
        ~CBitmapButton(void);
        virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(StdCtrl::CBitmapButton)
            CHAIN_MSG_MAP(ControlComponent<StdCtrl::CBitmapButton>)
            CHAIN_MSG_MAP(WTL::CBitmapButton)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()
        virtual void InitProperty(void);
        LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        DECLARE_PROPERTY(Caption,CString)	
        DECLARE_WINSTYLE_PROPERTY(HorizAlign)
        DECLARE_WINSTYLE_PROPERTY(VertAlign)
        DECLARE_WINSTYLE_BOOL_PROPERTY(Flat)
        DECLARE_WINSTYLE_BOOL_PROPERTY(DefPushButton)
        DECLARE_WINSTYLE_BOOL_PROPERTY(MultiLine)
        DECLARE_WINSTYLE_BOOL_PROPERTY(Notify)
        DECLARE_WINSTYLE_BOOL_PROPERTY(PushButton)
        DECLARE_WINSTYLE_BOOL_PROPERTY(LeftText)
        DECLARE_WINSTYLE_PROPERTY(Style)
        DECLARE_PROPERTY(Check,long)
    };

	class CCheckBox:public StdCtrl::CButton
	{
		BOOL checked;
	public:
		CCheckBox(LPTSTR _name=NULL);
		~CCheckBox(void);
		virtual void InitProperty(void);
		DECLARE_WINSTYLE_PROPERTY(CheckBoxStyle)
		//DECLARE_WINSTYLE_BOOL_PROPERTY(Auto3State)
		//DECLARE_WINSTYLE_BOOL_PROPERTY(AutoCheckBox)
	};

	class CRadioButton:public StdCtrl::CButton
	{
		BOOL checked;
	public:
		CRadioButton(LPTSTR _name=NULL);
		~CRadioButton(void);
		virtual void InitProperty(void);
		DECLARE_WINSTYLE_PROPERTY(RadioButtonStyle)	
	};

	class CGroupBox:public StdCtrl::CButton
	{
		BOOL checked;
	public:
		CGroupBox(LPTSTR _name=NULL);
		~CGroupBox(void);
		virtual void InitProperty(void);
		BEGIN_MSG_MAP_EX(CGroupBox)
			CHAIN_MSG_MAP(StdCtrl::CButton)
		END_MSG_MAP()
	};

}
//////////////////////////////////////////////////////////////////////////
#endif