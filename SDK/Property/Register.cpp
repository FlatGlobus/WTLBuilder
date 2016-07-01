// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "Register.h"
//добавить обработку нулевого имени и страницы
///////////////////////////////////////////////////////////////////////////////////////////////
//__RegisterComponent::__RegisterComponent(LPCSTR Name, LPCSTR Cp,UINT ID,CAppModule *m):page(Cp),name(Name),bitmap(NULL),resID(ID),
//module(m)
//{
//	RegisterEvent(iGetComponentInfo,this,&__RegisterComponent::GetInfo);
//	RegisterEvent(iCreateComponent,this,&__RegisterComponent::Create);
//	RegisterEvent(iGetComponentBitmap,this,&__RegisterComponent::GetComponentBitmap);
//}
///////////////////////////////////////////////////////////////////////////////////////////////
/*__RegisterComponent::~__RegisterComponent(void)
{
	UnRegisterEvent(this);
	if(bitmap)
		::DeleteObject(bitmap);
}
///////////////////////////////////////////////////////////////////////////////////////////////
void __RegisterComponent::GetInfo(int _type)
{
	if(name!=NULL && page!=NULL && (_type & type))
	{
		SendEvent(iSendComponentInfo,name,page,LoadBitmap(),type);
		if(bitmap)
			::DeleteObject(bitmap);

		bitmap=NULL;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL __RegisterComponent::CheckComponentName(LPCSTR _name,LPCSTR _page)
{
	if(strcmp(_name,name)==0 && strcmp(_page,page)==0)
		return TRUE;
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void __RegisterComponent::GetComponentBitmap(LPCSTR _name,LPCSTR _page,HBITMAP * bitmap)
{
    if(CheckComponentName(_name,_page) && bitmap!=NULL)
    {
        *bitmap=LoadBitmap();
	    StopEvent(iGetComponentBitmap);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
HBITMAP __RegisterComponent::LoadBitmap(void)
{
	if(bitmap==NULL)
		bitmap=::LoadBitmap(module->GetResourceInstance(),MAKEINTRESOURCE(resID));
	return bitmap;
}
///////////////////////////////////////////////////////////////////////////////////////////////
*/