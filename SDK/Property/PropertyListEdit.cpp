// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
void CInplaceListEdit::ShowProperty(PropertyBase *prop)
{
    CRect rect;
    GetWindowRect(&rect);
    CRect parentRect;
    ::GetClientRect(GetParent(),&parentRect);
    ::ScreenToClient(GetParent(),&rect.TopLeft());
    ::ScreenToClient(GetParent(),&rect.BottomRight());

    int itemcount=GetCustomValCount(prop->GetType());
    int m_nNumLines = min(itemcount,5);

    int nHeight = rect.Height();
    rect.bottom = rect.bottom + m_nNumLines*nHeight;
    if(rect.bottom > parentRect.bottom)
        rect.OffsetRect(0,-(m_nNumLines-1)*nHeight);

    CCustomVal * values=GetCustomVal(prop->GetType());
    if(values)
    {
        for (int i = 0; values[i].name!=NULL; i++) 
        {
            int idx=AddString(values[i].decorate);
            SetItemData(idx,values[i].id);
        }
    }
    SetItemHeight(-1,nHeight);
    MoveWindow(rect);

    CString val=ValueToDecorateString(prop->GetType(),prop->GetValue(true));

    if(SelectString(-1,val) == LB_ERR) 
        SetWindowText(val);	
}

void CInplaceListEdit::UpdateProperty(PropertyBase *prop)
{
    int curr = GetCurSel();
    if(curr!=-1 && IsCancel()==FALSE)
    {
        long val=(long)GetItemData(curr);
        if( *((long *)prop->GetValue(true))!=val)
        {
            prop->SetValue(&val, true);
            ::UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
        }
    }
}

LRESULT CInplaceListEdit::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
    ::SetFocus(GetParent());
    bHandled=TRUE;
    return lRes;
}

HWND CInplaceListEdit::CreateEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint &,LPARAM)
{
    CRect rc(Rect);
    rc.bottom-=1;
    rc.left+=1;

    CInplaceListEdit * temp= new CInplaceListEdit;
    temp->SetProperty(prop);
    HWND ret=temp->Create(Parent,rc);
    return ret;
}	
