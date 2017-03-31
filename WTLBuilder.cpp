// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "resource.h"
#include "WTLBuilderView.h"
#include "aboutdlg.h"
#include "MainFrm.h"
#include "ModuleLoader.h"
#include "Path.h"
#include "cgfiltyp.h"

CAppModule _Module;

BOOL isMSXMLInstalled();
void RegisterWFF();

static CModuleLoader modules;

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

int Run(LPTSTR lpstrCmdLine, int nCmdShow = SW_SHOWDEFAULT)
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);

    CMainFrame wndMain;
    CRect rc(0,0,GetSystemMetrics(SM_CXSCREEN),wndMain.CalcWindowSize());//127
    if(wndMain.CreateEx(NULL,rc) == NULL)
    {
        ATLTRACE(_T("Main window creation failed!\n"));
        return 0;
    }

    CreateBridge();
    StartCommandTimer();
    
    _Module.Lock();		
    wndMain.ShowWindow(nCmdShow);
    modules.Load();
    SendEvent(evLoadPackages);
    //Package->LoadPackages();
    SendEvent(evStartingUp);
    SendEvent(evGetComponentInfo,TypeComponent);//get only controls
    CPath initFileName(CPath::GetAppPath());
    initFileName.SetTitle(_T("WTLbuilder"));
    initFileName.SetExt(_T("js"));

    if(lpstrCmdLine != NULL && strlen(lpstrCmdLine) != 0)
        wndMain.LoadFormFromFile(lpstrCmdLine);
    int nRet = theLoop.Run();

    DestroyBridge();

    _Module.RemoveMessageLoop();
    modules.Free();
    return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    //if(isMSXMLInstalled()==FALSE)
    //    return FALSE;

    HRESULT hRes = ::CoInitializeEx(NULL,COINIT_APARTMENTTHREADED /*COINIT_MULTITHREADED*/);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ATLASSERT(SUCCEEDED(hRes));
    
    // this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
    ::DefWindowProc(NULL, 0, 0, 0L);

    AtlInitCommonControls(ICC_WIN95_CLASSES|ICC_COOL_CLASSES|ICC_DATE_CLASSES|
        ICC_INTERNET_CLASSES|ICC_PAGESCROLLER_CLASS|ICC_NATIVEFNTCTL_CLASS|ICC_USEREX_CLASSES| ICC_TAB_CLASSES);	// add flags to support other controls

    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));

    ULONG uToken = 0;
    Gdiplus::GdiplusStartupInput gsi;
    Gdiplus::GdiplusStartupOutput gso;
    Gdiplus::GdiplusStartup(&uToken, &gsi, &gso);

    TCHAR szTokens[] = _T("-/");

    int nRet = 0;
    BOOL bRun = TRUE;
    LPCTSTR lpszToken = FindOneOf(lpstrCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("unreg"))==0)
        {
            bRun = FALSE;
            break;
        }
        if (lstrcmpi(lpszToken, _T("reg"))==0)
        {
            bRun = FALSE;
            RegisterWFF();
            break;
        }
        lpszToken = FindOneOf(lpszToken, szTokens);
    }
    
    if(bRun)
        nRet = Run(lpstrCmdLine, nCmdShow);

    _Module.Term();

    Gdiplus::GdiplusShutdown(uToken);

    ::CoUninitialize();
    return nRet;
}

BOOL isMSXMLInstalled()
{
    try
    {
        HKEY hKey;
        DWORD retCode;
        _TCHAR szTemp[MAX_PATH];
        DWORD dwLen;
        retCode = RegOpenKeyEx(HKEY_CLASSES_ROOT,
            _T("CLSID\\{88d969c0-f192-11d4-a65f-0040963251e5}\\InProcServer32"), 
            0, 
            KEY_QUERY_VALUE, 
            &hKey);
        if (retCode != ERROR_SUCCESS)
            return FALSE;
        retCode = RegQueryValueEx(hKey, _T(""), NULL, NULL,
            (LPBYTE)szTemp, &(dwLen = sizeof(szTemp)));
        if (retCode != ERROR_SUCCESS)
            return FALSE;

        RegCloseKey(hKey);
        
        double dVer;
        int i;
        
        for (i = (int)_tcslen(szTemp); i >= 0; --i)
        {
            if (szTemp[i] ==_T('\\'))
                break;
        }
        
        if (_stscanf_s(szTemp + i + 1, _T("msxml%lf"), &dVer) == 0 || dVer< 4.0)
        {
            MessageBox(NULL,_T("Error: MSXML 4.0 is not installed."),_T("WTLBuilder"),MB_OK|MB_ICONSTOP);
                return FALSE;
        }
        else
            return TRUE;
    }
    catch(...)
    {
    }
    return FALSE;
}


void RegisterWFF()
{

    CGCFileTypeAccess fta;

    // get full file path to program executable file
    TCHAR	szProgPath[MAX_PATH * 2];
    ::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));

    CString csTempText;

    fta.SetExtension(_T("wff"));

    // just pass file path in quotes on command line
    csTempText  = szProgPath;
    csTempText += _T(" \"%1\"");
    fta.SetShellOpenCommand(csTempText);
    fta.SetDocumentShellOpenCommand(csTempText);
    fta.SetDocumentClassName(_T("WTLBuilder.Document"));
    fta.SetDocumentDescription(_T("WTLBuilder Form File"));

    // use first icon in program
    csTempText  = szProgPath;
    csTempText += ",0";
    fta.SetDocumentDefaultIcon(csTempText);

    // set the necessary registry entries	
    fta.RegSetAllInfo();
}