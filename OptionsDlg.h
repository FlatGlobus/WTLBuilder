#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "LayoutMgr.h"
#include "Panel.h"
//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define    IDC_OPTLISTBOX    1008
#define    IDC_OPTPANELHOST    1009
#define    IDC_COPTIONSDLG_PANEL10    1010
#define    IDC_COPTIONSDLG_CODEGENERATION    1011
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class COptionsDlg:public CResizableDialogImpl<COptionsDlg>
//{{WTLBUILDER_BASE_CLASS
//}}WTLBUILDER_BASE_CLASS
{
    CToolTipCtrl    m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
    CFont    m_formFont;
    CButton    m_ok;
    CButton    m_cancel;
    CListBox    m_optListbox;
    Panel::CPanelHost    m_panelhost;
    Panel::CPanel    m_panel10;
    Panel::CPanel    codeGeneration;
//}}WTLBUILDER_MEMBER_DECLARATION
    void InitLayout(void);
public:
    virtual void DefineLayout();
    enum { IDD = IDD_NULL };
    static const UINT _controlsToClip[];

    typedef CResizableDialogImpl<COptionsDlg> thisClass;

    BEGIN_MSG_MAP(COptionsDlg)
        CHAIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    COptionsDlg(void);
    ~COptionsDlg(void);

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
