//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "[!FILENAME].h"
//#include "CDialogTemplate.h"
///////////////////////////////////////////////////////////////////////////////
CDialogTemplate::CDialogTemplate(void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

CDialogTemplate::~CDialogTemplate(void)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
}

LRESULT CDialogTemplate::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(476,395);

	m_panel0.Create(m_hWnd,CRect(0,0,476,37),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT,IDC_CFORMTYPE_PANEL0);
	m_panel0.SetFont((HFONT)m_formFont);
	m_panel0.SetInnerBorder(BDR_RAISEDINNER);
	m_panel0.SetOuterBorder(BDR_SUNKENOUTER);
	m_panel0.SetEdgeType(BF_RECT);
	m_panel0.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel0.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel0.SetHorizTextAlign(DT_CENTER);
	m_panel0.SetVertTextAlign(DT_VCENTER);
	m_panel0.SetSingleLine(true);
	m_panel0.SetCaption(_TEXT(""));

	m_panel1.Create(m_hWnd,CRect(0,37,476,358),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT,IDC_CFORMTYPE_PANEL1);
	m_panel1.SetFont((HFONT)m_formFont);
	m_panel1.SetInnerBorder(0);
	m_panel1.SetOuterBorder(BDR_RAISEDOUTER);
	m_panel1.SetEdgeType(BF_RECT);
	m_panel1.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel1.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel1.SetHorizTextAlign(DT_CENTER);
	m_panel1.SetVertTextAlign(DT_VCENTER);
	m_panel1.SetSingleLine(true);
	m_panel1.SetCaption(_TEXT(""));

	m_panel8.Create(m_hWnd,CRect(0,358,476,395),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT,IDC_CFORMTYPE_PANEL8);
	m_panel8.SetFont((HFONT)m_formFont);
	m_panel8.SetInnerBorder(BDR_RAISEDINNER);
	m_panel8.SetOuterBorder(0);
	m_panel8.SetEdgeType(BF_RECT);
	m_panel8.SetTextColor(GetSysColor(COLOR_BTNTEXT));
	m_panel8.SetBkColor(GetSysColor(COLOR_BTNFACE));
	m_panel8.SetHorizTextAlign(DT_CENTER);
	m_panel8.SetVertTextAlign(DT_VCENTER);
	m_panel8.SetSingleLine(true);
	m_panel8.SetCaption(_TEXT(""));

	m_button9.Create(m_panel8,CRect(306,7,380,29),_TEXT("&Ok"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
	m_button9.SetFont((HFONT)m_formFont);

	m_button10.Create(m_panel8,CRect(386,7,460,29),_TEXT("&Cancel"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
	m_button10.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
	CenterWindow();

	return TRUE;
}

LRESULT CDialogTemplate::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

