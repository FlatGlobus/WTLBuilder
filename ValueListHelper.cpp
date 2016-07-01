// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "ValueListHelper.h"
#include "PropertyItem.h"


long __stdcall CValueListHelper::GetValCount(BSTR customValName)
{
    CCustomVal * values=GetCustomVal(CString(customValName));
    if(values)
    {
        long i=0;
        for (i = 0; values[i].name!=NULL; i++);
        return i;
    }
    return 0;
}

BSTR __stdcall CValueListHelper::GetValName(BSTR customValName,long idx)
{
    CCustomVal * values=GetCustomVal(CString(customValName));
    if(values)
    {
        long i=0;
        for (i = 0; values[i].name!=NULL && i != idx ; i++);

        if(i==idx && values[i].name!=NULL)
        {
            CString str(values[i].decorate);
            return str.AllocSysString();
        }
    }
    return NULL;
}

long __stdcall CValueListHelper::GetValID(BSTR customValName,long idx)
{
    CCustomVal * values=GetCustomVal(CString(customValName));
    if(values)
    {
        long i=0;
        for (i = 0; values[i].name!=NULL && i != idx ; i++);

        if(i==idx && values[i].name!=NULL)
            return values[i].id;
    }
    return 0;
}
