// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __MDICHILDWINDOWIMPL_H
#define __MDICHILDWINDOWIMPL_H
//////////////////////////////////////////////////////////////////////////
namespace Form
{
    class CMDIChildWindowImpl:public CFormComponent
    {
    public:

        DECLARE_FRAME_WND_CLASS(NULL,IDI_FORM)

        CMDIChildWindowImpl(LPTSTR _name=NULL);
        ~CMDIChildWindowImpl(void);
        virtual void InitProperty(void);
        virtual BOOL CreateComponent(Component *);
        virtual void OnFinalMessage(HWND /*hWnd*/);
        virtual CRect GetMinRect();
    };
}
//////////////////////////////////////////////////////////////////////////
#endif