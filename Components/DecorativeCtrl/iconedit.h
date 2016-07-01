/** @file iconedit.h
 *
 *	@brief Definition of iconedit.h
 *
 *	@author JaeWook Choi
 *	@version 1.02
 *
 *	<b><i>This software is provided "as is" without express or implied warranty. Use it at your own risk!</i></b>
 *
 *	1.02 -	a)	Added UnsubclassWindow()
 *
 *			b)	It draws disabled icon when the edit control is disabled
 *
 *			c)	It works for multi-line Edit control (ES_MULTILINE style) even though this control wasn't intended to be used in that way
 *
 *  1.01 -	a)	Removed EM_GETRECT and EM_GETMARGINS message handlers (default handler get called)
 *				So now it works well with CToolTipCtrl::AdjustRect()
 *
 *			b)	Changed EM_SETRECT, EM_SETRECTNP and EM_SETMARGINS handlers and if you use these messages
 *				then it is your responsibility to reserve space for icon drawing
 *				(if it sets the margin less than the minimum (::GetSystemMetrics(SM_CXSMICON)) required
 *				to draw icon it will use the minimum instead)
 *
 *			c)	Added GetIconMargins() function
 *
 *	1.0	-		Initial Release
 *
 */

#if !defined(_ICONEDIT_H_INCLUDED_)

#pragma once

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLAPP_H__
	#error iconedit.h requires atlapp.h to be included first
#endif

#ifndef __ATLCTRLS_H__
	#error iconedit.h requires atlctrls.h to be included first
#endif

namespace codeproject
{

/**
 *	@brief CIconEditT class.
 *
 */
template<class TBASE = CEdit>
class CIconEditT : public CWindowImpl<CIconEditT, TBASE>
{
	typedef CWindowImpl<CIconEditT, TBASE>	baseClass;

public:
	BEGIN_MSG_MAP(CIconEditT)
		MESSAGE_HANDLER(WM_NCHITTEST,	OnNcHitTest)
		MESSAGE_HANDLER(WM_MOUSEMOVE,	OnMouseMove)
		MESSAGE_HANDLER(WM_GETDLGCODE,	OnGetDlgCode)
		MESSAGE_HANDLER(WM_PAINT,		OnPaint)
		MESSAGE_HANDLER(EM_SETMARGINS,	OnSetMargins)
		MESSAGE_HANDLER(EM_SETRECT,		OnSetRect)
		MESSAGE_HANDLER(EM_SETRECTNP,	OnSetRectNP)
	END_MSG_MAP()

protected:
	HICON m_hIcon;
	RECT m_rcIcon;
	SIZE m_szMargin;
	BOOL m_bShowIcon;

public:
	// c'tor
	CIconEditT() : m_hIcon(NULL), m_bShowIcon(TRUE)
	{
		m_szMargin.cx = 2;
		m_szMargin.cy = 0;

		UpdateIconRect();
	}

	// d'tor
	virtual ~CIconEditT()
	{
		if(m_hIcon)
		{
			::DestroyIcon(m_hIcon);
			m_hIcon = NULL;
		}
	}

	// properties
	HICON SetIcon(ATL::_U_STRINGorID icon, HINSTANCE hResourceInstance = NULL)
	{
		HICON hIconOld = m_hIcon;

		m_hIcon = (HICON)::LoadImage(
			(NULL == hResourceInstance) ? _Module.GetResourceInstance() : hResourceInstance,
			icon.m_lpstr,
			IMAGE_ICON,
			::GetSystemMetrics(SM_CXSMICON),
			::GetSystemMetrics(SM_CYSMICON),
			LR_DEFAULTCOLOR);

		if(m_bShowIcon && m_hWnd)
			InvalidateRect(&m_rcIcon);

		return hIconOld;
	}

	HICON SetIcon(HICON hIcon)
	{
		HICON hIconOld = m_hIcon;

		m_hIcon = hIcon;

		if(m_bShowIcon && m_hWnd)
			InvalidateRect(&m_rcIcon);

		return hIconOld;
	}

	void SetIconMargins(USHORT cx, USHORT cy = 0)
	{
		if(m_hWnd && cx != m_szMargin.cx)
		{
			UINT nLMargin = LOWORD((DWORD)DefWindowProc(EM_GETMARGINS, 0, 0L));
			nLMargin -= 2 * (m_szMargin.cx - cx);
			const UINT cxSmallIcon = ::GetSystemMetrics(SM_CXSMICON);
			if(cxSmallIcon > nLMargin)
			{
				ATLTRACE(_T("\nCIconEditT::SetIconMargins(): the left margin is changed to %d in order to reserve the minimum space for drawing icon.\n\n"), cxSmallIcon);
				nLMargin = cxSmallIcon;
				cx = 0;
			}

			DefWindowProc(EM_SETMARGINS, EC_LEFTMARGIN, MAKELONG(nLMargin, 0));
		}

		m_szMargin.cx = cx;
		m_szMargin.cy = cy;

		UpdateIconRect();

		if(m_bShowIcon && m_hWnd)
			InvalidateRect(&m_rcIcon);
	}

	void SetIconMargins(LPSIZE pszMargin)
	{
		SetIconMargins((USHORT)pszMargin->cx, (USHORT)pszMargin->cy);
	}

	void GetIconMargins(LPSIZE pszMargin)
	{
		if(NULL == pszMargin)
			return;

		pszMargin->cx = m_szMargin.cx;
		pszMargin->cy = m_szMargin.cy;
	}

	void ShowIcon(BOOL bShow = TRUE)
	{
		m_bShowIcon = bShow;

		if(m_hWnd)
			InvalidateRect(&m_rcIcon);
	}

	// operations
	BOOL SubclassWindow(HWND hWnd)
	{
		UINT nDefLMargin = LOWORD((DWORD)::SendMessage(hWnd, EM_GETMARGINS, 0, 0L));
		::SendMessage(hWnd, EM_SETMARGINS, EC_LEFTMARGIN, MAKELONG(nDefLMargin + (::GetSystemMetrics(SM_CXSMICON) + 2 * m_szMargin.cx), 0));

		return baseClass::SubclassWindow(hWnd);
	}

	HWND UnsubclassWindow(BOOL bForce = FALSE)
	{
		HWND hWnd = baseClass::UnsubclassWindow(bForce);

		UINT nDefLMargin = LOWORD((DWORD)::SendMessage(hWnd, EM_GETMARGINS, 0, 0L));
		::SendMessage(hWnd, EM_SETMARGINS, EC_LEFTMARGIN, MAKELONG(nDefLMargin - (::GetSystemMetrics(SM_CXSMICON) + 2 * m_szMargin.cx), 0));

		return hWnd;
	}

	// Implementations
protected:
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(WM_NCHITTEST == uMsg);
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);

		if(HTCLIENT == lRes)
		{
			POINT ptHit = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			ScreenToClient(&ptHit);

			const int nMargin = (m_rcIcon.right - m_rcIcon.left) + ( 2 * m_szMargin.cx );
			if(nMargin > ptHit.x)
				return HTBORDER;
		}

		return lRes;
	}

	// ADDED! This handler is required only for the edit control in WinXP common control version 6
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(WM_MOUSEMOVE == uMsg);
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);

		if( (MK_LBUTTON & wParam ) && m_bShowIcon && m_hIcon)
			InvalidateRect(&m_rcIcon);

		return lRes;
	}

	LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(WM_GETDLGCODE == uMsg);
		LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);

		if(m_bShowIcon && m_hIcon)
			InvalidateRect(&m_rcIcon);

		return lRes;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(WM_PAINT == uMsg);
		if(m_bShowIcon && m_hIcon)
		{
			RECT rcUpdate;
			GetUpdateRect(&rcUpdate);
			LRESULT lRes = (LRESULT)TRUE;
			if(!::EqualRect(&rcUpdate, &m_rcIcon))
			{
				// if the rectangle area required to be updated is bigger than m_rcIcon
				// let the default handler handle it first
				lRes = DefWindowProc(uMsg, wParam, lParam);

				// then invalidate only the m_rcIcon area again in order to draw our icon in it
				InvalidateRect(&m_rcIcon);
			}

			CPaintDC dc(m_hWnd);
			DrawIcon(dc);

			return lRes;
		}

		return DefWindowProc(uMsg, wParam, lParam);
	}

	LRESULT OnSetMargins(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(EM_SETMARGINS == uMsg);

		if(EC_LEFTMARGIN | wParam)
		{
			UINT nLMargin = LOWORD(lParam), nRMargin = LOWORD(lParam);
			const UINT cxIconMargin = ::GetSystemMetrics(SM_CXSMICON) + 2 * m_szMargin.cx;
			if(cxIconMargin > nLMargin)
			{
				ATLTRACE(_T("\nCIconEditT::OnSetMargins(): the left margin is changed to %d in order to reserve the space for drawing icon.\n\n"), cxIconMargin);
				nLMargin = cxIconMargin;
			}

			lParam = (LPARAM)MAKELONG(nLMargin, nRMargin);
		}

		return DefWindowProc(uMsg, wParam, lParam);
	}

	LRESULT OnSetRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(EM_SETRECT == uMsg);

		LPRECT prcFmt = (LPRECT)lParam;
		const UINT cxIconMargin = ::GetSystemMetrics(SM_CXSMICON) + 2 * m_szMargin.cx;
		if(cxIconMargin > (UINT)prcFmt->left)
		{
			ATLTRACE(_T("\nCIconEditT::OnSetRect(): the left of formatting rectangle is changed to %d in order to reserve the space for drawing icon.\n\n"), cxIconMargin);
			prcFmt->left = cxIconMargin;
		}

		return DefWindowProc(uMsg, wParam, lParam);
	}

	LRESULT OnSetRectNP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &/*bHandled*/)
	{
		ATLASSERT(EM_SETRECTNP == uMsg);

		LPRECT prcFmt = (LPRECT)lParam;
		const UINT cxIconMargin = ::GetSystemMetrics(SM_CXSMICON) + 2 * m_szMargin.cx;
		if(cxIconMargin > (UINT)prcFmt->left)
		{
			ATLTRACE(_T("\nCIconEditT::OnSetRectNP(): the left of formatting rectangle is changed to %d in order to reserve the space for drawing icon.\n\n"), cxIconMargin);
			prcFmt->left = cxIconMargin;
		}

		return DefWindowProc(uMsg, wParam, lParam);
	}

	void DrawIcon(HDC hdcClient = NULL)
	{
		CDCHandle dc;
		if(NULL != hdcClient)
			dc.Attach(hdcClient);
		else
			dc.Attach(GetDC());

		int nSaveDC = dc.SaveDC();

		// Make a mask from the icon rectangle
		dc.IntersectClipRect(&m_rcIcon);

		// obtain the appropriate HBRUSH to erase background
		HBRUSH hBrush = (HBRUSH)::SendMessage(GetParent(), WM_CTLCOLOREDIT, (WPARAM)(HDC)dc, (LPARAM)m_hWnd);
		if(NULL == hBrush)
			hBrush = (HBRUSH)::GetStockObject(WHITE_BRUSH);

		CBrush brush(hBrush);
		
		// erase background of m_rcIcon rectangle area
		//	dc.FillRect(&m_rcIcon, brush);
		
		if(m_hIcon)
		{
			if(!(ES_MULTILINE & GetStyle()) || 0 == GetFirstVisibleLine())
			{
				// draw the icon
				dc.SetBkMode(TRANSPARENT);

				if(IsWindowEnabled())
				{
					dc.DrawIconEx(
						m_rcIcon.left,
						m_rcIcon.top,
						m_hIcon,
						m_rcIcon.right - m_rcIcon.left,
						m_rcIcon.bottom - m_rcIcon.top,
						0,
						brush);
				}
				else
				{
					POINT ptIcon = { m_rcIcon.left, m_rcIcon.top };
					SIZE szIcon = { m_rcIcon.right - m_rcIcon.left, m_rcIcon.bottom - m_rcIcon.top };

					dc.DrawState(ptIcon, szIcon, m_hIcon, DSS_DISABLED);
				}
			}
		}

		dc.RestoreDC(nSaveDC);

		if(NULL != hdcClient)
			dc.Detach();
		else
			ReleaseDC(dc.Detach());
	}

	void UpdateIconRect()
	{
		m_rcIcon.left = m_szMargin.cx;
		m_rcIcon.right = m_rcIcon.left + ::GetSystemMetrics(SM_CXSMICON);
		m_rcIcon.top = m_szMargin.cy;
		m_rcIcon.bottom = m_rcIcon.top + ::GetSystemMetrics(SM_CYSMICON);
	}
};

class CIconEdit : public CIconEditT<CEdit>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_IconEdit"), GetWndClassName())
};

}	// namespace codeproject

#endif // !defined(_ICONEDIT_H_INCLUDED_)
