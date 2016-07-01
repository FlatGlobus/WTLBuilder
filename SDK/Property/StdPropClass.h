// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __STDPROPCLASS_H
#define __STDPROPCLASS_H
//////////////////////////////////////////////////////////////////////////
class PROPERTY_API CPointEx:public CPoint
{
public:
    CPointEx():CPoint()
    {
    }
    
    DECLARE_PROPERTY(x,int)
    DECLARE_PROPERTY(y,int)

    void AddProperty(LPCTSTR Name,CProperties & objprop);

    DECLARE_CALLBACK(Change,change)
};

class PROPERTY_API CSizeEx:public CSize
{
public:
    CSizeEx():CSize()
    {
    }

    DECLARE_PROPERTY(cx,int)
    DECLARE_PROPERTY(cy,int)

    void AddProperty(LPCTSTR Name,CProperties & objprop);

    DECLARE_CALLBACK(Change,change)
};

class PROPERTY_API CRectEx:public CRect
{
public:
    CRectEx():CRect()
    {
    }

    DECLARE_PROPERTY(Left,int)
    DECLARE_PROPERTY(Top,int)
    DECLARE_PROPERTY(Right,int)
    DECLARE_PROPERTY(Bottom,int)

    void AddProperty(LPCTSTR Name,CProperties & objprop);

    DECLARE_CALLBACK(Change,change)

};
//////////////////////////////////////////////////////////////////////////
#endif