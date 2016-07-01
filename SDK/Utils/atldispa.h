#if !defined(AFX_ATLDISPA_H__20010608_7B20_BD08_5EED_0080AD509054__INCLUDED_)
#define AFX_ATLDISPA_H__20010608_7B20_BD08_5EED_0080AD509054__INCLUDED_

#pragma once

/////////////////////////////////////////////////////////////////////////////
// atldispa - Dynamic IDispatch handler
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2001-2005 Bjarke Viksoe.
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
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

#ifndef __ATLCOM_H__
  #error atldispa.h requires atlcom.h to be included first
#endif


/////////////////////////////////////////////////////////////////////////////
// Dynamic IDispatch macros

// Parameter types: by value VTs
#define VTS_EMPTY           L"\x00"
#define VTS_I2              L"\x02"      // a 'short'
#define VTS_I4              L"\x03"      // a 'long'
#define VTS_R4              L"\x04"      // a 'float'
#define VTS_R8              L"\x05"      // a 'double'
#define VTS_CY              L"\x06"      // a 'CY'
#define VTS_DATE            L"\x07"      // a 'DATE'
#define VTS_BSTR            L"\x08"      // a 'BSTR'
#define VTS_DISPATCH        L"\x09"      // an 'IDispatch*'
#define VTS_SCODE           L"\x0A"      // a 'SCODE'
#define VTS_BOOL            L"\x0B"      // a 'BOOL'
#define VTS_VARIANT         L"\x0C"      // a 'VARIANT'
#define VTS_UNKNOWN         L"\x0D"      // an 'IUnknown*'

// Parameter types: by reference VTs
#define VTS_REF_I2          L"\x4002"    // a 'short*'
#define VTS_REF_I4          L"\x4003"    // a 'long*'
#define VTS_REF_R4          L"\x4004"    // a 'float*'
#define VTS_REF_R8          L"\x4005"    // a 'double*'
#define VTS_REF_CY          L"\x4006"    // a 'CY*'
#define VTS_REF_DATE        L"\x4007"    // a 'DATE*'
#define VTS_REF_BSTR        L"\x4008"    // a 'BSTR*'
#define VTS_REF_DISPATCH    L"\x4009"    // an 'IDispatch**'
#define VTS_REF_SCODE       L"\x400A"    // a 'SCODE*'
#define VTS_REF_BOOL        L"\x400B"    // a 'VARIANT_BOOL*'
#define VTS_REF_VARIANT     L"\x400C"    // a 'VARIANT*'
#define VTS_REF_UNKNOWN     L"\x400D"    // an 'IUnknown**'


template< class T >
struct _ATL_DISPATCH_ENTRY
{
  OLECHAR *szName;
  DISPID dispid;
  UINT wFlags;
  VARTYPE vtReturn;
  UINT nArgs;
  LPCWSTR vtArgs;
  VARTYPE vtSingle;
  void (__stdcall T::*pfn)();
};

#define BEGIN_DISPATCH_MAP(theClass) \
   static const _ATL_DISPATCH_ENTRY<theClass>* _GetDispMap()\
   {\
      typedef theClass _atl_disp_classtype;\
      static const _ATL_DISPATCH_ENTRY<_atl_disp_classtype> _dispmap[] = {

#define DISP_METHOD_ID(func, dispid, vtRet, nCnt, vtArgs) \
   { OLESTR(#func), dispid, DISPATCH_METHOD, vtRet, nCnt, { vtArgs }, VT_EMPTY, (void (__stdcall _atl_disp_classtype::*)())&func },

#define DISP_METHOD(func, vtRet, nCnt, vtArgs) \
   DISP_METHOD_ID(func, DISPID_UNKNOWN, vtRet, nCnt, vtArgs)

#define DISP_METHOD0_ID(func, dispid, vtRet) \
   { OLESTR(#func), dispid, DISPATCH_METHOD, vtRet, 0, { VTS_EMPTY }, VT_EMPTY, (void (__stdcall _atl_disp_classtype::*)())&func },

#define DISP_METHOD0(func, vtRet) \
   DISP_METHOD0_ID(func, DISPID_UNKNOWN, vtRet)

#define DISP_METHOD1_ID(func, dispid, vtRet, vtArg) \
   { OLESTR(#func), dispid, DISPATCH_METHOD, vtRet, 1, NULL, vtArg, (void (__stdcall _atl_disp_classtype::*)())&func },

#define DISP_METHOD1(func, vtRet, vtArg) \
   DISP_METHOD1_ID(func, DISPID_UNKNOWN, vtRet, vtArg)

#define DISP_PROP_ID(member, dispid, vt) \
   { OLESTR(#member), dispid, DISPATCH_PROPERTYGET, vt, 0, { VTS_EMPTY }, VT_EMPTY, (void (__stdcall _atl_disp_classtype::*)())&get_##member }, \
   { OLESTR(#member), DISPID_PROPERTYPUT, DISPATCH_PROPERTYPUT, VT_EMPTY, 1, NULL, vt, (void (__stdcall _atl_disp_classtype::*)())&put_##member },

#define DISP_PROP(member, vt) \
   DISP_PROP_ID(member, DISPID_UNKNOWN, vt)

#define DISP_PROPGET_ID(member, dispid, vt) \
   { OLESTR(#member), dispid, DISPATCH_PROPERTYGET, vt, 0, { VTS_EMPTY }, VT_EMPTY, (void (__stdcall _atl_disp_classtype::*)())&get_##member },

#define DISP_PROPGET(member, vt) \
   DISP_PROPGET_ID(member, DISPID_UNKNOWN, vt)

#define DISP_PROPPUT_ID(member, dispid, vt) \
   { OLESTR(#member), dispid, DISPATCH_PROPERTYPUT, VT_EMPTY, 1, NULL, vt, (void (__stdcall _atl_disp_classtype::*)())&put_##member },

#define DISP_PROPPUT(member, vt) \
   DISP_PROPPUT_ID(member, DISPID_UNKNOWN, vt)

#define END_DISPATCH_MAP() {0}}; return _dispmap;}


/////////////////////////////////////////////////////////////////////////////
// IDispDynImpl

template< class T, const IID* pdiid = &IID_NULL >
class ATL_NO_VTABLE IDispDynImpl : public IDispatch
{
public:
   IDispDynImpl()
   {
   }

   // These are here only to support use in non-COM objects   
   STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppvObject)
   {
      // NOTE: If compile errors occour at this location, 
      //       add/remove the "ATL::" namespace qualifiers in front 
      //       of the InlineIsEqualGUID() methods below.
      //       This is due to a problem in old MS Platform SDK releases.
      if( InlineIsEqualGUID(riid, *pdiid) || 
          InlineIsEqualUnknown(riid) ||
          InlineIsEqualGUID(riid, IID_IDispatch) )
      {
         if( ppvObject==NULL ) return E_POINTER;
         *ppvObject = this;
         AddRef();
#ifdef _ATL_DEBUG_INTERFACES
         _Module.AddThunk((IUnknown**)ppvObject, _T("IDispDynImpl"), riid);
#endif // _ATL_DEBUG_INTERFACES
         return S_OK;
      }
      else {
         return E_NOINTERFACE;
      }
   }
   virtual ULONG STDMETHODCALLTYPE AddRef()
   {
      return 1;
   }
   virtual ULONG STDMETHODCALLTYPE Release()
   {
      return 1;
   }

   STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
   {
      *pctinfo = 0; 
      return S_OK;
   }

   STDMETHOD(GetTypeInfo)(UINT /*itinfo*/, LCID /*lcid*/, ITypeInfo** /*pptinfo*/)
   {
      return E_NOTIMPL;
   }

   STDMETHOD(GetIDsOfNames)(REFIID /*riid*/, LPOLESTR* rgszNames, UINT cNames, LCID /*lcid*/, DISPID* rgdispid)
   {
      HRESULT Hr = S_OK;
      for( UINT i=0; i<cNames; i++ ) {
         const _ATL_DISPATCH_ENTRY<T>* pMap = T::_GetDispMap();
         DISPID dispid = 1;
         while( pMap->pfn!=NULL ) {
            if( ::lstrcmpiW(pMap->szName, rgszNames[i])==0 ) {
               rgdispid[i] = pMap->dispid==DISPID_UNKNOWN ? dispid : pMap->dispid;
               break;
            }
            dispid++;
            pMap++;
         }
         if( pMap->pfn==NULL ) {
            rgdispid[i] = DISPID_UNKNOWN;
            Hr = DISP_E_UNKNOWNNAME; 
         }
      }
      return Hr;
   }

   STDMETHOD(Invoke)(DISPID dispidMember, REFIID /*riid*/,
      LCID /*lcid*/, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
      EXCEPINFO* /*pexcepinfo*/, UINT* /*puArgErr*/)
   {
      if( (DISPATCH_PROPERTYPUT!=wFlags) && (pdispparams->cNamedArgs>0) ) return DISP_E_NONAMEDARGS;
      const _ATL_DISPATCH_ENTRY<T>* pMap = T::_GetDispMap();
      DISPID i = 1;
      while( pMap->pfn!=NULL ) {
         DISPID dispid = pMap->dispid==DISPID_UNKNOWN ? i : pMap->dispid;
         if( dispidMember==dispid ) {
            if( (DISPATCH_PROPERTYPUT==wFlags) && (DISPID_PROPERTYPUT==(pMap+1)->dispid) ) 
               pMap++;
            VARTYPE* pArgs = (VARTYPE*) pMap->vtArgs;
            if( pArgs == NULL ) pArgs = (VARTYPE*) &pMap->vtSingle;
            UINT nArgs = pMap->nArgs;
            if( pdispparams->cArgs != nArgs ) return DISP_E_BADPARAMCOUNT;
            VARIANTARG** ppVarArgs = nArgs ? (VARIANTARG**)_alloca(sizeof(VARIANTARG*)*nArgs) : NULL;
            VARIANTARG* pVarArgs = nArgs ? (VARIANTARG*)_alloca(sizeof(VARIANTARG)*nArgs) : NULL;
            UINT i;
            for( i=0; i<nArgs; i++ ) {
               ppVarArgs[i] = &pVarArgs[i];
               ::VariantInit(&pVarArgs[i]);
               if( FAILED(::VariantCopyInd(&pVarArgs[i], &pdispparams->rgvarg[nArgs-i-1])) ) return DISP_E_TYPEMISMATCH;
               if( FAILED(::VariantChangeType(&pVarArgs[i], &pVarArgs[i], 0, pArgs[i])) ) return DISP_E_TYPEMISMATCH;
            }
            T *pT = static_cast<T*>(this);
            CComStdCallThunk<T> thunk;
            thunk.Init(pMap->pfn, pT);
            CComVariant tmpResult;
            if( pvarResult==NULL ) pvarResult = &tmpResult;
            HRESULT Hr = ::DispCallFunc(
               &thunk,
               0,
               CC_STDCALL,
               pMap->vtReturn,
               nArgs,
               pArgs,
               nArgs ? ppVarArgs : NULL,
               pvarResult);
            for( i=0; i<nArgs; i++ ) ::VariantClear(&pVarArgs[i]);
            return Hr;
         }
         i++;
         pMap++;
      }
      return DISP_E_MEMBERNOTFOUND;
   }
};


/////////////////////////////////////////////////////////////////////////////
// CComDynTypeInfoHolder

template< class T >
class CComDynTypeInfoHolder
{
// Should be 'protected' but can cause compiler to generate fat code.
public:
   const GUID* m_pguid;
   const GUID* m_plibid;
   WORD m_wMajor;
   WORD m_wMinor;
   ITypeInfo* m_pInfo;
   long m_dwRef;
   struct stringdispid
   {
      CComBSTR bstr;
      int nLen;
      DISPID id;
   };
   stringdispid* m_pCache;
   int m_nArgs;
   // The above members must be present in that order because they
   // are initialized by ATL (as a static member)
   INTERFACEDATA* m_pITF;

public:
   HRESULT GetTI(LCID lcid, ITypeInfo** ppInfo)
   {
      HRESULT Hr = S_OK;
      if( m_pInfo==NULL ) Hr = GetTI(lcid);
      *ppInfo = m_pInfo;
      if( m_pInfo!=NULL ) {
         m_pInfo->AddRef();
         Hr = S_OK;
      }
      return Hr;
   }
   HRESULT GetTI(LCID lcid);
   HRESULT EnsureTI(LCID lcid)
   {
      HRESULT Hr = S_OK;
      if( m_pInfo==NULL ) Hr = GetTI(lcid);
      return Hr;
   }

   // This function is called by the module on exit
   // It is registered through _Module.AddTermFunc()
   static void __stdcall Cleanup(DWORD dw)
   {
      CComDynTypeInfoHolder* p = (CComDynTypeInfoHolder*)dw;
      if( p->m_pInfo != NULL ) {
         p->m_pInfo->Release();
         p->m_pInfo = NULL;
         // Release internal interface block
         for( UINT i=0; i<p->m_pITF->cMembers; i++ ) delete [] p->m_pITF->pmethdata[i].ppdata;
         delete [] p->m_pITF->pmethdata;
         delete p->m_pITF;
      }
      if( p->m_pCache != NULL ) {
         delete [] p->m_pCache;
         p->m_pCache = NULL;
      }
   }

   HRESULT GetTypeInfo(UINT /*itinfo*/, LCID lcid, ITypeInfo** pptinfo)
   {
      HRESULT Hr = E_POINTER;
      if( pptinfo!=NULL ) Hr = GetTI(lcid, pptinfo);
      return Hr;
   }
   HRESULT GetIDsOfNames(REFIID /*riid*/, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid)
   {
      HRESULT Hr = EnsureTI(lcid);
      if( m_pInfo != NULL ) {
         for( int i=0; i<(int)cNames; i++ ) {
            int n = ocslen(rgszNames[i]);
            int j;
            for( j=0; j<m_nArgs; j++ ) {
               if( (n==m_pCache[j].nLen) &&
                   (memcmp(m_pCache[j].bstr, rgszNames[i], m_pCache[j].nLen * sizeof(OLECHAR)) == 0) )
               {
                  rgdispid[i] = m_pCache[j].id;
                  break;
               }
            }
            if( j==m_nArgs) {
               Hr = m_pInfo->GetIDsOfNames(rgszNames, cNames, rgdispid);
               if( FAILED(Hr) ) break;
            }
         }
      }
      return Hr;
   }

   HRESULT Invoke(IDispatch* p, DISPID dispidMember, REFIID /*riid*/,
      LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
      EXCEPINFO* /*pexcepinfo*/, UINT* /*puArgErr*/)
   {
      HRESULT Hr = EnsureTI(lcid);
      if( m_pInfo != NULL ) {
         // As Chris Sells so elegantly put it in his dispimpl2.h sample
         // the ATL library assumes that the methods are always placed on 
         // the IDispatch interface. So instead we implement our own Invoke(),
         // (much in dismay of the documentation of IDispatch::Invoke in Platform SDK).
/*
         Hr = m_pInfo->Invoke(p, dispidMember, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);         
*/
/*
         T *pT = (T*)(p);
         Hr = m_pInfo->Invoke(pT, dispidMember, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);         
*/
         if( (DISPATCH_PROPERTYPUT!=wFlags) && (pdispparams->cNamedArgs>0) ) return DISP_E_NONAMEDARGS;
         const _ATL_DISPATCH_ENTRY<T>* pMap = T::_GetDispMap();
         DISPID i = 1;
         while( pMap->pfn!=NULL ) {
            DISPID dispid = pMap->dispid==DISPID_UNKNOWN ? i : pMap->dispid;
            if( dispidMember==dispid ) {
               if( (DISPATCH_PROPERTYPUT==wFlags) && (DISPID_PROPERTYPUT==(pMap+1)->dispid) ) 
                  pMap++;
               VARTYPE* pArgs = (VARTYPE*) pMap->vtArgs;
               if( pArgs == NULL ) pArgs = (VARTYPE*) &pMap->vtSingle;
               UINT nArgs = pMap->nArgs;
               if( pdispparams->cArgs!=nArgs ) return DISP_E_BADPARAMCOUNT;
               VARIANTARG** ppVarArgs = nArgs ? (VARIANTARG**)_alloca(sizeof(VARIANTARG*)*nArgs) : NULL;
               VARIANTARG* pVarArgs = nArgs ? (VARIANTARG*)_alloca(sizeof(VARIANTARG)*nArgs) : NULL;
               UINT i;
               for( i=0; i<nArgs; i++ ) {
                  ppVarArgs[i] = &pVarArgs[i];
                  ::VariantInit(&pVarArgs[i]);
                  if( FAILED(::VariantCopyInd(&pVarArgs[i], &pdispparams->rgvarg[nArgs-i-1])) ) return DISP_E_TYPEMISMATCH;
                  if( FAILED(::VariantChangeType(&pVarArgs[i], &pVarArgs[i], 0, pArgs[i])) ) return DISP_E_TYPEMISMATCH;
               }
               T *pT = static_cast<T*>(p);
               CComStdCallThunk<T> thunk;
               thunk.Init(pMap->pfn, pT);
               CComVariant tmpResult;
               if( pvarResult==NULL ) pvarResult = &tmpResult;
               HRESULT Hr = ::DispCallFunc(
                  &thunk,
                  0,
                  CC_STDCALL,
                  pMap->vtReturn,
                  nArgs,
                  pArgs,
                  nArgs ? ppVarArgs : NULL,
                  pvarResult);
               for( i=0; i<nArgs; i++ ) ::VariantClear(&pVarArgs[i]);
               return Hr;
            }
            i++;
            pMap++;
         }
         return DISP_E_MEMBERNOTFOUND;
      }
      return Hr;
   }
   HRESULT LoadNameCache(ITypeInfo* /*pTypeInfo*/)
   {
      // A name cache is really not useful here since we already have
      // a fine map of the names. Oh well...
      const _ATL_DISPATCH_ENTRY<T>* pTemp, *pMap = T::_GetDispMap();
      pTemp = pMap;
      m_nArgs = 0;      
      while( pTemp->pfn!=NULL ) {
         m_nArgs++;
         pTemp++;
      }
      m_pCache = m_nArgs==0 ? NULL : new stringdispid[m_nArgs];
      DISPID i = 0;
      while( pMap->pfn!=NULL ) {
         m_pCache[i].bstr = pMap->szName;
         m_pCache[i].nLen = ::SysStringLen(m_pCache[i].bstr);
         m_pCache[i].id = pMap->dispid==DISPID_UNKNOWN ? i+1 : pMap->dispid;
         // NOTE: In case of DISPID_PROPERTYPUT we assume that a name entry 
         // exists before it, which will have the correct DISPID.
         pMap++;
         i++;
      }
      return S_OK;
   }
};

template< class T >
inline HRESULT CComDynTypeInfoHolder<T>::GetTI(LCID lcid)
{   
   const _ATL_DISPATCH_ENTRY<T>* pTemp, *pMap = T::_GetDispMap();
   pTemp = pMap;
   UINT nArgs = 0;
   while( pTemp->pfn!=NULL ) {
      nArgs++;
      pTemp++;
   }
   // Create INTERFACEDATA structures.
   // HACK: They cannot be created on the stack. Seems that the ancient
   //       CreateDispTypeInfo() method uses weak references?!
   m_pITF = new INTERFACEDATA;
   m_pITF->cMembers = nArgs;
   METHODDATA* pM = m_pITF->pmethdata = new METHODDATA[nArgs];
   DISPID dispid = 1;
   DISPID oldid = 0;
   LONG i = 0; // Method index
   while( pMap->pfn!=NULL ) {
      pM->szName = pMap->szName;
      pM->dispid = pMap->dispid==DISPID_UNKNOWN ? dispid : pMap->dispid;
      if( pMap->dispid==DISPID_PROPERTYPUT ) pM->dispid = oldid; // Support hack in our DISP_PROP macro
      pM->iMeth = i;
      pM->cc = CC_STDCALL;
      pM->ppdata = NULL;
      pM->cArgs = pMap->nArgs;
      if( pMap->nArgs>0 ) {
         PARAMDATA* pParams = pM->ppdata = new PARAMDATA[pMap->nArgs];
         for( UINT j=0; j<pMap->nArgs; j++ ) {
            pParams->szName = NULL;
            pParams->vt = pMap->vtArgs != NULL ? pMap->vtArgs[j] : pMap->vtSingle;
            pParams++;
         }
      }
      pM->wFlags = (USHORT) pMap->wFlags;
      pM->vtReturn = pMap->vtReturn;
      // Next entry..
      oldid = pM->dispid;
      dispid++;
      i++;
      pM++;
      pMap++;
   }
   HRESULT Hr = ::CreateDispTypeInfo(m_pITF, lcid, &m_pInfo);
   // The result of CreateDispTypeInfo() is very disappointing. It
   // doesn't create a full ITypeInfo object, so calling ITypeInfo::GetTypeAttr()
   // claims that there are NO methods and properties in the list (?).
   // This basically renders the idea of creating a CComTypeInfoHolder clone
   // useless. I might as well have done a better IDispatch impl instead.
   if( SUCCEEDED(Hr) ) {
      LoadNameCache(m_pInfo);
      _Module.AddTermFunc(Cleanup, (DWORD)this);
   }
   return Hr;
};


#endif // !defined(AFX_ATLDISPA_H__20010608_7B20_BD08_5EED_0080AD509054__INCLUDED_)