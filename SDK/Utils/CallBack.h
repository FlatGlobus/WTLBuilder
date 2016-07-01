// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
#ifndef __CALLBACK__H
#define __CALLBACK__H
//////////////////////////////////////////////////////////////////////////////////////////////////
class CallBack
{
public:
	typedef void (CallBack::*CallBackMethod)(void);
protected:
	CallBack *self;
	CallBackMethod method;
public:

	CallBack(void):self(NULL),method(NULL)
	{
	}

	CallBack(const CallBack & n):self(n.self),method(n.method)
	{
	}
	
	void Reset(void)
	{
        	self=NULL;
	        method=NULL;
	}

	void operator ()(void)
	{
		if(self && method)
			(self->*(method))();
	}

	template <class T1> void operator ()(T1 par)
	{
		typedef void (CallBack::*CallBackMethod1)(T1);
		if(self && method)
			(self->*((CallBackMethod1)method))(par);
	}

	template <class T1,class T2> void operator ()(T1 par1,T2 par2)
	{
		typedef void (CallBack::*CallBackMethod2)(T1,T2);
		if(self && method)
			(self->*((CallBackMethod2)method))(par1,par2);
	}

	template <class T1,class T2,class T3> void operator ()(T1 par1,T2 par2,T3 par3)
	{
		typedef void (CallBack::*CallBackMethod3)(T1,T2,T3);
		if(self && method)
			(self->*((CallBackMethod3)method))(par1,par2,par3);
	}
	
	template<class T> void SetObject(T *s )
	{
		self=(CallBack *)(void*)s;
	}
	
	template<class T> void SetMethod(T s)
	{
		method=(CallBackMethod&)s;
	}

	operator CallBack *(void)
	{
		return self;
	}

	operator CallBackMethod (void)
	{
		return method;
	}
	
	CallBack & operator=(CallBack * s)
	{
		self=s;
		return *this;
	}

	CallBack & operator=(CallBackMethod m)
	{
		method=m;
		return *this;
	}

	CallBack & operator=(CallBack & n)
	{
		self=n.self;
		method=n.method;
		return *this;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_CALLBACK(Name,Var)\
void Set##Name(CallBack & n)\
{\
	Var=n;\
}\
CallBack & Get##Name(void)\
{\
	return Var;\
}\
__declspec(property(get=Get##Name, put=Set##Name)) CallBack & Name;\
protected:\
	CallBack Var;\
public:
//////////////////////////////////////////////////////////////////////////////////////////////////
#endif