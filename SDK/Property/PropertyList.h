// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROPERTYLIST_H
#define __PROPERTYLIST_H

#include <atlcrack.h>
#include <atlctrls.h>
#include "Property.h"
#include "LineTracker.h"
#include "PropertyItem.h"

class CPropertyList : 
	public CWindowImpl< CPropertyList, CListBox>,
	public COwnerDraw< CPropertyList>
{
public:
	DECLARE_WND_CLASS_EX(_T("WTLBUILDER_PROPLIST"),CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,COLOR_WINDOW)

	CPropertyList();
	HWND Create(HWND Parent,CRect & rect,UINT id);

	BEGIN_MSG_MAP(CPropertyList)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)		
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnDblClick)
		MESSAGE_HANDLER(WM_SIZE, OnSize)	
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(OCM_CTLCOLORLISTBOX,OnCtlColor)
        MESSAGE_HANDLER(WM_MOUSEWHEEL,OnMouseWheel)
		REFLECTED_COMMAND_CODE_HANDLER(LBN_SELCHANGE,OnSelChange)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CPropertyList>, 1)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnDblClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& handled);
	LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& handled);
	LRESULT OnSelChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/);
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void DeleteItem(DELETEITEMSTRUCT *lpdis);
	void MeasureItem(MEASUREITEMSTRUCT * lpMeasureItemStruct);
	void DrawItem(DRAWITEMSTRUCT * lpdis);
	void DrawPropertyRect(HDC hDC,const CRect & DrawRc,PropertyBase * prop,BOOL Selected);
	void DrawPropertyValue(HDC hDC,const CRect & DrawRc,PropertyBase * prop);
	void DrawButton(HDC hDC,const CRect & DrawRc,BOOL Pressed=FALSE);
	int ButtonRect(const CRect & rc);
	void DrawHorizLine(HDC hDC,const CRect & DrawRc);
	void ResetContent(void);
	void UpdateProperty(const CString & pn);
	CRect GetPropRect(int idx);
	BOOL DoEditItem(int index, CRect &EditRc,CPoint & point);
	void InsertProperty(CProperties * p);
	int InsertSubProperty(int Index,PropertyBase * prop);
	void RemoveSubProperty(int Index,PropertyBase * prop);
	BOOL DoClickTest(CPoint &pt);
	BOOL DoButtonTest(CPoint & pt);
	CString GetPropertyName(int idx);
	PropertyBase* GetProperty(int idx);
protected:
    void CloseAllChildren();

	CLineTracker	m_Tracker;
	CFont			m_Font;
	CBitmap			m_PlusBmp;
	CBitmap			m_MinusBmp;
	CBitmap			m_ButtonBmp;
	BOOL			m_ButtonPressed;
	CProperties *	properties;
	int				m_SelectedIndex;
	CBrush			m_bkgBrush;
	HWND			m_propEdit;
};
//////////////////////////////////////////////////////////////////////////
#endif