// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#ifndef __UTIL_H
#define __UTIL_H

#define KEYDOWN(Key) ((GetKeyState(Key)&0x8000)!=0)
/////////////////////////////////////////////////////////////////////////////////////////
//замечательное округление
template <class T> inline long _round(T val)
{
	return val > 0 ? (long)(val+.5) : (long)(val-.5);
}

template <class T> inline void _swap(T & val1,T & val2)
{
	T val=val1;
	val1=val2;
	val1=val;
}

template <class T> inline int sign(T val)
{
	return val >= 0 ? 1 : -1;
}

//расстояние между точками
unsigned long Distanse(CPoint & pt1,CPoint & pt2);
//расстояние между точкой и отрезком
unsigned long Distanse(CPoint &pt,CPoint &pt1,CPoint &pt2);

//попадание точки в прямоугольник
inline BOOL PtInRect(CRect &rc,CPoint& point)
{
	return point.x >= rc.left && point.x <= rc.right
		&& point.y >= rc.top && point.y <= rc.bottom;
}
//попадание прямоугольника rc2 в прямоугольник rc1
inline BOOL RectInRect(CRect &rc1,CRect& rc2)
{
	return rc2.left >= rc1.left && rc2.right <= rc1.right
		&& rc2.top >= rc1.top && rc2.bottom <= rc1.bottom;
}

inline void NormalizeRect(CRect & rc)
{
	if(rc.left > rc.right)
        _swap(rc.left,rc.right);
	if(rc.top > rc.bottom)
		_swap(rc.top,rc.bottom);
}

inline CString MakeString(LPCTSTR fmt,...)
{
    CString valstr;

    va_list argList;
    va_start(argList, fmt);
    valstr.FormatV(fmt, argList);
    va_end(argList);

    return valstr;
}

/////////////////////////////////////////////////////////////////////////////////////////
inline BOOL IsIdentifier(const CString str)
{
    BOOL retFlag=FALSE;
    if(str.GetLength()==0)
        return retFlag;

    if(_istalpha(str[0])==TRUE || str[0] == _T('_'))
    {
        retFlag = TRUE;
        for(int i = 1 ; i <str.GetLength(); i++)
            if(__iscsym(str[i]) == FALSE)
            {
                retFlag = FALSE;
                break;
            }
    }

    return retFlag;
}

template <class T> inline int FindItem(const CSimpleArray<T> &array,const T &val)
{
    for(int i=0; i < array.GetSize();i++)
        if(array[i]==val)
            return i;
    return -1;
}

inline BOOL ExtractName(const CString &str, CString &cmpPage, CString &cmpName)
{
	int pos = str.Find(':');
	if (pos == -1)
		return FALSE;

	cmpName = str.Right(str.GetLength() - (pos + 1));
	cmpPage = str.Left(pos);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////
#endif