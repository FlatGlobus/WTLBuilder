// MaskEd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaskEdit class

#ifndef _MASKDEFINE_
#define _MASKDEFINE_

//#include "SimpleDate.h"

class CMaskEdit : public CWindowImpl<CMaskEdit, CEdit>
{
// Constructors
public:
  CMaskEdit();
  
// Attributes
  BOOL m_bUseMask;
  BOOL m_isdate; //added this
  BOOL m_isTime;
  CString m_str; //added this
  CString m_strMask;
  CString m_strLiteral;
  CString m_strValid;
  BOOL m_bMaskKeyInProgress;
  CString m_strHours;
  CString m_strMins;
  CString m_strMaskLiteral;

// Operations
  BOOL CheckChar(UINT nChar);
  void SetMask(LPCTSTR lpMask, LPCTSTR lpLiteral = NULL, LPCTSTR lpValid = NULL);
  void SendChar(UINT nChar);
public:

	BEGIN_MSG_MAP(CMaskEdit)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	END_MSG_MAP()
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
};

/*class CDateEdit : public CMaskEdit
{
public:
  CDateEdit();

  void SetDate(CSimpleDate& Date);
  CSimpleDate GetDate();
  BEGIN_MSG_MAP(CDateEdit)
	  CHAIN_MSG_MAP(CMaskEdit)
  END_MSG_MAP()
};
*/
/*class CTimeEdit : public CMaskEdit
{
public:
  CTimeEdit();

// Implementation
public:
  void SetTime(CSimpleDate& Date);
  void SetTime(CString Date);
  CSimpleDate GetTime();
  CString GetTimeStr();
  void SetHours(int hrs);
  void SetMins(int mins);

  BEGIN_MSG_MAP(CTimeEdit)
	CHAIN_MSG_MAP(CMaskEdit)	
  END_MSG_MAP()
	  
};
*/
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace DecorativeCtrl
{
	class CMaskEditComp:public CMaskEdit,public ControlComponent<CMaskEditComp>
	{
	public:
		CMaskEditComp(LPTSTR _name);
		~CMaskEditComp(void);
		
		BEGIN_MSG_MAP(CMaskEditComp)
			CHAIN_MSG_MAP(ControlComponent<CMaskEditComp>)
			CHAIN_MSG_MAP(CMaskEdit)
		END_MSG_MAP()
			
		BOOL CreateComponent(Component * _Parent);
		void InitProperty(void);
		DECLARE_PROPERTY(Caption,CString)
		DECLARE_PROPERTY(Mask,CString)
		DECLARE_PROPERTY(Literal,CString)
		DECLARE_PROPERTY(UseMask,BOOL)
		DECLARE_PROPERTY(IsDate,BOOL)
		DECLARE_PROPERTY(IsTime,BOOL)
		
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoHScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoVScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LowerCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoHideSel)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OemConvert)
		DECLARE_WINSTYLE_BOOL_PROPERTY(UpperCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(WantReturn)
		DECLARE_WINSTYLE_PROPERTY(TextAlign)
	};

	/*class CDateEditComp:public CDateEdit,public ControlComponent<CDateEditComp>
	{
	public:
		CDateEditComp(LPTSTR _name);
		~CDateEditComp(void);
		
		BEGIN_MSG_MAP(CDateEditComp)
			CHAIN_MSG_MAP(ControlComponent<CDateEditComp>)
			CHAIN_MSG_MAP(CDateEdit)
		END_MSG_MAP()
			
		BOOL CreateComponent(Component * _Parent);
		void InitProperty(void);
		DECLARE_PROPERTY(Caption,CString)
		DECLARE_PROPERTY(Mask,CString)
		DECLARE_PROPERTY(Literal,CString)
		DECLARE_PROPERTY(UseMask,BOOL)
		DECLARE_PROPERTY(IsDate,BOOL)
		DECLARE_PROPERTY(IsTime,BOOL)
			
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoHScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoVScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LowerCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoHideSel)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OemConvert)
		DECLARE_WINSTYLE_BOOL_PROPERTY(UpperCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(WantReturn)
		DECLARE_WINSTYLE_PROPERTY(TextAlign)
	};
	*/
};

#endif

//////////////////////////////////////////////////////////////////////////
#endif
