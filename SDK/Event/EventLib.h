// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __EVENTLIB__H
#define __EVENTLIB__H
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "Event.h"
#include <map>

#ifndef CAST
#define CAST(new_type,old_object) (*((new_type *)(&(old_object))))
#endif

#define BEGIN_AVAILABLE_ID 40000
#define DEF_TIMER_RESOLUTION 500

class Gag
{
};

typedef void (Gag::*EventMethod)(void);
class DispatcherCommand;
typedef std::map<long, DispatcherCommand *>::iterator mapIterator;
///////////////////////////////////////////////////////////////////////////////////////////////////
EVENT_API void __Add(DWORD command,Gag *,EventMethod,BYTE);
EVENT_API void __Add(DWORD command,Gag *,EventMethod,DWORD interval,BYTE);
EVENT_API void __AddIdle(DWORD command,Gag *,EventMethod,DWORD interval,BYTE);
EVENT_API void __Remove(Gag *);
EVENT_API void __Remove(DWORD,Gag *);
EVENT_API DWORD __GetFirst(DWORD command,Gag *&object,EventMethod & method, mapIterator &cmdsPtr);
EVENT_API DWORD __GetNext(DWORD idx,Gag *&object,EventMethod &method, mapIterator &cmdsPtr);
EVENT_API DWORD GetAvailableCommandID();
EVENT_API BOOL StartCommandTimer(UINT resolution=DEF_TIMER_RESOLUTION);
EVENT_API void StopCommandTimer(void);
EVENT_API void StartAllCommand(void);
EVENT_API void StartCommand(DWORD command);
EVENT_API void StopAllCommand(void);
EVENT_API void StopCommand(DWORD command);
EVENT_API BOOL StartCommandIdle(void);
EVENT_API void StopCommandIdle(void);
EVENT_API void EnableMsgPump(BOOL val=TRUE);
EVENT_API BOOL IsEnabledMsgPump();
//////////////////////////////////////////////////////////////////////////
EVENT_API void CreateBridge();
EVENT_API void DestroyBridge();
//////////////////////////////////////////////////////////////////////////
class CMsgPump
{
public:
    CMsgPump(){EnableMsgPump(FALSE);}
    ~CMsgPump(){EnableMsgPump(TRUE);}
};
//////////////////////////////////////////////////////////////////////////
#define MIN_PR 255
#define MAX_PR 0
#define DEF_PR 128
//priority 0-max 255-min
template <class T,class T1> inline void RegisterEvent(DWORD command,T object,T1 method,BYTE priority=DEF_PR)
{
    __Add(command,CAST(Gag *,object),CAST(EventMethod, method),priority);
}
//////////////////////////////////////////////////////////////////////////
typedef void (__cdecl *CFunc)();
template <class T> inline void RegisterEventCFunc(DWORD command,T method,BYTE priority=DEF_PR)
{
    __Add(command,CAST(Gag *,method),CAST(EventMethod, method),priority);
}
//////////////////////////////////////////////////////////////////////////
template <class T,class T1> inline void RegisterTimerEvent(DWORD command,T object,T1 method,DWORD interval,BYTE priority=DEF_PR)
{
    __Add(command,CAST(Gag *,object),CAST(EventMethod, method),interval,priority);
}
//////////////////////////////////////////////////////////////////////////
template <class T,class T1> inline void RegisterIdleEvent(DWORD command,T object,T1 method,DWORD interval,BYTE priority=DEF_PR)
{
    __AddIdle(command,CAST(Gag *,object),CAST(EventMethod, method),interval,priority);
}
//////////////////////////////////////////////////////////////////////////
template <class T> inline void UnRegisterEvent(T object)
{
    __Remove((Gag *)object);
}
//////////////////////////////////////////////////////////////////////////
template <class T> inline void UnRegisterTimerEvent(DWORD command,T object)
{
    __Remove(command,(Gag *)object);
}
//////////////////////////////////////////////////////////////////////////
EVENT_API void StopEvent(DWORD command);
EVENT_API BOOL __MessagePump(void);
EVENT_API DWORD GetLastInputTime(void);
///////////////////////////////////////////////////////////////////////////////////////////////////
EVENT_API bool SendEvent(DWORD command);
template <class T1> bool SendEvent(DWORD command,T1 par)
{
    try
    {
        Gag	* object;						
        typedef void (Gag::*EventMethodPar)(T1);
        EventMethodPar method;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(object && method)
            {
                (object->*(method))(par);
            }
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
}

template <class T1,class T2> bool SendEvent(DWORD command,T1 par,T2 par2)
{
    try
    {
        Gag	* object;						
        typedef void (Gag::*EventMethodPar)(T1,T2);
        EventMethodPar method;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(object && method)
            {
                (object->*(method))(par,par2);
            }
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
}

template <class T1,class T2,class T3> bool SendEvent(DWORD command,T1 par,T2 par2,T3 par3)
{
    try
    {
        Gag	* object;						
        typedef void (Gag::*EventMethodPar)(T1,T2,T3);
        EventMethodPar method;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(object && method)
            {
                (object->*(method))(par,par2,par3);
            }
        }
    }
    catch(...)
    {
        return false;
    }
    return true;
}

template <class T1,class T2,class T3,class T4> bool SendEvent(DWORD command,T1 par,T2 par2,T3 par3,T4 par4)
{
    try
    {
        Gag	* object;						
        typedef void (Gag::*EventMethodPar)(T1,T2,T3,T4);
        EventMethodPar method;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(object && method)
            {
                (object->*(method))(par,par2,par3,par4);
            }
        }
    }
    catch(...)
    {
        return false;
    }
    return true;
}

template <class T1,class T2,class T3,class T4,class T5> bool SendEvent(DWORD command,T1 par,T2 par2,T3 par3,T4 par4,T5 par5)
{
    try
    {
        Gag	* object;						
        typedef void (Gag::*EventMethodPar)(T1,T2,T3,T4,T5);
        EventMethodPar method;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(object && method)
            {
                (object->*(method))(par,par2,par3,par4,par5);
            }
        }
    }
    catch(...)
    {
        return false;
    }
    return true;
}

template <class T1,class T2,class T3,class T4,class T5,class T6> bool SendEvent(DWORD command,T1 par,T2 par2,T3 par3,T4 par4,T5 par5,T6 par6)
{
    try
    {
        Gag	* object;						
        typedef void (Gag::*EventMethodPar)(T1,T2,T3,T4,T5,T6);
        EventMethodPar method;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(object && method)
            {
                (object->*(method))(par,par2,par3,par4,par5,par6);
            }
        }
    }
    catch(...)
    {
        return false;
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////
#define SEND_METHOD 0
#define POST_METHOD 1

class _Arg
{
public:
    DWORD command;
    UINT  postMethod;

    _Arg(DWORD c,UINT pm):command(c),postMethod(pm)
    {
    }

    virtual void Free()
    {
        if(this)
            delete this;
    }

    virtual void SendEvent(void)
    {
        try
        {
            Gag	* object;						
            EventMethod method;
            mapIterator cmdsPtr;
            for(long idx=__GetFirst(command,object,method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,method,cmdsPtr))
            {
                if(object && method)
                {
                    (object->*(method))();
                }
            }
        }
        catch(...)
        {
        }

    }
};

template <class T> 
class _Arg1:public _Arg
{
public:
    T par;

    _Arg1(DWORD c,T p,UINT pm):_Arg(c,pm),par(p)
    {
    }

    virtual void SendEvent(void)
    {
        try
        {
            Gag	* object;						
            typedef void (Gag::*EventMethodPar)(T);
            EventMethodPar method;
            mapIterator cmdsPtr;
            for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
            {
                if(object && method)
                {
                    (object->*(method))(par);
                }
            }
        }
        catch(...)
        {
        }

    }

};

template <class T,class T1> 
class _Arg2:public _Arg
{
public:
    T par;
    T1 par1;

    _Arg2(DWORD c,T p,T1 p1,UINT pm):_Arg(c,pm),par(p),par1(p1)
    {
    }

    virtual void SendEvent(void)
    {
        try
        {
            Gag	* object;						
            typedef void (Gag::*EventMethodPar)(T,T1);
            EventMethodPar method;
            mapIterator cmdsPtr;
            for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
            {
                if(object && method)
                {
                    (object->*(method))(par,par1);
                }
            }
        }
        catch(...)
        {
        }

    }
};

template <class T, class T1, class T2> 
class _Arg3:public _Arg
{
public:
    T par;
    T1 par1;
    T2 par2;

    _Arg3(DWORD c,T p,T1 p1,T2 p2,UINT pm):_Arg(c,pm),par(p),par1(p1),par2(p2)
    {
    }

    virtual void SendEvent(void)
    {
        try
        {
            Gag	* object;						
            typedef void (Gag::*EventMethodPar)(T,T1,T2);
            EventMethodPar method;
            mapIterator cmdsPtr;
            for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
            {
                if(object && method)
                {
                    (object->*(method))(par,par1,par2);
                }
            }
        }
        catch(...)
        {
        }

    }
};

template <class T, class T1, class T2,class T3> 
class _Arg4:public _Arg
{
public:
    T par;
    T1 par1;
    T2 par2;
    T3 par3;

    _Arg4(DWORD c,T p,T1 p1,T2 p2,T3 p3,UINT pm):_Arg(c,pm),par(p),par1(p1),par2(p2),par3(p3)
    {
    }

    virtual void SendEvent(void)
    {
        try
        {
            Gag	* object;						
            typedef void (Gag::*EventMethodPar)(T,T1,T2,T3);
            EventMethodPar method;
            mapIterator cmdsPtr;
            for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
            {
                if(object && method)
                {
                    (object->*(method))(par,par1,par2,par3);
                }
            }
        }
        catch(...)
        {
        }

    }
};

template <class T, class T1, class T2,class T3,class T4> 
class _Arg5:public _Arg
{
public:
    T par;
    T1 par1;
    T2 par2;
    T3 par3;
    T4 par4;

    _Arg5(DWORD c,T p,T1 p1,T2 p2,T3 p3,T4 p4,UINT pm):_Arg(c,pm),par(p),par1(p1),par2(p2),par3(p3),par4(p4)
    {
    }

    virtual void SendEvent(void)
    {
        try
        {
            Gag	* object;						
            typedef void (Gag::*EventMethodPar)(T,T1,T2,T3,T4);
            EventMethodPar method;
            mapIterator cmdsPtr;
            for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
            {
                if(object && method)
                {
                    (object->*(method))(par,par1,par2,par3.par4);
                }
            }
        }
        catch(...)
        {
        }

    }
};
//////////////////////////////////////////////////////////////////////////
EVENT_API void _PostEvent(_Arg * args);
//////////////////////////////////////////////////////////////////////////
inline void PostEvent(DWORD command,UINT pm=POST_METHOD)
{
    try
    {
        _Arg * arg=new _Arg(command,pm);
        _PostEvent(arg);
    }
    catch(...)
    {
    }
}

template <class T> void PostEvent(DWORD command,T par,UINT pm=POST_METHOD)
{
    try
    {
        _Arg1<T> * arg=new _Arg1<T>(command,par,pm);
        _PostEvent(arg);
    }
    catch(...)
    {
    }

}

template <class T,class T1> void PostEvent(DWORD command,T par, T1 par1,UINT pm=POST_METHOD)
{
    try
    {
        _Arg2<T,T1> * arg=new _Arg2<T,T1>(command,par,par1,pm);
        _PostEvent(arg);
    }
    catch(...)
    {
    }

}

template <class T,class T1,class T2> void PostEvent(DWORD command,T par, T1 par1,T2 par2,UINT pm=POST_METHOD)
{
    try
    {
        _Arg3<T,T1,T2> * arg=new _Arg3<T,T1,T2>(command,par,par1,par2,pm);
        _PostEvent(arg);
    }
    catch(...)
    {
    }

}

template <class T,class T1,class T2,class T3> void PostEvent(DWORD command,T par, T1 par1,T2 par2,T3 par3,UINT pm=POST_METHOD)
{
    try
    {
        _Arg4<T,T1,T2,T3> * arg=new _Arg4<T,T1,T2,T3>(command,par,par1,par2,par3,pm);
        _PostEvent(arg);
    }
    catch(...)
    {
    }

}

template <class T,class T1,class T2,class T3,class T4> void PostEvent(DWORD command,T par, T1 par1,T2 par2,T3 par3,T4 par4,UINT pm=POST_METHOD)
{
    try
    {
        _Arg4<T,T1,T2,T3,T4> * arg=new _Arg5<T,T1,T2,T3,T4>(command,par,par1,par2,par3,par4,pm);
        _PostEvent(arg);
    }
    catch(...)
    {
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T1> void SendEventCFunc(DWORD command,T1 par)
{
    try
    {
        typedef void (__cdecl *CFuncPar)(T1);
        CFuncPar method;
        Gag	* object;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(method)
                method(par);
        }
    }
    catch (...)
    {
    }
}

template <class T1,class T2> void SendEventCFunc(DWORD command,T1 par,T2 par2)
{
    try
    {
        typedef void (__cdecl *CFuncPar)(T1,T2);
        CFuncPar method;
        Gag	* object;
        mapIterator cmdsPtr;
        for(long idx=__GetFirst(command,object,(EventMethod &)method,cmdsPtr);idx!=-1;idx=__GetNext(idx,object,(EventMethod &)method,cmdsPtr))
        {
            if(method)
                method(par,par2);
        }
    }
    catch (...)
    {
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif