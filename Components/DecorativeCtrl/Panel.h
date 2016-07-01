// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#if !defined(PANELCMP_H)
#define PANELCMP_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Panel.h>
#include "CPagesEdit.h"
#include "StdPropClass.h"

namespace DecorativeCtrl
{
   class CPanelComp:public Panel::CPanel,public ControlComponent<DecorativeCtrl::CPanelComp>
	{
		BOOL isHosted;
        CPointEx cornerPar;
        CColorref _textColor;
        CColorref _bkColor;
        CColorref _borderColor;

        void OnCornerParChanged(CPointEx *);
        void OnGradientChanged(CGradientRender *);
	public:
		CPanelComp(LPTSTR _name=NULL);
		~CPanelComp(void);
        typedef Panel::CPanel panelBase;
        typedef DecorativeCtrl::CPanelComp thisClass;
		virtual BOOL CreateComponent(Component *);
        BEGIN_MSG_MAP(CPanelComp)
			CHAIN_MSG_MAP(ControlComponent<DecorativeCtrl::CPanelComp>)
            CHAIN_MSG_MAP(panelBase)
            FORWARD_NOTIFICATIONS()
		END_MSG_MAP()

		virtual void InitProperty(void);
		virtual HintItem GetHint(CPoint &);

		DECLARE_PROPERTY(Hosted,BOOL)
		DECLARE_PROPERTY(InnerBorder,long)
		DECLARE_PROPERTY(OuterBorder,long)
		DECLARE_PROPERTY(EdgeType,long)
		DECLARE_PROPERTY(Caption,CString)
		DECLARE_PROPERTY(TextColor,CColorref)
		DECLARE_PROPERTY(BkColor,CColorref)
        DECLARE_PROPERTY(BorderColor,CColorref)
		DECLARE_PROPERTY(HorizTextAlign,long)
		DECLARE_PROPERTY(VertTextAlign,long)
		DECLARE_PROPERTY(SingleLine,BOOL)
        DECLARE_PROPERTY(Theme,BOOL)
        DECLARE_PROPERTY(RoundCorners,BOOL)
        DECLARE_PROPERTY(Gradient,BOOL)
	};

   class CPanelHostComp:public Panel::CPanelHost,public ControlComponent<DecorativeCtrl::CPanelHostComp>
	{
        CPointEx cornerPar;
		CString currentName;
        CColorref _bkColor;
        CColorref _borderColor;
        CRect GetMinRect();
        void CopyProperties(CPanelComp * comp);
        void OnCornerParChanged(CPointEx *);

	public:
		CPanelHostComp(LPTSTR _name=NULL);
		~CPanelHostComp(void);

      typedef Panel::CPanelHost panelHostBase;

		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(DecorativeCtrl::CPanelHostComp)
			CHAIN_MSG_MAP(ControlComponent<DecorativeCtrl::CPanelHostComp>)
			CHAIN_MSG_MAP(panelHostBase)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		DECLARE_PROPERTY(InnerBorder,long)
		DECLARE_PROPERTY(OuterBorder,long)
		DECLARE_PROPERTY(BkColor,CColorref)
		DECLARE_PROPERTY(CurrentPage,CString)
        DECLARE_PROPERTY(Pages,CString)
        DECLARE_PROPERTY(Theme,BOOL)
        DECLARE_PROPERTY(RoundCorners,BOOL)
        DECLARE_PROPERTY(BorderColor,CColorref)

		CPanelComp * AddPanel(const CString&,DecorativeCtrl::CPanelComp*);
        void AddPanel(DecorativeCtrl::CPanelComp* panel);
        void DeleteComponent(DecorativeCtrl::CPanelComp * panel);
		void Reset();
		virtual void InitProperty(void);
        virtual void SetBoundsRect(CRect);
		long FindPanel(const CString &);
        void EndEditPages(const CPageInfoArray &);
	};
}
#endif
/////////////////////////////////////////////////////////////////////////////


