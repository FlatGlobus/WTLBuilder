// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "FontList.h"
//////////////////////////////////////////////////////////////////////////
void CFontListEdit::ShowProperty(PropertyBase *prop)
{
    CRect rect;
    GetWindowRect(&rect);
    CRect parentRect;
    ::GetClientRect(GetParent(),&parentRect);
    ::ScreenToClient(GetParent(),&rect.TopLeft());
    ::ScreenToClient(GetParent(),&rect.BottomRight());
	
    CClientDC dc(NULL);		
    EnumFonts (dc, 0,(FONTENUMPROC) EnumFontProc,(LPARAM)this);

    int itemcount=GetCount();
    if(itemcount==LB_ERR)
        return;
    int m_nNumLines = min(itemcount,5);

    int nHeight = rect.Height();
    rect.bottom = rect.bottom + m_nNumLines*nHeight;
    if(rect.bottom > parentRect.bottom)
        rect.OffsetRect(0,-(m_nNumLines-1)*nHeight);

    CString val=*((CString *)prop->GetValue(true));
    SetItemHeight(-1,nHeight);
    MoveWindow(rect);
    if(SelectString(-1,val) == LB_ERR) 
        SetWindowText(val);	
	
}

void CFontListEdit::UpdateProperty(PropertyBase *prop)
{
    int curr = GetCurSel();
    if(curr!=-1 && IsCancel()==FALSE)
    {
        CString v;
        CListBox::GetText(curr,v);

        if( *((CString *)prop->GetValue(true))!=v)
        {
            prop->SetValue(&v, true);
            ::UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
        }
    }
}

BOOL CALLBACK CFontListEdit::EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC /*lptm*/, DWORD dwType, LPARAM lpData)	
{	
    CFontListEdit *pThis = reinterpret_cast<CFontListEdit*>(lpData);		
    int index = pThis->AddString(lplf->lfFaceName);
    pThis->SetItemData (index, dwType); 
    return TRUE;
}

HWND CFontListEdit::CreateEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint &,LPARAM)
{
    CRect rc(Rect);
    rc.bottom-=1;
    rc.left+=1;

    CFontListEdit * temp= new CFontListEdit;
    temp->SetProperty(prop);
    HWND ret=temp->Create(Parent,rc);
    return ret;
}	
