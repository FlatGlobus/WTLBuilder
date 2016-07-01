//////////////////////////////////////////////////////////////////////////
#pragma once

#include "LayoutMgr.h"
#include <atlscrl.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef ATL::CFrameWinTraits [!CLASSNAME]WinTraits;
//}}WTLBUILDER_WINDOW_STYLE
class [!CLASSNAME]:public CFrameWindowImpl<[!CLASSNAME],CWindow,[!CLASSNAME]WinTraits>,
	public CUpdateUI<[!CLASSNAME]>,public CScrollImpl<[!CLASSNAME]>,
	public LayoutMgr<[!CLASSNAME]>,public CMessageFilter, public CIdleHandler
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
	typedef CFrameWindowImpl<[!CLASSNAME], CWindow, [!CLASSNAME]WinTraits>	baseClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_FRAME_WND_CLASS(NULL, NULL)
//}}WTLBUILDER_WINCLASS_DECLARATION

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP([!CLASSNAME])
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<[!CLASSNAME]>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<[!CLASSNAME]>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//{{WTLBUILDER_MSG_MAP
//}}WTLBUILDER_MSG_MAP
		CHAIN_MSG_MAP(CUpdateUI<[!CLASSNAME]>)
		CHAIN_MSG_MAP(baseClass)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	[!CLASSNAME](void);
	~[!CLASSNAME](void);
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
