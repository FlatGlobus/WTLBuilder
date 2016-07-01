// ***************************************************************
//  GridCtrl   version:  1.0   ·  date: 07/06/2007
//  Written by Vlad Tembekov (http://www.wtlbuilder.com)
//  Copyright (C) 2007 - All Rights Reserved Vlad Tembekov
// ***************************************************************
//  This code may be used in compiled form in any way you desire. This
//  file may be redistributed by any means PROVIDING it is 
//  not sold for profit without the authors written consent, and 
//  providing that this notice and the authors name is included. 
//
//  This file is provided "as is" with no expressed or implied warranty.
//  The author accepts no liability if it causes any damage to you or your
//  computer whatsoever.
// ***************************************************************
#include "stdafx.h"
#ifdef __WTLBUILDER__
#include "atlstr.h"
#include "GridCtrl.h"
#include "resource.h"
#include "ComponentList.h"


void GridCtrlCellEdit(HWND parent,PropertyBase *prop,LPARAM);

namespace DecorativeCtrl
{
    typedef long GridCtrlCellEditType; 
    //static void RegisterGridCtrlEdit();
    REGISTER_COMPONENT_EX(CGridCtrl,CGridCtrlComp,DecorativeCtrl,IDB_GRIDCTRL)

    CGridCtrlComp::CGridCtrlComp(LPTSTR _name):ControlComponent<DecorativeCtrl::CGridCtrlComp>(_name)
    {
        SetDefaultSize(100,80);
        //RegisterGridCtrlEdit();
    }


    CGridCtrlComp::~CGridCtrlComp(void)
    {
    }

    BOOL CGridCtrlComp::CreateComponent(Component * _Parent)
    {
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),GetBoundsRect(),NULL,get_InternalWindowStyle(),get_InternalWindowStyleEx());
        return ::IsWindow(m_hWnd);
    }

    void CGridCtrlComp::InitProperty(void)
    {
        ControlComponent<CGridCtrlComp>::InitProperty();
//        PUBLIC_PROPERTY(Font,false)
//        DEFINE_PROPERTY(LineNumbers,BOOL,CGridCtrlComp,TRUE)
//        DEFINE_PROPERTY(ContextMenu,BOOL,CGridCtrlComp,FALSE)
//        DEFINE_PROPERTY(ReadOnly,BOOL,CGridCtrlComp,FALSE)
//        DEFINE_PROPERTY(VerticalLines,BOOL,CGridCtrlComp,TRUE)
//        DEFINE_PROPERTY(HorizontalLines,BOOL,CGridCtrlComp,TRUE)
//        DEFINE_PROPERTY(Listener,BOOL,CGridCtrlComp,TRUE)
//        DEFINE_PROPERTY_2(Cell,GridCtrlCellEditType,CGridCtrlComp,0)

//        cellFont.AddProperty("CellFont",objprop);
//        cellFont.Change.SetObject(this);
        //cellFont.Change.SetMethod(&CGridCtrlComp::OnCellFontChange);

        //headerFont.AddProperty("HeaderFont",objprop);
        //headerFont.Change.SetObject(this);
        //headerFont.Change.SetMethod(&CGridCtrlComp::OnHeaderFontChange);
    }

   //void CGridCtrlComp::set_LineNumbers(BOOL val)
   //{
   //    SetExtendedGridStyle(val ? GS_EX_LINENUMBERS : 0, val==0 ? GS_EX_LINENUMBERS : 0);
   //    SetModified();
   //}
   //
   //BOOL CGridCtrlComp::get_LineNumbers(void)
   //{
   //   return (GetExtendedGridStyle() & GS_EX_LINENUMBERS)!=0;
   //}

   //void CGridCtrlComp::set_ContextMenu(BOOL val)
   //{
   //    SetExtendedGridStyle(val ? GS_EX_CONTEXTMENU : 0, val==0 ? GS_EX_CONTEXTMENU : 0);
   //    SetModified();
   //}
   //
   //BOOL CGridCtrlComp::get_ContextMenu(void)
   //{
   //   return (GetExtendedGridStyle() & GS_EX_CONTEXTMENU)!=0;
   //}

   //void CGridCtrlComp::set_ReadOnly(BOOL val)
   //{
   //    SetExtendedGridStyle(val ? GS_EX_READONLY : 0, val==0 ? GS_EX_READONLY : 0);
   //    SetModified();
   //}
   //
   //BOOL CGridCtrlComp::get_ReadOnly(void)
   //{
   //   return (GetExtendedGridStyle() & GS_EX_READONLY)!=0;
   //}

   //void CGridCtrlComp::set_VerticalLines(BOOL val)
   //{
   //    SetExtendedGridStyle(val ? GS_EX_VGRIDLINES : 0, val==0 ? GS_EX_VGRIDLINES : 0);
   //    SetModified();
   //}

   //BOOL CGridCtrlComp::get_VerticalLines(void)
   //{
   //    return (GetExtendedGridStyle() & GS_EX_VGRIDLINES)!=0;
   //}

   //void CGridCtrlComp::set_HorizontalLines(BOOL val)
   //{
   //    SetExtendedGridStyle(val ? GS_EX_HGRIDLINES : 0, val==0 ? GS_EX_HGRIDLINES : 0);
   //    SetModified();
   //}

   //BOOL CGridCtrlComp::get_HorizontalLines(void)
   //{
   //    return (GetExtendedGridStyle() & GS_EX_HGRIDLINES)!=0;
   //}

   //void CGridCtrlComp::OnCellFontChange(CFontEx *font)
   //{
   //     SetCellFont(*font);
   //     SetModified();
   //}

   //void CGridCtrlComp::OnHeaderFontChange(CFontEx *font)
   //{
   //     SetHeaderFont(*font);
   //     SetModified();
   //}

   //void CGridCtrlComp::set_Listener(BOOL val)
   //{
   //    if(listener!=val)
   //    {
   //        listener=val;
   //        SetModified();
   //    }
   //}

   //BOOL CGridCtrlComp::get_Listener()
   //{
   //    return listener;
   //}

//static void RegisterGridCtrlEdit()
//{
//	static BOOL IsInited=FALSE;
//
//	if(IsInited==TRUE)
//		return;
//	RegisterEdit("GridCtrlCellEditType",NULL,GridCtrlCellEdit);
//
//	IsInited=TRUE;
//}

};
#endif