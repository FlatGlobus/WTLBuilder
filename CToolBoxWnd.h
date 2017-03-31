// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once 

//#undef __WTLBUILDER__

#include "Panel.h"
#include "wtlenh.h"
#include "SDK\Property\PropertyList.h"
#include "ButtonST.h"

//#define __WTLBUILDER__

typedef CSimpleArray<CString> CStringArray;
class Component;

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define	IDC_PANELHOST	1010
#define	IDC_CTOOLBOXWND_PROPERTIES	1012
#define	IDC_CTOOLBOXWND_FORMS	1013
#define	IDC_TABCTRL	1011
#define	IDC_COMPONENTS	1014
#define	IDC_PROPERTYLIST	1015
#define	IDC_TOOLBAR_PANEL	1016
#define	IDC_SHOW	1017
#define	IDC_CLOSE	1018
#define	IDC_FORMLIST	1019
#define	IDC_SORT	1020
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef CWinTraits<WS_OVERLAPPED|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_TABSTOP|WS_BORDER|WS_DLGFRAME|WS_THICKFRAME,WS_EX_TOOLWINDOW|WS_EX_WINDOWEDGE>	CToolBoxWndWinTraits;
//}}WTLBUILDER_WINDOW_STYLE
class CToolBoxWnd:public CFrameWindowImpl<CToolBoxWnd,CWindow,CToolBoxWndWinTraits>,
    public CScrollImpl<CToolBoxWnd>,public LayoutMgr<CToolBoxWnd>,public CReflection
{
    CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
    CFont	m_formFont;
    Panel::CPanelHost	m_panelhost;
    Panel::CPanel	m_properties;
    Panel::CPanel	m_forms;
    CTabCtrl	m_tabctrl;
    CComboBox	m_components;
    CPropertyList	*m_propertylist;
    Panel::CPanel	m_toolbarpanel;
    CButtonST	m_show;
    CButtonST	m_close;
    CListBox	m_formList;
    CButtonST	m_sort;
    CImageList  m_images;
//}}WTLBUILDER_MEMBER_DECLARATION
    
    void InitLayout(void);
    virtual void DefineLayout();

    void SetActiveForm(Component *);
    void AddForm(Component *);
    void CloseAllForms();
    void CloseForm(Component *,BOOL *);
    Component *activeForm;
public:
    virtual void GetDialogRect(LPRECT r);
    virtual void GetOffset(LPPOINT offset);
    virtual void DoPaint(CDCHandle /*dc*/);
    static const UINT _controlsToClip[];

    typedef CFrameWindowImpl<CToolBoxWnd, CWindow, CToolBoxWndWinTraits>	thisClass;

    //DECLARE_WND_CLASS_EX("TOOLBOXWND",CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,COLOR_BTNFACE)

    virtual BOOL PreTranslateMessage(MSG* pMsg);	

   BEGIN_MSG_MAP_EX(CToolBoxWnd)
        MESSAGE_HANDLER(WM_SIZE, LayoutMgr<CToolBoxWnd>::OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<CToolBoxWnd>::OnEraseBackground)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_CLOSE,OnClose)
        COMMAND_ID_HANDLER(IDC_CLOSE,OnCloseForm)
        COMMAND_ID_HANDLER(IDC_SHOW,OnShowForm)
        COMMAND_ID_HANDLER(IDC_SORT,OnSort)
        COMMAND_CODE_HANDLER(CBN_SELCHANGE,OnComponentChange)
        COMMAND_CODE_HANDLER(LBN_SELCHANGE,OnFormChange)
        NOTIFY_CODE_HANDLER_EX(TCN_SELCHANGE, OnTabSelect)
        NOTIFY_CODE_HANDLER_EX(LBN_DBLCLK,OnFormsDblClk)
        CHAIN_MSG_MAP(thisClass)
        REFLECT_NOTIFICATIONS_EX()
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    CToolBoxWnd(void);
    ~CToolBoxWnd(void);
    int FindForm(Component *);
    HWND Create(HWND);
    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnComponentChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnFormChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnTabSelect(LPNMHDR pnmh);
    LRESULT OnCloseForm(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnShowForm(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnSort(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnFormsDblClk(LPNMHDR);
    LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
