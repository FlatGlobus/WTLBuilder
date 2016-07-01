// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "Panel.h"
#include "_util.h"
/////////////////////////////////////////////////////////////////////////////
typedef long VertTextRectAlign;
typedef long HorizTextRectAlign;
typedef CString PageName;
typedef CString PagesType;

void PagesEdit(HWND parent,PropertyBase *prop,LPARAM);
namespace DecorativeCtrl
{
typedef long Inner;
typedef long Outer;
typedef long Edge;
static void RegisterPanelStyles();
REGISTER_COMPONENT_EX(CPanel,CPanelComp,DecorativeCtrl,IDB_PANEL)
REGISTER_COMPONENT_EX(CPanelHost,CPanelHostComp,DecorativeCtrl,IDB_PANELHOST)

CPanelComp::CPanelComp(LPTSTR _name):ControlComponent<DecorativeCtrl::CPanelComp>(_name),isHosted(FALSE),
    _textColor(textColor),_bkColor(bkColor),_borderColor(borderColor)
{
	SetDefaultSize(80,50);
	RegisterPanelStyles();
    enableTabIndex=FALSE;
}

CPanelComp::~CPanelComp(void)
{
}

BOOL CPanelComp::CreateComponent(Component * _Parent)
{
    SetComponentParent(_Parent);
    CWindowImpl<Panel::CPanel>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
    cornerPar.Change.SetObject(this);
    cornerPar.Change.SetMethod(&CPanelComp::OnCornerParChanged);
    gradientRender.Change.SetObject(this);
    gradientRender.Change.SetMethod(&CPanelComp::OnGradientChanged);
	return ::IsWindow(m_hWnd);
}

HintItem CPanelComp::GetHint(CPoint & at)
{
	if(isHosted==TRUE)
		return hiNone;
	return ControlComponent<DecorativeCtrl::CPanelComp>::GetHint(at);
}

void CPanelComp::InitProperty(void)
{
	ControlComponent<DecorativeCtrl::CPanelComp>::InitProperty();
	DEFINE_PROPERTY(InnerBorder,Inner,CPanelComp,BDR_RAISEDINNER)
	DEFINE_PROPERTY(OuterBorder,Outer,CPanelComp,BDR_RAISEDOUTER)
	DEFINE_PROPERTY(EdgeType,Edge,CPanelComp,BF_RECT)
	DEFINE_PROPERTY(TextColor,CColorref,CPanelComp,textColor)
	DEFINE_PROPERTY(BkColor,CColorref,CPanelComp,bkColor)
    DEFINE_PROPERTY(BorderColor,CColorref,CPanelComp,borderColor)
	DEFINE_PROPERTY(Caption,CString,CPanelComp,_T(""))
	DEFINE_PROPERTY(Hosted,BOOL,CPanelComp,FALSE)
	PUBLIC_PROPERTY(Hosted,FALSE)
	DEFINE_PROPERTY(HorizTextAlign,HorizTextRectAlign,CPanelComp,DT_CENTER)
	DEFINE_PROPERTY(VertTextAlign,VertTextRectAlign,CPanelComp,DT_VCENTER)
	DEFINE_PROPERTY(SingleLine,BOOL,CPanelComp,TRUE)
    SET_PROP_VALUE(ControlParent,TRUE)
    DEFINE_PROPERTY(Theme,BOOL,CPanelComp,GetTheme())
    DEFINE_PROPERTY(RoundCorners,BOOL,CPanelComp,GetRoundCorners())
    cornerPar.AddProperty(_T("RoundCorners"),objprop);
    DEFINE_PROPERTY(Gradient,BOOL,CPanelComp,GetEnableGradient())
    gradientRender.AddProperty(_T("Gradient"),objprop);
}

void CPanelComp::OnCornerParChanged(CPointEx *)
{
    SetCornerParam(cornerPar);
    SetModified();
}

void CPanelComp::OnGradientChanged(CGradientRender *)
{
    startColor = gradientRender.get_StartColor();
    endColor = gradientRender.get_EndColor();
    gradientType = gradientRender.get_GradientType();
    transformationType = gradientRender.get_TransformationType();
    InvalidateRect(NULL);
    SetModified();
}

void CPanelComp::set_Hosted(BOOL val)
{
	isHosted=val;
	if(isHosted==TRUE)
		((DecorativeCtrl::CPanelHostComp *)GetComponentParent())->AddPanel(this);
    SetModified();
}

BOOL CPanelComp::get_Hosted(void)
{
	return isHosted;
}

void CPanelComp::set_Theme(BOOL val)
{
    SetTheme(val);
    if(val==TRUE)
    {
        SetRoundCorners(FALSE);
        UpdateProperty(_T("RoundCorners"));
    }

    SetModified();
}

BOOL CPanelComp::get_Theme(void)
{
    return GetTheme();
}

void CPanelComp::set_InnerBorder(long val)
{
   CPanel::SetInnerBorder(val);
   SetModified();
}

long CPanelComp::get_InnerBorder()
{
	return CPanel::GetInnerBorder();
}

void CPanelComp::set_OuterBorder(long val)
{
	CPanel::SetOuterBorder(val);
    SetModified();
}

long CPanelComp::get_OuterBorder()
{
	return CPanel::GetOuterBorder();
}

void CPanelComp::set_EdgeType(long val)
{
	CPanel::SetEdgeType(val);
    SetModified();
}

long CPanelComp::get_EdgeType()
{
	return CPanel::GetEdgeType();
}

void CPanelComp::set_Caption(CString val)
{
	CPanel::SetCaption(val);
    SetModified();
}

CString CPanelComp::get_Caption()
{
	return CPanel::GetCaption();
}

void CPanelComp::set_TextColor(CColorref val)
{
    _textColor = val;
	CPanel::SetTextColor(val);
    SetModified();
}

CColorref CPanelComp::get_TextColor()
{
	return _textColor;
}

CColorref CPanelComp::get_BkColor()
{
	return _bkColor;
}

void CPanelComp::set_BkColor(CColorref val)
{
    _bkColor = val;
	CPanel::SetBkColor(val);
    SetModified();
}

CColorref CPanelComp::get_BorderColor()
{
    return _borderColor;
}

void CPanelComp::set_BorderColor(CColorref val)
{
    _borderColor = val;
    CPanel::SetBorderColor(val);
    SetModified();
}
long CPanelComp::get_HorizTextAlign()
{
	return CPanel::GetHorizTextAlign();
}

void CPanelComp::set_HorizTextAlign(long val)
{
	CPanel::SetHorizTextAlign(val);
    SetModified();
}

void CPanelComp::set_VertTextAlign(long val)
{
	CPanel::SetVertTextAlign(val);
    SetModified();
}

long CPanelComp::get_VertTextAlign()
{
	return CPanel::GetVertTextAlign();
}

void CPanelComp::set_SingleLine(BOOL val)
{
	CPanel::SetSingleLine(val);
    SetModified();
}

BOOL CPanelComp::get_SingleLine()
{
	return CPanel::GetSingleLine();
}

void CPanelComp::set_RoundCorners(BOOL val)
{
    SetRoundCorners(val);
    if(val==TRUE)
    {
        SetTheme(FALSE);
        UpdateProperty(_T("Theme"));
    }
    SetModified();
}

BOOL CPanelComp::get_RoundCorners(void)
{
    return GetRoundCorners();
}

void CPanelComp::set_Gradient(BOOL val)
{
    SetEnableGradient(val);
    SetModified();
}

BOOL CPanelComp::get_Gradient()
{
    return GetEnableGradient();
}

BEGIN_LIST_PROPERTY(Inner)
LIST_ITEM_DECORATE(BDR_RAISEDINNER,BDR_RAISEDINNER,Raised)
LIST_ITEM_DECORATE(BDR_SUNKENINNER,BDR_SUNKENINNER,Sunken)
LIST_ITEM_DECORATE(0,0,None)
END_LIST_ITEM(Inner)

BEGIN_LIST_PROPERTY(Outer)
LIST_ITEM_DECORATE(BDR_RAISEDOUTER,BDR_RAISEDOUTER,Raised)
LIST_ITEM_DECORATE(BDR_SUNKENOUTER,BDR_SUNKENOUTER,Sunken)
LIST_ITEM_DECORATE(0,0,None)
END_LIST_ITEM(Outer)

BEGIN_LIST_PROPERTY(Edge)
LIST_ITEM_DECORATE(BF_RECT,BF_RECT,Rect)
LIST_ITEM_DECORATE(BF_LEFT,BF_LEFT,Left)
LIST_ITEM_DECORATE(BF_BOTTOM,BF_BOTTOM,Bottom)
LIST_ITEM_DECORATE(BF_RIGHT,BF_RIGHT,Right)
LIST_ITEM_DECORATE(BF_TOP,BF_TOP,Top)
LIST_ITEM_DECORATE(BF_TOPLEFT,BF_TOPLEFT,TopLeft)
LIST_ITEM_DECORATE(BF_TOPRIGHT,BF_TOPRIGHT,TopRight)
LIST_ITEM_DECORATE(BF_BOTTOMLEFT,BF_BOTTOMLEFT,BottomLeft)
LIST_ITEM_DECORATE(BF_BOTTOMRIGHT,BF_BOTTOMRIGHT,BottomRight)
END_LIST_ITEM(Edge)

static void RegisterPanelStyles()
{
	static BOOL IsInited=FALSE;

	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(Inner)
	REGISTER_LIST_PROPERTY(Outer)
	REGISTER_LIST_PROPERTY(Edge)

	//RegisterConversion(_T("PagesType"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("PagesType"),NULL,PagesEdit);
	//RegisterDrawProperty(_T("PageName"),DrawPropertyValueText);
	RegisterEdit(_T("PageName"),CPagesListEdit::CreateInplaceEdit,NULL);
	IsInited=TRUE;
}
//////////////////////////////////////////////////////////////////////////
CPanelHostComp::CPanelHostComp(LPTSTR _name):ControlComponent<DecorativeCtrl::CPanelHostComp>(_name)
{
	RegisterPanelStyles();
	SetDefaultSize(80,50);
}

CPanelHostComp::~CPanelHostComp(void)
{
}

BOOL CPanelHostComp::CreateComponent(Component * _Parent)
{
    ADD_WIN_STYLE_EX(WS_EX_CONTROLPARENT)
    SetComponentParent(_Parent);
	Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
    cornerPar.Change.SetObject(this);
    cornerPar.Change.SetMethod(&CPanelHostComp::OnCornerParChanged);

	return ::IsWindow(m_hWnd);
}

CPanelComp * CPanelHostComp::AddPanel(const CString& panelName,DecorativeCtrl::CPanelComp* panel)
{
	if(panel==NULL)
		panel=(DecorativeCtrl::CPanelComp *)GetComponents()->Create(this,_T("DecorativeCtrl:CPanel"),CRect(0,0,bounds.Width(),bounds.Height()));
	if(panel)
	{
        CopyProperties(panel);
		SetCurrent(-1);
		panel->ShowWindow(SW_HIDE);
		if(panelName.IsEmpty()==FALSE)
			panel->set_Name(panelName);
		panel->set_Hosted(TRUE);//panel will add to panels array itself
        SetModified();
	}
    return panel;
}

void CPanelHostComp::AddPanel(DecorativeCtrl::CPanelComp * panel)
{
   CPanelHost::AddPanel(panel);
   CopyProperties(panel);
	if(panel->get_Name()==currentName)
		set_CurrentPage(currentName);
	else
		panel->ShowWindow(SW_HIDE);
    SetModified();
}

void CPanelHostComp::Reset()
{
	panels.RemoveAll();
	UpdateProperty(_T("CurrentPage"));
    SetModified();
}

void CPanelHostComp::DeleteComponent(DecorativeCtrl::CPanelComp* panel)
{
    if(panel)
    {
        for(long i=0; i < GetCount(); i++)
        {
            if(GetAt(i)==panel)
            {
                GetComponents()->Delete((DecorativeCtrl::CPanelComp *)GetAt(i),TRUE);
                panels.RemoveAt(i);
                break;
            }
        }
    }

}

void CPanelHostComp::SetBoundsRect(CRect rc)
{
    ControlComponent<DecorativeCtrl::CPanelHostComp>::SetBoundsRect(rc);

    CRect panelsRc;
    panelsRc.left = 0;
    panelsRc.top = 0;
    panelsRc.right = bounds.Width();
    panelsRc.bottom = bounds.Height();
    for(int i=0; i < GetCount(); i++)
    {
        Component *comp=dynamic_cast<Component *>(GetAt(i));
        comp->SetBoundsRect(panelsRc);
    }
}

void CPanelHostComp::InitProperty(void)
{
	ControlComponent<DecorativeCtrl::CPanelHostComp>::InitProperty();
	DEFINE_PROPERTY(CurrentPage,PageName,CPanelHostComp,_T(""))
	DEFINE_PROPERTY(Pages,PagesType,CPanelHostComp,_T(""))
	DEFINE_PROPERTY(InnerBorder,Inner,CPanelHostComp,BDR_RAISEDINNER)
	DEFINE_PROPERTY(OuterBorder,Outer,CPanelHostComp,BDR_RAISEDOUTER)
	DEFINE_PROPERTY(BkColor,CColorref,CPanelHostComp,_bkColor)
    DEFINE_PROPERTY(Theme,BOOL,CPanelHostComp,TRUE)
    DEFINE_PROPERTY(RoundCorners,BOOL,CPanelHostComp,GetRoundCorners())
    cornerPar.AddProperty(_T("RoundCorners"),objprop);
    DEFINE_PROPERTY(BorderColor,CColorref,CPanelHostComp,borderColor)
}

void CPanelHostComp::OnCornerParChanged(CPointEx *)
{
    CPanel::SetCornerParam(cornerPar);
    for(long i=0;i < GetCount();i++)
        CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    SetModified();
}

CString CPanelHostComp::get_CurrentPage()
{
	long idx=GetCurrent();
	if(idx==-1 || idx >= GetCount())
		return _T("");
	return currentName=((DecorativeCtrl::CPanelComp *)GetAt(idx))->get_Name();
}

void CPanelHostComp::set_CurrentPage(CString val)
{
	currentName=val;
	long idx=FindPanel(val);
	if(idx!=-1)
	{
		SetCurrent(idx);
		
		for(long i=0; i < GetCount(); i++)
			((DecorativeCtrl::CPanelComp*)GetAt(i))->set_Visible(i!=current? FALSE : TRUE);

        CopyProperties((DecorativeCtrl::CPanelComp*)GetAt(idx));
        SetModified();
	}
}

void CPanelHostComp::set_Pages(CString val)
{
    panels.RemoveAll();
    if(val.IsEmpty())
        return;
    int idx=-1;
    while((idx=val.Find(_T("\n")))!=-1)
    {
        CString panelName(val.Left(idx));
        Component * comp=GetComponents()->Find(panelName);
        AddPanel(panelName,(DecorativeCtrl::CPanelComp *)comp);
        val.Delete(0,idx+1);
    }
    SetModified();
}

CString CPanelHostComp::get_Pages()
{
    CString ret;
    for(int i=0; i < panels.GetSize();i++)
    {
        ret+=((DecorativeCtrl::CPanelComp *)panels[i])->get_Name();
        ret+=_T('\n');
    }
    return ret;
}

long CPanelHostComp::FindPanel(const CString & str)
{
	for(long i=0; i < panels.GetSize();i++)
	{
		if(((DecorativeCtrl::CPanelComp *)GetAt(i))->get_Name()==str)
			return i;
	}
	return -1;
}

void CPanelHostComp::set_InnerBorder(long val)
{
    CPanel::SetInnerBorder(val);
	for(long i=0;i < GetCount();i++)
		CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    SetModified();
}

long CPanelHostComp::get_InnerBorder()
{
	return CPanel::GetInnerBorder();
}

void CPanelHostComp::set_OuterBorder(long val)
{
	CPanel::SetOuterBorder(val);
    for(long i=0;i < GetCount();i++)
        CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    SetModified();
}

long CPanelHostComp::get_OuterBorder()
{
	return CPanel::GetOuterBorder();
}

void CPanelHostComp::set_BkColor(CColorref val)
{
    _bkColor = val;
	CPanel::SetBkColor(val);
    for(long i=0;i < GetCount();i++)
        CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    SetModified();
}

CColorref CPanelHostComp::get_BkColor()
{
	return _bkColor;
}

void CPanelHostComp::set_Theme(BOOL val)
{
    CPanel::SetTheme(val);
    for(long i=0;i < GetCount();i++)
        CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    SetModified();
}

BOOL CPanelHostComp::get_Theme()
{
    return CPanel::GetTheme();
}

void CPanelHostComp::set_RoundCorners(BOOL val)
{
    CPanel::SetRoundCorners(val);
    for(long i=0;i < GetCount();i++)
        CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    //if(val==TRUE)
    //{
        //SetTheme(FALSE);
        //UpdateProperty(_T("Theme"));
    //}
    SetModified();
}

BOOL CPanelHostComp::get_RoundCorners(void)
{
    return CPanel::GetRoundCorners();
}

CColorref CPanelHostComp::get_BorderColor()
{
    return _borderColor;
}

void CPanelHostComp::set_BorderColor(CColorref val)
{
    _borderColor = val;
    CPanel::SetBorderColor(val);
    for(long i=0;i < GetCount();i++)
        CopyProperties((DecorativeCtrl::CPanelComp *)GetAt(i));
    SetModified();
}

CRect CPanelHostComp::GetMinRect()
{
    CRect minRc;
    minRc.left=0;
    minRc.top=0;
    minRc.right=0;
    minRc.bottom=0;

    BOOL flag=FALSE;
    for(int i=0; i < GetCount(); i++)
    {
        Component *comp=dynamic_cast<Component *>(GetAt(i));
        CRect rc = comp->GetMinRect();
        minRc.right=max(minRc.right,rc.right);
        minRc.bottom=max(minRc.bottom,rc.bottom);
        flag=TRUE;
    }

    if(flag==FALSE)
        minRc.SetRectEmpty();
    else
    {
        minRc.left=0;
        minRc.top=0;
    }

    return minRc;
}

void CPanelHostComp::EndEditPages(const CPageInfoArray &array)
{
    for(int i=0; i < array.GetSize();i++)
    {
        CPanelComp * comp = (DecorativeCtrl::CPanelComp *)array[i].ptr;
        if(comp!=NULL)
        {
            CString editedName;
            CString oldName;
            editedName=array[i].name;
            oldName=comp->get_Name();
            if(editedName!=oldName)
                ((DecorativeCtrl::CPanelComp *)array[i].ptr)->set_Name(editedName);
        }
    }

    for(int i=0; i < panels.GetSize();i++)
    {

        int index=FindItem(array,CPageInfo(((DecorativeCtrl::CPanelComp *)GetAt(i))->get_Name()));
        if(index==-1)
        {
            DeleteComponent((DecorativeCtrl::CPanelComp *)GetAt(i));
            i=0;
        }
    }
    
    Component * before = NULL;
    Component * after = this;
    Reset();
    for(int i=0; i < array.GetSize(); i++ )
    {
        before = AddPanel(array[i].name,(DecorativeCtrl::CPanelComp *)array[i].ptr);//InsertAt!!!
        GetComponents()->MoveAfter(before,after);
        after=before;
    }

}

void CPanelHostComp::CopyProperties(DecorativeCtrl::CPanelComp * comp)
{
    comp->set_InnerBorder(get_InnerBorder());
    comp->set_OuterBorder(get_OuterBorder());
    //comp->set_EdgeType(get_EdgeType());
    comp->set_BkColor(get_BkColor());
    comp->set_Theme(get_Theme());
    comp->set_RoundCorners(get_RoundCorners());
    if(get_RoundCorners() == TRUE)
    {
        comp->SetCornerParam(GetCornerParam());
        comp->SetBorderColor(GetBorderColor());
    }
}
//////////////////////////////////////////////////////////////////////////
}

