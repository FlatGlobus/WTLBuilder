// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "Text3d.h"

/////////////////////////////////////////////////////////////////////////////
CText3d::CText3d(void)
{
	bkcolor=::GetSysColor(COLOR_BTNFACE);//FW_NORMAL
	font.CreateFont(-12, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, VARIABLE_PITCH | FF_ROMAN, _T("MS Sans Serif"));
}

CText3d::~CText3d()
{
}

//int CText3d::Create(DWORD style, const CRect& rect, HWND pParentWnd, UINT id)   
//{
//	Init();
//	return Create(NULL, NULL, style, rect, pParentWnd, id);
//}

LRESULT CText3d::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	CRect rc;
	GetClientRect(&rc);
	CText3d* pT = static_cast<CText3d*>(this);
	if(wParam != NULL)
	{
		Draw((HDC)wParam,rc);
	}
	else
	{
		CPaintDC dc(m_hWnd);
		Draw(dc.m_hDC,rc);
	}
	return 0;
}

LRESULT CText3d::OnEraseBackground(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	return TRUE;
}

void CText3d::SetCaption(const CString & str)
{
	if (caption != str)
	{
		caption = str;
		Invalidate();
	}
}

const CString & CText3d::GetCaption(void)
{
	return caption;
}

void CText3d::SetTextColor(COLORREF c)
{
	if(textcolor!=c)
	{
		textcolor=c;
		Invalidate();
	}
}

COLORREF CText3d::GetTextColor(void)
{
	return textcolor;
}

void CText3d::SetBkColor(COLORREF c)
{
	if(bkcolor!=c)
	{
		bkcolor=c;
		Invalidate();
	}
}

COLORREF CText3d::GetBkColor(void)
{
	return bkcolor;
}

void CText3d::SetShadowColor(COLORREF c)
{
	if(shadowcolor!=c)
	{
		shadowcolor=c;
		Invalidate();
	}
}

COLORREF CText3d::GetShadowColor(void)
{
	return shadowcolor;
}

void CText3d::SetTextType(long val)
{
	if(textType!=val)
	{
		textType=val;
		Invalidate();
	}
}

long CText3d::GetTextType(void)
{
	return textType;
}

void CText3d::SetShift(long val)
{
	if(shift!=val)
	{
		shift=val;
		Invalidate();
	}
}

long CText3d::GetShift(void)
{
	return shift;
}

CFont & CText3d::GetFont(void)
{
	return font;
}

void CText3d::SetFont(CFont &f, BOOL bRedraw)
{
	if (f)
	{
		font.DeleteObject();
		font.Attach(f);
		if (::IsWindow(m_hWnd))
			CWindowImpl< CText3d, CWindow, CControlWinTraits >::SetFont(f, bRedraw);
	}
}

void CText3d::Draw(HDC DC, const CRect& rect)
{
	int l = caption.GetLength();
	if(l==0)
		return;
	CRect rectClient = rect;
	DoGradientFill(DC,rectClient);

	CDCHandle dc(DC);
	CSize textSizeClient;
	CFont pFontOld=dc.SelectFont(font);
	dc.GetTextExtent(caption, l,&textSizeClient);
	
	int minx = rectClient.left+ (rectClient.Width() - textSizeClient.cx)/2;
	int miny = rectClient.top+ (rectClient.Height() - textSizeClient.cy)/2;
	
	int oldBkMode = dc.SetBkMode(TRANSPARENT);
	
	COLORREF oldTextColor = dc.SetTextColor(textcolor);
	
	int cx = minx;
	int cy = miny;
	if (textType==ThreeDText)
	{
		cx += 3;
		cy += 3;
		
		// draw 3D highlights
		dc.SetTextColor(::GetSysColor(COLOR_3DDKSHADOW));
		dc.TextOut(cx - shift*2, cy + shift*2, caption);
		dc.TextOut(cx + shift*2, cy - shift*2, caption);
		dc.TextOut(cx + shift*2, cy + shift*2, caption);
		dc.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
		dc.TextOut(cx + shift*1, cy - shift*2, caption);
		dc.TextOut(cx - shift*2, cy + shift*1, caption);
		dc.TextOut(cx - shift*2, cy - shift*2, caption);
		dc.SetTextColor(::GetSysColor(COLOR_3DSHADOW));
		dc.TextOut(cx - shift*1, cy + shift*1, caption);
		dc.TextOut(cx + shift*1, cy - shift*1, caption);
		dc.TextOut(cx + shift*1, cy + shift*1, caption);
		dc.SetTextColor(::GetSysColor(COLOR_3DLIGHT));
		dc.TextOut(cx, cy - shift*1, caption);
		dc.TextOut(cx - shift*1, cy, caption);
		dc.TextOut(cx - shift*1, cy - shift*1, caption);
		dc.SetTextColor(textcolor);
	}
	else
		if(textType==ShadowText)
		{
			dc.SetTextColor(shadowcolor);
			dc.TextOut(cx+shift, cy+shift, caption);
		}
		
		// draw the text
		dc.SetTextColor(textcolor);	
		dc.TextOut(cx, cy, caption);
		
		// restore DC
		dc.SetTextColor(oldTextColor);
		dc.SetBkMode(oldBkMode);
		dc.SelectFont(pFontOld);
}

void CText3d::DoGradientFill(HDC DC, CRect &rc)
{
	CDCHandle dc(DC);
	// This will make 2^6 = 64 fountain steps
	int nShift = 6;
	int nSteps = 1 << nShift;
	for( int i = 0; i < nSteps; i++ ) {
		// Do a little alpha blending
		BYTE bR = (BYTE) ((GetRValue(colorLeft) * (nSteps - i) +
			GetRValue(colorRight) * i) >> nShift);
		BYTE bG = (BYTE) ((GetGValue(colorLeft) * (nSteps - i) +
			GetGValue(colorRight) * i) >> nShift);
		BYTE bB = (BYTE) ((GetBValue(colorLeft) * (nSteps - i) +
			GetBValue(colorRight) * i) >> nShift);
		
		CBrush br;
		br.CreateSolidBrush( RGB(bR,bG,bB) );
		// then paint with the resulting color
		RECT r2 = rc;
		//if( m_bHorizontal ) {
         //   r2.bottom = rc.bottom - ((i * (rc.bottom-rc.top)) >> nShift);
           // r2.top = rc.bottom - (((i + 1) * (rc.bottom-rc.top)) >> nShift);
            //if( (r2.bottom-r2.top) > 0 ) dc.FillRect(&r2, br);
		//}
		//else {
            r2.left = rc.left + ((i * (rc.right-rc.left)) >> nShift);
            r2.right = rc.left + (((i + 1) * (rc.right-rc.left)) >> nShift);
            if( (r2.right-r2.left) > 0 ) dc.FillRect(&r2, br);
		//}
	}
}
