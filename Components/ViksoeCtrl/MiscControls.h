#if !defined(AFX_MISCCONTROLS_H__20071124_2942_73E9_067E_0080AD509054__INCLUDED_)
#define AFX_MISCCONTROLS_H__20071124_2942_73E9_067E_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////
// CInfoButton
//

class CInfoButtonCtrl : public CFadeStateButtonCtrl
{
public:
   WTL::CBitmap m_bmpButton;

   BOOL GenerateImages(LPCTSTR pstrText, UINT uBitmapRes = 0, int cx = 0, int cy = 0)
   {
      ATLASSERT(pstrText);

      if( !m_bmpButton.IsNull() ) m_bmpButton.DeleteObject();

      SetFadeButtonStyle(FSTBS_CAPTUREBKG);

      USES_CONVERSION;
      LPCWSTR pwstr = T2CW(pstrText);
      int cchLen = ::lstrlenW(pwstr);

      Gdiplus::Bitmap bmTemp(180, 120);
      Gdiplus::Graphics gTemp(&bmTemp);
      Gdiplus::FontFamily fontFamily(L"MS Shell Dlg 2");
      Gdiplus::Font font(&fontFamily, 12, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
      Gdiplus::RectF rcText;
      gTemp.MeasureString(pwstr, cchLen, &font, Gdiplus::PointF(0.0, 0.0), &rcText);
      
      CRect rcButton(0, 0, (int)(rcText.Width + 0.5) + 10, (int)(rcText.Height + 0.5) + 5);

      Gdiplus::Bitmap* pIcon = NULL;
      if( uBitmapRes != 0 ) pIcon = GdipGetPngBitmapFromResource(uBitmapRes, _T("PNG"));
      int cxIcon = 0;
      int cyIcon = 0;
      if( pIcon != NULL ) {
         cxIcon = pIcon->GetWidth() / NUM_STATES;
         cyIcon = pIcon->GetHeight();
         rcButton.right += cxIcon + 3;
         if( rcButton.bottom < (INT)(cyIcon + 2) ) rcButton.bottom = (INT)(cyIcon + 2);
      }
      if( rcButton.right < cx ) rcButton.right = cx;
      if( rcButton.bottom < cy ) rcButton.bottom = cy;

      Gdiplus::Bitmap bm24bpp(rcButton.Width() * NUM_STATES, rcButton.Height(), PixelFormat32bppARGB);
      Gdiplus::Graphics g(&bm24bpp);
      int xoffset = 0;
      for( int i = 0; i < NUM_STATES; i++  )
      {
         if( i == IMAGE_HOT || i == IMAGE_PRESSED ) {
            g.SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed);
            Gdiplus::GraphicsPath* pBorder = _MakeRoundRect(Gdiplus::Point(xoffset, 0), Gdiplus::Point(xoffset + rcButton.Width() - 2, rcButton.Height() - 2), 35);
            Gdiplus::SolidBrush brBorder(Gdiplus::Color(120,255,255,255));
            g.FillPath(&brBorder, pBorder);
            Gdiplus::Pen penBorder(Gdiplus::Color(255,0,102,204));
            g.DrawPath(&penBorder, pBorder);
            delete pBorder;
            g.SetSmoothingMode(Gdiplus::SmoothingModeDefault);
         }
         int iconoffset = 0;
         if( pIcon != NULL ) {
            g.DrawImage(pIcon, Gdiplus::Rect(xoffset + 4, 2, cxIcon, cyIcon), i * cxIcon, 0, cxIcon, cyIcon, Gdiplus::UnitPixel);            
            iconoffset += (pIcon->GetWidth() / NUM_STATES) + 3;
         }
         Gdiplus::PointF pointF(xoffset + iconoffset + 4.0f, 2.0f);
         Gdiplus::SolidBrush brText(Gdiplus::Color(255, 0, 102, 204));
         g.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
         g.DrawString(pwstr, -1, &font, pointF, &brText);
         xoffset += rcButton.Width();
      }

      delete pIcon;

      bm24bpp.GetHBITMAP(Gdiplus::Color(0,0,0,0), &m_bmpButton.m_hBitmap);
      SetBitmap(m_bmpButton);

      return TRUE;
   }

   Gdiplus::GraphicsPath* _MakeRoundRect(Gdiplus::Point topLeft, Gdiplus::Point bottomRight, INT percentageRounded) const
   {
      INT left  = min(topLeft.X, bottomRight.X);
      INT right = max(topLeft.X, bottomRight.X);
      INT top    = min(topLeft.Y, bottomRight.Y);
      INT bottom = max(topLeft.Y, bottomRight.Y);
      INT minDef = min((right - left), (bottom - top));
      INT offsetX = minDef * percentageRounded / 100; 
      INT offsetY = minDef * percentageRounded / 100;
      Gdiplus::GraphicsPath* path = new Gdiplus::GraphicsPath();
      path->AddArc(right - offsetX, top, offsetX, offsetY, 270, 90);
      path->AddArc(right - offsetX, bottom - offsetY, offsetX, offsetY, 0, 90);
      path->AddArc(left, bottom - offsetY, offsetX, offsetY, 90, 90);
      path->AddArc(left, top, offsetX, offsetY, 180, 90);
      path->AddLine(left + offsetX, top, right - offsetX / 2, top);
      path->CloseFigure();
      return path;
   }
};


//////////////////////////////////////////////////////////////////////
// CSeparatorCtrl
//

class CSeparatorCtrl : 
   public ATL::CWindowImpl<CSeparatorCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_LineSeparator"))

   COLORREF m_clrBack;
   COLORREF m_clrLight;
   COLORREF m_clrDark;

   CSeparatorCtrl() : m_clrBack(RGB(234,240,248)), m_clrDark(RGB(208,220,232)), m_clrLight(RGB(255,255,255))
   {
   }

   void SetColors(COLORREF clrBack, COLORREF clrDark, COLORREF clrLight)
   {
      m_clrBack = clrBack;
      m_clrLight = clrLight;
      m_clrDark = clrDark;
      if( IsWindow() ) Invalidate();
   }

   BEGIN_MSG_MAP(CSeparatorCtrl)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
   END_MSG_MAP()

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      CClientDC dc = m_hWnd;
      CRect rcClient;
      GetClientRect(&rcClient);
      dc.FillSolidRect(&rcClient, m_clrBack);
      int cxMiddle = rcClient.CenterPoint().x;
      TRIVERTEX triv1[] = {
         { rcClient.left,  rcClient.top,       (WORD)(GetRValue(m_clrBack) << 8),  (WORD)(GetGValue(m_clrBack) << 8),  (WORD)(GetBValue(m_clrBack) << 8),  0xFF00 },
         { cxMiddle,       rcClient.top + 1,   (WORD)(GetRValue(m_clrDark) << 8),  (WORD)(GetGValue(m_clrDark) << 8),  (WORD)(GetBValue(m_clrDark) << 8),  0xFF00 },
         { cxMiddle,       rcClient.top,       (WORD)(GetRValue(m_clrDark) << 8),  (WORD)(GetGValue(m_clrDark) << 8),  (WORD)(GetBValue(m_clrDark) << 8),  0xFF00 },
         { rcClient.right, rcClient.top + 1,   (WORD)(GetRValue(m_clrBack) << 8),  (WORD)(GetGValue(m_clrBack) << 8),  (WORD)(GetBValue(m_clrBack) << 8),  0xFF00 },
         { rcClient.left,  rcClient.top + 1,   (WORD)(GetRValue(m_clrBack) << 8),  (WORD)(GetGValue(m_clrBack) << 8),  (WORD)(GetBValue(m_clrBack) << 8),  0xFF00 },
         { cxMiddle,       rcClient.top + 2,   (WORD)(GetRValue(m_clrLight) << 8), (WORD)(GetGValue(m_clrLight) << 8), (WORD)(GetBValue(m_clrLight) << 8), 0xFF00 },
         { cxMiddle,       rcClient.top + 1,   (WORD)(GetRValue(m_clrLight) << 8), (WORD)(GetGValue(m_clrLight) << 8), (WORD)(GetBValue(m_clrLight) << 8), 0xFF00 },
         { rcClient.right, rcClient.top + 2,   (WORD)(GetRValue(m_clrBack) << 8),  (WORD)(GetGValue(m_clrBack) << 8),  (WORD)(GetBValue(m_clrBack) << 8),  0xFF00 },
      };
      GRADIENT_RECT grc1[] = { {0, 1}, {2, 3}, {4, 5}, {6,7} };
      dc.GradientFill(triv1, sizeof(triv1) / sizeof(triv1[0]), grc1, sizeof(grc1) / sizeof(grc1[0]), GRADIENT_FILL_RECT_H);
      return 1;
   }
};


//////////////////////////////////////////////////////////////////////
// CKeywordListCtrl
//

class CKeywordListCtrl : 
   public ATL::CWindowImpl<CKeywordListCtrl, WTL::CListViewCtrl>,
   public WTL::CCustomDraw<CKeywordListCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_KeywordList"))

   CImageList m_Images;

   BEGIN_MSG_MAP(CKeywordListCtrl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      CHAIN_MSG_MAP_ALT( CCustomDraw<CKeywordListCtrl>, 1 )
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc();

      ModifyStyle(LVS_SHOWSELALWAYS, LVS_NOCOLUMNHEADER | LVS_NOSORTHEADER | LVS_SORTASCENDING);

//      m_Images.Create(IDB_KEYWORDS, 16, 0, RGB(255,0,255));

      AddColumn(_T(""), 0);
      SetImageList(m_Images, LVSIL_SMALL);
      SetViewType(LV_VIEW_DETAILS);
      SetBkColor(RGB(238,243,250));

      _PopulateList();

      return lRes;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
      bHandled = FALSE;
      return 0;
   }

   // Implementation

   void _PopulateList()
   {
//#define STR(nRes) CString(MAKEINTRESOURCE(nRes))
//      InsertItem(0, STR(IDS_KEYWORD_ANIMALS));
//      InsertItem(1, STR(IDS_KEYWORD_OCEAN));
//      InsertItem(2, STR(IDS_KEYWORD_LANDSCAPES));
   }

   // Custom Draw

   DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
   {
      return CDRF_NOTIFYITEMDRAW;
   }

   DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
   {
      CDCHandle dc = lpNMCustomDraw->hdc;
      int iItem = (int) lpNMCustomDraw->dwItemSpec;
      CRect rc = lpNMCustomDraw->rc;
      TCHAR szText[100] = { 0 };
      GetItemText(iItem, 0, szText, 99);
      COLORREF clrBack = GetBkColor();
      if( (lpNMCustomDraw->uItemState & CDIS_SELECTED) != 0 ) clrBack = RGB(214,234,251);
      dc.FillSolidRect(&rc, clrBack);
      m_Images.Draw(dc, 0, CPoint(1, rc.CenterPoint().y - 12), ILD_TRANSPARENT | ILD_PRESERVEALPHA);
      CRect rcText = rc;
      rcText.left += 20;
      dc.SetBkMode(TRANSPARENT);
      dc.SetTextColor(RGB(0,0,0));
      dc.DrawText(szText, -1, rcText, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
      if( (lpNMCustomDraw->uItemState & CDIS_FOCUS) != 0 ) dc.DrawFocusRect(rc);
      return CDRF_SKIPDEFAULT;
   }
};


//////////////////////////////////////////////////////////////////////
// CSearchEditCtrl
//

class CSearchEditCtrl : 
   public ATL::CWindowImpl<CSearchEditCtrl>,
   public WTL::CCustomDraw<CSearchEditCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_SearchEx"))

   CContainedWindowT<CEdit> m_ctrlEdit;
   CToolBarCtrl m_ctrlToolBar;
   CImageList m_Images;
   CRect m_rcButton;            // Size of button (w. dropdown)
   bool m_bDropped;             // Is dropdown activated? (sadly there is no runtime state for this)
   bool m_bTracking;            // Is button hot?

   CSearchEditCtrl() : m_ctrlEdit(this, 1), m_bDropped(false), m_bTracking(false)
   {
   }

   BEGIN_MSG_MAP(CSearchEditCtrl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnDropDown)
      COMMAND_CODE_HANDLER(EN_CHANGE, OnEditChange)
//      COMMAND_ID_HANDLER(IDC_SEARCHDROP, OnClearEdit)
      CHAIN_MSG_MAP( CCustomDraw<CSearchEditCtrl> )
   ALT_MSG_MAP( 1 )
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
      MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      USES_CONVERSION;

//      m_Images.CreateFromImage(IDB_SEARCH, 16, 0, RGB(0,0,0), IMAGE_BITMAP, LR_CREATEDIBSECTION);

      m_ctrlEdit.Create(m_hWnd, rcDefault, _T(""), WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, 0);
      m_ctrlEdit.SetFont(AtlGetDefaultShellFont());
//      m_ctrlEdit.SetCueBannerText(T2CW(CString(MAKEINTRESOURCE(IDS_SEARCH))));

      DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP 
                      | TBSTYLE_TRANSPARENT | TBSTYLE_CUSTOMERASE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS 
                      | CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_NORESIZE | CCS_TOP;
      m_ctrlToolBar.Create(m_hWnd, rcDefault, _T(""), dwStyle);
//      m_ctrlToolBar.SetExtendedStyle(TBSTYLE_EX_MIXEDBUTTONS |  TBSTYLE_EX_DRAWDDARROWS);
      m_ctrlToolBar.ModifyStyleEx(0, TBSTYLE_EX_DOUBLEBUFFER);
      m_ctrlToolBar.SetImageList(m_Images);
      m_ctrlToolBar.SetIndent(0);
      m_ctrlToolBar.SetButtonSize(CSize(22, 28));
//      m_ctrlToolBar.InsertButton(0, IDC_SEARCHDROP, BTNS_BUTTON | BTNS_DROPDOWN, TBSTATE_ENABLED, 0, 0, 0);
//      m_ctrlToolBar.GetRect(IDC_SEARCHDROP, &m_rcButton);

      return 0;
   }

   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
   {
      CRect rcClient(0, 0, LOWORD(lParam), HIWORD(lParam));
      CRect rcEdit(0, 2, rcClient.Width() - m_rcButton.Width(), rcClient.Height());
      m_ctrlEdit.SetWindowPos(NULL, &rcEdit, SWP_NOACTIVATE | SWP_NOZORDER);
      CRect rcToolBar(rcClient.Width() - m_rcButton.Width() + 1, -1, rcClient.right, rcClient.Height());
      m_ctrlToolBar.SetWindowPos(NULL, &rcToolBar, SWP_NOACTIVATE | SWP_NOZORDER);
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnClearEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      m_ctrlEdit.SetWindowText(_T(""));
      return 0;
   }

   LRESULT OnDropDown(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& bHandled)
   {
      m_bDropped = true;
      m_ctrlToolBar.Invalidate();

      CMenu menu;
//      menu.LoadMenu(IDM_SEARCHALL);
      CMenuHandle submenu = menu.GetSubMenu(0);
      RECT rcItem = { 0 };
//      m_ctrlToolBar.GetItemRect(m_ctrlToolBar.CommandToIndex(IDC_SEARCHDROP), &rcItem);
      ::MapWindowPoints(m_ctrlToolBar, HWND_DESKTOP, (LPPOINT) &rcItem, 2);
      TPMPARAMS tpmp = { sizeof(tpmp) };
      rcItem.bottom -= 6;
      tpmp.rcExclude = rcItem;
      TrackPopupMenuEx(submenu, TPM_LEFTBUTTON | TPM_RIGHTALIGN, rcItem.right, rcItem.bottom, m_hWnd, &tpmp);

      m_bDropped = false;
      m_ctrlToolBar.Invalidate();
      bHandled = FALSE;
      return 0;
   }
   
   LRESULT OnEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
//      m_ctrlToolBar.ChangeBitmap(IDC_SEARCHDROP, m_ctrlEdit.GetWindowTextLength() > 0 ? 1 : 0);
      // TODO: Notify someone about SEARCH filter change!
      return 0;
   }

   // Edit messages

   LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      if( !m_bTracking ) {
         _StartTrackMouseLeave();
         m_bTracking = true;
         m_ctrlToolBar.Invalidate();
      }
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_bTracking = false;
      m_ctrlToolBar.Invalidate();
      return 0;
   }
   LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      if( wParam == VK_ESCAPE ) {
         m_ctrlEdit.SetWindowText(_T(""));
         return 0;
      }
      bHandled = FALSE;
      return 0;
   }

   // ListView Custom Draw

   DWORD OnPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
   {
      return CDRF_SKIPDEFAULT;
   }

   DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
   {
      return CDRF_NOTIFYITEMDRAW;
   }

   DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
   {
      LPNMTBCUSTOMDRAW lpNMTBCD = (LPNMTBCUSTOMDRAW) lpNMCustomDraw;
      CONST INT CX_DROPARROW = 16;
      CDCHandle dc = lpNMTBCD->nmcd.hdc;
      bool bIsHot = (lpNMCustomDraw->uItemState & CDIS_HOT) != 0;
      bool bIsPressed = (lpNMCustomDraw->uItemState & CDIS_SELECTED) != 0;
      CRect rcButton = lpNMTBCD->nmcd.rc;
      CRect rcDrop = lpNMTBCD->nmcd.rc;
      rcButton.right = rcDrop.left = rcButton.right - CX_DROPARROW;
      int cyMiddle = rcButton.CenterPoint().y - 2;
      // Paint button part
      COLORREF clrWhite = ::GetSysColor(COLOR_WINDOW);
      int nTextLen = m_ctrlEdit.GetWindowTextLength();
//      int iImage = m_ctrlToolBar.GetBitmap(IDC_SEARCHDROP);
      if( !bIsHot || nTextLen == 0 ) {
         dc.FillSolidRect(&rcButton, clrWhite); 
//         m_Images.DrawEx(iImage, dc, rcButton.CenterPoint().x - 8, rcButton.top + 3, 16, 16, clrWhite, RGB(0,0,0), ILD_TRANSPARENT);
      }
      else {
         COLORREF clrTop = RGB(234,246,253);
         COLORREF clrMiddle1 = RGB(215,239,252);
         COLORREF clrMiddle2 = RGB(189,230,253);
         COLORREF clrBottom = RGB(166,217,244);
         if( bIsPressed ) {
            clrTop = clrMiddle1 = RGB(194,228,246);
            clrMiddle2 = RGB(169,217,242);
            clrBottom =  RGB(146,204,236);
         }
         TRIVERTEX triv1[] = {
            { rcButton.left,  rcButton.top,       (WORD)(GetRValue(clrTop) << 8),      (WORD)(GetGValue(clrTop) << 8),      (WORD)(GetBValue(clrTop) << 8),      0xFF00 },
            { rcButton.right, cyMiddle,           (WORD)(GetRValue(clrMiddle1) << 8),  (WORD)(GetGValue(clrMiddle1) << 8),  (WORD)(GetBValue(clrMiddle1) << 8),  0xFF00 },
            { rcButton.left,  cyMiddle,           (WORD)(GetRValue(clrMiddle2) << 8),  (WORD)(GetGValue(clrMiddle2) << 8),  (WORD)(GetBValue(clrMiddle2) << 8),  0xFF00 },
            { rcButton.right, rcButton.bottom,    (WORD)(GetRValue(clrBottom) << 8),   (WORD)(GetGValue(clrBottom) << 8),   (WORD)(GetBValue(clrBottom) << 8),   0xFF00 },
         };
         GRADIENT_RECT grc1[] = { {0, 1}, {2, 3} };
         dc.GradientFill(triv1, sizeof(triv1) / sizeof(triv1[0]), grc1, sizeof(grc1) / sizeof(grc1[0]), GRADIENT_FILL_RECT_V);
         dc.Draw3dRect(rcButton, RGB(250,253,254), RGB(250,253,254));
         dc.FillSolidRect(CRect(rcButton.left, rcButton.top, rcButton.left + 1, rcButton.bottom), RGB(44,98,139));
//         m_Images.DrawEx(iImage, dc, rcButton.CenterPoint().x - 8, rcButton.top + 3, 16, 16, clrWhite, RGB(0,0,0), ILD_TRANSPARENT);
      }
      // Paint dropdown button
      if( !bIsHot && !m_bTracking ) {
         dc.FillSolidRect(&rcDrop, clrWhite); 
      }
      else {
         COLORREF clrTop = RGB(234,246,253);
         COLORREF clrMiddle1 = RGB(215,239,252);
         COLORREF clrMiddle2 = RGB(189,230,253);
         COLORREF clrBottom = RGB(166,217,244);
         if( m_bDropped ) {
            clrTop = clrMiddle1 = RGB(194,228,246);
            clrMiddle2 = RGB(169,217,242);
            clrBottom =  RGB(146,204,236);
         }
         TRIVERTEX triv1[] = {
            { rcDrop.left,  rcDrop.top,       (WORD)(GetRValue(clrTop) << 8),      (WORD)(GetGValue(clrTop) << 8),      (WORD)(GetBValue(clrTop) << 8),      0xFF00 },
            { rcDrop.right, cyMiddle,         (WORD)(GetRValue(clrMiddle1) << 8),  (WORD)(GetGValue(clrMiddle1) << 8),  (WORD)(GetBValue(clrMiddle1) << 8),  0xFF00 },
            { rcDrop.left,  cyMiddle,         (WORD)(GetRValue(clrMiddle2) << 8),  (WORD)(GetGValue(clrMiddle2) << 8),  (WORD)(GetBValue(clrMiddle2) << 8),  0xFF00 },
            { rcDrop.right, rcDrop.bottom,    (WORD)(GetRValue(clrBottom) << 8),   (WORD)(GetGValue(clrBottom) << 8),   (WORD)(GetBValue(clrBottom) << 8),   0xFF00 },
         };
         GRADIENT_RECT grc1[] = { {0, 1}, {2, 3} };
         dc.GradientFill(triv1, sizeof(triv1) / sizeof(triv1[0]), grc1, sizeof(grc1) / sizeof(grc1[0]), GRADIENT_FILL_RECT_V);
         if( !bIsPressed ) dc.Draw3dRect(rcDrop, RGB(250,253,254), RGB(250,253,254));
         dc.FillSolidRect(CRect(rcDrop.left - 1, rcDrop.top, rcDrop.left, rcDrop.bottom), RGB(44,98,139));
      }
      // Paint dropdown arrow
      int xoffset = rcDrop.left + 2;
      POINT points[] =
      {
         { xoffset + 2, cyMiddle - 2 },
         { xoffset + 8, cyMiddle - 2 },
         { xoffset + 5, cyMiddle + 1 },
      };
      CPen pen;
      CBrush brush;
      pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
      brush.CreateSolidBrush(RGB(0,0,0));
      HPEN hOldPen = dc.SelectPen(pen);
      HBRUSH hOldBrush = dc.SelectBrush(brush);
      dc.Polygon(points, sizeof(points) / sizeof(points[0]));
      dc.SelectBrush(hOldBrush);
      dc.SelectPen(hOldPen);
      return CDRF_SKIPDEFAULT;
   }

   // Implementation

   BOOL _StartTrackMouseLeave()
   {
      TRACKMOUSEEVENT tme = { 0 };
      tme.cbSize = sizeof(tme);
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = m_ctrlEdit;
      return _TrackMouseEvent(&tme);
   }
};


//////////////////////////////////////////////////////////////////////
// CWinXPButton
//

class CWinXPButton : public CFadeStateButtonCtrl
{
public:
   CBitmap m_bmpButton;

   BOOL GenerateImages(LPCTSTR pstrText, UINT uBitmapRes = 0, BOOL bDropDown = FALSE)
   {
      ATLASSERT(pstrText);

      if( !m_bmpButton.IsNull() ) m_bmpButton.DeleteObject();

      USES_CONVERSION;
      LPCWSTR pwstr = T2CW(pstrText);
      int cchLen = ::lstrlenW(pwstr);

      Gdiplus::Bitmap bmTemp(200, 40);
      Gdiplus::Graphics gTemp(&bmTemp);
      Gdiplus::FontFamily fontFamily(L"MS Shell Dlg 2");
      Gdiplus::Font font(&fontFamily, 12, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
      Gdiplus::RectF rcText;
      gTemp.MeasureString(pwstr, cchLen, &font, Gdiplus::PointF(0.0, 0.0), &rcText);

      CRect rcButton(0, 0, (int)(rcText.Width + 0.5), (int)(rcText.Height + 0.5));

      Gdiplus::Bitmap* pIcon = NULL;
      if( uBitmapRes != 0 ) pIcon = GdipGetPngBitmapFromResource(uBitmapRes, _T("BMP")/*_T("PNG")*/);
      int cxIcon = 0;
      int cyIcon = 0;
      if( pIcon != NULL ) {
         cxIcon = pIcon->GetWidth() / NUM_STATES;
         cyIcon = pIcon->GetHeight();
         rcButton.right += cxIcon + 12;
         if( rcButton.bottom < (INT)(cyIcon + 12) ) rcButton.bottom = (INT)(cyIcon + 12);
      }

      if( bDropDown ) rcButton.right += 14;

      Gdiplus::Bitmap bm24bpp(rcButton.Width() * NUM_STATES, rcButton.Height(), PixelFormat32bppARGB);
      Gdiplus::Graphics g(&bm24bpp);
      int xoffset = 0;
      for( int i = 0; i < NUM_STATES; i++  )
      {
         if( i == IMAGE_HOT || i == IMAGE_PRESSED ) {
            g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            Gdiplus::Color clrGr1;
            Gdiplus::Color clrGr2;
            if( i == IMAGE_HOT ) clrGr1.SetFromCOLORREF(RGB(255,255,255)), clrGr2.SetFromCOLORREF(RGB(240,240,240));
            if( i == IMAGE_PRESSED ) clrGr1.SetFromCOLORREF(RGB(240,240,240)), clrGr2.SetFromCOLORREF(RGB(255,255,255));
            Gdiplus::Rect rcBack(xoffset + 3, 3, rcButton.Width() - 5, rcButton.Height() - 5);
            Gdiplus::LinearGradientBrush brBack(rcBack, clrGr1, clrGr2, Gdiplus::LinearGradientModeVertical);
            g.FillRectangle(&brBack, rcBack);
            Gdiplus::GraphicsPath* pBorder1 = _MakeRoundRect(Gdiplus::Point(xoffset + 0, 0), Gdiplus::Point(xoffset + rcButton.Width() - 2, rcButton.Height() - 2), 38);
            Gdiplus::GraphicsPath* pBorder2 = _MakeRoundRect(Gdiplus::Point(xoffset + 1, 1), Gdiplus::Point(xoffset + rcButton.Width() - 3, rcButton.Height() - 3), 38);
            Gdiplus::GraphicsPath* pBorder3 = _MakeRoundRect(Gdiplus::Point(xoffset + 2, 2), Gdiplus::Point(xoffset + rcButton.Width() - 4, rcButton.Height() - 4), 38);
            Gdiplus::Pen penBorder1(Gdiplus::Color(255,105,105,105));
            Gdiplus::Pen penBorder2(Gdiplus::Color(255,169,208,246));
            Gdiplus::Pen penBorder3(Gdiplus::Color(255,205,224,243));
            g.DrawPath(&penBorder3, pBorder3);
            g.DrawPath(&penBorder2, pBorder2);
            g.DrawPath(&penBorder1, pBorder1);
            delete pBorder3;
            delete pBorder2;
            delete pBorder1;
            g.SetSmoothingMode(Gdiplus::SmoothingModeDefault);
         }
         if( i == IMAGE_DISABLED ) {
            g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            Gdiplus::GraphicsPath* pBorder = _MakeRoundRect(Gdiplus::Point(xoffset + 0, 0), Gdiplus::Point(xoffset + rcButton.Width() - 2, rcButton.Height() - 2), 38);
            Gdiplus::Pen penBorder(Gdiplus::Color(255,105,105,105));
            Gdiplus::SolidBrush brBack(Gdiplus::Color(255,255,255,255));
            g.FillPath(&brBack, pBorder);
            g.DrawPath(&penBorder, pBorder);
            delete pBorder;
            g.SetSmoothingMode(Gdiplus::SmoothingModeDefault);
         }
         int iconoffset = 0;
         if( pIcon != NULL ) {
            g.DrawImage(pIcon, Gdiplus::Rect(xoffset + 7, 7, cxIcon, cyIcon), i * cxIcon, 0, cxIcon, cyIcon, Gdiplus::UnitPixel);            
            iconoffset += cxIcon + 3;
         }
         Gdiplus::PointF pointF(xoffset + iconoffset + 4.0f, 2.0f);
         Gdiplus::SolidBrush brText(Gdiplus::Color(255,0,0,0));
         g.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
         g.DrawString(pwstr, -1, &font, pointF, &brText);
         if( bDropDown ) {
            POINT pt = { xoffset + iconoffset + 9 + (INT) rcText.Width, 14 };
            Gdiplus::GraphicsPath path;
            path.AddLine(pt.x, pt.y - 2,     pt.x + 6, pt.y - 2);
            path.AddLine(pt.x + 6, pt.y - 2, pt.x + 3, pt.y + 1);
            path.AddLine(pt.x + 3, pt.y + 1, pt.x, pt.y - 2);
            Gdiplus::SolidBrush brDropDown(Gdiplus::Color(255,0,0,0));
            g.FillPath(&brDropDown, &path);
         }
         xoffset += rcButton.Width();
      }

      delete pIcon;

      bm24bpp.GetHBITMAP(Gdiplus::Color(0,0,0,0), &m_bmpButton.m_hBitmap);
      SetBitmap(m_bmpButton);
      SizeToBitmap();

      return TRUE;
   }

   Gdiplus::GraphicsPath* _MakeRoundRect(Gdiplus::Point topLeft, Gdiplus::Point bottomRight, INT percentageRounded) const
   {
      INT left  = min(topLeft.X, bottomRight.X);
      INT right = max(topLeft.X, bottomRight.X);
      INT top    = min(topLeft.Y, bottomRight.Y);
      INT bottom = max(topLeft.Y, bottomRight.Y);
      INT minDef = min((right - left), (bottom - top));
      INT offsetX = minDef * percentageRounded / 100; 
      INT offsetY = minDef * percentageRounded / 100;
      Gdiplus::GraphicsPath* path = new Gdiplus::GraphicsPath();
      ATLASSERT(path);
      path->AddArc(right - offsetX, top, offsetX, offsetY, 270, 90);
      path->AddArc(right - offsetX, bottom - offsetY, offsetX, offsetY, 0, 90);
      path->AddArc(left, bottom - offsetY, offsetX, offsetY, 90, 90);
      path->AddArc(left, top, offsetX, offsetY, 180, 90);
      path->AddLine(left + offsetX, top, right - offsetX / 2, top);
      path->CloseFigure();
      return path;
   }
};


//////////////////////////////////////////////////////////////////////
// CFillerCtrl
//

class CFillerCtrl : 
   public ATL::CWindowImpl<CFillerCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_Filler"))

   COLORREF m_clrBack;

   CFillerCtrl() : m_clrBack(RGB(234,240,248))
   {
   }

   BEGIN_MSG_MAP(CSeparatorCtrl)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
   END_MSG_MAP()

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      CClientDC dc = m_hWnd;
      CRect rcClient;
      GetClientRect(&rcClient);
      dc.FillSolidRect(&rcClient, m_clrBack);
      return 1;
   }
};


//////////////////////////////////////////////////////////////////////
// CPhotoStatusBarCtrl
//

class CPhotoStatusBarCtrl : 
   public ATL::CWindowImpl<CPhotoStatusBarCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoStatusBar"))

   CFont m_fontStatusBar;
   COLORREF m_clrBack;
   int m_nSel;

   CPhotoStatusBarCtrl() : m_clrBack(RGB(234,240,248)), m_nSel(0)
   {
      CLogFont lf;
      lf.SetStatusFont();
      m_fontStatusBar.CreateFontIndirect(&lf);
   }

   BEGIN_MSG_MAP(CPhotoStatusBarCtrl)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
//      MESSAGE_HANDLER(WM_USER_SELECTION_CHANGE, OnSelectionChange)
   END_MSG_MAP()

   LRESULT OnSelectionChange(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_nSel = (int) wParam;
      Invalidate();
      return 0;
   }

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return 1;
   }

   LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( wParam != NULL )
      {
         DoPaint((HDC) wParam);
      }
      else
      {
         CPaintDC dc(m_hWnd);
         DoPaint(dc.m_hDC);
      }
      return 0;
   }

   // Implementation

   void DoPaint(CDCHandle dc)
   {
      CRect rcClient;
      GetClientRect(&rcClient);

      dc.FillSolidRect(&rcClient, m_clrBack);

      CString sText;
      int nItems;// = _Photos.GetImageCount();
//      if( m_nSel > 0 ) sText.Format(IDS_STATUSBAR_SEL, nItems, m_nSel);
//      else sText.Format(IDS_STATUSBAR_NOSEL, nItems);

      rcClient.left += 20;
      HFONT hOldFont = dc.SelectFont(m_fontStatusBar);
      dc.SetBkMode(TRANSPARENT);
      dc.SetTextColor(RGB(0,0,0));
      dc.DrawText(sText, -1, rcClient, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
      dc.SelectFont(hOldFont);
   }
};


//////////////////////////////////////////////////////////////////////
// CStarRatingCtrl
//

class CStarRatingCtrl : 
   public ATL::CWindowImpl<CStarRatingCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_PhotoRating"))

   CStarRatingCtrl() : m_clrBack(RGB(234,240,248)), m_iHoverItem(-1), m_bTracking(false), m_iRating(0)
   {
   }

   enum { CXY_ICON = 16 };
   enum { MAX_STARS = 5 };

   CImageList m_Images;                 // Star images
   COLORREF m_clrBack;                  // Background
   int m_iRating;                       // Current rating
   bool m_bTracking;                    // Is button hot?
   int m_iHoverItem;                    // Currently highlighted (hot) item

   void SetRating(int iRating)
   {
      m_iRating = iRating;
      if( IsWindow() ) Invalidate();
   }

   BEGIN_MSG_MAP(CStarRatingCtrl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
//      MESSAGE_HANDLER(WM_USER_SELECTION_CHANGE, OnSelectionChange)
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
//      CBitmap bmpImages = AtlLoadBitmapImage(IDB_TREEIMAGES, LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
//      CBitmap bmpMask = AtlLoadBitmapImage(IDB_TREEIMAGES_MASK, LR_MONOCHROME);
      m_Images.Create(CXY_ICON, CXY_ICON, ILC_COLOR24 | ILC_MASK, 16, 0);
//      m_Images.Add(bmpImages, bmpMask);
      ResizeClient(CXY_ICON * MAX_STARS, CXY_ICON);
      return 0;
   }

   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      m_Images.Destroy();
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return 1;
   }
   LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( wParam != NULL )
      {
         DoPaint((HDC) wParam);
      }
      else
      {
         CPaintDC dc(m_hWnd);
         DoPaint(dc.m_hDC);
      }
      return 0;
   }

   LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      if( !m_bTracking ) {
         _StartTrackMouseLeave();
         m_bTracking = true;
      }
      CPoint pt(lParam);
      int iHoverItem = pt.x / CXY_ICON;
      if( iHoverItem != m_iHoverItem ) {
         m_iHoverItem = iHoverItem;
         Invalidate();
      }
      return 0;
   }
   LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_bTracking = false;
      m_iHoverItem = -1;
      Invalidate();
      return 0;
   }

   LRESULT OnSelectionChange(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
//      PHOTOINFO** ppInfo = (PHOTOINFO**) lParam;
  //    int nCount = (int) wParam;
    //  if( nCount > 0 ) {
      //   long lRating = 0;
        // GdipGetBitmapProperty(ppInfo[0]->pImage, PropertyTagExifRating, lRating);
        // SetRating(lRating);
      //}
      return 0;
   }

   void DoPaint(CDCHandle dc)
   {
      CRect rcClient;
      GetClientRect(&rcClient);

      dc.FillSolidRect(&rcClient, m_clrBack);

      int i;
      COLORREF clrFront = RGB(131,159,187);
      RECT rc = { 0, 0, CXY_ICON, CXY_ICON };
      if( m_iHoverItem >= 0 ) 
      {
         for( i = 0; i <= m_iHoverItem && i < MAX_STARS; i++ ) {
            m_Images.DrawEx(10, dc, rc, m_clrBack, clrFront, ILD_TRANSPARENT);
            ::OffsetRect(&rc, CXY_ICON, 0);
         }
         for( ; i <= m_iRating - 1 && i < MAX_STARS; i++ ) {
            m_Images.DrawEx(10, dc, rc, m_clrBack, clrFront, ILD_TRANSPARENT | ILD_BLEND25);
            m_Images.DrawEx(15, dc, rc, m_clrBack, clrFront, ILD_TRANSPARENT);
            ::OffsetRect(&rc, CXY_ICON, 0);
         }
         for( ; i < MAX_STARS; i++ ) {
            m_Images.DrawEx(15, dc, rc, m_clrBack, clrFront, ILD_TRANSPARENT);
            ::OffsetRect(&rc, CXY_ICON, 0);
         }
      }
      else 
      {
         for( i = 0; i <= m_iRating - 1 && i < MAX_STARS; i++ ) {
            m_Images.DrawEx(10, dc, rc, m_clrBack, clrFront, ILD_TRANSPARENT);
            ::OffsetRect(&rc, CXY_ICON, 0);
         }
         for( ; i < MAX_STARS; i++ ) {
            m_Images.DrawEx(15, dc, rc, m_clrBack, clrFront, ILD_TRANSPARENT);
            ::OffsetRect(&rc, CXY_ICON, 0);
         }
      }
   }

   // Implementation

   BOOL _StartTrackMouseLeave()
   {
      TRACKMOUSEEVENT tme = { 0 };
      tme.cbSize = sizeof(tme);
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = m_hWnd;
      return _TrackMouseEvent(&tme);
   }
};



#endif // !defined(AFX_MISCCONTROLS_H__20071124_2942_73E9_067E_0080AD509054__INCLUDED_)
