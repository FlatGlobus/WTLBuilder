#ifndef __CFILE_H
#define __CFILE_H
//////////////////////////////////////////////////////////////////////////
#include <fcntl.h> // filecontrol : _O_RDONLY symbol and other stuff
#include <tchar.h> // _fgetts ==> fgets
#include <stdio.h>
#include <io.h>

class CFile
{
	// Members
protected:
	//UINT		m_hFile; // handle to actual file (created by ::CreateFile WIN32 API)
	HANDLE		m_hFile; // handle to actual file (created by ::CreateFile WIN32 API)
	BOOL		m_bCloseOnDelete;
	CString		m_strFileName;


public:
// Flag values
	enum OpenFlags {
		modeRead =          0x0000,
		modeWrite =         0x0001,
		modeReadWrite =     0x0002,
		shareCompat =       0x0000,
		shareExclusive =    0x0010,
		shareDenyWrite =    0x0020,
		shareDenyRead =     0x0030,
		shareDenyNone =     0x0040,
		modeNoInherit =     0x0080,
		modeCreate =        0x1000,
		modeNoTruncate =    0x2000,
		typeText =          0x4000, // typeText and typeBinary are used in
		typeBinary =   (int)0x8000 // derived classes only
		};

	enum SeekPosition { 
		begin = 0x0, 
		current = 0x1, 
		end = 0x2 };

	// Constructor/Destructor
public:
	CFile()
	{
		m_hFile = INVALID_HANDLE_VALUE;
		m_bCloseOnDelete = FALSE;
	}
	~CFile()
	{
		if (m_hFile != INVALID_HANDLE_VALUE && m_bCloseOnDelete)
			Close();
	}

	// Methods
public:
	BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags)
	{
		// CFile objects are always binary and CreateFile does not need flag
		nOpenFlags &= ~(UINT)typeBinary;

		m_bCloseOnDelete = FALSE;
		m_hFile = INVALID_HANDLE_VALUE;
		m_strFileName.Empty();

		// map read/write mode
		DWORD dwAccess = 0;
		switch (nOpenFlags & 3)
		{
			case modeRead:
				dwAccess = GENERIC_READ;
				break;
			case modeWrite:
				dwAccess = GENERIC_WRITE;
				break;
			case modeReadWrite:
				dwAccess = GENERIC_READ|GENERIC_WRITE;
				break;
			default:
				;  // invalid share mode
		}

		// map share mode
		DWORD dwShareMode = 0;
		switch (nOpenFlags & 0x70)    // map compatibility mode to exclusive
		{
			default:
				;  // invalid share mode?
			case shareCompat:
			case shareExclusive:
				dwShareMode = 0;
				break;
			case shareDenyWrite:
				dwShareMode = FILE_SHARE_READ;
				break;
			case shareDenyRead:
				dwShareMode = FILE_SHARE_WRITE;
				break;
			case shareDenyNone:
				dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
				break;
		}

		// map modeNoInherit flag
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;

		// map creation flags
		DWORD dwCreateFlag;
		if (nOpenFlags & modeCreate)
		{
			if (nOpenFlags & modeNoTruncate)
				dwCreateFlag = OPEN_ALWAYS;
			else
				dwCreateFlag = CREATE_ALWAYS;
		}
		else
			dwCreateFlag = OPEN_EXISTING;

		// attempt file creation
		HANDLE hFile = ::CreateFile(lpszFileName, dwAccess, dwShareMode, &sa,
			dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return FALSE;

		m_hFile = hFile;
		m_bCloseOnDelete = TRUE;

		return TRUE;
	}

	LONG Seek( LONG lOff, UINT nFrom )
	{
		if (m_hFile == INVALID_HANDLE_VALUE)	return 0;

		return 	::SetFilePointer(m_hFile, lOff, NULL, (DWORD)nFrom);
	}

	DWORD SeekToEnd()
	{
		return Seek(0, CFile::end);
	}


	UINT Read(void* lpBuf, UINT nCount)
	{
		if (nCount == 0) return 0;   // avoid Win32 "null-read"

		DWORD dwRead = 0;
		
		::ReadFile(m_hFile, lpBuf, nCount, &dwRead, NULL);

		return (UINT)dwRead;
	}

	BOOL ReadEntireFile(/*out*/CString &szContent)
	{
		szContent.Empty();

		char buf[4096+1];
        memset(buf,0,(4096+1)*sizeof(char));
		UINT nRead;
		while ( (nRead=Read(buf,4096)) > 0 )
		{
			buf[nRead]='\0'; 
			szContent += buf;
		}

		return szContent.GetLength()>0;
	}

	void Write( const void* lpBuf, UINT nCount )
	{
		if (m_hFile == INVALID_HANDLE_VALUE)	return;

		if (nCount == 0)
			return;     // avoid Win32 "null-write" option

		DWORD nWritten;
	    ::WriteFile(m_hFile, lpBuf, nCount, &nWritten, NULL);
	}

	void Write(CString &s)
	{
		if (!s.IsEmpty())
#ifndef _UNICODE
			Write((LPCTSTR)s, s.GetLength());
#else
            Wr  ite(s, s.GetLength());
#endif
	}

	void Flush()
	{
		if (m_hFile == INVALID_HANDLE_VALUE)	return;

		::FlushFileBuffers(m_hFile);
	}

	void Close()
	{
		if (m_hFile != INVALID_HANDLE_VALUE)
			::CloseHandle(m_hFile);

		m_hFile = INVALID_HANDLE_VALUE;
		m_bCloseOnDelete = FALSE;
		m_strFileName.Empty();
	}
};
	inline CFile & operator<<(CFile & file,_TCHAR& val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}

	inline CFile & operator<<(CFile & file,LPTSTR val)
	{
		short len=0;
		if(val==NULL)
		{
			file.Write(&len,sizeof(len));
		}
		else
		{
            len=(short)_tcslen(val);
			file.Write(&len,sizeof(len));
			file.Write(val,len);
		}
		return file;
	}

	inline CFile & operator<<(CFile & file,short& val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}

	inline CFile & operator<<(CFile & file,int &val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}

	inline CFile & operator<<(CFile & file,long &val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}
	inline CFile & operator<<(CFile & file,float &val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}
	inline CFile & operator<<(CFile & file,double& val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}
	inline CFile & operator<<(CFile & file,CString & val)
	{
		short len=val.GetLength();
		file.Write(&len,sizeof(len));
        if(len)
			file.Write((LPCTSTR)val,len);
		return file;
	}

	inline CFile & operator>>(CFile & file,_TCHAR &val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}

	inline CFile & operator>>(CFile & file,LPTSTR& val)
	{
		short len=0;
		file.Read(&len,sizeof(len));
		if(len)
		{
			if(val!=NULL)
				delete [] val;
            val=new _TCHAR [len+1];
			file.Read(val,len);
			val[len]=0;
		}
		return file;
	}

	inline CFile & operator>>(CFile & file,short & val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}

	inline CFile & operator>>(CFile & file,int & val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}
	inline CFile & operator>>(CFile & file,long &val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}
	inline CFile & operator>>(CFile & file,float &val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}
	inline CFile & operator>>(CFile & file,double &val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}
	inline CFile & operator>>(CFile & file,CString & val)
	{
		short len=0;
		file.Read(&len,sizeof(len));
		if(len)
		{
			LPTSTR temp=new _TCHAR[len+1];
			file.Read(temp,len);
			temp[len]=0;
			val=temp;
			delete [] temp;
		}
		return file;
	}

inline CFile & operator<<(CFile & file,COLORREF val)
	{
		file.Write(&val,sizeof(val));
		return file;
	}

inline CFile & operator>>(CFile & file,COLORREF &val)
	{
		file.Read(&val,sizeof(val));
		return file;
	}

class CStdioFile : public CFile
{
	// Members
protected:
	FILE*		m_pStream;

	// Constructor/Destructor
public:

	CStdioFile()
	{
		m_pStream = NULL;
	}

	~CStdioFile()
	{
		if (m_pStream != NULL && m_bCloseOnDelete)
			Close();
	}


	// Methods
public:
	BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags)
	{
		m_pStream = NULL;

		if (!CFile::Open(lpszFileName, (nOpenFlags & ~typeText)))
			return FALSE;

		_TCHAR szMode[4]; // C-runtime open string
		int nMode = 0;

		// determine read/write mode depending on CFile mode
		if (nOpenFlags & modeCreate)
		{
			if (nOpenFlags & modeNoTruncate)
				szMode[nMode++] = _T('a');
			else
				szMode[nMode++] = _T('w');
		}
		else if (nOpenFlags & modeWrite)
			szMode[nMode++] = _T('a');
		else
			szMode[nMode++] = _T('r');

		// add '+' if necessary (when read/write modes mismatched)
		if (szMode[0] == _T('r') && (nOpenFlags & modeReadWrite) ||
			szMode[0] != _T('r') && !(nOpenFlags & modeWrite))
		{
			// current szMode mismatched, need to add '+' to fix
			szMode[nMode++] = _T('+');
		}

		// will be inverted if not necessary
		int nFlags = _O_RDONLY|_O_TEXT;
		if (nOpenFlags & (modeWrite|modeReadWrite))
			nFlags ^= _O_RDONLY;

		if (nOpenFlags & typeBinary)
			szMode[nMode++] = _T('b'), nFlags ^= _O_TEXT;
		else
			szMode[nMode++] = _T('t');
		szMode[nMode++] = _T('\0');

		// open a C-runtime low-level file handle
		int nHandle = _open_osfhandle((intptr_t)m_hFile, nFlags);

		// open a C-runtime stream from that handle
		if (nHandle != -1)
            m_pStream = _tfdopen(nHandle, szMode);

		if (m_pStream == NULL)
		{
			return FALSE;
		}

		return TRUE;
	}


	BOOL ReadString(CString& rString)
	{
		rString.Empty();

		const int nMaxSize = 256;
		_TCHAR lpsz[nMaxSize+1];
		LPTSTR lpszResult;
		size_t nLen = 0;
		for (;;)
		{
			lpsz[0]=_T('\0');

			lpszResult = _fgetts(lpsz, nMaxSize+1, m_pStream);

			// handle error/eof case
			if (lpszResult == NULL && !feof(m_pStream))
			{
				break;
			}

            nLen = _tcslen(lpsz);
			rString += lpsz;

			// if string is read completely or EOF
			if (lpszResult == NULL ||
				nLen<nMaxSize ||
				lpsz[nLen-1] == _T('\n'))
				break;
			
		}

		// remove '\n' from end of string if present
		nLen = rString.GetLength();
		if (nLen != 0 && rString.GetAt((int)nLen-1) == _T('\n'))
			rString.SetAt((int)nLen-1,_T('\0'));

		return (lpszResult != NULL);
	}

	void Close()
	{
		int nErr = 0;

		if (m_pStream != NULL)
			nErr = fclose(m_pStream);

		m_hFile = INVALID_HANDLE_VALUE;
		m_bCloseOnDelete = FALSE;
		m_pStream = NULL;
	}
};
//////////////////////////////////////////////////////////////////////////
CString LoadString(const CString & fileName);
BOOL SaveString(const CString & fileName,CString &source);
//////////////////////////////////////////////////////////////////////////
#endif