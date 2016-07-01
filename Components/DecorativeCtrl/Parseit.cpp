#include "stdafx.h"
#include <stdarg.h>
#include "parseit.h"

///////////////////////////////////////////////////////////////////////////
//	Desc:	default constructor just set some default values
//	params:
//	returns:
///////////////////////////////////////////////////////////////////////////
CParseIt::CParseIt(BOOL Strip)
{
	_tcscpy(Seperator,_T(","));
	StripQuotes=Strip;
	NumFields=0;
	TheData=NULL;
}

///////////////////////////////////////////////////////////////////////////
//	Desc:	construct object to parse data using sep for the list of seperators
//	params:
//	returns:
///////////////////////////////////////////////////////////////////////////
CParseIt::CParseIt(LPCTSTR Data,LPCTSTR Sep,BOOL Strip)
{
	NumFields=0;
	StripQuotes=Strip;
	TheData=new _TCHAR[_tcslen(Data)+1];
	_tcscpy(TheData,Data);
	_tcsncpy(Seperator,Sep,9);
	Parse();
	
}
///////////////////////////////////////////////////////////////////////////
//	Desc:	destructor: free all allocated memory variables and free up the
//			data stored in the pointer array
//	params:
//	returns:
///////////////////////////////////////////////////////////////////////////
CParseIt::~CParseIt()
{   
	CParseField* pData;
	if(TheData!=NULL)
		delete[] TheData;
	for(int y=0;y < TheFields.GetSize();++y)
	{
		pData=(CParseField*)TheFields[y];
		delete pData;
	}						
}

void CParseIt::ReSet()
{
	CParseField* pData;
	if(TheData!=NULL)
	{
		delete[] TheData;
		TheData=NULL;
	}
	for(int y=0;y < TheFields.GetSize();++y)
	{
		pData=(CParseField*)TheFields[y];
		delete pData;
	}						
	TheFields.RemoveAll();

}

///////////////////////////////////////////////////////////////////////////
//	Desc:	parse the string data using sep as a seperator list
//	params: data=string to parse sep= list of seperators
//	returns:TRUE if all is well else FALSE if error occours
///////////////////////////////////////////////////////////////////////////
BOOL CParseIt::Parse(LPCTSTR Data,LPCTSTR Sep,BOOL Strip)
{
	if(TheData!=NULL)
		return FALSE;
	StripQuotes=Strip;
	_tcsncpy(Seperator,Sep,9);
	TheData=new _TCHAR[_tcslen(Data)+1];
	_tcscpy(TheData,Data);
	return Parse();
}
///////////////////////////////////////////////////////////////////////////
//	Desc:	Called to do actual parsing of data
//	params:	none
//	returns:TRUE if OK else FALSE
///////////////////////////////////////////////////////////////////////////
BOOL CParseIt::Parse()
{
	if(TheData==NULL)
		return FALSE;                      
	
	for(int p=0;p < TheFields.GetSize();++p)
	{
		CParseField* pData=(CParseField*)TheFields[p];
		delete pData;
	}						
	TheFields.RemoveAll();
		
	NumFields=0;
	CString t;		
	t.Empty();        
	for(int y=0;y < (int)_tcslen(TheData);++y)
	{                       
		if( !IsSeperator(TheData[y]))
		{
			if(StripQuotes)
			{
				if(TheData[y] !='\"')
					t+=TheData[y];
			}
			else
				t+=TheData[y];
		}
		else
		{
			CParseField* pData=new CParseField;     
			*pData=t;
			TheFields.Add(pData);
			t.Empty();
			++NumFields;
		}   
	}
	CParseField* pData=new CParseField;
	*pData=t;
	TheFields.Add(pData);
	++NumFields;
	return TRUE;		
}
///////////////////////////////////////////////////////////////////////////
//	Desc: 	determines if the given cahracter is in the list of seperators
//	params:	The character in question
//	returns:TRUE if the cahr is a seperator else FALSE
///////////////////////////////////////////////////////////////////////////
BOOL CParseIt::IsSeperator(_TCHAR s)
{
	for(int x=0;x < (int) _tcslen(Seperator);++x)
	{
		if(s==Seperator[x])
			return TRUE;
	}
	return FALSE;
}					
///////////////////////////////////////////////////////////////////////////
//	Desc:	returns field n in the cstring buff (1 based not zero based
//	params: The field number (1..nun fields) and a CString reference
//	returns:TRUE if OK else FALSE (out of bounds index)
///////////////////////////////////////////////////////////////////////////
BOOL CParseIt::GetField(int N,CString& Buff)
{   
	if(N <= TheFields.GetSize() && N > 0)
	{      
		Buff=(LPCTSTR)*(CParseField*)TheFields[--N];
		return TRUE;
	}
	Buff.Empty();
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////
//	Desc:	returns field n in the string buff (1 based not zero based
//	params: The field number (1..nun fields) and a pointer to a string
//	returns:TRUE if OK else FALSE (out of bounds index)
///////////////////////////////////////////////////////////////////////////
BOOL CParseIt::GetField(int N,LPTSTR Buff)
{   
	if(N <= TheFields.GetSize() && N > 0)
	{      
		_tcscpy(Buff,(LPCTSTR)*(CParseField*)TheFields[--N]);
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////
//	Desc:	returns the CParseField object for the indicated field ( 1 based)
//	params:	the 1 based index of the field
//	returns:A CparseField object ( this can be cast to a string,long,double or int)
///////////////////////////////////////////////////////////////////////////
CParseField  CParseIt::GetField(int N)
{                                        
	CParseField p;
	if(N <= TheFields.GetSize() && N > 0)
	{      
		--N;
		return *(CParseField*)TheFields[N];
	}
	return p;
}

