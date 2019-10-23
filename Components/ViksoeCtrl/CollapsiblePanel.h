#if !defined(AFX_COLLAPSIBLEPANEL_H__20031129_797C_31F4_B029_0080AD509054__INCLUDED_)
#define AFX_COLLAPSIBLEPANEL_H__20031129_797C_31F4_B029_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Collapsible Panel - Windows XP Explorer widget
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2003 - 2005 Bjarke Viksoe.
// Scroll support kindly added by Anatoly Ivasyuk (aivasyuk@dtlink.com)
// Include math.h for smooth interpolated animations.
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#ifndef __cplusplus
  #error WTL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLCTRLS_H__
  #error CollapsiblePanel.h requires atlctrls.h to be included first
#endif

#ifndef __ATLGDIX_H__
  #error This control requires my atlgdix.h to be included first
#endif

#if (_WIN32_IE < 0x0400)
  #error This control requires _WIN32_IE >= 0x0400
#endif

#include <zmouse.h>


// Control notifications
#define CPN_EXPANDING     1
#define CPN_EXPANDED      2

// Extended Panel style
#define CPS_EX_NOANIMATE       0x00000001
#define CPS_EX_FLATSTYLE       0x00000002
#define CPS_EX_DEEPDISABLE     0x00000004
#define CPS_EX_SHAREIMAGELIST  0x00000008
#define CPS_EX_OWNERDRAW       0x00000010
#define CPS_EX_NOEXPANDBUTTON  0x00000020
#define CPS_EX_EXPANDCLICK     0x00000040
#define CPS_EX_NOSCROLLBAR     0x00000080
#define CPS_EX_SELHIGHLIGHT    0x00000100


template< class T, class TBase = CWindow, class TWinTraits = CControlWinTraits >
class ATL_NO_VTABLE CCollapsiblePanelImpl : 
   public CWindowImpl< T, TBase, TWinTraits >,
   public COffscreenDrawRect< T >
{
public:
   enum { ANIMATETIMER_ID = 22 };    // Happens to be my lucky number!
   enum { IMAGE_GAP = 5 };           // Gap between button-base and icon-base

   typedef struct tagPANEL
   {
      HWND hWnd;                     // Handle to view
      int iImage;                    // Image Index into ImageList
      bool bEnabled;                 // Is panel enabled?
      bool bExpanded;                // Is panel expanded?
      LPTSTR pstrTitle;              // Display title
      COLORREF clrText;              // Text color. If CLR_INVALID then use default
      COLORREF clrBar1;              // Bar color. If CLR_INVALID then use default
      COLORREF clrBar2;              // Bar color. If CLR_INVALID then use default
      HBITMAP hbmpButton;            // Bitmap representation of button
      SIZE szChild;                  // Preferred size of child pane
      DWORD dwAnimateStopTime;       // Time when animation should stop
      int cy;                        // Current child height
   } PANEL;

   typedef struct tagPANELTHEME
   {
      COLORREF clrBack;
      COLORREF clrTextActive;
      COLORREF clrTextInactive;
      COLORREF clrTextSel;
      COLORREF clrBarActive1;
      COLORREF clrBarActive2;
      COLORREF clrBarInactive1;
      COLORREF clrBarInactive2;
      COLORREF clrBarSel1;
      COLORREF clrBarSel2;
      COLORREF clrBorder;
      int iArc;
   } PANELTHEME;

   CSimpleArray<PANEL> m_aPanels;    // Collection of panels
   int m_iCurSel;                    // Last known selected panel
   CFont m_fntBold;                  // Caption font
   DWORD m_dwExtStyle;               // Extended style flags
   PANELTHEME m_Theme;               // Color configuration
   CIconHandle m_iconCollapse;       // Icon for expander button
   CIconHandle m_iconExpand;         // Icon for expander button
   bool m_bOwnCollapseIcons;         // We own expand icons?
   CImageList m_Images;              // Images for icons
   CImageList m_ImagesGrey;          // Images for grey icons
   SIZE m_szMargin;                  // Margins between window and panels
   int m_cyPadding;                  // Padding between panels
   int m_cyButton;                   // Height of button (including icon)
   int m_cyBar;                      // Height of bar (colored text/caption)
   WORD m_cxLastWidth;               // Last known width of window
   WORD m_cyLastHeight;              // Last known height of window
   DWORD m_dwAnimateTime;            // How long time to allow animation (in ms)
   UINT m_uMsgMouseWheel;            // Mouse wheel registered message

   // Operations

   BOOL SubclassWindow(HWND hWnd)
   {
      ATLASSERT(m_hWnd==NULL);
      ATLASSERT(::IsWindow(hWnd));
      BOOL bRet = CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(hWnd);
      if( bRet ) _Init();
      return bRet;
   }
   // Call this in your WTL PreTranslateMessage handler do properly
   // manage tabbing and other dialog-specific things...
   BOOL PreTranslateMessage(MSG* pMsg)
   {
      if( m_iCurSel < 0 ) return FALSE;
      return ::IsDialogMessage(m_aPanels[m_iCurSel].hWnd, pMsg);
   }
   int GetCurSel() const
   {
      return m_iCurSel;
   }
   void SetCurSel(int iSel)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_iCurSel = iSel;
      _RecalcLayout();
   }
   void DeleteAllItems()
   {
      ATLASSERT(::IsWindow(m_hWnd));
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         if( m_aPanels[i].hbmpButton != NULL ) ::DeleteObject(m_aPanels[i].hbmpButton);
         delete [] m_aPanels[i].pstrTitle;
      }
      m_aPanels.RemoveAll();
      m_iCurSel = -1;
      Invalidate();
   }
   int GetItemCount() const
   {
      return m_aPanels.GetSize();
   }
   int InsertItem(HWND hWndView, LPCTSTR pstrTitle, int iImage = -1, COLORREF clrText = CLR_INVALID)
   {
      ATLASSERT(::IsWindow(hWndView));
      ATLASSERT(!::IsBadStringPtr(pstrTitle,-1));
      ATLASSERT(iImage==-1 || !m_Images.IsNull()); // Need to assign ImageList first
      ATLASSERT(((DWORD)::GetWindowLong(hWndView, GWL_STYLE) & WS_CLIPSIBLINGS)!=0); // Must have CLIPSIBLINGS
      // Assign new parent to panel
      ::SetParent(hWndView, m_hWnd);
      // Make sure the panel is resized to the preferred size
      // before it's added so we can know its size when expanding it!
      RECT rc;
      ::GetWindowRect(hWndView, &rc);
      ATLASSERT(rc.right-rc.left>0 && rc.bottom-rc.top>0);
      // Add the item in the list
      PANEL panel = { 0 };
      panel.hWnd = hWndView;
      ATLTRY( panel.pstrTitle = new TCHAR[::lstrlen(pstrTitle) + 1] );
      if( panel.pstrTitle == NULL ) return -1;
      ::lstrcpy(panel.pstrTitle, pstrTitle);
      panel.bExpanded = true;
      panel.bEnabled = true;
      panel.clrText = clrText;
      panel.clrBar1 = CLR_INVALID;
      panel.clrBar2 = CLR_INVALID;
      panel.iImage = iImage;
      panel.szChild.cx = rc.right - rc.left;
      panel.cy = panel.szChild.cy = rc.bottom - rc.top;
      m_aPanels.Add(panel);
      if( IsWindow() ) Invalidate();
      ::ShowWindow(hWndView, SW_SHOWNOACTIVATE);
      return m_aPanels.GetSize() - 1;
   }
   BOOL GetItemExpanded(int iIndex) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( iIndex < 0 || iIndex >= m_aPanels.GetSize() ) return FALSE;
      return m_aPanels[iIndex].bExpanded == true;
   }
   BOOL SetItemExpanded(int iIndex, BOOL bExpanded, BOOL bAnimate = FALSE)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( iIndex < 0 || iIndex >= m_aPanels.GetSize() ) return FALSE;
      if( m_aPanels[iIndex].bExpanded == (bExpanded == TRUE) ) return TRUE;
      // Send notification
      ::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CPN_EXPANDING), (LPARAM) m_hWnd);
      // Set panel attributes
      PANEL& panel = m_aPanels[iIndex];
      panel.bExpanded = bExpanded == TRUE;
      DWORD dwTick = ::GetTickCount();
      if( bAnimate && (m_dwExtStyle & CPS_EX_NOANIMATE) == 0 ) dwTick += m_dwAnimateTime;
      panel.dwAnimateStopTime = dwTick;
      // Display panel now so animation can be shown
      ::ShowWindow(panel.hWnd, SW_SHOWNOACTIVATE);
      // Start the show
      SetTimer(ANIMATETIMER_ID, 30L);  // 30 ms timer
      SendMessage(WM_TIMER, ANIMATETIMER_ID);
      if( !bAnimate ) {
         _RecalcLayout();
         _RearrangePanels();
         _RecalcScrollBar();
      }
      return TRUE;
   }
   BOOL GetItemEnabled(int iIndex) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( iIndex < 0 || iIndex >= m_aPanels.GetSize() ) return FALSE;
      return m_aPanels[iIndex].bEnabled == true;
   }
   BOOL SetItemEnabled(int iIndex, BOOL bEnabled)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( iIndex < 0 || iIndex >= m_aPanels.GetSize() ) return FALSE;
      m_aPanels[iIndex].bEnabled = bEnabled == TRUE;
      if( (m_dwExtStyle & CPS_EX_DEEPDISABLE) != 0 ) ::EnableWindow(m_aPanels[iIndex].hWnd, bEnabled);
      _RecalcLayout();
      return TRUE;
   }
   BOOL SetItemColors(int iIndex, COLORREF clrText, COLORREF clrBar1 = CLR_INVALID, COLORREF clrBar2 = CLR_INVALID)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( iIndex < 0 || iIndex >= m_aPanels.GetSize() ) return FALSE;
      m_aPanels[iIndex].clrText = clrText;
      m_aPanels[iIndex].clrBar1 = clrBar1;
      m_aPanels[iIndex].clrBar2 = clrBar2;
      _RecalcLayout();
      return TRUE;
   }
   DWORD SetExtendedPanelStyle(DWORD dwStyle)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      DWORD dwOldStyle = m_dwExtStyle;
      m_dwExtStyle = dwStyle;
      Invalidate();
      return dwOldStyle;
   }
   void SetAnimateTime(DWORD dwAnimateTime)
   {
      m_dwAnimateTime = dwAnimateTime;
   }
   void SetExpandBitmaps(UINT nExpand, UINT nCollapse)
   {
      ATLASSERT(m_iconCollapse.IsNull());
      m_iconExpand.LoadIcon(nExpand);
      m_iconCollapse.LoadIcon(nCollapse);
      m_bOwnCollapseIcons = true;
      ATLASSERT(!m_iconExpand.IsNull());
      ATLASSERT(!m_iconCollapse.IsNull());
   }
   void SetExpandBitmaps(HICON hicoExpand, HICON hicoCollapse)
   {
      ATLASSERT(m_iconCollapse.IsNull());
      ATLASSERT(hicoExpand!=NULL);
      ATLASSERT(hicoCollapse!=NULL);
      m_iconExpand = hicoExpand;
      m_iconCollapse = hicoCollapse;
      m_bOwnCollapseIcons = false;
   }
   CImageList SetImageList(HIMAGELIST hImages, int nImageList)
   {
      CImageList hOldImages;
      switch( nImageList ) {
      case LVSIL_NORMAL:
         hOldImages = m_Images;
         m_Images = hImages;
         break;
      case LVSIL_STATE:
         hOldImages = m_ImagesGrey;
         m_ImagesGrey = hImages;
         break;
      default:
         ATLASSERT(false);
      }
      _RecalcLayout();
      return hOldImages;
   }
   void SetMargins(int cx, int cy)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_szMargin.cx = cx;
      m_szMargin.cy = cy;
      _RecalcLayout();
   }
   int GetPadding() const
   {
      return m_cyPadding;
   }
   void SetPadding(int iPadding)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_cyPadding = iPadding;
      _RearrangePanels();
      _RecalcScrollBar();
   }
   PANELTHEME GetPanelTheme() const
   {
      return m_Theme;
   }
   void SetPanelTheme(const PANELTHEME Theme)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_Theme = Theme;
      _RecalcLayout();
   }
   RECT GetPanelRect(int iIndex, BOOL bIncludeButton) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      RECT rc = { 0 };
      if( iIndex < 0 || iIndex >= m_aPanels.GetSize() ) return rc;
      GetClientRect(&rc);
      ::OffsetRect(&rc, 0, -GetScrollPos(SB_VERT));
      ::InflateRect(&rc, -m_szMargin.cx, -m_szMargin.cy);
      for( int i = 0; i <= iIndex; i++ ) {
         if( m_aPanels[i].iImage >= 0 ) rc.top += m_cyButton - m_cyBar;
         rc.top += m_cyBar;
         if( i == iIndex ) {
            rc.bottom = rc.top + m_aPanels[i].cy;
            if( bIncludeButton ) rc.top -= m_cyButton;
            if( !bIncludeButton && (GetStyle() & WS_BORDER) != 0 ) ::InflateRect(&rc, -1, -1);
            return rc;
         }
         rc.top += m_aPanels[i].cy + m_cyPadding;
      }
      ATLASSERT(false);
      return rc;
   }

   // Implementation

   void _Init()
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(GetStyle() & WS_CLIPCHILDREN);

      m_iCurSel = -1;
      m_dwExtStyle = 0;
      m_cxLastWidth = 0;
      m_cyLastHeight = 0;

      CFontHandle font = GetFont();
      if( font.IsNull() ) font = AtlGetDefaultGuiFont();
      LOGFONT lf;
      font.GetLogFont(&lf);
      lf.lfWeight += FW_BOLD;
      if( !m_fntBold.IsNull() ) m_fntBold.DeleteObject();
      m_fntBold.CreateFontIndirect(&lf);
      SetFont(m_fntBold);

      m_szMargin.cx = 10;
      m_szMargin.cy = 12;
      m_cyPadding = 8;
      m_cyButton = 12;
      m_cyBar = 12;

      m_dwAnimateTime = 250;

      m_Theme.clrBack = RGB(195,199,211);
      m_Theme.clrTextActive = RGB(0,0,128);
      m_Theme.clrTextInactive = RGB(120,120,120);
      m_Theme.clrTextSel = RGB(255,255,255);
      m_Theme.clrBarActive1 = RGB(255,255,255);
      m_Theme.clrBarActive2 = RGB(214,215,224);
      m_Theme.clrBarInactive1 = RGB(245,245,245);
      m_Theme.clrBarInactive2 = RGB(184,184,184);
      m_Theme.clrBarSel1 = RGB(45,120,245);
      m_Theme.clrBarSel2 = RGB(128,128,128);
      m_Theme.clrBorder = RGB(0,0,0);
      m_Theme.iArc = 10;

      m_uMsgMouseWheel = ::RegisterWindowMessage(MSH_MOUSEWHEEL);
   }
   void _RecalcLayout()
   {
      // No need to do this before first WM_SIZE is seen
      if( m_cxLastWidth == 0 ) return;
      // Need to recreate all buttons because view changed
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         if( m_aPanels[i].hbmpButton != NULL ) {
            ::DeleteObject(m_aPanels[i].hbmpButton);
            m_aPanels[i].hbmpButton = NULL;
         }
      }
      // Calculate button size
      CClientDC dc = m_hWnd;
      HFONT hOldFont = dc.SelectFont(GetFont());
      TEXTMETRIC tm = { 0 };
      dc.GetTextMetrics(&tm);
      dc.SelectFont(hOldFont);
      SIZE szIcons = { 0 };
      if( !m_Images.IsNull() ) m_Images.GetIconSize(szIcons);
      m_cyBar = max(16 + 6, tm.tmHeight + 6);
      m_cyButton = max(m_cyBar, szIcons.cy + IMAGE_GAP);
      // Repaint
      Invalidate();
   }
   void _RecalcScrollBar()
   {
      // Check that we can manipulate the scrollbar
      if( (m_dwExtStyle & CPS_EX_NOSCROLLBAR) != 0 ) return;
      // Scrollbar support by Anatoly Ivasyuk.
      // Get the location of the last panel in the list
      int iPos = GetScrollPos(SB_VERT);
      RECT rc = GetPanelRect(GetItemCount() - 1, TRUE);
      // Update the scrollbar based on the total height
      SCROLLINFO si = { 0 };
      si.cbSize = sizeof(si);
      si.fMask = SIF_RANGE | SIF_PAGE;
      si.nMin = 0;
      si.nMax = rc.bottom + m_szMargin.cy + iPos;
      si.nPage = m_cyLastHeight;
      SetScrollInfo(SB_VERT, &si, TRUE);
      if( (UINT) iPos > si.nMax - si.nPage ) _RearrangePanels();
   }
   void _RearrangePanels()
   {
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         RECT rc = GetPanelRect(i, FALSE);
         ::SetWindowPos(m_aPanels[i].hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
      }
      Invalidate();
   }
#if defined(_INC_MATH)
   double _CosineInterpolate(double y1, double y2, double mu) const
   {
#ifndef PI
      #define PI 3.1415926535897932384626433832795029L
#endif // PI
      double mu2 = (1.0 - cos(mu * PI)) / 2.0;
      return y1 * (1.0 - mu2) + y2 * mu2;
   }
#endif // _INC_MATH
   void _CreateButton(CDCHandle dc, int iIndex, RECT rcItem)
   {
      // Create bitmap for button-background
      PANEL& panel = m_aPanels[iIndex];
      ::OffsetRect(&rcItem, -rcItem.left, -rcItem.top);
      int cx = rcItem.right - rcItem.left;
      int cy = rcItem.bottom - rcItem.top;
      CDC dcMem;
      dcMem.CreateCompatibleDC(dc);
      CBitmapHandle bmp;
      bmp.CreateCompatibleBitmap(dc, cx, cy);
      HBITMAP hOldBmp = dcMem.SelectBitmap(bmp);
      // Clear background
      dcMem.FillSolidRect(&rcItem, m_Theme.clrBack);
      // Figure out colors
      COLORREF clrBar1 = panel.clrBar1;
      if( clrBar1 == CLR_INVALID ) clrBar1 = m_Theme.clrBarActive1;
      if( iIndex == m_iCurSel && (m_dwExtStyle & CPS_EX_SELHIGHLIGHT) != 0 ) clrBar1 = m_Theme.clrBarSel1;
      if( !panel.bEnabled ) clrBar1 = m_Theme.clrBarInactive1;
      COLORREF clrBar2 = panel.clrBar2;
      if( clrBar2 == CLR_INVALID ) clrBar2 = m_Theme.clrBarActive2;
      if( iIndex == m_iCurSel && (m_dwExtStyle & CPS_EX_SELHIGHLIGHT) != 0 ) clrBar2 = m_Theme.clrBarSel2;
      if( !panel.bEnabled ) clrBar2 = m_Theme.clrBarInactive2;
      // Draw stuff
      if( (m_dwExtStyle & CPS_EX_OWNERDRAW) != 0 )
      {
#ifndef ODS_INACTIVE
         const UINT ODS_INACTIVE = 0x0080;
#endif // ODS_INACTIVE
         DRAWITEMSTRUCT dis = { 0 };
         dis.CtlID = GetDlgCtrlID();
         dis.CtlType = ODT_STATIC;
         dis.itemAction = ODA_DRAWENTIRE;
         dis.hwndItem = m_hWnd;
         dis.hDC = dc;
         dis.itemID = iIndex;
         dis.itemState = 0;
         if( m_iCurSel == iIndex ) dis.itemState |= ODS_SELECTED;
         if( !panel.bExpanded ) dis.itemState |= ODS_INACTIVE;
         if( !panel.bEnabled ) dis.itemState |= ODS_DISABLED;
         dis.rcItem = GetPanelRect(iIndex, FALSE);
         ::SendMessage(GetParent(), WM_DRAWITEM, (WPARAM) dis.CtlID, (LPARAM) &dis);
      }
      else if( (m_dwExtStyle & CPS_EX_FLATSTYLE) != 0 )
      {
         CPen pen;
         pen.CreatePen(PS_SOLID, 1, clrBar2);
         CBrush brush;
         brush.CreateSolidBrush(clrBar1);
         HPEN hOldPen = dcMem.SelectPen(pen);
         HBRUSH hOldBrush = dcMem.SelectBrush(brush);
         dcMem.Rectangle(&rcItem);
         dcMem.SelectBrush(hOldBrush);
         dcMem.SelectPen(hOldPen);
      }
      else
      {
         // Prepare brushes and pens
         CPen pen;
         pen.CreatePen(PS_SOLID, 1, clrBar2);
         CBrush brush;
         brush.CreateSolidBrush(clrBar1);
         HPEN hOldPen = dcMem.SelectPen(pen);
         HBRUSH hOldBrush = dcMem.SelectBrush(brush);
         // Create clip region
         CRgn rgn;
         rgn.CreateRoundRectRgn(rcItem.left, rcItem.top, rcItem.right, rcItem.bottom + 666, m_Theme.iArc, m_Theme.iArc);
         dcMem.SelectClipRgn(rgn);
         // Paint gradient
         if( dcMem.GetDeviceCaps(BITSPIXEL) > 8 ) {
            // This will make 2^6 = 64 fountain steps
            const int nShift = 6;
            int nSteps = 1 << nShift;
            for( int i = 0; i < nSteps; i++ ) {
               // Do a little alpha blending
               BYTE bR = (BYTE) ((GetRValue(clrBar1) * (nSteps - i) +
                          GetRValue(clrBar2) * i) >> nShift);
               BYTE bG = (BYTE) ((GetGValue(clrBar1) * (nSteps - i) +
                          GetGValue(clrBar2) * i) >> nShift);
               BYTE bB = (BYTE) ((GetBValue(clrBar1) * (nSteps - i) +
                          GetBValue(clrBar2) * i) >> nShift);
               // then paint with the resulting color
               RECT r2 = rcItem;
               r2.left = rcItem.left + ((i * (rcItem.right - rcItem.left)) >> nShift);
               r2.right = rcItem.left + (((i + 1) * (rcItem.right - rcItem.left)) >> nShift);
               if( (r2.right - r2.left) > 0 ) dcMem.FillSolidRect(&r2, RGB(bR,bG,bB));
            }
         }
         else {
            dcMem.FillSolidRect(&rcItem, clrBar1);
         }
         dcMem.SelectClipRgn(NULL);
         // Repaint frame
         dcMem.SelectStockBrush(NULL_BRUSH);
         dcMem.RoundRect(rcItem.left, rcItem.top, rcItem.right, rcItem.bottom + 666, m_Theme.iArc, m_Theme.iArc);
         // Done
         dcMem.SelectBrush(hOldBrush);
         dcMem.SelectPen(hOldPen);
      }
      dcMem.SelectBitmap(hOldBmp);
      panel.hbmpButton = bmp.Detach();
   }

   // Message map and handlers

   BEGIN_MSG_MAP(CCollapsiblePanelImpl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
      MESSAGE_HANDLER(WM_TIMER, OnTimer)
      MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
      MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDown)
      MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
      MESSAGE_HANDLER(m_uMsgMouseWheel, OnMouseWheel)
      MESSAGE_HANDLER(WM_PARENTNOTIFY, OnMouseActivate)
      MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
      CHAIN_MSG_MAP( COffscreenDrawRect< T > )
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc();
      _Init();
      return lRes;
   }
   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      DeleteAllItems();
      if( m_bOwnCollapseIcons ) {
         if( !m_iconCollapse.IsNull() ) m_iconCollapse.DestroyIcon();
         if( !m_iconExpand.IsNull() ) m_iconExpand.DestroyIcon();
      }
      if( (m_dwExtStyle & CPS_EX_SHAREIMAGELIST) == 0 ) {
         if( m_Images.IsNull() ) m_Images.Destroy();
         if( m_ImagesGrey.IsNull() ) m_ImagesGrey.Destroy();
      }
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
   {
      if( m_cxLastWidth != LOWORD(lParam) ) {
         m_cxLastWidth = LOWORD(lParam);
         _RecalcLayout();
         _RearrangePanels();
         _RecalcScrollBar();
      }
      if( m_cyLastHeight != HIWORD(lParam) ) {
         m_cyLastHeight = HIWORD(lParam);
         _RecalcScrollBar();
      }
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      bHandled = FALSE;
      if( wParam != ANIMATETIMER_ID ) return 0;
      // Process movement of any animating panel
      bool bStillAnimating = false;
      DWORD dwTick = ::GetTickCount();
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         if( m_aPanels[i].dwAnimateStopTime > 0 ) {
            PANEL& panel = m_aPanels[i];
            if( dwTick >= panel.dwAnimateStopTime ) {
               // Done animating this panel
               panel.dwAnimateStopTime = 0;
               panel.cy = panel.bExpanded ? panel.szChild.cy : 0;
               // Show/hide child window
               ::ShowWindow(panel.hWnd, panel.bExpanded ? SW_SHOWNOACTIVATE : SW_HIDE);
               // Send notification
               ::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CPN_EXPANDED), (LPARAM) m_hWnd);
            }
            else 
            {
#if defined(_INC_MATH)
               double mu;
               double dblTimeDiff = panel.dwAnimateStopTime - dwTick;
               if( dblTimeDiff <= 0.0 || m_dwAnimateTime == 0 ) mu = 1.0;
               else mu = dblTimeDiff / (double) m_dwAnimateTime;
               int iHeight = (int) _CosineInterpolate(0, panel.szChild.cy, mu);
               panel.cy = panel.bExpanded ? panel.szChild.cy - iHeight : iHeight;
#else  // _INC_MATH
               int iDiff = panel.bExpanded ? panel.szChild.cy - panel.cy : panel.cy;
               iDiff /= 2;
               panel.cy = panel.bExpanded ? panel.szChild.cy - iDiff : iDiff;
#endif // _INC_MATH
               bStillAnimating = true;
            }
         }
      }
      _RearrangePanels();
      if( !bStillAnimating ) 
      {
         _RecalcLayout();
         _RecalcScrollBar();
         KillTimer(ANIMATETIMER_ID);
      }
      return 0;
   }
   LRESULT OnVScroll(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      // Scrollbar support added by Anatoly Ivasyuk
      // Get all the vertial scroll bar information
      SCROLLINFO si = { 0 };
      si.cbSize = sizeof(si);
      si.fMask  = SIF_ALL;
      GetScrollInfo(SB_VERT, &si);  
      // Save the position for comparison later on
      int yPos = si.nPos;  
      switch( LOWORD(wParam) ) {
      case SB_TOP:
         // User clicked the HOME keyboard key
         si.nPos = si.nMin;
         break;           
      case SB_BOTTOM:
         // User clicked the END keyboard key
         si.nPos = si.nMax;
         break;          
      case SB_LINEUP:
         // User clicked the top arrow
         si.nPos -= si.nMax / 10;
         break;           
      case SB_LINEDOWN:
         // User clicked the bottom arrow
         si.nPos += si.nMax / 10;
         break;           
      case SB_PAGEUP:
         // User clicked the shaft above the scroll box
         si.nPos -= si.nPage;
         break;           
      case SB_PAGEDOWN:
         // User clicked the shaft below the scroll box
         si.nPos += si.nPage;
         break;           
      case SB_THUMBTRACK:
         // User dragged the scroll box
         si.nPos = si.nTrackPos;
         break;           
      default:
         break; 
      }
      // Set the position and then retrieve it.  Due to adjustments
      //   by Windows it may not be the same as the value set.
      si.fMask = SIF_POS;
      SetScrollInfo(SB_VERT, &si, TRUE);
      GetScrollInfo(SB_VERT, &si);
      if( si.nPos != yPos ) {                    
         _RecalcLayout();
         _RearrangePanels();
         Invalidate();
      }       
      return 0;
   }
   LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      int zDelta = (int) (short) HIWORD(wParam);
      for( int i = 0; i < abs(zDelta); i += 40 ) SendMessage(WM_VSCROLL, MAKEWPARAM(zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0), NULL);
      return 0;
   }
   LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         // Limit click area to button (or just header)
         RECT rc = GetPanelRect(i, TRUE);
         rc.top += m_cyButton - m_cyBar;
         rc.bottom = rc.top + m_cyBar;
         if( (m_dwExtStyle & CPS_EX_EXPANDCLICK) != 0 ) ::SetRect(&rc, rc.right - 30, rc.top + 3, rc.right, rc.bottom - 3);
         if( ::PtInRect(&rc, pt) ) {
            if( GetItemEnabled(i) ) {
              m_iCurSel = i;
              SetItemExpanded(i, !GetItemExpanded(i), TRUE);
              if( (m_dwExtStyle & CPS_EX_SELHIGHLIGHT) != 0 ) _RecalcLayout();
              ::SetFocus(NULL);
              break;
            }
         }
      }
      return 0;
   }
   LRESULT OnMouseActivate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc();
      POINT pt = { 0 };
      ::GetCursorPos(&pt);
      ScreenToClient(&pt);
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         RECT rc = GetPanelRect(i, FALSE);
         if( ::PtInRect(&rc, pt) ) {
            if( GetItemEnabled(i) && m_iCurSel != i ) {
               m_iCurSel = i;
               if( (m_dwExtStyle & CPS_EX_SELHIGHLIGHT) != 0 ) _RecalcLayout();
               ::SetFocus(m_aPanels[m_iCurSel].hWnd);
            }
            break;
         }
      }
      return lRes;
   }

   // Paint override

   void DoPaint(CDCHandle dc, RECT& rect)
   {
      ATLASSERT(!m_iconExpand.IsNull());

      RECT rcClient;
      GetClientRect(&rcClient);

      dc.FillSolidRect(&rect, m_Theme.clrBack);

      ::InflateRect(&rcClient, -m_szMargin.cx, -m_szMargin.cy);

      HFONT hOldFont = dc.SelectFont(GetFont());
      dc.SetBkMode(TRANSPARENT);
      for( int i = 0; i < m_aPanels.GetSize(); i++ ) {
         RECT rcItem = GetPanelRect(i, TRUE);
         // Should we paint this button at all?
         RECT rcButton = rcItem;
         rcButton.bottom = rcButton.top + m_cyButton;
         RECT rcDummy = { 0 };
         if( !::IntersectRect(&rcDummy, &rect, &rcButton) ) continue;
         // Recreate button bitmap?
         const PANEL& panel = m_aPanels[i];
         RECT rcBar = { rcButton.left, rcButton.bottom - m_cyBar, rcButton.right, rcButton.bottom };
         if( panel.hbmpButton == NULL ) _CreateButton(dc, i, rcBar);
         ATLASSERT(panel.hbmpButton!=NULL);
         // Paint button
         CDC dcBmp;
         dcBmp.CreateCompatibleDC(dc);
         HBITMAP hOldBmp = dcBmp.SelectBitmap(panel.hbmpButton);
         dc.BitBlt(rcBar.left, rcBar.top, rcBar.right - rcBar.left, rcBar.bottom, dcBmp, 0, 0, SRCCOPY);
         dcBmp.SelectBitmap(hOldBmp);
         // Rect for text
         RECT rcText = rcButton;
         rcText.left += 10;
         rcText.right -= 4;
         rcText.top = rcText.bottom - m_cyBar;
         // Add expander
         if( (m_dwExtStyle & CPS_EX_NOEXPANDBUTTON) == 0 ) {
            dc.DrawIconEx(rcBar.right - 24, rcBar.top + 3, panel.bExpanded ? m_iconCollapse : m_iconExpand, 16, 16);
            rcText.right -= 26;
         }
         // Add icon
         if( panel.iImage >= 0 && !m_Images.IsNull() ) {
            SIZE szIcon;
            m_Images.GetIconSize(szIcon);
            POINT pt = { rcItem.left + 2, rcItem.top + 2 };
            if( !panel.bEnabled && !m_ImagesGrey.IsNull() ) {
               m_ImagesGrey.Draw(dc, panel.iImage, pt, ILD_TRANSPARENT);
            }
            else {
               m_Images.Draw(dc, panel.iImage, pt, ILD_TRANSPARENT);
            }
            rcText.left += szIcon.cx;
         }
         // Print text
         COLORREF clrText = panel.clrText;
         if( clrText == CLR_INVALID ) clrText = m_Theme.clrTextActive;
         if( i == m_iCurSel && (m_dwExtStyle & CPS_EX_SELHIGHLIGHT) != 0 ) clrText = m_Theme.clrTextSel;
         if( !m_aPanels[i].bEnabled ) clrText = m_Theme.clrTextInactive;
         dc.SetTextColor(clrText);
         dc.DrawText(panel.pstrTitle, -1, &rcText, DT_SINGLELINE | DT_END_ELLIPSIS | DT_VCENTER);
         // Optional border around child
         if( GetStyle() & WS_BORDER ) {
            RECT rcChild = rcItem;
            rcChild.top += m_cyButton;
            CPen pen;
            pen.CreatePen(PS_SOLID, 1, m_Theme.clrBorder);
            HPEN hOldPen = dc.SelectPen(pen);
            HBRUSH hOldBrush = dc.SelectStockBrush(NULL_BRUSH);
            dc.Rectangle(&rcChild);
            dc.SelectBrush(hOldBrush);
            dc.SelectPen(hOldPen);
         }
      }
      dc.SelectFont(hOldFont);
   }
};

class CCollapsiblePanelCtrl : public CCollapsiblePanelImpl<CCollapsiblePanelCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_CollapsiblePanel"))
};


#endif // !defined(AFX_COLLAPSIBLEPANEL_H__20031129_797C_31F4_B029_0080AD509054__INCLUDED_)

