// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "..\Property\PropertyListEdit.h"
#include "..\Property\ComponentList.h"
#include "SplitterBar.h"
//////////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
namespace ViksoeCtrl
{
	REGISTER_COMPONENT_EX(CVertSplitterCtrl,CVertSplitterCtrlComp,ViksoeCtrl,IDB_SCANFEDITCTRL)
		
    CVertSplitterCtrlComp::CVertSplitterCtrlComp(char * _name):ControlComponent<CVertSplitterCtrlComp>(_name),
    leftPaneWnd(NULL),rightPaneWnd(NULL)
	{
		SetDefDim(10,80);
	}
	
	
	CVertSplitterCtrlComp::~CVertSplitterCtrlComp(void)
	{
	}
	
	BOOL CVertSplitterCtrlComp::CreateComponent(Component * _Parent)
	{
		Parent=_Parent;
		CVertSplitterCtrl::Create(GetComponentParent()->GetHandle(),GetBoundsRect(),NULL,get_CtrlWindowStyle(),get_CtrlWindowStyleEx());
		_Init();
		return ::IsWindow(m_hWnd);
	}
	
	void CVertSplitterCtrlComp::InitProperty(void)
	{
		ControlComponent<CVertSplitterCtrlComp>::InitProperty();
        DEFINE_CLASS_PROPERTY(LeftPane,ComponentName,CVertSplitterCtrlComp,(LPCSTR)leftPane)
        DEFINE_CLASS_PROPERTY(RightPane,ComponentName,CVertSplitterCtrlComp,(LPCSTR)rightPane)

	}
	
    void CVertSplitterCtrlComp::set_LeftPane(CString val)
    {
        if(CheckPaneName(val)==TRUE)
        {
            leftPaneWnd=Find(val);

            if(leftPaneWnd!=NULL)
                leftPane=val;
            else
                leftPane=CComponentListEdit::GetNoneStr();

            if(leftPaneWnd!=NULL && rightPaneWnd!=NULL)
            {
                SetSplitterPanes(leftPaneWnd->GetHandle(),rightPaneWnd->GetHandle());
            }
            SetModified();
        }
    }
    
    CString CVertSplitterCtrlComp::get_LeftPane()
    {
        return leftPane;
    }

    void CVertSplitterCtrlComp::set_RightPane(CString val)
    {
        if(CheckPaneName(val)==TRUE)
        {
            rightPaneWnd=Find(val);
            if(rightPaneWnd!=NULL)
                rightPane=val;
            else
                rightPane=CComponentListEdit::GetNoneStr();

            if(leftPaneWnd!=NULL && rightPaneWnd!=NULL)
            {
                SetSplitterPanes(leftPaneWnd->GetHandle(),rightPaneWnd->GetHandle());
            }
            SetModified();
        }
    }
    
    CString CVertSplitterCtrlComp::get_RightPane()
    {
        return rightPane;
    }
    
    BOOL CVertSplitterCtrlComp::CheckPaneName(CString str)
    {
        if(str==CComponentListEdit::GetNoneStr())
            return TRUE;

        if(str==GetParentForm()->get_Name())
            return FALSE;

        if(str==Parent->get_Name())
            return FALSE;

        if(str==leftPane)
            return FALSE;

        if(str==rightPane)
            return FALSE;

        return TRUE;
    }

};
#endif
