// [!output WTL_VIEW_FILE].h : interface of the [!output WTL_VIEW_CLASS] class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LayoutMgr.h"
#include <atlscrl.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef ATL::CControlWinTraits [!output WTL_VIEW_CLASS]WinTraits;
//}}WTLBUILDER_WINDOW_STYLE

[!if WTL_VIEWTYPE_GENERIC || WTL_VIEWTYPE_FORM || WTL_VIEWTYPE_SCROLL]
class [!output WTL_VIEW_CLASS] : public [!output WTL_VIEW_BASE_CLASS]<[!output WTL_VIEW_CLASS]>,
[!else]
class [!output WTL_VIEW_CLASS] : public [!output WTL_VIEW_BASE_CLASS]<[!output WTL_VIEW_CLASS], [!output WTL_VIEW_BASE]>,
[!endif]
	public CScrollImpl<[!output WTL_VIEW_CLASS]>,public LayoutMgr<[!output WTL_VIEW_CLASS]>
//{{WTLBUILDER_BASE_CLASS
//}}WTLBUILDER_BASE_CLASS
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();
public:
	virtual void GetDialogRect(LPRECT r);
	virtual void GetOffset(LPPOINT offset);
	virtual void DoPaint(CDCHandle /*dc*/);
	static const UINT _controlsToClip[];

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_WND_CLASS(NULL)
//}}WTLBUILDER_WINCLASS_DECLARATION

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP([!output WTL_VIEW_CLASS])
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
[!if WTL_VIEWTYPE_GENERIC]
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
[!endif]
	END_MSG_MAP()

  [!output WTL_VIEW_CLASS](void);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
