#pragma once
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "LayoutMgr.h"
#include "Panel.h"
//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define    IDC_COPTIONSDLG_LISTBOX8    1008
#define    IDC_COPTIONSDLG_PANELHOST9    1009
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class [!CLASSNAME]:public CResizableDialogImpl<[!CLASSNAME]>
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
//}}WTLBUILDER_MEMBER_DECLARATION
    void InitLayout(void);
public:
    virtual void DefineLayout();
    enum { IDD = IDD_NULL };
    static const UINT _controlsToClip[];

    typedef CResizableDialogImpl<[!CLASSNAME]> thisClass;

    BEGIN_MSG_MAP([!CLASSNAME])
        CHAIN_MSG_MAP(thisClass)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        NOTIFY_HANDLER(IDC_OPTIONSDLG_OPTIONSTREE,TVN_SELCHANGED, OnSelchangedOptionsTree)
        NOTIFY_HANDLER(IDC_OPTIONSDLG_OPTIONSTREE,TVN_SELCHANGING, OnSelchangingOptionsTree)
        REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    [!CLASSNAME](void);
    ~[!CLASSNAME](void);

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnSelchangedOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
    LRESULT OnSelchangingOptionsTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};
//////////////////////////////////////////////////////////////////////////
