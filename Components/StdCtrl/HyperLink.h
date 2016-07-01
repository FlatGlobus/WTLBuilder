// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __HYPERLINK_H
#define __HYPERLINK_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
    //class CHyperLink:public WTL::CHyperLinkImpl<CHyperLink>,public ControlComponent<StdCtrl::CHyperLink>
    class CHyperLink:public WTL::CHyperLink,public ControlComponent<StdCtrl::CHyperLink>
	{
        CString label;
        CString hyperlink;
        CColorref   clrLink;
        CColorref   clrVisited;
	public:
		CHyperLink(LPTSTR _name=NULL);
		~CHyperLink(void);
		virtual BOOL CreateComponent(Component *);

        BEGIN_MSG_MAP(StdCtrl::CHyperLink)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CHyperLink>)
            CHAIN_MSG_MAP(CHyperLinkImpl<WTL::CHyperLink>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_PROPERTY(Label,CString)
        DECLARE_PROPERTY(HyperLink,CString)
        DECLARE_PROPERTY(ColorLink,CColorref)
        DECLARE_PROPERTY(ColorVisited,CColorref)
        DECLARE_PROPERTY(PaintLabel,BOOL)
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
