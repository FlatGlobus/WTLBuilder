// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "PropertyBoolEdit.h"
//////////////////////////////////////////////////////////////////////////
void CInplaceBoolEdit::ShowProperty(PropertyBase *prop)
{
    SetCheck(*((BOOL *)prop->GetValue(true)) ? BST_CHECKED : BST_UNCHECKED);
    SetWindowText(prop->ToString());
}

void CInplaceBoolEdit::UpdateProperty(PropertyBase *prop)
{
    ::UpdateProperty(prop->GetName());
}

LRESULT CInplaceBoolEdit::OnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    BOOL check=GetCheck()==BST_UNCHECKED;
    GetProperty()->SetValue(&check, true);
    check=*reinterpret_cast<BOOL *>(GetProperty()->GetValue(true));
    SetCheck(check ? BST_CHECKED : BST_UNCHECKED);
    SetWindowText(GetProperty()->ToString());
    SendEvent(evAddUndo,NULL);
    bHandled=TRUE;
    return 1;
}
//////////////////////////////////////////////////////////////////////////
void CInplaceboolEdit::ShowProperty(PropertyBase *prop)
{
    SetCheck(*((bool *)prop->GetValue(true)) == true ? BST_CHECKED : BST_UNCHECKED);
    SetWindowText(prop->ToString());
}

void CInplaceboolEdit::UpdateProperty(PropertyBase *prop)
{
    ::UpdateProperty(prop->GetName());
}

LRESULT CInplaceboolEdit::OnClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    bool check=GetCheck()==BST_UNCHECKED;
    GetProperty()->SetValue(&check, true);
    check=*reinterpret_cast<bool *>(GetProperty()->GetValue(true));
    SetCheck(check == true ? BST_CHECKED : BST_UNCHECKED);
    SetWindowText(GetProperty()->ToString());
    SendEvent(evAddUndo,NULL);
    bHandled=FALSE;
    return 0;
}
