// wtl_message_reflection.h: implementation of message reflection
// for WTL wrappers for Windows Controls
// (c) Alexander Fedorov, 2001. lamer2000@hotmail.com
//////////////////////////////////////////////////////////////////////

#ifndef wtl_message_reflection
#define wtl_message_reflection

#ifndef WM_REFLECT_BASE
#define WM_REFLECT_BASE 0xBC00
#endif

// WM_NOTIFY_REFLECTOR
// Should be placed in message map of window which
// should reflect WM_NOTIFY to its child controls

#define WM_NOTIFY_REFLECTOR()\
	if(uMsg == WM_NOTIFY)\
	{\
		UINT code = ((LPNMHDR)lParam)->code;\
		switch(code)\
		{\
		case NM_SETCURSOR:\
			break;\
		default:\
			if ((NULL != lParam) &&\
			(NULL != ((LPNMHDR)lParam)->hwndFrom))\
			{\
				BOOL bHandled = ::SendMessage(((LPNMHDR)lParam)->hwndFrom, WM_NOTIFY + WM_REFLECT_BASE, wParam, lParam);\
				if(bHandled) \
					return TRUE; \
			};\
		};\
	}\


// NOTIFY_REFLECT_CODE_HANDLER
// Should be placed in message map of control which
// wants to handle its own notifications

#define NOTIFY_REFLECT_CODE_HANDLER(cd, func) \
{ \
	if (((WM_NOTIFY + WM_REFLECT_BASE) == uMsg) && \
		(NULL != lParam) && \
		(cd == ((LPNMHDR)lParam)->code)) \
	{\
		bHandled = FALSE;\
		lResult = func((int)wParam, (LPNMHDR)lParam, bHandled);\
		if(bHandled)\
			return TRUE;\
	}\
}

#endif


