// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __IMAGELIST_H
#define __IMAGELIST_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
    class CMenu:public Component
    {
		WTL::CMenu hMenu;
		CString menuID;
		void CreateSampleMenu();
    public:
        CMenu(LPTSTR _name=NULL);
        ~CMenu(void);
        virtual BOOL CreateComponent(Component *);
		virtual void DeleteComponent();

        virtual void InitProperty(void);
        virtual CString     GetComponetKind(){return _T("MENU");}
        virtual HANDLE GetHandle();
		DECLARE_PROPERTY(ID,CString)	
    };
}
//////////////////////////////////////////////////////////////////////////
#endif
