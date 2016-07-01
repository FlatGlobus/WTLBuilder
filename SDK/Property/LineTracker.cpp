// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "LineTracker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineTracker::CLineTracker(void):m_Parent(NULL),m_Pressed(FALSE),m_Pos(0)
{
    m_Cursor=::LoadCursor(NULL,IDC_SIZEWE);
}

CLineTracker::~CLineTracker()
{

}

void CLineTracker::SetParent(HWND p)
{
    m_Parent=p;
	CRect rc(GetParentDim());
	m_Pos=(rc.left+rc.right)/2;
}

void CLineTracker::MouseDown(const CPoint &pt)
{
	CRect rc(GetParentDim());
    if(!rc.PtInRect(pt))
        return; 

    m_OldCursor=SetCursor(m_Cursor);

    m_Pressed=TRUE;
    m_Pos=pt.x;

    Draw(m_Pos);
}

void CLineTracker::MouseMove(const CPoint &pt)
{
    CheckPos(pt);

    if(m_Pressed==TRUE)
    {
		CRect rc(GetParentDim());
        if(!rc.PtInRect(pt))
			return; 

        SetCursor(m_Cursor);

        Draw(m_Pos);

        m_Pos=pt.x;

        Draw(m_Pos);
    }
}

void CLineTracker::MouseUp(const CPoint &pt)
{
    m_Pressed=FALSE;
    Draw(m_Pos);

	CRect rc(GetParentDim());
    if(!rc.PtInRect(pt))
    {
		m_Pos=pt.x;
		Draw(m_Pos);
    }
    SetCursor(m_OldCursor);
}

int CLineTracker::GetPos()
{
    return m_Pos;
}

void CLineTracker::SetPos(int p)
{
	CRect rc(GetParentDim());
    if(rc.left <= p && p <= rc.right)
        m_Pos=p;
}

void CLineTracker::Draw(int p)
{
    CClientDC dc(m_Parent);

	CRect rc(GetParentDim());

    int bkmode=dc.SetBkMode(TRANSPARENT);
    int rop=dc.SetROP2(R2_NOT);

    CPen pen;
	pen.CreatePen(PS_DOT,1,RGB(255,255,255));
    CPen oldPen=dc.SelectPen(pen);

	dc.MoveTo(p,rc.top);
	dc.LineTo(p,rc.bottom);

    dc.SelectPen(oldPen);

    dc.SetROP2(rop);
    dc.SetBkMode(bkmode); 
}

BOOL CLineTracker::CheckPos(const CPoint &pt)
{
    if(((m_Pos-1) <= pt.x) && (pt.x <= (m_Pos+1)))
    {
        SetCursor(m_Cursor);
        return TRUE;
    }
    return FALSE;       
}

CRect CLineTracker::GetParentDim(void)
{
	CRect rc;
	if(m_Parent && ::IsWindow(m_Parent))
		GetClientRect(m_Parent,&rc);
	return rc;
}