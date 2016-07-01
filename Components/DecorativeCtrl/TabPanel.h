// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TABCTRL_H
#define __TABCTRL_H
//////////////////////////////////////////////////////////////////////////
#include <atlcrack.h>
#include <Panel.h>


template <class T, class TBase = CWindow, class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CTabPanelImpl: 
public CWindowImpl<T, TBase, TWinTraits>
{
protected:
    CTabCtrl m_tab;
    Panel::CPanelHost m_panelHost;

public:
    typedef CTabPanelImpl< T, TBase, TWinTraits > thisClass;
    BEGIN_MSG_MAP_EX(thisClass)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
        MESSAGE_HANDLER(WM_ENABLE, OnEnable)
        MESSAGE_HANDLER(WM_SETFONT,OnSetFont)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(TCN_SELCHANGE, OnTabSelChange)
        REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()    

    CTabPanelImpl()
    {
    }
    
    ~CTabPanelImpl()
    {
        
    }

    void UpdateLayout()
    {
        if(::IsWindow(m_hWnd))
        {
            RECT rc;
            GetClientRect(&rc);
            
            if(::IsWindow(m_tab.m_hWnd))
            {
                CRect tabRect;
                m_tab.GetItemRect(0,tabRect);
                tabRect.top=0;
                tabRect.left=0;
                tabRect.right=rc.right;
                m_tab.SetWindowPos(HWND_TOP, &tabRect, SWP_NOZORDER|SWP_NOACTIVATE);
            
                if(::IsWindow(m_panelHost.m_hWnd))
                {
                    CRect panelRect(rc);
                    panelRect.top=tabRect.bottom;
                    m_panelHost.SetWindowPos(HWND_TOP,&panelRect,SWP_NOZORDER|SWP_NOACTIVATE);
                }
            }
        }
    }
    
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
        m_tab.Create(m_hWnd,&rcDefault,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,0);

        m_panelHost.Create(m_hWnd,rcDefault,NULL,WS_CHILD|WS_VISIBLE,0);

        BOOL bDummy;
        OnSize(WM_SIZE, SIZE_RESTORED, 0, bDummy);
        
        return lRes;
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        if( wParam != SIZE_MINIMIZED )
        {
            T* pT = static_cast<T*>(this);
            pT->UpdateLayout();
        }
        return 0;
    }
    

    LRESULT OnEnable(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_tab.EnableWindow((BOOL)wParam);
        m_panelHost.EnableWindow((BOOL)wParam);
        return 0;
    }

    LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return TRUE;
    }

    LRESULT OnSetFont(UINT, WPARAM wParam,LPARAM lParam,BOOL&)
    {
        if(wParam)
        {
            if(::IsWindow(m_tab.m_hWnd))
                m_tab.SetFont((HFONT)wParam,(BOOL)lParam);
            if(::IsWindow(m_panelHost.m_hWnd))
                m_panelHost.SetFont((HFONT)wParam,(BOOL)lParam);
        }
        return 0;
    }
    
    LRESULT OnTabSelChange(LPNMHDR pnmh)
    {
        int current=m_tab.GetCurSel();
        return 0;
    }

    void AddPage(LPTSTR pageName)
    {
        if(pageName==NULL)
            return;

        int cur=m_tab.GetItemCount();
        if(cur!=0)
            cur+=1;
        
        TCITEM tab = { 0 };
        tab.mask = TCIF_TEXT;   
        tab.pszText = (LPTSTR)pageName;
        tab.cchTextMax = _tcslen(pageName);
        m_tab.InsertItem(cur, &tab);
        
    }
};    

class CTabPanel: public CTabPanelImpl<CTabPanel>
{
public:
    DECLARE_WND_SUPERCLASS(_T("WTL_TabPanel"), GetWndClassName())
};

//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CTabPanelComp:public CTabPanel,public ControlComponent<CTabPanelComp>
	{
	public:
		CTabPanelComp(LPTSTR _name=NULL);
		~CTabPanelComp(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(CTabPanelComp)
			CHAIN_MSG_MAP(ControlComponent<CTabPanelComp>)
            CHAIN_MSG_MAP(CTabPanel)
		END_MSG_MAP()

		virtual void InitProperty(void);
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
