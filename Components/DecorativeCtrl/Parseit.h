#ifndef	__PARSEIT_H_
#define	__PARSEIT_H_

///////////////////////////////////////////////////////////////////////////////////	
//	class definition for the ParseField class
///////////////////////////////////////////////////////////////////////////////////
//	this class is just a CString with some assignment and cast operators
//	it is used to store a parsed field value and allow the data to be accessed
//	thru casting the result to the wanted datatype
//	************************** ALLOWED OPERATIONS *********************************
//	CParseField p;
//	p="1234.12" 		// assignment to LPCTSTR
//	CStrinf e=(LPCTSTR)p;//	operator (LPCTSTR)
//	double d=(double)p;	//	d=1234.12 	operator double 
//	int n=(int)p;		//	n=1234 	operator int
//////////////////////////////////////////////////////////////////////////////////
#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlgdi.h>
#include <atlmisc.h>

class CParseField
{
public:
	CParseField() {};
	~CParseField() {};

    operator int() 		{ return _tstoi(TheData);};
	operator long()		{ return _tstoi(TheData);};
	operator double()	{ return _tstoi(TheData);};
	operator LPCTSTR()	{ return (LPCTSTR) TheData;}; const
	CParseField& operator =(LPCTSTR s) {TheData=s;return *this;};
	CParseField&  operator =(CString& s) {TheData=s;return *this;};
	CParseField&  operator =(CParseField& s) {TheData=s.TheData;return *this;};
	
// Implementation
protected:
	CString	TheData;
};
///////////////////////////////////////////////////////////////////////////////////
//	END OF CparseField DEFINITION AND CODE ( ALL FUNCTIONS HERE)
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////	
//	class definition for the Parsing class
///////////////////////////////////////////////////////////////////////////////////
typedef CSimpleArray<CParseField*> CParseFieldArray;

class CParseIt
{
public:
	CParseIt(BOOL Strip=FALSE);
	CParseIt(LPCTSTR Data,LPCTSTR Sep=_T(","),BOOL Strip=FALSE);
	~CParseIt();

	//	use default constructoe then call this function to open and use a file contaimning
	//	the data    
    
// Attributes
public:
// Operations             
protected:           
	BOOL 		IsSeperator(_TCHAR s);
public:         
	//	returns the one based number of fields if 0 there are no fields
	int			GetNumFields() {return NumFields;};
	//	returns the list of seperators
	LPCTSTR		GetSeperator() {return Seperator;};
	//	sets the seperator list IE "|,*"
    void		SetSeperator(LPCTSTR Sep) {_tcsncpy(Seperator,Sep,9);};
	//	parse a object constructed bt the second constructor (data,sep);
	BOOL		Parse();
	//	parse a object created by the default constructor will call Parse();
	BOOL		Parse(LPCTSTR Data,LPCTSTR Sep=_T(","),BOOL Strip=FALSE);
	//	returns the 1 based field in a cstring or a string
	BOOL	 	GetField(int nFNum,CString& Buff);
	BOOL	 	GetField(int nFNum,LPTSTR Buff);
	//	will return the cparsefield object. This can be cast to the desired type
	//	by (int) (long) (double) (lpcstr)
	CParseField	GetField(int n);
	
// Implementation
public:
	void ReSet();

protected:
	BOOL		StripQuotes;
	_TCHAR		Seperator[10];
	int			NumFields;
	CParseFieldArray	TheFields;	
	LPTSTR		TheData;
	
};




#endif
