// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#if !defined(AFX_CPANEL_H)
#define AFX_CPANEL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <atlcrack.h>
#include <atltheme.h>
#include "GradientRender.h"

namespace Panel
{
   class CPanel : public CWindowImpl<CPanel>,public CThemeImpl<CPanel>
   {
   protected:
      long		inner;
      long		outer;
      long		edge;
      CString	caption;
      COLORREF	textColor;
      COLORREF	bkColor;
      COLORREF  borderColor;
      CFont		font;
      long		vertAlign;
      long		horizAlign;
      long		singleLine;
      BOOL      theme;
      BOOL      roundCorners;
      CPoint    cornerParam;

      COLORREF  startColor;
      COLORREF  endColor;
      GradientType gradientType;
      TransformationType transformationType;
      BOOL      enableGradient;
      CGradientRender gradientRender;

   public:
      DECLARE_WND_CLASS(NULL)
         
      CPanel(void);
      virtual ~CPanel();
      
      void SetInnerBorder(long);
      long GetInnerBorder(void);
      
      void SetOuterBorder(long);
      long GetOuterBorder(void);
      
      void SetEdgeType(long);
      long GetEdgeType(void);
      
      void SetCaption(CString);
      CString GetCaption(void);
      
      void SetTextColor(COLORREF);
      COLORREF GetTextColor(void);
      
      void SetBkColor(COLORREF);
      COLORREF GetBkColor(void);
      
      void SetBorderColor(COLORREF);
      COLORREF GetBorderColor(void);

      void SetHorizTextAlign(long);
      long GetHorizTextAlign(void);
      
      void SetVertTextAlign(long);
      long GetVertTextAlign(void);
      
      void SetSingleLine(BOOL);
      BOOL GetSingleLine(void);

      void SetTheme(BOOL);
      BOOL GetTheme(void);

      void SetRoundCorners(BOOL);
      BOOL GetRoundCorners(void);

      void SetCornerParam(const CPoint &);
      const CPoint & GetCornerParam(void);

      void SetStartColor(COLORREF);
      COLORREF GetStartColor(void);

      void SetEndColor(COLORREF);
      COLORREF GetEndColor(void);

      void SetGradientType(GradientType);
      GradientType GetGradientType(void);

      void SetTransformationType(TransformationType);
      TransformationType GetTransformationType(void);

      void SetEnableGradient(BOOL);
      BOOL GetEnableGradient();

      BEGIN_MSG_MAP(CPanel)
         CHAIN_MSG_MAP(CThemeImpl<CPanel>)
         MESSAGE_HANDLER(WM_PAINT, OnPaint)
         MESSAGE_HANDLER(WM_CREATE, OnCreate)
         MESSAGE_HANDLER(WM_SETFONT,OnSetFont)
         MESSAGE_HANDLER(WM_GETFONT,OnGetFont)
         FORWARD_NOTIFICATIONS()
      END_MSG_MAP()
      
      LRESULT OnCreate(UINT, WPARAM,LPARAM,BOOL&);
      LRESULT OnPaint(UINT, WPARAM,LPARAM,BOOL&);
      LRESULT OnSetFont(UINT, WPARAM,LPARAM,BOOL&);
      LRESULT OnGetFont(UINT, WPARAM,LPARAM,BOOL&);
   };
   //////////////////////////////////////////////////////////////////////////
   typedef CSimpleArray<CPanel*> CPanels;
   
   class CPanelHost : public CPanel
   {
   protected:
      CPanels panels;
      long current;
   public:
      DECLARE_WND_CLASS(NULL)
         
      CPanelHost(void);
      virtual ~CPanelHost();
      
      void AddPanel(CPanel *);
      long GetCurrent();
      void SetCurrent(long);
      void SetCurrent(CPanel *);
      long GetCount();
      CPanel*GetAt(long);
      
      BEGIN_MSG_MAP(CPanelHost)
         MESSAGE_HANDLER(WM_SIZE, OnSize)
         MESSAGE_HANDLER(WM_SHOWWINDOW,OnShow) 
         FORWARD_NOTIFICATIONS()
         CHAIN_MSG_MAP(CPanel)
      END_MSG_MAP()
      LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
      LRESULT OnShow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
   };
};
//////////////////////////////////////////////////////////////////////////
#endif 

