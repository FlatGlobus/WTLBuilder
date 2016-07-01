// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __INPLACEEDIT_H
#define __INPLACEEDIT_H
//////////////////////////////////////////////////////////////////////////
#include "PropertyItem.h"
#include "command.h"
#include "EventLib.h"

#pragma warning(disable: 4275)

template <class T,class TBase,class TWinTraits>
class PROPERTY_API CInplaceEditBase :
public CWindowImpl<CInplaceEditBase<T,CWindow,TWinTraits>,TBase,TWinTraits>
{
	BOOL m_cancel;
	PropertyBase * m_prop;
public:
	CInplaceEditBase():m_cancel(FALSE),m_prop(NULL)
	{
	}

	void SetProperty(PropertyBase * prop)
	{
		m_prop=prop;
	}

	PropertyBase * GetProperty()
	{
		return m_prop;
	}

	BOOL IsCancel() 
	{
		return m_cancel;
	}

	virtual void ShowProperty(PropertyBase *)=0;
	virtual void UpdateProperty(PropertyBase *)=0;

	CString GetText()
	{
		int nLen = GetWindowTextLength();
		LPTSTR lpszText=NULL;
		if(nLen > 0)
		{
			lpszText = (LPTSTR)_alloca((nLen+1)*sizeof(TCHAR));
			GetWindowText(lpszText, nLen+1);
		}
		return lpszText;
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	BEGIN_MSG_MAP(CInplaceEditBase)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{	
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		SetFont((HFONT)::SendMessage(GetParent(),WM_GETFONT,0,0));
		SetFocus();
		ShowProperty(m_prop);
		return lRes;
	}

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
		switch( wParam )
		{
		case VK_ESCAPE:
			m_cancel = TRUE;
			::SetFocus(GetParent());
			break;
		case VK_RETURN:
			m_cancel = FALSE;
			UpdateProperty(m_prop);
			break;
		case VK_UP:
		case VK_DOWN:
			::SendMessage(GetParent(), uMsg, wParam, lParam);
			bHandled = TRUE;
			return 0;
		}
		bHandled = TRUE;
		return lRes;
	}

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
        DefWindowProc();
		if(m_cancel == FALSE)
			UpdateProperty(m_prop);
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return DefWindowProc(uMsg, wParam, lParam) | DLGC_WANTALLKEYS;
	}

	static HWND CreateEdit(HWND Parent,CRect & Rect,PropertyBase * prop,CPoint &point,LPARAM)
	{
		CRect rc(Rect);
		rc.bottom-=1;
		rc.left+=1;
				
		T * temp= new T;
		temp->SetProperty(prop);
		HWND ret=temp->Create(Parent,rc);
		if(::IsWindow(ret) && point.x!=-1 && point.y!=-1)
		{
			::ClientToScreen(Parent,&point);
			::ScreenToClient(ret,&point);
			::SendMessage(ret,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(point.x,point.y));
			::SendMessage(ret,WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(point.x,point.y));
		}
		return ret;
	}	

};

//////////////////////////////////////////////////////////////////////////
#endif