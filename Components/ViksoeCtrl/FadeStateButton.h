#if !defined(AFX_FADESTATEBUTTON_H__20071124_346D_BE68_E300_0080AD509054__INCLUDED_)
#define AFX_FADESTATEBUTTON_H__20071124_346D_BE68_E300_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlframe.h>

#ifndef _WTL_IMAGEHELPERS_
   #error "This source file requires ImageHelpers.h included"
#endif // _WTL_IMAGEHELPERS_


// FadeState Button styles
#define FSTBS_COMPOSITE    0x00000001
#define FSTBS_CAPTUREBKG   0x00000002
#define FSTBS_DOUBLEBUFFER 0x00000004


template< class T, class TBase = WTL::CButton, class TWinTraits = ATL::CControlWinTraits >
class ATL_NO_VTABLE CFadeStateButtonImpl : 
   public ATL::CWindowImpl< T, TBase, TWinTraits >,
   public WTL::CDoubleBufferImpl< T >
{
public:
   DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

   typedef WTL::CDoubleBufferImpl< T > _DblBuffer;

   enum { FADE_TIMERID = 5 };

   enum
   {
      IMAGE_DISABLED = 0,
      IMAGE_NORMAL   = 1,
      IMAGE_HOT      = 2,
      IMAGE_PRESSED  = 3,
      NUM_STATES,
   };

   CString m_sToolTipText; // ToolTip text
   CToolTipCtrl m_tip;     // ToolTip control
   CBrush m_brBack;        // Brush background (when FSTBS_CAPTUREBKG is active)
   CBitmapHandle m_bitmap; // Bitmap containing button graphics (all states)
   BITMAP m_bmInfo;             // Information about button bitmap
   COLORREF m_clrBack;          // Background color (solid when FSTBS_CAPTUREBKG is not active)

   DWORD m_dwStyle;             // Extended buttons tyles
   bool m_bPressed;             // Is button pressed?
   bool m_bTracking;            // Is button hot?
   bool m_bFocus;               // Is button focused?
   bool m_bDeleteOnDestroy;     // Delete class instance on window destuction
   int m_iLastImage;            // Last image shown
   int m_iDimImage;             // Other image in fade transition
   int m_iSpeed;                // Fade speed
   DWORD m_uFade;               // Fade phase
   DWORD m_dwFadeTick;          // Last Fade tick

   // Operations

   CFadeStateButtonImpl() :
      m_iLastImage(IMAGE_NORMAL),
      m_iDimImage(IMAGE_NORMAL),
      m_iSpeed(13),
      m_uFade(255),
      m_dwStyle(0),
      m_bFocus(false),
      m_bPressed(false),
      m_bTracking(false),
      m_bDeleteOnDestroy(false)
   {
   }

   BOOL SubclassWindow(HWND hWnd)
   {
#if (_MSC_VER >= 1300)
      BOOL bRet = ATL::CWindowImpl< T, TBase, TWinTraits>::SubclassWindow(hWnd);
#else // _MSC_VER >= 1300
      typedef ATL::CWindowImpl< T, TBase, TWinTraits> _baseClass;
      BOOL bRet = _baseClass::SubclassWindow(hWnd);
#endif // _MSC_VER >= 1300
      if( bRet ) Init();
      return bRet;
   }

   void OnFinalMessage(HWND /*hWnd*/)
   {
      if( m_bDeleteOnDestroy ) delete this;
   }

   DWORD SetFadeButtonStyle(DWORD dwStyle)
   {
      DWORD dwOldStyle = m_dwStyle;
      CWindow wndParent = GetParent();
      if( (dwStyle & FSTBS_COMPOSITE) != 0 ) m_clrBack = RGB(0,0,0);
      if( (wndParent.GetExStyle() & WS_EX_COMPOSITED) != 0 ) dwStyle &= ~FSTBS_DOUBLEBUFFER;
      m_dwStyle = dwStyle;
      if( IsWindow() ) Invalidate();
      return dwOldStyle;
   }

   void SetDeleteOnDestroy()
   {
      m_bDeleteOnDestroy = true;
   }

   void SetToolTipText(LPCTSTR pstrText)
   {
      m_sToolTipText = pstrText;
      if( !m_tip.IsWindow() ) return;
      m_tip.Activate(FALSE);
      if( !m_sToolTipText.IsEmpty() ) {
         m_tip.Activate(TRUE);
         m_tip.AddTool(m_hWnd, (LPCTSTR) m_sToolTipText);
      }
   }

   void SetBkColor(COLORREF clrBack)
   {
      m_clrBack = clrBack;
      if( IsWindow() ) Invalidate();
   }

   void SetFadeSpeed(int iSpeed)
   {
      if( iSpeed <= 0 ) iSpeed = 13;
      m_iSpeed = iSpeed;
   }

   void SetBitmap(UINT nRes, LPCTSTR pstrRcType)
   {
      CBitmapHandle bmp = AtlLoadGdiplusImage(nRes, pstrRcType);
      ATLASSERT(!bmp.IsNull());
      SetBitmap(bmp);
   }
   void SetBitmap(HBITMAP hBitmap)
   {
      if( !m_brBack.IsNull() ) m_brBack.DeleteObject();
      m_bitmap = hBitmap;
      if( hBitmap == NULL ) return;
      m_bitmap.GetBitmap(m_bmInfo);
      ATLASSERT(m_bmInfo.bmBitsPixel==32);
      if( IsWindow() ) Invalidate();
   }
   HBITMAP GetBitmap() const
   {
      return m_bitmap;
   }
   void SizeToBitmap()
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(!m_bitmap.IsNull());
      ResizeClient(m_bmInfo.bmWidth / NUM_STATES, m_bmInfo.bmHeight);
   }

   // Message map and handlers

   BEGIN_MSG_MAP(CFadeStateButtonImpl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
      MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
      MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClick)
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
      MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)
      MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
      MESSAGE_HANDLER(WM_KILLFOCUS, OnFocus)
      MESSAGE_HANDLER(WM_ENABLE, OnEnable)
      MESSAGE_HANDLER(WM_TIMER, OnTimer)
      MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, OnPosChanging)
      if( (m_dwStyle & FSTBS_DOUBLEBUFFER) != 0 ) 
      {
         CHAIN_MSG_MAP( _DblBuffer )
      }
      else
      {
         MESSAGE_HANDLER(WM_PAINT, OnPaint)
         MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
         MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      }
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      Init();
      bHandled = FALSE;
      return 1;
   }
   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      if( m_tip.IsWindow() ) {
         m_tip.DestroyWindow();
         m_tip.m_hWnd = NULL;
      }
      bHandled = FALSE;
      return 1;
   }

   LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   {
      MSG msg = { m_hWnd, uMsg, wParam, lParam };
      if( m_tip.IsWindow() ) m_tip.RelayEvent(&msg);
      bHandled = FALSE;
      return 1;
   }
   LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      if( !m_bTracking ) {
         _StartTrackMouseLeave();
         m_bTracking = true;
         Invalidate();
      }
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      if( m_bTracking ) {
         m_bTracking = false;
         Invalidate();
      }
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
      if( ::GetCapture() == m_hWnd ) m_bPressed = true;
      // Bring back this legacy notification
      ::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_PUSHED), (LPARAM) m_hWnd);
      return lRet;
   }
   LRESULT OnLButtonDblClick(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      // HACK: Ideally we would remove the CS_DBLCLCKS class style, but since we're
      //       subclassing the control we're forced to make it act like a regular click.
      //       Otherwise double-clicks will not show the button as pushed.
      return SendMessage(WM_LBUTTONDOWN, wParam, lParam);
   } 
   LRESULT OnCaptureChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( m_bPressed ) m_bPressed = false;
      Invalidate();
      return 0;
   }

   LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      if( wParam == FADE_TIMERID ) Invalidate();
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnPosChanging(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( !m_brBack.IsNull() ) m_brBack.DeleteObject();
      return 0;
   }

   LRESULT OnFocus(UINT uMsg, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      m_bFocus = (uMsg == WM_SETFOCUS);
      Invalidate();
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnEnable(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      Invalidate();
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

   // Implementation

   void Init()
   {
      // We need this style to prevent Windows from painting the button
      ModifyStyle(0, BS_OWNERDRAW);

      // Create a tool tip
      m_tip.Create(m_hWnd);
      ATLASSERT(m_tip.IsWindow());
      SetToolTipText(m_sToolTipText);

      m_clrBack = ::GetSysColor(COLOR_WINDOW);
      if( (m_dwStyle & FSTBS_COMPOSITE) != 0 ) m_clrBack = RGB(0,0,0);

      // Get tooltip text from caption
      TCHAR szToolTipText[300] = { 0 };
      GetWindowText(szToolTipText, (sizeof(szToolTipText) / sizeof(TCHAR)) - 1);
      if( ::lstrlen(szToolTipText) > 0 ) SetToolTipText(szToolTipText);

      if( !IsWindowEnabled() ) m_iLastImage = m_iDimImage = IMAGE_DISABLED;
   }

   void DoPaint(CDCHandle dc)
   {
      CRect rcClient;
      GetClientRect(&rcClient);

      // Paint background
      if( (m_dwStyle & FSTBS_CAPTUREBKG) != 0 ) 
      {
         // Even if AtlGetBackgroundBrush() tries to capture the background with WM_ERASEBKGND
         // too, it doesn't seem to work properly. So you must put all parent painting in the
         // WM_PAINT handler.
         if( m_brBack.IsNull() ) m_brBack = AtlGetBackgroundBrush(m_hWnd, ::GetParent(m_hWnd));
         HBRUSH hOldBrush = dc.SelectBrush(m_brBack);
         dc.PatBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), PATCOPY);
         dc.SelectBrush(hOldBrush);
      }
      else
      {
         dc.FillSolidRect(rcClient, m_clrBack);
      }

      // Figure out which image we're displaying
      int iImage = IMAGE_NORMAL;
      if( m_bTracking ) iImage = IMAGE_HOT;
      if( m_bPressed ) iImage = IMAGE_PRESSED;
      if( !IsWindowEnabled() ) iImage = IMAGE_DISABLED;

      DWORD uState = GetState();
      if( (uState & BST_PUSHED) != 0 ) iImage = IMAGE_PRESSED;
      if( (uState & BST_CHECKED) != 0 ) iImage = IMAGE_PRESSED;

      CDC dcCompat;
      dcCompat.CreateCompatibleDC(dc);
      ATLASSERT(!m_bitmap.IsNull());
      HBITMAP hOldBitmap = dcCompat.SelectBitmap(m_bitmap);

      DWORD dwTick = ::GetTickCount();

      // If the image changed; we may need to start a fade operation...
      if( iImage != m_iLastImage ) {
         if( iImage == IMAGE_PRESSED || m_iLastImage == IMAGE_PRESSED || !IsWindowVisible() ) {
            m_iLastImage = m_iDimImage = iImage;
            m_uFade = 255;
            KillTimer(FADE_TIMERID);
         }
         else {
            m_iDimImage = m_iLastImage;
            m_iLastImage = iImage;
            m_uFade = (255 - m_uFade) * 2;
            if( m_uFade > 255 ) m_uFade = 255;
            m_dwFadeTick = dwTick;
            SetTimer(FADE_TIMERID, 20);  // 20ms
         }
      }

      // Determine transition phase between the two images
      if( m_uFade < 255 ) {
         m_uFade += (dwTick - m_dwFadeTick) * 10 / m_iSpeed;  // Speed calculation
         m_dwFadeTick = dwTick;
         if( m_uFade >= 255 ) {
            m_uFade = 255;
            KillTimer(FADE_TIMERID);
         }
      }

      int xoffset1 = iImage * (m_bmInfo.bmWidth / NUM_STATES);
      int xoffset2 = m_iDimImage * (m_bmInfo.bmWidth / NUM_STATES);

      BLENDFUNCTION bf = { 0 };
      bf.BlendOp = AC_SRC_OVER; 
      bf.BlendFlags = 0; 
      bf.AlphaFormat = AC_SRC_ALPHA;
      if( m_uFade == 255 ) {
         bf.SourceConstantAlpha = 255;
         dc.AlphaBlend(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), dcCompat, xoffset1, 0, m_bmInfo.bmWidth / NUM_STATES, m_bmInfo.bmHeight, bf);
      }
      else {
         bf.SourceConstantAlpha = (BYTE)(255 - m_uFade);
         dc.AlphaBlend(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), dcCompat, xoffset2, 0, m_bmInfo.bmWidth / NUM_STATES, m_bmInfo.bmHeight, bf);
         // ---
         if( m_uFade >= 128 ) bf.SourceConstantAlpha = 255;
         else bf.SourceConstantAlpha = (BYTE)((m_uFade - 255) * 2);
         dc.AlphaBlend(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), dcCompat, xoffset1, 0, m_bmInfo.bmWidth / NUM_STATES, m_bmInfo.bmHeight, bf);
      }

      dcCompat.SelectBitmap(hOldBitmap);
   }

   BOOL _StartTrackMouseLeave()
   {
      TRACKMOUSEEVENT tme = { 0 };
      tme.cbSize = sizeof(tme);
      tme.dwFlags = TME_LEAVE;
      tme.hwndTrack = m_hWnd;
      return _TrackMouseEvent(&tme);
   }
};


class CFadeStateButtonCtrl : public CFadeStateButtonImpl<CFadeStateButtonCtrl>
{
public:
   DECLARE_WND_SUPERCLASS(_T("WTL_FadeStateButton"), GetWndClassName())
};
//////////////////////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__

namespace ViksoeCtrl
{
   class CFadeStateButtonCtrlComp:public CFadeStateButtonCtrl,public ControlComponent<CFadeStateButtonCtrlComp>
   {
   public:
      CFadeStateButtonCtrlComp(char * _name);
      ~CFadeStateButtonCtrlComp(void);
   
      BEGIN_MSG_MAP(CFadeStateButtonCtrlComp)
         CHAIN_MSG_MAP(ControlComponent<CFadeStateButtonCtrlComp>)
         CHAIN_MSG_MAP(CFadeStateButtonCtrl)
      END_MSG_MAP()
      
      BOOL CreateComponent(Component * _Parent);
      void InitProperty(void);
   };
};

#endif

#endif // !defined(AFX_FADESTATEBUTTON_H__20071124_346D_BE68_E300_0080AD509054__INCLUDED_)

