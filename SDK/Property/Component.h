// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __COMPONENT_H
#define __COMPONENT_H
//////////////////////////////////////////////////////////////////////////
#include <atlcrack.h>
#include "atldispa.h"
#include "PropertyItem.h"
#include "DesignerCtrl.h"
#include "BitVect.h"
#include "GDIUtil.h"
#include <atldlgs.h>
#include <atlwin.h>
#include "Codegen.h"
#include "Path.h"
#include "DOMxml.h"
#include <atlscrl.h>
#include "LayoutMgr.h"
#include "Layout.h"
#include <vector>
//////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_WINSTYLE_PROPERTY(Class,Name,Style)\
void Class::set_##Name(long val)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	windowStyle&=~(Style);\
	windowStyle|=val;\
	set_InternalWindowStyle(windowStyle);\
}\
long Class::get_##Name(void)\
{\
	return get_InternalWindowStyle() & (Style);\
}

#define IMPLEMENT_WINSTYLE_PROPERTY_I(Name,Style)\
void set_##Name(long val)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	windowStyle&=~(Style);\
	windowStyle|=val;\
	set_InternalWindowStyle(windowStyle);\
}\
long get_##Name(void)\
{\
	return get_InternalWindowStyle() & (Style);\
}

#define DECLARE_WINSTYLE_BOOL_PROPERTY(Name)\
public:\
	void set_##Name(BOOL n);\
	BOOL get_##Name(void);

#define IMPLEMENT_WINSTYLE_BOOL_PROPERTY(Class,Name,Style)\
void Class::set_##Name(BOOL val)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	windowStyle = val == TRUE ? (windowStyle | (Style)): (windowStyle & ~(Style));\
	set_InternalWindowStyle(windowStyle);\
}\
BOOL Class::get_##Name(void)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	DWORD val=get_InternalWindowStyle();\
	return (val & (Style))==Style;\
}

#define IMPLEMENT_WINSTYLE_BOOL_PROPERTY_I(Name,Style)\
	void set_##Name(BOOL val)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	windowStyle = val == TRUE ? (windowStyle | (Style)): (windowStyle & ~(Style));\
	set_InternalWindowStyle(windowStyle);\
}\
	BOOL get_##Name(void)\
{\
	DWORD val=get_InternalWindowStyle();\
	return (val & (Style))==Style;\
}

#define IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_I(Name,Style)\
	void set_##Name(BOOL val)\
{\
	DWORD windowStyleEx=get_InternalWindowStyleEx();\
	windowStyleEx = val == TRUE ? (windowStyleEx | (Style)): (windowStyleEx & ~(Style));\
	set_InternalWindowStyleEx(windowStyleEx);\
}\
	BOOL get_##Name(void)\
{\
	DWORD windowStyleEx=get_InternalWindowStyleEx();\
	return (windowStyleEx & (Style))==Style;\
}

#define IMPLEMENT_WINSTYLE_BOOL_PROPERTY_NOT(Class,Name,Style)\
	void Class::set_##Name(BOOL val)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	windowStyle = val == FALSE ? (windowStyle | (Style)): (windowStyle & ~(Style));\
	set_InternalWindowStyle(windowStyle);\
}\
	BOOL Class::get_##Name(void)\
{\
	DWORD val=get_InternalWindowStyle();\
	return (val & (Style))==FALSE;\
}

#define IMPLEMENT_WINSTYLE_BOOL_PROPERTY_NOT_I(Name,Style)\
	void set_##Name(BOOL val)\
{\
	DWORD windowStyle=get_InternalWindowStyle();\
	windowStyle = val == FALSE ? (windowStyle | (Style)): (windowStyle & ~(Style));\
	set_InternalWindowStyle(windowStyle);\
}\
	BOOL get_##Name(void)\
{\
	DWORD val=get_InternalWindowStyle();\
	return (val & (Style))==FALSE;\
}

#define IMPLEMENT_EXWINSTYLE_BOOL_PROPERTY_NOT(Class,Name,Style)\
	void Class::set_##Name(BOOL val)\
{\
	DWORD windowStyle = get_InternalWindowStyleEx(); \
	windowStyle = val == FALSE ? (windowStyle | (Style)): (windowStyle & ~(Style));\
	set_InternalWindowStyleEx(windowStyle);\
}\
	BOOL Class::get_##Name(void)\
{\
	DWORD val=get_InternalWindowStyleEx();\
	return (val & (Style))==FALSE;\
}

#define ADD_WIN_STYLE(Style)\
{\
	DWORD windowStyle = get_InternalWindowStyle(); \
	windowStyle |= (Style);\
	set_InternalWindowStyle(windowStyle);\
}

#define ADD_WIN_STYLE_EX(Style)\
{\
	DWORD windowStyle = get_InternalWindowStyleEx(); \
	windowStyle |= (Style);\
	set_InternalWindowStyleEx(windowStyle);\
}

#define SET_WIN_STYLE(Style) set_InternalWindowStyle(Style);
#define SET_WIN_STYLE_EX(Style)	set_InternalWindowStyleEx(Style);

//////////////////////////////////////////////////////////////////////////
#define WM_SETCTRLFONT WM_USER+201 
#define WM_GETCTRLFONT WM_USER+202 
#define WM_UPDATELAYOUT WM_USER+203 
//////////////////////////////////////////////////////////////////////////

#define BOX_SIDE 3
#define BOX_SIDE2 6

#define DEF_SIZE_W	32
#define DEF_SIZE_H	16

enum HintItem {hiNone,hiLeftTop,hiTopMedium,hiRightTop,hiRightMedium,hiRightBottom,
				hiBottomMedium,hiLeftBottom,hiLeftMedium,hiCaption,hiField,hiAll}; 
enum ComponentState {csCreating,csDeleting,csLoading,csSaving,csMoving,csReserved1,csReserved2};
class Components;
//////////////////////////////////////////////////////////////////////////
class PROPERTY_API Component:public IDispDynImpl<Component>
{
protected:
	CProperties objprop;
//	BOOL		selected;
	BOOL		pressed;	
	CPoint		deltaPoint;
	CString		name;
	CDesignerCtrl *designer;
	Component	*Parent;	
	CBitVect    state;
	CString		className;
	CRect		bounds;
    CRect       minRC;
	CString		parentName;
	long		uniqueID;
	CSize		defaultSize;
    long        tabIndex;
    BOOL        enableTabIndex;

	void UpdateBoundsProp(CRect &);
	CString		MakeDefaultName();
	void		SetDefaultSize(int cx,int cy);
	DECLARE_PROPERTY(ParentName,CString)
public:
	Component(LPCTSTR _className=NULL);
    Component(const Component &);
	virtual ~Component(void);
    DECLARE_CALLBACK(Changed,changed)
//////////////////////////////////////////////////////////////////////////
	BEGIN_DISPATCH_MAP(Component)
		DISP_METHOD1_ID(Item, DISPID_VALUE, VT_VARIANT , VT_BSTR)
		DISP_PROPGET(Count,VT_I4)
		DISP_PROPGET(Class,VT_BSTR)
		DISP_PROPGET(Components,VT_DISPATCH)
		DISP_PROPGET(Code,VT_DISPATCH)
		DISP_PROPGET(Form,VT_DISPATCH)
		DISP_PROPGET(IsControl,VT_BOOL)
		DISP_PROPGET(IsForm,VT_BOOL)
	END_DISPATCH_MAP()
	_variant_t __stdcall Item(BSTR propName);
	long __stdcall get_Count(void);
	BSTR __stdcall get_Class(void);
	IDispatch * __stdcall get_Components();
	virtual IDispatch* __stdcall get_Code();
	IDispatch * __stdcall get_Form();
	virtual BOOL __stdcall get_IsControl();
	virtual BOOL __stdcall get_IsForm();
//////////////////////////////////////////////////////////////////////////
	virtual BOOL CreateComponent(Component *);
    virtual void ComponentCreated();
	virtual void DeleteComponent();
	virtual void InitProperty(void);
	void ShowProperties(void);
	
	DECLARE_PROPERTY(Left,long)
	DECLARE_PROPERTY(Top,long)
	DECLARE_PROPERTY(Width,long)
	DECLARE_PROPERTY(Height,long)
	DECLARE_PROPERTY(Name,CString)
	DECLARE_PROPERTY(UniqueID,long)

	virtual CRect	GetBoundsRect(void);
	virtual void	SetBoundsRect(CRect);
	__declspec(property(get=GetBoundsRect, put=SetBoundsRect)) CRect Bounds;
	virtual BOOL CheckBounds(CRect rc);

	virtual BOOL MouseDown(CDC *,CPoint,HintItem);
	virtual BOOL MouseMove(CDC *,CPoint,HintItem);
	virtual BOOL MouseUp(CDC *,CPoint,HintItem);
	virtual CRect Move(CPoint &at,HintItem hint);
	virtual HintItem GetHint(CPoint &);
	virtual void Paint(CDC & dc);
	virtual void PaintSelect(CDC & dc);
	virtual void Load(CXMLDOMNode &);
	virtual void Save(CXMLDOMNode &);
	void DesignerToComponent(CRect & rc);
	void ComponentToDesigner(CRect & rc);
	void DesignerToComponent(CPoint &);
	void ComponentToDesigner(CPoint &);
    long DesignerToComponentX(long);
    long ComponentToDesignerX(long);
    long DesignerToComponentY(long);
    long ComponentToDesignerY(long);
	void SetState(ComponentState,BOOL flag=TRUE);
	BOOL GetState(ComponentState);
	void ResetState(void);	
	virtual BOOL IsControl();
	virtual BOOL IsForm();
	virtual HANDLE GetHandle(void);
	Component*GetComponentParent();	
	void SetComponentParent(Component*);	
	Component*GetParentForm();	
	CDesignerCtrl * GetDesigner();
	Components * GetComponents();
	void SetDesigner(CDesignerCtrl *);
	CProperties * GetProperty();
	virtual CString     GetClassName();	
	Component * Find(const CString & name);
    virtual CString     GetComponetKind();
	virtual void set_Layout(BOOL val);
	virtual BOOL get_Layout(void);
	virtual CLayout *	get_leftLayout();
	virtual CLayout	*	get_topLayout();
	virtual CLayout	*	get_rightLayout();
	virtual CLayout	*	get_bottomLayout();
	virtual CLayout	*	get_hCenterLayout();
	virtual CLayout	*	get_vCenterLayout();
	virtual void UnAttach(Component * component);
	virtual void SetModified(CRect * rc=NULL);
	void set_Focus(BOOL val);
	BOOL get_Focus();
    virtual Component * Clone();
    virtual CRect GetMinRect();
    void set_TabIndex(long);
    long get_TabIndex();
    BOOL EnableTabIndex();

	void set_Selected(BOOL);
	BOOL get_Selected(void);
	__declspec(property(get=get_Selected, put=set_Selected)) BOOL Selected;

	void set_FirstSelected(BOOL);
	BOOL get_FirstSelected(void);
	__declspec(property(get=get_FirstSelected, put=set_FirstSelected)) BOOL FirstSelected;
};
//////////////////////////////////////////////////////////////////////////
typedef std::vector<Component *> ComponentArray;
typedef std::vector<Component *>::iterator ComponentArrayIter; 

enum CurrMode {cmSelect,cmCreate};
class  PROPERTY_API Components:public IDispDynImpl<Components>
{
public:
    friend class Component;
	Components(void);
	~Components(void);
//////////////////////////////////////////////////////////////////////////
	BEGIN_DISPATCH_MAP(Components)
		DISP_METHOD_ID(Item,DISPID_VALUE,VT_DISPATCH,1,VTS_I4 )
		DISP_PROPGET_ID(_NewEnum,DISPID_NEWENUM,VT_UNKNOWN)
		DISP_PROPGET(Count,VT_I4)
		DISP_METHOD1(Add,VT_EMPTY,VT_DISPATCH)
		DISP_METHOD1(Remove,VT_EMPTY,VT_I4)
	END_DISPATCH_MAP()
	IDispatch*__stdcall Item(long Index);
	long __stdcall get_Count(void);
	LPUNKNOWN __stdcall get__NewEnum();
	void __stdcall Add(Component *);
	void __stdcall Remove(long Index);
//////////////////////////////////////////////////////////////////////////
	void	SetDesigner(CDesignerCtrl *);
	CDesignerCtrl *	GetDesigner(void);
	Component *	GetCurrentParent(CPoint &);
	Component*GetParentForm();
	Component * Create(CRect &,BOOL multiCreate);//by mouse
	Component * Create(Component *,LPCTSTR name,CRect &);//by code
	void MouseDown(CPoint);
	void MouseMove(CPoint);
	void MouseUp(CPoint);
	Component * ComponentFromPt(CPoint & at,BOOL realBounds=FALSE);
	Component * SelectComponentFromPt(CPoint & at,BOOL seleted=FALSE);
	void UnselectAll(void);
	int	GetSelCount(void);
	Component * GetSingleSel(void);
	Component * GetFirstSel(void);
	int GetFirstSelIdx(void);
	void Paint(CDC &);
	void Load(CXMLDOMNode &);
	void Save(CXMLDOMNode &,BOOL onlySelected = FALSE);
	void IncrementMove(long x,long y);
	void IncrementSize(long x,long y, BOOL rightBottom);
	void Delete(void);
    BOOL Delete(Component * comp, BOOL deleteSelf = TRUE);
	void RemoveAll(void);
	Component * Find(const CString &);
    int FindLeftestIdx(int pos);
	int FindRightestIdx(int fromPos);
    int FindTopestIdx(int pos);
	int FindBottomestIdx(int pos);
	void SetSelectMode(BOOL);
    BOOL IsSelectMode(); 
	Component * GetAt(int);
	int GetCount(void);
	void MoveAfter(Component *comp,Component *after,BOOL childrenToo=TRUE);
	long GetNextId(void);
	void Invalidate(BOOL hideSelMarks=FALSE);
	void MakeGoldenSectionWidht(void);
	void MakeGoldenSectionHeight(void);
    ComponentArray * Clone(BOOL onlySelected);
    ComponentArray * Clone(Component * comp);
    void Paste(ComponentArray *,Component *,CPoint *);
    void ChangeParent(Component *parent);
    int FindByHandle(HWND);
    int ControlsCount();
    BOOL SetTabIndex(CPoint &,long &);
    BOOL SetTabIndex(Component *,long &);
protected:
	void SelectControl(int idx,Component * active);
	void SelectComponent(LPCTSTR);
	Component * FindByParent(Component *);
	void InsertAt(int idx,Component * comp);
	int FindIndex(Component *);
    int FindParentIndex(Component *);
    //return 0 if not found
    long FindMaxTabIndex();
    long FindMinTabIndex();
    long FindNextTabIndex(long);

	void MouseDownAll(CDC *,CPoint);
	void MouseMoveAll(CDC *,CPoint);
	void MouseUpAll(CDC *,CPoint);
	void SetStateAll(ComponentState,BOOL flag=TRUE,BOOL SelectedOnly=TRUE);	 

	void ShowCursor(HintItem h);
	CPoint SnapToGrid(CPoint);
	void AlignLeft(Component *,long);
	void AlignTop(Component *,long);
	void AlignRight(Component *,long);
	void AlignBottom(Component *,long);
	void AlignHoriz(Component *);
	void AlignVert(Component *);
	void MakeSameWidth(Component *,long);
	void MakeSameHeight(Component *,long);
	void MakeSameSize(Component *,long);
    void ToParent(Component *,long);
    void HorizOrder(Component *, long);
    void VertOrder(Component *, long);
	void HorizOrderRight(Component *, long);
	void VertOrderBottom(Component *, long);
	void CenterHoriz();
	void CenterVert();
    void CenterGroupHoriz(Component*, long);
    void CenterGroupVert(Component*, long);
    void ChangeComponentsParent(Component*);
    void ReSetTabIndex();
    int  FindByTabIndex(long);
	void SelectAll(Component*);
    

	ComponentArray	components;
	CDesignerCtrl *	designer;

	BOOL		pressed;	
	HintItem	hint;
	CurrMode	currMode;	
	long		id;	
	BOOL		hideall;
	CString		newComponentName;
	BOOL        freeze;
};
//////////////////////////////////////////////////////////////////////////
BOOL ExtractName(const CString &str,CString &cmpPage,CString &cmpName);
//////////////////////////////////////////////////////////////////////////
#endif