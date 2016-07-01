// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "Panel.h"

namespace Panel
{
   /////////////////////////////////////////////////////////////////////////////
   CPanel::CPanel(void):caption(_T("")),textColor(GetSysColor(COLOR_BTNTEXT)),bkColor(GetSysColor(COLOR_BTNFACE)),
      inner(BDR_RAISEDINNER),outer(BDR_RAISEDOUTER),edge(BF_RECT),vertAlign(DT_VCENTER),horizAlign(DT_CENTER),
      singleLine(DT_SINGLELINE),theme(FALSE),roundCorners(FALSE),cornerParam(3,3),borderColor(RGB(0,0,0)),
      startColor(RGB(0,0,0)),endColor(RGB(0xFF,0xFF,0xFF)),gradientType(GRADIENT_HORIZONTAL),transformationType(TRANSFORMATION_NONE),
      enableGradient(FALSE)
   {
      font.CreateFont(-12,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
         PROOF_QUALITY,VARIABLE_PITCH | FF_ROMAN,_T("MS Sans Serif"));
   }
   
   CPanel::~CPanel()
   {
   }
   
   LRESULT CPanel::OnCreate(UINT, WPARAM,LPARAM,BOOL& bHandled)
   {
       OpenThemeData (L"TAB");
       //OpenThemeData (L"BUTTON");
       bHandled=FALSE;
       return 0;
   }

   LRESULT CPanel::OnPaint(UINT, WPARAM,LPARAM,BOOL&)
   {
      CPaintDC dc(m_hWnd); 
      CRect r;
      GetClientRect(&r);
      
      CRgn rgn;
      HRGN oldRgn=NULL;
      if(roundCorners)
      {
          rgn.CreateRoundRectRgn(r.left,r.top,r.right,r.bottom,cornerParam.x,cornerParam.y);
          dc.SelectClipRgn(rgn);
      }

      if(m_hTheme == NULL || theme == FALSE)
      {
          if(enableGradient==FALSE)
            dc.FillSolidRect(&r,bkColor);
          else
            gradientRender.DrawGradient(dc,r,startColor,endColor,gradientType,transformationType);
      }
      else
        DrawThemeBackground(dc,TABP_BODY,0,&r,NULL);
        //DrawThemeBackground(dc,BP_PUSHBUTTON,0,&r,NULL);
      
      if(!caption.IsEmpty())
      {
         CFont oldFont=dc.SelectFont(font);
         COLORREF tc=dc.SetTextColor(textColor);
         int bkm=dc.SetBkMode(TRANSPARENT);
         dc.DrawText(caption,caption.GetLength(),r,vertAlign|horizAlign|singleLine);
         dc.SetTextColor(tc);
         dc.SetBkMode(bkm);
         dc.SelectFont(oldFont);
      }
      if(m_hTheme == NULL || theme == FALSE)
      {
          if(roundCorners==FALSE)
          {
            dc.DrawEdge(&r,inner|outer,edge);
          }
          else
          {
              dc.SelectClipRgn(NULL);
              CPen pen;
              HBRUSH oldBrush = dc.SelectStockBrush(NULL_BRUSH);
              pen.CreatePen(PS_INSIDEFRAME,1,borderColor);
              HPEN oldpen=dc.SelectPen(pen);
              dc.RoundRect(r,cornerParam);
              dc.SelectPen(oldpen);
              dc.SelectBrush(oldBrush);
          }
      }
      else
          DrawThemeEdge(dc,TABP_BODY,0,&r,inner|outer,edge);
          //DrawThemeEdge(dc,BP_PUSHBUTTON,0,&r,inner|outer,edge);

      return 0;
   }
   
   LRESULT CPanel::OnSetFont(UINT, WPARAM wParam,LPARAM lParam,BOOL&)
   {
      if(wParam)
      {
         LOGFONT lf;
         if(::GetObject((HFONT)wParam,sizeof(LOGFONT),&lf)!=0)
         {
            font.DeleteObject();
            font.CreateFontIndirect(&lf);
            if(lParam)
               InvalidateRect(NULL);
         }
      }
      return 0;
   }
   
   LRESULT CPanel::OnGetFont(UINT, WPARAM,LPARAM,BOOL& Handled)
   {
      Handled=TRUE;
      return (LRESULT)(HFONT)font;
   }
   
   //LRESULT CPanel::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   //{
   //   return TRUE;
   //}
   
   void CPanel::SetInnerBorder(long val)
   {
      if(inner!=val)
      {
         inner=val;
         Invalidate();
         UpdateWindow();
      }
   }
   
   long CPanel::GetInnerBorder(void)
   {
      return inner;
   }
   
   void CPanel::SetOuterBorder(long val)
   {
      if(outer!=val)
      {
         outer=val;
         Invalidate();
         UpdateWindow();
      }
   }
   
   long CPanel::GetOuterBorder(void)
   {
      return outer;
   }
   
   void CPanel::SetEdgeType(long val)
   {
      if(edge!=val)
      {
         edge=val;
         Invalidate();
         UpdateWindow();
      }
   }
   
   long CPanel::GetEdgeType(void)
   {
      return edge;
   }
   
   void CPanel::SetCaption(CString str)
   {
      if(caption!=str)
      {
         caption=str;
         Invalidate();
      }
   }
   
   CString CPanel::GetCaption(void)
   {
      return caption;
   }
   
   void CPanel::SetTextColor(COLORREF c)
   {
      if(textColor!=c)
      {
         textColor=c;
         Invalidate();
      }
   }
   
   COLORREF CPanel::GetTextColor(void)
   {
      return textColor;
   }
   
   void CPanel::SetBkColor(COLORREF c)
   {
      if(bkColor!=c)
      {
         bkColor=c;
         Invalidate();
      }
   }
   
   COLORREF CPanel::GetBkColor(void)
   {
      return bkColor;
   }
   
   void CPanel::SetBorderColor(COLORREF c)
   {
       if(borderColor!=c)
       {
           borderColor=c;
           Invalidate();
       }
   }

   COLORREF CPanel::GetBorderColor(void)
   {
       return borderColor;
   }

   void CPanel::SetHorizTextAlign(long val)
   {
      horizAlign&=~(DT_LEFT|DT_CENTER|DT_RIGHT);
      horizAlign|=val;
      InvalidateRect(NULL);
   }
   
   long CPanel::GetHorizTextAlign(void)
   {
      return horizAlign & (DT_LEFT|DT_CENTER|DT_RIGHT);
   }
   
   void CPanel::SetVertTextAlign(long val)
   {
      vertAlign&=~(DT_TOP|DT_VCENTER|DT_BOTTOM);
      vertAlign|=val;
      InvalidateRect(NULL);
   }
   
   long CPanel::GetVertTextAlign(void)
   {
      return vertAlign & (DT_TOP|DT_VCENTER|DT_BOTTOM);
   }
   
   void CPanel::SetSingleLine(BOOL val)
   {
      if(val==TRUE)
         singleLine|=DT_SINGLELINE;
      else
         singleLine&=~DT_SINGLELINE;
      InvalidateRect(NULL);
   }
   
   BOOL CPanel::GetSingleLine(void)
   {
      return (singleLine & DT_SINGLELINE)!=0;
   }

   void CPanel::SetTheme(BOOL val)
   {
       theme=val;
       InvalidateRect(NULL);
   }

   BOOL CPanel::GetTheme(void)
   {
        return theme;
   }

   void CPanel::SetRoundCorners(BOOL val)
   {
        roundCorners = val;
        InvalidateRect(NULL);
   }

   BOOL CPanel::GetRoundCorners(void)
   {
        return roundCorners;
   }

   void CPanel::SetCornerParam(const CPoint &pt)
   {
        cornerParam = pt;
        InvalidateRect(NULL);
   }

   const CPoint & CPanel::GetCornerParam(void)
   {
       return cornerParam; 
   }

   void CPanel::SetStartColor(COLORREF val)
   {
        startColor = val;
        InvalidateRect(NULL);
   }

   COLORREF CPanel::GetStartColor(void)
   {
        return startColor;
   }

   void CPanel::SetEndColor(COLORREF val)
   {
        endColor = val;
        InvalidateRect(NULL);
   }

   COLORREF CPanel::GetEndColor(void)
   {
        return endColor;
   }

   void CPanel::SetGradientType(GradientType val)
   {
        gradientType = val;
        InvalidateRect(NULL);
   }

   GradientType CPanel::GetGradientType(void)
   {
        return gradientType;
   }

   void CPanel::SetTransformationType(TransformationType val)
   {
        transformationType = val;
        InvalidateRect(NULL);
   }

   TransformationType CPanel::GetTransformationType(void)
   {
        return transformationType;
   }

   void CPanel::SetEnableGradient(BOOL val)
   {
       enableGradient = val;
       InvalidateRect(NULL);
   }

   BOOL CPanel::GetEnableGradient()
   {
       return enableGradient;
   }
   //////////////////////////////////////////////////////////////////////////
   CPanelHost::CPanelHost():current(-1)
   {
   }
   
   CPanelHost::~CPanelHost()
   {
   }
   
   void CPanelHost::AddPanel(CPanel * panel)
   {
      CRect rc;
      GetClientRect(&rc);
      panel->MoveWindow(rc);
      
      if(panels.Find(panel)==-1)
         panels.Add(panel);
      if(panels.GetSize()==1)
         SetCurrent(0l);
   }
   
   long CPanelHost::GetCurrent()
   {
      return current;
   }
   
   void CPanelHost::SetCurrent(long c)
   {
      if(c!=-1 && c < panels.GetSize())
      {
         if(current!=-1)
            panels[current]->ShowWindow(SW_HIDE);
         panels[c]->ShowWindow(SW_SHOW);
      }
      current=c;
   }
   
   void CPanelHost::SetCurrent(CPanel * panel)
   {
      int idx;
      if((idx=panels.Find(panel))!=-1)
         SetCurrent(idx);
   }
   
   LRESULT CPanelHost::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      CRect rc;
      GetClientRect(&rc);
      for(int i=0; i < panels.GetSize(); i++)
         panels[i]->MoveWindow(rc);
      return 0;
   }
   
   LRESULT CPanelHost::OnShow(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      if(current!=-1 && wParam==TRUE && panels.GetSize()!=0)
         panels[current]->ShowWindow(SW_HIDE);
      return 0;
   }
   
   long CPanelHost::GetCount()
   {
      return panels.GetSize();
   }
   
   CPanel*CPanelHost::GetAt(long idx)
   {
      if(idx <panels.GetSize())
      {
         return panels[idx];
      }
      
      return NULL;
   }
};

