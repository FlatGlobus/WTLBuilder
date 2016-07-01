// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PACKAGE_DLG_H
#define __PACKAGE_DLG_H
/////////////////////////////////////////////////////////////////////////////////////////
#include "Package.h"
class CPackageDlg : public CDialogImpl<CPackageDlg>
{
public:
	enum { IDD = IDD_PACKAGE_DLG };
	
	BEGIN_MSG_MAP(CPackageDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		END_MSG_MAP()
		
		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(GetParent());
		packageList.Attach(GetDlgItem(IDC_LIST1));
		FillPackages();	
		return TRUE;
	}
	
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}

	void FillPackages(void)
	{
		for(int i=0; i < packages->GetSize(); i++)
		packageList.InsertItem(0,(*packages)[i].GetName());
	}

	CListViewCtrl packageList;
	CPackages *   packages;
};

/////////////////////////////////////////////////////////////////////////////////////////	
#endif