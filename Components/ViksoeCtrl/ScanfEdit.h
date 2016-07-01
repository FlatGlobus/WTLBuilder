#if !defined(AFX_SCANFEDIT_H__20030216_8415_B629_378A_0080AD509054__INCLUDED_)
#define AFX_SCANFEDIT_H__20030216_8415_B629_378A_0080AD509054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma once

/////////////////////////////////////////////////////////////////////////////
// ScanfEdit - A Masked Edit control
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2003 Bjarke Viksoe.
//
// Add the following macro to the parent's message map:
//   REFLECT_NOTIFICATIONS_EX()
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

#ifndef __cplusplus
  #error WTL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLCTRLS_H__
  #error ScanfEdit.h requires atlctrls.h to be included first
#endif

// Include va_arg support
#include <stdarg.h>


/////////////////////////////////////////////////////////////////////////////
// 

typedef struct
{
   int iItem;                               // Index for current Item
   HWND hwnd;                               // Owner window handle
   TCHAR szType[4];                         // Format type
   TCHAR szFormat[12];                      // Format string
   int iWidth;                              // Format width
   int iPrecision;                          // Format precision
   TCHAR chPadding;                         // Format padding character
   UINT iStyle;                             // Format draw style (alignment)
   TCHAR szText[128];                       // Item value or print text
} SCANF_INFO;


/////////////////////////////////////////////////////////////////////////////
// 

#include "ScanfEditBehaviour.h"


/////////////////////////////////////////////////////////////////////////////
// 

// Extended control styles
#define SFS_SHOWSELALWAYS    0x00000001
#define SFS_NOSEL            0x00000002
#define SFS_INSIDEONLY       0x00000004


template< class T, class TBase = CEdit, class TWinTraits = CControlWinTraits >
class ATL_NO_VTABLE CScanfEditImpl : 
   public CWindowImpl< T, TBase, TWinTraits >,
   public COwnerDraw< T >
{
public:
   DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

   IScanfBehaviour* m_pCurItem;
   DWORD m_dwExtStyle;
   //
   CSimpleArray<IScanfBehaviour*> m_Items;
   COLORREF m_clrText;
   COLORREF m_clrBack;
   SIZE m_szMargins;

   // Operations

   BOOL SubclassWindow(HWND hWnd)
   {
      ATLASSERT(m_hWnd==NULL);
      ATLASSERT(::IsWindow(hWnd));
      BOOL bRet = CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(hWnd);
      if( bRet ) _Init();
      return bRet;
   }

   int scanf(BOOL bPopulate, ...)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      va_list args;
      va_start(args, bPopulate);     
      int nCount = 0;
      for( int i = 0; i < m_Items.GetSize(); i++ ) {
         IScanfBehaviour* pItem = m_Items[i];
         if( pItem->CanActivate() ) {
            if( bPopulate ) pItem->scanf(args);
            nCount++;
         }
      }
      va_end(args);
      return nCount;
   }

   DWORD SetExtendedScanfStyle(DWORD dwStyle)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      DWORD dwOldStyle = m_dwExtStyle;
      m_dwExtStyle = dwStyle;
      Invalidate();
      return dwOldStyle;
   }
   BOOL SetFormat(LPCTSTR pstrFormat)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(!::IsBadStringPtr(pstrFormat,-1));
      BOOL bRes = _ParseFormat(pstrFormat);
      Invalidate();
      return bRes;
   }
   void SetTextColor(COLORREF clr)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_clrText = clr;
      Invalidate();
   }
   void SetBkColor(COLORREF clr)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_clrBack = clr;
      Invalidate();
   }
   void SetMargins(int nLeft, int nRight)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_szMargins.cx = nLeft;
      m_szMargins.cy = nRight;
      Invalidate();
   }
   
   int GetItemCount() const
   {
      return m_Items.GetSize();
   }
   IScanfBehaviour* GetItem(int iItem) const
   {
      if( !_IsItemValid(iItem) ) return NULL;
      return m_Items[iItem];
   }
   BOOL ActivateItem(int iItem, BOOL bForward)
   {
      int nCount = m_Items.GetSize();
      
      // Find next item in line...
      if( bForward ) {
         while( iItem < nCount && !m_Items[iItem]->CanActivate() ) iItem++;
      }
      else {
         iItem--;
         while( iItem >= 0 && !m_Items[iItem]->CanActivate() ) iItem--;
      }

      if( iItem < 0 ) {
         if( m_dwExtStyle & SFS_INSIDEONLY ) {
            // Activate last item instead!
            ActivateItem(m_Items.GetSize() - 1, FALSE);
         }
         else {
            // Unable to activate any item, so let's set focus to the next
            // Windows control in the tabbing order...
            ::SetFocus(::GetNextDlgTabItem(GetParent(), m_hWnd, TRUE));
         }
         return FALSE;
      }
      if( iItem >= nCount ) {
         if( m_dwExtStyle & SFS_INSIDEONLY ) {
            // Activate first item instead!
            if( m_Items.GetSize() > 0 ) ActivateItem(0, TRUE);
         }
         else {
            // Unable to activate any item, so let's set focus to the next
            // Windows control in the tabbing order...
            ::SetFocus(::GetNextDlgTabItem(GetParent(), m_hWnd, FALSE));
         }
         return FALSE;
      }
      // Ok, we can activate the new item...
      if( m_pCurItem ) m_pCurItem->OnLostFocus();
      m_pCurItem = m_Items[iItem];
      m_pCurItem->OnSetFocus();
      Invalidate();
      return TRUE;
   }
   BOOL GetItemRect(int iItem, LPRECT pRect) const
   {
      if( !_IsItemValid(iItem) ) return FALSE;
      CClientDC dc(m_hWnd);
      HFONT hOldFont = dc.SelectFont(GetFont());
      GetClientRect(pRect);
      ::InflateRect(pRect, -m_szMargins.cx, -m_szMargins.cy);
      int i;  
      for(i = 0; i < iItem; i++ ) pRect->left += m_Items[i]->GetItemWidth((HDC)dc);
      pRect->right = pRect->left + m_Items[i]->GetItemWidth((HDC)dc);
      dc.SelectFont(hOldFont);
      return TRUE;
   }

   // Implementation

   void _Init()
   {
      ATLASSERT(::IsWindow(m_hWnd));

      SetFont(AtlGetDefaultGuiFont());
      ModifyStyle(0x0F, SS_OWNERDRAW | SS_NOTIFY); // We need these!

      m_pCurItem = NULL;
      m_dwExtStyle = 0UL;
      m_clrText = CLR_INVALID;
      m_clrBack = CLR_INVALID;
      m_szMargins.cx = m_szMargins.cy = 2;

      //int nLen = GetWindowTextLength() + 1;
      //LPTSTR pstrFormat = (LPTSTR) alloca(nLen * sizeof(TCHAR));
      //GetWindowText(pstrFormat, nLen);
      //_ParseFormat(pstrFormat);
      ActivateItem(0, TRUE);
   }

   BOOL _ParseFormat(LPCTSTR pstrScanfFormat)
   {
      _ClearItems();

      int nLen = ::lstrlen(pstrScanfFormat);
      if( nLen == 0 ) return TRUE;

      SCANF_INFO info_template = { 0 };
      info_template.hwnd = m_hWnd;
      info_template.iStyle = DT_RIGHT;

      SCANF_INFO info = info_template;
      LPTSTR pstrText = info.szText;
      LPTSTR pstrFormat = info.szFormat;
      int iItem = 0;

      for( LPCTSTR pstr = pstrScanfFormat; *pstr; pstr = ::CharNext(pstr) ) {

         // Handle '%' character, but watch out for '%%'
         if( *pstr != _T('%') || *(::CharNext(pstr)) == _T('%') ) {
            *pstrText++ = *pstr;
#ifdef _MBCS
            if( ::IsDBCSLeadByte(*pstr) ) *pstrText++ = *(pstr + 1);
#endif
            *pstrText = _T('\0');
            continue;
         }

         if( info.szText[0] != _T('\0') ) {
            IScanfBehaviour* pItem;
            ATLTRY(pItem = new CScanfLabel(info));
            if( pItem ) m_Items.Add(pItem);
         }
         info = info_template;
         info.iItem = ++iItem;
         pstrText = info.szText;
         pstrFormat = info.szFormat;

         // Handle '%' character with format
         *pstrFormat++ = *pstr;
         pstr = ::CharNext(pstr);
         
         for( ; *pstr; pstr = ::CharNext(pstr) ) {
            *pstrFormat++ = *pstr;
            if( *pstr == _T('-') ) info.iStyle = DT_LEFT;
            else if( *pstr == _T('0') ) info.chPadding = *pstr;
            else if( *pstr == _T(' ') ) info.chPadding = *pstr;
            else if( *pstr == _T('#') ) info.chPadding = *pstr;
            else break;
         }
         pstrFormat--;

         // Handle width
         while( *pstr >= _T('0') && *pstr <= _T('9') ) {
            info.iWidth = info.iWidth * 10 + (*pstr - _T('0'));
            *pstrFormat++ = *pstr;
            pstr = ::CharNext(pstr);
         }

         // Handle precision
         if( *pstr == _T('.') ) {
            *pstrFormat++ = *pstr;
            pstr = ::CharNext(pstr);
            while( *pstr >= _T('0') && *pstr <= _T('9') ) {
               info.iPrecision = info.iPrecision * 10 + (*pstr - _T('0'));
               *pstrFormat++ = *pstr;
               pstr = ::CharNext(pstr);
            }
         }

         // Ignore various size-specifiers
         for( ; *pstr; pstr = ::CharNext(pstr) ) {
            if( *pstr == _T('l') ) ;
            else break;
         }

         // Ok, stuff it all inside the information structure...
         info.szType[0] = *pstr;
         info.szType[1] = _T('\0');

         *pstrFormat++ = *pstr;
         *pstrFormat++ = _T('\0');

         IScanfBehaviour* pItem;
         ATLTRY(pItem = _CreateItem(info.szType, info));
         ATLASSERT(pItem); // Format type not supported!
         if( pItem ) m_Items.Add(pItem);

         info = info_template;
         info.iItem = ++iItem;
         pstrText = info.szText;
         pstrFormat = info.szFormat;
      }

      if( info.szText[0] != _T('\0') ) {
         IScanfBehaviour* pItem;
         ATLTRY(pItem = new CScanfLabel(info));
         if( pItem ) m_Items.Add(pItem);
      }

      return TRUE;
   }
   void _ClearItems()
   {
      for( int i = 0; i < m_Items.GetSize(); i++ ) delete m_Items[i];
      m_Items.RemoveAll();
      m_pCurItem = NULL;
   }
   IScanfBehaviour* _CreateItem(LPCTSTR pstrType, const SCANF_INFO& info)
   {
      if( CScanfInteger::IsSupported(pstrType) ) return new CScanfInteger(info);
      if( CScanfString::IsSupported(pstrType) ) return new CScanfString(info);
      if( CScanfYear::IsSupported(pstrType) ) return new CScanfYear(info);
      if( CScanfMonth::IsSupported(pstrType) ) return new CScanfMonth(info);
      if( CScanfWeekday::IsSupported(pstrType) ) return new CScanfWeekday(info);
      return NULL;
   }
   inline bool _IsItemValid(int iItem) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(iItem>=0 && iItem<m_Items.GetSize());
      return iItem >= 0 && iItem < m_Items.GetSize();
   }

   // Message map and handlers

   BEGIN_MSG_MAP(CScanfEditImpl)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)      
      MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)      
      MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)      
      MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
      MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
      MESSAGE_HANDLER(WM_CHAR, OnChar)
      CHAIN_MSG_MAP_ALT( COwnerDraw< T >, 1 )
      DEFAULT_REFLECTION_HANDLER()
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      LRESULT lRes = DefWindowProc();
      _Init();
      return lRes;
   }
   LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
   {
      _ClearItems();
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return 1; // We're painting stuff!
   }
   LRESULT OnGetDlgCode(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return DLGC_WANTALLKEYS | DLGC_WANTCHARS;
   }
   LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( m_pCurItem ) m_pCurItem->OnSetFocus();
      Invalidate();
      return 0;
   }
   LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if( m_pCurItem ) m_pCurItem->OnLostFocus();
      Invalidate();
      return 0;
   }
   LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      SetFocus();
      POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
      for( int i = 0; i < m_Items.GetSize(); i++ ) {
         RECT rcItem;
         GetItemRect(i, &rcItem);
         if( ::PtInRect(&rcItem, pt) ) ActivateItem(i, TRUE);
      }
      return 0;
   }
   LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   {
      if( m_pCurItem && m_pCurItem->OnKeyDown(wParam, lParam) ) {
         Invalidate();
         return 0;
      }
      switch( wParam ) {
      case VK_TAB:
         ::PostMessage(GetParent(), WM_NEXTDLGCTL, ::GetKeyState(VK_SHIFT) < 0 ? 1 : 0, (LPARAM) FALSE);
         return 0;
      case VK_LEFT:
         if( m_pCurItem ) ActivateItem(m_pCurItem->info.iItem - 1, FALSE);
         return 0;
      case VK_RIGHT:
         if( m_pCurItem ) ActivateItem(m_pCurItem->info.iItem + 1, TRUE);
         return 0;
      }
      bHandled = FALSE;
      return 0;
   }

   LRESULT OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
   {
      if( m_pCurItem && m_pCurItem->OnChar( (TCHAR) wParam, lParam ) ) {
         Invalidate();
         return 0;
      }
      return 0;
   }

   void SetWindowText(CString & str)
   {
		for(int i=0; i < str.GetLength();i++)
			SendMessage(WM_CHAR, str[i], 1);
		Invalidate();
   }
   // COwnerDraw

   void DrawItem(LPDRAWITEMSTRUCT lpDIS)
   {
      CDCHandle dc = lpDIS->hDC;
      RECT rc = lpDIS->rcItem;
      UINT iState = lpDIS->itemState & ~ODS_SELECTED;

      COLORREF clrBack = m_clrBack;
      if( clrBack == CLR_INVALID ) clrBack = ::GetSysColor(COLOR_WINDOW);
      dc.FillSolidRect(&rc, clrBack);

      ::InflateRect(&rc, -m_szMargins.cx, -m_szMargins.cy);

      COLORREF clrText = m_clrText;
      if( clrText == CLR_INVALID ) clrText = ::GetSysColor(COLOR_WINDOWTEXT);
      
      int nCount = m_Items.GetSize();
      for( int i = 0; i < nCount; i++  ) {
         IScanfBehaviour* pItem = m_Items[i];
         UINT iNewState = iState;
         if( pItem == m_pCurItem ) iNewState |= ODS_SELECTED;

         int iWidth = pItem->GetItemWidth(dc);
         RECT rcCell = rc;
         rcCell.right = min(rcCell.left + iWidth, rc.right);
         if( rcCell.left >= rc.right ) break;

         dc.SetBkMode(TRANSPARENT);
         dc.SetTextColor(clrText);
         if( iNewState & ODS_SELECTED ) {
            dc.SetBkMode(OPAQUE);
            if( ::GetFocus() == m_hWnd && (m_dwExtStyle & SFS_NOSEL) == 0 ) {
               dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
               dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
            }
            else if( m_dwExtStyle & SFS_SHOWSELALWAYS ) {
               dc.SetBkColor(::GetSysColor(COLOR_BTNFACE));
               dc.SetTextColor(::GetSysColor(COLOR_BTNSHADOW));
            }
         }

         m_Items[i]->Render(dc, rcCell, iNewState);

         rc.left += iWidth;
      }
   }
};


class CScanfEditCtrl : public CScanfEditImpl<CScanfEditCtrl>
{
public:
   DECLARE_WND_SUPERCLASS(_T("WTL_ScanfEdit"), GetWndClassName())  
};
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
	class CScanfEditCtrlComp:public CScanfEditCtrl,public ControlComponent<CScanfEditCtrlComp>
	{
		CString caption;
		CString mask;
	public:
		CScanfEditCtrlComp(LPTSTR _name);
		~CScanfEditCtrlComp(void);
		
		BEGIN_MSG_MAP(CScanfEditCtrlComp)
			CHAIN_MSG_MAP(ControlComponent<CScanfEditCtrlComp>)
			CHAIN_MSG_MAP(CScanfEditCtrl)
		END_MSG_MAP()
			
		BOOL CreateComponent(Component * _Parent);
		void InitProperty(void);
		DECLARE_PROPERTY(Caption,CString)
		DECLARE_PROPERTY(Mask,CString)
	};
};

#endif




#endif // !defined(AFX_SCANFEDIT_H__20030216_8415_B629_378A_0080AD509054__INCLUDED_)

