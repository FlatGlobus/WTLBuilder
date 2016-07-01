// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#if !defined(AFX_TEXT3D_H)
#define AFX_TEXT3D_H

#include <InitTempl.h>

enum {PlainText=0,ShadowText=1,ThreeDText=2};

class CText3d : public CWindowImpl< CText3d, CWindow, CControlWinTraits >
{
public:
	CText3d(void);
	virtual ~CText3d();
	//int Create(DWORD style,const CRect& rect, CWnd* pParentWnd,UINT id); 

	void SetCaption(const CString &);
	const CString & GetCaption(void);
	__declspec(property(get=GetCaption, put=SetCaption)) const CString & Caption;

	void SetTextColor(COLORREF);
	COLORREF GetTextColor(void);
	__declspec(property(get=GetTextColor, put=SetTextColor)) COLORREF TextColor;

	void SetBkColor(COLORREF);
	COLORREF GetBkColor(void);
	__declspec(property(get=GetBkColor, put=SetBkColor)) COLORREF BkColor;
	
	void SetShadowColor(COLORREF);
	COLORREF GetShadowColor(void);
	__declspec(property(get=GetShadowColor, put=SetShadowColor)) COLORREF ShadowColor;

	void SetTextType(long);
	long GetTextType(void);
	__declspec(property(get=GetTextType, put=SetTextType)) long TextType;

	void SetShift(long);
	long GetShift(void);
	__declspec(property(get=GetShift, put=SetShift)) long Shift;
	
	virtual CFont & GetFont(void);
	virtual void SetFont(CFont & ,BOOL bRedraw=TRUE);
protected:
	CString								caption;
	Init<long,ShadowText>				textType;
	Init<long,1>						shift;
	Init<COLORREF,RGB(0xFF,0xFF,0xFF)>	textcolor;
	Init<COLORREF,RGB(0xF7,0xF7,0xF7)>	bkcolor;
	Init<COLORREF,RGB(0,0,0)>			shadowcolor;
	CFont		font;
	Init<COLORREF,RGB(230, 230, 230)>	colorLeft;
    Init<COLORREF,RGB(98,98,98)>	colorRight;

protected:
	BEGIN_MSG_MAP(CText3d)
		//MESSAGE_HANDLER(WM_CREATE, OnCreate)
		//MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
	END_MSG_MAP()

	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
	
	void Draw(HDC DC, const CRect& rect);
	void DoGradientFill(HDC DC, CRect &rc);

};
//////////////////////////////////////////////////////////////////////////
#endif 

