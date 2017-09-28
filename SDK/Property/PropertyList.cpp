// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include <atlcrack.h>
#include "Property.h"
#include <atlctrls.h>
#include "LineTracker.h"
#include "PropertyItem.h"
#include "GDIUtil.h"
#include "PropertyList.h"
#include "resource.h"


#define RIGHT_SHIFT 10
#define ITEM_HEIGHT 16

/////////////////////////////////////////////////////////////////////////////
CPropertyList::CPropertyList():m_ButtonPressed(FALSE),properties(NULL),m_SelectedIndex(-1),m_propEdit(NULL)
{
}

HWND CPropertyList::Create(HWND Parent,CRect & rect,UINT id)
{
	m_PlusBmp.LoadBitmap(IDB_PLUS);
	m_MinusBmp.LoadBitmap(IDB_MINUS);
	m_ButtonBmp.LoadBitmap(IDB_BUTTON);
	m_bkgBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	return CWindowImpl< CPropertyList, CListBox >::Create(Parent,rect,NULL,
		LBS_OWNERDRAWFIXED|WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY|
		LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT,0,id);
}

LRESULT CPropertyList::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	m_Font.CreateFont(-12,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Ms Sans Serif"));
	SetFont(m_Font);
	m_Tracker.SetParent(m_hWnd);
	SetItemHeight(-1,ITEM_HEIGHT);
	return lRes;
}

LRESULT CPropertyList::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	ResetContent();
	return 0;
}

LRESULT CPropertyList::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LRESULT lRes = 0;

	CPoint point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);

	if(m_Tracker.CheckPos(point))
		m_Tracker.MouseDown(point);
	else
		lRes = DefWindowProc(uMsg, wParam, lParam);
	DoButtonTest(point);
	return lRes;
}

LRESULT CPropertyList::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	CPoint point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	m_Tracker.MouseMove(point);   
	return lRes;
}

LRESULT CPropertyList::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LRESULT lRes = 0;
	if(GetFocus()!=m_hWnd)
		SetFocus();

	CPoint point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);

	if(m_Tracker.CheckPos(point))
	{
		m_Tracker.MouseUp(point);
		Invalidate();
	}
	else
	{
		lRes = DefWindowProc(uMsg, wParam, lParam);
		if(m_SelectedIndex!=-1)
		{
			PropertyBase * prop=GetProperty(m_SelectedIndex);
            if(prop->GetReadOnly()==TRUE)
                return lRes;
			CRect rc(GetPropRect(m_SelectedIndex));

			if(DoButtonTest(point) && GetExPropEdit(prop->GetType()))
			{
				if(m_ButtonPressed==TRUE)
				{
					m_ButtonPressed=FALSE;
					CClientDC dc(m_hWnd);
					DrawButton(dc,rc,FALSE);
				}
				GetExPropEdit(prop->GetType())(m_hWnd,prop,NULL);
			}
			else    
				if(DoClickTest(point)==FALSE)
				{
					rc.left=m_Tracker.GetPos();
					DoEditItem(m_SelectedIndex,rc,point);
				}
		}
	}    
	return lRes;
}

LRESULT CPropertyList::OnDblClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);

	if(DoClickTest(point))
	{
		PropertyBase * prop=GetProperty(m_SelectedIndex);
		if(prop==NULL)
			return 0;

		if(prop->HasChild())  
		{
			if(prop->GetExpand()==false)
			{
				InsertSubProperty(m_SelectedIndex,prop);
				prop->SetExpand(true);
			}   
			else
			{
				RemoveSubProperty(m_SelectedIndex,prop);
				prop->SetExpand(false);
			}
		}

	}
	else
		if(DoButtonTest(point))
		{
			PropertyBase * prop=GetProperty(m_SelectedIndex);
            if(prop->GetReadOnly()==TRUE)
            {
                bHandled = FALSE;
                return 0;
            }

			if(m_ButtonPressed==TRUE && GetExPropEdit(prop->GetType()))
			{	
				CRect rc(GetPropRect(m_SelectedIndex));
				m_ButtonPressed=FALSE;
				CClientDC dc(m_hWnd);
				DrawButton(dc,rc,FALSE);
				GetExPropEdit(prop->GetType())(m_hWnd,prop,NULL);
			}
		}
		bHandled = FALSE;
		return 0;
}

LRESULT CPropertyList::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch( wParam )
	{
	case VK_UP:
		if(m_SelectedIndex==0)
		{
			bHandled=TRUE;
			return 0;
		}
		break;
	case VK_DOWN:

		if(m_SelectedIndex==(GetCount()-1))
		{
			bHandled=TRUE;
			return 0;
		}
		break;
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CPropertyList::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
	//TODO destroy prop editor
	if(GetFocus()!=m_hWnd && ::IsWindow(GetWindow(GW_CHILD)))
		SetFocus();

	if(m_Tracker.GetPos()==0 && LOWORD(lParam)!=0)
		m_Tracker.SetPos(LOWORD(lParam)/2);

	handled=FALSE;
	return 0;
}

LRESULT CPropertyList::OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	SetBkColor((HDC)wParam,::GetSysColor(COLOR_BTNFACE));
	SetTextColor((HDC)wParam,RGB(0,0,0));
	handled=TRUE;
	return (LRESULT)(HBRUSH)m_bkgBrush;
}

LRESULT CPropertyList::OnSelChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/)
{
	if(hWndCtl==m_hWnd && m_SelectedIndex!=GetCurSel())
	{
		if(GetFocus()!=m_hWnd)
			SetFocus();

		CRect rc;
		rc=GetPropRect(m_SelectedIndex);
		InvalidateRect(&rc,FALSE);

		m_SelectedIndex=GetCurSel();
		if(m_SelectedIndex!=-1)
		{
			rc=GetPropRect(m_SelectedIndex);
			InvalidateRect(&rc,FALSE);
			rc.left=m_Tracker.GetPos();
			DoEditItem(m_SelectedIndex,rc,CPoint(-1,-1));
		}
	}

	return 0;
}

LRESULT CPropertyList::OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CDCHandle dc((HDC)wParam);
	CRect rc;
	GetClientRect(&rc);
    dc.FillSolidRect(&rc,::GetSysColor(COLOR_BTNFACE));
	return TRUE;
}

void CPropertyList::DeleteItem(DELETEITEMSTRUCT *lpdis)
{
}

void CPropertyList::MeasureItem(MEASUREITEMSTRUCT * lpMeasureItemStruct)
{
}

void CPropertyList::DrawItem(DRAWITEMSTRUCT * lpdis)
{
	if( lpdis->itemID==-1 )
		return;

	CDCHandle dc(lpdis->hDC);

	if(lpdis->itemAction & (ODA_DRAWENTIRE))
	{
		int bkmode=dc.SetBkMode(TRANSPARENT);
		PropertyBase *prop=reinterpret_cast<PropertyBase*>(lpdis->itemData);
		if(prop)
		{
			DrawPropertyRect(dc,lpdis->rcItem,prop,(lpdis->itemState & ODS_SELECTED));
			DrawPropertyValue(dc,lpdis->rcItem,prop);

			if(GetExPropEdit(prop->GetType()))
				DrawButton(dc,lpdis->rcItem);
		}

		DrawHorizLine(dc,lpdis->rcItem);
		{
			CPen pen;
			pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
			CPen oldPen=dc.SelectPen(pen);
			CRect rc;
			GetClientRect(&rc);
			dc.MoveTo(m_Tracker.GetPos(),rc.top);
			dc.LineTo(m_Tracker.GetPos(),rc.bottom);
			dc.SelectPen(oldPen);
		}
		dc.SetBkMode(bkmode);
	}
}

void CPropertyList::DrawPropertyRect(HDC hDC,const CRect & DrawRc,PropertyBase * prop,BOOL Selected)
{
	CDCHandle dc(hDC);
	CRect rc(DrawRc);
	rc.right=m_Tracker.GetPos();

	rc.top+=1;
	rc.bottom-=1;
	rc.left+=1;
	rc.right-=1;
	dc.FillSolidRect(&rc,GetSysColor(COLOR_BTNFACE));
	CString text(prop->GetName());
	int idx=text.ReverseFind('.');
	if(idx!=-1)
		text.Delete(0,idx+1);

	rc.left+=RIGHT_SHIFT*(prop->GetLevel());

	if(prop->HasChild())
	{
		if(prop->GetExpand())
			DrawTransparentBitmap(dc,m_MinusBmp,rc.left+1,rc.top+2, RGB(0xFF,0xFF,0xFF));
		else
			DrawTransparentBitmap(dc,m_PlusBmp,rc.left+1,rc.top+2, RGB(0xFF,0xFF,0xFF));
	}

	rc.left+=12;	

	int txtcolor=dc.SetTextColor(RGB(0,0,0));
	dc.DrawText((LPCTSTR)text,text.GetLength(),&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	dc.SetTextColor(txtcolor);
}

void CPropertyList::DrawPropertyValue(HDC hDC,const CRect & DrawRc,PropertyBase * prop)
{
	CDCHandle dc(hDC);
	CRect rc(DrawRc);
	rc.left=m_Tracker.GetPos();
	rc.left+=1;
	dc.FillSolidRect(&rc,GetSysColor(COLOR_BTNFACE));
	prop->DrawProperty(hDC,rc);
}

void CPropertyList::DrawButton(HDC hDC,const CRect & DrawRc,BOOL Pressed)
{
	CDCHandle dc(hDC);
	CRect rc(DrawRc);
	rc.left=ButtonRect(rc);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	CPen oldPen=dc.SelectPen(pen);

	dc.MoveTo(rc.left,rc.top);
	dc.LineTo(rc.left,rc.bottom);	

	dc.SelectPen(oldPen);

	rc.left+=1;
	rc.bottom-=1;

	if(Pressed==FALSE)
	{
		dc.Draw3dRect(&rc,RGB(255,255,255),RGB(0,0,0));

		rc.left+=1;
		rc.top+=1;
		rc.bottom-=1;
		rc.right-=1;
	}
	dc.FillSolidRect(&rc,GetSysColor(COLOR_BTNFACE));
}

int CPropertyList::ButtonRect(const CRect & rc)
{
	return rc.right-16;
}

void CPropertyList::DrawHorizLine(HDC hDC,const CRect & DrawRc)
{
	CDCHandle dc(hDC);
	CRect rc(DrawRc);
	rc.bottom-=1;
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	CPen oldPen=dc.SelectPen(pen);
	dc.MoveTo(DrawRc.left,rc.bottom);
	dc.LineTo(DrawRc.right,rc.bottom);
	dc.SelectPen(oldPen);
}

void CPropertyList::ResetContent(void)
{
    CloseAllChildren();
	properties=NULL;
	CListBox::ResetContent();
	m_SelectedIndex=-1;
	m_ButtonPressed=FALSE;
}

void CPropertyList::UpdateProperty(const CString & pn)
{
	PropertyBase * tmp;
	for(int i=0;i < GetCount();i++)
	{
		tmp=GetProperty(i);
		if(tmp && tmp->GetName() == pn)
		{
			CRect rc(GetPropRect(i));
			InvalidateRect(&rc,FALSE);
			return;
		}
	}
}

CRect CPropertyList::GetPropRect(int idx)
{
	CRect rc;
	if(idx >= 0 && idx < GetCount())
		GetItemRect(idx,&rc);
	return rc;
}

BOOL CPropertyList::DoEditItem(int index, CRect &EditRc,CPoint & point)
{
	PropertyBase *prop=GetProperty(index);
	if(prop==NULL || prop->GetReadOnly()==TRUE)
		return FALSE;

	CRect rc(EditRc);

	if(GetExPropEdit(prop->GetType()))
		rc.right=ButtonRect(rc);

	InPropEdit ie=GetInPropEdit(prop->GetType());

	if(ie)
	{
		if(::IsWindow(m_propEdit))
			::DestroyWindow(m_propEdit);
		m_propEdit=(*ie)(m_hWnd,rc,prop,point,NULL);
		return TRUE;
	}
	return FALSE;
}

void CPropertyList::InsertProperty(CProperties * p)
{
	if(p==NULL)
	{
		properties=NULL;
		return;
	}

	if(properties==p)
		return;
    
	if(properties != NULL)
		properties->SetTopIndex(GetTopIndex());
	
	CListBox::ResetContent();
	m_SelectedIndex=-1;
	m_ButtonPressed=FALSE;
	properties=p;
    PropertyVectorIter iter;
	for ( iter = properties->begin(); iter != properties->end( ); iter++ )
	{
		if((*iter)->GetPublished()==TRUE)
		{
			int index=AddString((*iter)->GetName());
			SetItemDataPtr(index,*iter);
			if((*iter)->GetExpand())
			{
				InsertSubProperty(index,(*iter));
			}
		}
	}
	SetTopIndex(properties->GetTopIndex());
}

int CPropertyList::InsertSubProperty(int Index,PropertyBase * prop)
{
	int Level=prop->GetLevel()+1;
	int i=0;

    PropertyVectorIter iter;
	for ( iter = prop->GetChild().begin(); iter != prop->GetChild().end( ); iter++ )
	{
		if((*iter)->GetPublished()==TRUE)
		{
			CString name;
			name.Format(_T("%s.%s"),prop->GetName(),(*iter)->GetName());
			int idx=InsertString(Index+i+1,name);
			(*iter)->SetLevel(Level);
			SetItemDataPtr(Index+i+1,(*iter));
			if((*iter)->GetExpand())
				i=InsertSubProperty(idx,(*iter));
			i++;
		}
	}
	return i;
}

void CPropertyList::RemoveSubProperty(int Index,PropertyBase * prop)
{
	PropertyVectorIter iter;
	for ( iter = prop->GetChild().begin(); iter != prop->GetChild().end( ); iter++ )
	{
		if((*iter)->GetExpand())
		{
			RemoveSubProperty(Index+1,(*iter));
			(*iter)->SetExpand(FALSE);
		}
		(*iter)->SetLevel(0);
		DeleteString(Index+1);
	}
}

BOOL CPropertyList::DoClickTest(CPoint &pt)
{
	if(pt.x <= m_Tracker.GetPos())
		return TRUE;
	return FALSE;
}

BOOL CPropertyList::DoButtonTest(CPoint & pt)
{
	m_SelectedIndex=GetCurSel();

	if(m_SelectedIndex==-1)
		return FALSE;

	PropertyBase * prop=GetProperty(m_SelectedIndex);

	if(prop==NULL)
		return FALSE;

	CRect rc=GetPropRect(m_SelectedIndex);

	if(ButtonRect(rc) <= pt.x && GetExPropEdit(prop->GetType()))
	{
		if(m_ButtonPressed==FALSE)
		{
			CClientDC dc(m_hWnd);
			DrawButton(dc,rc,TRUE);
		}
		m_ButtonPressed=TRUE;
		return TRUE;
	}
	return FALSE;
}

CString CPropertyList::GetPropertyName(int idx)
{
	return idx >= 0 && idx < GetCount() ? reinterpret_cast<PropertyBase*>(GetItemData(idx))->GetName() : _T("");
}

PropertyBase* CPropertyList::GetProperty(int idx)
{
	return idx >= 0 && idx < GetCount() ? reinterpret_cast<PropertyBase*>(GetItemData(idx)) : NULL;
}

LRESULT CPropertyList::OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    int zDelta = ((short)HIWORD(wParam)/WHEEL_DELTA)*(-1);
    if (zDelta<0)
        SendMessage(WM_VSCROLL,SB_LINEUP,0);
    if (zDelta>0)
        SendMessage(WM_VSCROLL,SB_LINEDOWN,0);

    bHandled = TRUE;
    return 0;
}

static BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
{
    ::DestroyWindow(hwndChild); 
    return TRUE;
}

void CPropertyList::CloseAllChildren()
{
    EnumChildWindows(m_hWnd, EnumChildProc, NULL); 
}
//////////////////////////////////////////////////////////////////////////
