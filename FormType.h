// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __FORMTYPE__H
#define __FORMTYPE__H
//////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "Path.h"

//{{WTLBUILDER_INCLUDE_DECLARATION
#include "Panel.h"
#include "ButtonST.h"
//}}WTLBUILDER_INCLUDE_DECLARATION


//{{WTLBUILDER_CONTROL_ID_DECLARATION
#define    IDC_CFORMTYPE_PANEL1    1001
#define    IDC_FORMS_LIST    1000
#define    IDC_CFORMTYPE_STATIC6    1006
#define    IDC_CFORMTYPE_PANEL8    1008
#define    IDC_CFORMTYPE_STATIC11    1011
#define    IDC_PATH_EDIT    1012
#define    ID_BROWSE    1013
#define    IDC_CFORMTYPE_STATIC14    1014
#define    IDC_CLASS_NAME_EDIT    1016
#define    IDC_DIALOGIMPL1_BUTTONST19    1019
#define    IDC_DIALOGIMPL1_BUTTONST20    1020
#define    IDC_DIALOGIMPL1_STATIC21    1021
#define    IDC_FILE_NAME_EDIT    1022
//}}WTLBUILDER_CONTROL_ID_DECLARATION

class CFormType:public CDialogImpl<CFormType>
{
    CToolTipCtrl    m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
    CFont    m_formFont;
    Panel::CPanel    m_panel1;
    CListViewCtrl    m_formsList;
    CStatic    m_static6;
    Panel::CPanel    m_panel8;
    CButton    m_create;
    CButton    m_cancel;
    CStatic    m_static11;
    CEdit    m_path;
    CButton    m_browse;
    CStatic    m_static14;
    CEdit    m_name;
    CButtonST    m_buttonst19;
    CButtonST    m_buttonst20;
    CStatic    m_static21;
    CEdit    m_filename;
//}}WTLBUILDER_MEMBER_DECLARATION
    CStringArray tmpList;
    CImageList    m_images;
    CString     location;
    CString     formName;
    CString     filename;

    CString     templatePath;
    CString        componentType;

    void FillTemplates(LPCTSTR _name,LPCTSTR _page,HBITMAP _bitmap,int type);
    void FillTemplates();
    CString ShowBrowseDlg();
    BOOL CheckData();
    void CreateFileName();
public:
    enum { IDD = IDD_NULL };

    BEGIN_MSG_MAP(CFormType)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        COMMAND_ID_HANDLER(ID_BROWSE, OnBrowse)
        NOTIFY_HANDLER(IDC_FORMS_LIST,NM_CLICK,OnItemClick)
        COMMAND_CODE_HANDLER(EN_CHANGE,OnChange)
        
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnItemClick(WPARAM,LPNMHDR,BOOL &);
    LRESULT OnBrowse(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    CString GetLocation();
    CString GetFormName();
    CString GetTemplatePath();
    CString GetComponentType();
    CString GetFileName();
};
//////////////////////////////////////////////////////////////////////////
#endif