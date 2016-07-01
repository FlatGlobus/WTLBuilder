// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __REGISTER_H
#define __REGISTER_H
//////////////////////////////////////////////////////////////////////////
#include "EventLib.h"
#include "Command.h"
#include <atlmisc.h>

#pragma warning( disable:4251)

#define TypeComponent 0x1
#define TypeForm 0x2

class Component;

class  __RegisterComponent
{
public:
    __RegisterComponent(LPCTSTR Name, LPCTSTR Cp,UINT ID):page(Cp),name(Name),bitmap(NULL),resID(ID)
    {
        RegisterEvent(evGetComponentInfo,this,&__RegisterComponent::GetInfo);
        RegisterEvent(evCreateComponent,this,&__RegisterComponent::Create);
        RegisterEvent(evGetComponentBitmap,this,&__RegisterComponent::GetComponentBitmap);
    }
    __RegisterComponent::~__RegisterComponent(void)
    {
        UnRegisterEvent(this);
        if(bitmap)
            ::DeleteObject(bitmap);
    }

    void GetInfo(int _type)
    {
        if(name!=NULL && page!=NULL && (_type & type))
        {
            SendEvent(evSendComponentInfo,name,page,LoadBitmap(),type);
            if(bitmap)
                ::DeleteObject(bitmap);

            bitmap=NULL;
        }
    }

    void GetComponentBitmap(LPCTSTR _name,LPCTSTR _page,HBITMAP * bitmap)
    {
        if(CheckComponentName(_name,_page) && bitmap!=NULL)
        {
            *bitmap=LoadBitmap();
            StopEvent(evGetComponentBitmap);
        }
    }
protected:
    BOOL CheckComponentName(LPCTSTR _name,LPCTSTR _page)
    {
        if(_tcscmp(_name,name)==0 && _tcscmp(_page,page)==0)
            return TRUE;
        return FALSE;
    }

    HBITMAP LoadBitmap(void)
    {
        if(bitmap==NULL)
            bitmap=AtlLoadBitmap(MAKEINTRESOURCE(resID));
        return bitmap;
    }

	virtual void Create(LPCTSTR _name,LPCTSTR _page,Component **objPtr) = 0;
public:
	LPCTSTR		name;
	LPCTSTR		page;
	HBITMAP		bitmap;
	UINT		resID;
	int		type;
};
//////////////////////////////////////////////////////////////////////////
#define REGISTER_COMPONENT(Name,Page,ID)\
class _RegisterComponent##Name:public __RegisterComponent\
{\
public:\
    inline _RegisterComponent##Name(LPCTSTR _name, LPCTSTR _page,UINT _ID):__RegisterComponent(_name, _page,_ID)\
						{type=TypeComponent;}\
    virtual void Create(LPCTSTR n,LPCTSTR p,Component **objPtr)\
    {\
		if(CheckComponentName(n,p))\
		{\
	    	*objPtr=(Component *)new Name(_T(#Page)##_T(":")##_T(#Name));\
			StopEvent(evCreateComponent);\
		}\
    }\
}; static _RegisterComponent##Name _Component##Name##(_T(#Name),_T(#Page),ID);
//////////////////////////////////////////////////////////////////////////
#define REGISTER_COMPONENT_EX(FriendlyName,Name,Page,ID)\
   class _RegisterComponent##Name:public __RegisterComponent\
{\
public:\
   inline _RegisterComponent##Name(LPCTSTR _name, LPCTSTR _page,UINT _ID):__RegisterComponent(_name, _page,_ID)\
{type=TypeComponent;}\
   virtual void Create(LPCTSTR n,LPCTSTR p,Component **objPtr)\
{\
   if(CheckComponentName(n,p))\
{\
    *objPtr=(Component *)new Name(_T(#Page)##_T(":")##_T(#FriendlyName));\
	StopEvent(evCreateComponent);\
}\
}\
};  static _RegisterComponent##Name _Component##Name##(_T(#FriendlyName),_T(#Page),ID);
//////////////////////////////////////////////////////////////////////////
#define REGISTER_FORM(Name,Page)\
class  _RegisterComponent##Name:public __RegisterComponent\
{\
public:\
	inline _RegisterComponent##Name(LPCTSTR _name, LPCTSTR _page):__RegisterComponent(_name, _page,0)\
	{type=TypeForm;}\
	virtual void Create(LPCTSTR n,LPCTSTR p,Component **objPtr)\
	{\
		if(CheckComponentName(n,p))\
		{\
			*objPtr=(Component *)new Name(_T(#Page)##_T(":")##_T(#Name));\
			StopEvent(evCreateComponent);\
		}\
	}\
}; static _RegisterComponent##Name _Component##Name##(_T(#Name),_T(#Page));
//////////////////////////////////////////////////////////////////////////
class  __RegisterPage
{
public:
    __RegisterPage(LPCTSTR _pageName,UINT ID):pageName(_pageName),bitmap(NULL),resID(ID)
    {
        RegisterEvent(evGetPageBitmap,this,&__RegisterPage::GetPageBitmap);
    }
    __RegisterPage::~__RegisterPage(void)
    {
        UnRegisterEvent(this);
        if(bitmap)
            ::DeleteObject(bitmap);
    }

    void GetPageBitmap(LPCTSTR _pageName,HBITMAP * bitmap)
    {
        if(CheckName(_pageName) && bitmap!=NULL)
        {
            *bitmap=LoadBitmap();
            StopEvent(evGetPageBitmap);
        }
    }
protected:
    BOOL CheckName(LPCTSTR _pageName)
    {
        if(_tcscmp(_pageName,pageName)==0)
            return TRUE;
        return FALSE;
    }

    HBITMAP LoadBitmap(void)
    {
        if(bitmap==NULL)
            bitmap=::LoadBitmap(_Module.GetResourceInstance(),MAKEINTRESOURCE(resID));
        return bitmap;
    }
public:
    LPCTSTR		pageName;
    HBITMAP		bitmap;
    UINT		resID;
};
//////////////////////////////////////////////////////////////////////////
#define REGISTER_PAGE(Page,ID) static __RegisterPage _page##Page##(_T(#Page),ID);
//////////////////////////////////////////////////////////////////////////

#endif
