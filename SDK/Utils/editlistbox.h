#if !defined(__EDITLISTBOX_H_)
#define __EDITLISTBOX_H_


// Change these resource ID:s if you have collisions...
#ifdef RC_INVOKED
#define IDB_EDITLISTBOX 690
#else
#define IDB_EDITLISTBOX MAKEINTRESOURCE(690)
#endif // RC_INVOKED

#ifndef RC_INVOKED

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CEditListBox - Editable List box (ala DevStudio6)
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2001 Bjarke Viksoe.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//
// Fixes by Ludvig A. Norin (Ludvig@home.se), 2002:
//   + Added an empty last item
//   + Fixed enable/disable of the buttons
//   + Created a fixed implementation of the CBitmapButton class
//   + Recreated the IDB_EDITLISTBOX icons to resemble VS6 exactly
//   + Changed the button layout algorithm to match VS6 style
//   + Changed the heading background color to COLOR_BTNFACE
//   + Created a resource include file for the bitmap
//     - In VS6, menu View->Resource includes..., add the line
//       #include "EditListBox.rc"
//       to the "Compile-time directives" section, and put the 
//       EditListBox files, including the Res\ directory
//       in the VS6 Include path. 
//       You should not define your own IDB_EDITLISTBOX resource,
//       it just works<tm>. (This is how it's done in some WTL
//       classes).
#ifndef __cplusplus
   #error WTL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLCTRLS_H__
   #error EditListBox.h requires atlctrls.h to be included first
#endif

#ifndef __ATLCTRLX_H__
   #error EditListBox.h requires atlctrlx.h to be included first
#endif


// EditListBox Window styles
#define EDLS_NOMOVEBUTTONS   0x00000001
#define EDLS_BROWSE          0x00000002

// EditListBox Notification messages
#define EDLN_FIRST           (0U-1900U)
#define EDLN_LAST            (0U-1950U)

#define EDLN_BROWSE          (EDLN_FIRST-1)
#define EDLN_ITEMCHANGING    (EDLN_FIRST-2)
#define EDLN_ITEMCHANGED     (EDLN_FIRST-3)
#define EDLN_INSERTITEM      (EDLN_FIRST-4)
#define EDLN_DELETEITEM      (EDLN_FIRST-5)
#define EDLN_BEGINLABELEDIT  (EDLN_FIRST-6)
#define EDLN_ENDLABELEDIT    (EDLN_FIRST-7)

typedef struct 
{
    NMHDR hdr;
    int iIndex;
} NMEDITLIST, *PNMEDITLIST;

// Internal EditListBox command messages
#define EDLM_NEW        0x0210
#define EDLM_DELETE     0x0211
#define EDLM_ITEMUP     0x0212
#define EDLM_ITEMDOWN   0x0213

#define WM_EDITLIST_CLEANUP WM_USER+124


// Fixed CBitmapButton class - code copied from atlctrlx.h,
// changed marked with FIX BEGIN - FIX END comments
//
// Written by Ludvig A. Norin, Ludvig@home.se
class CFixedBitmapButton : public CBitmapButtonImpl<CFixedBitmapButton>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_FixedBitmapButton"), GetWndClassName())

	CFixedBitmapButton(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE, HIMAGELIST hImageList = NULL) 
      : CBitmapButtonImpl<CFixedBitmapButton>(dwExtendedStyle, hImageList)
	{ 
   }

	void DoPaint(CDCHandle dc)
	{
		ATLASSERT(m_ImageList.m_hImageList != NULL); // image list must be set
		ATLASSERT(m_nImage[0] != -1); 		// main bitmap must be set

		// set bitmap according to the current button state
		int nImage = -1;
		bool bHover = IsHoverMode();
		if(m_fPressed == 1)
			nImage = m_nImage[_nImagePushed];
		else if((!bHover && m_fFocus == 1) || (bHover && m_fMouseOver == 1))
			nImage = m_nImage[_nImageFocusOrHover];
		else if(!IsWindowEnabled())
			nImage = m_nImage[_nImageDisabled];
		if(nImage == -1)	// not there, use default one
			nImage = m_nImage[_nImageNormal];

		// draw the button image
		int xyPos = 0;
		if((m_fPressed == 1) && ((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0) && (m_nImage[_nImagePushed] == -1))
			xyPos = 1;

      // These are fixes to the CBitmapButtonImpl implementation,
      // which paints the bitmap at 0,0, which is where the border
      // should be (if it is enabled)
      // FIX START
      if (m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) xyPos++;
      if (m_dwExtendedStyle & BMPBTN_AUTO3D_DOUBLE) xyPos+=2;
      // FIX END


      // The original CBitmapButton implementation required different
      // icons for enabled/disabled buttons. If no disabled image was
      // supplied, it's impossible to see that the button is disabled!
      // Who came up with that brilliant idea?! Anyway, here's a fix
      // that use DrawState, if no disabled image was supplied.
      // FIX START
      if (!IsWindowEnabled() && (nImage == m_nImage[_nImageNormal]))
         ::DrawState(dc, NULL, NULL, (LPARAM)m_ImageList.GetIcon(nImage), 0, xyPos, xyPos, 0, 0, DST_ICON|DSS_DISABLED);
      else
		   m_ImageList.Draw(dc, nImage, xyPos, xyPos, ILD_NORMAL);
      // FIX END

		// draw 3D border if required
		if((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0)
		{
			RECT rect;
			GetClientRect(&rect);

			if(m_fPressed == 1)
				dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_SUNKENOUTER : EDGE_SUNKEN, BF_RECT);
			else if(!bHover || m_fMouseOver == 1)
				dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_RAISEDINNER : EDGE_RAISED, BF_RECT);

			if(!bHover && m_fFocus == 1)
			{
				::InflateRect(&rect, -2 * ::GetSystemMetrics(SM_CXEDGE), -2 * ::GetSystemMetrics(SM_CYEDGE));
				dc.DrawFocusRect(&rect);
			}
		}
	}

   // Also, the border is not erased in hover mode, so we
   // need to override the WM_ERASEBKGND implementation in 
   // CBitmapButtonImpl:
   // FIX START
	BEGIN_MSG_MAP(CFixedBitmapButton)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
      CHAIN_MSG_MAP(CBitmapButtonImpl<CFixedBitmapButton>)
	END_MSG_MAP()

	LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
      if (IsHoverMode()) 
      {
         bHandled = TRUE;
         DefWindowProc(uMsg, wParam, lParam);
      }
      else
      {
         bHandled = FALSE;
      }
		return 0;
	}
   // FIX END
};


template <class T, class TBase = CWindow, class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CEditListBoxImpl : 
   public CWindowImpl<T, TBase, TWinTraits>
{
public:
   CListBox      m_wndList;
   CContainedWindowT<CEdit> m_wndEdit;
   CButton       m_wndBrowse;
   CImageList    m_wndImages;
   CFixedBitmapButton m_wndButtons[4];
   short         m_nButtons;
   CString       m_strLastItem;

   typedef CEditListBoxImpl< T, TBase, TWinTraits > thisClass;
   BEGIN_MSG_MAP(thisClass)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_ENABLE, OnEnable)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
      MESSAGE_HANDLER(WM_VKEYTOITEM, OnKeyDown)
      COMMAND_CODE_HANDLER(LBN_SELCHANGE, OnSelChange)
      COMMAND_CODE_HANDLER(LBN_DBLCLK, OnDblClick)
      COMMAND_ID_HANDLER(EDLM_NEW, OnNew)
      COMMAND_ID_HANDLER(EDLM_DELETE, OnDelete)
      COMMAND_ID_HANDLER(EDLM_ITEMUP, OnUp)
      COMMAND_ID_HANDLER(EDLM_ITEMDOWN, OnDown)
      MESSAGE_HANDLER(WM_EDITLIST_CLEANUP, OnCleanUp)
      COMMAND_CODE_HANDLER(BN_CLICKED, OnBrowseClick)
   ALT_MSG_MAP(1) // Edit control
      MESSAGE_HANDLER(WM_GETDLGCODE, OnEditGetDlgCode)
      MESSAGE_HANDLER(WM_CHAR, OnEditKey)
      MESSAGE_HANDLER(WM_KILLFOCUS, OnEditLostFocus)
   END_MSG_MAP()

   CEditListBoxImpl() : m_wndEdit(this, 1), m_nButtons(0), m_strLastItem(_T("Click here to add item"))
   {
   }

   ~CEditListBoxImpl()
   {
      m_wndImages.Destroy();
   }

   // Operations

   void SetAddItemCaption(CString const &str)
   {
      ATLASSERT(!::IsWindow(m_wndList.m_hWnd));
      m_strLastItem = str;
   }

   BOOL SubclassWindow(HWND hWnd)
   {
      ATLASSERT(m_hWnd==NULL);
      ATLASSERT(::IsWindow(hWnd));
      BOOL bRet = CWindowImpl< CEditListBox, CWindow, CControlWinTraits >::SubclassWindow(hWnd);
      if(bRet) _Init();
      return bRet;
   }

   int GetSelectedIndex() const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      int idx = m_wndList.GetCurSel();
      // Hack to make an empty last item
      if (idx != LB_ERR)
         idx = ((idx-1) == -1) ? LB_ERR : --idx;

      return idx;
   }

   void SetMaxText(int iMax)
   {
      m_wndEdit.LimitText(iMax);
   }

   int InsertItem(int iIndex, LPCTSTR pstrText)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(!::IsBadStringPtr(pstrText,-1));

      // Hack to make an empty last item
      if (iIndex > GetItemCount())
         return FALSE;
      int idx = iIndex;
      if (iIndex == -1) idx = GetItemCount();

      idx = m_wndList.InsertString(idx, pstrText);
      if( idx==0 )
          m_wndList.SetCurSel(0);
      return idx;
   }
   
   BOOL SetItemData(int iIndex, void * data)
   {
       ATLASSERT(::IsWindow(m_hWnd));
       return m_wndList.SetItemData(iIndex, (DWORD_PTR)data) >=0;
   }

   void * GetItemData(int iIndex)
   {
       ATLASSERT(::IsWindow(m_hWnd));
       return (void *)m_wndList.GetItemData(iIndex);
   }
   
   BOOL SelectItem(int iIndex)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      // Hack to make an empty last item
      if (iIndex >= GetItemCount())
         return FALSE;

      return m_wndList.SetCurSel(iIndex) != LB_ERR;
   }

   int FindItem(LPCTSTR pstrText) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(!::IsBadStringPtr(pstrText,-1));
      return m_wndList.FindString(-1, pstrText);
   }

   int FindItemExact(LPCTSTR pstrText) const
   {
       ATLASSERT(::IsWindow(m_hWnd));
       ATLASSERT(!::IsBadStringPtr(pstrText,-1));
       return m_wndList.FindStringExact(-1, pstrText);
   }

   BOOL BrowseSelected()
   {
      if( (GetStyle() & EDLS_BROWSE)==0 ) return FALSE;
      if( m_wndList.GetCurSel()==-1 ) return FALSE;
      BOOL bDummy;
      OnBrowseClick(0, 0, 0, bDummy);
      return TRUE;
   }

   void DeleteAllItems()
   {
      m_wndList.ResetContent();
      _InsertEmptyLastItem();
   }

   BOOL DeleteItem(int iIndex)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(iIndex>=0);
 
      // Hack to make an empty last item
      if (iIndex >= GetItemCount())
         return FALSE;

      return m_wndList.DeleteString(iIndex) != LB_ERR;
   }

   BOOL SetItemText(int iIndex, LPCTSTR pstrText)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(iIndex>=0);
      ATLASSERT(!::IsBadStringPtr(pstrText,-1));

      // Hack to make an empty last item
      if (!DeleteItem(iIndex)) return FALSE;

      return InsertItem(iIndex, pstrText) != LB_ERR;
   }

   BOOL GetItemText(int iIndex, LPTSTR pstrText, UINT cchMax) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(iIndex>=0);
      ATLASSERT(!::IsBadWritePtr(pstrText, cchMax));
      *pstrText = _T('\0');

      // Hack to make an empty last item
      if (iIndex >= GetItemCount()) return FALSE;

      if( (UINT)m_wndList.GetTextLen(iIndex)>cchMax ) return FALSE;
      return m_wndList.GetText(iIndex, pstrText);
   }

   int GetItemCount() const
   {
      ATLASSERT(::IsWindow(m_hWnd));

      // Hack to make an empty last item
      int i = m_wndList.GetCount();
      return (i == 0) ? 0 : (i-1);
   }

   HWND GetEditCtrl() const
   {
      return m_wndEdit;
   }

   // Implementation

   void _Init()
   {
      DWORD dwStyle = GetStyle();

      RECT rc;
      GetClientRect(&rc);

      //m_wndImages.Create(IDB_EDITLISTBOX, 20, 4, RGB(255,0,255));
      m_wndImages.Create(IDB_EDITLISTBOX, 16, 4, RGB(192,192,192));
      m_wndList.Create(m_hWnd, rcDefault, NULL, 
         WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
         LBS_NOTIFY | LBS_HASSTRINGS | LBS_WANTKEYBOARDINPUT | WS_VSCROLL|LBS_NOINTEGRALHEIGHT,
         WS_EX_CLIENTEDGE);
      ATLASSERT(m_wndList.IsWindow());
      m_wndList.SetFont(AtlGetDefaultGuiFont());
#ifndef __WTLBUILDER__
      m_wndEdit.Create(this, 1, m_wndList, &rcDefault, NULL, WS_BORDER | WS_CHILD | ES_AUTOHSCROLL);
      ATLASSERT(m_wndEdit.IsWindow());
      m_wndEdit.SetFont(AtlGetDefaultGuiFont());
      SetMaxText(MAX_PATH);
#endif
      m_wndBrowse.Create(m_hWnd, rcDefault, _T("..."), WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
      ATLASSERT(m_wndBrowse.IsWindow());
      m_wndBrowse.SetFont(AtlGetDefaultGuiFont());
#ifndef __WTLBUILDER__
      // Resize items
      RECT rcEdit;
      m_wndEdit.GetWindowRect(&rcEdit);
      int nHeight;
      nHeight = max( rcEdit.bottom-rcEdit.top, m_wndList.GetItemHeight(0) );
      nHeight += 4;
      m_wndList.SetItemHeight(0, nHeight);
#endif
      // Create navigation buttons
      _AddButton(EDLM_NEW, 0);
      _AddButton(EDLM_DELETE, 1);
      if( (dwStyle & EDLS_NOMOVEBUTTONS)==0 ) {
         _AddButton(EDLM_ITEMUP, 2);
         _AddButton(EDLM_ITEMDOWN, 3);
      }

      // Create the empty last item
      _InsertEmptyLastItem();

      // Resize control
      BOOL bDummy;
      OnSize(WM_SIZE, SIZE_RESTORED, 0, bDummy);
      _UpdateButtons();
   }

   void _AddButton(int iCmd, int iImage)
   {
      ATLASSERT(m_nButtons < sizeof(m_wndButtons)/sizeof(*m_wndButtons));
      m_wndButtons[m_nButtons].Create(m_hWnd, rcDefault, NULL, 0,0, iCmd);
      m_wndButtons[m_nButtons].SetImageList(m_wndImages);
      m_wndButtons[m_nButtons].SetImages(iImage);
      m_wndButtons[m_nButtons].SetBitmapButtonExtendedStyle(BMPBTN_AUTOSIZE | BMPBTN_HOVER | BMPBTN_AUTO3D_SINGLE | BMPBTN_SHAREIMAGELISTS);
      m_nButtons++;
   }

   LRESULT _SendNotifyMsg(UINT code, int iIndex) const
   {
      NMEDITLIST nm = { 0 };
      nm.hdr.hwndFrom = m_hWnd;
      nm.hdr.idFrom = GetDlgCtrlID();
      nm.hdr.code = code;
      nm.iIndex = iIndex;
      return ::SendMessage(GetParent(), WM_NOTIFY, nm.hdr.idFrom, (LPARAM)&nm);
   }

   void _BeginEdit(int iIndex)
   {
      ATLASSERT(iIndex>=0);
      if( iIndex<0 ) return;

      // Hack to make an empty last item
      if (iIndex == GetItemCount())
      {
         iIndex = m_wndList.InsertString(iIndex, _T(""));
         m_wndList.SetCurSel(iIndex);
      }

      // Allow owner to cancel action
      if( _SendNotifyMsg(EDLN_BEGINLABELEDIT, iIndex) != 0 ) return;
      
      // Copy text to Edit control
      int len = m_wndList.GetTextLen(iIndex)+1;
      LPTSTR pstr = (LPTSTR)_alloca(len*sizeof(TCHAR));
      ATLASSERT(pstr);
      m_wndList.GetText(iIndex, pstr);
      m_wndEdit.SetWindowText(pstr);

      RECT rc;
      m_wndList.GetItemRect(iIndex, &rc);
      if( GetStyle() & EDLS_BROWSE ) {
         int cx = rc.bottom - rc.top;
         RECT rcBrowse = { rc.right-cx, rc.top, rc.right, rc.bottom };
         m_wndList.MapWindowPoints(m_hWnd, &rcBrowse);
         m_wndBrowse.SetWindowPos(HWND_TOP, &rcBrowse, SWP_SHOWWINDOW|SWP_NOACTIVATE);
         rc.right -= cx;
      }

      m_wndEdit.SetWindowPos(HWND_TOP, &rc, SWP_SHOWWINDOW);
      m_wndEdit.SetSel(0,-1);
      m_wndEdit.SetFocus();
   }

   void _InsertEmptyLastItem()
   {
      CString str;
      str = _T("< ") + m_strLastItem + _T(" >");
      m_wndList.InsertString(-1, str);
   }

   void _UpdateButtons() 
   {
      ATLASSERT(m_wndList.IsWindow());
      ATLASSERT(IsWindow());
      int curIdx = m_wndList.GetCurSel();
      int i = GetItemCount();
      if (i==0) curIdx = -1;

      bool bNew = true;
      bool bNone = (curIdx == -1) ? true : false;
      bool bNoDel = (curIdx >= i) ? true : false;
      bool bNoUp = ((curIdx == 0) || (curIdx >= i)) ? true : false;
      bool bNoDn = (curIdx >= i-1) ? true : false;

      if (!IsWindowEnabled()) 
      {
         curIdx = -1;
         bNew = false;
      }

      m_wndButtons[0].EnableWindow((!bNone || bNew )? TRUE : FALSE);
      m_wndButtons[1].EnableWindow((bNone || bNoDel) ? FALSE : TRUE);
      if (m_wndButtons[2].IsWindow())
         //m_wndButtons[2].EnableWindow((bNone || bNoUp) ? FALSE : TRUE);
         m_wndButtons[2].EnableWindow((bNone || bNoDn) ? FALSE : TRUE);

      if (m_wndButtons[3].IsWindow())
         //m_wndButtons[3].EnableWindow((bNone || bNoDn) ? FALSE : TRUE);
         m_wndButtons[3].EnableWindow((bNone || bNoUp) ? FALSE : TRUE);
         
   }

   // Overridables

   void UpdateLayout()
   {
      if(::IsWindow(m_hWnd))
      {
         RECT rc;
         GetClientRect(&rc);
         
         RECT rcButtons = rc;
         rcButtons.right -= 1;
         rcButtons.left = rcButtons.right;
         rcButtons.top += 1;
         rcButtons.bottom = rcButtons.top + ::GetSystemMetrics(SM_CYCAPTION) - 2;
         for( int i=m_nButtons-1; i>=0; i-- ) {
            RECT rcButton = rcButtons;
            ::GetClientRect(m_wndButtons[i], &rcButton);
            rcButtons.left -= 18;
            m_wndButtons[i].SetWindowPos(HWND_TOP, &rcButtons, SWP_NOZORDER|SWP_NOACTIVATE);
            rcButtons.right = rcButtons.left;
         }
         
         rc.top = rc.top + ::GetSystemMetrics(SM_CYCAPTION);
         if(::IsWindow(m_wndList.m_hWnd))
            m_wndList.SetWindowPos(HWND_TOP, &rc, SWP_NOZORDER|SWP_NOACTIVATE);
      }
   }

   void DrawCaption(CDCHandle dc)
   {
      RECT rc;
      GetClientRect(&rc);
      rc.bottom = rc.top + ::GetSystemMetrics(SM_CYCAPTION);

      CBrush brBtnFace;
      brBtnFace.CreateSysColorBrush(COLOR_BTNFACE);
      dc.FillRect(&rc, brBtnFace);
      dc.Draw3dRect(&rc, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
      
      ::InflateRect(&rc, -2, 0);

      dc.SetBkMode(TRANSPARENT);
      dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));

      HFONT oldFont = dc.SelectFont(AtlGetDefaultGuiFont());

      int len = GetWindowTextLength()+1;
      LPTSTR pstrCaption = (LPTSTR)_alloca(len*sizeof(TCHAR));
      ATLASSERT(pstrCaption);
      GetWindowText(pstrCaption, len);
      dc.DrawText(pstrCaption, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_VCENTER);

      dc.SelectFont(oldFont);
   }

   // Message handlers

   LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
      _Init();
      return lRes;
   }

   LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      T* pT = static_cast<T*>(this);
      if(wParam != NULL)
      {
         pT->DrawCaption((HDC)wParam);
      }
      else
      {
         CPaintDC dc(m_hWnd);
         pT->DrawCaption(dc.m_hDC);
      }
      return 0;
   }

   LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( wParam != SIZE_MINIMIZED ) {
         T* pT = static_cast<T*>(this);
         pT->UpdateLayout();
      }
      return 0;
   }

   LRESULT OnEnable(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      m_wndList.EnableWindow((BOOL)wParam);
      _UpdateButtons();

      return 0;
   }

   LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return 1; // client area occupied by controls
   }

   LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      BOOL bDummy;
      switch( LOWORD(wParam) ) {
      case VK_INSERT:
         OnNew(0,0,0,bDummy);
         break;
      case VK_DELETE:
         OnDelete(0,0,0,bDummy);
         break;
      case VK_F2:
         OnDblClick(0,0,0,bDummy);
         break;
      }
      // Always let default handler get a shot at this...
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnDblClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _BeginEdit( m_wndList.GetCurSel() );
      _UpdateButtons();
      return 0;
   }

   LRESULT OnSelChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _UpdateButtons();
      return 0;
   }


   LRESULT OnNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      if( m_wndEdit.IsWindowVisible() ) return 0;
      ::SetFocus(m_wndList);

      // Hack to make an empty last item
      int iIndex = m_wndList.InsertString(GetItemCount(), _T(""));

      m_wndList.SetCurSel(iIndex);
      if( _SendNotifyMsg(EDLN_INSERTITEM, m_wndList.GetCurSel())==0 ) {
         // Owner accepts insert, so go to edit mode right away...
         _BeginEdit(iIndex);
      }
      else {
         // In case owner cancels the insert and did not change the
         // item text, we delete it again...
         PostMessage(WM_EDITLIST_CLEANUP);
      }
      _UpdateButtons();
      return 0;
   }

   LRESULT OnDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      if( m_wndEdit.IsWindowVisible() ) return 0;
      int iIndex = m_wndList.GetCurSel();
      if( iIndex==-1 ) return 0;

      // Hack to make an empty last item
      if (iIndex == GetItemCount()) return 0;

      if( _SendNotifyMsg(EDLN_DELETEITEM, iIndex)==0 ) {
         DeleteItem(iIndex);
      }
      _UpdateButtons();
      return 0;
   }

   //LRESULT OnUp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   LRESULT OnDown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      if( m_wndEdit.IsWindowVisible() ) return 0;
      int idxSelected = m_wndList.GetCurSel();

      // Hack to make an empty last item
      if( idxSelected==GetItemCount()) return 0;

      if( idxSelected==-1 || idxSelected==0 ) return 0;
      int idxOther = idxSelected - 1;
      CComBSTR bstrSelected, bstrOther;
      void * dataPtrSelected,*dataPtrOther;
      m_wndList.GetTextBSTR(idxSelected, bstrSelected.m_str);
      dataPtrSelected = (void*)m_wndList.GetItemData(idxSelected);
      m_wndList.GetTextBSTR(idxOther, bstrOther.m_str);
      dataPtrOther = (void*)m_wndList.GetItemData(idxOther);
      USES_CONVERSION;
      SetItemText(idxSelected, OLE2CT(bstrOther));
      SetItemData(idxSelected,dataPtrOther);
      SetItemText(idxOther, OLE2CT(bstrSelected));
      SetItemData(idxOther,dataPtrSelected);
      m_wndList.SetCurSel(idxOther);
      _UpdateButtons();
      return 0;
   }

   //LRESULT OnDown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   LRESULT OnUp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      if( m_wndEdit.IsWindowVisible() ) return 0;
      int idxSelected = m_wndList.GetCurSel();

      // Hack to make an empty last item
      if( idxSelected==-1 || idxSelected>=GetItemCount()-1 ) return 0;

      int idxOther = idxSelected + 1;
      CComBSTR bstrSelected, bstrOther;
      void * dataPtrSelected, *dataPtrOther;
      m_wndList.GetTextBSTR(idxSelected, bstrSelected.m_str);
      dataPtrSelected = (void*)m_wndList.GetItemData(idxSelected);
      m_wndList.GetTextBSTR(idxOther, bstrOther.m_str);
      dataPtrOther = (void*)m_wndList.GetItemData(idxOther);
      USES_CONVERSION;
      SetItemText(idxSelected, OLE2CT(bstrOther));
      SetItemData(idxSelected,dataPtrOther);
      SetItemText(idxOther, OLE2CT(bstrSelected));
      SetItemData(idxOther,dataPtrSelected);
      m_wndList.SetCurSel(idxOther);
      _UpdateButtons();
      return 0;
   }

   LRESULT OnCleanUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      // This is a maintenance message:
      //   Here we remove all empty items.
      for( int i=0; i<m_wndList.GetCount(); i++ ) {
         if( m_wndList.GetTextLen(i)==0 ) {
            DeleteItem(i);
            i=-1; // loop again
         }
      }
      return 0;
   }

   LRESULT OnBrowseClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      _SendNotifyMsg(EDLN_BROWSE, m_wndList.GetCurSel());
      // We MUST set focus back to the edit control - otherwise
      // the focus logic will be screwed.
      ::SetFocus(m_wndEdit);
      return 0;
   }

   // CEdit

   LRESULT OnEditLostFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   {
      // Check if we lost focus to the browse button
      HWND hwndNew = lParam==0 ? ::GetFocus() : (HWND)lParam;
      if( hwndNew==m_wndBrowse ) return DefWindowProc(uMsg, wParam, lParam);

      int iIndex = m_wndList.GetCurSel();
      _SendNotifyMsg(EDLN_ENDLABELEDIT, iIndex);
      // Hide controls
      m_wndEdit.ShowWindow(SW_HIDE);
      m_wndBrowse.ShowWindow(SW_HIDE);
      // Ask parent if it accepts the change
      if( _SendNotifyMsg(EDLN_ITEMCHANGING, iIndex)==0 ) {
         // Owner accepted text change.
         // Copy edit text to selected listview item
         int len = m_wndEdit.GetWindowTextLength()+1;
         LPTSTR pstr = (LPTSTR)_alloca(len*sizeof(TCHAR));
         ATLASSERT(pstr);
         m_wndEdit.GetWindowText(pstr, len);        
         SetItemText(iIndex, pstr);
         // Send "Item Changed" notify message
         _SendNotifyMsg(EDLN_ITEMCHANGED, iIndex);
      }
      m_wndList.SetCurSel(iIndex);
      PostMessage(WM_EDITLIST_CLEANUP);
      _UpdateButtons();
      bHandled = FALSE; // Windows needs this to disable cursor
      return 0;
   }

   LRESULT OnEditKey(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      switch( wParam ) {
      case VK_ESCAPE:
         {
            // Copy original listview text to edit control.
            // When the edit control looses focus, it will
            // transfer this text back to the list.
            int iIndex = m_wndList.GetCurSel();
            int len = m_wndList.GetTextLen(iIndex)+1;
            LPTSTR pstr = (LPTSTR)_alloca(len*sizeof(TCHAR));
            ATLASSERT(pstr);
            m_wndList.GetText(iIndex, pstr);
            m_wndEdit.SetWindowText(pstr);           
         }
         // FALL THROUGH...
      case VK_RETURN:
         {
            m_wndList.SetFocus(); // Causes Edit WM_KILLFOCUS
            return 0;
         }
      }
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnEditGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      return DefWindowProc(uMsg, wParam, lParam) | DLGC_WANTALLKEYS;
   }
};

class CEditListBox : public CEditListBoxImpl<CEditListBox>
{
public:
   DECLARE_WND_SUPERCLASS(_T("WTL_EditListBox"), GetWndClassName())
};

#endif // !RC_INVOKED
//////////////////////////////////////////////////////////////////////////
#endif // !defined(__EDITLISTBOX_H_)
