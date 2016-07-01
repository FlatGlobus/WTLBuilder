// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "PropertyTextEdit.h"
//////////////////////////////////////////////////////////////////////////
void CInplaceTextEdit::ShowProperty(PropertyBase *prop)
{
    LimitText(256);
    SetWindowText(prop->ToString());
}

void CInplaceTextEdit::UpdateProperty(PropertyBase *prop)
{
    if(IsCancel()==FALSE)
    {
        CString str=GetText();
        if(prop->ToString()!=str)
        {
            prop->FromString(GetText());
            ::UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
        }
    }
}
//////////////////////////////////////////////////////////////////////////
void CInplaceIntEdit::ShowProperty(PropertyBase *prop)
{
    LimitText(256);
    SetWindowText(prop->ToString());
}

void CInplaceIntEdit::UpdateProperty(PropertyBase *prop)
{
    if(IsCancel()==FALSE)
    {
        CString str=GetText();
        if(prop->ToString()!=str)
        {
            prop->FromString(GetText());
            ::UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
        }
    }
}

LRESULT CInplaceIntEdit::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if(isdigit((int)wParam) || wParam == '-')
        return 0;
    bHandled=TRUE;
    return TRUE;
}
