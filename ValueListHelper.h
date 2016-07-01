// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __VALUELISTHELPER_H
#define __VALUELISTHELPER_H
//////////////////////////////////////////////////////////////////////////
class CValueListHelper : public IDispDynImpl<CValueListHelper>
{
public:

    BEGIN_DISPATCH_MAP(CValueListHelper)
        DISP_METHOD(GetValCount, VT_I4, 1, VTS_BSTR)
        DISP_METHOD(GetValID, VT_I4, 2, VTS_BSTR VTS_I4)
        DISP_METHOD(GetValName, VT_BSTR, 2, VTS_BSTR VTS_I4)
    END_DISPATCH_MAP()

    long __stdcall GetValCount(BSTR customValName);
    long __stdcall GetValID(BSTR customValName,long idx);
    BSTR __stdcall GetValName(BSTR customValName,long idx);
};
//////////////////////////////////////////////////////////////////////////
#endif