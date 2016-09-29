// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "component.h"
#include "DesignerCtrl.h"
#include "GDIUtil.h"
#include "EventLib.h"
#include "Command.h"
#include <_util.h>
#include <math.h>
#include "resource.h"

#define MIN_DIST 2

#define MOVEX(sign) isShowgrid ? gridDim.cx*sign : 1*sign
#define MOVEY(sign) isShowgrid ? gridDim.cy*sign : 1*sign
/////////////////////////////////////////////////////////////////////////////
// CDesignerCtrl
long DistPointSeg(CPoint &point,CPoint &pn,CPoint &pk);
PROPERTY_API BOOL IsPasteEnabled();

CDesignerCtrl::CDesignerCtrl():components(NULL),isShowgrid(TRUE),gridDim(6,6),isGridPressed(FALSE),
isShowGoldenGrid(FALSE),FromLeftToRight(TRUE),FromTopToBottom(TRUE),isGoldenGridMoveable(FALSE),
componentCreated(FALSE),curentComp(NULL),offset(0,0),tabIndexMode(FALSE),tabIndex(0)
{
}

CDesignerCtrl::~CDesignerCtrl()
{
}
/////////////////////////////////////////////////////////////////////////////
HWND CDesignerCtrl::Create(Component * _Parent,Components * c)
{
	Parent=_Parent;
	CRect rc;
	::GetClientRect((HWND)Parent->GetHandle(),&rc);
	if (CWindowImpl<CDesignerCtrl, CWindow>::Create((HWND)Parent->GetHandle(),rc,NULL,WS_CHILD|WS_VISIBLE,WS_EX_TOPMOST|WS_EX_TRANSPARENT,DESIGNERCTRL_ID)!=NULL)
	{
		components=c;
		//SetFocus();
        CalculateGoldenXY();
        EnableTrackMenu(TRUE);
        SetMenuID(IDR_FORM);
	}
	return m_hWnd;
}

LRESULT CDesignerCtrl::OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return TRUE;
}

LRESULT CDesignerCtrl::OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	BOOL shift = GetKeyState(VK_SHIFT) & 0x8000;
	BOOL ctrl = GetKeyState(VK_CONTROL) & 0x8000;
	switch (wParam)
	{
	case VK_DELETE:
        {   
            CMsgPump msgPump; 
			components->Delete();
            ::RedrawWindow((HWND)GetParentForm()->GetHandle(),NULL,NULL,RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_INTERNALPAINT);
            SendEvent(evAddUndo,Parent);
            PostEvent(evSetActiveForm,GetParentForm());
			break;
        }
	case VK_UP:
		if(shift != 0)
			components->IncrementSize(0,MOVEY(-1),ctrl == 0);
		else
			components->IncrementMove(0,MOVEY(-1));
		break;
			
	case VK_DOWN:
		if(shift != 0) 
			components->IncrementSize(0,MOVEY(1),ctrl == 0);
		else
			components->IncrementMove(0,MOVEY(1));
		break;
			
	case VK_LEFT:
		if(shift != 0)
			components->IncrementSize(MOVEX(-1),0,ctrl == 0);
		else
			components->IncrementMove(MOVEX(-1),0);
		break;
			
	case VK_RIGHT:
		if(shift != 0)
			components->IncrementSize(MOVEX(1),0,ctrl == 0);
		else
			components->IncrementMove(MOVEX(1),0);
		break;
	case VK_TAB:
		{
			int idx=components->GetFirstSelIdx();
			if(idx!=-1)
			{
				idx=idx < components->GetCount()-1 ? idx+1 : 0;
				components->UnselectAll();
				components->GetAt(idx)->Selected=TRUE;
				components->GetAt(idx)->FirstSelected=TRUE;
				components->Invalidate();
			}
		}
		break;
		}

	BringToTop();

	return 1;
}

LRESULT CDesignerCtrl::OnKeyUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
    switch (wParam)
    {
        case VK_UP:
        case VK_DOWN:
        case VK_LEFT:
        case VK_RIGHT:
            SendEvent(evAddUndo,Parent);
        break;
        case VK_SHIFT:
            if(componentCreated == TRUE)
                PostEvent(evResetSelectedComponent);
            break;
    };
	BringToTop();
    return 1;
}

LRESULT CDesignerCtrl::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    downPoint=LParamToPoint(lParam);
    if(tabIndexMode)
    {
        if(components->SetTabIndex(downPoint,tabIndex))
        {
            SendEvent(evAddUndo,Parent);
            ::RedrawWindow((HWND)Parent->GetHandle(),NULL,NULL,RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_INTERNALPAINT);
        }
        else
            SetTabIndexMode(FALSE);
    }
    else
    {
        if(IsGoldenGrid(downPoint)==TRUE && isShowGoldenGrid==TRUE && isGoldenGridMoveable==TRUE)
        {
            deltaPoint=downPoint;
            isGridPressed=TRUE;
        }
        else
		{
            components->MouseDown(downPoint);
        }
    }
    SetCapture();
	//BringToTop();
	return 0;
}

LRESULT CDesignerCtrl::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    if(isGridPressed==FALSE)
    {
		CPoint pt=LParamToPoint(lParam)
	    components->MouseUp(pt);
        if(downPoint.x!=pt.x || downPoint.y!=pt.y || componentCreated == TRUE)
            SendEvent(evAddUndo,Parent);
    }
    else
    {
        offset+=deltaPoint=LParamToPoint(lParam)-deltaPoint;
        MoveGoldenXY(deltaPoint);
        ::RedrawWindow((HWND)Parent->GetHandle(),NULL,NULL,RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_INTERNALPAINT);
        UpdateProperty(_T("OffsetX"));
        UpdateProperty(_T("OffsetY"));
    }

    if((GetKeyState(VK_LSHIFT) & 0x100 || GetKeyState(VK_RSHIFT) & 0x100)==FALSE)
        componentCreated=FALSE;

    isGridPressed=FALSE;
	ReleaseCapture();
	BringToTop();
	return 0;
}

LRESULT CDesignerCtrl::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    CPoint currPoint=LParamToPoint(lParam);

	{
		CPoint pt(currPoint);
		ClientToScreen(&pt);
		::ScreenToClient(GetParent(), &pt);

		pt=SnapToGrid(pt);
	}

    if(isGridPressed==TRUE)
    {
        offset+=deltaPoint=currPoint-deltaPoint;
        MoveGoldenXY(deltaPoint);
        deltaPoint=currPoint;
        ::RedrawWindow((HWND)Parent->GetHandle(),NULL,NULL,RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_INTERNALPAINT);
        UpdateProperty(_T("GSGuides.OffsetX"));
        UpdateProperty(_T("GSGuides.OffsetY"));
    }
    else
    {
	    components->MouseMove(currPoint);
    }
	return 0;
}

LRESULT CDesignerCtrl::OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CDesignerCtrl::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);
    CalculateGoldenXY();
    MoveGoldenXY(offset);
    PaintGoldenGrid(dc);
    ShowTabIndexes(dc);
    components->Paint(dc);
    
	return 0;
}

LRESULT CDesignerCtrl::OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	BringToTop();
	bHandled = FALSE;
	return TRUE;
}

LRESULT CDesignerCtrl::OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    if( wParam != SIZE_MINIMIZED )
    {
		BringToTop();
        CalculateGoldenXY();
        MoveGoldenXY(offset);
    }
   
    return 0;
}

Component  * CDesignerCtrl::GetParentForm()
{
	return Parent;
}

Components * CDesignerCtrl::GetComponents()
{
	return components;
}

void CDesignerCtrl::PaintGoldenGrid(CDC & hdc)
{
    if(isShowGoldenGrid==FALSE)
        return;
    if(xGolden.size()==0 || yGolden.size()==0)
        return;
    CRect rc(xGolden.front(),yGolden.front(),xGolden.back(),yGolden.back());

    hdc.SelectClipRgn(NULL);

    CROP rop(hdc,R2_XORPEN);
    CPenEx pen(PS_SOLID,1,RGB(0x0FF,0x0FF,0x7F));
    CSel penObj(hdc,pen);
    for(size_t x=0; x < xGolden.size();++x)
    {
        hdc.MoveTo(xGolden[x],rc.top);
        hdc.LineTo(xGolden[x],rc.bottom);
    }

    for(size_t y=0; y < yGolden.size();++y)
    {
        hdc.MoveTo(rc.left,yGolden[y]);
        hdc.LineTo(rc.right,yGolden[y]);
    }
}

BOOL CDesignerCtrl::IsGoldenGrid(CPoint & at)
{
    if(xGolden.size()==0 || yGolden.size()==0)
        return FALSE;
    CRect rc(xGolden.front(),yGolden.front(),xGolden.back(),yGolden.back());

    for(size_t x=0; x < xGolden.size();x++)
    {
        if(DistPointSeg(at,CPoint(xGolden[x],rc.top),CPoint(xGolden[x],rc.bottom)) < MIN_DIST)
            return TRUE;
    }
    
    for(size_t y=0; y < yGolden.size();y++)
    {
        if(DistPointSeg(at,CPoint(rc.left,yGolden[y]),CPoint(rc.right,yGolden[y])) < MIN_DIST)
            return TRUE;
    }
    
    return FALSE;
}

int CDesignerCtrl::FindXSide(CPoint & at)
{
    if(xGolden.size()==0 || yGolden.size()==0)
        return FALSE;
    CRect rc(xGolden.front(),yGolden.front(),xGolden.back(),yGolden.back());

    long delta=0x7FFFFFFF;   
    int idx=-1;
    for(size_t x=0; x < xGolden.size();x++)
    {
        long temp;
        if((temp=DistPointSeg(at,CPoint(xGolden[x],rc.top),CPoint(xGolden[x],rc.bottom))) < delta)
        {
            delta=temp;
            idx=(int)x;
        }
    }
    return idx;
}

int CDesignerCtrl::FindYSide(CPoint & at)
{
    if(xGolden.size()==0 || yGolden.size()==0)
        return FALSE;
    CRect rc(xGolden.front(),yGolden.front(),xGolden.back(),yGolden.back());

    long delta=0x7FFFFFFF;   
    int idx=-1;
    for(size_t y=0; y < yGolden.size();y++)
    {
        long temp;
        if((temp=DistPointSeg(at,CPoint(rc.left,yGolden[y]),CPoint(rc.right,yGolden[y]))) < delta)
        {
            delta=temp;
            idx=(int)y;
        }
    }
    
    return idx;
}

void CDesignerCtrl::MoveGoldenXY(CPoint &xy)
{
    for(size_t x=0; x < xGolden.size();x++)
        xGolden[x]=xGolden[x]+xy.x;
    
    for(size_t y=0; y < yGolden.size();y++)
        yGolden[y]=yGolden[y]+xy.y;
}

void CDesignerCtrl::CalculateGoldenXY()
{
    xGolden.clear();
    yGolden.clear();
    
    CRect rc;
    GetClientRect(&rc);
    
    if(rc.Width() < 20 || rc.Height() < 20)
        return;

    xGolden.push_back(rc.right);
    for(double x=(double)rc.right; x > 8.0; )
    {
        x*=0.618;
        if(FromLeftToRight)
            xGolden.push_back(_round(x));
        else
            xGolden.push_back(rc.right-_round(x));
    }
    xGolden.push_back(rc.left);

    yGolden.push_back(rc.top);
    for(double y=(double)rc.bottom; y > 8.0; )
    {
        y*=0.618;
        if(FromTopToBottom)
            yGolden.push_back(_round(y));
        else
            yGolden.push_back(rc.bottom-_round(y));
    }
    yGolden.push_back(rc.bottom);

    
    std::sort(xGolden.begin(),xGolden.end());
    std::sort(yGolden.begin(),yGolden.end());
}

void CDesignerCtrl::PaintGrid(CDC & dc,COLORREF bkColor)
{
    CRect rc;
    ::GetClientRect(GetParent(),&rc);
	::ClientToScreen(GetParent(), &rc.TopLeft());
  	::ClientToScreen(GetParent(), &rc.BottomRight());
  	ScreenToClient(rc);

    bkColor=::GetSysColor(bkColor);

    if(IsShowGrid()==TRUE && gridDim.cx > 0 && gridDim.cy >0)
    {
        CPaintDCEx pdc(dc,rc);
        pdc.FillSolidRect(&rc,bkColor);
        pdc.SetROP2(R2_NOT);
        for (int x = 0; x <= rc.right; x += gridDim.cx)
            for (int y = 0; y < rc.bottom; y += gridDim.cy)
                pdc.SetPixel(x, y, RGB(0xFF,0xFF,0xFF));
    }
    else
        dc.FillSolidRect(&rc,bkColor);
}

void CDesignerCtrl::SetTabIndexMode(BOOL val)
{
    tabIndexMode=val;
    if(tabIndexMode)
        tabIndex=0;
    ::RedrawWindow((HWND)Parent->GetHandle(),NULL,NULL,RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_ALLCHILDREN|RDW_INTERNALPAINT);
}

BOOL CDesignerCtrl::GetTabIndexMode()
{
    return tabIndexMode;
}

void CDesignerCtrl::ShowTabIndexes(CDC & dc)
{
    if(tabIndexMode==FALSE)
        return;

    CRect rc;
    Component * comp;
    CString str;
    CFontEx font;
    CSel _font(dc,font);
    CTextColor textColor(dc,RGB(0xFF,0xFF,0xFF));
    CBackColor backColor(dc,RGB(128,128,0));

    for(int i=0; i < components->GetCount(); i++)
    {
        comp=components->GetAt(i);
        if(comp->EnableTabIndex()==TRUE && comp->IsControl() == TRUE)
        {
            rc=comp->GetBoundsRect();
            comp->ComponentToDesigner(rc);
            str.Format(_T(" %u "),comp->get_TabIndex());
            dc.DrawText(str,str.GetLength(),&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        }
    }
}

CRect CDesignerCtrl::SnapToGrid(const CRect &rc)
{
	CRect ret(rc);
    if (IsShowGrid())
    {   
		CSize sz = GetGridSize();
        ret.left = ((rc.left + sz.cx / 2 )/ sz.cx) * sz.cx;
        ret.top = ((rc.top + sz.cy / 2) / sz.cy) * sz.cy;
        ret.right = ((rc.right + sz.cx / 2) / sz.cx) * sz.cx;
        ret.bottom = ((rc.bottom + sz.cy / 2) / sz.cy) * sz.cy;
    }
	return rc;
}

CPoint CDesignerCtrl::SnapToGrid(const CPoint &xy)
{
	CPoint ret(xy);
    if (IsShowGrid())
    {
		CSize sz = GetGridSize();
		ret.x = ((xy.x + sz.cx / 2) / sz.cx) * sz.cx;
		ret.y = ((xy.y + sz.cy / 2) / sz.cy) * sz.cy;
    }
	return ret;
}

LRESULT CDesignerCtrl::OnUpdateDesigner(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
    ::RedrawWindow(m_hWnd,NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_INTERNALPAINT);
    return 0;
}

void CDesignerCtrl::CustomizeMenu(CMenuHandle & menu,CPoint & at)
{
    downPoint=at;
	ClientToScreen(&at);
	::ScreenToClient(GetParent(), &at);

	components->UnselectAll();
	curentComp = components->SelectComponentFromPt(downPoint);
	if (curentComp)
	{
		curentComp->Selected = TRUE;
		curentComp->FirstSelected = TRUE;
	}


	menu.EnableMenuItem(ID_EDIT_CUT, (curentComp != NULL ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);
	menu.EnableMenuItem(ID_EDIT_COPY, (curentComp != NULL ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);
	menu.EnableMenuItem(ID_EDIT_CLEAR, (curentComp != NULL ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);
	menu.EnableMenuItem(ID_EDIT_SELECT_ALL, (components->GetCount() != 0 ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);

    if(curentComp==NULL)
        curentComp=Parent;
	menu.EnableMenuItem(ID_EDIT_PASTE, (IsPasteEnabled() ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);
}

LRESULT CDesignerCtrl::OnEditCommand(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    SendEvent(evOnEditCommand,wID,curentComp,&downPoint);
    curentComp=NULL;
    return 0;
}

void CDesignerCtrl::ShowGrid(BOOL val)
{
    isShowgrid=val;
}

BOOL CDesignerCtrl::IsShowGrid()
{
    return isShowgrid;
}


void CDesignerCtrl::ShowGSGuides(BOOL val)
{
    isShowGoldenGrid=val;
}

BOOL CDesignerCtrl::IsShowGSGuides()
{
    return isShowGoldenGrid;
}

void CDesignerCtrl::SetMoveableGSGuides(BOOL val)
{
    isGoldenGridMoveable=val;
}

BOOL CDesignerCtrl::IsMoveableGSGuides()
{
    return isGoldenGridMoveable;
}

CSize & CDesignerCtrl::GetGridSize()
{
    return gridDim;
}

void CDesignerCtrl::SetFromTopToBottom(BOOL val)
{
    if(val!=FromTopToBottom)
    {
        FromTopToBottom=val;
        CalculateGoldenXY();
        MoveGoldenXY(offset);
    }
}

BOOL CDesignerCtrl::GetFromTopToBottom()
{
    return FromTopToBottom;
}

void CDesignerCtrl::SetFromLeftToRight(BOOL val)
{
    if(val!=FromLeftToRight)
    {
        FromLeftToRight=val;
        CalculateGoldenXY();
        MoveGoldenXY(offset);
    }
}

BOOL CDesignerCtrl::GetFromLeftToRight()
{
    return FromLeftToRight;
}

void CDesignerCtrl::SetOffset(CPoint val)
{
    if(isGoldenGridMoveable)
    {
        offset=val;
        CalculateGoldenXY();
        MoveGoldenXY(offset);
    }
}

CPoint CDesignerCtrl::GetOffset()
{
    return offset;
}

void CDesignerCtrl::SetComponentCreated()
{
    componentCreated=TRUE;
}

void CDesignerCtrl::BringToTop()
{
	CRect rc;
	::GetClientRect((HWND)GetParentForm()->GetHandle(),&rc);
	SetWindowPos(HWND_TOPMOST/*HWND_TOP*/,rc.left,rc.top,rc.right,rc.bottom,SWP_NOMOVE|SWP_NOREDRAW|SWP_NOSIZE);
	//SetFocus();	
}
////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long Distanse(CPoint & pt1,CPoint & pt2)
{
    return _round(_hypot(double(max(pt1.x,pt2.x)-min(pt1.x,pt2.x)),
        double(max(pt1.y,pt2.y)-min(pt1.y,pt2.y))));
}
////////////////////////////////////////////////////////////////////////////////////////////////
long DistPointSeg(CPoint &point,CPoint &pn,CPoint &pk)
// point - точка, pn,pk - начало и конец отрезка, prj - проекция точки на прямую (pn,pk)
// return: расстояние от точки до отрезка
{
    CPoint ppr;  // проекция точки на прямую (pn,pk)
    long dx,dy;
    double delta,delta1,delta2;
    
    if (pn==pk)
    {
        return Distanse(point,pn);
    }
    
    dx=(long)(pk.x-pn.x);  dy=(long)(pk.y-pn.y);
    delta1=(double)((long)(point.x-pn.x)*dx+(long)(point.y-pn.y)*dy);
    delta2=(double)((long)(pk.x-point.x)*dx+(long)(pk.y-point.y)*dy);
    delta=delta1+delta2;
    ppr.x=(unsigned long)((delta2*(double)pn.x+delta1*(double)pk.x)/delta);
    ppr.y=(unsigned long)((delta2*(double)pn.y+delta1*(double)pk.y)/delta);
    
    if (ppr.x >= min(pn.x,pk.x) && ppr.x <= max(pn.x,pk.x) && // проекция точки
        ppr.y >= min(pn.y,pk.y) && ppr.y <= max(pn.y,pk.y))   // лежит на отрезке
        return Distanse(point,ppr);
    else  // проекция точки не лежит на отрезке
        return min(Distanse(point,pn),Distanse(point,pk));
}  

