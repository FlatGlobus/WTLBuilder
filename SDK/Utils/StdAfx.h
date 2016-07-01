#pragma once

#define _WIN32_WINNT 0x0600
#include <WinSDKVer.h>

#define _WTL_NO_THEME_DELAYLOAD
#define _WTL_NO_CSTRING

#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable:4838)

#include <atlstr.h>
#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
extern CAppModule _Module;
#include <atlcom.h>
#include <atlhost.h>
#include <atlctl.h>
#include <atlgdi.h>
#include <atlctrls.h>
#include <atlcrack.h>
#include <atlmisc.h>
//#include "..\mmgr\mmgr.h"
