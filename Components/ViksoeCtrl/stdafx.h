// TODO: reference additional headers your program requires here
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _WIN32_WINNT 0x0600
#include <WinSDKVer.h>

#define _WTL_NO_THEME_DELAYLOAD
#define _WTL_NO_CSTRING

#include "warning.h"

#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>
#include "atlshellextbase.h"

class CExAppModule : public CAppModule
{
public:
    CShellMalloc m_Allocator;
};

extern CExAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <AtlMisc.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include "EventLib.h"
#include "component.h"
#include "ctrlcomponent.h"
#include "resource.h"
#include "Register.h"
//#include "mmgr.h"

#pragma comment( lib, "utils.lib" )
#pragma comment( lib, "event.lib" )
//#pragma comment( lib, "mmgr.lib" )
#pragma comment( lib, "property.lib" )

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

