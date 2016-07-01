#ifndef WTLENH_H
#define WTLENH_H

/*--------------------------------------------------------------------------
	This are reflection macros which allows reflection for a certain control
	Normally (with ATL macros) you can turn on or off reflection only for
	all controls. So all controls must have a default reflection handler,
	but standard controls haven't.

	The following code is taken from the file ATLWIN.H
	CWindowImplRoot< TBase >::ReflectNotifications
	If the ATL team had splitted the function into 2 parts, the
	concept could be easily extended. So we have to do code duplication.
*/

class CReflection
{
protected:
	HWND GetHandleFromMsg(HWND hWndParent, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// The following code is taken from the file ATLWIN.H
		// CWindowImplRoot< TBase >::ReflectNotifications
		HWND hWndChild = NULL;

		switch(uMsg)
		{
		case WM_COMMAND:
			if(lParam != NULL)	// not from a menu
				hWndChild = (HWND)lParam;
			break;
		case WM_NOTIFY:
			hWndChild = ((LPNMHDR)lParam)->hwndFrom;
			break;
		case WM_PARENTNOTIFY:
			switch(LOWORD(wParam))
			{
			case WM_CREATE:
			case WM_DESTROY:
				hWndChild = (HWND)lParam;
				break;
			default:
				hWndChild = ::GetDlgItem(hWndParent, HIWORD(wParam));
				break;
			}
			break;
		case WM_DRAWITEM:
			if(wParam)	// not from a menu
				hWndChild = ((LPDRAWITEMSTRUCT)lParam)->hwndItem;
			break;
		case WM_MEASUREITEM:
			if(wParam)	// not from a menu
				hWndChild = ::GetDlgItem(hWndParent, ((LPMEASUREITEMSTRUCT)lParam)->CtlID);
			break;
		case WM_COMPAREITEM:
			if(wParam)	// not from a menu
				hWndChild = ::GetDlgItem(hWndParent, ((LPCOMPAREITEMSTRUCT)lParam)->CtlID);
			break;
		case WM_DELETEITEM:
			if(wParam)	// not from a menu
				hWndChild = ::GetDlgItem(hWndParent, ((LPDELETEITEMSTRUCT)lParam)->CtlID);
			break;
		case WM_VKEYTOITEM:
		case WM_CHARTOITEM:
		case WM_HSCROLL:
		case WM_VSCROLL:
			hWndChild = (HWND)lParam;
			break;
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			hWndChild = (HWND)lParam;
			break;
		default:
			break;
		}

		return hWndChild;
	}

	LRESULT ReflectForCtrl(
		HWND hWndParent, HWND hWnd, UINT uMsgToReflect,
		UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// reflect everything or only the given message
		if ((uMsgToReflect == -1) || (uMsgToReflect == uMsg)) {

			// determine child handle
			HWND hWndChild = GetHandleFromMsg(hWndParent, uMsg, wParam, lParam);
			if(hWndChild == NULL)
			{
				bHandled = FALSE;
				return 1;
			}

			// reflect message for the given control
			ATLASSERT(::IsWindow(hWndChild));
			if (hWnd == hWndChild) {
				bHandled = TRUE;
				return ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
			}
		}

		// otherwise keep unhandled
		bHandled = FALSE;
		return 1;
	}
};

// Message reflection macros
#define REFLECT_NOTIFICATIONS_FOR_CTRL(theHandle)							\
	{																		\
		bHandled = TRUE;													\
		lResult = ReflectForCtrl(m_hWnd, theHandle, -1,						\
			 uMsg, wParam, lParam, bHandled);								\
		if(bHandled)														\
			return TRUE;													\
	}

#define REFLECT_NOTIFICATION_FOR_CTRL(theHandle, theNotification)			\
	{																		\
		bHandled = TRUE;													\
		lResult = ReflectForCtrl(m_hWnd, theHandle, theNotification,		\
			 uMsg, wParam, lParam, bHandled);								\
		if(bHandled)														\
			return TRUE;													\
	}

#endif