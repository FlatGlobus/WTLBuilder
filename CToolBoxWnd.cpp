// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <LayoutMgr.h>
#include "resource.h"
#include "SDK\Property\Component.h"
#include "CToolBoxWnd.h"
//////////////////////////////////////////////////////////////////////////
const UINT CToolBoxWnd::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
	IDC_PANELHOST,
	IDC_TABCTRL,
	IDC_COMPONENTS,
	IDC_PROPERTYLIST,
	IDC_TOOLBAR_PANEL,
	IDC_FORMLIST,
//}}WTLBUILDER_CTRLTOCLIP
		0
};
//////////////////////////////////////////////////////////////////////////
CToolBoxWnd::CToolBoxWnd(void):m_propertylist(NULL),activeForm(NULL)
{
	RegisterEvent(evSetActiveForm,this,&CToolBoxWnd::SetActiveForm);
	RegisterEvent(evCloseAllForms,this,&CToolBoxWnd::CloseAllForms,128);
	RegisterEvent(evCloseForm,this,&CToolBoxWnd::CloseForm,128);
	RegisterEvent(evAddForm,this,&CToolBoxWnd::AddForm);
	
}

CToolBoxWnd::~CToolBoxWnd(void)
{
	UnRegisterEvent(this);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
}

BOOL CToolBoxWnd::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_MOUSEWHEEL)
    {
        if(m_panelhost.GetCurrent()==0)
            m_propertylist->SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
        else
            m_formList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
    }

	m_toolTip.RelayEvent(pMsg);
	return thisClass::PreTranslateMessage(pMsg);
}

HWND CToolBoxWnd::Create(HWND Parent)
{

	CRect screen;
	HWND desktopWnd = GetDesktopWindow();
	::GetWindowRect(desktopWnd, &screen);

	CRect mainRc,rc;
	::GetWindowRect(Parent,&mainRc);
    rc.left=0;
	rc.top=mainRc.bottom;
	rc.right=max(300,mainRc.Width()/6);
	
//	rc.bottom=mainRc.top+(screen.Height()/10)*9;
	rc.bottom = screen.Height() - mainRc.Height();
	thisClass::Create(Parent,rc);
	if(::IsWindow(m_hWnd))
		ShowWindow(SW_SHOW);
	
	return m_hWnd;
}


LRESULT CToolBoxWnd::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(233,472);

	m_panelhost.Create(m_hWnd,CRect(0,21,233,472),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,0,IDC_PANELHOST);
	m_panelhost.SetFont((HFONT)m_formFont);
	m_panelhost.SetInnerBorder(0);
	m_panelhost.SetOuterBorder(0);
	m_panelhost.SetEdgeType(BF_RECT);
	m_panelhost.SetBkColor(GetSysColor(COLOR_BTNFACE));

	m_properties.Create(m_panelhost,CRect(0,0,233,451),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CTOOLBOXWND_PROPERTIES);
	m_properties.SetFont((HFONT)m_formFont);
	m_properties.SetInnerBorder(0);
	m_properties.SetOuterBorder(0);
	m_properties.SetEdgeType(BF_RECT);
	m_properties.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_properties.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_properties.SetHorizTextAlign(DT_CENTER);
	m_properties.SetVertTextAlign(DT_VCENTER);
	m_properties.SetSingleLine(true);
	m_properties.SetCaption(_TEXT(""));
	m_panelhost.AddPanel(&m_properties);

	m_forms.Create(m_panelhost,CRect(0,0,233,451),NULL,WS_CHILD|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_CTOOLBOXWND_FORMS);
	m_forms.SetFont((HFONT)m_formFont);
	m_forms.SetInnerBorder(0);
	m_forms.SetOuterBorder(0);
	m_forms.SetEdgeType(BF_RECT);
	m_forms.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_forms.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_forms.SetHorizTextAlign(DT_CENTER);
	m_forms.SetVertTextAlign(DT_VCENTER);
	m_forms.SetSingleLine(true);
	m_forms.SetCaption(_TEXT(""));
	m_panelhost.AddPanel(&m_forms);

	m_tabctrl.Create(m_hWnd,CRect(0,0,233,21),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP|TCS_SINGLELINE|TCS_TABS|TCS_RIGHTJUSTIFY,0,IDC_TABCTRL);
	TCITEM m_tabctrlItem = { 0 };
	m_tabctrlItem.mask = TCIF_TEXT|TCIF_IMAGE;
	m_tabctrlItem.pszText = _TEXT("Properties");
	m_tabctrlItem.cchTextMax = lstrlen(m_tabctrlItem.pszText);
	m_tabctrlItem.iImage = 0;
	
	m_tabctrl.InsertItem(0, &m_tabctrlItem);
	m_tabctrlItem.pszText = _TEXT("Forms");
	m_tabctrlItem.cchTextMax = lstrlen(m_tabctrlItem.pszText);
	m_tabctrlItem.iImage = -1;
	m_tabctrl.InsertItem(1, &m_tabctrlItem);
	m_tabctrl.SetCurSel(0);
	m_tabctrl.SetFont((HFONT)m_formFont);

	m_components.Create(m_properties,CRect(0,0,233,217),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL|CBS_HASSTRINGS,0,IDC_COMPONENTS);
	m_components.SetFont((HFONT)m_formFont);
	m_components.LimitText(0);
	m_components.SetItemHeight(-1,15);
	m_components.SetItemHeight(0,13);
	m_components.SetDroppedWidth(234);
	m_components.SetHorizontalExtent(40);

	m_propertylist=CreatePropertyList(m_properties,CRect(0,21,233,450),IDC_PROPERTYLIST);

	m_toolbarpanel.Create(m_forms,CRect(0,0,233,35),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT,IDC_TOOLBAR_PANEL);
	m_toolbarpanel.SetFont((HFONT)m_formFont);
	m_toolbarpanel.SetInnerBorder(0);
	m_toolbarpanel.SetOuterBorder(0);
	m_toolbarpanel.SetEdgeType(BF_RECT);
	m_toolbarpanel.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_toolbarpanel.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_toolbarpanel.SetHorizTextAlign(DT_CENTER);
	m_toolbarpanel.SetVertTextAlign(DT_VCENTER);
	m_toolbarpanel.SetSingleLine(false);
	m_toolbarpanel.SetCaption(_TEXT(""));

	m_show.Create(m_toolbarpanel,CRect(4,4,31,31),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_SHOW);
	m_show.SetFont((HFONT)m_formFont);
	m_show.SetFlat(true);
	m_show.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_show.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_show.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));
	m_show.SetTooltipText(_TEXT("Show Form"));
	m_show.SetIcon(IDI_SHOW_FORM,IDI_SHOW_FORM);

	m_close.Create(m_toolbarpanel,CRect(34,4,61,31),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_CLOSE);
	m_close.SetFont((HFONT)m_formFont);
	m_close.SetFlat(true);
	m_close.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_close.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_close.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));
	m_close.SetTooltipText(_TEXT("Close Form"));
	m_close.SetIcon(IDI_CLOSE_FORM,IDI_CLOSE_FORM);

	m_formList.Create(m_forms,CRect(0,36,233,451),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|LBS_NOINTEGRALHEIGHT,0,IDC_FORMLIST);
	m_formList.SetFont((HFONT)m_formFont);
	m_formList.SetItemHeight(0,13);
	m_formList.SetHorizontalExtent(40);

	m_sort.Create(m_toolbarpanel,CRect(203,4,230,31),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_SORT);
	m_sort.SetFont((HFONT)m_formFont);
	m_sort.SetFlat(true);
	m_sort.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_sort.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_sort.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));
	m_sort.SetTooltipText(_TEXT("Sort Form list"));
	m_sort.SetIcon(IDI_SORT_FORM,IDI_SORT_FORM);
	m_sort.EnablePressedState(true);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
	m_panelhost.SetCurrent(&m_properties);
//}}WTLBUILDER_POST_CREATION

	m_tabctrl.SetCurSel(0);
	m_images.Create(16,16,ILC_COLOR8|ILC_MASK,0,1);
    m_images.AddIcon(AtlLoadIcon(IDI_PROP_ICON));
    	
	m_tabctrl.SetImageList(m_images);	
	
	InitLayout();
//////////////////////////////////////////////////////////////////////////

	CRect screen;
	HWND desktopWnd = GetDesktopWindow();
	::GetWindowRect(desktopWnd, &screen);

	CRect mainRc;
	::GetWindowRect(GetParent(), &mainRc);
	int width = 250;
	int height = mainRc.top + (screen.Height() / 10) * 7;
	ResizeClient(width, height);

	return 0;
}

void CToolBoxWnd::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
	AttachForm(m_panelhost,ATTACH_LEFT);
	AttachForm(m_panelhost,ATTACH_TOP);
	AttachForm(m_panelhost,ATTACH_RIGHT);
	AttachForm(m_panelhost,ATTACH_BOTTOM);
	AttachForm(m_tabctrl,ATTACH_LEFT);
	AttachForm(m_tabctrl,ATTACH_RIGHT);
	AttachForm(m_components,ATTACH_LEFT);
	AttachForm(m_components,ATTACH_RIGHT);
	AttachForm(*m_propertylist,ATTACH_LEFT);
	AttachForm(*m_propertylist,ATTACH_TOP);
	AttachForm(*m_propertylist,ATTACH_RIGHT);
	AttachForm(*m_propertylist,ATTACH_BOTTOM);
	AttachForm(m_toolbarpanel,ATTACH_LEFT);
	AttachForm(m_toolbarpanel,ATTACH_TOP);
	AttachForm(m_formList,ATTACH_LEFT);
	AttachForm(m_formList,ATTACH_TOP);
	AttachForm(m_formList,ATTACH_RIGHT);
	AttachForm(m_formList,ATTACH_BOTTOM);
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CToolBoxWnd::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
	_minClientSize.cx = 233;
	_minClientSize.cy = 472;
	_prevClientSize = _minClientSize;

	_minWindowSize.cx = 241;
	_minWindowSize.cy = 498;

	SetNPositions(1);
	DefineLayout();
//}}WTLBUILDER_INITLAYOUT
}

void CToolBoxWnd::GetDialogRect(LPRECT r)
{
	GetClientRect(r);	
	if (r->right < m_sizeAll.cx)
	{
		r->right = m_sizeAll.cx;
	}
	if (r->bottom < m_sizeAll.cy)
	{
		r->bottom = m_sizeAll.cy;
	}
}

void CToolBoxWnd::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void CToolBoxWnd::DoPaint(CDCHandle /*dc*/)
{

}

LRESULT CToolBoxWnd::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	return 0;
}

LRESULT CToolBoxWnd::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    ShowWindow(SW_HIDE);
    bHandled = TRUE;
    return 0;
}

void CToolBoxWnd::SetActiveForm(Component *form)
{
	if (form == NULL)
	{
		SetWindowText(_T(""));
		return;
	}

	activeForm = form;
	if (::IsWindow(m_components.m_hWnd) == FALSE)
		return;

	if (::IsWindow(m_formList.m_hWnd) == FALSE)
		return;

	m_components.ResetContent();
	int idx = m_components.AddString((LPCTSTR)activeForm->get_Name());
	m_components.SetItemDataPtr(idx, activeForm);
	m_components.SetCurSel(idx);
	SetWindowText(activeForm->GetClassName());

	if ((idx = FindForm(activeForm)) == -1)
	{
		idx = m_formList.AddString((LPCTSTR)activeForm->get_Name());
		m_formList.SetItemDataPtr(idx, activeForm);
	}

	m_formList.SetCurSel(FindForm(activeForm));

	for (int i = 0; i < activeForm->GetComponents()->GetCount(); i++)
	{
		idx = m_components.AddString((LPCTSTR)activeForm->GetComponents()->GetAt(i)->get_Name());
		m_components.SetItemDataPtr(idx, activeForm->GetComponents()->GetAt(i));
		if (activeForm->GetComponents()->GetAt(i)->FirstSelected)
		{
			m_components.SetCurSel(idx);
			SetWindowText(activeForm->GetComponents()->GetAt(i)->GetClassName());
		}
	}
}

LRESULT CToolBoxWnd::OnComponentChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    int idx=m_components.GetCurSel();
    if(idx!=-1)
    {
        activeForm->GetComponents()->UnselectAll();
        Component * temp=(Component *)m_components.GetItemDataPtr(idx);
        if(activeForm!=temp)
        {
            temp->Selected=TRUE;
            temp->FirstSelected=TRUE;
            activeForm->GetComponents()->Invalidate();
        }
        temp->ShowProperties();
        SetWindowText(temp->GetClassName());
        //::BringWindowToTop((HWND)activeForm->GetHandle());
    }
    else
        SetWindowText(_T(""));
    return 0;
}

LRESULT CToolBoxWnd::OnFormChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CToolBoxWnd::OnTabSelect(LPNMHDR pnmh)
{
	long currentPanel=m_tabctrl.GetCurSel();
	m_panelhost.SetCurrent(currentPanel);
	return 0;
}

void CToolBoxWnd::AddForm(Component *form)
{
    if(FindForm(form)==-1)
    {
        int idx=m_formList.AddString((LPCTSTR)form->get_Name());
        m_formList.SetItemDataPtr(idx,form);
		if(m_formList.GetCount() == 1 )
			m_formList.SetCurSel(0);
    }
}

void CToolBoxWnd::CloseAllForms()
{
    if(IsWindow()==FALSE)
        return;

	if(::IsWindow(m_formList.m_hWnd))
		m_formList.ResetContent();
	if(::IsWindow(m_components.m_hWnd))
		m_components.ResetContent();
	activeForm=NULL;
    SetWindowText(_T(""));
}

void CToolBoxWnd::CloseForm(Component * form,BOOL *remove)
{
    if(*remove==FALSE)
        return;

    if(::IsWindow(m_formList.m_hWnd))
    {
        int idx=FindForm(form);
        if(idx!=-1)
            m_formList.DeleteString(idx);
        m_formList.SetCurSel(-1);

    }

    if(activeForm==form)
        m_components.ResetContent();

    activeForm=NULL;
    SetWindowText(_T(""));
}

LRESULT CToolBoxWnd::OnCloseForm(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_formList.GetCurSel();
	if(idx!=-1)
	{
        BOOL remove=TRUE;
		SendEvent(evCloseForm,m_formList.GetItemDataPtr(idx),&remove);
        if(remove==TRUE)
        {
            m_components.ResetContent();
		    m_formList.DeleteString(idx);
            SetWindowText(_T(""));
        }
	}
	
	return 0;
}

LRESULT CToolBoxWnd::OnShowForm(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int idx=m_formList.GetCurSel();
	if(idx!=-1)
	{
		activeForm=(Component *)m_formList.GetItemDataPtr(idx);
		::ShowWindow((HWND)activeForm->GetHandle(), SW_SHOWNORMAL);
		SendEvent(evSetActiveForm,activeForm);
	}
	return 0;
}

LRESULT CToolBoxWnd::OnFormsDblClk(LPNMHDR)
{
	return 0;
}

LRESULT CToolBoxWnd::OnSort(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_sort.SetPressed(!m_sort.GetPressed());
	m_formList.ModifyStyle(m_sort.GetPressed() == false ? LBS_SORT: 0,m_sort.GetPressed()? LBS_SORT: 0);
	return 0;
}

int CToolBoxWnd::FindForm(Component * form)
{
	for(int i=0; i < m_formList.GetCount(); i++)
	{
		if(form==(Component *)m_formList.GetItemDataPtr(i))
			return i;
	}
	return -1;
}