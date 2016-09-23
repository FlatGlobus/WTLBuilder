// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "OutputWindow.h"
#include "_util.h"
#include "cscripteditor.h"

#define FIRST_ROW_WIDTH 20
//////////////////////////////////////////////////////////////////////////
const UINT COutputWindow::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
	IDC_LISTVIEW,
	IDC_COUTPUTWINDOW_PANEL3,
//}}WTLBUILDER_CTRLTOCLIP
    0
};
//////////////////////////////////////////////////////////////////////////
COutputWindow::COutputWindow(void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
    RegisterEvent(evOutput,this,&COutputWindow::OutputStr);
    RegisterEvent(evScriptError,this,&COutputWindow::OutputScriptError);
	RegisterEvent(evClearOutput, this, &COutputWindow::ClearList);
}

COutputWindow::~COutputWindow(void)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
    UnRegisterEvent(this);
}

BOOL COutputWindow::PreTranslateMessage(MSG* pMsg)
{
    m_toolTip.RelayEvent(pMsg);
    return thisClass::PreTranslateMessage(pMsg);
}

LRESULT COutputWindow::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_toolTip.Create(m_hWnd);

    //{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(805,144);
	SetWindowText(_T("Output"));

	m_listviewctrl.Create(m_hWnd,CRect(0,26,805,146),NULL,WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_TABSTOP|LVS_REPORT|LVS_SINGLESEL|LVS_NOLABELWRAP|LVS_ALIGNTOP|LVS_NOCOLUMNHEADER|LVS_NOSORTHEADER,0,IDC_LISTVIEW);
	m_listviewctrl.SetFont((HFONT)m_formFont);
	m_listviewctrl.SetExtendedListViewStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP,0);

	m_panel3.Create(m_hWnd,CRect(0,0,805,26),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,WS_EX_CONTROLPARENT,IDC_COUTPUTWINDOW_PANEL3);
	m_panel3.SetFont((HFONT)m_formFont);
	m_panel3.SetInnerBorder(0);
	m_panel3.SetOuterBorder(0);
	m_panel3.SetEdgeType(BF_RECT);
	m_panel3.SetBkColor(RGB(0xF0,0xF0,0xF0));
	m_panel3.SetTextColor(RGB(0x00,0x00,0x00));
	m_panel3.SetHorizTextAlign(DT_CENTER);
	m_panel3.SetVertTextAlign(DT_VCENTER);
	m_panel3.SetSingleLine(true);

	m_clear_list.Create(m_panel3,CRect(0,0,20,20),_T(""),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_CLEAR_LIST);
	m_clear_list.SetFont((HFONT)m_formFont);
	m_clear_list.SetFlat(true);
	m_clear_list.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_clear_list.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
	m_clear_list.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));
	m_clear_list.SetIcon(IDI_CLEAR_ERR,IDI_CLEAR_ERR);

//}}WTLBUILDER_MEMBER_CREATION

    //{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

    //{{WTLBUILDER_TABSTOP
	m_clear_list.SetWindowPos(m_listviewctrl,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
//}}WTLBUILDER_TABSTOP

    imageList.Create(16,16,ILC_COLOR8,0,0);
    CRect rc;
    m_listviewctrl.GetClientRect(&rc);
    m_listviewctrl.InsertColumn(0,_T(""),LVCFMT_LEFT,rc.Width()/*FIRST_ROW_WIDTH*/,-1);
    //m_listviewctrl.InsertColumn(1,_T(""),LVCFMT_LEFT,rc.Width()-FIRST_ROW_WIDTH);
    m_listviewctrl.SetImageList(imageList,LVSIL_SMALL);
    imageList.AddIcon(AtlLoadIcon(IDI_INFO_MSG));
    imageList.AddIcon(AtlLoadIcon(IDI_WARN_MSG));
    imageList.AddIcon(AtlLoadIcon(IDI_ERROR_MSG));
    InitLayout();
    return 0;
}

void COutputWindow::DefineLayout()
{
    //{{WTLBUILDER_ATTACH_CONTROLS
	AttachForm(m_listviewctrl,ATTACH_LEFT);
	AttachWidget(m_listviewctrl,ATTACH_TOP,m_panel3);
	AttachForm(m_listviewctrl,ATTACH_RIGHT);
	AttachForm(m_listviewctrl,ATTACH_BOTTOM);
	AttachForm(m_panel3,ATTACH_LEFT);
	AttachForm(m_panel3,ATTACH_TOP);
	AttachForm(m_panel3,ATTACH_RIGHT);
//}}WTLBUILDER_ATTACH_CONTROLS
}

void COutputWindow::InitLayout()
{
    //{{WTLBUILDER_INITLAYOUT
	_minClientSize.cx = 805;
	_minClientSize.cy = 144;
	_prevClientSize = _minClientSize;

	_minWindowSize.cx = 821;
	_minWindowSize.cy = 182;

	SetNPositions(1);
	ShowHandle(false);
	DefineLayout();
//}}WTLBUILDER_INITLAYOUT
    //SetScrollSize(_minClientSize);
}

void COutputWindow::GetDialogRect(LPRECT r)
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

void COutputWindow::GetOffset(LPPOINT offset)
{
    *offset = m_ptOffset;
}

void COutputWindow::DoPaint(CDCHandle /*dc*/)
{

}

void __stdcall COutputWindow::Show(void)
{
    if(IsWindow())
        ShowWindow(SW_SHOW);
}

void __stdcall COutputWindow::Hide(void)
{
    if(IsWindow())
        ShowWindow(SW_HIDE);
}

void __stdcall COutputWindow::Clear(void)
{
    for(;m_listviewctrl.GetItemCount();)
    {
        CScriptError * se=(CScriptError *)m_listviewctrl.GetItemData(0);
        if(se!=NULL)
            delete se;
        m_listviewctrl.DeleteItem(0);
    }
    //m_listviewctrl.
}

HWND COutputWindow::Create(HWND Parent)
{
    CRect rc;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc , 0);
    int desiredWidth = rc.Width()-200;

    rc.left=rc.Width()/2-desiredWidth/2;
    rc.right=rc.left+desiredWidth;
    rc.top=rc.bottom-300;

    thisClass::Create(Parent,rc);
    return m_hWnd;
}

//called from script
void __stdcall COutputWindow::put_Info(BSTR strText)
{
    USES_CONVERSION;
    LPCTSTR lpText = OLE2CT(strText);
    //m_listviewctrl.AddItem(m_listviewctrl.GetItemCount(),0,lpText,0);
	OutputStr(InfoMsg, lpText);
}

void __stdcall COutputWindow::put_Warn(BSTR strText)
{
	USES_CONVERSION;
	LPCTSTR lpText = OLE2CT(strText);
	//m_listviewctrl.AddItem(m_listviewctrl.GetItemCount(), 0, lpText, 0);
	OutputStr(WarnMsg, lpText);
}

void __stdcall COutputWindow::put_Err(BSTR strText)
{
	USES_CONVERSION;
	LPCTSTR lpText = OLE2CT(strText);
	//m_listviewctrl.AddItem(m_listviewctrl.GetItemCount(), 0, lpText, 0);
	OutputStr(ErrorMsg, lpText);
}


//called from program
void COutputWindow::OutputStr(int msgType,LPCTSTR msg)
{
    m_listviewctrl.AddItem(m_listviewctrl.GetItemCount(),0,msg,msgType);
	Show();
}

LRESULT COutputWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    bHandled = TRUE;
    return 0;
}

LRESULT COutputWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    ShowWindow(SW_HIDE);
    bHandled = TRUE;
    return 0;
}

void COutputWindow::OutputScriptError(CScriptError *se)
{
    CString errStr = MakeString("Script error: function name %s line %u  %s %s", (LPCTSTR)se->GetFunc(), se->GetLine(), (LPCTSTR)se->GetError(), (LPCTSTR)se->GetDescr());
    
    int idx = m_listviewctrl.AddItem(m_listviewctrl.GetItemCount(),0,errStr,ErrorMsg);
    if(idx != -1)
        m_listviewctrl.SetItemData(idx,(DWORD_PTR)se);

	Show();
}

LRESULT COutputWindow::OnDblClick(int,LPNMHDR pnmh, BOOL&)
{
    int idx=m_listviewctrl.GetSelectedIndex();
    if(idx > -1)
    {
        CScriptError *se = (CScriptError *)m_listviewctrl.GetItemData(idx);
        if(se!=NULL && se->GetFile().IsEmpty()==FALSE)
        {
            CScriptEditor * editor = new CScriptEditor();
            editor->Create(GetParent(),se);
        }
    }
	
    return 0;
}

LRESULT COutputWindow::OnClearList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_listviewctrl.DeleteAllItems();
	return 0;
}

void COutputWindow::ClearList()
{
	m_listviewctrl.DeleteAllItems();
}