#include "StdAfx.h"
#include "OptionsDlg.h"
///////////////////////////////////////////////////////////////////////////////
const UINT [!CLASSNAME]::_controlsToClip[] =
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
    ResizeClient(602,441);
    SetWindowText(_T("Options"));

    m_ok.Create(m_hWnd,CRect(433,410,507,432),_T("OK"),WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
    m_ok.SetFont((HFONT)m_formFont);

    m_cancel.Create(m_hWnd,CRect(517,410,591,432),_T("Cancel"),WS_CHILD|WS_VISIBLE|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
    m_cancel.SetFont((HFONT)m_formFont);

    m_optListbox.Create(m_hWnd,CRect(8,8,192,396),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP,WS_EX_CLIENTEDGE,IDC_COPTIONSDLG_LISTBOX8);
    m_optListbox.SetFont((HFONT)m_formFont);
    m_optListbox.SetItemHeight(0,13);
    m_optListbox.SetHorizontalExtent(40);

    m_panelhost.Create(m_hWnd,CRect(200,8,594,396),NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP,0,IDC_COPTIONSDLG_PANELHOST9);
    m_panelhost.SetFont((HFONT)m_formFont);
    m_panelhost.SetInnerBorder(0);
    m_panelhost.SetOuterBorder(0);
    m_panelhost.SetTheme(TRUE);
    m_panelhost.SetBkColor(RGB(0x00,0x00,0x00));

//}}WTLBUILDER_MEMBER_CREATION
//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION
    CenterWindow();
    DefineLayout();

    m_optionsTree.InsertItem(TVIF_TEXT,_T("Item"),0,0,0,0,(LPARAM)&m_panel6,NULL,NULL);

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

LRESULT COptionsDlg::OnSelchangedOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
    if(IDC_OPTIONSDLG_OPTIONSTREE==idCtrl)
    {
        HTREEITEM hCurrent = m_optionsTree.get_SelectedItem();
        if(hCurrent)
        {
            CPanel *panel=static_cast<CPanel *>((void*)m_optionsTree.GetItemData(hCurrent));
            if(panel)
                m_pages.SetCurrent(panel);
        }
    }
    return 0;
}

LRESULT COptionsDlg::OnSelchangingOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
    if(IDC_OPTIONSDLG_OPTIONSTREE==idCtrl)
    {
        HTREEITEM hCurrent = m_optionsTree.get_SelectedItem();
        if(hCurrent)
        {
            CPanel *panel=static_cast<CPanel *>((void*)m_optionsTree.GetItemData(hCurrent));
            if(panel)
                m_pages.SetCurrent(panel);
        }
    }
    return 0;
}
