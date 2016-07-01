
/////////////////////////////////////////////////////////////////////////////
// 

class IScanfBehaviour
{
public:
   SCANF_INFO info;

   IScanfBehaviour(const SCANF_INFO /*info*/) { };
   virtual ~IScanfBehaviour() { };
   virtual bool CanActivate() const = 0;
   virtual void scanf(va_list& /*args*/) = 0;
   virtual void Render(CDCHandle /*dc*/, const RECT /*rc*/, UINT /*iState*/) = 0;
   virtual int GetItemWidth(CDCHandle /*dc*/) const = 0;
   virtual void GetItemText(LPTSTR /*pstrText*/) const = 0;
   virtual int GetItemTextLength() const = 0;
   //
   virtual bool OnKeyDown(WPARAM /*wParam*/, LPARAM /*lParam*/) = 0;
   virtual bool OnChar(TCHAR /*ch*/, LPARAM /*lParam*/) = 0;
   virtual void OnSetFocus() = 0;
   virtual void OnLostFocus() = 0;
   //
   static bool IsSupported(LPCTSTR /*pstrType*/);
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfBehaviour : public IScanfBehaviour
{
public:
   CScanfBehaviour(const SCANF_INFO _info) :
      IScanfBehaviour(_info)
   {
      info = _info;
   }
   bool CanActivate() const { return true; };
   bool OnKeyDown(WPARAM /*wParam*/, LPARAM /*lParam*/) { return false; };
   bool OnChar(TCHAR /*ch*/, LPARAM /*lParam*/) { return false; };
   void OnSetFocus() { };
   void OnLostFocus() { };
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfLabel : public CScanfBehaviour
{
public:
   CScanfLabel(const SCANF_INFO _info) :
      CScanfBehaviour(_info)
   {
   }
   bool CanActivate() const 
   { 
      return false; 
   }
   void scanf(va_list& /*args*/)
   {
      // Dummy! Cannot activate!
   }
   void Render(CDCHandle dc, const RECT rc, UINT /*iState*/)
   {
      RECT rcItem = rc;
      dc.DrawText(info.szText, -1, &rcItem, DT_LEFT | DT_SINGLELINE);
   }
   int GetItemWidth(CDCHandle dc) const
   {
      RECT rc = { 0, 0, 999, 999 };
      dc.DrawText(info.szText, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_CALCRECT);
      return rc.right - rc.left;
   }
   void GetItemText(LPTSTR pstrText) const
   {
      ::lstrcpy(pstrText, info.szText);
   }
   int GetItemTextLength() const
   {
      return ::lstrlen(info.szText);
   }
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfInteger : public CScanfBehaviour
{
public:
   int m_iValue;
   int m_iRangeLow;
   int m_iRangeHigh;
   bool m_bJustActivated;

   CScanfInteger(const SCANF_INFO _info) :
      CScanfBehaviour(_info),
      m_iValue(0L),
      m_iRangeLow(0L),
      m_iRangeHigh(999999999L),
      m_bJustActivated(false)
   {
      if( info.iWidth > 0 ) {
         m_iRangeHigh = 9;
         for( int i = 0; i < info.iWidth - 1; i++ ) m_iRangeHigh = (m_iRangeHigh * 10L) + 9;
      }
   }
   bool CanActivate() const 
   { 
      return true; 
   }
   void scanf(va_list& args)
   {
      *(va_arg(args, int*)) = m_iValue;
   }
   void Render(CDCHandle dc, const RECT rc, UINT /*iState*/)
   {
      TCHAR szValue[32];
      GetItemText(szValue);
      RECT rcItem = rc;
      dc.DrawText(szValue, -1, &rcItem, info.iStyle | DT_SINGLELINE);
   }
   void GetItemText(LPTSTR pstrText) const
   {
      ::wsprintf(pstrText, info.szFormat, m_iValue);
   }
   int GetItemTextLength() const
   {
      TCHAR szValue[32];
      GetItemText(szValue);
      return ::lstrlen(szValue);
   }
   int GetItemWidth(CDCHandle dc) const
   {
      TCHAR szValue[32];
      GetItemText(szValue);
      RECT rc = { 0, 0, 999, 999 };
      dc.DrawText(szValue, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_CALCRECT);
      return rc.right - rc.left;
   }
   void OnSetFocus()
   {
      m_bJustActivated = true;
   }
   bool OnKeyDown(WPARAM wParam, LPARAM /*lParam*/) 
   { 
      switch( wParam ) {
      case VK_DELETE:
      case VK_BACK:
         m_iValue = m_iRangeLow <= 0 ? 0 : m_iRangeLow;
         return true;
      case VK_HOME:
         m_iValue = m_iRangeLow;
         return true;
      case VK_END:
         m_iValue = m_iRangeHigh;
         return true;
      case VK_UP:
         if( m_iValue < m_iRangeHigh ) m_iValue++;
         return true;
      case VK_DOWN:
         if( m_iValue > m_iRangeLow ) m_iValue--;
         return true;
      }
      return false; 
   }
   bool OnChar(TCHAR ch, LPARAM /*lParam*/) 
   { 
      if( ch < _T('0') || ch > _T('9') ) return false;
      int iOldValue = m_iValue;
      m_iValue = (m_iValue * 10L) + (ch - _T('0'));
      if( m_bJustActivated || m_iValue > m_iRangeHigh ) m_iValue = ch - _T('0');
      if( m_iValue < m_iRangeLow ) m_iValue = iOldValue;
      if( m_iValue > m_iRangeHigh ) m_iValue = iOldValue;
      m_bJustActivated = false;
      return true; 
   }

   static bool IsSupported(LPCTSTR pstrType) 
   { 
      if( ::lstrcmp(pstrType, _T("d")) == 0 ) return true;
      return false; 
   }
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfString : public CScanfBehaviour
{
public:
   CScanfString(const SCANF_INFO _info) :
      CScanfBehaviour(_info)
   {
   }
   bool CanActivate() const 
   { 
      return true; 
   }
   void scanf(va_list& args)
   {
      ::lstrcpy((va_arg(args, TCHAR*)), info.szText);
   }
   void Render(CDCHandle dc, const RECT rc, UINT /*iState*/)
   {
      TCHAR szValue[64];
      GetItemText(szValue);
      RECT rcItem = rc;
      dc.DrawText(szValue, -1, &rcItem, info.iStyle | DT_SINGLELINE);
   }
   void GetItemText(LPTSTR pstrText) const
   {
      ::wsprintf(pstrText, info.szFormat, info.szText);
      if( ::lstrlen(pstrText) == 0 ) ::lstrcpy(pstrText, _T(" "));
   }
   int GetItemTextLength() const
   {
      TCHAR szValue[64];
      GetItemText(szValue);
      return ::lstrlen(szValue);
   }
   int GetItemWidth(CDCHandle dc) const
   {
      TCHAR szValue[64];
      GetItemText(szValue);
      RECT rc = { 0, 0, 999, 999 };
      dc.DrawText(szValue, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_CALCRECT);
      int iWidth = rc.right - rc.left;
      return iWidth == 0 ? 10 : iWidth;
   }
   bool OnKeyDown(WPARAM wParam, LPARAM /*lParam*/) 
   { 
      switch( wParam ) {
      case VK_DELETE:
      case VK_BACK:
         info.szText[0] = _T('\0');
         return true;
      }
      return false; 
   }
   bool OnChar(TCHAR ch, LPARAM /*lParam*/) 
   { 
      if( ch < _T(' ') ) return false;
      int nLen = ::lstrlen(info.szText);
      if( nLen >= info.iWidth ) info.szText[0] = _T('\0');
      TCHAR pstrText[] = { ch, 0 };
      ::lstrcat(info.szText, pstrText);
      return true; 
   }

   static bool IsSupported(LPCTSTR pstrType) 
   { 
      if( ::lstrcmp(pstrType, _T("s")) == 0 ) return true;
      return false; 
   }
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfYear : public CScanfInteger
{
public:
   CScanfYear(const SCANF_INFO _info) :
      CScanfInteger(_info)
   {
      SYSTEMTIME stNow;
      ::GetLocalTime(&stNow);
      m_iValue = (int) stNow.wYear;
      m_iRangeLow = 1800;
      m_iRangeHigh = 9999;
      ::lstrcpy(info.szFormat, _T("%4d"));
      info.iWidth = 4;
   }
   void OnLostFocus()
   {
      if( m_iValue < 50 ) m_iValue += 2000;
      if( m_iValue < 1800 ) m_iValue = 1800;
   }
   static bool IsSupported(LPCTSTR pstrType) 
   { 
      if( ::lstrcmp(pstrType, _T("y")) == 0 ) return true;
      return false; 
   }
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfMonth : public CScanfInteger
{
public:
   int m_iMaxWidth;

   CScanfMonth(const SCANF_INFO _info) :
      CScanfInteger(_info)
   {
      CClientDC dc(info.hwnd);
      HFONT hOldFont = dc.SelectFont(CWindow(info.hwnd).GetFont());
      m_iMaxWidth = 0;
      for( LCTYPE i = LOCALE_SMONTHNAME1; i < LOCALE_SMONTHNAME12; i++ ) {
         TCHAR szName[32];
         ::GetLocaleInfo(LOCALE_USER_DEFAULT, i, szName, sizeof(szName)/sizeof(TCHAR));
         SIZE szText;
         dc.GetTextExtent(szName, ::lstrlen(szName), &szText);
         m_iMaxWidth = max(m_iMaxWidth, szText.cx);
      }
      dc.SelectFont(hOldFont);
      SYSTEMTIME stNow;
      ::GetLocalTime(&stNow);
      m_iValue = (int) stNow.wMonth;
      m_iRangeLow = 1;
      m_iRangeHigh = 12;
      info.iStyle = DT_CENTER;
   }
   void GetItemText(LPTSTR pstrText) const
   {
      ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SMONTHNAME1 + m_iValue - 1, pstrText, 32);
   }
   int GetItemWidth(CDCHandle dc) const
   {
      return m_iMaxWidth;
   }

   static bool IsSupported(LPCTSTR pstrType) 
   { 
      if( ::lstrcmp(pstrType, _T("m")) == 0 ) return true;
      return false; 
   }
};


/////////////////////////////////////////////////////////////////////////////
// 

class CScanfWeekday : public CScanfInteger
{
public:
   int m_iMaxWidth;

   CScanfWeekday(const SCANF_INFO _info) :
      CScanfInteger(_info)
   {
      CClientDC dc(info.hwnd);
      HFONT hOldFont = dc.SelectFont(CWindow(info.hwnd).GetFont());
      m_iMaxWidth = 0;
      for( LCTYPE i = LOCALE_SDAYNAME1; i < LOCALE_SDAYNAME7; i++ ) {
         TCHAR szName[32];
         ::GetLocaleInfo(LOCALE_USER_DEFAULT, i, szName, sizeof(szName)/sizeof(TCHAR));
         SIZE szText;
         dc.GetTextExtent(szName, ::lstrlen(szName), &szText);
         m_iMaxWidth = max(m_iMaxWidth, szText.cx);
      }
      dc.SelectFont(hOldFont);
      m_iValue = 1;
      m_iRangeLow = 1;
      m_iRangeHigh = 7;
      info.iStyle = DT_CENTER;
   }
   void GetItemText(LPTSTR pstrText) const
   {
      ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDAYNAME1 + m_iValue - 1, pstrText, 32);
   }
   int GetItemWidth(CDCHandle dc) const
   {
      return m_iMaxWidth;
   }

   static bool IsSupported(LPCTSTR pstrType) 
   { 
      if( ::lstrcmp(pstrType, _T("w")) == 0 ) return true;
      return false; 
   }
};
