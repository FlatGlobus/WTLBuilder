
#pragma once

#define _WIN32_WINNT 0x0600
#include <WinSDKVer.h>

#define _ATL_STATIC_REGISTRY
#define _WTL_NO_THEME_DELAYLOAD
#define _WTL_NO_CSTRING

#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable:4838)

#include <windows.h>
#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <AtlMisc.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlctrlx.h>
#include "resource.h"
#include "EventLib.h"
#include "SDK\Command.h"
#include "PropertyItem.h"
//#include "SDK\mmgr\mmgr.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
