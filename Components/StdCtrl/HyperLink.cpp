// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include <atlctrlx.h>
#include "hyperlink.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	REGISTER_COMPONENT(CHyperLink,StdCtl,IDB_HYPERLINK)

	CHyperLink::CHyperLink(LPTSTR _name):ControlComponent<StdCtrl::CHyperLink>(_name),clrLink(RGB(0, 0, 255)),
    clrVisited(RGB(128, 0, 128))
	{
		SetDefaultSize(40,20);
	}

    
    CHyperLink::~CHyperLink(void)
	{
	}

	BOOL CHyperLink::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		Create((HWND)_Parent->GetHandle(),GetBoundsRect(),get_Label(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CHyperLink::InitProperty(void)
	{
		ControlComponent<StdCtrl::CHyperLink>::InitProperty();
        DEFINE_PROPERTY(PaintLabel,BOOL,CHyperLink,TRUE)
		DEFINE_PROPERTY(Label,CString,CHyperLink,_T(""))
	    DEFINE_PROPERTY(HyperLink,CString,CHyperLink,_T(""))
        DEFINE_PROPERTY(ColorLink,CColorref,CHyperLink,clrLink)
        DEFINE_PROPERTY(ColorVisited,CColorref,CHyperLink,clrVisited)
    }

    void CHyperLink::set_Label(CString str)
    {
        label=(LPCTSTR)str;
        SetLabel((LPCTSTR)label);
        if(IsWindow())
           InvalidateRect(NULL);
        SetModified();
    }
        
    CString CHyperLink::get_Label(void)
    {
        if(state.GetBit(csLoading))
        {
           label= GET_PROP_VALUE(CString, Label)
        }
        return label;
    }

    void CHyperLink::set_HyperLink(CString str)
    {
        hyperlink=(LPCTSTR)str;
        SetHyperLink((LPCTSTR)hyperlink);
        if(IsWindow())
            InvalidateRect(NULL);
        SetModified();
    }
    
    CString CHyperLink::get_HyperLink(void)
    {
        if(state.GetBit(csLoading))
        {
            hyperlink= GET_PROP_VALUE(CString, HyperLink)
        }
        return hyperlink;
    }

    void CHyperLink::set_ColorLink(CColorref val)
    {
        m_clrLink=clrLink=val;
        if(IsWindow())
           InvalidateRect(NULL);
        SetModified();
    }
    
    CColorref CHyperLink::get_ColorLink(void)
    {
        return clrLink;
    }

    void CHyperLink::set_ColorVisited(CColorref val)
    {
        m_clrVisited=clrVisited=val;
        if(IsWindow())
            InvalidateRect(NULL);
        SetModified();
    }
    
    CColorref CHyperLink::get_ColorVisited(void)
    {
        return clrVisited;
    }

    void CHyperLink::set_PaintLabel(BOOL val)
    {
        m_bPaintLabel=val==TRUE;
        if(IsWindow())
            InvalidateRect(NULL);
        SetModified();
    }
    
    BOOL CHyperLink::get_PaintLabel(void)
    {
        return m_bPaintLabel;
    }

//////////////////////////////////////////////////////////////////////////
}