//////////////////////////////////////////////////////////////////////////
#pragma once 

#include "LayoutMgr.h"
#include <atlscrl.h>

//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
typedef ATL::CControlWinTraits [!CLASSNAME]WinTraits;
//}}WTLBUILDER_WINDOW_STYLE

class [!CLASSNAME]:public CWindowImpl<[!CLASSNAME],CWindow,[!CLASSNAME]WinTraits>,
	public CScrollImpl<[!CLASSNAME]>,public LayoutMgr<[!CLASSNAME]>
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
	typedef CWindowImpl<[!CLASSNAME], CWindow, [!CLASSNAME]WinTraits>	baseClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
	DECLARE_WND_CLASS(NULL)
//}}WTLBUILDER_WINCLASS_DECLARATION

	BOOL PreTranslateMessage(MSG* pMsg);	

	BEGIN_MSG_MAP([!CLASSNAME])
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<[!CLASSNAME]>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<[!CLASSNAME]>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	[!CLASSNAME](void);

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
