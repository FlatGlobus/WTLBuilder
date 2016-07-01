// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "MapFile.h"
//////////////////////////////////////////////////////////////////////////
MapFile::MapFile(DWORD delta)
{
	OpenMode=(openMode)-1;
	Buffer=NULL;
	CP=0;
	Size=0;
	Limit=0;
	Buffer=NULL;
	hFile=hFileMap=NULL;
	Delta=delta;
	kakDela=FALSE;
}
//////////////////////////////////////////////////////////////////////////
MapFile::MapFile(const CString& p,DWORD delta):path(p)
{
	Buffer=NULL;
	CP=0;
	Size=0;
	Limit=0;
	Buffer=NULL;
	hFile=hFileMap=NULL;
	Delta=delta;
	kakDela=FALSE;
}
//////////////////////////////////////////////////////////////////////////
MapFile::~MapFile(void)
{
	Close();
}
//////////////////////////////////////////////////////////////////////////
void MapFile::Open(const CString& p,openMode om,DWORD size)
{
    path = p;
	if(Buffer)
        return;
	Buffer=NULL;
	OpenMode=om;
	CP=0;
	
	if(((hFile=CreateFile((LPCTSTR)path,om))==INVALID_HANDLE_VALUE) && (om !=omTemp))
	{
		hFile=NULL;
		kakDela=FALSE;
		return;
	}
	
	switch(om)
	{
	case omRead:
		Size=GetFileSize(hFile,NULL);
		Limit=Size;
		break;
	case omWrite:
		Size=GetFileSize(hFile,NULL);
		if(Size > size)
			Limit=Size+Delta;
		else
			Limit=size;
		break;
	default:    Size=0;
		Limit=size;
	}
	
	hFileMap=CreateFileMapping(hFile,om,Limit);
	
	if(hFileMap==NULL)
	{
		CloseHandle(hFile);
		hFile=NULL;
		kakDela=FALSE;
		return;
	}
	
	Buffer=MapViewOfFile(hFileMap,om,Limit);
	if(Buffer==NULL)
	{
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		hFileMap=hFile=NULL;
		Buffer=NULL;
		kakDela=FALSE;
		return;
	}
	kakDela=TRUE;
}
//////////////////////////////////////////////////////////////////////////
void MapFile::Close(void)
{
	if(Buffer)
        UnmapViewOfFile(Buffer);
	if(hFileMap)
        CloseHandle(hFileMap);
	if((OpenMode!=omTemp) && (hFile!=NULL))
	{
		if((OpenMode==omWrite)||(OpenMode==omCreate))
		{
			SetFilePointer(hFile,Size,NULL,FILE_BEGIN);
			SetEndOfFile(hFile);
			FlushFileBuffers(hFile);
		}
		CloseHandle(hFile);
	}
	Buffer=hFile=hFileMap=NULL;
	kakDela=FALSE;
}
//////////////////////////////////////////////////////////////////////////
DWORD MapFile::Length(void)
{
	return Size;
}
//////////////////////////////////////////////////////////////////////////
void MapFile::Seek(DWORD offset,short fromWhere)
{
	switch(fromWhere)
	{
	case 0:
		if(offset<=Size)
			CP=offset;
		else
			CP=Size;
		break;
		
	case 1:if(CP+offset <= Size)
			   CP+=offset;
		else
			CP=Size;
		break;
		
	case 2:
		if(offset <= Size)
			CP=Size-offset;
		else
			CP=Size;
		
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
DWORD MapFile::Tell(void)
{
	return CP;
}
//////////////////////////////////////////////////////////////////////////
int MapFile::Eof(void)
{
	return CP>=Limit;
}
//////////////////////////////////////////////////////////////////////////
void MapFile::CopyTo(MapFile & Dest)
{
	if(Dest.Buffer==NULL) return;
	Dest.reSize(Size);
	MoveMemory(Dest.Buffer,Buffer,Size);
	Dest.Size=Size;
}
//////////////////////////////////////////////////////////////////////////
void MapFile::reSize(DWORD size)
{
	switch(OpenMode)
	{
	case omWrite :
	case omCreate:reSizeNoCopy(size);
		break;
	case omTemp  :reSizeWithCopy(size);
		break;
	case omRead
        :break;//error
	default :break;
	}
}
//////////////////////////////////////////////////////////////////////////
void MapFile::reSizeNoCopy(DWORD size)
{
	UnmapViewOfFile(Buffer);
	CloseHandle(hFileMap);
	Limit=size;
	hFileMap=CreateFileMapping(hFile,OpenMode,Limit);
	
	if(hFileMap==NULL)
	{
		CloseHandle(hFile);
		hFile=NULL;
		kakDela=FALSE;
	}
	
	Buffer=MapViewOfFile(hFileMap,OpenMode,Limit);
	if(Buffer==NULL)
	{
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		hFileMap=hFile=NULL;
		Buffer=NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
void MapFile::reSizeWithCopy(DWORD size)
{
	DWORD tmpLimit=Limit+size;
	HANDLE tmpFileMap=CreateFileMapping(INVALID_HANDLE_VALUE,omTemp,tmpLimit);
	
	PVOID tmpBuffer=MapViewOfFile(tmpFileMap,omTemp,tmpLimit);
	if(Buffer==NULL)
	{
		CloseHandle(tmpFileMap);
		kakDela=FALSE;
	}
	MoveMemory(tmpBuffer,Buffer,Limit);
	
	UnmapViewOfFile(Buffer);
	CloseHandle(hFileMap);
	
	hFileMap=tmpFileMap;
	Buffer=tmpBuffer;
	Limit=tmpLimit;
}
//////////////////////////////////////////////////////////////////////////
HANDLE MapFile::CreateFile(LPCTSTR _path,openMode om)
{
	if(_path)
	{
		HANDLE tmpHANDLE;
			switch(om)
			{
			case omRead  :tmpHANDLE=::CreateFile(_path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL);
				break;
			case omWrite :tmpHANDLE=::CreateFile(_path,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL);
				break;
			case omCreate:tmpHANDLE=::CreateFile(_path,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL);
				break;
			case omTemp:
                return INVALID_HANDLE_VALUE;
			}
			if(tmpHANDLE!=INVALID_HANDLE_VALUE)
				return tmpHANDLE;
	}
	return INVALID_HANDLE_VALUE;
}
//////////////////////////////////////////////////////////////////////////
HANDLE MapFile::CreateFileMapping(HANDLE _file,openMode om,DWORD &size)
{
	if((_file==INVALID_HANDLE_VALUE) && (om!=omTemp))
		return NULL;
	switch(om)
	{
	case omRead  :return ::CreateFileMapping(_file,NULL,PAGE_READONLY,0,0,NULL);
	case omCreate:
	case omWrite :
		{
			size=GetFileSize(_file,NULL)+size;
			return ::CreateFileMapping(_file,NULL,PAGE_READWRITE,0,size,NULL);
		}
		
	case omTemp:return ::CreateFileMapping(_file,NULL,PAGE_READWRITE,0,size,NULL);
	}
	
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
PVOID MapFile::MapViewOfFile(HANDLE fileMap,openMode om,DWORD size)
{
	switch(om)
	{
    case omRead  : return ::MapViewOfFile(fileMap,FILE_MAP_READ,0,0,0);
		
    case omWrite :
    case omCreate: return ::MapViewOfFile(fileMap,FILE_MAP_WRITE,0,0,size);
		
    case omTemp  : return ::MapViewOfFile(fileMap,FILE_MAP_WRITE,0,0,size);
	}
	
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
MapFile & MapFile::operator <<(LPTSTR str)
{
	DWORD len=0;
	if(str==NULL)
	{
		*this<<len;
	}
	else
	{
		len=(DWORD)_tcslen(str);
		*this<<len;
		PutBuffer((void *)str,len);
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////
MapFile & MapFile::operator >>(LPTSTR&str)
{
	if(str)
	{
		delete [] str;
		str=NULL;
	}

	DWORD len;
	*this>>len;
	if(len)
	{
		str=new _TCHAR[len+1];
		GetBuffer((void *)str,len);
		str[len]=0;
	}
	return *this;
}
