// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __TOOLPANEL_H
#define __TOOLPANEL_H
//////////////////////////////////////////////////////////////////////////
#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <GDIUtil.h>
#include <atlcrack.h>
#include <atltheme.h>
#include "_util.h"

#define  _BUTTON_WIDTH 10
#define  WM_SELCHANGEPANEL	WM_USER+255
#define  WM_SELCHANGE		WM_USER+256

#define BTN_WIDTH 27
#define BTN_HEIGHT 27

#define PAGE_IMG_WIDTH 16
#define PAGE_IMG_HEIGHT 16

class CButtonInfo
{
public:
CButtonInfo():id(-1)
    {}
    CButtonInfo(const CString &_name,DWORD _id):name(_name),id(_id)
    {}
    CString name;
    DWORD   id;
};

typedef CSimpleArray<CButtonInfo> CButtonInfoArray;

class CToolPanel:
    public CWindowImpl< CToolPanel, CWindow, CControlWinTraits >, public CThemeImpl<CToolPanel>
{
protected:
    CImageList	images;
    static long	selected;
    int			visibleCount;
    int			imageCount;
    int			colWidth;
    int			colHeight;
    int			firstVisible;
    int			lastVisible;
    int         curToolTipItem;
    BOOL		leftPressed;
    BOOL		rightPressed;
    static CButtonInfoArray buttons;
    CString		name;
    WORD		pageID;
    
    CToolTipCtrl	m_toolTip;
public:
    CToolPanel(const CString & str,WORD _pageID,int cx=BTN_WIDTH,int cy=BTN_HEIGHT):colHeight(cy),colWidth(cx),firstVisible(0),lastVisible(0),
                leftPressed(FALSE),rightPressed(FALSE),name(str),pageID(_pageID),imageCount(0),curToolTipItem(-1)
    {
    }
    
    BEGIN_MSG_MAP(CToolPanel)
        CHAIN_MSG_MAP(CThemeImpl<CToolPanel>)
        MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
        MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
        MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnLButtonDblClk)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(TTN_NEEDTEXTW,OnNeedText)
    END_MSG_MAP()

    HWND Create(HWND Parent,CRect & rc,UINT id)
    {
        CWindowImpl<CToolPanel>::Create(Parent,rc,NULL,WS_CHILD,0,id);
        DWORD clsStyle=::GetClassLong(m_hWnd,GCL_STYLE);
        clsStyle^=CS_DBLCLKS;
        ::SetClassLong(m_hWnd,GCL_STYLE,clsStyle);

        images.Create(colWidth-2,colHeight-2,ILC_COLOR8|ILC_MASK,0,1);
         
        images.SetBkColor(RGB(192,192,192)/*CLR_NONE*/ /*::GetSysColor(COLOR_BTNFACE)*/);
        CalculateVisibleCount();

        m_toolTip.Create(*this,NULL,NULL,TTS_ALWAYSTIP,WS_EX_TOPMOST);
        // Create inactive
        m_toolTip.Activate(false);
        // Enable multiline
        m_toolTip.SetMaxTipWidth(400);
        CRect rect; 
        GetClientRect(rect);
        m_toolTip.AddTool(*this,_T(""), rect,1);
        m_toolTip.Activate(TRUE);
        return m_hWnd;
    }
    
    LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if(m_toolTip.IsWindow())
            m_toolTip.RelayEvent((LPMSG)m_pCurrentMsg);
        bHandled = FALSE;
        return TRUE;
    }

    LRESULT OnNeedText(LPNMHDR pnmh)
    {
        TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pnmh;
        pTTT->lpszText=_T("");
        return 0;
    }

    LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        CPoint point;
        point.x = LOWORD(lParam);
        point.y = HIWORD(lParam);
        if(visibleCount < imageCount)		
        {			
            CRect clientRc;
            GetClientRect(&clientRc);
            CRect leftRect(clientRc);
            leftRect.right=leftRect.left+_BUTTON_WIDTH;
            if(leftRect.PtInRect(point))
            {
                ScrollRight();
                leftPressed=TRUE;
            }

            CRect rightRect(clientRc);
            rightRect.left=rightRect.right-_BUTTON_WIDTH;
            if(rightRect.PtInRect(point))
            {
                ScrollLeft();
                rightPressed=TRUE;
            }
        }

        if(!rightPressed && !leftPressed)
        {
            selected=IndexFromPoint(CPoint(point.x-(visibleCount < imageCount ? _BUTTON_WIDTH : 0),point.y));	
            if(LOWORD(selected) < imageCount)
                ::PostMessage(GetParent(),WM_SELCHANGEPANEL,(WPARAM)m_hWnd,selected);
            else
                selected=-1;
        }
        Invalidate();
        return 0;
    }

    LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        CPoint point;
        point.x = LOWORD(lParam);
        point.y = HIWORD(lParam);
        long sel=MAKELONG(IndexFromPoint(CPoint(point.x-(visibleCount < imageCount ? _BUTTON_WIDTH : 0),point.y)),pageID);
        if(sel!=curToolTipItem)
        {
            curToolTipItem = sel;
            CString cmpPage, cmpName;
            ExtractName(get_SelectedName(sel), cmpPage, cmpName);
            m_toolTip.UpdateTipText(ATL::_U_STRINGorID(cmpName),(HWND)*this,1);
        }
        return 0;
    }

    LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        if(leftPressed || rightPressed)		
        {
            leftPressed=FALSE;
            rightPressed=FALSE;
            Invalidate();
        }
        return 0;
    }
    
    LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        m_toolTip.RelayEvent((LPMSG)GetCurrentMessage());
        CPoint point;
        point.x = LOWORD(lParam);
        point.y = HIWORD(lParam);
        
        CRect clientRc;
        GetClientRect(&clientRc);
        CRect leftRect(clientRc);
        leftRect.right=leftRect.left+_BUTTON_WIDTH;
        if(leftRect.PtInRect(point))
        {
            leftPressed=TRUE;
            ScrollRight();
            Invalidate();
        }
        
        CRect rightRect(clientRc);
        rightRect.left=rightRect.right-_BUTTON_WIDTH;
        if(rightRect.PtInRect(point))
        {
            rightPressed=TRUE;
            ScrollLeft();
            Invalidate();
        }
        
        if(!rightPressed && !leftPressed)
        {
            selected=IndexFromPoint(CPoint(point.x-_BUTTON_WIDTH,point.y));	
            if(selected!=-1)
                ::PostMessage(GetParent(),WM_SELCHANGEPANEL,(WPARAM)m_hWnd,selected);
        }

        rightPressed=leftPressed=FALSE;
        Invalidate();
        return 0;
    }

    LRESULT OnPaint(UINT, WPARAM,LPARAM,BOOL&)
    {
        CPaintDC    pdc(m_hWnd);
        CRect clientRect;
        GetClientRect(clientRect);
        CPaintDCEx	dc(pdc,clientRect);
        PaintGrid(dc);
        return FALSE;
    }

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CRect rc;
        GetClientRect(&rc);
        CalculateVisibleCount();
        bHandled = FALSE; 
        return 0;
    }

    CString SplitName(const CString& cmdName)
    {
        if(cmdName.IsEmpty()==FALSE)
            return name+_T(":")+cmdName;
        return _T("");
    }
    
    int Find(const CString& cmdName)
    {
        CString str=SplitName(cmdName);
        for(int i=0; i < buttons.GetSize();i++)
        {
            if(buttons[i].name==str)
                return i;
        }
        return -1;
    }

    BOOL AddImage(HBITMAP bitmap,const CString& cmdName)
    {
        int ret=FALSE;
        ret=images.Add(bitmap,RGB(192,192,192));
        if(ret!=-1)
        {
            imageCount=images.GetImageCount();
            if(Find(cmdName)!=-1)
                return ret!=-1;

            buttons.Add(CButtonInfo(SplitName(cmdName),MAKELONG(ret,pageID)));
            InvalidateRect(NULL,TRUE);
        }
        return ret!=-1;
    }

    BOOL AddImage(ATL::_U_STRINGorID bitmap,const CString& cmdName)
    {
        int ret=FALSE;
        HBITMAP hBitmap=::LoadBitmap(_Module.GetResourceInstance(), bitmap.m_lpstr);
        return AddImage(hBitmap,cmdName);
    }
    
    void PaintGrid(CDC & dc)
    {
        CloseThemeData();
        OpenThemeData (L"TAB");
        CRect clientRc;
        GetClientRect(&clientRc);
        if(m_hTheme == NULL)
            dc.FillSolidRect(&clientRc,GetSysColor(COLOR_3DFACE));
        else
            DrawThemeBackground(dc,TABP_BODY,0,&clientRc,NULL);

        if(images.IsNull())
            return;
        
        int imCount=images.GetImageCount();
        int shift=0;
        if(visibleCount < imageCount)		
            shift=_BUTTON_WIDTH;

        int colCount=min(visibleCount,imageCount);
        for(int col=0;col < colCount;col++)
        {
            if(MAKELONG((firstVisible+col),pageID)==selected)
                dc.Draw3dRect(shift+col*colWidth, 0, colWidth,colHeight,RGB(0,0,0),RGB(255,255,255));
            images.Draw(dc,firstVisible+col,CPoint(shift+col*colWidth+1,1),ILD_TRANSPARENT/*ILD_NORMAL*/);
        }

        if(visibleCount < imageCount)		
        {
            DrawLeftScroolButton(dc);
            DrawRightScroolButton(dc);
        }
    }

    long IndexFromPoint(CPoint & point)
    {
        return MAKELONG((firstVisible+(point.x / (colWidth))),pageID);
    }

    int get_Selected()
    {
        return selected;
    }
    
    void UnSelect()
    {
        selected=-1;
        Invalidate();
        ::PostMessage(GetParent(),WM_SELCHANGEPANEL,(WPARAM)m_hWnd,selected);
    }

    void SetColWidth(int cx)
    {
        if(colWidth != cx)
        {
            colWidth = cx;
            CalculateVisibleCount();
            Invalidate();
        }
    }
    
    void DrawLeftScroolButton(CDC & dc)
    {
        CloseThemeData();
        OpenThemeData (L"BUTTON");

        CRect rc;
        GetClientRect(&rc);
        rc.right=rc.left+_BUTTON_WIDTH;
        rc.bottom=27;

        if(m_hTheme == NULL)
        {
            dc.FillSolidRect(rc,GetSysColor(COLOR_BTNFACE));
            if(!leftPressed)
                dc.Draw3dRect(rc,RGB(255,255,255),RGB(0,0,0));
            else
            {
                dc.Draw3dRect(rc,RGB(0,0,0),RGB(255,255,255));
                rc.left+=1;
            }
        }
        else
            DrawThemeBackground(dc,BP_PUSHBUTTON,leftPressed ? PBS_PRESSED  : PBS_NORMAL,&rc,NULL);
            
        DrawLeftArrow(dc,CPoint(rc.left+2,(rc.top+rc.bottom)/2));
    }

    void DrawRightScroolButton(CDC & dc)
    {
        CloseThemeData();
        OpenThemeData (L"BUTTON");

        CRect rc;
        GetClientRect(&rc);
        rc.left=rc.right-_BUTTON_WIDTH;
        rc.bottom = 27;		
        if(m_hTheme == NULL)
        {
            dc.FillSolidRect(rc,GetSysColor(COLOR_BTNFACE));
            if(!rightPressed)
                dc.Draw3dRect(rc,RGB(255,255,255),RGB(0,0,0));
            else
            {
                dc.Draw3dRect(rc,RGB(0,0,0),RGB(255,255,255));
                rc.right+=1;
            }
        }
        else
            DrawThemeBackground(dc,BP_PUSHBUTTON,leftPressed ? PBS_PRESSED  : PBS_NORMAL,&rc,NULL);
        DrawRightArrow(dc,CPoint(rc.right-3,(rc.top+rc.bottom)/2));
    }

    void DrawRightArrow(CDC & dc,CPoint at,COLORREF fillColor=RGB(0x0,0x0,0x0))
    {
        POINT pts[]={
            {-4,0},
            {-4,-4},
            {0,0},
            {-4,4},
            {-4,0}
        };

        CPen Pen;
        Pen.CreatePen(PS_INSIDEFRAME,1,RGB(0,0,0));
        dc.SelectPen(Pen);
        
        CBrush Brush;
        Brush.CreateSolidBrush(fillColor);
        dc.SelectBrush(Brush);
        
        for(int i=0; i < 5;i++)
        {
            pts[i].x+=at.x;
            pts[i].y+=at.y;
        }
        dc.Polygon(pts,5);
    }
    
    // <-
    void DrawLeftArrow(CDC & dc,CPoint at,COLORREF fillColor=RGB(0x0,0x0,0x0))
    {
        POINT pts[]={
            {4,0},
            {4,-4},
            {0,0},
            {4,4},
            {4,0}
        };
        CPen Pen;
        Pen.CreatePen(PS_INSIDEFRAME,1,RGB(0,0,0));
        dc.SelectPen(Pen);
        
        CBrush Brush;
        Brush.CreateSolidBrush(fillColor);
        dc.SelectBrush(Brush);
        
        for(int i=0; i < 5;i++)
        {
            pts[i].x+=at.x;
            pts[i].y+=at.y;
        }
        dc.Polygon(pts,5);
    }

    void ScrollRight()
    {
        if(images.IsNull())
            return;
        CRect clientRect;
        GetClientRect(clientRect);
        firstVisible=firstVisible!=0 ? firstVisible-1 : 0;
    }

    void ScrollLeft()
    {
        if(images.IsNull())
            return;
        if(firstVisible ==(imageCount-visibleCount))
            return;
        firstVisible=firstVisible < (imageCount-visibleCount) ? firstVisible+1 : imageCount-visibleCount+1;
    }

    void CalculateVisibleCount(void)
    {
        CRect clientRect;
        GetClientRect(clientRect);
        visibleCount=clientRect.Width() / colWidth;
        if(visibleCount >= imageCount)
            firstVisible=0;
    }

    const CString & GetName()
    {
        return name;
    }

    static CString get_SelectedName(void)
    {
        for(int i=0; i < buttons.GetSize();i++)
            if(buttons[i].id==selected)
                return buttons[i].name;
        return _T("");
    }

    CString get_SelectedName(int idx)
    {
        for(int i=0; i < buttons.GetSize();i++)
            if(buttons[i].id==idx)
                return buttons[i].name;
        return _T("");
    }
    
    static void ReleaseButtonArray()
    {
        buttons.RemoveAll();
    }
};
//////////////////////////////////////////////////////////////////////////
typedef CSimpleArray<CToolPanel *> CPanelArray;

class CToolTab : 
public CWindowImpl<CToolTab, CTabCtrl>,
public CDynamicChain
{
public:
    DECLARE_WND_SUPERCLASS(NULL, CTabCtrl::GetWndClassName())
    
    CPanelArray pages;
    int 		currentPanel;	
    HWND		m_hWndClient;
    CImageList  imageList;

    BEGIN_MSG_MAP(CToolTab)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_SELCHANGEPANEL,OnChange);
        REFLECTED_NOTIFY_CODE_HANDLER_EX(TCN_SELCHANGE, OnTabSelect)
    END_MSG_MAP()
        
    CToolTab():m_hWndClient(NULL),currentPanel(-1)
    {
    }

    virtual ~CToolTab()
    {
        for(int i=0; i < pages.GetSize();i++)
            delete pages[i];
        pages.RemoveAll();
        CToolPanel::ReleaseButtonArray();		
    }
    
    HWND Create(HWND hWndParent, CRect rc,int ID)
    {
        imageList.Create(PAGE_IMG_WIDTH,PAGE_IMG_HEIGHT,ILC_COLOR8|ILC_MASK,0,1);
        //imageList.SetBkColor(RGB(192,192,192));
        
        HWND tabWnd = CWindowImpl<CToolTab, CTabCtrl>::Create(hWndParent,rc,NULL, 
            WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | TCS_TABS | TCS_FOCUSNEVER,0,ID);
            
        if(::IsWindow(tabWnd))
            SetImageList(imageList);
        return tabWnd;    
    }

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if(currentPanel!=-1)
        {
            m_hWndClient=*pages[currentPanel];
            CRect client,item;
            GetItemRect(currentPanel,&item);

            GetClientRect(&client);
            client.top = item.bottom + 1;
            if(::IsWindow(m_hWndClient))
                ::MoveWindow(m_hWndClient,client.left,client.top,client.Width(),client.Height(), FALSE);
        }
        return 0;
    }
    
    LRESULT OnTabSelect(LPNMHDR pnmh)
    {
        HWND hwndOld=NULL, hwndNew=NULL;
        if(currentPanel!=-1)
            hwndOld=*pages[currentPanel];
                
        currentPanel=GetCurSel();

        if(currentPanel!=-1)
        {
            hwndNew=*pages[currentPanel];
            SetChainEntry(0,pages[currentPanel]);
        }
        m_hWndClient = hwndNew;
        CRect item, client;
        GetItemRect(currentPanel,&item);
        GetClientRect(&client);

        client.top = item.bottom+1;		

        if(::IsWindow(hwndOld))
            ::ShowWindow(hwndOld, SW_HIDE);

        if (::IsWindow(hwndNew))
        {
            ::MoveWindow(hwndNew, client.left, client.top, client.Width(), client.Height(), FALSE);
            ::ShowWindow(hwndNew, SW_SHOW);
        }
        return 0;
    };
    
    LRESULT OnChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ::SendMessage(::GetParent(m_hWnd),WM_SELCHANGE,(WPARAM)m_hWnd,lParam);
        bHandled=FALSE;
        return 0;
    }

    CToolPanel *AddPage(const CString & name)
    {
        CToolPanel * temp=GetPanel(name);
        if(temp)
            return temp;

        HBITMAP bmp=NULL;
        SendEvent(evGetPageBitmap,(LPCTSTR)name,&bmp);
        int imgIdx = -1;
        if(bmp!=NULL)
            imgIdx=imageList.Add(bmp,RGB(192,192,192));

        TCITEM tab = { 0 };
        tab.mask = TCIF_TEXT|TCIF_IMAGE;   
        tab.pszText = (LPTSTR)(LPCTSTR)name;
        tab.cchTextMax = name.GetLength();
        tab.iImage = imgIdx;
        int currIdx = AddItem(&tab);

        SetFont(AtlGetStockFont(ANSI_VAR_FONT));
        temp=new CToolPanel(name,currIdx);
        pages.Add(temp);

        CRect client,item;
        GetItemRect(currIdx,&item);
        GetClientRect(&client);
        client.top = item.bottom+1;
        
        temp->Create(m_hWnd, client,100 + currIdx);
        temp->AddImage(IDB_ARROW,_T(""));
        BOOL isFirst = FALSE;
        SendEvent(evIsFirstPage, (LPCTSTR)name, &isFirst);
        if(isFirst == TRUE)
        {
            currentPanel= currIdx;
            m_hWndClient=*pages[currentPanel];
            SetChainEntry(0, pages[currentPanel]);
            SetCurSel(currentPanel);
            pages[currentPanel]->ShowWindow(SW_SHOW);
        }
        
        return temp;
    }

    CToolPanel *GetPanel(int idx)
    {
        return pages[idx];
    }

    CToolPanel *GetPanel(const CString& str)
    {
        for(int i=0; i < pages.GetSize(); i++)
            if(pages[i]->GetName()==str)
                return pages[i];
        return NULL;
    }

    BOOL AddImage(const CString& str,HBITMAP bitmap,const CString& cmdName)
    {
        CToolPanel *panel=GetPanel(str);
        if(panel==NULL)
        {
            panel = AddPage(str);
            if(panel == NULL)
                return FALSE;
        }
        BOOL ret=panel->AddImage(bitmap,cmdName);
        return ret;
    }

    BOOL AddImage(const CString& str,ATL::_U_STRINGorID bitmap,const CString& cmdName)
    {
        CToolPanel *panel=GetPanel(str);
        if(panel==NULL)
        {
            if((panel=AddPage(str))==NULL)
                return FALSE;
        }
        return panel->AddImage(bitmap,cmdName);
    }

    CString get_SelectedName(void)
    {
        return CToolPanel::get_SelectedName();
    }

    void UnSelect()
    {
        for(int i=0; i < pages.GetSize(); i++)
            pages[i]->UnSelect();

    }
    
};

//////////////////////////////////////////////////////////////////////////
#endif

