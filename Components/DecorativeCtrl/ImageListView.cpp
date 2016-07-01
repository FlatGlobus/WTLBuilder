// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#ifdef __WTLBUILDER__
#include "imagelistview.h"
#include "resource.h"

namespace DecorativeCtrl
{
    REGISTER_COMPONENT_EX(CImageListView,CImageListViewComp,DecorativeCtrl,IDB_IMAGEVIEW)

    CImageListViewComp::CImageListViewComp(LPTSTR _name):ControlComponent<DecorativeCtrl::CImageListViewComp>(_name)
    {
    }

    CImageListViewComp::~CImageListViewComp(void)
    {
    }

    BOOL CImageListViewComp::CreateComponent(Component * _Parent)
    {
        SetComponentParent(_Parent);
        Create((HWND)_Parent->GetHandle(),GetBoundsRect(),style);
        return ::IsWindow(m_hWnd);
    }

    void CImageListViewComp::InitProperty(void)
    {
        bitmap.Change.SetObject(this);
        bitmap.Change.SetMethod(&CImageListViewComp::OnImageChange);
        ControlComponent<CImageListViewComp>::InitProperty();
        HIDE_PROPERTY(Font)
        BEGIN_SUB_PROPERTY(_T("Style"),CImageListViewComp)
            DEFINE_SUB_PROPERTY(Transparent,BOOL,CImageListViewComp,TRUE)
            DEFINE_SUB_PROPERTY(Mask,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(Image,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(Blend25,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(Blend50,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(OverlayMask,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(PreserveAlpha,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(Scale,BOOL,CImageListViewComp,FALSE)
            DEFINE_SUB_PROPERTY(DPIScale,BOOL,CImageListViewComp,FALSE)
        END_SUB_PROPERTY

        BEGIN_SUB_PROPERTY(_T("ImageSize"),CImageListViewComp)
            DEFINE_SUB_PROPERTY(cx,long,CImageListViewComp,16)
            DEFINE_SUB_PROPERTY(cy,long,CImageListViewComp,15)
        END_SUB_PROPERTY

        DEFINE_PROPERTY(ImageBkColor,CColorref,CImageListViewComp,GetImageBkColor())
        DEFINE_PROPERTY(MaskColor,CColorref,CImageListViewComp,GetMaskColor())
        DEFINE_PROPERTY(BkColor,CColorref,CImageListViewComp,GetBkColor())
        bitmap.AddProperty(_T("Bitmap"),objprop);
    }

    void CImageListViewComp::OnImageChange(CImage * image)
    {
        if((HBITMAP)bitmap)
            LoadBitmapImage(image->get_FileName());
        else
            Clear();

        SetModified();
    }

    void CImageListViewComp::ReCreateImageList()
    {
        if(!images.IsNull())
        {
            LoadBitmapImage(bitmap.get_FileName());
        }
    }

    void CImageListViewComp::set_ImageBkColor(CColorref val)
    {
        SetImageBkColor(val);
        ReCreateImageList();
        SetModified();
    }

    CColorref CImageListViewComp::get_ImageBkColor()
    {
        return GetImageBkColor();
    }

    void CImageListViewComp::set_BkColor(CColorref val)
    {
        SetBkColor(val);
        SetModified();
    }

    CColorref CImageListViewComp::get_BkColor()
    {
        return GetBkColor();
    }

    void CImageListViewComp::set_MaskColor(CColorref val)
    {
        SetMaskColor(val);
        ReCreateImageList();
        SetModified();
    }

    CColorref CImageListViewComp::get_MaskColor()
    {
        return GetMaskColor();
    }

    void CImageListViewComp::set_cx(long val)
    {
        SetWidth(val);
        ReCreateImageList();
        SetModified();
    }

    long CImageListViewComp::get_cx()
    {
        return GetWidth();
    }

    void CImageListViewComp::set_cy(long val)
    {
        SetHeight(val);
        ReCreateImageList();
        SetModified();
    }

    long CImageListViewComp::get_cy()
    {
        return GetHeight();
    }

};
#endif