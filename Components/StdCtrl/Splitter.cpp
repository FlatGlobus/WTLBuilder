// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "atlsplit.h"
#include "Splitter.h"
#include "resource.h"
#include "PropertyListEdit.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
typedef long VertSplitterPane;
typedef long HorSplitterPane;
static void RegisterSplitterStyles();
namespace StdCtrl
{
	REGISTER_COMPONENT(CSplitterWindow,StdCtl,IDB_SPLITTERWINDOW)

	CSplitterWindow::CSplitterWindow(LPTSTR _name):ControlComponent<CSplitterWindow>(_name),
    leftPaneParent(NULL),rightPaneParent(NULL),leftPane(CComponentListEdit::GetNoneStr()),rightPane(CComponentListEdit::GetNoneStr())
	{
        RegisterSplitterStyles();
		enableTabIndex=FALSE;
	}

    CSplitterWindow::~CSplitterWindow(void)
	{
	}

	BOOL CSplitterWindow::CreateComponent(Component * _Parent)
	{
		ADD_WIN_STYLE(WS_CHILD | WS_VISIBLE)
        SetComponentParent(_Parent);
        baseClass::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
                
		return ::IsWindow(m_hWnd);
	}

    void CSplitterWindow::SetBoundsRect(CRect rc)
    {
        ControlComponent<StdCtrl::CSplitterWindow>::SetBoundsRect(rc);
        if(::IsWindow(m_hWnd))
        {
            SetSplitterRect(NULL);
            UpdateSplitterLayout();
            if(get_Pos()==4)
                SetSplitterPos(-1);
        }
    }

	void CSplitterWindow::InitProperty(void)
	{
        ControlComponent<StdCtrl::CSplitterWindow>::InitProperty();
        DEFINE_PROPERTY(LeftPane,ComponentName,CSplitterWindow,(LPCTSTR)leftPane)
        DEFINE_PROPERTY(RightPane,ComponentName,CSplitterWindow,(LPCTSTR)rightPane)
        DEFINE_PROPERTY(Pos,long,CSplitterWindow,-1)
        BEGIN_SUB_PROPERTY(_T("ExtStyles"),CSplitterWindow)
            DEFINE_SUB_PROPERTY(Proportional,BOOL,CSplitterWindow,TRUE)
            DEFINE_SUB_PROPERTY(NonInteractive,BOOL,CSplitterWindow,FALSE)
            DEFINE_SUB_PROPERTY(RightAligned,BOOL,CSplitterWindow,FALSE)
        END_SUB_PROPERTY
        DEFINE_PROPERTY(SinglePaneMode,VertSplitterPane,CSplitterWindow,SPLIT_PANE_NONE)
        DEFINE_PROPERTY(ActivePane,VertSplitterPane,CSplitterWindow,SPLIT_PANE_NONE)
	}
    
    void CSplitterWindow::set_LeftPane(CString val)
    {
        if(val!=leftPane && CheckPaneName(val)==TRUE)
        {
            Component * leftPaneWnd;
            if((leftPaneWnd=Find(leftPane))!=NULL)
            {
                leftPaneWnd->SetComponentParent(GetParentForm());
                CPoint pt(get_Left(),get_Top());
//                ComponentToDesigner(pt);
//                leftPaneWnd->DesignerToComponent(pt);
                leftPaneWnd->set_Left(pt.x);
                leftPaneWnd->set_Top(pt.y);
                leftPaneWnd->Changed.Reset();
            }

            leftPaneWnd=Find(val);

            if(leftPaneWnd!=NULL)
            {
                if(leftPaneWnd->GetComponentParent()!=this)
                {    
                    GetComponents()->MoveAfter(leftPaneWnd,this);
                    leftPaneWnd->SetComponentParent(this);
                }
                leftPaneWnd->Changed.SetObject(this);
                leftPaneWnd->Changed.SetMethod(&CSplitterWindow::LeftPaneChanged);
                leftPane=val;
            }
            else
                leftPane=CComponentListEdit::GetNoneStr();
            
            SetSplitterPane(SPLIT_PANE_LEFT,leftPaneWnd!=NULL && ::IsWindow((HWND)leftPaneWnd->GetHandle())? (HWND)leftPaneWnd->GetHandle() : NULL);
            SetModified();
        }
    }
    
    CString CSplitterWindow::get_LeftPane()
    {
        CComponentListEdit::SetComponentKind(_T(""));
        return leftPane;
    }

    void CSplitterWindow::LeftPaneChanged(Component* comp)
    {
        if(comp->GetState(csDeleting) == TRUE && GetState(csDeleting) == FALSE)
        {
            leftPane=CComponentListEdit::GetNoneStr();
            comp->Changed.Reset();
            SetSplitterPane(SPLIT_PANE_LEFT,NULL);
        }
        else
            leftPane=comp->get_Name();
    }

    void CSplitterWindow::set_RightPane(CString val)
    {
        if(val!=rightPane && CheckPaneName(val)==TRUE)
        {
            Component * rightPaneWnd;
            if((rightPaneWnd=Find(rightPane))!=NULL)
            {
                rightPaneWnd->SetComponentParent(GetParentForm());
                CRect rc;
                GetSplitterPaneRect(SPLIT_PANE_RIGHT,&rc);
                rc.left+=get_Left();
                rc.top+=get_Top();
//                ComponentToDesigner(rc);
//                rightPaneWnd->DesignerToComponent(rc);
                rightPaneWnd->set_Left(rc.left);
                rightPaneWnd->set_Top(rc.top);
                rightPaneWnd->Changed.Reset();
            }
            
            rightPaneWnd=Find(val);
            
            if(rightPaneWnd!=NULL)
            {
                if(rightPaneWnd->GetComponentParent()!=this)
                {   
                    GetComponents()->MoveAfter(rightPaneWnd,this);
                    rightPaneWnd->SetComponentParent(this);
                }
                rightPaneWnd->Changed.SetObject(this);
                rightPaneWnd->Changed.SetMethod(&CSplitterWindow::RightPaneChanged);
                rightPane=val;
            }
            else
                rightPane=CComponentListEdit::GetNoneStr();
            
            SetSplitterPane(SPLIT_PANE_RIGHT,rightPaneWnd!=NULL ? (HWND)rightPaneWnd->GetHandle() : NULL);
            SetModified();
        }
    }
    
    CString CSplitterWindow::get_RightPane()
    {
        CComponentListEdit::SetComponentKind(_T(""));
        return rightPane;
    }

    void CSplitterWindow::RightPaneChanged(Component* comp)
    {
        if(comp->GetState(csDeleting))
        {
            rightPane=CComponentListEdit::GetNoneStr();
            comp->Changed.Reset();
            SetSplitterPane(SPLIT_PANE_RIGHT,NULL);
        }
        else
            rightPane=comp->get_Name();
    }

    void CSplitterWindow::set_Proportional(BOOL val)
    {
        DWORD style=GetSplitterExtendedStyle();
        style = val == TRUE ? (style | SPLIT_PROPORTIONAL): (style & ~SPLIT_PROPORTIONAL);        
        SetSplitterExtendedStyle(style,0);
        UpdateSplitterLayout();
        SetModified();
    }
    
    BOOL CSplitterWindow::get_Proportional()
    {
        return (GetSplitterExtendedStyle() & SPLIT_PROPORTIONAL)==SPLIT_PROPORTIONAL;
    }

    void CSplitterWindow::set_NonInteractive(BOOL val)
    {
        DWORD style=GetSplitterExtendedStyle();
        style = val == TRUE ? (style | SPLIT_NONINTERACTIVE): (style & ~SPLIT_NONINTERACTIVE);        
        SetSplitterExtendedStyle(style,0);
        UpdateSplitterLayout();
        SetModified();
    }
    
    BOOL CSplitterWindow::get_NonInteractive()
    {
        return (GetSplitterExtendedStyle() & SPLIT_NONINTERACTIVE)==SPLIT_NONINTERACTIVE;
    }

    void CSplitterWindow::set_RightAligned(BOOL val)
    {
        DWORD style=GetSplitterExtendedStyle();
        style = val == TRUE ? (style | SPLIT_RIGHTALIGNED): (style & ~SPLIT_RIGHTALIGNED);
        SetSplitterExtendedStyle(style,0);
        UpdateSplitterLayout();
        SetModified();
    }
    
    BOOL CSplitterWindow::get_RightAligned()
    {
        return (GetSplitterExtendedStyle() & SPLIT_RIGHTALIGNED)==SPLIT_RIGHTALIGNED;
    }

    void CSplitterWindow::set_Pos(long val)
    {
        SetSplitterPos(val);
        SetModified();
    }
    
    long CSplitterWindow::get_Pos()
    {
      return GetSplitterPos();
    }

    void CSplitterWindow::set_SinglePaneMode(long val)
    {
        SetSinglePaneMode(val);
        SetModified();
    }

    long CSplitterWindow::get_SinglePaneMode()
    {
        return GetSinglePaneMode();
    }

    void CSplitterWindow::set_ActivePane(long val)
    {
        activePane=val;
        SetModified();
    }
    
    long CSplitterWindow::get_ActivePane()
    {
        return activePane;
    }

    BOOL CSplitterWindow::CheckPaneName(CString str)
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
//////////////////////////////////////////////////////////////////////////
	REGISTER_COMPONENT(CHorSplitterWindow,StdCtl,IDB_HORSPLITTERWINDOW)

	CHorSplitterWindow::CHorSplitterWindow(LPTSTR _name):ControlComponent<CHorSplitterWindow>(_name),
    topPaneParent(NULL),bottomPaneParent(NULL),topPane(CComponentListEdit::GetNoneStr()),bottomPane(CComponentListEdit::GetNoneStr())
	{
        RegisterSplitterStyles();
	}

    CHorSplitterWindow::~CHorSplitterWindow(void)
	{
	}

	BOOL CHorSplitterWindow::CreateComponent(Component * _Parent)
	{
		ADD_WIN_STYLE(WS_CHILD | WS_VISIBLE)
        SetComponentParent(_Parent);
        baseClass::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
        
		return ::IsWindow(m_hWnd);
	}

    void CHorSplitterWindow::SetBoundsRect(CRect rc)
    {
        ControlComponent<StdCtrl::CHorSplitterWindow>::SetBoundsRect(rc);
        if(::IsWindow(m_hWnd))
        {
            SetSplitterRect(NULL);
            UpdateSplitterLayout();
            if(get_Pos()==4)
                SetSplitterPos(-1);
        }
    }

	void CHorSplitterWindow::InitProperty(void)
	{
        ControlComponent<StdCtrl::CHorSplitterWindow>::InitProperty();
        DEFINE_PROPERTY(TopPane,ComponentName,CHorSplitterWindow,(LPCTSTR)topPane)
        DEFINE_PROPERTY(BottomPane,ComponentName,CHorSplitterWindow,(LPCTSTR)bottomPane)
        DEFINE_PROPERTY(Pos,long,CHorSplitterWindow,-1)
        BEGIN_SUB_PROPERTY(_T("ExtStyles"),CHorSplitterWindow)
            DEFINE_SUB_PROPERTY(Proportional,BOOL,CHorSplitterWindow,TRUE)
            DEFINE_SUB_PROPERTY(NonInteractive,BOOL,CHorSplitterWindow,FALSE)
            DEFINE_SUB_PROPERTY(BottomAligned,BOOL,CHorSplitterWindow,FALSE)
        END_SUB_PROPERTY
        DEFINE_PROPERTY(SinglePaneMode,HorSplitterPane,CHorSplitterWindow,SPLIT_PANE_NONE)
        DEFINE_PROPERTY(ActivePane,HorSplitterPane,CHorSplitterWindow,SPLIT_PANE_NONE)
	}

    void CHorSplitterWindow::set_TopPane(CString val)
    {
        if(val!=topPane && CheckPaneName(val)==TRUE)
        {
            Component * topPaneWnd;
            if((topPaneWnd=Find(topPane))!=NULL)
            {
                topPaneWnd->SetComponentParent(GetParentForm());
                CPoint pt(get_Left(),get_Top());
//                ComponentToDesigner(pt);
//                topPaneWnd->DesignerToComponent(pt);
                topPaneWnd->set_Left(pt.x);
                topPaneWnd->set_Top(pt.y);
                topPaneWnd->Changed.Reset();
            }

            topPaneWnd=Find(val);

            if(topPaneWnd!=NULL)
            {
                if(topPaneWnd->GetComponentParent()!=this)
                {    
                    GetComponents()->MoveAfter(topPaneWnd,this);
                    topPaneWnd->SetComponentParent(this);
                }
                topPane=val;
                topPaneWnd->Changed.SetObject(this);
                topPaneWnd->Changed.SetMethod(&CHorSplitterWindow::TopPaneChanged);
            }
            else
                topPane=CComponentListEdit::GetNoneStr();
            
            SetSplitterPane(SPLIT_PANE_TOP,topPaneWnd!=NULL && ::IsWindow((HWND)topPaneWnd->GetHandle())? (HWND)topPaneWnd->GetHandle() : NULL);
            SetModified();
        }
    }
    
    CString CHorSplitterWindow::get_TopPane()
    {
        CComponentListEdit::SetComponentKind(_T(""));
        return topPane;
    }

    void CHorSplitterWindow::TopPaneChanged(Component* comp)
    {
        if(comp->GetState(csDeleting))
        {
            topPane=CComponentListEdit::GetNoneStr();
            comp->Changed.Reset();
            SetSplitterPane(SPLIT_PANE_TOP,NULL);
        }
        else
            topPane=comp->get_Name();
    }

    void CHorSplitterWindow::set_BottomPane(CString val)
    {
        if(val!=bottomPane && CheckPaneName(val)==TRUE)
        {
            Component * bottomPaneWnd;
            if((bottomPaneWnd=Find(bottomPane))!=NULL)
            {
                bottomPaneWnd->SetComponentParent(GetParentForm());
                CRect rc;
                GetSplitterPaneRect(SPLIT_PANE_BOTTOM,&rc);
                rc.left+=get_Left();
                rc.top+=get_Top();
//                ComponentToDesigner(rc);
//                bottomPaneWnd->DesignerToComponent(rc);
                bottomPaneWnd->set_Left(rc.left);
                bottomPaneWnd->set_Top(rc.top);
                bottomPaneWnd->Changed.Reset();
            }
            
            bottomPaneWnd=Find(val);
            
            if(bottomPaneWnd!=NULL)
            {
                if(bottomPaneWnd->GetComponentParent()!=this)
                {   
                    GetComponents()->MoveAfter(bottomPaneWnd,this);
                    bottomPaneWnd->SetComponentParent(this);
                }
                bottomPane=val;
                bottomPaneWnd->Changed.SetObject(this);
                bottomPaneWnd->Changed.SetMethod(&CHorSplitterWindow::BottomPaneChanged);
            }
            else
                bottomPane=CComponentListEdit::GetNoneStr();
            
            SetSplitterPane(SPLIT_PANE_BOTTOM,bottomPaneWnd!=NULL ? (HWND)bottomPaneWnd->GetHandle() : NULL);
            SetModified();
        }
    }
    
    CString CHorSplitterWindow::get_BottomPane()
    {
        CComponentListEdit::SetComponentKind(_T(""));
        return bottomPane;
    }

    void CHorSplitterWindow::BottomPaneChanged(Component* comp)
    {
        if(comp->GetState(csDeleting))
        {
            bottomPane=CComponentListEdit::GetNoneStr();
            comp->Changed.Reset();
            SetSplitterPane(SPLIT_PANE_BOTTOM,NULL);
        }
        else
            bottomPane=comp->get_Name();
    }

    void CHorSplitterWindow::set_Proportional(BOOL val)
    {
        DWORD style=GetSplitterExtendedStyle();
        style = val == TRUE ? (style | SPLIT_PROPORTIONAL): (style & ~SPLIT_PROPORTIONAL);        
        SetSplitterExtendedStyle(style,0);
        UpdateSplitterLayout();
        SetModified();
    }
    
    BOOL CHorSplitterWindow::get_Proportional()
    {
        return (GetSplitterExtendedStyle() & SPLIT_PROPORTIONAL)==SPLIT_PROPORTIONAL;
    }

    void CHorSplitterWindow::set_NonInteractive(BOOL val)
    {
        DWORD style=GetSplitterExtendedStyle();
        style = val == TRUE ? (style | SPLIT_NONINTERACTIVE): (style & ~SPLIT_NONINTERACTIVE);        
        SetSplitterExtendedStyle(style,0);
        UpdateSplitterLayout();
        SetModified();
    }
    
    BOOL CHorSplitterWindow::get_NonInteractive()
    {
        return (GetSplitterExtendedStyle() & SPLIT_NONINTERACTIVE)==SPLIT_NONINTERACTIVE;
    }

    void CHorSplitterWindow::set_BottomAligned(BOOL val)
    {
        DWORD style=GetSplitterExtendedStyle();
        style = val == TRUE ? (style | SPLIT_BOTTOMALIGNED): (style & ~SPLIT_BOTTOMALIGNED);
        SetSplitterExtendedStyle(style,0);
        UpdateSplitterLayout();
        SetModified();
    }
    
    BOOL CHorSplitterWindow::get_BottomAligned()
    {
        return (GetSplitterExtendedStyle() & SPLIT_BOTTOMALIGNED)==SPLIT_BOTTOMALIGNED;
    }

    void CHorSplitterWindow::set_Pos(long val)
    {
        SetSplitterPos(val);
        SetModified();
    }
    
    long CHorSplitterWindow::get_Pos()
    {
      return GetSplitterPos();
    }

    void CHorSplitterWindow::set_SinglePaneMode(long val)
    {
        SetSinglePaneMode(val);
        SetModified();
    }

    long CHorSplitterWindow::get_SinglePaneMode()
    {
        return GetSinglePaneMode();
    }

    void CHorSplitterWindow::set_ActivePane(long val)
    {
        activePane=val;
        SetModified();
    }
    
    long CHorSplitterWindow::get_ActivePane()
    {
        return activePane;
    }

    BOOL CHorSplitterWindow::CheckPaneName(CString str)
    {
        if(str==CComponentListEdit::GetNoneStr())
            return TRUE;

        if(str==GetParentForm()->get_Name())
            return FALSE;

        if(str==Parent->get_Name())
            return FALSE;

        if(str==topPane)
            return FALSE;

        if(str==bottomPane)
            return FALSE;

        return TRUE;
    }
}
//////////////////////////////////////////////////////////////////////////
BEGIN_LIST_PROPERTY(VertSplitterPane)
    LIST_ITEM_DECORATE(SPLIT_PANE_LEFT,SPLIT_PANE_LEFT,LeftPane)
    LIST_ITEM_DECORATE(SPLIT_PANE_RIGHT,SPLIT_PANE_RIGHT,RightPane)
    LIST_ITEM_DECORATE(SPLIT_PANE_NONE,SPLIT_PANE_NONE,None)
END_LIST_ITEM(VertSplitterPane)

BEGIN_LIST_PROPERTY(HorSplitterPane)
    LIST_ITEM_DECORATE(SPLIT_PANE_TOP,SPLIT_PANE_TOP,TopPane)
    LIST_ITEM_DECORATE(SPLIT_PANE_BOTTOM,SPLIT_PANE_BOTTOM,BottomPane)
    LIST_ITEM_DECORATE(SPLIT_PANE_NONE,SPLIT_PANE_NONE,None)
END_LIST_ITEM(HorSplitterPane)

static void RegisterSplitterStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;
    
    REGISTER_LIST_PROPERTY(VertSplitterPane)
    REGISTER_LIST_PROPERTY(HorSplitterPane)

    IsInited=TRUE;
    
}
