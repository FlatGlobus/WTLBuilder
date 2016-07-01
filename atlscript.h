#if !defined(AFX_ATLSCRIPT_H__20000806_99C6_7916_E2C2_0080AD509054__INCLUDED_)
#define AFX_ATLSCRIPT_H__20000806_99C6_7916_E2C2_0080AD509054__INCLUDED_

#pragma once

/////////////////////////////////////////////////////////////////////////////
// atlscript.h
// Some default Active Scripting interface implementations.
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2000 Bjarke Viksoe.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#ifndef __cplusplus
   #error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLBASE_H__
   #error atlscript.h requires atlbase.h to be included first
#endif


// Stuff from Active Scripting SDK.
// Is at least to be found on the latest PlatformSDK.
// If you can get hold of a copy of the activdbg.h then 
// see notes below...
#include <activscp.h>


/////////////////////////////////////////////////////////////////////////////
// IActiveScriptSite

template< class T >
class ATL_NO_VTABLE IActiveScriptSiteImpl : public IActiveScriptSite
{
public:
   CComPtr<IActiveScript> m_spIActiveScript;
   bool m_bNoFailures;

   STDMETHOD(GetLCID)(LCID* /*plcid*/) 
   { 
      return E_NOTIMPL; 
   }

   STDMETHOD(GetItemInfo)( 
               LPCOLESTR /*pstrName*/,
               DWORD /*dwReturnMask*/,
               IUnknown** /*ppiunkItem*/,
               ITypeInfo** /*ppti*/)
   {
      return E_FAIL;
   }

   STDMETHOD(GetDocVersionString)(BSTR* pbstrVersion)
   {
      if( pbstrVersion==NULL ) return E_POINTER;
      *pbstrVersion = ::SysAllocString(OLESTR("Script 1.0"));
      return S_OK;
   }

   STDMETHOD(OnScriptTerminate)( 
               const VARIANT* /*pvarResult*/,
               const EXCEPINFO* /*pexcepinfo*/)
   {
      return S_OK;
   }
     
   STDMETHOD(OnStateChange)(SCRIPTSTATE /*ssScriptState*/)
   {
      return S_OK;
   }
     
   STDMETHOD(OnScriptError)(IActiveScriptError* pScriptError)
   {
      ATLASSERT(pScriptError);
      EXCEPINFO e;
      DWORD dwContext;
      ULONG ulLine;
      LONG lPos;
      pScriptError->GetExceptionInfo(&e);
      pScriptError->GetSourcePosition(&dwContext, &ulLine, &lPos);
      LPCTSTR pstrFormat = _T("An error occured while parsing script:\n\nSource: %ws\nError: %08X\nDescription: %ws\nLine: %d");
      LPTSTR pstrStr = new TCHAR[1024];
      ::wsprintf( pstrStr, pstrFormat,
         e.bstrSource,
         e.scode,
         e.bstrDescription,
         ulLine+1);
      ::MessageBox(::GetActiveWindow(), pstrStr, _T("Compile Error"), MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
      delete [] pstrStr;
      //
      if( m_spIActiveScript ) m_spIActiveScript->SetScriptState(SCRIPTSTATE_DISCONNECTED);
      m_bNoFailures = false;
      return S_OK;
   }

   STDMETHOD(OnEnterScript)()
   {
      m_bNoFailures = true;
      return S_OK;
   }

   STDMETHOD(OnLeaveScript)()
   {
      return S_OK;
   }
};


/////////////////////////////////////////////////////////////////////////////
// IActiveScriptSiteWindow

template< class T >
class ATL_NO_VTABLE IActiveScriptSiteWindowImpl : public IActiveScriptSiteWindow
{
public:
   STDMETHOD(GetWindow)(HWND* phWnd)
   {
      if( phWnd==NULL ) return E_POINTER;
      T* pT = static_cast<T*>(this);
      ATLASSERT(::IsWindow(pT->m_hWnd));
      *phWnd = pT->m_hWnd;
      return S_OK;
   }

   STDMETHOD(EnableModeless)(BOOL /*fEnable*/)
   {
      return S_OK;
   }
};


/////////////////////////////////////////////////////////////////////////////
// IActiveScriptSiteDebug

#if defined(__activdbg_h__) || defined(__ACTIVDBG_H__)

// NOTE: Derive from this when you do not want the
//       script debugger to activate automatically.
//       Add the SCRIPTTEXT_HOSTMANAGESSOURCE flag to the
//       ParseScriptText() method.
// NOTE: This doesn't seem to be an officially MS supported
//       interface. See Microsoft Q216073 and Q216271 for download 
//       of activdbg.h!
template< class T >
class ATL_NO_VTABLE IActiveScriptSiteDebugImpl : public IActiveScriptSiteDebug
{
public:
   STDMETHOD(GetDocumentContextFromPosition)( 
            DWORD /*dwSourceContext*/,
            ULONG /*uCharacterOffset*/,
            ULONG /*uNumChars*/,
            IDebugDocumentContext** /* ppsc */)
   {
      return E_NOTIMPL;
   }

   STDMETHOD(GetApplication)(IDebugApplication** /*ppda*/)
   {
      return E_NOTIMPL;
   }

   STDMETHOD(GetRootApplicationNode)(IDebugApplicationNode** /*ppdanRoot*/)
   {
      return E_NOTIMPL;
   }

   STDMETHOD(OnScriptErrorDebug)( 
            IActiveScriptErrorDebug* /*pErrorDebug*/,
            BOOL* /*pfEnterDebugger*/,
            BOOL* /*pfCallOnScriptErrorWhenContinuing*/)
   {
      return E_NOTIMPL;
   }
};

#endif // __activdbg_h__


#endif // !defined(AFX_ATLSCRIPT_H__20000806_99C6_7916_E2C2_0080AD509054__INCLUDED_)
