// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "StdPropClass.h"
//////////////////////////////////////////////////////////////////////////
void CPointEx::AddProperty(LPCTSTR Name,CProperties & objprop)
{
    BEGIN_SUB_PROPERTY(Name,CPointEx)
        DEFINE_SUB_PROPERTY(x,int,CPointEx,0)
        DEFINE_SUB_PROPERTY(y,int,CPointEx,0)
    END_SUB_PROPERTY
}

void CPointEx::set_x(int val)
{
    x=val;
    change(this);
}

int CPointEx::get_x()
{
    return x;
}

void CPointEx::set_y(int val)
{
    y=val;
    change(this);
}

int CPointEx::get_y()
{
    return y;
}
//////////////////////////////////////////////////////////////////////////
void CSizeEx::AddProperty(LPCTSTR Name,CProperties & objprop)
{
    BEGIN_SUB_PROPERTY(Name,CSizeEx)
        DEFINE_SUB_PROPERTY(cx,int,CSizeEx,0)
        DEFINE_SUB_PROPERTY(cy,int,CSizeEx,0)
    END_SUB_PROPERTY
}

void CSizeEx::set_cx(int val)
{
    cx=val;
    change(this);
}

int CSizeEx::get_cx()
{
    return cx;
}

void CSizeEx::set_cy(int val)
{
    cy=val;
    change(this);
}

int CSizeEx::get_cy()
{
    return cy;
}
//////////////////////////////////////////////////////////////////////////
void CRectEx::AddProperty(LPCTSTR Name,CProperties & objprop)
{
    BEGIN_SUB_PROPERTY(Name,CRectEx)
        DEFINE_SUB_PROPERTY(Left,int,CRectEx,0)
        DEFINE_SUB_PROPERTY(Top,int,CRectEx,0)
        DEFINE_SUB_PROPERTY(Right,int,CRectEx,0)
        DEFINE_SUB_PROPERTY(Bottom,int,CRectEx,0)
    END_SUB_PROPERTY
}

void CRectEx::set_Left(int val)
{
    left=val;
    change(this);
}

int CRectEx::get_Left()
{
    return left;
}

void CRectEx::set_Top(int val)
{
    top=val;
    change(this);
}

int CRectEx::get_Top()
{
    return top;
}

void CRectEx::set_Right(int val)
{
    right=val;
    change(this);
}

int CRectEx::get_Right()
{
    return right;
}

void CRectEx::set_Bottom(int val)
{
    bottom=val;
    change(this);
}

int CRectEx::get_Bottom()
{
    return bottom;
}