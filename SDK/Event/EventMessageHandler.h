// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __EVENT_MESSAGE_HANDLER_H
#define __EVENT_MESSAGE_HANDLER_H
//////////////////////////////////////////////////////////////////////////
#define MESSAGE_HANDLER_EV(msg, command) \
	if(uMsg == msg) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define MESSAGE_RANGE_HANDLER_EV(msgFirst, msgLast,command) \
	if(uMsg >= msgFirst && uMsg <= msgLast) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_HANDLER_EV(id, code, command) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_ID_HANDLER_EV(id, command) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_CODE_HANDLER_EV(code, command) \
	if(uMsg == WM_COMMAND && code == HIWORD(wParam)) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define COMMAND_RANGE_HANDLER_EV(idFirst, idLast, command) \
	if(uMsg == WM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_HANDLER_EV(id, cd, command) \
	if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_ID_HANDLER_EV(id, command) \
	if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_CODE_HANDLER_EV(cd, command) \
	if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}

#define NOTIFY_RANGE_HANDLER_EV(idFirst, idLast, command) \
	if(uMsg == WM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
	{ \
		bHandled = TRUE; \
		lResult = 0; \
		SendEvent(T command)\
		if(bHandled) \
			return TRUE; \
	}
//////////////////////////////////////////////////////////////////////////
#endif