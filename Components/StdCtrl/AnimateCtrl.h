// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#ifndef __ANIMATECTRL_H
#define __ANIMATECTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CAviImage
	{
		CString fileName;
		CString	id;
	public:
		CAviImage();
		~CAviImage();
		void set_FileName(CString);
		CString get_FileName();
		void set_ID(CString);
		CString get_ID(void);

		void AddProperty(LPCTSTR,CProperties &);
		DECLARE_CALLBACK(Change,change)
	};

	class CAnimateCtrl:public CWindowImpl<StdCtrl::CAnimateCtrl,WTL::CAnimateCtrl>,public ControlComponent<StdCtrl::CAnimateCtrl>
	{
		BOOL	play;	
		CAviImage image;
		void OnImageChange(CAviImage *);
	public:
		CAnimateCtrl(LPTSTR _name=NULL);
		~CAnimateCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CAnimateCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CAnimateCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoPlay)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Center)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Timer)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Transparent)
		DECLARE_PROPERTY(Play,BOOL)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
