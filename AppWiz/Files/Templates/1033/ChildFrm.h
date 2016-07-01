// [!output WTL_CHILD_FRAME_FILE].h : interface of the [!output WTL_CHILD_FRAME_CLASS] class
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
typedef ATL::CMDIChildWinTraits [!output WTL_CHILD_FRAME_CLASS]WinTraits;
//}}WTLBUILDER_WINDOW_STYLE

class [!output WTL_CHILD_FRAME_CLASS] : public [!output WTL_CHILD_FRAME_BASE_CLASS]<[!output WTL_CHILD_FRAME_CLASS], CMDIWindow, [!output WTL_CHILD_FRAME_CLASS]WinTraits>,
		public CScrollImpl<[!output WTL_CHILD_FRAME_CLASS]>,public LayoutMgr<[!output WTL_CHILD_FRAME_CLASS]>
//{{WTLBUILDER_BASE_CLASS
//}}WTLBUILDER_BASE_CLASS
{
	CToolTipCtrl	m_toolTip;
//{{WTLBUILDER_MEMBER_DECLARATION
//}}WTLBUILDER_MEMBER_DECLARATION

	void InitLayout(void);
	virtual void DefineLayout();
	virtual void DoPaint(CDCHandle /*dc*/);
public:
	virtual void GetOffset(LPPOINT offset);
	virtual void GetDialogRect(LPRECT r);
	static const UINT _controlsToClip[];

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MDICHILD)
//}}WTLBUILDER_WINCLASS_DECLARATION

[!if WTL_USE_VIEW]
	[!output WTL_VIEW_CLASS] m_view;

[!endif]
	virtual void OnFinalMessage(HWND /*hWnd*/);

	typedef [!output WTL_CHILD_FRAME_BASE_CLASS]<[!output WTL_CHILD_FRAME_CLASS], CMDIWindow, [!output WTL_CHILD_FRAME_CLASS]WinTraits> _baseClass;

	BEGIN_MSG_MAP([!output WTL_CHILD_FRAME_CLASS])
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_FORWARDMSG, OnForwardMsg)
		CHAIN_MSG_MAP(_baseClass)
	END_MSG_MAP()

	[!output WTL_CHILD_FRAME_CLASS](void);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnForwardMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
};
