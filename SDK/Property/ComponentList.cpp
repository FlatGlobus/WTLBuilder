// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
CString CComponentListEdit::kind=_T("");

CComponentListEdit::CComponentListEdit(PropertyBase * p):m_fCancel(false),prop(p)
{
}

void CComponentListEdit::OnFinalMessage(HWND /*hWnd*/)
{
    delete this;
}

LRESULT CComponentListEdit::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    //using WTL::CString;
    LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
    SetFont( (HFONT)::SendMessage(GetParent(), WM_GETFONT, 0, 0) );

    CRect rect;
    GetWindowRect(&rect);
    ::ScreenToClient(GetParent(),&rect.TopLeft());
    ::ScreenToClient(GetParent(),&rect.BottomRight());

    CRect parentRect;
    ::GetClientRect(GetParent(),&parentRect);

    Component * component=prop->GetProperties()->GetComponent();
    Components *components=component->GetComponents();
    CString selfName=component->get_Name();
    CString val=*((CString *)prop->GetValue(true));
    for (int i = 0; i < components->GetCount(); i++) 
    {
        if(components->GetAt(i)->GetComponetKind()==kind ||
            kind.IsEmpty())
        {
            CString str=components->GetAt(i)->get_Name();
            if(selfName!=str)
            {
                int idx=AddString(str);
                SetItemData(idx,i);
            }
        }
    }

    int itemcount=GetCount()+1;
    int m_nNumLines = min(itemcount,5);

    int nHeight = rect.Height();
    rect.bottom = rect.bottom + m_nNumLines*nHeight;
    if(rect.bottom > parentRect.bottom)
        rect.OffsetRect(0,-(m_nNumLines-1)*nHeight);

    int idx=AddString(GetNoneStr());
    SetItemData(idx,-1);

    SetItemHeight(-1,nHeight);
    MoveWindow(rect);
    if(SelectString(-1,val) == LB_ERR) 
        SetWindowText(val);	
    SetFocus();
    return lRes;
}

LRESULT CComponentListEdit::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

    switch( wParam )
    {
    case VK_ESCAPE:
        m_fCancel = true;
        ::SetFocus(GetParent());
        break;
    case VK_RETURN:
        ::SetFocus(GetParent());
        break;
        return 0;
    }
    bHandled = FALSE;
    return 0;
}

LRESULT CComponentListEdit::OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    UpdateProperty();
    PostMessage(WM_CLOSE);
    bHandled = FALSE;
    return 0;
}

LRESULT CComponentListEdit::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
    ::SetFocus(GetParent());
    bHandled=TRUE;
    return 0;
}

void CComponentListEdit::UpdateProperty(void)
{
//    using WTL::CString;
    if( !m_fCancel )
    {
        int curr = GetCurSel();
        if(curr!=-1)
        {
            CString v;
            GetText(curr,v);
            if( *((CString *)prop->GetValue(true))!=v)
            {
                prop->SetValue(&v, true);
                ::UpdateProperty(prop->GetName());
                SendEvent(evAddUndo,NULL);
            }
        }
    }

}

LRESULT CComponentListEdit::OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    return DefWindowProc(uMsg, wParam, lParam) | DLGC_WANTALLKEYS;
}

HWND CComponentListEdit::CreateInplaceEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint&,LPARAM)
{
    CComponentListEdit * temp= new CComponentListEdit(prop);
    return temp->Create(Parent,Rect);
}	

LPCTSTR CComponentListEdit::GetNoneStr()
{
	static TCHAR * NONE_STR= _T("NULL");
    return NONE_STR;
}

void CComponentListEdit::SetComponentKind(LPCTSTR _kind)
{
    kind=_kind;
}
