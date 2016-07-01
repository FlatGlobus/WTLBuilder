// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __SHELLPROPMACRO_H 
#define __SHELLPROPMACRO_H
//////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_SHELL_BOOL_PROPERTY(Class,Name,Style)\
    void Class::set_##Name(BOOL val)\
{\
    DWORD tempVal = val == TRUE ? (GetShellStyle() | (Style)) : (GetShellStyle() & ~(Style));\
    SetShellStyle(tempVal);\
    Populate(path);\
    SetModified();\
}\
    BOOL Class::get_##Name(void)\
{\
    long val=GetShellStyle();\
    return (val & (Style))==Style;\
}

//////////////////////////////////////////////////////////////////////////
#endif