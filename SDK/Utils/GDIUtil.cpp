// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "gdiutil.h"
#ifdef __WTLBUILDER__
#include "Property.h"
#include "PropertyListEdit.h"
#endif
//#include <afxdlgs.h>
//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENT_NOTIFY(CPenEx,Notify,notify)
#ifdef __WTLBUILDER__
typedef int PenStyle;
#endif

//REGISTER_LIST_PROPERTY(Bold)
//REGISTER_LIST_PROPERTY(CharSet)
//REGISTER_LIST_PROPERTY(OutPrecision)
//REGISTER_LIST_PROPERTY(ClipPrecision)
//REGISTER_LIST_PROPERTY(Quality)

//REGISTER_LIST_PROPERTY(BrushStyle)
//REGISTER_LIST_PROPERTY(BrushHatch)


CPenEx::CPenEx(void):handle(NULL)
{
	logpen.lopnStyle=PS_SOLID;
	logpen.lopnWidth.x=1;
	logpen.lopnColor=RGB(0,0,0);
}

CPenEx::CPenEx(int style,int width,CColorref color)
{
	handle=CreatePen(style,width,color);
	logpen.lopnStyle=style;
	logpen.lopnWidth.x=width;
	logpen.lopnColor=color;
}

CPenEx::~CPenEx()
{
	if(handle)
		DeleteObject(handle);
}

void CPenEx::set_Style(int s)
{
	logpen.lopnStyle=s;
	DeleteObject(handle);
	handle=CreatePenIndirect(&logpen);
	change(this);
}

int  CPenEx::get_Style(void)
{
	return logpen.lopnStyle;
}

void CPenEx::set_Width(int w)
{
	logpen.lopnWidth.x=w;
	DeleteObject(handle);
	handle=CreatePenIndirect(&logpen);
	change(this);
}

int  CPenEx::get_Width(void)
{
	return logpen.lopnWidth.x;
}

void CPenEx::set_Color(CColorref c)
{
	logpen.lopnColor=c;
	DeleteObject(handle);
	handle=CreatePenIndirect(&logpen);
	change(this);
}

CColorref CPenEx::get_Color(void)
{
	return logpen.lopnColor;
}

CPenEx::operator HPEN()
{
	return handle;
}
#ifdef __WTLBUILDER__
void CPenEx::AddProperty(LPCTSTR Name,CProperties & objprop)
{
	BEGIN_SUB_PROPERTY(Name,CPenEx)
		DEFINE_SUB_PROPERTY(Style,PenStyle,CPenEx,PS_SOLID)
		DEFINE_SUB_PROPERTY(Width,int,CPenEx,1)
		DEFINE_SUB_PROPERTY(Color,CColorref,CPenEx,0)
	END_SUB_PROPERTY
}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
//IMPLEMENT_NOTIFY(CBrushEx,Notify,notify)
CBrushEx::CBrushEx(void):handle(NULL)
{
	logbrush.lbStyle=BS_NULL;
	logbrush.lbHatch=HS_BDIAGONAL;
	logbrush.lbColor=RGB(0xFF,0xFF,0xFF);
}

CBrushEx::CBrushEx(int style,int hatch,CColorref color)
{
	logbrush.lbStyle=style;
	logbrush.lbHatch=hatch;
	logbrush.lbColor=color;
	handle=CreateBrushIndirect(&logbrush);
}

CBrushEx::CBrushEx(CColorref color)
{
	logbrush.lbStyle=BS_SOLID;
	logbrush.lbHatch=0;
	logbrush.lbColor=color;
	handle=CreateBrushIndirect(&logbrush);
}

CBrushEx::~CBrushEx()
{
	if(handle)
		DeleteObject(handle);
}

void CBrushEx::set_Style(long s)
{
	logbrush.lbStyle=s;
	DeleteObject(handle);
	handle=CreateBrushIndirect(&logbrush);
	change(this);
}

long  CBrushEx::get_Style(void)
{
	return logbrush.lbStyle;
}

void CBrushEx::set_Hatch(long h)
{
	logbrush.lbHatch=h;
	DeleteObject(handle);
	handle=CreateBrushIndirect(&logbrush);
	change(this);
}

long  CBrushEx::get_Hatch(void)
{
	return (int)logbrush.lbHatch;
}

void CBrushEx::set_Color(CColorref c)
{
	logbrush.lbColor=c;
	DeleteObject(handle);
	handle=CreateBrushIndirect(&logbrush);
	change(this);
}

CColorref CBrushEx::get_Color(void)
{
	return logbrush.lbColor;
}

CBrushEx::operator HBRUSH()
{
	return handle;
}
#ifdef __WTLBUILDER__
typedef long BrushStyle;
typedef long BrushHatch;
void CBrushEx::AddProperty(LPCTSTR Name,CProperties & objprop)
{
	BEGIN_SUB_PROPERTY(Name,CBrushEx)
		DEFINE_SUB_PROPERTY(Style,BrushStyle,CBrushEx,BS_SOLID)
		DEFINE_SUB_PROPERTY(Hatch,BrushHatch,CBrushEx,0)
		DEFINE_SUB_PROPERTY(Color,CColorref,CBrushEx,RGB(0xFF,0xFF,0xFF))
	END_SUB_PROPERTY
}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
typedef long CharSet;
#endif

CFontEx::CFontEx():handle(NULL)
{
	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	_tcscpy(lf.lfFaceName,_T("MS Sans Serif"));
	
	handle=CreateFontIndirect(&lf);
	fontColor=0;
}

CFontEx::CFontEx(const CString & facename)
{
	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	_tcscpy(lf.lfFaceName, (LPCTSTR)facename);
	
	handle=CreateFontIndirect(&lf);
	
	fontColor=0;
}

CFontEx::CFontEx(LOGFONT& logfont)
{
	memcpy(&lf,&logfont,sizeof(LOGFONT));
	handle=CreateFontIndirect(&lf);
	fontColor=0;
}

CFontEx::CFontEx(CFont *font)
{
	font->GetLogFont(&lf);
	handle=CreateFontIndirect(&lf);
	fontColor=0;
}

CFontEx::CFontEx(CFontEx & font)
{
	font.get_LogFont(lf);
	handle=CreateFontIndirect(&lf);
	fontColor=0;
}

CFontEx::~CFontEx()
{
	if(handle)
		DeleteObject(handle);
}
#ifdef __WTLBUILDER__
typedef CString FontFaceName;

void CFontEx::AddProperty(LPCTSTR Name,CProperties & objprop)
{
	BEGIN_SUB_PROPERTY(Name,CFontEx)
		DEFINE_SUB_PROPERTY(Height,long,CFontEx,get_Height())
		DEFINE_SUB_PROPERTY(Bold,BOOL,CFontEx,get_Bold())
		DEFINE_SUB_PROPERTY(Italic,BOOL,CFontEx,get_Italic())
		DEFINE_SUB_PROPERTY(Underline,BOOL,CFontEx,get_Underline())
		DEFINE_SUB_PROPERTY(StrikeOut,BOOL,CFontEx,get_StrikeOut())
		DEFINE_SUB_PROPERTY(CharSet,CharSet,CFontEx,get_CharSet())
		DEFINE_SUB_PROPERTY(FaceName,FontFaceName,CFontEx,get_FaceName())
	END_SUB_PROPERTY
	//DEFINE_SUB_PROPERTY(Color,COLORREF,CFontEx,GetColor())
}
#endif
void CFontEx::set_Height(long height)
{
	DeleteObject(handle);
	lf.lfHeight=height;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_Width(long width)
{
	DeleteObject(handle);
	lf.lfWidth=width;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_Escapement(long esc)
{
	DeleteObject(handle);
	lf.lfEscapement=esc;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_Orientation(long or)
{
	DeleteObject(handle);
	lf.lfOrientation=or;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_Weight(long weight)
{
	DeleteObject(handle);
	lf.lfWeight=weight;
	handle=CreateFontIndirect(&lf);
	change(this);	
}

void CFontEx::set_CharSet(long charset)
{
	DeleteObject(handle);
	lf.lfCharSet=(BYTE)charset;
	handle=CreateFontIndirect(&lf);
	change(this);	
}

void CFontEx::set_OutPrecision(long op)
{
	DeleteObject(handle);
	lf.lfOutPrecision=(BYTE)op;
	handle=CreateFontIndirect(&lf);
	change(this);	
}

void CFontEx::set_ClipPrecision(long cp)
{
	DeleteObject(handle);
	lf.lfClipPrecision=(BYTE)cp;
	handle=CreateFontIndirect(&lf);
	change(this);	
}

void CFontEx::set_Quality(long qual)
{
	DeleteObject(handle);
	lf.lfQuality=(BYTE)qual;
	handle=CreateFontIndirect(&lf);
	change(this);	
}

void CFontEx::set_PitchAndFamily(long paf)
{
	DeleteObject(handle);
	lf.lfPitchAndFamily=(BYTE)paf;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_FaceName(CString facename)
{
	DeleteObject(handle);
	_tcscpy(lf.lfFaceName,(LPCTSTR)facename);
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_Bold(BOOL B)
{
	if(B)
		set_Weight(FW_BOLD);
	else
		set_Weight(FW_NORMAL);
	change(this);
}

void CFontEx::set_Italic(BOOL i)
{
	DeleteObject(handle);
	lf.lfItalic=i;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_Underline(BOOL u)
{
	DeleteObject(handle);
	lf.lfUnderline=u;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_StrikeOut(BOOL s)
{
	DeleteObject(handle);
	lf.lfStrikeOut=s;
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::set_LogFont(LOGFONT& logfont)
{
	//lf=logfont;
	memcpy(&lf,&logfont,sizeof(LOGFONT));
	DeleteObject(handle);
	handle=CreateFontIndirect(&lf);
	change(this);
}

void CFontEx::get_LogFont(LOGFONT& logfont)
{
	memcpy(&logfont,&lf,sizeof(LOGFONT));
}

long CFontEx::get_Height()
{
	return lf.lfHeight;
}

long CFontEx::get_Width()
{
	return lf.lfWidth;
}

long CFontEx::get_Escapement()
{
	return lf.lfEscapement;
}

long CFontEx::get_Orientation()
{
	return lf.lfEscapement;
}

long CFontEx::get_Weight()
{
	return lf.lfWeight;
}

long CFontEx::get_CharSet()
{
	return lf.lfCharSet;
}

long CFontEx::get_OutPrecision()
{
	return lf.lfOutPrecision;
}

long CFontEx::get_ClipPrecision()
{
	return lf.lfClipPrecision;
}

long CFontEx::get_Quality()
{
	return lf.lfQuality;
}

long CFontEx::get_PitchAndFamily()
{
	return lf.lfPitchAndFamily;
}

CString CFontEx::get_FaceName()
{
	return lf.lfFaceName;
}

BOOL CFontEx::get_Bold()
{
	return lf.lfWeight == FW_BOLD ? TRUE : FALSE;
}

BOOL CFontEx::get_Italic()
{
	return (BOOL)lf.lfItalic;
}

BOOL CFontEx::get_Underline()
{
	return (BOOL)lf.lfUnderline;
}

BOOL CFontEx::get_StrikeOut()
{
	return (BOOL)lf.lfStrikeOut;
}

void CFontEx::set_Color(CColorref color)
{
	fontColor=color;
	change(this);
}

CColorref CFontEx::get_Color(void)
{
	return fontColor;
}

CFontEx::operator HFONT()
{
	return handle;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CSel::CSel(HDC DC, HPEN hPen)
{
	m_hOldGdiObject = NULL;
	m_pDC = NULL;
	
	if(DC)
	{
		ATLASSERT(hPen);
		if(hPen)
		{
			m_pDC = DC;
			m_hOldGdiObject = ::SelectObject(m_pDC,hPen);
		}
	}
}

CSel::CSel(HDC DC, HBRUSH hBrush)
{
	m_hOldGdiObject = NULL;
	m_pDC = NULL;
	
	if(DC)
	{
		ATLASSERT(hBrush);
		if(hBrush)
		{
			m_pDC = DC;
			m_hOldGdiObject = ::SelectObject(m_pDC,hBrush);
		}
	}
}

CSel::CSel(HDC DC, HFONT hFont)
{
	m_hOldGdiObject = NULL;
	m_pDC = NULL;
	
	if(DC)
	{
		m_pDC = DC;
		ATLASSERT(hFont);
		if(hFont)
			m_hOldGdiObject = ::SelectObject(m_pDC,hFont);
		
	}
}

CSel::CSel(HDC DC, int index)
{
	m_hOldGdiObject = NULL;
	m_pDC = NULL;
	
	if(DC)
	{
		m_pDC = DC;
		m_hOldGdiObject = ::SelectObject(m_pDC,::GetStockObject(index));
	}
}

CSel::~CSel()
{
	if(m_hOldGdiObject && m_pDC)
		::SelectObject(m_pDC, m_hOldGdiObject);
	
}
//////////////////////////////////////////////////////////////////////////
void DrawGradientFill(CDC & DC, CRect & pRect, CColorref crStart, CColorref crEnd,int Orient, int nSegments)
{
	if(Orient==grHoriz)
		DrawHorGradientFill(DC,pRect,crStart,crEnd,nSegments);
	else
		DrawVertGradientFill(DC,pRect,crStart,crEnd,nSegments);
}
//////////////////////////////////////////////////////////////////////////
void DrawHorGradientFill(CDC & pDC, CRect &pRect, CColorref crStart, CColorref crEnd, int nSegments)
{
	COLORREF cr;
	int nR = GetRValue(crStart);
	int nG = GetGValue(crStart);
	int nB = GetBValue(crStart);
	
	int neB = GetBValue(crEnd);
	int neG = GetGValue(crEnd);
	int neR = GetRValue(crEnd);
	
	if(nSegments > pRect.Width())
		nSegments = pRect.Width();
	
	int nDiffR = (neR - nR);
	int nDiffG = (neG - nG);
	int nDiffB = (neB - nB);
	
	int ndR = 256 * (nDiffR) / (max(nSegments,1));
	int ndG = 256 * (nDiffG) / (max(nSegments,1));
	int ndB = 256 * (nDiffB) / (max(nSegments,1));
	
	nR *= 256;
	nG *= 256;
	nB *= 256;
	
	neR *= 256;
	neG *= 256;
	neB *= 256;
	
	int nCX = pRect.Width() / max(nSegments,1), nLeft = pRect.left, nRight;
	pDC.SelectStockPen(NULL_PEN);
	
	for (int i = 0; i < nSegments; i++, nR += ndR, nG += ndG, nB += ndB)
	{
		// Use special code for the last segment to avoid any problems
		// with integer division.
		
		if (i == (nSegments - 1))
			nRight = pRect.right;
		else
			nRight = nLeft + nCX;
		
		cr = RGB(nR / 256, nG / 256, nB / 256);
		
		{
			CBrush br;
			br.CreateSolidBrush(cr);
			CRect rc(nLeft, pRect.top, nRight + 1, pRect.bottom);
			pDC.FillRect(&rc, br);
		}
		
		// Reset the left side of the drawing rectangle.
		
		nLeft = nRight;
	}
}
//////////////////////////////////////////////////////////////////////////
void DrawVertGradientFill(CDC & pDC, CRect &pRect, CColorref crStart, CColorref crEnd, int nSegments)
{
	COLORREF cr;
	int nR = GetRValue(crStart);
	int nG = GetGValue(crStart);
	int nB = GetBValue(crStart);
	
	int neB = GetBValue(crEnd);
	int neG = GetGValue(crEnd);
	int neR = GetRValue(crEnd);
	
	if(nSegments > pRect.Height())
		nSegments = pRect.Height();
	
	int nDiffR = (neR - nR);
	int nDiffG = (neG - nG);
	int nDiffB = (neB - nB);
	
	int ndR = 256 * (nDiffR) / (max(nSegments,1));
	int ndG = 256 * (nDiffG) / (max(nSegments,1));
	int ndB = 256 * (nDiffB) / (max(nSegments,1));
	
	nR *= 256;
	nG *= 256;
	nB *= 256;
	
	neR *= 256;
	neG *= 256;
	neB *= 256;
	
	int nCY = pRect.Height() / max(nSegments,1), nTop = pRect.top, nBottom;
	pDC.SelectStockPen(NULL_PEN);
	
	for (int i = 0; i < nSegments; i++, nR += ndR, nG += ndG, nB += ndB)
	{
		// Use special code for the last segment to avoid any problems
		// with integer division.
		
		if (i == (nSegments - 1))
			nBottom = pRect.bottom;
		else
			nBottom = nTop + nCY;
		
		cr = RGB(nR / 256, nG / 256, nB / 256);
		
		{
			CBrush br;
			br.CreateSolidBrush(cr);
			CRect rc(pRect.left, nTop, pRect.right,nBottom + 1);
			pDC.FillRect(&rc, br);
		}
		
		// Reset the left side of the drawing rectangle.
		
		nTop = nBottom;
	}
}
//////////////////////////////////////////////////////////////////////////
void DrawGradientText(CDC &DC,int x, int y, CString & text, CColorref crStart, CColorref crEnd, int Orient,int nSegments)
{
	DC.SetBkMode(TRANSPARENT);
	DC.BeginPath(); 
	
	DC.TextOut(x,y,(LPCTSTR)text,text.GetLength()); 
	DC.CloseFigure();
	EndPath(DC); 
	DC.SelectClipPath(RGN_COPY); 
	SIZE sz;
	DC.GetTextExtent((LPCTSTR)text,text.GetLength(), &sz);
	CRect rc(x,y,x+sz.cx,y+sz.cy);
	DrawGradientFill(DC,rc,crStart,crEnd,Orient,nSegments);
	SelectClipRgn(DC,NULL);
}
//////////////////////////////////////////////////////////////////////////
void DrawTransparentBitmap (HDC hdc, HBITMAP hBitmap, long xStart,
					 long yStart, COLORREF cTransparentColor)
	{
	BITMAP     bm;
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT      ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hBitmap);   // Select the bitmap
	GetObject(hBitmap, sizeof(BITMAP), (LPTSTR)&bm);
	ptSize.x = bm.bmWidth;            // Get width of bitmap
	ptSize.y = bm.bmHeight;           // Get height of bitmap
	DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
	// to logical points

	// Create some DCs to hold temporary data.
	hdcBack   = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem    = CreateCompatibleDC(hdc);
	hdcSave   = CreateCompatibleDC(hdc);
	// Create a bitmap for each DC.

	// Monochrome DC
	bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	// Monochrome DC
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	// Each DC must select a bitmap object to store pixel data.
	bmBackOld   = (HBITMAP) SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP) SelectObject(hdcObject, bmAndObject);
	bmMemOld    = (HBITMAP) SelectObject(hdcMem, bmAndMem);
	bmSaveOld   = (HBITMAP) SelectObject(hdcSave, bmSave);

	// Set proper mapping mode.
	SetMapMode(hdcTemp, GetMapMode(hdc));

	// Save the bitmap sent here, because it will be overwritten.
	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	cColor = SetBkColor(hdcTemp, cTransparentColor);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
		SRCCOPY);

	// Set the background color of the source DC back to the original
	// color.
	SetBkColor(hdcTemp, cColor);

	// Create the inverse of the object mask.
	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
		NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
		SRCCOPY);

	// Mask out the places where the bitmap will be placed.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	// Copy the destination to the screen.
	BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
		SRCCOPY);

	// Place the original bitmap back into the bitmap sent here.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	// Delete the memory bitmaps.
	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	// Delete the memory DCs.
	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
	}

//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__

BEGIN_LIST_PROPERTY(PenStyle)
	LIST_ITEM(PS_SOLID,PS_SOLID) 
	LIST_ITEM(PS_DASH,PS_DASH) 
	LIST_ITEM(PS_DOT,PS_DOT) 
	LIST_ITEM(PS_DASHDOT,PS_DASHDOT) 
	LIST_ITEM(PS_DASHDOTDOT,PS_DASHDOTDOT) 
	LIST_ITEM(PS_INSIDEFRAME,PS_INSIDEFRAME) 
END_LIST_ITEM(PenStyle)

BEGIN_LIST_PROPERTY(BrushStyle)
	LIST_ITEM(BS_SOLID,BS_SOLID) 
	LIST_ITEM(BS_HATCHED,BS_HATCHED) 
	LIST_ITEM(BS_NULL,BS_NULL) 
END_LIST_ITEM(BrushStyle)

BEGIN_LIST_PROPERTY(BrushHatch)
	LIST_ITEM(HS_BDIAGONAL,HS_BDIAGONAL) 
	LIST_ITEM(HS_CROSS,HS_CROSS) 
	LIST_ITEM(HS_DIAGCROSS,HS_DIAGCROSS) 
	LIST_ITEM(HS_FDIAGONAL,HS_FDIAGONAL) 
	LIST_ITEM(HS_HORIZONTAL,HS_HORIZONTAL) 
	LIST_ITEM(HS_VERTICAL,HS_VERTICAL) 
END_LIST_ITEM(BrushHatch)

BEGIN_LIST_PROPERTY(Bold)
	LIST_ITEM_DECORATE(FALSE,FW_NORMAL,false) 
	LIST_ITEM_DECORATE(TRUE,FW_BOLD,true) 
END_LIST_ITEM(Bold)

BEGIN_LIST_PROPERTY(CharSet)
	LIST_ITEM_DECORATE(ANSI_CHARSET,ANSI_CHARSET,Ansi)
	LIST_ITEM_DECORATE(DEFAULT_CHARSET,DEFAULT_CHARSET,Default)
	LIST_ITEM_DECORATE(SYMBOL_CHARSET,SYMBOL_CHARSET,Symbol)
	LIST_ITEM_DECORATE(SHIFTJIS_CHARSET,SHIFTJIS_CHARSET,ShiftJis)
	LIST_ITEM_DECORATE(HANGEUL_CHARSET,HANGEUL_CHARSET,Hangeul)
	LIST_ITEM_DECORATE(HANGUL_CHARSET,HANGUL_CHARSET,Hangul)
	LIST_ITEM_DECORATE(GB2312_CHARSET,GB2312_CHARSET,GB2312)
	LIST_ITEM_DECORATE(CHINESEBIG5_CHARSET,CHINESEBIG5_CHARSET,ChineseBig5)
	LIST_ITEM_DECORATE(OEM_CHARSET,OEM_CHARSET,OEM)
	LIST_ITEM_DECORATE(JOHAB_CHARSET,JOHAB_CHARSET,Johab)
	LIST_ITEM_DECORATE(HEBREW_CHARSET,HEBREW_CHARSET,Hebrew)
	LIST_ITEM_DECORATE(ARABIC_CHARSET,ARABIC_CHARSET,Arabic)
	LIST_ITEM_DECORATE(GREEK_CHARSET,GREEK_CHARSET,Greek)
	LIST_ITEM_DECORATE(TURKISH_CHARSET,TURKISH_CHARSET,Turkish)
	LIST_ITEM_DECORATE(VIETNAMESE_CHARSET,VIETNAMESE_CHARSET,Vietnamese)
	LIST_ITEM_DECORATE(THAI_CHARSET,THAI_CHARSET,Thai)
	LIST_ITEM_DECORATE(EASTEUROPE_CHARSET,EASTEUROPE_CHARSET,EastEurope)
	LIST_ITEM_DECORATE(RUSSIAN_CHARSET,RUSSIAN_CHARSET,Russian)
END_LIST_ITEM(CharSet)

BEGIN_LIST_PROPERTY(OutPrecision)
	LIST_ITEM(OUT_CHARACTER_PRECIS,OUT_CHARACTER_PRECIS)
	LIST_ITEM(OUT_DEFAULT_PRECIS,OUT_DEFAULT_PRECIS)
	LIST_ITEM(OUT_DEVICE_PRECIS,OUT_DEVICE_PRECIS)
	LIST_ITEM(OUT_OUTLINE_PRECIS,OUT_OUTLINE_PRECIS)
	LIST_ITEM(OUT_RASTER_PRECIS,OUT_RASTER_PRECIS)
	LIST_ITEM(OUT_STRING_PRECIS,OUT_STRING_PRECIS)
	LIST_ITEM(OUT_STROKE_PRECIS,OUT_STROKE_PRECIS)
	LIST_ITEM(OUT_TT_ONLY_PRECIS,OUT_TT_ONLY_PRECIS)
	LIST_ITEM(OUT_TT_PRECIS,OUT_TT_PRECIS)
END_LIST_ITEM(OutPrecision)

BEGIN_LIST_PROPERTY(ClipPrecision)
	LIST_ITEM(CLIP_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS)
	LIST_ITEM(CLIP_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS)
	LIST_ITEM(CLIP_STROKE_PRECIS,CLIP_STROKE_PRECIS)
	LIST_ITEM(CLIP_EMBEDDED,CLIP_EMBEDDED)
	LIST_ITEM(CLIP_LH_ANGLES,CLIP_LH_ANGLES)
END_LIST_ITEM(ClipPrecision)

BEGIN_LIST_PROPERTY(Quality)
	LIST_ITEM(DEFAULT_QUALITY,DEFAULT_QUALITY)
	LIST_ITEM(DRAFT_QUALITY,DRAFT_QUALITY)
	LIST_ITEM(PROOF_QUALITY,PROOF_QUALITY)
END_LIST_ITEM(Quality)

BEGIN_LIST_PROPERTY(VertTextRectAlign)
LIST_ITEM(DT_TOP,DT_TOP)
LIST_ITEM(DT_VCENTER,DT_VCENTER)
LIST_ITEM(DT_BOTTOM,DT_BOTTOM)
END_LIST_ITEM(VertTextRectAlign)

BEGIN_LIST_PROPERTY(HorizTextRectAlign)
LIST_ITEM(DT_LEFT,DT_LEFT)
LIST_ITEM(DT_CENTER,DT_CENTER)
LIST_ITEM(DT_RIGHT,DT_RIGHT)
END_LIST_ITEM(HorizTextRectAlign)

typedef CString ImageBmpIcoFileNameType;
typedef CString ImageIcoFileNameType;
typedef CString ImageBmpFileNameType;

CImage::CImage(int t):type(t),bitmap(NULL),icon(NULL),cx(0),cy(0)
{
}

CImage::~CImage()
{
	DeleteObject();
}

void CImage::set_FileName(CString val)
{
    if(fileName!=val)
    {
	    fileName=val;
	    Load();
    }
}

CString CImage::get_FileName()
{
	return fileName.GetPath();
}

void CImage::DeleteObject()
{
	if(bitmap)
		::DeleteObject(bitmap);

	if(icon)
		::DestroyIcon(icon);
	bitmap=NULL;
	icon=NULL;
}

BOOL CImage::Load()
{   
    HBITMAP bmp=NULL;
    BITMAP bmpInfo;
	if(fileName.IsFilePath()==TRUE)
	{
        DeleteObject();
		if(fileName.GetExt().CompareNoCase(_T("bmp"))==0)
			bmp=bitmap=(HBITMAP)LoadImage(NULL,(LPCTSTR)fileName,IMAGE_BITMAP,cx,cy,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		else
			if(fileName.GetExt().CompareNoCase(_T("ico"))==0)
            {
                icon=(HICON)LoadImage(NULL,(LPCTSTR)fileName,IMAGE_ICON,cx,cy,LR_LOADFROMFILE);
                ICONINFO icoInfo;
                if(GetIconInfo(icon, &icoInfo))
                    bmp=icoInfo.hbmColor;
            }
        cx=cy=0;
        if(bmp!=NULL)
        {
            GetObject(bmp, sizeof(BITMAP), &bmpInfo);
            cx=bmpInfo.bmWidth;
            cy=bmpInfo.bmHeight;
        }
        ::UpdateProperty(propName+_T(".FileName"));
	    ::UpdateProperty(propName+_T(".ImageType"));
        //::UpdateProperty(propName+_T(".ID"));
        ::UpdateProperty(propName+_T(".Width"));
        ::UpdateProperty(propName+_T(".Height"));
        change(this);
    }
	return bitmap!=NULL || icon!=NULL;
}

void CImage::set_Width(long val)
{
    if(cx!=val)
    {
        cx=val;
        Load();
    }
}

long CImage::get_Width()
{
    return cx;
}

void CImage::set_Height(long val)
{
    if(cy!=val)
    {
        cy=val;
        Load();
    }
}

long CImage::get_Height()
{
    return cy;
}

void CImage::set_ID(CString val)
{
	id=val;
}

CString CImage::get_ID(void)
{
	return id;
}

void CImage::set_ImageType(CString)
{
}

CString CImage::get_ImageType(void)
{
	if(bitmap)
		return _T("Bitmap");
	else
		if(icon)
			return _T("Icon");
	return _T("None");
}

void CImage::AddProperty(LPCTSTR Name,CProperties & objprop)
{
    propName=Name;
	BEGIN_SUB_PROPERTY(Name,CImage)
        if((type & BITMAP_TYPE) && (type & ICON_TYPE))
		    DEFINE_SUB_PROPERTY(FileName,ImageBmpIcoFileNameType,CImage,fileName.GetPath())
        else
        if(type & BITMAP_TYPE)
            DEFINE_SUB_PROPERTY(FileName,ImageBmpFileNameType,CImage,fileName.GetPath())
            else
            if(type & ICON_TYPE)
                DEFINE_SUB_PROPERTY(FileName,ImageIcoFileNameType,CImage,fileName.GetPath())

		    DEFINE_SUB_PROPERTY(ID,CString,CImage,_T(""))
		    DEFINE_SUB_PROPERTY(ImageType,CString,CImage,_T("None"))
            DEFINE_SUB_PROPERTY(Width,long,CImage,0)
            DEFINE_SUB_PROPERTY(Height,long,CImage,0)
	END_SUB_PROPERTY
    READONLY_PROPERTY_STR(propName+_T(".ImageType"),TRUE)
}


void RegisterGDIProp(void)
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;

    REGISTER_LIST_PROPERTY(Bold)
    REGISTER_LIST_PROPERTY(CharSet)
    REGISTER_LIST_PROPERTY(OutPrecision)
    REGISTER_LIST_PROPERTY(ClipPrecision)
    REGISTER_LIST_PROPERTY(Quality)
    REGISTER_LIST_PROPERTY(VertTextRectAlign)
    REGISTER_LIST_PROPERTY(HorizTextRectAlign)

        //	REGISTER_LIST_PROPERTY(BrushStyle)
        //	REGISTER_LIST_PROPERTY(BrushHatch)

    IsInited=TRUE;
}

#endif