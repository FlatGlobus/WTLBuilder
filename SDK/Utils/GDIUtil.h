// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __GDIUTIL_H
#define __GDIUTIL_H
#include "CallBack.h"
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
#include "path.h"

class PropertyBase;
class CProperties;

#define SYSCOLOR_SIGN 0x80000000

class CColorref
{
public:
    CColorref():color(RGB(0,0,0)){}
    CColorref(COLORREF val):color(val)
    {

    }
    CColorref(int val):color(val|SYSCOLOR_SIGN){}
    CColorref(const CColorref &val):color(val.color){}
    CColorref & operator=(COLORREF val)
    {
        color=val;
        return *this;
    }
    
    CColorref & operator=(int val)
    {
        color=val|SYSCOLOR_SIGN;
        return *this;
    }

    operator COLORREF()
    {
        return GetColor();	
    }

    int operator ==(const CColorref &val)
    {
        return color==val.color;
    }

    int operator ==(const COLORREF val)
    {
        return GetColor()==val;
    }

    int operator !=(const CColorref &val)
    {
        return color!=val.color;
    }

    int operator !=(const COLORREF val)
    {
        return GetColor()!=val;
    }

    COLORREF GetColor()
    {
        if(color < 0 && color!=CLR_DEFAULT && color!=CLR_NONE)
            return ::GetSysColor(color&~SYSCOLOR_SIGN);
        return (COLORREF)color;	
    }

    BYTE GetRed()
    {
        return (BYTE)(GetColor() & 0xFF);
    }

    BYTE GetGreen()
    {
        return (BYTE)((GetColor() >> 8) & 0xFF);
    }

    BYTE GetBlue()
    {
        return (BYTE)((GetColor()>>16) & 0xFF);
    }

protected:
    long color;
};

#define BITMAP_TYPE 0x01
#define ICON_TYPE 0x02

class CImage
{
    HBITMAP bitmap;
    HICON	icon;
    CPath fileName;
    CString	id;
    int type;
    int cx,cy;
    CString propName;
    
    void DeleteObject();
public:
    CImage(int t=BITMAP_TYPE|ICON_TYPE);
    ~CImage();
    void set_FileName(CString);
    CString get_FileName();
    BOOL Load();
    void set_ID(CString);
    CString get_ID(void);

    void set_ImageType(CString);
    CString get_ImageType(void);
    
    void set_Width(long);
    long get_Width();

    void set_Height(long);
    long get_Height();

    void AddProperty(LPCTSTR,CProperties &);
    DECLARE_CALLBACK(Change,change)
    operator HBITMAP(void)
    {
        return bitmap;
    }

    operator HICON()
    {
        return icon;
    }
protected:
};
void RegisterGDIProp(void);
#else
typedef COLORREF CColorref;
#endif
//////////////////////////////////////////////////////////////////////////
#define LParamToPoint(lParam)  CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));

class CPenEx
{
public:
    CPenEx(void);
    CPenEx(int style,int width,CColorref color);
    ~CPenEx();

    void set_Style(int);
    int  get_Style(void);
    __declspec(property(get=get_Style, put=set_Style)) int Style;

    void set_Width(int);
    int  get_Width(void);
    __declspec(property(get=get_Width, put=set_Width)) int Width;

    void set_Color(CColorref);
    CColorref get_Color(void);
    __declspec(property(get=get_Color, put=set_Color)) CColorref Color;
#ifdef __WTLBUILDER__
    void AddProperty(LPCTSTR,CProperties &);
#endif
    operator HPEN();
    DECLARE_CALLBACK(Change,change)
protected:
    LOGPEN	logpen;
    HPEN handle;
};

class CBrushEx
{
public:
    CBrushEx(void);
    CBrushEx(CColorref);
    CBrushEx(int style,int hatch,CColorref color);
    ~CBrushEx(void);

    void set_Style(long);
    long  get_Style(void);
    __declspec(property(get=get_Style, put=set_Style)) long Style;

    void set_Hatch(long);
    long  get_Hatch(void);
    __declspec(property(get=get_Hatch, put=set_Hatch)) long Hatch;

    void set_Color(CColorref);
    CColorref get_Color(void);
    __declspec(property(get=get_Color, put=set_Color)) CColorref Color;
#ifdef __WTLBUILDER__
    void AddProperty(LPCTSTR,CProperties &);
#endif
    operator HBRUSH(); 
    DECLARE_CALLBACK(Change,change)
protected:
    LOGBRUSH logbrush;
    HBRUSH   handle;
};

class CFontEx 
{
public:
    CFontEx();
    CFontEx(const CString & facename);
    CFontEx(LOGFONT& logfont);
    CFontEx(CFont * font);
    CFontEx(CFontEx & font);
    virtual ~CFontEx();

    void set_Height(long height);
    long get_Height(void);
    __declspec(property(get=get_Height, put=set_Height)) long Height;

    void set_Width(long width);
    long get_Width(void);
    __declspec(property(get=get_Width, put=get_Width)) long Width;

    void set_Escapement(long esc);
    long get_Escapement(void);
    __declspec(property(get=get_Escapement, put=set_Escapement)) long Escapement;

    void set_Orientation(long or);
    long get_Orientation(void);
    __declspec(property(get=get_Orientation, put=set_Orientation)) long Orientation;

    void set_Weight(long weight);
    long get_Weight(void);
    __declspec(property(get=get_Weight, put=set_Weight)) long Weight;

    void set_CharSet(long charset);
    long get_CharSet();
    __declspec(property(get=get_CharSet, put=set_CharSet)) long Charset;

    void set_OutPrecision(long op);
    long get_OutPrecision(void);
    __declspec(property(get=get_OutPrecision, put=set_OutPrecision)) long OutPrecision;

    void set_ClipPrecision(long cp);
    long get_ClipPrecision(void);
    __declspec(property(get=get_ClipPrecision, put=set_ClipPrecision)) long ClipPrecision;

    void set_Quality(long qual);
    long get_Quality(void);
    __declspec(property(get=get_Quality, put=set_Quality)) long Quality;

    void set_PitchAndFamily(long paf);
    long get_PitchAndFamily(void);
    __declspec(property(get=get_PitchAndFamily, put=set_PitchAndFamily)) long PitchAndFamily;

    void set_FaceName(CString);
    CString get_FaceName(void);
    __declspec(property(get=get_FaceName, put=set_FaceName)) CString FaceName;

    void set_Bold(BOOL B);
    BOOL get_Bold(void);
    __declspec(property(get=get_Bold, put=set_Bold)) BOOL Bold;

    void set_Italic(BOOL i);
    BOOL get_Italic(void);
    __declspec(property(get=get_Italic, put=set_Italic)) BOOL Italic;

    void set_Underline(BOOL u);
    BOOL get_Underline(void);
    __declspec(property(get=get_Underline, put=set_Underline)) BOOL Underline;

    void set_StrikeOut(BOOL s);
    BOOL get_StrikeOut(void);
    __declspec(property(get=get_StrikeOut, put=set_StrikeOut)) BOOL StrikeOut;

    void set_LogFont(LOGFONT& logfont);
    void get_LogFont(LOGFONT& logfont);

    void set_Color(CColorref color);
    CColorref get_Color(void);
    __declspec(property(get=get_Color, put=set_Color)) CColorref Color;

#ifdef __WTLBUILDER__
    void AddProperty(LPCTSTR,CProperties &);
#endif	
    operator HFONT();

    DECLARE_CALLBACK(Change,change)
protected:
    LOGFONT lf;
    CColorref fontColor;
    HFONT    handle;
};
////////////////////////////////////////////////////////////////////////////////////////////////
class CSel 
{
public:
    CSel(HDC DC, HPEN);
    CSel(HDC DC, HBRUSH);
    CSel(HDC DC, HFONT);
    CSel(HDC DC, int);
protected:
    HDC m_pDC;
    HANDLE m_hOldGdiObject;
public:
    virtual ~CSel();
};

template <class T>
void Unused(T rT)
{
    static_cast<void>(rT);
};

class CGDI
{
protected:
    HDC m_pDC;

    CGDI(HDC DC) : 
      m_pDC(DC)
    {
    }

    virtual ~CGDI()
    {
        m_pDC = NULL;
    }
};

class CTextColor : public CGDI
{
    CColorref m_LastColor;

public:
    CTextColor(HDC DC, CColorref theColor) : CGDI(DC),
      m_LastColor(RGB(0,0,0))
    {
        m_LastColor = ::SetTextColor(m_pDC,theColor);
    }

    virtual ~CTextColor()
    {
        Unused(SetTextColor(m_pDC,m_LastColor));
    }

};

class CBackColor : public CGDI
{
    CColorref m_LastColor;

public:
    CBackColor(HDC DC, CColorref theColor) : CGDI(DC),
      m_LastColor(RGB(0,0,0))
    {
        m_LastColor = ::SetBkColor(m_pDC,theColor);
    }

    virtual ~CBackColor()
    {
        Unused(::SetBkColor(m_pDC,m_LastColor));
    }
};

class CBKMode : public CGDI
{
    int m_LastMode;
public:
    CBKMode(HDC DC, int theMode) : CGDI(DC),
      m_LastMode(0)
    {
        m_LastMode = ::SetBkMode(m_pDC,theMode);
    }

    virtual ~CBKMode()
    {
        Unused(::SetBkMode(m_pDC,m_LastMode));
    }
};

class CTextAlign : public CGDI
{
UINT m_Last;

public:
    CTextAlign(HDC DC, UINT nTextAlign) : CGDI(DC),
      m_Last(0)
    {
        m_Last = ::SetTextAlign(m_pDC,nTextAlign);
    }

    virtual ~CTextAlign()
    {
        Unused(::SetTextAlign(m_pDC,m_Last));
    }
};


class CROP : public CGDI
{
int m_Last;

public:
    CROP(HDC DC, int nROP) : CGDI(DC),
      m_Last(0)
    {
        m_Last = ::SetROP2(m_pDC,nROP);
    }

    virtual ~CROP()
    {
        Unused(::SetROP2(m_pDC,m_Last));
    }
};

class CMapMode : public CGDI
{
int m_Last;
public:
    CMapMode(HDC DC, int nMapMode) : CGDI(DC),
      m_Last(0)
    {
        m_Last = ::SetMapMode(m_pDC,nMapMode);
    }

    virtual ~CMapMode()
    {
        Unused(::SetMapMode(m_pDC,m_Last));
    }
};
//////////////////////////////////////////////////////////////////////////
enum {grHoriz,grVert};
void DrawGradientFill(CDC & DC, CRect & pRect, CColorref crStart, CColorref crEnd,int Orient=grHoriz, int nSegments=100);
void DrawHorGradientFill(CDC & DC, CRect & pRect, CColorref crStart, CColorref crEnd, int nSegments=100);
void DrawVertGradientFill(CDC & pDC, CRect &pRect, CColorref crStart, CColorref crEnd, int nSegments=100);
void DrawGradientText(CDC & DC,int x, int y, CString & text, CColorref crStart, CColorref crEnd,int Orient=grHoriz, int nSegments=100);
//////////////////////////////////////////////////////////////////////////
class CPaintDCEx : public CDC
{
private:
    CBitmap m_bitmap; // Offscreen bitmap
    CBitmap m_oldBitmap; // bitmap originally found in CMemDC
    CDC		m_pDC; // Saves CDC passed in constructor
    CRect	m_rect; // Rectangle of drawing area.
    BOOL	m_bMemDC; // TRUE if CDC really is a Memory DC.
public:
    CPaintDCEx(HDC DC, CRect & ClentRect) : CDC(), m_oldBitmap(NULL), m_pDC(DC), m_rect(ClentRect)
    {
        // Create a Memory DC
        CreateCompatibleDC(DC);
        //::GetClipBox(DC,&m_rect);
        m_bitmap.CreateCompatibleBitmap(DC, m_rect.Width(), m_rect.Height());
        if(m_bitmap.IsNull())
            return;
        m_oldBitmap = SelectBitmap(m_bitmap);
        //SetWindowOrg(m_rect.left, m_rect.top);
    }
    
    ~CPaintDCEx()
    {
        // Copy the offscreen bitmap onto the screen.
        m_pDC.BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
            *this, m_rect.left, m_rect.top, SRCCOPY);
        // Swap back the original bitmap.
        SelectBitmap(m_oldBitmap);
        m_bitmap.DeleteObject();
    }
    
    // Allow usage as a pointer
    CPaintDCEx * operator->() {return this;}
    // Allow usage as a pointer
    operator CPaintDCEx*() {return this;}
};

inline void DrawBitmap(CDC & dc,HBITMAP bmp,int x ,int y)
{
    CDC memDC;
    BITMAP bstruct;
    ::GetObject(bmp,sizeof(BITMAP),&bstruct);
    memDC.CreateCompatibleDC(dc);
    memDC.SetMapMode(dc.GetMapMode());
    CBitmap pOldBitmap = memDC.SelectBitmap(bmp);
    dc.BitBlt(x,y,bstruct.bmWidth,bstruct.bmHeight,memDC,
            0,0,SRCCOPY);
    memDC.SelectBitmap(pOldBitmap);
}

void DrawTransparentBitmap (HDC hdc, HBITMAP hBitmap, long xStart,
                     long yStart, COLORREF cTransparentColor);

//////////////////////////////////////////////////////////////////////////
#endif