// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TRACKMENU_H
#define __TRACKMENU_H
//////////////////////////////////////////////////////////////////////////
template <class T>
class CTrackMenu
{
protected:
	UINT m_nMenuID;
	BOOL m_bShowMenu;
	BOOL m_bAutoAdd;
	CString m_menuCaption;
	BOOL m_enable;
public:
	CTrackMenu():m_nMenuID(0),m_bShowMenu(FALSE),m_enable(TRUE)
	{
	}

	BEGIN_MSG_MAP(CTrackMenu<T>)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	END_MSG_MAP()
	
	void SetMenuID(UINT id)
	{
		m_nMenuID = id;
	}
	
	void EnableTrackMenu(BOOL val) 
	{
		m_enable=val;
	}

	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if(m_enable)
			ShowMenu(CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
		return 0;
	}

	BOOL ShowMenu(CPoint& pt)
	{
		if(m_nMenuID==0)
			return FALSE;

		m_bShowMenu = TRUE;
		static_cast<T*>(this)->RedrawWindow();

		CMenu menu;
		menu.LoadMenu(m_nMenuID);

		CMenuHandle menuPopup = menu.GetSubMenu(0);

		CustomizeMenu(menuPopup,pt);

		static_cast<T*>(this)->ClientToScreen(&pt);

		if (m_menuCaption.IsEmpty()==FALSE)
		{
			menuPopup.InsertMenu(0, MF_BYPOSITION | MF_STRING, static_cast<T*>(this)->GetDlgCtrlID(), (LPCTSTR)m_menuCaption);
			::SetMenuDefaultItem(menuPopup, 0, true);
		}

		BOOL bRet = menuPopup.TrackPopupMenu(0, pt.x, pt.y, static_cast<T*>(this)->m_hWnd/*static_cast<T*>(this)->GetParent()*/);
		MSG msg;
		while(PeekMessage(&msg,static_cast<T*>(this)->m_hWnd, WM_RBUTTONDOWN, WM_RBUTTONDOWN, PM_REMOVE))
			;

		m_bShowMenu = false;
		static_cast<T*>(this)->RedrawWindow();
		return bRet;
	}

	virtual void CustomizeMenu(CMenuHandle & menu,CPoint &)
	{
	}
};
//////////////////////////////////////////////////////////////////////////
#endif