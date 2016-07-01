// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __FORMCOMPONENT_H
#define __FORMCOMPONENT_H
//////////////////////////////////////////////////////////////////////////
#include "_util.h"
#include "path.h"

#define IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(Name)\
inline void set_##Name(BOOL val)\
{\
    classStyle = val == TRUE ? (classStyle | (Name)): (classStyle & ~(Name));\
    SetModified();\
}\
inline BOOL get_##Name(void)\
{\
    return (classStyle & (Name))==Name;\
}
//////////////////////////////////////////////////////////////////////////
#define MAX_UNDOS 100

typedef CAtlArray<CString> UndoArray;

class Undo
{
    static size_t   max_undos;
    UndoArray       undo;
    BOOL            changed;
	BOOL            fixChanges;
public:
    Undo();
    ~Undo();
    void Add(const CString &);
    CString Get();
    void EnableUndo();
    BOOL IsModified();
    void Reset();
};
//////////////////////////////////////////////////////////////////////////
typedef CSimpleArray<UINT> UINTArray;

class CXMLDOMDocument2;

class PROPERTY_API CFormComponent:
    public CFrameWindowImpl<CFormComponent,CWindow>,
    //public CScrollImpl<CFormComponent>,
    //public LayoutMgr<CFormComponent>,
    public Component
{
protected:
	Components		components;
	CPath    		fileName;
	BOOL			enableClose;
	BOOL			showWindow;
	CCodeGenerator  codeGen;
	CFontEx			formFont;
	CString			caption;
    DWORD           classStyle;
	BOOL			visible;
	long			clientWidth;
	long			clientHeight;
	SystemColor		bkColor;
	UINTArray		_controls;
	BOOL			enableLayout;
	long			nPositions;
    CImage          formIcon;
    BOOL            fromTemplate;
    long            idBase;//для каждой формы задается базовый номер для вычисления ID контрола
    //ctrlID+idBase таким образом ID контрола становится уникальным в приложении   
	//CBrushEx		bkBrush;
    Undo            undo;
    CString			viewCtrl;
//    CString			toolBarCtrl;
//    CString			statusBarCtrl;
//    CString         menu;
	BOOL			sizeChanged;
    BOOL            showHandle;


    void ViewCtrlChanged(Component*);
    void ToolBarChanged(Component*);
    void StatusBarChanged(Component*);
    void MenuChanged(Component*);
	BOOL GenerateXML(CXMLDOMDocument2 & Doc);
	BOOL LoadFromString(const CString &,BOOL loadForm);
    void IsFormChanged(Component*,BOOL *);
public:
    enum SaveOperation {soSave,soSaveAs,soSaveAsTemplate};
	UINT	*		_controlsToClip;

	CFormComponent(LPTSTR _name=NULL);
	virtual ~CFormComponent();

	typedef CScrollImpl<CFormComponent>	scrollBase;
    typedef CFrameWindowImpl<CFormComponent,CWindow> baseClass;

    virtual BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP_EX(CFormComponent)
        MESSAGE_HANDLER(WM_PAINT,OnPaint)
		//CHAIN_MSG_MAP(scrollBase)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_SIZE,OnSize)
		MESSAGE_HANDLER(WM_MOVE,OnMove)
		MESSAGE_HANDLER(WM_CLOSE,OnClose)
		MESSAGE_HANDLER(WM_GETCTRLFONT,OnGetFormFont)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnButtonDown)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN,OnButtonDown)
		MESSAGE_HANDLER(WM_NCRBUTTONDOWN,OnButtonDown)
		//MESSAGE_HANDLER(WM_ERASEBKGND, LayoutMgr<CFormComponent>::OnEraseBackground)
		//MESSAGE_HANDLER(WMU_PS_ATTACH_PS, LayoutMgr<CFormComponent>::OnAttachPropertySheet)
		MESSAGE_HANDLER(WM_UPDATELAYOUT,OnUpdateLayout)
        MESSAGE_HANDLER(WM_EXITSIZEMOVE,OnEndSizeMove)
        MESSAGE_HANDLER(WM_GETMINMAXINFO,OnGetMinMaxInfo)
        CHAIN_MSG_MAP(baseClass)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	IDispatch* __stdcall get_Code();
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnEndSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual void DoPaint(CDCHandle dc);
    LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	void SetFormFont(CFontEx *);
	LRESULT OnGetFormFont(UINT,WPARAM,LPARAM, BOOL& bHandled);
	virtual void InitProperty(void);


	IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(HScroll,(WS_HSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(VScroll,(WS_VSCROLL))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(MinimizeBox,(WS_MINIMIZEBOX))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(MaximizeBox,(WS_MAXIMIZEBOX))
	IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(SysMenu,(WS_SYSMENU))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(ClipSiblings,(WS_CLIPSIBLINGS))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(ClipChildren,(WS_CLIPCHILDREN))
	//IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Child, (WS_CHILD))
	//IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Border, (WS_BORDER))

	IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ModalFrame,(WS_EX_DLGMODALFRAME))
	IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(TopMost,(WS_EX_TOPMOST))
	IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(Transparent,(WS_EX_TRANSPARENT))
	IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(MDIChild,(WS_EX_MDICHILD))
	IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ToolWindow,(WS_EX_TOOLWINDOW))
	IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ContextHelp,(WS_EX_CONTEXTHELP))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(AcceptFiles,(WS_EX_ACCEPTFILES))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(WindowEdge,(WS_EX_WINDOWEDGE))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ClientEdge,(WS_EX_CLIENTEDGE))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(ControlParent,(WS_EX_CONTROLPARENT))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(StaticEdge,(WS_EX_STATICEDGE))
    IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(AppWindow,(WS_EX_APPWINDOW))
    
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_BYTEALIGNCLIENT)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_BYTEALIGNWINDOW)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_CLASSDC)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_DBLCLKS)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_GLOBALCLASS)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_HREDRAW)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_NOCLOSE)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_OWNDC)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_PARENTDC)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_SAVEBITS)
    IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_VREDRAW)
	IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_IME)
	IMPLEMENT_CLASSSTYLE_BOOL_PROPERTY_I(CS_DROPSHADOW)


    DECLARE_PROPERTY(WndClient,CString)
	//пока полностью не реализовано, убрать, чтоб не мешалось
    //DECLARE_PROPERTY(WndToolBar,CString)
    //DECLARE_PROPERTY(WndStatusBar,CString)
    //DECLARE_PROPERTY(Menu,CString)

	//set window style WS_OVERLAPPED or WS_POPUP or WS_CHILD
	DECLARE_PROPERTY(WindowStyle, DWORD)
	DECLARE_PROPERTY(LocalizeName,CString)
	DECLARE_PROPERTY(LangID,LangID)
    DECLARE_PROPERTY(ShowHandle,BOOL)

	void set_EnableLayout(BOOL val);
	BOOL get_EnableLayout();
	void set_NPositions(long val);
	long get_NPositions();
	void set_ClientHeight(long val);
	long get_ClientHeight();
	void set_ClientWidth(long val);
	long get_ClientWidth();
	void set_BorderStyle(DWORD val);
	DWORD get_BorderStyle(void);
	void set_CaptionBar(BOOL val);
	BOOL get_CaptionBar(void);
	void set_Caption(CString str);
	CString get_Caption(void);
	void set_ShowWindow(BOOL val);
	BOOL get_ShowWindow(void);
	virtual BOOL IsForm();
	virtual void SetBoundsRect(CRect rc);
	virtual CRect GetBoundsRect(void);
	void SaveAsTemplate(Component * frm,CString* templatePath);
    void SaveAsForm(Component * frm);
	void SaveForm(Component * frm,SaveOperation operation);
	void LoadForm(Component *mainForm,Component ** formPtr,LPCTSTR formFileName,BOOL _fromTemplate);
	void CloseForm(Component * cmp,BOOL * remove);
	void GetFormFileName(Component * cmp,CString* formFileName);
	void GenerateCode();
    void GenerateLocFile(LPCTSTR fileName);
	DWORD get_InternalWindowStyle();
	void set_InternalWindowStyle(DWORD s);
	DWORD get_InternalWindowStyleEx();
	void set_InternalWindowStyleEx(DWORD s);
	void set_Visible(BOOL val);
	BOOL get_Visible();
	void set_Color(COLORREF val);
	COLORREF get_Color();
	void GetDialogRect(LPRECT r);
	void GetOffset(LPPOINT offset);
    void DefineLayout();
	LRESULT OnUpdateLayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void InitLayout();
	virtual void UnAttach(Component * component);
    void set_GSGuides(BOOL val);
    BOOL get_GSGuides();
    void set_FromLeftToRight(BOOL val);
    BOOL get_FromLeftToRight();
    void set_FromTopToBottom(BOOL val);
    BOOL get_FromTopToBottom();
    void ShowGrid(Component * form, BOOL val);
    void set_Grid(BOOL val);
    BOOL get_Grid();
    void SetGridWidth(Component * form, long val);
    void set_GridWidth(long cx);
    long get_GridWidth();
    void SetGridHeight(Component * form, long val);
    void set_GridHeight(long cy);
    long get_GridHeight();
    void set_OffsetX(long val);
    long get_OffsetX();
    void set_OffsetY(long val);
    long get_OffsetY();
    void set_Moveable(BOOL val);
    BOOL get_Moveable();
    void MakeGoldenSectionWidht(Component *from);
    void MakeGoldenSectionHeight(Component *from);
    void OnImageChange(CImage * image);
    void set_BaseCtrlID(long val);
    long get_BaseCtrlID(void);
    virtual void AddUndo(Component * form);
    void UndoChanges(Component * form);
    void EditCopy(Component * form,Component *comp);
    void EditCut(Component * form,Component *comp);
    void EditPaste(Component * form,Component *comp,CPoint *);
    void EditDelete(Component * form);
    virtual HANDLE GetHandle(void);
    void TabIndex(Component * form,BOOL);
    void SetFormFileName(Component* comp,LPTSTR);
};
//////////////////////////////////////////////////////////////////////////
#endif