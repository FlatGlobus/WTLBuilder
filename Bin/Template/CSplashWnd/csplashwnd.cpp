#include "stdafx.h"
#include "csplashwnd.h"
//////////////////////////////////////////////////////////////////////////
[!CLASSNAME]::[!CLASSNAME](UINT nBitmapID, int nTimeout, HWND hParent)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
    m_nTimeout=nTimeout;
    m_hParent=hParent;
    // Load the bitmap
    if (!m_bmp.LoadBitmap(nBitmapID))
    {
        ATLTRACE(_T("Failed to load spash bitmap\n"));
        return;
    }
    // Get the bitmap size
    CSize size;
    if (!m_bmp.GetSize(size))
    {
        ATLTRACE(_T("Failed to get spash bitmap size\n"));
        return;
    }
    // Create the window rect (we will centre the window later)
    CRect rect(0, 0, size.cx, size.cy);
    // Create the window
    if (!Create(NULL, rect))
    {
        ATLTRACE(_T("Failed to create splash window\n"));
        return;
    }
    UpdateWindow();
}

[!CLASSNAME]::~[!CLASSNAME]()
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
}
/// Called when the window is destroyed
void [!CLASSNAME]::OnFinalMessage(HWND /*hWnd*/)
{
    delete this;
}

LRESULT [!CLASSNAME]::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
//{{WTLBUILDER_MEMBER_CREATION
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
//}}WTLBUILDER_POST_CREATION

    CenterWindow(m_hParent);
    // Set the timer
    SetTimer(DEF_TIMER_ID, m_nTimeout);
    return 0;
}

LRESULT [!CLASSNAME]::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // Draw the bmp
    CPaintDC dc(m_hWnd);

    CDC dcImage;
    if (dcImage.CreateCompatibleDC(dc.m_hDC))
    {
        CSize size;
        if (m_bmp.GetSize(size))
        {
            HBITMAP hBmpOld = dcImage.SelectBitmap(m_bmp);
            dc.BitBlt(0, 0, size.cx, size.cy, dcImage, 0, 0, SRCCOPY);
            dcImage.SelectBitmap(hBmpOld);
        }
    }

    return 0;
}

LRESULT [!CLASSNAME]::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    KillTimer(DEF_TIMER_ID);
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT [!CLASSNAME]::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // No need to paint a background
    return TRUE;
}

LRESULT [!CLASSNAME]::OnButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT [!CLASSNAME]::OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    if (wParam == VK_ESCAPE)
        PostMessage(WM_CLOSE);
    return 0;
}
