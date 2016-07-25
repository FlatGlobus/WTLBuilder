// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "WTLBuilderView.h"
#include "MainFrm.h"
#include "OptionsDlg.h"
#include "_util.h"

const TCHAR* const WTLBuilderRegKey = _T("Software\\WTLBuilder");

#define FILE_MENU_POSITION 0
#define RECENT_MENU_POSITION 11
BOOL IsPasteEnabled();
//////////////////////////////////////////////////////////////////////////
const UINT CMainFrame::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
    0
};

//////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame(void):project(this),enableUndo(FALSE),userMenuCount(MIN_USER_MENU_ID)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
	RegisterEvent(evAddMenu,this,&CMainFrame::AddMenu);
	RegisterEvent(evSendComponentInfo,this,&CMainFrame::FillToolPanel);
	RegisterEvent(evResetSelectedComponent,this,&CMainFrame::ResetSelectedComponent);
    RegisterEvent(evFormLoaded,this,&CMainFrame::FormSavedLoaded);
    RegisterEvent(evFormSaved,this,&CMainFrame::FormSavedLoaded);
    RegisterEvent(evShowGrid, this,&CMainFrame::SetGridButton); 
    RegisterEvent(evSetGridSizeX, this,&CMainFrame::SetGridWidth); 
    RegisterEvent(evSetGridSizeY, this,&CMainFrame::SetGridHeight); 
    RegisterEvent(evEnableUndo, this,&CMainFrame::EnableUndo);
    RegisterEvent(evOnEditCommand, this,&CMainFrame::OnEditCommand);
	RegisterEvent(evSetActiveForm, this,&CMainFrame::SetActiveForm);
    RegisterEvent(evAddUndo, this,&CMainFrame::SetActiveForm);
    RegisterEvent(evUndo, this,&CMainFrame::SetActiveForm);
	RegisterEvent(evLoadScriptFromFile, this, &CMainFrame::LoadScriptFromFile);
	RegisterEvent(evXYCursor, this, &CMainFrame::XYCursor);
}

CMainFrame::~CMainFrame(void)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION

	UnRegisterEvent(this);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    m_toolTip.RelayEvent(pMsg);
	return baseClass::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    UIEnable(ID_EDIT_CUT,project.Forms->Active!=NULL && 
        project.Forms->Active->GetComponents()->GetSelCount()!=0);

    UIEnable(ID_EDIT_COPY,project.Forms->Active!=NULL && 
        project.Forms->Active->GetComponents()->GetSelCount()!=0);

    UIEnable(ID_EDIT_PASTE,project.Forms->Active && IsPasteEnabled());

    UIEnable(ID_EDIT_SELECT_ALL,project.Forms->Active!=NULL);

    UIEnable(ID_EDIT_CLEAR,project.Forms->Active!=NULL && 
        project.Forms->Active->GetComponents()->GetSelCount()!=0);

    UIEnable(ID_EDIT_UNDO,enableUndo);
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_toolTip.Create(m_hWnd,NULL,NULL,TTS_ALWAYSTIP,WS_EX_TOPMOST);

    //CMenu menu;
    //menu.LoadMenu(IDR_MAINFRAME);
    //SetMenu(menu);
    //UIAddMenuBar(*this);
    m_hAccel = AtlLoadAccelerators(IDR_MAINFRAME);
///
    //{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(774,121);
	SetWindowText(_T("WTLBuilder"));

	m_panel.Create(m_hWnd,CRect(0,0,774,30),NULL,WS_CHILD|WS_VISIBLE,0,IDC_PANEL);
	m_panel.SetFont((HFONT)m_formFont);
	m_panel.SetInnerBorder(BDR_RAISEDINNER);
	m_panel.SetOuterBorder(0);
	m_panel.SetEdgeType(BF_RECT);
	m_panel.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel.SetHorizTextAlign(DT_CENTER);
	m_panel.SetVertTextAlign(DT_VCENTER);
	m_panel.SetSingleLine(true);

	m_panel1.Create(m_hWnd,CRect(0,30,774,60),NULL,WS_CHILD|WS_VISIBLE,0,IDC_PANEL1);
	m_panel1.SetFont((HFONT)m_formFont);
	m_panel1.SetInnerBorder(BDR_RAISEDINNER);
	m_panel1.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel1.SetEdgeType(BF_RECT);
	m_panel1.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel1.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel1.SetHorizTextAlign(DT_CENTER);
	m_panel1.SetVertTextAlign(DT_VCENTER);
	m_panel1.SetSingleLine(true);

	m_toolTab.Create(m_hWnd,CRect(0,60,774,121),IDC_TOOLTAB);
	m_buttonst3.Create(m_panel,CRect(109,6,129,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_ALIGN_LEFT);
	m_buttonst3.SetFont((HFONT)m_formFont);
	m_buttonst3.SetFlat(true);
	m_buttonst3.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst3.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst3.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst3.SetTooltipText(_T("Aligment Left"));
	m_buttonst3.SetIcon(IDI_ALIGN_LEFT,IDI_ALIGN_LEFT);

	m_buttonst4.Create(m_panel,CRect(133,6,153,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_ALIGN_RIGHT);
	m_buttonst4.SetFont((HFONT)m_formFont);
	m_buttonst4.SetFlat(true);
	m_buttonst4.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst4.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst4.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst4.SetTooltipText(_T("Aligment Right"));
	m_buttonst4.SetIcon(IDI_ALIGN_RIGHT,IDI_ALIGN_RIGHT);

	m_buttonst5.Create(m_panel,CRect(158,6,178,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_ALIGN_TOP);
	m_buttonst5.SetFont((HFONT)m_formFont);
	m_buttonst5.SetFlat(true);
	m_buttonst5.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst5.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst5.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst5.SetTooltipText(_T("Aligment Top"));
	m_buttonst5.SetIcon(IDI_ALIGN_TOP,IDI_ALIGN_TOP);

	m_buttonst6.Create(m_panel,CRect(181,6,201,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_ALIGN_BOTTOM);
	m_buttonst6.SetFont((HFONT)m_formFont);
	m_buttonst6.SetFlat(true);
	m_buttonst6.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst6.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst6.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst6.SetTooltipText(_T("Aligment Bottom"));
	m_buttonst6.SetIcon(IDI_ALIGN_BOTTOM,IDI_ALIGN_BOTTOM);

	m_panel7.Create(m_panel,CRect(206,6,208,24),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CMAINFRAME_PANEL7);
	m_panel7.SetFont((HFONT)m_formFont);
	m_panel7.SetInnerBorder(BDR_RAISEDINNER);
	m_panel7.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel7.SetEdgeType(BF_LEFT);
	m_panel7.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel7.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel7.SetHorizTextAlign(DT_CENTER);
	m_panel7.SetVertTextAlign(DT_VCENTER);
	m_panel7.SetSingleLine(true);

	m_buttonst8.Create(m_panel,CRect(214,6,234,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_SAME_WIDTH);
	m_buttonst8.SetFont((HFONT)m_formFont);
	m_buttonst8.SetFlat(true);
	m_buttonst8.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst8.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst8.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst8.SetTooltipText(_T("Make the same width"));
	m_buttonst8.SetIcon(IDI_SAME_WIDTH,IDI_SAME_WIDTH);

	m_edit.Create(m_panel,CRect(525,6,566,26),_T("0"),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_CMAINFRAME_EDIT10);
	m_edit.SetFont((HFONT)m_formFont);
	m_toolTip.AddTool((HWND)m_edit,(LPCTSTR)_T("Distance"));

	m_updownctrl11.Create(m_panel,CRect(544,6,561,26),NULL,WS_CHILD|WS_VISIBLE|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS|UDS_HOTTRACK,0,IDC_CMAINFRAME_UPDOWNCTRL11);
	m_updownctrl11.SetBase(10);
	m_updownctrl11.SetRange(-99,99);
	m_updownctrl11.SetPos(0);

	m_buttonst12.Create(m_panel,CRect(238,6,258,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_SAME_HEIGHT);
	m_buttonst12.SetFont((HFONT)m_formFont);
	m_buttonst12.SetFlat(true);
	m_buttonst12.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst12.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst12.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst12.SetTooltipText(_T("Make the same height"));
	m_buttonst12.SetIcon(IDI_SAME_HEIGHT,IDC_SAME_HEIGHT);

	m_panel13.Create(m_panel,CRect(309,6,311,24),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CMAINFRAME_PANEL13);
	m_panel13.SetFont((HFONT)m_formFont);
	m_panel13.SetInnerBorder(BDR_RAISEDINNER);
	m_panel13.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel13.SetEdgeType(BF_LEFT);
	m_panel13.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel13.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel13.SetHorizTextAlign(DT_CENTER);
	m_panel13.SetVertTextAlign(DT_VCENTER);
	m_panel13.SetSingleLine(true);

	m_buttonst14.Create(m_panel,CRect(262,6,282,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_SAME_SIZE);
	m_buttonst14.SetFont((HFONT)m_formFont);
	m_buttonst14.SetFlat(true);
	m_buttonst14.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst14.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst14.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst14.SetTooltipText(_T("Make the same size"));
	m_buttonst14.SetIcon(IDI_SAME_SIZE,IDC_SAME_SIZE);

	m_buttonst15.Create(m_panel,CRect(666,6,686,26),_T(""),WS_CHILD|BS_PUSHBUTTON,0,IDC_GS_HORIZ);
	m_buttonst15.SetFont((HFONT)m_formFont);
	m_buttonst15.SetFlat(true);
	m_buttonst15.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst15.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst15.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst15.SetIcon(IDI_GS_HORIZ,IDI_GS_HORIZ);

	m_buttonst16.Create(m_panel,CRect(692,6,712,26),_T(""),WS_CHILD|BS_PUSHBUTTON,0,IDC_GS_VERT);
	m_buttonst16.SetFont((HFONT)m_formFont);
	m_buttonst16.SetFlat(true);
	m_buttonst16.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst16.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst16.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst16.SetIcon(IDI_GS_VERT,IDI_GS_VERT);

	m_panel17.Create(m_panel,CRect(658,6,660,24),NULL,WS_CHILD,0,IDC_CMAINFRAME_PANEL17);
	m_panel17.SetFont((HFONT)m_formFont);
	m_panel17.SetInnerBorder(BDR_RAISEDINNER);
	m_panel17.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel17.SetEdgeType(BF_LEFT);
	m_panel17.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel17.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel17.SetHorizTextAlign(DT_CENTER);
	m_panel17.SetVertTextAlign(DT_VCENTER);
	m_panel17.SetSingleLine(true);

	m_buttonst18.Create(m_panel,CRect(317,6,337,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_CENTER_HORIZ);
	m_buttonst18.SetFont((HFONT)m_formFont);
	m_buttonst18.SetFlat(true);
	m_buttonst18.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst18.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst18.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst18.SetTooltipText(_T("Center Horizontal"));
	m_buttonst18.SetIcon(IDI_CENTER_HORIZ,IDI_CENTER_HORIZ);

	m_buttonst19.Create(m_panel,CRect(343,6,363,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_CENTER_VERT);
	m_buttonst19.SetFont((HFONT)m_formFont);
	m_buttonst19.SetFlat(true);
	m_buttonst19.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst19.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst19.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst19.SetTooltipText(_T("Center Vertical"));
	m_buttonst19.SetIcon(IDI_CENTER_VERT,IDI_CENTER_VERT);

	m_buttonst21.Create(m_panel,CRect(421,6,441,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_HORIZ_ORDER);
	m_buttonst21.SetFont((HFONT)m_formFont);
	m_buttonst21.SetFlat(true);
	m_buttonst21.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst21.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst21.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst21.SetTooltipText(_T("Set horizontal order"));
	m_buttonst21.SetIcon(IDI_HORIZ_ORDER,IDI_HORIZ_ORDER);

	m_buttonst22.Create(m_panel,CRect(447,6,467,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_VERT_ORDER);
	m_buttonst22.SetFont((HFONT)m_formFont);
	m_buttonst22.SetFlat(true);
	m_buttonst22.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst22.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst22.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst22.SetIcon(IDI_VERT_ORDER,IDI_VERT_ORDER);

	m_new.Create(m_panel,CRect(6,6,26,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,ID_FILE_NEW);
	m_new.SetFont((HFONT)m_formFont);
	m_new.SetFlat(true);
	m_new.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_new.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_new.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_new.SetTooltipText(_T("New file"));
	m_new.SetIcon(IDI_NEW,IDI_NEW);

	m_open.Create(m_panel,CRect(30,6,50,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,ID_FILE_OPEN);
	m_open.SetFont((HFONT)m_formFont);
	m_open.SetFlat(true);
	m_open.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_open.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_open.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_open.SetTooltipText(_T("Open file"));
	m_open.SetIcon(IDI_OPEN,IDI_OPEN);

	m_buttonst26.Create(m_panel,CRect(54,6,74,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,ID_FILE_SAVE);
	m_buttonst26.SetFont((HFONT)m_formFont);
	m_buttonst26.SetFlat(true);
	m_buttonst26.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst26.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst26.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst26.SetTooltipText(_T("Save file"));
	m_buttonst26.SetIcon(IDI_SAVE,IDI_SAVE);

	m_saveAll.Create(m_panel,CRect(78,6,98,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,ID_FILE_SAVEALL);
	m_saveAll.SetFont((HFONT)m_formFont);
	m_saveAll.SetFlat(true);
	m_saveAll.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_saveAll.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_saveAll.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_saveAll.SetTooltipText(_T("Save All"));
	m_saveAll.SetIcon(IDI_SAVE_ALL,IDI_SAVE_ALL);

	m_panel28.Create(m_panel,CRect(102,6,104,24),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CMAINFRAME_PANEL28);
	m_panel28.SetFont((HFONT)m_formFont);
	m_panel28.SetInnerBorder(BDR_RAISEDINNER);
	m_panel28.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel28.SetEdgeType(BF_LEFT);
	m_panel28.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel28.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel28.SetHorizTextAlign(DT_CENTER);
	m_panel28.SetVertTextAlign(DT_VCENTER);
	m_panel28.SetSingleLine(true);

	m_buttonst29.Create(m_panel,CRect(286,6,306,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_TOPARENT);
	m_buttonst29.SetFont((HFONT)m_formFont);
	m_buttonst29.SetFlat(true);
	m_buttonst29.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst29.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst29.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst29.SetTooltipText(_T("Make control size as parent client area size"));
	m_buttonst29.SetIcon(IDI_TOPARENT,IDI_TOPARENT);

	m_panel30.Create(m_panel,CRect(572,6,574,24),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CMAINFRAME_PANEL30);
	m_panel30.SetFont((HFONT)m_formFont);
	m_panel30.SetInnerBorder(BDR_RAISEDINNER);
	m_panel30.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel30.SetEdgeType(BF_LEFT);
	m_panel30.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel30.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel30.SetHorizTextAlign(DT_CENTER);
	m_panel30.SetVertTextAlign(DT_VCENTER);
	m_panel30.SetSingleLine(true);

	m_buttonst33.Create(m_panel,CRect(580,6,600,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_CREATION_ORDER);
	m_buttonst33.SetFont((HFONT)m_formFont);
	m_buttonst33.SetFlat(true);
	m_buttonst33.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst33.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst33.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst33.SetTooltipText(_T("Creation order"));
	m_buttonst33.SetIcon(IDI_CREATION_ORDER,IDI_CREATION_ORDER);

	m_buttonst37.Create(m_panel,CRect(369,6,389,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_CENTER_GROUP_HORIZ);
	m_buttonst37.SetFont((HFONT)m_formFont);
	m_buttonst37.SetFlat(true);
	m_buttonst37.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst37.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst37.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst37.SetTooltipText(_T("Center Controls Horizontal"));
	m_buttonst37.SetIcon(IDI_CENTER_GROUP_HORIZ,IDC_CENTER_GROUP_HORIZ);

	m_buttonst38.Create(m_panel,CRect(395,6,415,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_CENTER_GROUP_VERT);
	m_buttonst38.SetFont((HFONT)m_formFont);
	m_buttonst38.SetFlat(true);
	m_buttonst38.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst38.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst38.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst38.SetTooltipText(_T("Center Controls Vertical"));
	m_buttonst38.SetIcon(IDI_CENTER_GROUP_VERT,IDI_CENTER_GROUP_VERT);

	m_showgrid.Create(m_panel1,CRect(3,6,23,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_SHOW_GRID);
	m_showgrid.SetFont((HFONT)m_formFont);
	m_showgrid.SetFlat(true);
	m_showgrid.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_showgrid.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_showgrid.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_showgrid.SetIcon(IDI_SHOW_GRID,IDI_SHOW_GRID);
	m_showgrid.EnablePressedState(true);

	m_static49.Create(m_panel1,CRect(29,9,35,23),_T("x"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CMAINFRAME_STATIC49);
	m_static49.SetFont((HFONT)m_formFont);

	m_xedit.Create(m_panel1,CRect(42,6,81,26),_T("8"),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_XEDIT);
	m_xedit.SetFont((HFONT)m_formFont);

	m_updownctrl51.Create(m_panel1,CRect(62,6,79,26),NULL,WS_CHILD|WS_VISIBLE|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS,0,IDC_CMAINFRAME_UPDOWNCTRL51);
	m_updownctrl51.SetBase(10);
	m_updownctrl51.SetRange(1,99);
	m_updownctrl51.SetPos(6);

	m_static52.Create(m_panel1,CRect(87,9,93,23),_T("y"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CMAINFRAME_STATIC52);
	m_static52.SetFont((HFONT)m_formFont);

	m_yedit.Create(m_panel1,CRect(100,6,139,26),_T("8"),WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE,IDC_YEDIT);
	m_yedit.SetFont((HFONT)m_formFont);

	m_panel55.Create(m_panel1,CRect(144,6,146,24),NULL,WS_CHILD|WS_VISIBLE,0,IDC_CMAINFRAME_PANEL55);
	m_panel55.SetFont((HFONT)m_formFont);
	m_panel55.SetInnerBorder(BDR_RAISEDINNER);
	m_panel55.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel55.SetEdgeType(BF_LEFT);
	m_panel55.SetBkColor(RGB(0xF4,0xF3,0xEE));
	m_panel55.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel55.SetHorizTextAlign(DT_CENTER);
	m_panel55.SetVertTextAlign(DT_VCENTER);
	m_panel55.SetSingleLine(true);

	m_buttonst56.Create(m_panel1,CRect(538,4,558,24),_T(""),WS_CHILD|BS_PUSHBUTTON,0,IDC_SHOW_GSGRID);
	m_buttonst56.SetFont((HFONT)m_formFont);
	m_buttonst56.SetFlat(true);
	m_buttonst56.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst56.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst56.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst56.SetIcon(IDI_SHOW_GSGRID,IDI_SHOW_GSGRID);
	m_buttonst56.EnablePressedState(true);

	m_updownctrl57.Create(m_panel1,CRect(126,6,141,26),NULL,WS_CHILD|WS_VISIBLE|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS,0,IDC_CMAINFRAME_UPDOWNCTRL57);
	m_updownctrl57.SetBase(10);
	m_updownctrl57.SetRange(1,99);
	m_updownctrl57.SetPos(6);

	m_buttonst58.Create(m_panel,CRect(632,6,652,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_CHANGEPARENT);
	m_buttonst58.SetFont((HFONT)m_formFont);
	m_buttonst58.SetFlat(true);
	m_buttonst58.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst58.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst58.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst58.SetTooltipText(_T("Change parent"));
	m_buttonst58.SetIcon(IDI_CHANGEPARENT,IDI_CHANGEPARENT);

	m_tabOrder.Create(m_panel,CRect(606,6,626,26),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_TABORDER);
	m_tabOrder.SetFont((HFONT)m_formFont);
	m_tabOrder.SetFlat(true);
	m_tabOrder.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_tabOrder.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_tabOrder.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_tabOrder.SetIcon(IDI_TABORDER,IDI_TABORDER);
	m_tabOrder.EnablePressedState(true);

	m_buttonst60.Create(m_panel,CRect(473,6,493,26),_T(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_HORIZ_ORDER_RIGHT);
	m_buttonst60.SetFont((HFONT)m_formFont);
	m_buttonst60.SetFlat(true);
	m_buttonst60.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst60.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst60.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst60.SetIcon(IDI_HORIZ_ORDER_RIGHT,IDI_HORIZ_ORDER_RIGHT);

	m_buttonst61.Create(m_panel,CRect(499,6,519,26),_T(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,0,IDC_VERT_ORDER_BOTTOM);
	m_buttonst61.SetFont((HFONT)m_formFont);
	m_buttonst61.SetFlat(true);
	m_buttonst61.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_buttonst61.SetColor(CButtonST::BTNST_COLOR_BK_IN,RGB(0xF4,0xF3,0xEE));
	m_buttonst61.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0xF4,0xF3,0xEE));
	m_buttonst61.SetIcon(IDI_VERT_ORDER_BOTTOM,IDI_VERT_ORDER_BOTTOM);

	m_static62.Create(m_panel1,CRect(154,9,162,23),_T("X"),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|SS_LEFT,0,IDC_CMAINFRAME_STATIC62);
	m_static62.SetFont((HFONT)m_formFont);

	m_XCursor.Create(m_panel1,CRect(170,9,189,23),_T("0"),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|SS_LEFT,0,IDC_XCURSOR);
	m_XCursor.SetFont((HFONT)m_formFont);

	m_static64.Create(m_panel1,CRect(197,9,205,23),_T("Y"),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|SS_LEFT,0,IDC_STATICY);
	m_static64.SetFont((HFONT)m_formFont);

	m_YCursor.Create(m_panel1,CRect(213,9,232,23),_T("0"),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|SS_LEFT,0,IDC_YCURSOR);
	m_YCursor.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
	m_updownctrl11.SetBuddy(m_edit);
	m_updownctrl51.SetBuddy(m_xedit);
	m_updownctrl57.SetBuddy(m_yedit);
//}}WTLBUILDER_POST_CREATION
    InitLayout();
	//////////////////////////////////////////////////////////////////////////
    HMENU hMenu = GetMenu();
    HMENU hFileMenu = ::GetSubMenu(hMenu, FILE_MENU_POSITION);
    HMENU hMruMenu = ::GetSubMenu(hFileMenu, RECENT_MENU_POSITION);
    
    mru.SetMenuHandle(hMruMenu);
    mru.ReadFromRegistry(WTLBuilderRegKey);
    CalcWindowSize();
    MoveWindow(0,0,0,0);
    toolBox.Create(m_hWnd);
    
	//////////////////////////////////////////////////////////////////////////
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	outputWindow.Create(m_hWnd);
	m_ScriptHost.Init(m_hWnd);
	m_ScriptHost.LoadScriptsFromDir("Script\\");
	m_ScriptHost.AddScriptItem(L"Output",&outputWindow);
    m_ScriptHost.AddScriptItem(L"ValueList",&valueListHelper);
//////////////////////////////////////////////////////////////////////////
	return 0;
}

void CMainFrame::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CMainFrame::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
    //SetScrollSize(_minClientSize);
}

void CMainFrame::GetDialogRect(LPRECT r)
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

void CMainFrame::GetOffset(LPPOINT offset)
{
    *offset = m_ptOffset;
}

void CMainFrame::DoPaint(CDCHandle /*dc*/)
{

}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if(project.CloseAll()==TRUE)
    {
//	    SendEvent(evShutDown);
//	    StopCommandTimer();
//      mru.WriteToRegistry(WTLBuilderRegKey);
	    PostMessage(WM_CLOSE);
    }
	return 0;
}

LRESULT CMainFrame::OnFileNewForm( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ ) 
{
	EnableMsgPump(FALSE);
	project.New();
	BOOL bHandled;
	OnSelectComponent(0,0,0,bHandled);
	EnableMsgPump();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainFrame::OnCommonCommand(WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SendEvent(evOnCommand,(UINT)wID);
	return 0;
}

void CMainFrame::AddMenu(const CMenuHandle * pMenuAdd,bool bTopLevel)
{
	//CMenuHandle tempMenu(m_CmdBar.GetMenu());
	//MergeMenu(&tempMenu,pMenuAdd,bTopLevel);
	//m_CmdBar.AttachMenu(tempMenu);
	return;
}

LRESULT CMainFrame::OnMenuSelect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled=FALSE;
	return 0;
}

LRESULT CMainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    CRect rc;
    m_panel.GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.right=LOWORD(lParam);
    m_panel.MoveWindow(&rc);

    m_panel1.GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.right=LOWORD(lParam);
    m_panel1.MoveWindow(&rc);

    m_toolTab.GetWindowRect(&rc);
    ScreenToClient(&rc);
    rc.right=LOWORD(lParam);
    m_toolTab.MoveWindow(&rc);
	bHandled=FALSE;
	return 0;
}

void CMainFrame::FillToolPanel(LPCTSTR _name,LPCTSTR _page,HBITMAP _bitmap,int type)
{
	if((type & TypeForm) != TypeForm)
		m_toolTab.AddImage(_page,_bitmap ,_name);
}

LRESULT CMainFrame::OnSelectComponent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CString str=m_toolTab.get_SelectedName();
	SendEvent(evSelectComponent,(LPCTSTR)str);
	return 0;
}

void CMainFrame::ResetSelectedComponent(void)
{
	SendEvent(evSelectComponent,NULL);///временно
	m_toolTab.UnSelect();
}

HANDLE CMainFrame::GetHandle(void)
{
	return m_hWnd;
}

LRESULT CMainFrame::OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL&)
{
	SendEvent(evClearOutput);
	EnableMsgPump(FALSE);
	project.Save();
	EnableMsgPump();
	return 0;
}

LRESULT CMainFrame::OnFileSaveAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL&)
{
	SendEvent(evClearOutput);
    EnableMsgPump(FALSE);
    project.SaveAll();
    EnableMsgPump();
    return 0;
}

LRESULT CMainFrame::OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL&)
{
	SendEvent(evClearOutput);
	EnableMsgPump(FALSE);
	project.SaveAs();
	EnableMsgPump();
	return 0;
}

LRESULT CMainFrame::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL&)
{
	EnableMsgPump(FALSE);
	project.Open();
	BOOL bHandled;
	OnSelectComponent(0,0,0,bHandled);
	EnableMsgPump();
	return 0;
}

LRESULT CMainFrame::OnFileClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL&)
{
	EnableMsgPump(FALSE);
	project.CloseActive();
	EnableMsgPump();
	return 0;
}

LRESULT CMainFrame::OnAlignCommand(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(project.Forms->Active==NULL)
		return 0;

    _TCHAR text[8];
    m_edit.GetLine(0,text,3);
    long val=StrToLong(text);

	switch(wID)
	{
	case IDC_ALIGN_LEFT:
		SendEvent(evAlignComponentsLeft,project.Forms->Active, val);
		break;
	case IDC_ALIGN_TOP:
		SendEvent(evAlignComponentsTop,project.Forms->Active, val);
		break;
	case IDC_ALIGN_RIGHT:
		SendEvent(evAlignComponentsRight,project.Forms->Active, val);
		break;
	case IDC_ALIGN_BOTTOM:
		SendEvent(evAlignComponentsBottom,project.Forms->Active, val);
		break;
	case IDC_CENTER_HORIZ:
		SendEvent(evAlignComponentsHoriz,project.Forms->Active);
		break;
	case IDC_CENTER_VERT:
		SendEvent(evAlignComponentsVert,project.Forms->Active);
		break;
	case IDC_SAME_HEIGHT:
		SendEvent(evMakeSameHeight,project.Forms->Active, val);
		break;
	case IDC_SAME_WIDTH:
		SendEvent(evMakeSameWidth,project.Forms->Active, val);
		break;
	case IDC_SAME_SIZE:
		SendEvent(evMakeSameSize,project.Forms->Active, val);
		break;
	case IDC_GS_HORIZ:
		SendEvent(evGoldenSectionWidth,project.Forms->Active);
		break;
	case IDC_GS_VERT:
		SendEvent(evGoldenSectionHeight,project.Forms->Active);
		break;
    case IDC_TOPARENT:
        SendEvent(evToParent,project.Forms->Active, val);
        break;
    case IDC_HORIZ_ORDER:
        SendEvent(evHorizOrder,project.Forms->Active,val);
        break;
    case IDC_VERT_ORDER:
        SendEvent(evVertOrder,project.Forms->Active,val);
        break;
	case IDC_HORIZ_ORDER_RIGHT:
		SendEvent(evHorizOrderRight,project.Forms->Active,val);
		break;
	case IDC_VERT_ORDER_BOTTOM:
		SendEvent(evVertOrderBottom,project.Forms->Active,val);
		break;
    //case IDC_TOBACKGROUND:
    //    SendEvent(evToBackground,project.Forms->Active);
    //    break;
    //case IDC_TOFOREGROUND:
    //    SendEvent(evToForeground,project.Forms->Active);
    //    break;
    case IDC_CENTER_GROUP_HORIZ:
        SendEvent(evCenterGroupHoriz,project.Forms->Active,val);
        break;
    case IDC_CENTER_GROUP_VERT:
        SendEvent(evCenterGroupVert,project.Forms->Active,val);
        break;
    case IDC_CHANGEPARENT:
        SendEvent(evChangeParent,project.Forms->Active);
        break;
	}

	return 0;
}

LRESULT CMainFrame::OnSaveAsTemplate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
{
	EnableMsgPump(FALSE);
	project.SaveAsTemplate();
	EnableMsgPump(TRUE);
	return 0;
}

LRESULT CMainFrame::OnGenerateLocFile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
{
	EnableMsgPump(FALSE);
	project.GenerateLocFile();
	EnableMsgPump(TRUE);
    
	return 0;
}

LRESULT CMainFrame::OnOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	COptionsDlg dlg;
	if(dlg.DoModal(::GetDesktopWindow())==IDOK)
	{
	}
	return 0;
}

LRESULT CMainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if(project.CloseAll()==TRUE)
    {
		mru.WriteToRegistry(WTLBuilderRegKey);
		//delete m_pScriptHost;
        SendEvent(evShutDown);
        StopCommandTimer();
        bHandled=FALSE;
    }
    else
    {
	    bHandled=TRUE;
        return TRUE;
    }
	return 0;
}

LRESULT CMainFrame::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MINMAXINFO * minmax=(MINMAXINFO *)lParam;
    minmax->ptMaxSize.x=GetSystemMetrics(SM_CXSCREEN);
    minmax->ptMaxSize.y=windowHeight;

    minmax->ptMinTrackSize.x=GetSystemMetrics(SM_CXSCREEN);
    minmax->ptMinTrackSize.y=windowHeight;

    minmax->ptMaxTrackSize.x=GetSystemMetrics(SM_CXSCREEN);
    minmax->ptMaxTrackSize.y=windowHeight;
    
    bHandled=TRUE;
    return 0;
}

long CMainFrame::CalcWindowSize()
{
    long panelHeight=-1,toolTabHeight=-1;
    
    if(::IsWindow(m_panel))
    {
        CRect panelRc;
        ::GetWindowRect(m_panel,&panelRc);
        panelHeight=panelRc.Height();
    }

    if(::IsWindow(m_panel1))
    {
        CRect panelRc;
        ::GetWindowRect(m_panel1,&panelRc);
        panelHeight+=panelRc.Height();
    }

    if(::IsWindow(m_toolTab))
    {
        CRect toolTabRc;
        ::GetWindowRect(m_toolTab,&toolTabRc);
        toolTabHeight=toolTabRc.Height();
    }

    return windowHeight=panelHeight+toolTabHeight+GetSystemMetrics(SM_CYBORDER)*2
                 +GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENU);
}

LRESULT CMainFrame::OnWinIniChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    CalcWindowSize();
    SendEvent(evWinIniChange);
    bHandled=FALSE;
    return TRUE;
}

void CMainFrame::FormSavedLoaded(Component * form,LPCTSTR formName)
{
    mru.AddToList(formName);
    if(static_cast<Component *>(form)==static_cast<Component *>((Component*)project.get_Forms()->get_Active()))
        SetActiveForm(form);
}

LRESULT CMainFrame::OnFileRecent(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{			
    CString sFile;
    if(mru.GetFromList(wID, sFile))
    {										
        EnableMsgPump(FALSE);
        if(project.Open(CComBSTR((LPCTSTR)sFile))==TRUE)
            mru.MoveToTop(wID);
        else
            mru.RemoveFromList(wID);

        BOOL bHandled;
        OnSelectComponent(0,0,0,bHandled);
        EnableMsgPump();
    }
    else
    {
        ::MessageBeep(MB_ICONERROR);
        ::MessageBox(m_hWnd,_T("Cannot get file name from mru list"),_T("WTLBuilder"),MB_OK|MB_ICONERROR);
    }
    return 0;
}

void CMainFrame::OnEditCommand(WORD wID,Component *comp,CPoint * downPoint)
{
///////////////////////////////////////// to avoid app crash
	return;
////////////////////////////////////////
    if(project.Forms->Active==NULL)
        return ;

	CMsgPump msgPump;

    switch(wID)
    {
    case ID_EDIT_UNDO:
        SendEvent(evUndo,project.Forms->Active);
        break;
    case ID_EDIT_CUT:
        SendEvent(evCut,project.Forms->Active,comp);
        break;
    case ID_EDIT_COPY:
        SendEvent(evCopy,project.Forms->Active,comp);
        break;
    case ID_EDIT_PASTE:
        SendEvent(evPaste,project.Forms->Active,comp,downPoint);
        break;
    case ID_EDIT_SELECT_ALL:
        SendEvent(evSelectAll,project.Forms->Active);
        break;
    case ID_EDIT_CLEAR:
        SendEvent(evDelete,project.Forms->Active);
        break;
    };
}

LRESULT CMainFrame::OnTabOrder(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    bool pressed=m_tabOrder.GetPressed();
    m_tabOrder.SetPressed(pressed=!pressed);
    SendEvent(evTabIndex,project.Forms->Active,(BOOL)pressed);
    return 0;
}

LRESULT CMainFrame::OnEdit(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    OnEditCommand(wID,NULL,NULL);
    return 0;
}

LRESULT CMainFrame::OnView(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& bHandled)
{
    switch(wID)
    {
    case ID_VIEW_PROPERTY:
        toolBox.ShowWindow(SW_SHOW);
    	break;
    case ID_VIEW_OUTPUT:
        outputWindow.ShowWindow(SW_SHOW);
        break;
    };
    bHandled=TRUE;
    return TRUE;
}

LRESULT CMainFrame::OnShowGrid(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    m_showgrid.SetPressed(!m_showgrid.GetPressed());
    SendEvent(evShowGrid,project.Forms->Active,(BOOL)(m_showgrid.GetPressed()==true));
    return 0;
}

void CMainFrame::SetGridButton(void *obj,BOOL val)
{
    if(obj==NULL)
    {
        StopEvent(evShowGrid);
        if((BOOL)m_showgrid.GetPressed()!=val)
            m_showgrid.SetPressed((bool)(val==TRUE));
     }
}

void CMainFrame::SetGridWidth(void *obj,long val)
{
    if(obj==NULL)
    {
        CString str;
        str.Format(_T("%d"),val);
        m_xedit.SetWindowText(str);
		StopEvent(evSetGridSizeX);
    }
}

void CMainFrame::SetGridHeight(void *obj,long val)
{
    if(obj==NULL)
    {
        CString str;
        str.Format(_T("%d"),val);
        m_yedit.SetWindowText(str);
		StopEvent(evSetGridSizeY);
    }
}

LRESULT CMainFrame::OnXEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if(::IsWindow(m_xedit))
    {
        _TCHAR text[8];
        m_xedit.GetLine(0,text,3);
        long val=StrToLong(text);
        SendEvent(evSetGridSizeX,project.Forms->Active,val);
    }

    return 0;
}

LRESULT CMainFrame::OnYEditChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if(::IsWindow(m_yedit))
    {
        _TCHAR text[8];
        m_yedit.GetLine(0,text,3);
        long val=StrToLong(text);
        SendEvent(evSetGridSizeY,project.Forms->Active,val);
    }

    return 0;
}

void CMainFrame::EnableUndo(BOOL _enableundo)
{
    enableUndo=_enableundo;
}
//////////////////////////////////////////////////////////////////////////
int FindMenuItem(CMenuHandle & menu, LPCTSTR MenuString)
{
	int count = menu.GetMenuItemCount();
	for (int i = 0; i < count; i++)
	{
		CString str;
		if (menu.GetMenuString(i, str, MF_BYPOSITION) &&
			(_tcscmp(str, MenuString) == 0))
			return i;
	}

	return -1;
}

void __stdcall CMainFrame::InsertPopupItem(BSTR _after,BSTR _item)
{
	USES_CONVERSION;
	
	CString after = OLE2CT(_after);
	CString item = OLE2CT(_item);
	
	CMenuHandle menu=this->GetMenu();
	if(after.IsEmpty()==FALSE)
	{
		CMenu newMenu;
		newMenu.CreatePopupMenu();
		int pos = FindMenuItem(menu, (LPCTSTR)after);
		if (pos != -1)
			menu.InsertMenu(pos+1,MF_BYPOSITION|MF_POPUP, newMenu,item);
		else
			menu.AppendMenu(MF_POPUP, newMenu,item);

		newMenu.Detach();
		SetMenu(menu);
	}
}

void __stdcall CMainFrame::AppendItem(BSTR _popup,BSTR _item,BSTR _script)
{
	USES_CONVERSION;

	CString popup = OLE2CT(_popup);
	CString item = OLE2CT(_item);
	CString script = OLE2CT(_script);

	CMenuHandle menu=this->GetMenu();
	int pos;
	if(popup.IsEmpty()==FALSE)
	{
		pos = FindMenuItem(menu, (LPCTSTR)popup);
		if (pos == -1)
			return;
		CMenuHandle subMenu((HMENU)menu.GetSubMenu(pos));
		if(subMenu.IsMenu())
		{
			
			userMenuMap.SetAt(userMenuCount,script);
			subMenu.AppendMenu(MF_POPUP|MF_STRING, (UINT_PTR)userMenuCount, (LPCTSTR)item);
			userMenuCount++;
		}
		SetMenu(menu);
	}

}

LRESULT CMainFrame::OnUserMenu(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EnableMsgPump(FALSE);
	CString script = userMenuMap[(UINT)wID];
	//InvokeFunc(script.AllocSysString(), NULL,0,NULL);//VARIANT* Params, LONG Count, VARIANT* RetValue)
	EnableMsgPump();
	return 0;
}

void CMainFrame::LoadFormFromFile(LPCSTR formFileName)
{
	CPath fileName(formFileName);
	fileName.SetExt(_T("wff"));
	project.Open(CComBSTR(fileName.GetPath()));
}

void CMainFrame::SetActiveForm(Component *form)
{
	CString formFileName;
    BOOL flag=FALSE;
	if(form!=NULL)
	{
		SendEvent(evGetFormFileName,form,&formFileName);
        SendEvent(evIsFormChanged,form,&flag);
        SetWindowText(MakeString(_T("WTLBuilder - [%s]%c"),(LPCTSTR)formFileName,flag?'*':' '));
	}
	else
	{
		SetWindowText(_T("WTLBuilder"));
	}	
}

LRESULT CMainFrame::OnCtrlBuilder(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    return 0;
}

LRESULT CMainFrame::OnFileNewControl(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    return 0;
}

void CMainFrame::LoadScriptFromFile(LPCSTR file)
{
	m_ScriptHost.LoadScriptFromFile(_bstr_t(file));
}

void CMainFrame::XYCursor(CPoint pt)
{
	CString str;
	str.Format("%d", pt.x);
	m_XCursor.SetWindowText(str);
	str.Format("%d", pt.y);
	m_YCursor.SetWindowText(str);
}