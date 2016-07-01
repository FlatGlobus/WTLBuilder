// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __LABEL_H
#define __LABEL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CStatic:public CWindowImpl<StdCtrl::CStatic,WTL::CStatic>,
                  public ControlComponent<StdCtrl::CStatic>
	{
		CString caption;
		long    textAlign;
	public:
		CStatic(LPTSTR _name=NULL);
		~CStatic(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(CStatic)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CStatic>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);

		DECLARE_PROPERTY(Caption,CString)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Notify)
		DECLARE_WINSTYLE_PROPERTY(TextAlign)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Simple)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Etched)
		DECLARE_WINSTYLE_BOOL_PROPERTY(WordWrap)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoPrefix)
		   
	};

	class CPicture:public CWindowImpl<CPicture,WTL::CStatic>,public ControlComponent<StdCtrl::CPicture>
	{
        CImage image;
        void OnImageChange(CImage *);
	public:
		CPicture(LPTSTR _name=NULL);
		~CPicture(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(CPicture)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CPicture>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(Notify)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Etched)
        DECLARE_WINSTYLE_BOOL_PROPERTY(CenterImage)
	};

}
//////////////////////////////////////////////////////////////////////////
#endif