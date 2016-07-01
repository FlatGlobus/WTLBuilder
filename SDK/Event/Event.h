// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __EVENT_H
#define __EVENT_H
//////////////////////////////////////////////////////////////////////////
#ifdef EVENT_EXPORTS
        #define EVENT_API __declspec(dllexport)
#else
        #define EVENT_API __declspec(dllimport)
        #pragma comment( lib, "event.lib" )
#endif
//////////////////////////////////////////////////////////////////////////
#endif

