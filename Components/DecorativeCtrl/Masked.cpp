// MaskEd.cpp : implementation file
//
// Orginially written by : DunnoWho
// Modified by : Jeremy Davis, 24/07/1998
//     Added CTimeEdit::SetMins and CTimeEdit::SetHours

#include "stdafx.h"
#include "MaskEd.h"
/////////////////////////////////////////////////////////////////////////////
// CMaskEdit class
CMaskEdit::CMaskEdit()
{
  m_bUseMask = FALSE;
  m_strMask = _T("");
  m_strLiteral = _T("");
  m_strValid = _T("");
  m_strHours = _T("47");
  m_strMins = _T("59");
  m_bMaskKeyInProgress = FALSE;
  m_strMaskLiteral = _T("");
}

void CMaskEdit::SetMask(LPCTSTR lpMask, LPCTSTR lpLiteral, LPCTSTR lpValid)
{
  m_bUseMask = FALSE;
  if (lpMask == NULL) return;
  m_strMask = lpMask;
  if (m_strMask.IsEmpty()) return;
  if (lpLiteral != NULL)
  {
    m_strLiteral = lpLiteral;
    if (m_strLiteral.GetLength() != m_strMask.GetLength())
      m_strLiteral.Empty();
  }
  else
    m_strLiteral.Empty();
  if (lpValid != NULL)
    m_strValid = lpValid;
  else
    m_strValid.Empty();
  m_bUseMask = TRUE;
}

void CMaskEdit::SendChar(UINT nChar)
{
  m_bMaskKeyInProgress = TRUE;
  //#ifdef WIN32
  //  AfxCallWndProc(this, m_hWnd, WM_CHAR, nChar, 1);
  //#else
    SendMessage(WM_CHAR, nChar, 1);
  //DefWindowProc(WM_CHAR, nChar, 1);
  //#endif
  m_bMaskKeyInProgress = FALSE;
}

LRESULT CMaskEdit::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled=TRUE;
	if (!m_bMaskKeyInProgress)
		if (!CheckChar((UINT)wParam)) return 0;

	if (m_bUseMask)
	{
		if (isprint((int)wParam))
		{
			// si un masque existe, on est en insert mode
			int startPos, endPos;
			GetSel(startPos, endPos);
			SetSel(startPos, endPos+1);
			Clear();
			m_str.SetAt(endPos, (TCHAR)wParam); // added this
		}
		else if (wParam == VK_BACK)
		{
			int startPos, endPos;
			GetSel(startPos, endPos);
			// sanity range check
			if ((startPos == endPos) && (startPos >= 1) && (startPos <= m_str.GetLength()))
			{
				_TCHAR c;
		        // get the masked literal representation
			    if (!m_strMaskLiteral.IsEmpty())
					c = m_strMaskLiteral[startPos-1];
				
				// back space the cursor
				SendMessage(WM_KEYDOWN, VK_LEFT, 0);
				if (!m_strMaskLiteral.IsEmpty())
				{
					// update the _TCHAR backspacing over
					SendChar(c);

					// back space the cursor again
					SendMessage(WM_KEYDOWN, VK_LEFT, 0);
				}
			}
			else // out of range or have more than one _TCHAR selected
				MessageBeep((UINT)-1);
			return 0;
		}
	}

	
	LRESULT res=DefWindowProc(uMsg,wParam,lParam);

	if (!m_bMaskKeyInProgress && m_bUseMask && !m_strLiteral.IsEmpty())
	{
		int startPos, endPos;
		GetSel(startPos, endPos);
		// make sure the string is not longer than the mask
		if (endPos < m_strLiteral.GetLength())
		{
			UINT c = m_strLiteral.GetAt(endPos);
			if (c != '_') SendChar(c);
		}
	}
	return res;
}

BOOL CMaskEdit::CheckChar(UINT nChar)
{
  UINT c;

  // do not use mask
  if (!m_bUseMask) return TRUE;

  // control character, OK
  if (!isprint(nChar)) return TRUE;
	
  // unselect all selections, if any
  int startPos, endPos;
  GetSel(startPos, endPos);
  SetSel(-1, 0);
  SetSel(startPos, startPos);

  // check the key against the mask
  GetSel(startPos, endPos);

  // make sure the string is not longer than the mask
  if (endPos >= m_strMask.GetLength())
  {
    MessageBeep((UINT)-1);
    return FALSE;
  }

  // check to see if a literal is in this position
  c = '_';
  if (!m_strLiteral.IsEmpty())
    c = m_strLiteral.GetAt(endPos);

  if (c != '_')
  {
    SendChar(c);
    GetSel(startPos, endPos);
  }

  // check the valid string character
  if (m_strValid.Find(nChar) != -1) return TRUE;

  // check the key against the mask
  c = m_strMask.GetAt(endPos);
  BOOL doit = TRUE;
  switch (c)
  {
    case '0':		// digit only //completely changed this
    {
		BOOL doit = TRUE;
		if(isdigit(nChar))
		{
			if(m_isdate)
			{
				if(endPos == 0)
				{
					if(nChar > '3')
						doit = FALSE;
				}
				if(endPos == 1)
				{
					if(m_str.GetAt(0) == '3')
					{
						if(nChar > '1')
							doit = FALSE;
					}
				}
				if(endPos == 3)
				{
					if(nChar > '1')
						doit = FALSE;
				}
				if(endPos == 4)
				{
					if(m_str.GetAt(3) == '1')
					{
						if(nChar > '2')
							doit = FALSE;
					}
				}
			}
			else
			{
				if(m_isTime)
				{
					
					if(endPos == 0)
					{
						if(nChar > (UINT)m_strHours[0])
							doit = FALSE;
					}
					if(endPos == 1)
					{
						if(m_str.GetAt(0) == m_strHours[0])
						{
							if(nChar > (UINT)m_strHours[1])
								doit = FALSE;
						}
					}
					if(endPos == 3)
					{
						if(nChar > (UINT)m_strMins[0])
							doit = FALSE;
					}
					if(endPos == 4)
					{
						if(m_str.GetAt(3) == m_strMins[0])
						{
							if(nChar > (UINT)m_strMins[1])
								doit = FALSE;
						}
					}
				}
			}
			return doit;
		}
      break;
    }
    case '9':		// digit or space
    {
      if (isdigit(nChar)) return TRUE;
      if (nChar != VK_SPACE) return TRUE;
      break;
    }
    case '#':		// digit or space or '+' or '-'
    {
      if (isdigit(nChar)) return TRUE;
      if (nChar == VK_SPACE || nChar == VK_ADD || nChar == VK_SUBTRACT) return TRUE;
      break;
    }
    case 'L':		// alpha only
    {
      if (isalpha(nChar)) return TRUE;
      break;
    }
    case '?':		// alpha or space
    {
      if (isalpha(nChar)) return TRUE;
      if (nChar == VK_SPACE) return TRUE;
      break;
    }
    case 'A':		// alpha numeric only
    {
      if (_istalnum(nChar)) return TRUE;
      break;
    }
    case 'a':		// alpha numeric or space
    {
      if (_istalnum(nChar)) return TRUE;
      if (nChar == VK_SPACE) return TRUE;
      break;
    }
    case '&':		// all print character only
    {
      if (isprint(nChar)) return TRUE;
      break;
    }
  }
  MessageBeep((UINT)-1);
  return FALSE;
}

LRESULT CMaskEdit::OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
  // si un masque existe, tester les touches spéciales
  if (m_bUseMask)
  {
    switch (wParam)
    {
      case VK_DELETE:
      case VK_INSERT:
			bHandled=TRUE;
		  return TRUE;
    }
  }
  bHandled=FALSE;
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDateEdit class
/*
CDateEdit::CDateEdit()
{
  m_bUseMask = TRUE;
  m_isdate = TRUE; //added this
  m_strMask = _T("00/00/0000");
  m_strLiteral = _T("__/__/____");
}

void CDateEdit::SetDate(CSimpleDate& Date)
{
  CString strText((LPCTSTR)Date);
  m_str = m_strMaskLiteral = strText;
  SetWindowText(strText);
}

CSimpleDate CDateEdit::GetDate()
{
  CString strText;
  int textLen = GetWindowTextLength();
  if (textLen != 0)
  {
	  textLen += 1;
	  textLen = GetWindowText(strText.GetBuffer(textLen), textLen);
	  strText.ReleaseBuffer(textLen);
  }
  
  return CSimpleDate(strText);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CTimeEdit class completely new
/*
CTimeEdit::CTimeEdit()
{
  m_bUseMask = TRUE;
  m_isdate = FALSE; 
  m_strMask = _T("00:00");
  m_strLiteral = _T("__:__");
}

void CTimeEdit::SetTime(CSimpleDate& Date)
{
  CString strText;
  FormatCOleDateTime(strText, Date, 5);
  m_str = m_strMaskLiteral = strText;
  SetWindowText(strText);
}

void CTimeEdit::SetTime(CString Date)
{
	m_str = m_strMaskLiteral = Date;
	SetWindowText(Date);
}

COleDateTime CTimeEdit::GetTime()
{
  CString strText;
  GetWindowText(strText);
  return ReadCOleDateTime(strText);
}

CString CTimeEdit::GetTimeStr()
{
	CString strText;
	GetWindowText(strText);
	return strText;
}

void CTimeEdit::SetHours(int hrs)
{
	m_strHours.Format("%d", hrs);
}

void CTimeEdit::SetMins(int hrs)
{
	m_strMins.Format("%d", hrs);
}
*/
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace DecorativeCtrl
{
	static void RegisterEditStyles();
	typedef long EditAlignText;
	
	REGISTER_COMPONENT_EX(CMaskEdit,CMaskEditComp,DecorativeCtrl,IDB_MASKEDIT)
		
	CMaskEditComp::CMaskEditComp(LPTSTR _name):ControlComponent<CMaskEditComp>(_name)
	{
		SetDefaultSize(85,22);
		RegisterEditStyles();
	}
	
	
	CMaskEditComp::~CMaskEditComp(void)
	{
	}
	
	BOOL CMaskEditComp::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CMaskEdit::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),get_Caption(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}
	
	void CMaskEditComp::InitProperty(void)
	{
		ControlComponent<CMaskEditComp>::InitProperty();
		DEFINE_PROPERTY(Mask,CString,CMaskEditComp,m_strMask)
		DEFINE_PROPERTY(Literal,CString,CMaskEditComp,m_strLiteral)
		DEFINE_PROPERTY(UseMask,BOOL,CMaskEditComp,m_bUseMask)
		DEFINE_PROPERTY(IsDate,BOOL,CMaskEditComp,m_isdate)
		DEFINE_PROPERTY(IsTime,BOOL,CMaskEditComp,m_isTime)
		DEFINE_PROPERTY(Caption,CString,CMaskEditComp,_T(""))

		DEFINE_PROPERTY(AutoHScroll,BOOL,CMaskEditComp,FALSE)
		DEFINE_PROPERTY(AutoVScroll,BOOL,CMaskEditComp,FALSE)
		DEFINE_PROPERTY(LowerCase,BOOL,CMaskEditComp,FALSE)
		DEFINE_PROPERTY(OemConvert,BOOL,CMaskEditComp,FALSE)
		DEFINE_PROPERTY(UpperCase,BOOL,CMaskEditComp,FALSE)
		DEFINE_PROPERTY(WantReturn,BOOL,CMaskEditComp,FALSE)
		DEFINE_PROPERTY(TextAlign,EditAlignText,CMaskEditComp,ES_LEFT)
		PUBLIC_PROPERTY(VScroll,TRUE)
		PUBLIC_PROPERTY(HScroll,TRUE)
		
	}
	
	void CMaskEditComp::set_Caption(CString str)
	{
		m_str=str;
		if(IsWindow())
		{
			SetWindowText(m_str);
			SetModified();			
		}
	}
	
	CString CMaskEditComp::get_Caption(void)
	{
		if(state.GetBit(csLoading))
			m_str=GET_PROP_VALUE(CString,Caption)
		
		return m_str;
	}
	
	
	void CMaskEditComp::set_Mask(CString str)
	{
		m_strMask.Empty();
		m_strMask=str;
		SetModified();			
	}
	
	CString CMaskEditComp::get_Mask(void)
	{
		if(state.GetBit(csLoading))
		{
			m_strMask=GET_PROP_VALUE(CString,Mask)
		}
		return m_strMask;
	}

	void CMaskEditComp::set_Literal(CString str)
	{
		m_strLiteral=str;
		SetModified();			
	}
	
	CString CMaskEditComp::get_Literal(void)
	{
		if(state.GetBit(csLoading))
		{
			m_strLiteral=GET_PROP_VALUE(CString,Literal)
		}
		return m_strLiteral;
	}
	
	void CMaskEditComp::set_UseMask(BOOL val)
	{
		m_bUseMask=val;
		SetModified();			
	}
	
	BOOL CMaskEditComp::get_UseMask(void)
	{
		return m_bUseMask;
	}

	void CMaskEditComp::set_IsDate(BOOL val)
	{
		m_isdate=val;
		SetModified();			
	}
	
	BOOL CMaskEditComp::get_IsDate(void)
	{
		return m_isdate;
	}

	void CMaskEditComp::set_IsTime(BOOL val)
	{
		m_isTime=val;
		SetModified();			
	}
	
	BOOL CMaskEditComp::get_IsTime(void)
	{
		return m_isTime;
	}

	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,AutoHScroll,(ES_AUTOHSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,AutoVScroll,(ES_AUTOVSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,LowerCase,(ES_LOWERCASE))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,NoHideSel,(ES_NOHIDESEL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,OemConvert,(ES_OEMCONVERT))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,UpperCase,(ES_UPPERCASE))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CMaskEditComp,WantReturn,(ES_WANTRETURN))
	IMPLEMENT_WINSTYLE_PROPERTY(CMaskEditComp,TextAlign,(ES_LEFT|ES_CENTER|ES_RIGHT))
//////////////////////////////////////////////////////////////////////////
/*	REGISTER_COMPONENT_EX(CDateEdit,CDateEditComp,DecorativeCtrl,IDB_DATEEDIT)
		
	CDateEditComp::CDateEditComp(LPTSTR _name):ControlComponent<CDateEditComp>(_name)
	{
		SetDefaultSize(85,22);
		RegisterEditStyles();
	}
	
	
	CDateEditComp::~CDateEditComp(void)
	{
	}
	
	BOOL CDateEditComp::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CDateEdit::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),get_Caption(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		CSimpleDate Date(DDMMYYYY);
		SetDate(Date);
		return ::IsWindow(m_hWnd);
	}
	
	void CDateEditComp::InitProperty(void)
	{
		ControlComponent<CDateEditComp>::InitProperty();
		DEFINE_PROPERTY(Mask,CString,CDateEditComp,m_strMask)
		DEFINE_PROPERTY(Literal,CString,CDateEditComp,m_strLiteral)
		DEFINE_PROPERTY(UseMask,BOOL,CDateEditComp,m_bUseMask)
		DEFINE_PROPERTY(IsDate,BOOL,CDateEditComp,m_isdate)
		DEFINE_PROPERTY(IsTime,BOOL,CDateEditComp,m_isTime)
		DEFINE_PROPERTY(Caption,CString,CDateEditComp,m_str)

		DEFINE_PROPERTY(AutoHScroll,BOOL,CDateEditComp,FALSE)
		DEFINE_PROPERTY(AutoVScroll,BOOL,CDateEditComp,FALSE)
		DEFINE_PROPERTY(LowerCase,BOOL,CDateEditComp,FALSE)
		DEFINE_PROPERTY(OemConvert,BOOL,CDateEditComp,FALSE)
		DEFINE_PROPERTY(UpperCase,BOOL,CDateEditComp,FALSE)
		DEFINE_PROPERTY(WantReturn,BOOL,CDateEditComp,FALSE)
		DEFINE_PROPERTY(TextAlign,EditAlignText,CDateEditComp,ES_LEFT)
		PUBLIC_PROPERTY(VScroll,TRUE)
		PUBLIC_PROPERTY(HScroll,TRUE)
		
	}
	
	void CDateEditComp::set_Caption(CString str)
	{
		m_str=str;
		if(IsWindow())
		{
			SetWindowText(m_str);
			SetModified();			
		}
	}
	
	CString CDateEditComp::get_Caption(void)
	{
		if(state.GetBit(csLoading))
			m_str=GET_PROP_VALUE(CString, Caption)
		
		return m_str;
	}
	
	
	void CDateEditComp::set_Mask(CString str)
	{
		m_strMask.Empty();
		m_strMask=str;
		SetModified();			
	}
	
	CString CDateEditComp::get_Mask(void)
	{
		if(state.GetBit(csLoading))
		{
			m_strMask= GET_PROP_VALUE(CString, Mask)
		}
		return m_strMask;
	}

	void CDateEditComp::set_Literal(CString str)
	{
		m_strLiteral=str;
		SetModified();			
	}
	
	CString CDateEditComp::get_Literal(void)
	{
		if(state.GetBit(csLoading))
		{
			m_strLiteral= GET_PROP_VALUE(CString, Literal)
		}
		return m_strLiteral;
	}
	
	void CDateEditComp::set_UseMask(BOOL val)
	{
		m_bUseMask=val;
		SetModified();			
	}
	
	BOOL CDateEditComp::get_UseMask(void)
	{
		return m_bUseMask;
	}

	void CDateEditComp::set_IsDate(BOOL val)
	{
		m_isdate=val;
		SetModified();			
	}
	
	BOOL CDateEditComp::get_IsDate(void)
	{
		return m_isdate;
	}

	void CDateEditComp::set_IsTime(BOOL val)
	{
		m_isTime=val;
		SetModified();			
	}
	
	BOOL CDateEditComp::get_IsTime(void)
	{
		return m_isTime;
	}

	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,AutoHScroll,(ES_AUTOHSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,AutoVScroll,(ES_AUTOVSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,LowerCase,(ES_LOWERCASE))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,NoHideSel,(ES_NOHIDESEL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,OemConvert,(ES_OEMCONVERT))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,UpperCase,(ES_UPPERCASE))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CDateEditComp,WantReturn,(ES_WANTRETURN))
	IMPLEMENT_WINSTYLE_PROPERTY(CDateEditComp,TextAlign,(ES_LEFT|ES_CENTER|ES_RIGHT))
*/
//////////////////////////////////////////////////////////////////////////

	BEGIN_LIST_PROPERTY(EditAlignText)
		LIST_ITEM_DECORATE(ES_LEFT,ES_LEFT,Left)
		LIST_ITEM_DECORATE(ES_CENTER,ES_CENTER,Center)
		LIST_ITEM_DECORATE(ES_RIGHT,ES_RIGHT,Right)
	END_LIST_ITEM(EditAlignText)
	
	static void RegisterEditStyles()
	{
		static BOOL IsInited=FALSE;
		if(IsInited==TRUE)
			return;
		
		REGISTER_LIST_PROPERTY(EditAlignText)
			
			IsInited=TRUE;
	}

};
#endif
