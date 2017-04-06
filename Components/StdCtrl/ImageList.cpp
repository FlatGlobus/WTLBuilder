// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "imagelist.h"
#include "resource.h"
#include "PropertyListEdit.h"

typedef long ImageListFlags; 
static void RegisterImageListStyles();
namespace StdCtrl
{
REGISTER_COMPONENT(CImageList,StdCtl,IDB_IMAGELIST)

CImageList::CImageList(LPTSTR _name):Component(_name),bitmap(BITMAP_TYPE)
{
    RegisterImageListStyles();
    enableTabIndex=FALSE;
}

CImageList::~CImageList(void)
{
}

BOOL CImageList::CreateComponent(Component *_Parent)
{
    return Component::CreateComponent(_Parent);
}

void CImageList::InitProperty(void)
{
    bitmap.Change.SetObject(this);
    bitmap.Change.SetMethod(&CImageList::OnImageChange);
    Component::InitProperty();
    DEFINE_PROPERTY(Flag,ImageListFlags,CImageList,ILC_MASK)
    DEFINE_PROPERTY(BkColor,CColorref,CImageList,RGB(0,0,0))
    DEFINE_PROPERTY(Mask,CColorref,CImageList,RGB(0,0,0))
    DEFINE_PROPERTY(ImageCount,long,CImageList,0)
    DEFINE_PROPERTY(Grow,long,CImageList,0)
    BEGIN_SUB_PROPERTY(_T("ImageSize"),CImageList)
        DEFINE_SUB_PROPERTY(cx,long,CImageList,16)
        DEFINE_SUB_PROPERTY(cy,long,CImageList,16)
    END_SUB_PROPERTY
    bitmap.AddProperty(_T("Bitmap"),objprop);
}

void CImageList::OnImageChange(CImage * image)
{
    if(image)
    {
        InternalCreate();
        Add((HBITMAP)*image,(COLORREF)maskColor);
    }
    SetModified();
}



void CImageList::set_BkColor(CColorref val)
{
    bkColor=val;
    SetModified();
}

CColorref CImageList::get_BkColor(void)
{
    return bkColor;
}

void CImageList::set_Mask(CColorref val)
{
    maskColor=val;
    //OnImageChange(&bitmap);
    SetModified();
}

CColorref CImageList::get_Mask(void)
{
    return maskColor;
}

void CImageList::set_cx(long val)
{
    cx=val;
    InternalCreate();
    SetModified();
}

long CImageList::get_cx()
{
    return cx;
}

void CImageList::set_cy(long val)
{
    cy=val;
    InternalCreate();
    SetModified();
}

long CImageList::get_cy()
{
    return cy;
}

void CImageList::set_ImageCount(long val)
{
    imageCount=val;
    SetModified();
}

long CImageList::get_ImageCount()
{
    return imageCount;
}

void CImageList::set_Grow(long val)
{
    grow=val;
    InternalCreate();
    SetModified();
}

long CImageList::get_Grow()
{
    return grow;
}

void CImageList::set_Flag(long val)
{
    flag=val;
    InternalCreate();
    SetModified();
}

long CImageList::get_Flag()
{
    return flag;
}

void CImageList::set_Constructor(CString val)
{
    constructor=val;
    SetModified();
}

CString CImageList::get_Constructor(void)
{
    return constructor;
}

void CImageList::InternalCreate(void)
{
    Destroy();
    if(cx!=0 && cy!=0 && flag!=0)
        Create(cx,cy,flag,1,grow);
}
}

BEGIN_LIST_PROPERTY(ImageListFlags)
    LIST_ITEM(ILC_MASK,Mask)
    LIST_ITEM(ILC_COLOR,Color)
    LIST_ITEM(ILC_COLORDDB,ColorDDB)
    LIST_ITEM(ILC_COLOR4,Color4)
    LIST_ITEM(ILC_COLOR8,Color8)
    LIST_ITEM(ILC_COLOR16,Color16)
    LIST_ITEM(ILC_COLOR24,Color24)
    LIST_ITEM(ILC_COLOR32,Color32)
END_LIST_ITEM(ImageListFlags)

static void RegisterImageListStyles()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;
    REGISTER_LIST_PROPERTY(ImageListFlags)
    IsInited=TRUE;    
}
//////////////////////////////////////////////////////////////////////////
