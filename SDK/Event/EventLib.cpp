// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma warning(disable:4786)
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include "EventLib.h"

//////////////////////////////////////////////////////////////////////////
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////
class DispatcherItem
{
public:
	DispatcherItem(void):object(NULL),method(NULL),priority(255),resolution(0)
	{
	}

	DispatcherItem(const DispatcherItem & di):object(di.object),method(di.method),
		priority(di.priority),resolution(di.resolution)
	{
	}

	DispatcherItem(Gag * o,EventMethod m,BYTE p):object(o),method(m),priority(p),
		resolution(0)
	{

	}

	DispatcherItem(Gag * o,EventMethod m,UINT t,BYTE p):object(o),method(m),priority(p),
		resolution(t)
	{
		
	}
	
	Gag * object;
	EventMethod method;
	BYTE priority;
	UINT resolution;
};
//////////////////////////////////////////////////////////////////////////
bool ComparePriority (DispatcherItem  a, DispatcherItem  b)
{
	return a.priority < b.priority;
}

typedef vector<DispatcherItem> DispatcherItemArray;

class DispatcherCommand
{
public:
	DispatcherCommand(void):command(0xFFFFFFFF),disabled(false)
	{
	}

	DispatcherCommand(DWORD c):command(c),disabled(false)
	{
	}
	
	~DispatcherCommand() { array.clear(); }

	void Add(const DispatcherItem &item)
	{
		if(Find(item.object)==-1)
		{
			array.push_back(item);
		}
		Sort();
	}
	
	void Remove(Gag * obj)
	{
		int idx=Find(obj);
		if(idx!=-1)
            array.erase(array.begin()+idx);
	}

	int Find(Gag * obj)
	{
		DispatcherItemArray::iterator i=array.begin();
		for(int j=0;i!=array.end();i++,j++)
			if(i->object==obj)
				return j;
		return -1;
	}
	
	DispatcherItem & operator[](int idx) { return array[idx]; }

	int GetSize() { return (int)array.size(); }
	
	DWORD GetCommand(void) { return command; }
	
    void StopCommand() {disabled = true;}
    bool GetDisabled() {return disabled;}
    void ReleaseCommand() {disabled = false;}

protected:	

	void Sort()
	{
		sort(array.begin(),array.end(), ComparePriority);
	}
	
	DispatcherItemArray array;
	DWORD command;
    bool  disabled;
private:
	DispatcherCommand(const DispatcherCommand &)
	{
	}
};
//////////////////////////////////////////////////////////////////////////
typedef map<long,DispatcherCommand *> DispatcherCommandMap;
//typedef map<long,DispatcherCommand *>::iterator mapIterator;
typedef pair<long,DispatcherCommand *> Command_Pair;
class Dispatcher
{
public:
	Dispatcher(void);
	~Dispatcher(void);
	void Add(DWORD c,Gag * o,EventMethod m,BYTE p);
	void Add(DWORD c,Gag * o,EventMethod m,UINT timerID,BYTE p);
	void Remove(Gag *);
	long GetFirst(DWORD val,Gag *& o,EventMethod & m, mapIterator &cmdsPtr);
	long GetNext(DWORD idx,Gag *& o,EventMethod & m, mapIterator &cmdsPtr);
	void StopEvent(DWORD command);
	DWORD GetAvailableCommandID(void);
protected:
	DWORD lastUsedCommand;
	int   lastUsedIndex;
	DispatcherCommandMap commands;
	
};
static Dispatcher dispatcher;
//////////////////////////////////////////////////////////////////////////

//IEVENT_API void __Add(Gag * o,EventMethod m,BYTE p)
//{
//	dispatcher.Add((DWORD)o,o,m,p);
//}

EVENT_API void __Add(DWORD c,Gag * o,EventMethod m,BYTE p)
{
	dispatcher.Add(c,o,m,p);
}

EVENT_API void __Remove(Gag * val)
{
	dispatcher.Remove(val);
}

EVENT_API DWORD __GetFirst(DWORD command,Gag *&object,EventMethod & method, mapIterator &cmdsPtr)
{
	__MessagePump();
	return dispatcher.GetFirst(command,object,method,cmdsPtr);
}

EVENT_API DWORD __GetNext(DWORD idx,Gag *&object,EventMethod &method, mapIterator &cmdsPtr)
{
	__MessagePump();
	return dispatcher.GetNext(idx,object,method,cmdsPtr);
}

EVENT_API void StopEvent(DWORD command)
{
	dispatcher.StopEvent(command);
}

EVENT_API DWORD GetAvailableCommandID(void)
{
	return dispatcher.GetAvailableCommandID();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
Dispatcher::Dispatcher(void):lastUsedCommand(0xFFFFFFFF),
lastUsedIndex(0xFFFFFFFF)
{
}

Dispatcher::~Dispatcher(void)
{
    
	for(mapIterator i=commands.begin();i!=commands.end();++i)
		delete (i->second);
	
	commands.clear();
}

void Dispatcher::StopEvent(DWORD command)
{
    mapIterator idx=commands.find(command);
    if(idx!=commands.end())
    {
        idx->second->StopCommand();
    }
}

void Dispatcher::Add(DWORD c,Gag * o,EventMethod m,BYTE p)
{
    mapIterator idx=commands.find(c);
	if(idx==commands.end())
    {
        DispatcherCommand *dc=new DispatcherCommand(c);
        dc->Add(DispatcherItem(o,m,p));
		commands.insert(Command_Pair(c,dc));
    }
    else
	    idx->second->Add(DispatcherItem(o,m,p));
}

void Dispatcher::Add(DWORD c,Gag * o,EventMethod m,UINT timerID,BYTE p)
{
    mapIterator idx=commands.find(c);
	if(idx==commands.end())
    {
        DispatcherCommand *dc=new DispatcherCommand(c);
        dc->Add(DispatcherItem(o,m,timerID,p));
		commands.insert(Command_Pair(c,dc));
    }
    else
	    idx->second->Add(DispatcherItem(o,m,timerID,p));
}

void Dispatcher::Remove(Gag * val)
{
	mapIterator i=commands.begin();
	for(;i!=commands.end();i++)
	{
		i->second->Remove(val);
		if(i->second->GetSize()==0)
		{
			delete i->second;
			commands.erase(i);
			i=commands.begin();
		}
	}
}

long Dispatcher::GetFirst(DWORD c,Gag *& o,EventMethod & m, mapIterator &cmdsPtr)
{
	o=NULL;
	m=NULL;
		
	cmdsPtr = commands.find(c);
	if((mapIterator &)cmdsPtr==commands.end())
		return -1;
    ((mapIterator &)cmdsPtr)->second->ReleaseCommand();

	o=(*((mapIterator &)cmdsPtr)->second)[0].object;
	m=(*((mapIterator &)cmdsPtr)->second)[0].method;

	return 0;
}

long Dispatcher::GetNext(DWORD idx,Gag *& o,EventMethod & m, mapIterator &cmdsPtr)
{
	o=NULL;
	m=NULL;

    mapIterator cmd;
    //if(cmdsPtr==NULL)
    //    cmd=commands.find(command);
	//else
        cmd=CAST(mapIterator,cmdsPtr);

	if(cmd==commands.end())
		return -1;

    if(cmd->second->GetDisabled() == true)	
        return -1;

    if((idx+=1) < (DWORD)cmd->second->GetSize())
	 {
		 o=(*cmd->second)[idx].object;
		 m=(*cmd->second)[idx].method;
		 return idx;
	 }

	return -1;
}
//////////////////////////////////////////////////////////////////////////
bool CompareCommand (DispatcherCommand * a, DispatcherCommand * b)
{
	return a->GetCommand() < b->GetCommand();
}
//////////////////////////////////////////////////////////////////////////
DWORD Dispatcher::GetAvailableCommandID(void)
{
    //typedef map<long,DispatcherCommand *>::iterator mapIterator;
	for(long i= BEGIN_AVAILABLE_ID; i < 0xFFFFFFFF; i++)
        if(commands.find(i)==commands.end())
			return i;

	return 0;
}
//////////////////////////////////////////////////////////////////////////
class CommandItem
{
public:
	DWORD	command;
	UINT	count;	
	BOOL	state;
	DWORD	rest;

	CommandItem(void):command(0),count(0),state(FALSE)
	{
	}
	
	CommandItem(DWORD c):command(c),count(1),state(TRUE)
	{
	}

	void Add(void)
	{
		count+=1;
	}

	UINT Dec(void)
	{
		return count-=1;
	}

	void Start()
	{
		state=TRUE;
	}

	void Stop()
	{
		state=FALSE;
	}
};

bool operator==(const CommandItem& i1, const CommandItem& i2)
{
	return i1.command == i2.command;
}

typedef vector<CommandItem> CommandArray;
typedef CommandArray::iterator CommandArrayIterator;

class TimerItem
{
public:
	TimerItem():current(0),nextTime(0xFFFFFFFF),interval(0xFFFFFFFF)
		
	
	{
	}

	TimerItem(DWORD i):current(0),interval(i),nextTime(0xFFFFFFFF)
	{
	}
	
	void SetInterval(DWORD i)
	{
		interval=i;
	}

	DWORD GetInterval()
	{
		return interval;
	}
	
	BOOL GetFirstCommand(CommandItem& ci)
	{
		if(commands.empty())
			return FALSE;
		current=0;
		ci=commands[current];
		return TRUE;
	}

	BOOL GetNextCommand(CommandItem& ci)
	{
		if(commands.empty())
			return FALSE;

		current+=1;
		if(current >= (int)commands.size())
			return FALSE;
		ci=commands[current];
		return TRUE;
	}
		
	void AddCommand(DWORD command)
	{
		CommandArrayIterator found=find(commands.begin(),commands.end(),command);
		if(found==commands.end())
			commands.push_back(command);
		else
			found->Add();
	}

	BOOL RemoveCommand(DWORD command)
	{
		CommandArrayIterator found=find(commands.begin(),commands.end(),command);
		if(found!=commands.end())
		{
			if(found->Dec()==0)
			{
				commands.erase(found);
				return TRUE;
			}
		}
		return FALSE;
	}

	void SetCommandState(DWORD command,BOOL state)
	{
		if(command!=-1)
		{
			CommandArrayIterator found=find(commands.begin(),commands.end(),command);
			if(found!=commands.end())
			{
				if(state==TRUE)
					found->Start();
				else
					found->Stop();
			}
		}
		else
		{
			CommandArrayIterator found=commands.begin();
			while(found!=commands.end())
			{
				if(state==TRUE)
					found->Start();
				else
					found->Stop();
				++found;
			}
			
		}
	}
	
	BOOL IsEmpty(void)
	{
		return commands.empty();
	}
		
	BOOL IsReady(DWORD delta)
	{
		if((delta - nextTime) > interval)
			return TRUE;
		return FALSE;
	}

	void SetNextTime(DWORD nt)
	{
		nextTime=nt;
	}
		
protected:	
		
	DWORD nextTime; 
	DWORD interval;
	CommandArray commands;
	int current;
};

bool CompareTimers (TimerItem & a, TimerItem &  b)
{
	return a.GetInterval() < b.GetInterval();
}

typedef vector<TimerItem> TimersVector;
typedef TimersVector::iterator TimersVectorIterator;
//////////////////////////////////////////////////////////////////////////
class SimpleLock
{
public:
	SimpleLock(BOOL wait=FALSE)
	{
		if(wait==TRUE)
			IsLocked(wait);
		Lock();
	}

	~SimpleLock(void)
	{
		UnLock();
	}

	BOOL IsLocked(BOOL wait=FALSE)
	{
		if(wait==TRUE)
		{
			while(lockFlag==TRUE)
			{
				__MessagePump();
			}
		}
		
		return lockFlag;
	}
	
	void Lock()
	{
		lockFlag=TRUE;
	}
	
	void UnLock()
	{
		lockFlag=FALSE;
	}
	
protected:
	static BOOL lockFlag;
};

BOOL SimpleLock::lockFlag=FALSE;
//////////////////////////////////////////////////////////////////////////
class ThreadBridge
{
public:
	ThreadBridge();
	virtual ~ThreadBridge();
	void PostEvent(_Arg *arg);
	BOOL StartCommandTimer(UINT resolution);
	void StopCommandTimer(void);
	void AddTimerCommand(DWORD interval,DWORD command);
	void RemoveTimerCommand(DWORD interval);
	void SetTimerCommandState(DWORD command,BOOL state);
	void AddIdleCommand(DWORD interval,DWORD command);
	void RemoveIdleCommand(DWORD interval);
	void SetIdleCommandState(DWORD command,BOOL state);

	void EnableMsgPump(BOOL val)
	{
		enableMsgPump=val;
	}

	BOOL IsEnabledMsgPump()
	{
		return enableMsgPump;
	}

	friend EVENT_API BOOL __MessagePump(void);

protected:
	HWND WND;
	UINT TimerID;
	DWORD timerInterval;
	DWORD startTickCount;
	TimersVector timers;
	TimersVector idles;
	BOOL	enableMsgPump;

	UINT ThreadBridgeMessage;

	void SortTimer()
	{
		sort(timers.begin(),timers.end(), CompareTimers);
	}

	int FindTimer(DWORD interval)
	{
		TimersVectorIterator i=timers.begin();
		for(int j=0;i!=timers.end();++i,++j)
			if(i->GetInterval()==interval)
				return j;
			return -1;
	}

	void SortIdle()
	{
		sort(idles.begin(),idles.end(), CompareTimers);
	}
	
	int FindIdle(DWORD interval)
	{
		TimersVectorIterator i=idles.begin();
		for(int j=0;i!=idles.end();++i,++j)
			if(i->GetInterval()==interval)
				return j;
			return -1;
	}
	
	BOOL CreateThreadWindow();

	static LRESULT WINAPI wndproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	static VOID CALLBACK BridgeTimerProc(HWND,UINT,UINT_PTR,DWORD);
};


static ThreadBridge *_threadBridge = NULL;

void CreateBridge()
{
	if (_threadBridge == NULL)
		_threadBridge = new ThreadBridge;
}

void DestroyBridge()
{
	if (_threadBridge != NULL)
		delete _threadBridge;
	_threadBridge = NULL;
}
//////////////////////////////////////////////////////////////////////////
ThreadBridge::ThreadBridge():WND(0),TimerID(0),startTickCount(0),ThreadBridgeMessage(0),timerInterval(0xFFFF),
enableMsgPump(TRUE)
{
}
	
ThreadBridge::~ThreadBridge()
{
	if(IsWindow(WND))
		DestroyWindow(WND);
	StopCommandTimer();
}

BOOL ThreadBridge::CreateThreadWindow(void)
{
	if(IsWindow(WND)==FALSE)
	{
		WNDCLASS wc = {0, wndproc, 0, sizeof(this), GetModuleHandle(NULL), 0, 0, 0, 0, TEXT("ThreadBrige")};
		WND = CreateWindow((LPCTSTR)RegisterClass(&wc), TEXT("ThreadBrige"), 0, 0, 0, 0, 0, 0, 0, wc.hInstance, NULL);
		ThreadBridgeMessage=RegisterWindowMessage(TEXT("EventThreadBridgeMessage"));
	}
	return WND!=NULL;
}
	
void ThreadBridge::PostEvent(_Arg *arg)
{
	if(CreateThreadWindow()==TRUE)
	{
		if(arg && IsWindow(WND)!=FALSE)
		{
			if(arg->postMethod==POST_METHOD)
				::PostMessage(WND, ThreadBridgeMessage, 0,(LPARAM)arg);
			else
				::SendMessage(WND, ThreadBridgeMessage, 0, (LPARAM)arg);
		}
	}
}

BOOL ThreadBridge::StartCommandTimer(UINT resolution)
{
	if(timerInterval > resolution)
	{
		timerInterval=resolution;
		StopCommandTimer();
		if((resolution > 0 && resolution < 0xFFFF))
		{
			TimerID=(UINT)SetTimer(NULL,0,resolution,(TIMERPROC)BridgeTimerProc);
			startTickCount=GetTickCount();

			TimersVectorIterator found=timers.begin();
			while(found!=timers.end())
			{
				found->SetNextTime(startTickCount);
				found++;
			}
				
			return TRUE;
		}
	}
	return FALSE;
}

void ThreadBridge::StopCommandTimer(void)
{
	if(TimerID!=0)
	{
		KillTimer(WND,TimerID);
	}
	TimerID=0;
}

void ThreadBridge::AddTimerCommand(DWORD interval,DWORD command)
{
	int idx=FindTimer(interval);
	if(idx==-1)
	{
		TimerItem ti(interval);
		ti.AddCommand(command);
		timers.push_back(ti);
		SortTimer();
	}
	else
		timers[idx].AddCommand(command);
}

void ThreadBridge::SetTimerCommandState(DWORD command,BOOL state)
{
	TimersVectorIterator found=timers.begin();
	while(found!=timers.end())
	{
		found->SetCommandState(command,state);
		found++;
	}
}

void ThreadBridge::RemoveTimerCommand(DWORD command)
{
	TimersVectorIterator found=timers.begin();
	while(found!=timers.end())
	{
		found->RemoveCommand(command);
		found++;
	}
}

void ThreadBridge::AddIdleCommand(DWORD interval,DWORD command)
{
	int idx=FindIdle(interval);
	if(idx==-1)
	{
		TimerItem ti(interval);
		ti.AddCommand(command);
		ti.SetNextTime(0);
		idles.push_back(ti);
		SortIdle();
	}
	else
		idles[idx].AddCommand(command);
}

void ThreadBridge::SetIdleCommandState(DWORD command,BOOL state)
{
	TimersVectorIterator found=idles.begin();
	while(found!=idles.end())
	{
		found->SetCommandState(command,state);
		found++;
	}
}

void ThreadBridge::RemoveIdleCommand(DWORD command)
{
	TimersVectorIterator found=idles.begin();
	while(found!=idles.end())
	{
		found->RemoveCommand(command);
		found++;
	}
}

LRESULT WINAPI ThreadBridge::wndproc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if(_threadBridge != NULL && Msg==_threadBridge->ThreadBridgeMessage)
	{
		_Arg * arg=(_Arg*)lParam;
		if(arg)
		{
			arg->SendEvent();
			arg->Free();
		}
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

VOID CALLBACK ThreadBridge::BridgeTimerProc(HWND,UINT,UINT_PTR,DWORD currentTickCount)// проверку на 49 дней
{
	SimpleLock lock(TRUE);
	//currentTickCount=GetTickCount();
	if (_threadBridge != NULL)
	{
		for (int i = 0; i < (int)_threadBridge->timers.size() && _threadBridge->timers[i].IsReady(currentTickCount); i++)
		{
			CommandItem commandItem;
			if (_threadBridge->timers[i].GetFirstCommand(commandItem))
			{
				do
				{
					if (!commandItem.command)
						break;
					if (commandItem.state && ::IsWindow(_threadBridge->WND) != FALSE)
						::SendEvent(commandItem.command);
					//::PostEvent(commandItem.command);
				} while (_threadBridge->timers[i].GetNextCommand(commandItem));
			}
			_threadBridge->timers[i].SetNextTime(currentTickCount);
		};
	}
	//for(i=0; i < _threadBridge.idles.size() && _threadBridge.idles[i].IsReady(GetLastInputTime());i++)
	//{
	//	CommandItem commandItem;
	//	if(_threadBridge.idles[i].GetFirstCommand(commandItem))
	//	{
	//		do
	//		{
	//			if(!commandItem.command)
	//				break;
	//			if(commandItem.state)
	//				::PostEvent(commandItem.command);
	//		}
	//		while(_threadBridge.idles[i].GetNextCommand(commandItem));
	//	}
		//_threadBridge.idles[i].SetNextTime(currentTickCount);
	//}; 
	
}

EVENT_API void _PostEvent(_Arg * arg)
{
	if(_threadBridge != NULL)
		_threadBridge->PostEvent(arg);
}

EVENT_API void __Add(DWORD c,Gag * o,EventMethod m,DWORD interval,BYTE p)
{
	SimpleLock lock(TRUE);
	dispatcher.Add(c,o,m,interval,p);
	if (_threadBridge != NULL)
		_threadBridge->AddTimerCommand(interval,c);
}

EVENT_API void __Remove(DWORD command,Gag * val)
{
	SimpleLock lock(TRUE);
	dispatcher.Remove(val);	
	if (_threadBridge != NULL)
		_threadBridge->RemoveTimerCommand(command);
}

EVENT_API void StartCommand(DWORD command)
{
	SimpleLock lock(TRUE);
	if (_threadBridge != NULL)
		_threadBridge->SetTimerCommandState(command,TRUE);
}

EVENT_API void StopCommand(DWORD command)
{
	SimpleLock lock(TRUE);
	if (_threadBridge != NULL)
		_threadBridge->SetTimerCommandState(command,FALSE);
}

EVENT_API void StartAllCommand(void)
{
	SimpleLock lock(TRUE);
	if (_threadBridge != NULL)
		_threadBridge->SetTimerCommandState(0,TRUE);
}

EVENT_API void StopAllCommand(void)
{
	SimpleLock lock(TRUE);
	if (_threadBridge != NULL)
		_threadBridge->SetTimerCommandState(0,FALSE);
}

EVENT_API BOOL __MessagePump(void)
{
	if(IsEnabledMsgPump()==FALSE)
		return TRUE;

	MSG msg;
	if(::PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
	{
		if(msg.message != WM_QUIT)
		{
			::GetMessage(&msg,NULL,NULL,NULL);
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	return TRUE;
}

EVENT_API BOOL StartCommandTimer(UINT resolution)
{
	if (_threadBridge != NULL)
		return _threadBridge->StartCommandTimer(resolution);
	return FALSE;
}

EVENT_API void StopCommandTimer(void)
{
	if (_threadBridge != NULL)
		_threadBridge->StopCommandTimer();
}

EVENT_API void __AddIdle(DWORD c,Gag * o,EventMethod m,DWORD interval,BYTE p)
{
	dispatcher.Add(c,o,m,interval,p);
	if (_threadBridge != NULL)
		_threadBridge->AddIdleCommand(interval,c);
}

EVENT_API void EnableMsgPump(BOOL val)
{
	if (_threadBridge != NULL)
		_threadBridge->EnableMsgPump(val);
}

EVENT_API BOOL IsEnabledMsgPump()
{
	if (_threadBridge != NULL)
		return _threadBridge->IsEnabledMsgPump();
	return FALSE;
}

EVENT_API bool SendEvent(DWORD command)
{
	try
	{
		Gag	* object;
		EventMethod method;
		mapIterator cmdsPtr;
		for (long idx = __GetFirst(command, object, method, cmdsPtr); idx != -1; idx = __GetNext(idx, object, method, cmdsPtr))
		{
			if (object && method)
			{
				(object->*(method))();
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}
