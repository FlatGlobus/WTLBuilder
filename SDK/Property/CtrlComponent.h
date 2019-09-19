// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __CTRLCOMPONENT_H
#define __CTRLCOMPONENT_H
//////////////////////////////////////////////////////////////////////////
class  PROPERTY_API ControlComponentBase : public Component
{
protected:
    BOOL        focus; 
    //DWORD       windowStyle;
    //DWORD       windowStyleEx;
    BOOL        visible;	
    CString     toolTip;
    BOOL        enabletoolTip;
    CString     strID;
    CFontEx	    ctrlFont;
    BOOL        useControlFont;
    //CBrushEx	bkBrush;
    CLayout		leftLayout;
    CLayout		topLayout;
    CLayout		rightLayout;
    CLayout		bottomLayout;
    CLayout		hCenterLayout;
    CLayout		vCenterLayout;
    BOOL		layout;
public:
    ControlComponentBase(LPCTSTR name);
    virtual ~ControlComponentBase();

    BEGIN_MSG_MAP(ControlComponentBase)
        MESSAGE_HANDLER(WM_CREATE,OnCreate)
        MESSAGE_HANDLER(WM_SIZE,OnSize)
        MESSAGE_HANDLER(WM_MOVE,OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_SETCTRLFONT,OnSetCtrlFont)
        MESSAGE_HANDLER(WM_GETCTRLFONT,OnGetCtrlFont)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSetCtrlFont(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetCtrlFont(UINT,WPARAM,LPARAM, BOOL& bHandled);
    virtual void InitProperty(void);
    void SetControlFont(CFontEx *font);
    //use control font or form
    void set_Font(BOOL val);
    BOOL get_Font();
    void set_Focus(BOOL val);
    BOOL get_Focus();
    void set_Visible(BOOL val);
    BOOL get_Visible();
    void set_ToolTip(CString val);
    CString get_ToolTip();
    void set_EnableToolTip(BOOL val);
    BOOL get_EnableToolTip();
    void set_ID(CString val);
    CString get_ID(void);
    virtual BOOL IsControl();
    virtual void SetBoundsRect(CRect rc);
    virtual CRect GetBoundsRect(void);
    DWORD get_InternalWindowStyle();
    void set_InternalWindowStyle(DWORD s);
    DWORD get_InternalWindowStyleEx();
    void set_InternalWindowStyleEx(DWORD s);
    //void set_Color(CColorref val);
    //CColorref get_Color();
    virtual void set_Layout(BOOL val);
    virtual BOOL get_Layout(void);
    virtual CLayout *	get_leftLayout();
    virtual CLayout	*	get_topLayout();
    virtual CLayout	*	get_rightLayout();
    virtual CLayout	*	get_bottomLayout();
    virtual CLayout	*	get_hCenterLayout();
    virtual CLayout	*	get_vCenterLayout();

    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(TabStop,(WS_TABSTOP))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Group,(WS_GROUP))

    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(HScroll,(WS_HSCROLL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(VScroll,(WS_VSCROLL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Border,(WS_BORDER))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_NOT_I(Enabled,(WS_DISABLED))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ClientEdge,(WS_EX_CLIENTEDGE))

    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(Transparent,(WS_EX_TRANSPARENT))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(AcceptFiles,(WS_EX_ACCEPTFILES))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ControlParent,(WS_EX_CONTROLPARENT))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(ClipSiblings,(WS_CLIPSIBLINGS))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(ClipChildren,(WS_CLIPCHILDREN))
};
//////////////////////////////////////////////////////////////////////////
template <class T>
class ControlComponent: public ControlComponentBase
{
public:
    typedef ControlComponent<T> thisclass;

    ControlComponent(LPTSTR _name):ControlComponentBase(_name)
    {
    }

    virtual ~ControlComponent()
    {
        if(::IsWindow((HWND)GetHandle()))
            static_cast<T*>(this)->DestroyWindow();	
    }

    BEGIN_MSG_MAP(thisclass)
        CHAIN_MSG_MAP(ControlComponentBase)
    END_MSG_MAP()

    virtual HANDLE GetHandle(void)
    {
        return static_cast<T*>(this)->m_hWnd;
    }
};
PROPERTY_API BOOL ModifyWndStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = SWP_NOSIZE | SWP_NOMOVE);
PROPERTY_API BOOL ModifyWndStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = SWP_NOSIZE | SWP_NOMOVE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

