// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once

#define _WIN32_WINNT 0x0600
#include <WinSDKVer.h>

#define _WTL_NO_THEME_DELAYLOAD
#define WIN32_LEAN_AND_MEAN
//#define WINVER		0x0600
//#define _WIN32_WINNT	0x0600
//#define _WIN32_IE	0x0600
//#define _RICHEDIT_VER	0x0300
#define _WTL_NO_CSTRING

#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable:4838)

#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlgdi.h>
#include <atlmisc.h>
#include <atlctrls.h>
#include <atlframe.h>
#include "EventLib.h"
#include "command.h"
#include "Property.h"
#include "Component.h"
//#include "mmgr.h"

