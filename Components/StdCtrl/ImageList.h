// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __IMAGELIST_H
#define __IMAGELIST_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
	class CImageList:public WTL::CImageList,public Component
	{
        CColorref bkColor,maskColor;
        long cx,cy,imageCount,grow,flag;
        CImage bitmap;
        CString constructor;
        void OnImageChange(CImage *);
        void InternalCreate(void);
	public:
	CImageList(LPTSTR _name=NULL);
	~CImageList(void);
        virtual BOOL CreateComponent(Component *);
		virtual void InitProperty(void);
        DECLARE_PROPERTY(BkColor,CColorref)
        DECLARE_PROPERTY(Mask,CColorref)
        DECLARE_PROPERTY(cx,long)
        DECLARE_PROPERTY(cy,long)
        DECLARE_PROPERTY(Grow,long)
        DECLARE_PROPERTY(ImageCount,long)
        DECLARE_PROPERTY(Flag,long)
        DECLARE_PROPERTY(Constructor,CString)
        virtual CString GetComponetKind(){return _T("IMAGELIST");}
	};
}
//////////////////////////////////////////////////////////////////////////
#endif
