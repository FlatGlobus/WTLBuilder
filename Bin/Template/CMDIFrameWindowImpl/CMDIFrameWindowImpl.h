//////////////////////////////////////////////////////////////////////////
#pragma once 

#include<LayoutMgr.h>
#include <atlscrl.h>
//{{WTLBUILDER_INCLUDE_DECLARATION
//}}WTLBUILDER_INCLUDE_DECLARATION

//{{WTLBUILDER_CONTROL_ID_DECLARATION
//}}WTLBUILDER_CONTROL_ID_DECLARATION

//{{WTLBUILDER_WINDOW_STYLE
//}}WTLBUILDER_WINDOW_STYLE
class [!CLASSNAME]:public CMDIFrameWindowImpl<[!CLASSNAME],CWindow,[!CLASSNAME]WinTraits>,
	public CScrollImpl<[!CLASSNAME]>,public LayoutMgr<[!CLASSNAME]>
//{{WTLBUILDER_BASE_CLASS
//}}WTLBUILDER_BASE_CLASS
{
	CToolTipCtrl	m_toolTip;
//	CBrush		m_bkColor;
//{{WTLBUILDER_MEMBER_DECLARATION
//}}WTLBUILDER_MEMBER_DECLARATION
	void InitLayout(void);
	virtual void DefineLayout();
public:
	virtual void GetDialogRect(LPRECT r);
	virtual void GetOffset(LPPOINT offset);
	virtual void DoPaint(CDCHandle /*dc*/);
	static const UINT _controlsToClip[];
	typedef CMDIFrameWindowImpl<[!CLASSNAME], CWindow, [!CLASSNAME]WinTraits>	thisClass;

//{{WTLBUILDER_WINCLASS_DECLARATION
//}}WTLBUILDER_WINCLASS_DECLARATION
	
	//DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg);	

	BEGIN_MSG_MAP([!CLASSNAME])
		MESSAGE_HANDLER(WM_SIZE, LayoutMgr<[!CLASSNAME]>::OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<[!CLASSNAME]>::OnEraseBackground)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
//{{WTLBUILDER_MSG_MAP
//}}WTLBUILDER_MSG_MAP
		CHAIN_MSG_MAP(thisClass)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	[!CLASSNAME](void);
	~[!CLASSNAME](void);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
//////////////////////////////////////////////////////////////////////////
