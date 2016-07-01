/********************************************************************
*
* Copyright (C) 2001 Sven Wiegand
* 
* This file is free software; you can redistribute it and/or
* modify, but leave the headers intact and do not remove any 
* copyrights from the source.
*
* If you have further questions, suggestions or bug fixes, please
* let me know
*
*    sven.wiegand@web.de
*
********************************************************************/

#include "stdafx.h"
#include "InterfaceWrapper.h"

//-------------------------------------------------------------------
// class CInterfaceImplementationWrapper
//-------------------------------------------------------------------

CInterfaceImplementationWrapper::CInterfaceImplementationWrapper()
:	m_ulRef(0)
{}


CInterfaceImplementationWrapper::~CInterfaceImplementationWrapper()
{}


ULONG CInterfaceImplementationWrapper::AddRef()
{
	return InterlockedIncrement((long*)&m_ulRef);
}


ULONG CInterfaceImplementationWrapper::Release()
{
	ULONG	ulRef = InterlockedDecrement((long*)&m_ulRef);
	if (ulRef == 0)
		delete this;

	return ulRef;
}


HRESULT CInterfaceImplementationWrapper::QueryInterface(REFIID riid, void **ppv)
{
	if (*ppv == NULL)
		return E_FAIL;

	if (riid == IID_IUnknown)
		*ppv = dynamic_cast<IUnknown*>(this);
	else
		*ppv = NULL;

	if (*ppv == NULL)
		return E_NOINTERFACE;

	AddRef();
	return S_OK;
}


void CInterfaceImplementationWrapper::MethodPrologue()
{
}


//-------------------------------------------------------------------
// class CDispatchInterfaceImplementationWrapper
//-------------------------------------------------------------------

CDispatchInterfaceImplementationWrapper::CDispatchInterfaceImplementationWrapper(REFGUID rguidTypeLibrary, USHORT usVerMajor, USHORT usVerMinor, REFGUID rguidInterface)
:	CInterfaceImplementationWrapper()
{
	ITypeLib	*ptl = 0;
	HRESULT hr = LoadRegTypeLib(rguidTypeLibrary, usVerMajor, usVerMinor, 0, &ptl);
	ATLASSERT(SUCCEEDED(hr));
	if (!SUCCEEDED(hr))
		AfxThrowComException(hr);

	hr = ptl->GetTypeInfoOfGuid(rguidInterface, &m_pTypeInfo);
	ptl->Release();
	ATLASSERT(SUCCEEDED(hr));
	if (!SUCCEEDED(hr))
		AfxThrowComException(hr);
}


CDispatchInterfaceImplementationWrapper::~CDispatchInterfaceImplementationWrapper()
{
	m_pTypeInfo->Release();
}


HRESULT CDispatchInterfaceImplementationWrapper::GetTypeInfoCount(UINT *pctinfo)
{
	ATLASSERT(pctinfo);
	*pctinfo = 1;
	return S_OK;
}


HRESULT CDispatchInterfaceImplementationWrapper::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	ATLASSERT(iTInfo == 0 && ppTInfo != 0);
	(*ppTInfo = m_pTypeInfo)->AddRef();
	return S_OK;
}


HRESULT CDispatchInterfaceImplementationWrapper::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgid)
{
	ATLASSERT(riid == IID_NULL);
	return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgid);
}


HRESULT CDispatchInterfaceImplementationWrapper::Invoke(DISPID id, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	ATLASSERT(riid == IID_NULL);
	return m_pTypeInfo->Invoke((PVOID)GetInterface(), id, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}


//-------------------------------------------------------------------
// class CComException
//-------------------------------------------------------------------

CComException::CComException(HRESULT hr)
:	CException(TRUE),
	m_hr(hr)
{}


void CComException::Throw(HRESULT hr)
{
	CComException	*pE = new CComException(hr);
	if (!pE)
		return;

	throw pE;
}


//-------------------------------------------------------------------
// globals
//-------------------------------------------------------------------
#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

CException::CException()
{
	// most exceptions are deleted when not needed
	m_bAutoDelete = TRUE;
}

CException::CException(BOOL bAutoDelete)
{
	// for exceptions which are not auto-delete (usually)
	m_bAutoDelete = bAutoDelete;
}

void CException::Delete()
{
	// delete exception if it is auto-deleting
	if (m_bAutoDelete > 0)
	{
		delete this;
	}
}

BOOL CException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
								 PUINT pnHelpContext /* = NULL */ )
{
	if (pnHelpContext != NULL)
		*pnHelpContext = 0;

	if (nMaxError != 0 && lpszError != NULL)
		*lpszError = '\0';

	return FALSE;
}

int CException::ReportError(UINT nType /* = MB_OK */,
							UINT nError /* = 0 */)
{
	TCHAR   szErrorMessage[512];
	int     nDisposition;
	UINT    nHelpContext;

	if (GetErrorMessage(szErrorMessage, _countof(szErrorMessage), &nHelpContext))
		nDisposition = ::MessageBox(NULL,szErrorMessage,_T("WTLBuilder"), nType);
	else
	{
		nDisposition = ::MessageBox(NULL,_T("Unknown Error"),_T("WTLBuilder"), nType);
	}
	return nDisposition;
}



void AfxThrowComException(HRESULT hr)
{
	CComException::Throw(hr);
}