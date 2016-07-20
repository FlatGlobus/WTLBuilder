// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once

#pragma warning( disable:4275)

#define DECLARE_WND_CLASS_NULL(WndClassName) \
    static CWndClassInfo& GetWndClassInfo() \
{ \
    static CWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, StartWindowProc, \
        0, 0, NULL, NULL, NULL, (HBRUSH)NULL, NULL, WndClassName, NULL }, \
        NULL, NULL, IDC_ARROW, TRUE, 0, _T("") \
    }; \
    return wc; \
}

#include <vector>
#include <algorithm>
#include "TrackMenu.h"
#include <atlres.h>

#define DESIGNERCTRL_ID 0x7FFF
#define WM_UPDATE_DESIGNER WM_USER+204

typedef std::vector<long> CLongArray;
class Components;
class Component;
class  PROPERTY_API CDesignerCtrl : public CWindowImpl<CDesignerCtrl, CWindow>,
    public CTrackMenu<CDesignerCtrl>
{
public:
	DECLARE_WND_CLASS_NULL(_T("WTLBUILDER_DESIGNER_WINDOW"))
    CDesignerCtrl(void);
	HWND Create(Component *Parent,Components *);
	virtual ~CDesignerCtrl();
	BEGIN_MSG_MAP(CDesignerCtrl)
        MESSAGE_HANDLER(WM_SIZE,OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
        MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
        MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnLButtonDblClk)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGED,OnWindowPosChanged)
        MESSAGE_HANDLER(WM_UPDATE_DESIGNER,OnUpdateDesigner)
        COMMAND_ID_HANDLER(ID_EDIT_CUT,OnEditCommand)
        COMMAND_ID_HANDLER(ID_EDIT_COPY,OnEditCommand)
        COMMAND_ID_HANDLER(ID_EDIT_PASTE,OnEditCommand)
        COMMAND_ID_HANDLER(ID_EDIT_CLEAR,OnEditCommand)
        COMMAND_ID_HANDLER(ID_EDIT_SELECT_ALL,OnEditCommand)
        CHAIN_MSG_MAP(CTrackMenu<CDesignerCtrl>)
	END_MSG_MAP()

    void ShowGrid(BOOL val);
    BOOL IsShowGrid();
    void ShowGSGuides(BOOL val);
    BOOL IsShowGSGuides();
    void SetMoveableGSGuides(BOOL val);
    BOOL IsMoveableGSGuides();
    CSize & GetGridSize();
    void SetFromTopToBottom(BOOL val);
    BOOL GetFromTopToBottom();
    void SetFromLeftToRight(BOOL val);
    BOOL GetFromLeftToRight();
    void SetOffset(CPoint val);
    CPoint GetOffset();
    void SetComponentCreated();
    void PaintGoldenGrid(CDC &);
    Components * GetComponents();
    Component  * GetParentForm();
    void PaintGrid(CDC &,COLORREF);
    CPoint AlignToGrid(const CPoint &xy);
    CRect  AlignToGrid(const CRect & rc);
    void SetTabIndexMode(BOOL);
    BOOL GetTabIndexMode();
	void BringToTop();
	void DrawFocusRect(const CRect&);
protected:
    Component  * curentComp;
	Components * components;
	Component  * Parent;
	BOOL	    isShowgrid;		
    BOOL	    isShowGoldenGrid;
    BOOL	    isGoldenGridMoveable;
	CSize	    gridDim;
    CPoint      offset;
    CPoint	    deltaPoint;
    CPoint      downPoint;
    CLongArray  xGolden;
    CLongArray  yGolden;
    BOOL        isGridPressed;
    BOOL        FromLeftToRight;
    BOOL        FromTopToBottom;
    BOOL        componentCreated;
    BOOL        tabIndexMode;
    long        tabIndex;
   
    void CalculateGoldenXY();
    BOOL IsGoldenGrid(CPoint & at);
    void MoveGoldenXY(CPoint &xy);
    int FindXSide(CPoint & at);
    int FindYSide(CPoint & at);
    virtual void CustomizeMenu(CMenuHandle & menu,CPoint & at);
    void ShowTabIndexes(CDC &);
    
public:
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKeyUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnUpdateDesigner(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnEditCommand(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
