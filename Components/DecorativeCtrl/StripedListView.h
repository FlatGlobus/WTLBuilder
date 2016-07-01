// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef _STRIPEDLISTVIEW_H
#define _STRIPEDLISTVIEW_H
////////////////////////////////////////////////////////////////////////////////////////////////
class CStripedListView : public CWindowImpl<CStripedListView, CListViewCtrl>,
public CCustomDraw<CStripedListView>                   
{
    COLORREF firstColor,secondColor;
public:
    
    BEGIN_MSG_MAP(CStripedListView)    
        CHAIN_MSG_MAP(CCustomDraw<CStripedListView>)
    END_MSG_MAP()          	
        
    CStripedListView():firstColor(RGB(200,200,255)),secondColor(RGB(255,255,255))
    {
    }

    void SetFirstColor(COLORREF val)
    {
        firstColor=val;
        InvalidateRect(NULL);
    }

    COLORREF GetFirstColor()
    {
        return firstColor;
    }

    void SetSecondColor(COLORREF val)
    {
        secondColor=val;
        InvalidateRect(NULL);
    }

    COLORREF GetSecondColor()
    {
        return secondColor;
    }

    DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
    {		
        return  CDRF_NOTIFYITEMDRAW;
    }
    
    DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
    {
        NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( lpNMCustomDraw );    
        
        // This is the prepaint stage for an item. Here's where we set the
        // item's text color. Our return value will tell Windows to draw the
        // item itself, but it will use the new color we set here for the background     
        
        COLORREF crText;
        
        if ( (pLVCD->nmcd.dwItemSpec % 2) == 0 )
            crText = firstColor;
        else 
            crText = secondColor;        
        
        // Store the color back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrTextBk = crText;
        
        // Tell Windows to paint the control itself.
        return CDRF_DODEFAULT;
    }
    
};

#ifdef __WTLBUILDER__
namespace DecorativeCtrl
{
#define DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(Name)\
public:\
    void set_##Name(BOOL n);\
    BOOL get_##Name(void);
    
#define IMPLEMENT_LISTVIEWEXSTYLE_BOOL_PROPERTY(Class,Name,Style)\
    void Class::set_##Name(BOOL val)\
    {\
    DWORD listViewStyleEx = val == TRUE ? (GetExtendedListViewStyle() | (Style)): (GetExtendedListViewStyle() & ~(Style));\
    SetExtendedListViewStyle(listViewStyleEx,0);\
    SetModified();\
}\
    BOOL Class::get_##Name(void)\
    {\
    DWORD val=GetExtendedListViewStyle();\
    return (val & (Style))==Style;\
}
    
    class CStripedListViewComp:public CStripedListView,public ControlComponent<CStripedListViewComp>
	{
	public:
		CStripedListViewComp(LPTSTR _name=NULL);
		~CStripedListViewComp(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP_EX(CStripedListViewComp)
			CHAIN_MSG_MAP(ControlComponent<CStripedListViewComp>)
            CHAIN_MSG_MAP(CStripedListView)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoArrange)
		DECLARE_WINSTYLE_BOOL_PROPERTY(EditLabels)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoColumnHeader)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoLabelWrap)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoSortHeader)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OwnerData)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OwnerDrawFixed)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ShareImageLists)
		DECLARE_WINSTYLE_BOOL_PROPERTY(ShowSelAlways)
		DECLARE_WINSTYLE_BOOL_PROPERTY(SingleSel)
		DECLARE_WINSTYLE_PROPERTY(ListStyle)
		DECLARE_WINSTYLE_PROPERTY(Alignment)
		DECLARE_WINSTYLE_PROPERTY(Sort)
		

		///common styles
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoDivider)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoMoveY)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoParentAlign)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoResize)
		//DECLARE_WINSTYLE_BOOL_PROPERTY(HotTrack)

        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(CheckBoxes)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(GridLines)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(SubItemImages)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(TrackSelect)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(HeaderDragAndDrop)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(FullRowSelect)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(OneClickActivate)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(TwoClickActivate)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(FlatSB)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(Regional)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(InfoTip)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(UnderLineHot)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(UnderLineCold)
        DECLARE_LISTVIEWEXSTYLE_BOOL_PROPERTY(MultiWorkAreas)

        DECLARE_PROPERTY(FirstColor,CColorref)
        DECLARE_PROPERTY(SecondColor,CColorref)

	};
};
#endif   

////////////////////////////////////////////////////////////////////////////////////////////////
#endif 
