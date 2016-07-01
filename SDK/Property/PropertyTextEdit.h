// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROPERTYTEXTEDIT_H
#define __PROPERTYTEXTEDIT_H
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "InplaceEdit.h"

typedef CWinTraits<WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_LEFT|ES_AUTOHSCROLL|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,0> CInplaceTextEditTraits;

class PROPERTY_API CInplaceTextEdit : 
   public CInplaceEditBase<CInplaceTextEdit,CEdit,CInplaceTextEditTraits>
{
public:
	virtual void ShowProperty(PropertyBase *prop);
	void UpdateProperty(PropertyBase *prop);
};

//////////////////////////////////////////////////////////////////////////

typedef CWinTraits<WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_LEFT|ES_AUTOHSCROLL|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,0> CInplaceIntEditTraits;
class PROPERTY_API CInplaceIntEdit : 
   public CInplaceEditBase<CInplaceIntEdit,CEdit,CInplaceIntEditTraits>
{
public:
    typedef CInplaceEditBase<CInplaceIntEdit,CEdit,CInplaceIntEditTraits> baseClass;

	virtual void ShowProperty(PropertyBase *prop);
	void UpdateProperty(PropertyBase *prop);
    LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
#endif