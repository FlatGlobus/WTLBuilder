// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "Register.h"
#include "formtype.h"
//////////////////////////////////////////////////////////////////////////
LRESULT CFormType::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_images.Create(24,24,TRUE,0,1);

    //m_toolTip.Create(m_hWnd);
//{{WTLBUILDER_MEMBER_CREATION
    m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_T("MS Sans Serif"));
    SetFont((HFONT)m_formFont);
    ModifyStyle(GetStyle(),WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU);
    ResizeClient(476,401);
    SetWindowText(_T("New Form"));

    m_panel1.Create(m_hWnd,CRect(0,0,476,357),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT,IDC_CFORMTYPE_PANEL1);
    m_panel1.SetFont((HFONT)m_formFont);
    m_panel1.SetInnerBorder(0);
    m_panel1.SetOuterBorder(BDR_RAISEDOUTER);
    m_panel1.SetEdgeType(BF_RECT);
    m_panel1.SetBkColor(GetSysColor(COLOR_BTNFACE));
    m_panel1.SetTextColor(GetSysColor(COLOR_BTNTEXT));
    m_panel1.SetHorizTextAlign(DT_CENTER);
    m_panel1.SetVertTextAlign(DT_VCENTER);
    m_panel1.SetSingleLine(true);

    m_formsList.Create(m_panel1,CRect(10,34,466,247),NULL,WS_CHILD|WS_VISIBLE|WS_GROUP|WS_TABSTOP|LVS_LIST|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_SORTASCENDING|LVS_AUTOARRANGE|LVS_ALIGNTOP,WS_EX_CLIENTEDGE,IDC_FORMS_LIST);
    m_formsList.SetFont((HFONT)m_formFont);
    m_formsList.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT,0);

    m_static6.Create(m_panel1,CRect(10,10,88,24),_T("Form Templates"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CFORMTYPE_STATIC6);
    m_static6.SetFont((HFONT)m_formFont);

    m_panel8.Create(m_hWnd,CRect(0,358,476,401),NULL,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT,IDC_CFORMTYPE_PANEL8);
    m_panel8.SetFont((HFONT)m_formFont);
    m_panel8.SetInnerBorder(BDR_RAISEDINNER);
    m_panel8.SetOuterBorder(0);
    m_panel8.SetEdgeType(BF_RECT);
    m_panel8.SetBkColor(GetSysColor(COLOR_BTNFACE));
    m_panel8.SetTextColor(GetSysColor(COLOR_BTNTEXT));
    m_panel8.SetHorizTextAlign(DT_CENTER);
    m_panel8.SetVertTextAlign(DT_VCENTER);
    m_panel8.SetSingleLine(true);

    m_create.Create(m_panel8,CRect(308,10,382,32),_T("C&reate"),WS_CHILD|WS_VISIBLE|WS_DISABLED|WS_TABSTOP|BS_DEFPUSHBUTTON|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDOK);
    m_create.SetFont((HFONT)m_formFont);

    m_cancel.Create(m_panel8,CRect(392,10,466,32),_T("&Cancel"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,IDCANCEL);
    m_cancel.SetFont((HFONT)m_formFont);

    m_static11.Create(m_panel1,CRect(12,263,55,277),_T("Location:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CFORMTYPE_STATIC11);
    m_static11.SetFont((HFONT)m_formFont);

    m_path.Create(m_panel1,CRect(77,259,386,281),_T(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CLIENTEDGE,IDC_PATH_EDIT);
    m_path.SetFont((HFONT)m_formFont);

    m_browse.Create(m_panel1,CRect(393,259,467,281),_T("&Browse..."),WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_CENTER|BS_VCENTER,0,ID_BROWSE);
    m_browse.SetFont((HFONT)m_formFont);

    m_static14.Create(m_panel1,CRect(10,327,67,341),_T("Class name:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_CFORMTYPE_STATIC14);
    m_static14.SetFont((HFONT)m_formFont);

    m_name.Create(m_panel1,CRect(77,323,386,345),_T(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CLIENTEDGE,IDC_CLASS_NAME_EDIT);
    m_name.SetFont((HFONT)m_formFont);

    m_buttonst19.Create(m_panel1,CRect(408,11,428,31),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_DIALOGIMPL1_BUTTONST19);
    m_buttonst19.SetFont((HFONT)m_formFont);
    m_buttonst19.SetFlat(true);
    m_buttonst19.SetAlign(CButtonST::ST_ALIGN_HORIZ);
    m_buttonst19.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
    m_buttonst19.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));

    m_buttonst20.Create(m_panel1,CRect(438,11,458,31),_T(""),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,0,IDC_DIALOGIMPL1_BUTTONST20);
    m_buttonst20.SetFont((HFONT)m_formFont);
    m_buttonst20.SetFlat(true);
    m_buttonst20.SetAlign(CButtonST::ST_ALIGN_HORIZ);
    m_buttonst20.SetColor(CButtonST::BTNST_COLOR_BK_IN,GetSysColor(COLOR_BTNFACE));
    m_buttonst20.SetColor(CButtonST::BTNST_COLOR_BK_OUT,GetSysColor(COLOR_BTNFACE));

    m_static21.Create(m_panel1,CRect(12,294,60,308),_T("File name:"),WS_CHILD|WS_VISIBLE|SS_LEFT,0,IDC_DIALOGIMPL1_STATIC21);
    m_static21.SetFont((HFONT)m_formFont);

    m_filename.Create(m_panel1,CRect(77,291,386,313),_T(""),WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CLIENTEDGE,IDC_FILE_NAME_EDIT);
    m_filename.SetFont((HFONT)m_formFont);

//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
    m_path.SetWindowPos(m_formsList,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_browse.SetWindowPos(m_path,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_filename.SetWindowPos(m_browse,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_name.SetWindowPos(m_filename,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_create.SetWindowPos(m_name,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_cancel.SetWindowPos(m_create,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_buttonst19.SetWindowPos(m_cancel,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    m_buttonst20.SetWindowPos(m_buttonst19,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
//}}WTLBUILDER_TABSTOP

    m_formsList.SetImageList(m_images,LVSIL_SMALL);
    
    CenterWindow(GetDesktopWindow());
    FillTemplates();

    return TRUE;
}

LRESULT CFormType::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if(wID==IDOK)
    {
        int idx=m_formsList.GetSelectedIndex();
        if(idx!=-1 && idx < (int)tmpList.GetSize())
            componentType=tmpList[(int)m_formsList.GetItemData(idx)];
        
        m_name.GetWindowText(formName);
    }
    EndDialog(wID);
    return 0;
}

void CFormType::FillTemplates(LPCTSTR _name,LPCTSTR _page,HBITMAP _bitmap,int type)
{
    if((type & TypeForm) == TypeForm)
    {
        int idx=m_formsList.GetImageList(LVSIL_SMALL).Add(_bitmap,RGB(192,192,192));
        m_formsList.AddItem(m_formsList.GetItemCount(),0,_name,idx);
    }
}

void CFormType::FillTemplates()
{
    if(templatePath.IsEmpty())
    {
        templatePath=(LPCSTR)CPath::GetAppPath();
        templatePath+=_T("Template\\");
    }
    tmpList.RemoveAll();
    CPath::GetAllFilesFromFolder(templatePath,TRUE,tmpList);//,"*.wff");
    if(tmpList.GetSize())
    {
        //HBITMAP defImage=AtlLoadBitmap();
        //m_listviewctrl0.GetImageList(LVSIL_SMALL).Add(image,RGB(192,192,192));
        
        for(int i=0; i < tmpList.GetSize();i++)
        {
            CPath fileName(tmpList[i]);
            if(fileName.GetExt()==_T("wff"))
            {
                CPath imageFile = fileName;
                imageFile.SetExt(_T("bmp"));
                if(imageFile.ExistFile())
                {
                    HBITMAP image=(HBITMAP)LoadImage(NULL,imageFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                    if(image)
                    {
                        m_formsList.GetImageList(LVSIL_SMALL).Add(image,RGB(192,192,192));
                        ::DeleteObject(image);
                    }
                }
                else
                {
                    imageFile.SetExt(_T("ico"));
                    HICON image;
                    if(imageFile.ExistFile())
                        image=(HICON)LoadImage(NULL,imageFile,IMAGE_ICON,0,0,LR_LOADFROMFILE);
                    else
                        image=AtlLoadIcon(IDI_DEFAULT);
                    m_formsList.GetImageList(LVSIL_SMALL).AddIcon(image);
                    ::DeleteObject(image);
                }
                int idx=m_formsList.GetItemCount();
                m_formsList.AddItem(m_formsList.GetItemCount(),0,fileName.GetTitle(),idx);
                m_formsList.SetItemData(idx,i);
            }
        }
        m_formsList.SelectItem(0);
        componentType = tmpList[m_formsList.GetItemData(0)];
    }
}

LRESULT CFormType::OnItemClick(WPARAM,LPNMHDR,BOOL &)
{
    int idx=m_formsList.GetSelectedIndex();
    if(idx!=-1 && idx < (int)tmpList.GetSize())
        componentType=tmpList[m_formsList.GetItemData(idx)];
    CheckData();
    return NULL;
}

CString CFormType::ShowBrowseDlg()
{
    TCHAR path[MAX_PATH];
    memset(path, 0, MAX_PATH);
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = _T("Folder Location");
    bi.hwndOwner = (HWND)m_hWnd;
    bi.ulFlags = BIF_NEWDIALOGSTYLE|BIF_RETURNONLYFSDIRS;

    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
    if ( pidl != 0 )
    {
        // get the name of the folder
        SHGetPathFromIDList ( pidl, path );
        // free memory used
        IMalloc * imalloc = 0;
        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
        {
            imalloc->Free ( pidl );
            imalloc->Release ( );
        }
    }
    return CString(path);
}

LRESULT CFormType::OnBrowse(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    location = ShowBrowseDlg();
    m_path.SetWindowText(location);
    CheckData();
    return NULL;
}

LRESULT CFormType::OnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    if(wID == IDC_PATH_EDIT && m_path.IsWindow())
        m_path.GetWindowText(location);

    if(wID == IDC_CLASS_NAME_EDIT && m_name.IsWindow())
    {
        m_name.GetWindowText(formName);
        CreateFileName();
    }

    if(wID == IDC_FILE_NAME_EDIT && m_filename.IsWindow())
        m_filename.GetWindowText(filename);
    
    CheckData();
    return NULL;
}

CString CFormType::GetLocation()
{
    return location;
}

CString CFormType::GetFormName()
{
    return formName;
}

CString CFormType::GetTemplatePath()
{
    return templatePath;
}

CString CFormType::GetFileName()
{
    return filename;
}

CString CFormType::GetComponentType()
{
    return componentType;
}

BOOL CFormType::CheckData() 
{
    if(location.IsEmpty()==TRUE || formName.IsEmpty()==TRUE || componentType.IsEmpty()==TRUE || filename.IsEmpty() == TRUE)
    {
        m_create.EnableWindow(FALSE);
        return FALSE;
    }

    CPath temp(location);
    if(temp.ExistLocation() == FALSE)
    {
        m_create.EnableWindow(FALSE);
        return FALSE;
    }

    m_create.EnableWindow();

    return TRUE;
}

void CFormType::CreateFileName()
{
    //if()
    //formName

}