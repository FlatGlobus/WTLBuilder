// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SPLASHWND_H
#define __SPLASHWND_H
//////////////////////////////////////////////////////////////////////////
namespace Form
{
    class CSplashWnd:public CFormComponent
    {
    public:
        DECLARE_FRAME_WND_CLASS(NULL,IDI_FORM)
        CSplashWnd(LPTSTR _name=NULL);
        ~CSplashWnd(void);
        virtual void InitProperty(void);
        virtual BOOL CreateComponent(Component *);
        virtual void OnFinalMessage(HWND /*hWnd*/);
    };
}
//////////////////////////////////////////////////////////////////////////
#endif