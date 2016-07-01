// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "Event.h"
//////////////////////////////////////////////////////////////////////////
#pragma data_seg (".Evt")
extern HANDLE hModule;
HHOOK g_hHookKbd = NULL;		
HHOOK g_hHookMouse = NULL;
DWORD	g_dwLastInputTick = 0;
#pragma data_seg ()

EVENT_API DWORD GetLastInputTime()
{
	return GetTickCount()-g_dwLastInputTick;
}

/////////////////
// Keyboard hook: record tick count
//
LRESULT CALLBACK MyKbdHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code==HC_ACTION) {
		g_dwLastInputTick = GetTickCount();
	}
	return ::CallNextHookEx(g_hHookKbd, code, wParam, lParam);
}

/////////////////
// Mouse hook: record tick count
//
LRESULT CALLBACK MyMouseHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code==HC_ACTION) {
		g_dwLastInputTick = GetTickCount();
	}
	return ::CallNextHookEx(g_hHookMouse, code, wParam, lParam);
}

//////////////////
// Initialize DLL: install kbd/mouse hooks.
//
EVENT_API BOOL IdleUIInit(void)
{
	if (g_hHookKbd == NULL && hModule!=NULL)
	{
		g_hHookKbd   = SetWindowsHookEx(WH_KEYBOARD, MyKbdHook,   (HINSTANCE)hModule, 0);
		g_hHookMouse = SetWindowsHookEx(WH_MOUSE,		MyMouseHook, (HINSTANCE)hModule, 0);
		g_dwLastInputTick = GetTickCount();
	}
	return TRUE;
}

//////////////////
// Terminate DLL: remove hooks.
//
void IdleUITerm(void)
{
	BOOL bRet1;
	if(g_hHookKbd)
	bRet1 = UnhookWindowsHookEx(g_hHookKbd);
	BOOL bRet2;
	if(g_hHookMouse)
		bRet2 = UnhookWindowsHookEx(g_hHookMouse);
	g_dwLastInputTick=0xFFFFFFFF;
}
