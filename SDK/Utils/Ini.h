///////////////////////////////////////////////////////////////////
//                 Ini.h
//
// "CIni" is a simple API wrap class used for ini file access.
// The purpose of this class is to make ini file access more
// convenient than direct API calls.
//	
// This file is distributed "as is" and without any expressed or implied
// warranties. The author holds no responsibilities for any possible damages
// or loss of data that are caused by use of this file. The user must assume
// the entire risk of using this file.
//
// 7/08/2002    Bin Liu
//
// Update history:
//
//  7/08/2002 -- Initial release.
//  7/14/2002 -- Added "IncreaseInt" and "AppendString"
//  9/02/2002 -- Added "removeProfileSection" and "RemoveProfileEntry"
//  2/09/2003 -- The class has been made unicode-compliant
// 11/04/2003 -- Integrated MFC support, added in new member functions
//               for accessing arrays.
// 11/08/2003 -- Fixed "GetString" and "GetPathName" method, changed parameter
//               from "LPSTR" to "LPTSTR"
// 11/10/2003 -- Renamed method "GetKeys" to "GetKeyLines",
//               Added method "GetKeyNames"
//               Added parameter "bTrimString" to method "GetArray"
//
///////////////////////////////////////////////////////////////////

#ifndef __INI_H__
#define __INI_H__


#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlmisc.h>

#include <vector>
typedef std::vector<CString> StringVector;

// Number bases
#define BASE_BINARY			2
#define BASE_OCTAL			8
#define BASE_DECIMAL		10
#define BASE_HEXADECIMAL	16

//---------------------------------------------------------------
//	    Callback Function Type Definition
//---------------------------------------------------------------
// The callback function used for parsing a "double-null terminated string".
// When called, the 1st parameter passed in will store the newly extracted sub
// string, the 2nd parameter is a 32-bit user defined data, this parameter can
// be NULL. The parsing will terminate if this function returns zero. To use
// the callback, function pointer needs to be passed to "CIni::ParseDNTString".
typedef BOOL (CALLBACK *SUBSTRPROC)(LPCTSTR, LPVOID);

class CIni
{
public:		

	//-----------------------------------------------------------
	//    Constructors
	//-----------------------------------------------------------
	CIni(); // Default constructor
	CIni(LPCTSTR lpPathName); // Construct with a given file name

	//-----------------------------------------------------------
	//    Ini File Path Name Access
	//-----------------------------------------------------------
	void SetPathName(LPCTSTR lpPathName); // Specify a new file name
	DWORD GetPathName(LPTSTR lpBuffer, DWORD dwBufSize) const; // Retrieve current file name
	CString GetPathName() const;
	//------------------------------------------------------------
	//    Raw String Access
	//------------------------------------------------------------	
	DWORD GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDefault = NULL) const;
	CString GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault = NULL) const;
	BOOL WriteString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue) const;

	// Read a string from the ini file, append it with another string then write it
	// back to the ini file.
	BOOL AppendString(LPCTSTR Section, LPCTSTR lpKey, LPCTSTR lpString) const;
	
	//------------------------------------------------------------
	//    Ini File String Array Access
	//------------------------------------------------------------	
	// Parse the string retrieved from the ini file and split it into a set of sub strings.
	DWORD GetArray(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE) const;
	void GetArray(LPCTSTR lpSection, LPCTSTR lpKey, StringVector* pArray, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE) const;
	BOOL WriteArray(LPCTSTR lpSection, LPCTSTR lpKey, const StringVector* pArray, int nWriteCount = -1, LPCTSTR lpDelimiter = NULL) const;
	//------------------------------------------------------------
	//    Primitive Data Type Access
	//------------------------------------------------------------
	int GetInt(LPCTSTR lpSection, LPCTSTR lpKey, int nDefault, int nBase = BASE_DECIMAL) const;
	BOOL WriteInt(LPCTSTR lpSection, LPCTSTR lpKey, int nValue, int nBase = BASE_DECIMAL) const;
	BOOL IncreaseInt(LPCTSTR lpSection, LPCTSTR lpKey, int nIncrease = 1, int nBase = BASE_DECIMAL) const;
	
	UINT GetUInt(LPCTSTR lpSection, LPCTSTR lpKey, UINT nDefault, int nBase = BASE_DECIMAL) const;
	BOOL WriteUInt(LPCTSTR lpSection, LPCTSTR lpKey, UINT nValue, int nBase = BASE_DECIMAL) const;
	BOOL IncreaseUInt(LPCTSTR lpSection, LPCTSTR lpKey, UINT nIncrease = 1, int nBase = BASE_DECIMAL) const;
	
	BOOL GetBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bDefault) const;
	BOOL WriteBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bValue) const;
	BOOL InvertBool(LPCTSTR lpSection, LPCTSTR lpKey) const;
	
	double GetDouble(LPCTSTR lpSection, LPCTSTR lpKey, double fDefault) const;
	BOOL WriteDouble(LPCTSTR lpSection, LPCTSTR lpKey, double fValue, int nPrecision = -1) const;
	BOOL IncreaseDouble(LPCTSTR lpSection, LPCTSTR lpKey, double fIncrease, int nPrecision = -1) const;

	//------------------------------------------------------------
	//    User-Defined Data Type Access
	//------------------------------------------------------------
	POINT GetPoint(LPCTSTR lpSection, LPCTSTR lpKey, POINT ptDefault, int nBase = BASE_DECIMAL) const;
	BOOL WritePoint(LPCTSTR lpSection, LPCTSTR lpKey, POINT pt, int nBase = BASE_DECIMAL) const;
	
	RECT GetRect(LPCTSTR lpSection, LPCTSTR lpKey, RECT rcDefault, int nBase = BASE_DECIMAL) const;
	BOOL WriteRect(LPCTSTR lpSection, LPCTSTR lpKey, RECT rc, int nBase = BASE_DECIMAL) const;
	
	BOOL GetStruct(LPCTSTR lpSection, LPCTSTR lpKey, LPVOID lpData, DWORD dwDataSize) const;
	BOOL WriteStruct(LPCTSTR lpSection, LPCTSTR lpKey, const void* pData, DWORD dwDataSize) const;
	
	//------------------------------------------------------------
	//    Section Operations
	//------------------------------------------------------------
	BOOL IsSectionExist(LPCTSTR lpSection) const;
	DWORD GetSectionNames(LPTSTR lpBuffer, DWORD dwBufSize) const;
	void GetSectionNames(StringVector* pArray) const;
	BOOL CopySection(LPCTSTR lpSrcSection, LPCTSTR lpDestSection, BOOL bFailIfExist) const;
	BOOL MoveSection(LPCTSTR lpSrcSection, LPCTSTR lpDestSection, BOOL bFailIfExist = TRUE) const;
	BOOL DeleteSection(LPCTSTR lpSection) const;
	
	//------------------------------------------------------------
	//    Key Operations
	//------------------------------------------------------------
	BOOL IsKeyExist(LPCTSTR lpSection, LPCTSTR lpKey) const;	
	DWORD GetKeyLines(LPCTSTR lpSection, LPTSTR lpBuffer, DWORD dwBufSize) const;
	void GetKeyLines(LPCTSTR lpSection, StringVector* pArray) const;
	DWORD GetKeyNames(LPCTSTR lpSection, LPTSTR lpBuffer, DWORD dwBufSize) const;
	void GetKeyNames(LPCTSTR lpSection, StringVector* pArray) const;
	BOOL CopyKey(LPCTSTR lpSrcSection, LPCTSTR lpSrcKey, LPCTSTR lpDestSection, LPCTSTR lpDestKey, BOOL bFailIfExist) const;
	BOOL MoveKey(LPCTSTR lpSrcSection, LPCTSTR lpSrcKey, LPCTSTR lpDestSection, LPCTSTR lpDestKey, BOOL bFailIfExist = TRUE) const;
	BOOL DeleteKey(LPCTSTR lpSection, LPCTSTR lpKey) const;

	//------------------------------------------------------------
	// Parse a "Double-Null Terminated String"
	//------------------------------------------------------------
	static BOOL ParseDNTString(LPCTSTR lpString, SUBSTRPROC lpFnStrProc, LPVOID lpParam = NULL);

	//------------------------------------------------------------
	// Check for Whether a String Representing TRUE or FALSE
	//------------------------------------------------------------
	static BOOL StringToBool(LPCTSTR lpString, BOOL bDefault = FALSE);
		
protected:	

	//------------------------------------------------------------
	//    Helper Functions
	//------------------------------------------------------------
	static LPTSTR __StrDupEx(LPCTSTR lpStart, LPCTSTR lpEnd);
	static BOOL __TrimString(LPTSTR lpBuffer);
	LPTSTR __GetStringDynamic(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault = NULL) const;
	static DWORD __StringSplit(LPCTSTR lpString, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE);
	static void __ToBinaryString(UINT nNumber, LPTSTR lpBuffer, DWORD dwBufSize);
	static int __ValidateBase(int nBase);
	static void __IntToString(int nNumber, LPTSTR lpBuffer, int nBase);
	static void __UIntToString(UINT nNumber, LPTSTR lpBuffer, int nBase);
	static BOOL CALLBACK __SubStrCompare(LPCTSTR lpString1, LPVOID lpParam);
	static BOOL CALLBACK __KeyPairProc(LPCTSTR lpString, LPVOID lpParam);	
	static BOOL CALLBACK __SubStrAdd(LPCTSTR lpString, LPVOID lpParam);

	//------------------------------------------------------------
	//    Member Data
	//------------------------------------------------------------
	TCHAR m_szPathName[MAX_PATH + 1]; // Stores path of the associated ini file
};

#endif // #ifndef __INI_H__