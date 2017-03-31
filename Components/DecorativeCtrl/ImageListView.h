// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once

#include <GDIUtil.h>
#include <_util.h>

#define  _BUTTON_WIDTH 10
#define  DELTA_X 0
#define  WM_SELCHANGEPANEL	WM_USER+255
#define  WM_SELCHANGE		WM_USER+256

class CImageListView:
    public CWindowImpl< CImageListView, CWindow, CControlWinTraits >
{
protected:
    CImageList	images;
    long	    selected;
    int			visibleCount;
    int			imageCount;
    int			cx;
    int			cy;
    int			firstVisible;
    int			lastVisible;
    BOOL		leftPressed;
    BOOL		rightPressed;
    COLORREF    imageBkColor;
    COLORREF    mask;
    DWORD       style;
    COLORREF    bkColor;
    int         top;
public:
    DECLARE_WND_CLASS(_T("WTLBuilder_ImageListView"))
    CImageListView(int _cx=16,int _cy=15):cy(_cy),cx(_cx),firstVisible(0),lastVisible(0),
        leftPressed(FALSE),rightPressed(FALSE),imageCount(0),selected(-1),
        imageBkColor(CLR_DEFAULT),mask(CLR_DEFAULT),style(ILD_TRANSPARENT),
        bkColor(::GetSysColor(COLOR_WINDOW))
    {
    }

    BEGIN_MSG_MAP_EX(CImageListView)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
        MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
        MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnLButtonDblClk)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
        END_MSG_MAP()

    HWND Create(HWND Parent,CRect & rc,DWORD _style,UINT id =0)
    {
        style=_style;
        CWindowImpl<CImageListView>::Create(Parent, rc, NULL, WS_CHILD|WS_VISIBLE, 0, id);
        CreateImageList();
        CalculateVisibleCount();
        return m_hWnd;
    }

    LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        CDCHandle dc((HDC)wParam);
        CRect rc;
        GetClientRect(&rc);
        dc.FillSolidRect(&rc,bkColor);
        return TRUE;
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
//        CPoint point;
//        point.x = LOWORD(lParam);
//        point.y = HIWORD(lParam);
//        long sel=MAKELONG(IndexFromPoint(CPoint(point.x-(visibleCount < imageCount ? _BUTTON_WIDTH : 0),point.y)),pageID);
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
        return TRUE;
    }

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        CRect rc;
        GetClientRect(&rc);
        top=_round((double)rc.Height()/2.0)-_round((double)cy/2.0);
        CalculateVisibleCount();
        bHandled = FALSE; 
        return 0;
    }

    BOOL AddImage(HBITMAP bitmap)
    {
        int ret=FALSE;
        ret=images.Add(bitmap,mask);
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

    BOOL AddImage(HICON icon)
    {
        int ret=FALSE;
        ret=images.AddIcon(icon);
        if(ret!=-1)
        {
            imageCount=images.GetImageCount();
            InvalidateRect(NULL,TRUE);
        }
        return ret!=-1;
    }

    void PaintGrid(CDC & dc)
    {
        CRect clientRc;
        GetClientRect(&clientRc);
        dc.FillSolidRect(&clientRc,bkColor);
        if(images.IsNull())
            return;
       
        int shift=0;
        if(visibleCount < imageCount)		
            shift=_BUTTON_WIDTH;

        int colCount=min(visibleCount,imageCount);
        for(int col=0;col < colCount;col++)
        {
            //if((firstVisible+col)==selected)
                //dc.Draw3dRect(shift+col*cx, top, cx,cy,RGB(0,0,0),RGB(255,255,255));
            images.Draw(dc,firstVisible+col,CPoint(shift+col*cx+DELTA_X,top),style);
        }

        if(visibleCount < imageCount)		
        {
            DrawLeftScroolButton(dc);
            DrawRightScroolButton(dc);
        }
    }

    long IndexFromPoint(CPoint & point)
    {
        return firstVisible+(point.x/cx);
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

    void SetWidth(int _cx)
    {
        if(cx != _cx)
        {
            cx = _cx;
            CalculateVisibleCount();
            Invalidate();
        }
    }
    
    int GetWidth()
    {
        return cx;
    }


    void SetHeight(int _cy)
    {
        if(cy != _cy)
        {
            cy = _cy;
            CalculateVisibleCount();
            Invalidate();
        }
    }

    int GetHeight()
    {
        return cy;
    }

    void DrawLeftScroolButton(CDC & dc)
    {
        CRect rc;
        GetClientRect(&rc);

        rc.top=top;
        rc.right=rc.left+_BUTTON_WIDTH;
        rc.bottom=top+cy;

        dc.FillSolidRect(rc,GetSysColor(COLOR_BTNFACE));
        if(!leftPressed)
            dc.Draw3dRect(rc,RGB(255,255,255),RGB(0,0,0));
        else
        {
            dc.Draw3dRect(rc,RGB(0,0,0),RGB(255,255,255));
            rc.left+=1;
        }

        DrawLeftArrow(dc,CPoint(rc.left+2,(rc.top+rc.bottom)/2));
    }

    void DrawRightScroolButton(CDC & dc)
    {
        CRect rc;
        GetClientRect(&rc);
        rc.top=top;
        rc.left=rc.right-_BUTTON_WIDTH;
        rc.bottom = top+cy;		
        dc.FillSolidRect(rc,GetSysColor(COLOR_BTNFACE));
        if(!rightPressed)
            dc.Draw3dRect(rc,RGB(255,255,255),RGB(0,0,0));
        else
        {
            dc.Draw3dRect(rc,RGB(0,0,0),RGB(255,255,255));
            rc.right+=1;
        }
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
        visibleCount=clientRect.Width() / cx;
        if(visibleCount >= imageCount)
            firstVisible=0;
    }

    BOOL LoadBitmapImage(CString & fn,BOOL emptyImages=TRUE)
    {
        CPath fileName(fn);
        if(fileName.GetPath().IsEmpty()==FALSE)
        {
            if(fileName.GetExt().CompareNoCase(_T("bmp"))==0)
            {
                CBitmap bitmap=(HBITMAP)::LoadImage(NULL,fileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                if((HBITMAP)bitmap)
                {
                    if(emptyImages==TRUE)
                    {
                        CSize sz;
                        bitmap.GetSize(sz);
                        CreateImageList(sz.cx);
                    }
                    AddImage(bitmap);
                    CalculateVisibleCount();
                }
            }
            else
                if(fileName.GetExt().CompareNoCase(_T("ico"))==0)
                {
                    HICON icon=(HICON)::LoadImage(NULL,fileName,IMAGE_ICON,cx,cy,LR_LOADFROMFILE);
                    if(icon)
                        AddImage(icon);
                }
        }
        return imageCount != 0;
    }

    BOOL LoadBitmapImage(UINT id,BOOL emptyImages=TRUE)
    {
        CBitmap bitmap=AtlLoadBitmap(id);
        if((HBITMAP)bitmap)
        {
            if(emptyImages==TRUE)
            {
                CSize sz;
                bitmap.GetSize(sz);
                CreateImageList(sz.cx);
            }
            AddImage(bitmap);
            CalculateVisibleCount();
        }
        return imageCount != 0;
    }

    void Clear()
    {
        selected=-1;
        visibleCount=0;
        imageCount=0;
        firstVisible=0;
        lastVisible=0;
        leftPressed=FALSE;
        rightPressed=FALSE;
        if(!images.IsNull())
            images.Destroy();
    }

    void SetBkColor(COLORREF val)
    {
        bkColor=val;
        InvalidateRect(NULL);
    }

    COLORREF GetBkColor(void)
    {
        return bkColor;
    }

    void SetMaskColor(COLORREF val)
    {
        bkColor=val;
        InvalidateRect(NULL);
    }

    COLORREF GetMaskColor(void)
    {
        return bkColor;
    }

    void SetImageBkColor(COLORREF val)
    {
        imageBkColor=val;
        if(!images.IsNull())
        {
            images.SetBkColor(imageBkColor);
            InvalidateRect(NULL);
        }
    }

    COLORREF GetImageBkColor(void)
    {
        return imageBkColor;
    }

    protected:
        BOOL CreateImageList(int imageWidth = 0)
        {
            Clear();
            BOOL ret = images.Create(cx,cy,ILC_COLOR24|ILC_MASK,imageWidth/cx,1);
            if(ret)
                images.SetBkColor(imageBkColor);
            return ret;
        }
};
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace DecorativeCtrl
{

#define IMAGESTYLE_PROPERTY(Name,Style)\
    void set_##Name(BOOL val)\
    {\
    style = val == TRUE ? (style | (Style)): (style & ~(Style));\
    ReCreateImageList();\
    SetModified();\
    }\
    BOOL get_##Name(void)\
    {\
    return (style & (Style))==Style;\
    }

    class CImageListViewComp:public CImageListView,public ControlComponent<DecorativeCtrl::CImageListViewComp>
    {
        CImage bitmap;
        void OnImageChange(CImage *);
        void ReCreateImageList();
    public:
        CImageListViewComp(LPTSTR _name=NULL);
        ~CImageListViewComp();
        virtual BOOL CreateComponent(Component *);

        BEGIN_MSG_MAP_EX(CImageListViewComp)
            CHAIN_MSG_MAP(ControlComponent<CImageListViewComp>)
            CHAIN_MSG_MAP(CImageListView)
        END_MSG_MAP()

        DECLARE_PROPERTY(ImageBkColor,CColorref)
        DECLARE_PROPERTY(MaskColor,CColorref)
        DECLARE_PROPERTY(BkColor,CColorref)
        DECLARE_PROPERTY(cx,long)
        DECLARE_PROPERTY(cy,long)

        virtual void InitProperty(void);
        
        //IMAGESTYLE_PROPERTY(Normal,ILD_NORMAL)
        IMAGESTYLE_PROPERTY(Transparent,ILD_TRANSPARENT)
        IMAGESTYLE_PROPERTY(Mask,ILD_MASK)
        IMAGESTYLE_PROPERTY(Image,ILD_IMAGE)
        IMAGESTYLE_PROPERTY(Blend25,ILD_BLEND25)
        IMAGESTYLE_PROPERTY(Blend50,ILD_BLEND50)
        IMAGESTYLE_PROPERTY(OverlayMask,ILD_OVERLAYMASK)
        IMAGESTYLE_PROPERTY(PreserveAlpha,ILD_PRESERVEALPHA)
        IMAGESTYLE_PROPERTY(Scale,ILD_SCALE)
        IMAGESTYLE_PROPERTY(DPIScale,ILD_DPISCALE)
    };
};
#endif
//////////////////////////////////////////////////////////////////////////
