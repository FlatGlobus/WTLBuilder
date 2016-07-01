// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROPERTYBOOLEDIT_H
#define __PROPERTYBOOLEDIT_H
/////////////////////////////////////////////////////////////////////////////////////////////
#include "InplaceEdit.h"
typedef CWinTraits<WS_CHILD|WS_VISIBLE|BS_CHECKBOX|WS_TABSTOP,0> CInplaceBoolEditTraits;

class PROPERTY_API CInplaceBoolEdit : 
	public CInplaceEditBase<CInplaceBoolEdit,CButton,CInplaceBoolEditTraits>
{
public:
	typedef CInplaceEditBase<CInplaceBoolEdit,CButton,CInplaceBoolEditTraits> baseClass;
	BEGIN_MSG_MAP(CInplaceBoolEdit)
		CHAIN_MSG_MAP(baseClass)
		REFLECTED_COMMAND_CODE_HANDLER(BN_CLICKED,OnClick)
	END_MSG_MAP()

	virtual void ShowProperty(PropertyBase *prop);
	void UpdateProperty(PropertyBase *prop);
	LRESULT OnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

class PROPERTY_API CInplaceboolEdit : 
    public CInplaceEditBase<CInplaceboolEdit,CButton,CInplaceBoolEditTraits>
{
public:
    typedef CInplaceEditBase<CInplaceboolEdit,CButton,CInplaceBoolEditTraits> baseClass;
    BEGIN_MSG_MAP(CInplaceboolEdit)
        CHAIN_MSG_MAP(baseClass)
        REFLECTED_COMMAND_CODE_HANDLER(BN_CLICKED,OnClick)
    END_MSG_MAP()

    virtual void ShowProperty(PropertyBase *prop);
    void UpdateProperty(PropertyBase *prop);
    LRESULT OnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};
/////////////////////////////////////////////////////////////////////////////////////////////
#endif