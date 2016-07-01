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

#ifndef __INTERFACEWRAPPER_H__
#define __INTERFACEWRAPPER_H__

#include <atlbase.h>
#include <comdef.h>

/**
Thrown if a call to a COM-interface returned a non successfull
HRESULT value. The m_hr member contains the return value that
caused the error.

To throw such an exception you should always use the static
Throw() method or the global AfxThrowComException() function.
Both are creating an instance on the heap and throwing the pointer.

To destruct a catched pointer to a CComException object, call the
Delete() method.

@author Sven Wiegand
*/

class CException
{
public:
	// Constructors
	CException();   // sets m_bAutoDelete = TRUE
	explicit CException(BOOL bAutoDelete);   // sets m_bAutoDelete = bAutoDelete

	// Operations
	void Delete();  // use to delete exception in 'catch' block

	virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
		PUINT pnHelpContext = NULL);
	virtual int ReportError(UINT nType = MB_OK, UINT nMessageID = 0);

	// Implementation (setting m_bAutoDelete to FALSE is advanced)
public:
	virtual ~CException() = 0;
	BOOL m_bAutoDelete;
};

inline CException::~CException()
{ }

class  CComException : public CException
{
// construction/destruction
public:
	CComException(HRESULT hr);

// static helpers
public:
	/**
	Constructs a CComException object on the heap and throws the 
	pointer.

	The m_hr attribute of the constructed object will be set to the
	given value.
	*/
	static void Throw(HRESULT hr);

// attributes
public:
	/** Value returned by the COM call causing the exception. */
	HRESULT m_hr;
};


/** Calls CComException::Throw() */
void  AfxThrowComException(HRESULT hr);


/**
Base class for all the classes used to implement an interface.

Supports basic IUnknown features like internal reference counting.

@author Sven Wiegand
*/
class  CInterfaceImplementationWrapper
{
// construction/destruction
public:
	CInterfaceImplementationWrapper();
	virtual ~CInterfaceImplementationWrapper();

// overridables
public:
	virtual IUnknown* GetInterface() = 0;
	virtual ULONG AddRef();
	virtual ULONG Release();
	virtual HRESULT QueryInterface(REFIID riid, void **ppv);

protected:
	virtual void MethodPrologue();

// attributes
private:
	ULONG m_ulRef;
};


/**
Base class for all the classes used to implement an interface derived
from IDispatch.

Supports basic IDispatch features.

Only works for dual interfaces.

@author Sven Wiegand
*/
class  CDispatchInterfaceImplementationWrapper : public CInterfaceImplementationWrapper
{
// construction/destruction
public:
	CDispatchInterfaceImplementationWrapper(REFGUID rguidTypeLibrary, USHORT usVerMajor, USHORT usVerMinor, REFGUID rguidInterface);
	virtual ~CDispatchInterfaceImplementationWrapper();

// overridables
public:
	virtual HRESULT GetTypeInfoCount(UINT *pctinfo);
	virtual HRESULT GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
	virtual HRESULT GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgid);
	virtual HRESULT Invoke(DISPID id, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);

// attributes
private:
	ITypeInfo *m_pTypeInfo;
};


/**
Base class for all classes that are wrapping a com interface.

@author Sven Wiegand
*/
template<class T>
class  CInterfaceCallingWrapper
{
// construction/destruction
public:
	CInterfaceCallingWrapper();

	/**
	Attaches the given interface to this object.

	@param bIncrementRefCount
		Specify TRUE, if the reference count of the given interface
		should be incremented and FALSE otherwise.
	*/
	CInterfaceCallingWrapper(T *p, BOOL bIncrementRefCount = FALSE);

	/**
	Attaches the interface of the given wrapper to this object and
	increments the reference count of the interface.
	*/
	CInterfaceCallingWrapper(const CInterfaceCallingWrapper<T> &iw);

	/**
	Decrements the interfaces reference count.
	*/
	virtual ~CInterfaceCallingWrapper();

// operators
public:
	/** Returns the wrapped interface pointer */
	operator T*();

	/** Returns the dereferenced value of the interface pointer */
	T& operator*();

	/** Returns the address of the interface pointer */
	T** operator&();

	/** Use to access the interface pointer */
	T* operator->();

	/** Same as Attach(p, TRUE);	*/
	T* operator=(T *p);

	/** true if the wrapped interface pointer is NULL false otherwise */
	bool operator!();

// operations
public:
	/** 
	Attaches the specified pointer.

	Will fail if there is already an interface attached to this 
	wrapper. Call Detach() first.

	@param bIncrementRefCount
		Specify TRUE, if the reference count of the given interface
		should be incremented and FALSE otherwise.

	@return
		TRUE if the interface has been attached to the wrapper, FALSE
		if there is already an interface attached.
	*/
	BOOL Attach(T *p, BOOL bIncrementRefCount = FALSE);

	/**
	Returns the member pointer and detaches it from this object by 
	setting it to NULL.

	@param bIncrementRefCount
		Specify TRUE, if the reference count of the given interface
		should be decremented and FALSE otherwise.
	*/
	T* Detach(BOOL bDecrementRefCount = FALSE);

	/**
	Copies the internal pointer to a target pointer. The pointer's 
	reference count is incremented if successful. Returns NULL if the
	wrapped interface pointer is NULL.
	*/
	T* CopyTo();

	/**
	Creates an instance of an object in a type-safe manner.
	*/
	HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

	/**
	Creates an instance of an object in a type-safe manner.
	*/
	HRESULT CoCreateInstance(LPCTSTR lpszProgId, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

	/**
	Calls QueryInterface() on the internal pointer in a type-safe 
	manner.
	*/
	template<class Q> HRESULT QueryInterface(Q **p)
	{
		return m_p.QueryInterface(p);
	}

	/**
	Calls QueryInterface() on the internal pointer in a type-safe 
	manner.

	@param bThrowException
		If TRUE the method will throw a CComException if the call to 
		QueryInterface() fails, otherwise only a NULL pointer will
		be returned if the call fails.
	*/
	template<class Q> Q* QueryInterface(BOOL bThrowException = TRUE)
	{
		Q	*p = NULL;
		HRESULT	hr = m_p.QueryInterface(&p);
		if (hr != S_OK && bThrowException)
			AfxThrowComException(hr);

		return p;
	}

	/**
	Returns the wrapped interface pointer.
	*/
	T* P();

	/**
	Returns the wrapped interface pointer as const.
	*/
	T* GetP() const;

// attributes
private:
	CComPtr<T> m_p;
};


//-------------------------------------------------------------------
// class CInterfaceCallingWrapper
//-------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////
// construction/destruction

template<class T>
CInterfaceCallingWrapper<T>::CInterfaceCallingWrapper()
{}


template<class T>
CInterfaceCallingWrapper<T>::CInterfaceCallingWrapper(T *p, BOOL bIncrementRefCount /*= FALSE*/)
{
	Attach(p, bIncrementRefCount);
}


template<class T>
CInterfaceCallingWrapper<T>::CInterfaceCallingWrapper(const CInterfaceCallingWrapper<T> &iw)
:	m_p(iw.GetP())
{}


template<class T>
CInterfaceCallingWrapper<T>::~CInterfaceCallingWrapper()
{}

/////////////////////////////////////////////////////////////////////
// operators

template<class T>
CInterfaceCallingWrapper<T>::operator T*()
{
	return m_p;
}


template<class T>
T& CInterfaceCallingWrapper<T>::operator*()
{
	return *m_p;
}


template<class T>
T** CInterfaceCallingWrapper<T>::operator&()
{
	return &m_p;
}


template<class T>
T* CInterfaceCallingWrapper<T>::operator->()
{
	return m_p.p;
}


template<class T>
T* CInterfaceCallingWrapper<T>::operator=(T *p)
{
	Attach(p, TRUE);
	return m_p;
}


template<class T>
bool CInterfaceCallingWrapper<T>::operator!()
{
	return !m_p;
}


/////////////////////////////////////////////////////////////////////
// operations

template<class T>
BOOL CInterfaceCallingWrapper<T>::Attach(T *p, BOOL bIncrementRefCount /*= FALSE*/)
{
	// There is already an interface attached.
	// Call Detach() first.
	ATLASSERT(!m_p);
	if (m_p)
		return FALSE;

	m_p.Attach(p);
	if (bIncrementRefCount)
		m_p.p->AddRef();

	return TRUE;
}


template<class T>
T* CInterfaceCallingWrapper<T>::Detach(BOOL bDecrementRefCount /*= FALSE*/)
{
	if (bDecrementRefCount)
		m_p.p->Release();

	return m_p.Detach();
}


template<class T>
T* CInterfaceCallingWrapper<T>::CopyTo()
{
	T	*p;
	if (m_p.CopyTo(&p) == S_OK)
		return p;
	else
		return NULL;
}


template<class T>
HRESULT CInterfaceCallingWrapper<T>::CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	return m_p.CoCreateInstance(rclsid, pUnkOuter, dwClsContext);
}


template<class T>
HRESULT CInterfaceCallingWrapper<T>::CoCreateInstance(LPCTSTR lpszProgId, LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	BSTR		bstrProgId = CString(lpszProgId).AllocSysString();
	HRESULT	hr = m_p.CoCreateInstance(bstrProgId, pUnkOuter, dwClsContext);
	SysFreeString(bstrProgId);
	return hr;
}


template<class T>
T* CInterfaceCallingWrapper<T>::P()
{
	return m_p;
}


template<class T>
T* CInterfaceCallingWrapper<T>::GetP() const
{
	return m_p;
}

#endif //__INTERFACEWRAPPERS_H__