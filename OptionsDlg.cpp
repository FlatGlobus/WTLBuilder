#include "StdAfx.h"
#include "OptionsDlg.h"
///////////////////////////////////////////////////////////////////////////////
const UINT COptionsDlg::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
    0
};
//////////////////////////////////////////////////////////////////////////
COptionsDlg::COptionsDlg(void)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
    _showHandle=FALSE;
}

COptionsDlg::~COptionsDlg(void)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
}

LRESULT COptionsDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_CREATION
    m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
    SetFont((HFONT)m_formFont);
    ModifyStyle(GetStyle(),WS_OVERLAPPED|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX);
    ResizeClient(602,449);
    SetWindowText(_T("Options"));

    m_ok.Create(m_hWnd,CRect(433,416,507,438),_T("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
    m_ok.SetFont((HFONT)m_formFont);

    m_cancel.Create(m_hWnd,CRect(517,416,591,438),_T("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
    m_cancel.SetFont((HFONT)m_formFont);

    m_optListbox.Create(m_hWnd,CRect(8,8,192,396),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP|LBS_NOTIFY,WS_EX_CLIENTEDGE,IDC_OPTLISTBOX);
    m_optListbox.SetFont((HFONT)m_formFont);
    m_optListbox.AddString(_T("Code generation"));
    m_optListbox.SetItemHeight(0,13);
    m_optListbox.SetHorizontalExtent(40);

    m_panelhost.Create(m_hWnd,CRect(200,8,594,396),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP,0,IDC_OPTPANELHOST);
    m_panelhost.SetFont((HFONT)m_formFont);
    m_panelhost.SetInnerBorder(0);
    m_panelhost.SetOuterBorder(0);
    m_panelhost.SetTheme(TRUE);
    m_panelhost.SetBkColor(RGB(0x00,0x00,0x00));

    m_panel10.Create(m_hWnd,CRect(8,408,594,416),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,WS_EX_CONTROLPARENT,IDC_COPTIONSDLG_PANEL10);
    m_panel10.SetFont((HFONT)m_formFont);
    m_panel10.SetInnerBorder(BDR_SUNKENINNER);
    m_panel10.SetOuterBorder(BDR_RAISEDOUTER);
    m_panel10.SetEdgeType(BF_TOP);
    m_panel10.SetBkColor(RGB(0xF0,0xF0,0xF0));
    m_panel10.SetTextColor(RGB(0x00,0x00,0x00));
    m_panel10.SetHorizTextAlign(DT_CENTER);
    m_panel10.SetVertTextAlign(DT_VCENTER);
    m_panel10.SetSingleLine(true);

    codeGeneration.Create(m_panelhost,CRect(0,0,394,388),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,WS_EX_CONTROLPARENT,IDC_COPTIONSDLG_CODEGENERATION);
    codeGeneration.SetFont((HFONT)m_formFont);
    codeGeneration.SetInnerBorder(0);
    codeGeneration.SetOuterBorder(0);
    codeGeneration.SetEdgeType(BF_RECT);
    codeGeneration.SetTheme(TRUE);
    codeGeneration.SetTextColor(RGB(0x00,0x00,0x00));
    codeGeneration.SetHorizTextAlign(DT_CENTER);
    codeGeneration.SetVertTextAlign(DT_VCENTER);
    codeGeneration.SetSingleLine(true);
    m_panelhost.AddPanel(&codeGeneration);

    m_add_m_prefix.Create(codeGeneration,CRect(8,8,192,32),_T("Add m_ prefix to member name"),WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP|BS_AUTOCHECKBOX|BS_TEXT|BS_LEFT|BS_VCENTER|BS_FLAT,0,ID_ADD_M_PREFIX);
    m_add_m_prefix.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
    m_panelhost.SetCurrent(&codeGeneration);
//}}WTLBUILDER_POST_CREATION
    CenterWindow();
    DefineLayout();

    return TRUE;
}

LRESULT COptionsDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    EndDialog(wID);
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
    return 0;
}

void COptionsDlg::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void COptionsDlg::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
//}}WTLBUILDER_INITLAYOUT
    //SetScrollSize(_minClientSize);
}

LRESULT COptionsDlg::OnListBoxChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    return 0;
}

LRESULT COptionsDlg::OnM_Prefix(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    int ch=m_add_m_prefix.GetCheck();
    PostEvent(evCfgSetBOOLVal, _T("Code Generation"), _T("m_Prefix"), ch == BST_CHECKED ? TRUE: FALSE);

    return 0;
}