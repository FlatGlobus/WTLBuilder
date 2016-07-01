// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SCRIPT_ERROR_H
#define __SCRIPT_ERROR_H
/////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

class CScriptError
{
public:
    CScriptError();
    CScriptError(const CString &error, const CString & descr, long line, long pos);
	CScriptError(const CString &file,const CString &error, const CString & descr, long line, long pos);
    const CString & GetError();
    const CString & GetDescr();
    void SetFile(const CString & _file);
    const CString & GetFile();
    long GetLine();
    long GetPos();
protected:
    long line;
	long pos;
    CString error;
    CString descr;
    CString file;
};

typedef std::vector<CScriptError *> CScriptErrorVector;
///////////////////////////////////////////////////////////////////////////////////////
inline CScriptError::CScriptError()
{
}

inline CScriptError::CScriptError(const CString &_error, const CString & _descr, long _line, long _pos):
error(_error),descr(_descr),line(_line),pos(_pos)
{
}

inline CScriptError::CScriptError(const CString & _file,const CString &_error, const CString & _descr, long _line, long _pos):
file(_file),error(_error),descr(_descr),line(_line),pos(_pos)
{
}

inline const CString & CScriptError::GetError()
{
    return error;
}
inline const CString & CScriptError::GetDescr()
{
    return descr;
}

inline long CScriptError::GetLine()
{
    return line;
}

inline long CScriptError::GetPos()
{
    return pos;
}

inline void CScriptError::SetFile(const CString & _file)
{
    file = _file;
}

inline const CString & CScriptError::GetFile()
{
    return file;
}
/////////////////////////////////////////////////////////////////////////////////////////
#endif