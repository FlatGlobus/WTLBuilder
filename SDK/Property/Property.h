// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROPERTY_H
#define __PROPERTY_H

#ifdef PROPERTY_EXPORTS
#define PROPERTY_API __declspec( dllexport )
#else
#define PROPERTY_API
//#define PROPERTY_API __declspec ( dllimport )//to avoid a bug in VC++2003
#pragma comment( lib,"Property.lib")
#endif

//////////////////////////////////////////////////////////////////////////
#endif