// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once
//////////////////////////////////////////////////////////////////////////
namespace WTLBuilderCtrl
{
    //////////////////////////////////////////////////////////////////////////
    class CImgListCtrl:public CWindowImpl< CImgListCtrl, CWindow, CControlWinTraits >, public CThemeImpl<CImgListCtrl>
    {
    protected:
        CImageList	images;
        long	    selected;
        int			visibleCount;
        int			imageCount;
        int			colWidth;
        int			colHeight;
        int			firstVisible;
        int			lastVisible;
        BOOL		leftPressed;
        BOOL		rightPressed;

        CToolTipCtrl	m_toolTip;
    public:

    CImgListCtrl(int cx,int cy):colHeight(cy),colWidth(cx),firstVisible(0),lastVisible(0),
            leftPressed(FALSE),rightPressed(FALSE),imageCount(0)
        {
        }

        BEGIN_MSG_MAP_EX(CImgListCtrl)
            CHAIN_MSG_MAP(CThemeImpl<CImgListCtrl>)
            MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
            MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
            MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
            MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
            MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnLButtonDblClk)
            MESSAGE_HANDLER(WM_PAINT, OnPaint)
            //MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
            MESSAGE_HANDLER(WM_SIZE, OnSize)

            //REFLECTED_NOTIFY_CODE_HANDLER_EX(TTN_GETDISPINFO,OnNeedText)
            REFLECTED_NOTIFY_CODE_HANDLER_EX(TTN_NEEDTEXTW,OnNeedText)
            REFLECT_NOTIFICATIONS_EX()

            END_MSG_MAP()

            HWND Create(HWND Parent,CRect & rc,UINT id)
        {
            CWindowImpl<CImgListCtrl>::Create(Parent,rc,NULL,WS_CHILD,0,id);
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
                leftRect.right=leftRect.left+colWidth;
                if(leftRect.PtInRect(point))
                {
                    ScrollRight();
                    leftPressed=TRUE;
                }

                CRect rightRect(clientRc);
                rightRect.left=rightRect.right-colWidth;
                if(rightRect.PtInRect(point))
                {
                    ScrollLeft();
                    rightPressed=TRUE;
                }
            }

            if(!rightPressed && !leftPressed)
            {
                selected=IndexFromPoint(CPoint(point.x-(visibleCount < imageCount ? colWidth : 0),point.y));	
                if(LOWORD(selected) < imageCount)
                ;//???    ::PostMessage(GetParent(),WM_SELCHANGEPANEL,(WPARAM)m_hWnd,selected);
                else
                    selected=-1;
            }
            Invalidate();
            return 0;
        }

        LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
        {
            //CPoint point;
            //point.x = LOWORD(lParam);
            //point.y = HIWORD(lParam);
            //long sel=IndexFromPoint(CPoint(point.x-(visibleCount < imageCount ? colWidth : 0),point.y));
            //ATL::_U_STRINGorID strID((LPCTSTR)get_SelectedName(sel));
            //m_toolTip.UpdateTipText(strID,(HWND)*this,1);
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
            leftRect.right=leftRect.left+colWidth;
            if(leftRect.PtInRect(point))
            {
                leftPressed=TRUE;
                ScrollRight();
                Invalidate();
            }

            CRect rightRect(clientRc);
            rightRect.left=rightRect.right-colWidth;
            if(rightRect.PtInRect(point))
            {
                rightPressed=TRUE;
                ScrollLeft();
                Invalidate();
            }

            if(!rightPressed && !leftPressed)
            {
                selected=IndexFromPoint(CPoint(point.x-colWidth,point.y));	
                //if(selected!=-1)
                //    ::PostMessage(GetParent(),WM_SELCHANGEPANEL,(WPARAM)m_hWnd,selected);
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
            return TRUE;
        }

        LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
        {
            return TRUE;
        }

        LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
        {
            CRect rc;
            GetClientRect(&rc);
            CalculateVisibleCount();
            bHandled = FALSE; 
            return 0;
        }

        BOOL AddImage(HBITMAP bitmap)
        {
            int ret=FALSE;
            ret=images.Add(bitmap,RGB(192,192,192));
            if(ret!=-1)
            {
                imageCount=images.GetImageCount();
                InvalidateRect(NULL,TRUE);
            }
            return ret!=-1;
        }

        BOOL AddImage(ATL::_U_STRINGorID bitmap)
        {
            int ret=FALSE;
            HBITMAP hBitmap=::LoadBitmap(_Module.GetResourceInstance(), bitmap.m_lpstr);
            return AddImage(hBitmap);
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
                shift=colWidth;

            int colCount=min(visibleCount,imageCount);
            for(int col=0;col < colCount;col++)
            {
                if((firstVisible+col)==selected)
                    dc.Draw3dRect(shift+col*colWidth, 0, colWidth,colHeight,RGB(0,0,0),RGB(255,255,255));
                images.Draw(dc,firstVisible+col,CPoint(shift+col*colWidth+1,1),ILD_TRANSPARENT/*ILD_NORMAL*/);
            }

            if(visibleCount < imageCount)		
            {
                DrawLeftScroolButton(dc);
                DrawRightScroolButton(dc);
            }
        }

        //void SetSize(int cx)
        //{
        //	if(::IsWindow(m_hWnd))
        //	{
        //		int x=(cx/colWidth) * colWidth;
        //		MoveWindow(0,0,x,colHeight,TRUE);	
        //		CalculateVisibleCount();			
        //	}
        //}

        long IndexFromPoint(CPoint & point)
        {
            return firstVisible+(point.x / colWidth);
        }

        int get_Selected()
        {
            return selected;
        }

        void UnSelect()
        {
            selected=-1;
            Invalidate();
//            ::PostMessage(GetParent(),WM_SELCHANGEPANEL,(WPARAM)m_hWnd,selected);
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

        int GetColWidth()
        {
            return colWidth;
        }

        void DrawLeftScroolButton(CDC & dc)
        {
            CloseThemeData();
            OpenThemeData (L"BUTTON");

            CRect rc;
            GetClientRect(&rc);
            rc.right=rc.left+colWidth;
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
            rc.left=rc.right-colWidth;
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
    };
//////////////////////////////////////////////////////////////////////////
class CImgListCtrlComp:public CImgListCtrl,ControlComponent<CImgListCtrlComp>
{
public:
    CImgListCtrlComp(LPTSTR _name);
	~CImgListCtrlComp();
    virtual BOOL CreateComponent(Component *);
    BEGIN_MSG_MAP(CImgListCtrlComp)
        CHAIN_MSG_MAP(CImgListCtrl)
        CHAIN_MSG_MAP(ControlComponent<CImgListCtrlComp>)
        //REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
    virtual void InitProperty(void);
    DECLARE_PROPERTY(ImageWidth,long)
};
}