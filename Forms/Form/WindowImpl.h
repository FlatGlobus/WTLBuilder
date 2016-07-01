// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __WINDOWIMPL_H
#define __WINDOWIMPL_H
//////////////////////////////////////////////////////////////////////////
namespace Form
{

class CWindowImpl:public CFormComponent
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDI_FORM)
   
	CWindowImpl(LPTSTR _name=NULL);
	~CWindowImpl(void);
	virtual void InitProperty(void);
	virtual BOOL CreateComponent(Component *);
	virtual void OnFinalMessage(HWND /*hWnd*/);

	virtual BOOL __stdcall get_IsControl();
	virtual BOOL __stdcall get_IsForm();

    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Border,(WS_BORDER))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_NOT_I(Enabled,(WS_DISABLED))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(TabStop,(WS_TABSTOP))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Group,(WS_GROUP))
};
}
//////////////////////////////////////////////////////////////////////////
#endif