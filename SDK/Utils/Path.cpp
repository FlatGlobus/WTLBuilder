//////////////////////////////////////////////////////////////////////
//	Implemented by Samuel Gonzalo 
//
//	You may freely use or modify this code 
//////////////////////////////////////////////////////////////////////
//
// Path.cpp: implementation of the CPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Path.h"
#include "Shlwapi.h"
#include <direct.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPath::CPath()
{
	_bIsRelative = FALSE;
}

CPath::CPath(LPCTSTR szPath, BOOL bIsFolderPath)
{
	SetPath(szPath, bIsFolderPath);
}

CPath::~CPath()
{

}

void CPath::SetPath(LPCTSTR szPath, BOOL bIsFolderPath)
{
	char szParamPath[_MAX_PATH];
	char szDrive[_MAX_DRIVE], szDir[_MAX_DIR];
	char szName[_MAX_FNAME], szExt[_MAX_EXT];

	// Reset
	_sOriginalPath.Empty();
	_sDriveLabel.Empty();
	_bIsRelative = FALSE;
	_aDir.RemoveAll();
	_sExtName.Empty();

	// Original path
	_sOriginalPath = szPath;

	// Get args and remove them from path
	szParamPath[0] = 0x0;
	strcpy(szParamPath, szPath);

	PathUnquoteSpaces(szParamPath);
	if (szParamPath[0] == 0x0) return;

	_splitpath(szParamPath, szDrive, szDir, szName, szExt);

	// Drive
	_sDrive = szDrive;

	// Directory
	_sDir = szDir;
	_sDir.Replace('/', '\\');
	if (!_sDir.IsEmpty()) _bIsRelative = (_sDir[0] != '\\');
	
	// FileTitle
	if (bIsFolderPath)
	{
		_sDir = CPath::AddBackSlash(_sDir);
		_sDir += szName;
		_sDir = CPath::AddBackSlash(_sDir);
	}
	else
	{
		_sFileTitle = szName;
	}

	// Get extension name (e.g.: "txt")
	if (IsFilePath())
	{
		_sExtName = szExt;
		_sExtName.Remove('.');
	}
}

BOOL CPath::IsLocalPath()
{
	return !_sDrive.IsEmpty() && !_bIsRelative;
}

BOOL CPath::IsRelativePath()
{
	return _bIsRelative;
}

BOOL CPath::IsFilePath()
{
	return !_sFileTitle.IsEmpty();
}

BOOL CPath::ExistFile()
{
	if (!IsFilePath()) return FALSE;

	return PathFileExists(GetPath());
}

BOOL CPath::ExistLocation()
{
	return PathFileExists(GetLocation());
}

CString CPath::GetAbsolutePath(LPCTSTR szBaseFolder)
{
	if (!IsRelativePath()) return sCEmptyString;

	char	szAbsolutePath[_MAX_PATH];
	CString sFullPath(szBaseFolder);

	if (sFullPath.IsEmpty()) return sCEmptyString;

	sFullPath = CPath::AddBackSlash(sFullPath);
	sFullPath += GetPath();

	if (!PathCanonicalize(szAbsolutePath, sFullPath)) return sCEmptyString;

	return szAbsolutePath;
}

CString CPath::GetRelativePath(LPCTSTR szBaseFolder)
{
	if (IsRelativePath()) return sCEmptyString;

	char	szRelativePath[_MAX_PATH];
	CString	sRelPath;

	PathRelativePathTo(szRelativePath, szBaseFolder, FILE_ATTRIBUTE_DIRECTORY, 
					GetPath(), IsFilePath() ? 0 : FILE_ATTRIBUTE_DIRECTORY);

	sRelPath = szRelativePath;
	if (sRelPath.GetLength() > 1)
	{
		// Remove ".\" from the beginning
		if ((sRelPath[0] == '.') && (sRelPath[1] == '\\'))
			sRelPath.Right(sRelPath.GetLength() - 2);
	}

	return sRelPath;
}

CString CPath::GetPath(BOOL bOriginal)
{
	CString sPath;

	if (bOriginal)
		sPath = _sOriginalPath;
	else
		sPath = GetLocation() + GetFileName();

	return sPath;
}

CString	CPath::GetShortPath()
{
	char szShortPath[_MAX_PATH];
	szShortPath[0] = 0x0;

	GetShortPathName(GetPath(), szShortPath, _MAX_PATH);

	return szShortPath;
}

CString	CPath::GetLongPath()
{
	char szLongPath[_MAX_PATH];
	szLongPath[0] = 0x0;

	GetLongPathName(GetPath(), szLongPath, _MAX_PATH);

	return szLongPath;
}

CString CPath::GetDrive()
{
	return _sDrive;
}

CString	CPath::GetDriveLabel(BOOL bPCNameIfNetwork)
{
	if (_sDriveLabel.IsEmpty() && !IsRelativePath())
	{
		if ((bPCNameIfNetwork) && (!IsLocalPath()))
			_sDriveLabel = GetDir(0);
		else
		{
			CString sRoot;
			char	szVolumeName[256];

			szVolumeName[0] = '\0';
			if (IsLocalPath())
			{
				sRoot = _sDrive + CString("\\");
			}
			else if (GetDirCount() > 1)
			{
				sRoot.Format("\\\\%s\\%s\\", GetDir(0), GetDir(1));
			}

			GetVolumeInformation(sRoot, szVolumeName, 255, NULL, NULL, NULL, NULL, 0);

			_sDriveLabel = szVolumeName;
		}
	}

	return _sDriveLabel;
}

int	CPath::GetDirCount()
{
	FillDirArray();
	return _aDir.GetSize();
}

CString CPath::GetDir(int nIndex)
{
	if (nIndex < 0)
		return _sDir;
	else if (nIndex < GetDirCount())
	{
		FillDirArray();
		return _aDir[nIndex];
	}

	return sCEmptyString;
}

CString	CPath::GetLocation()
{
	return _sDrive + GetDir();
}

CString CPath::GetTitle()
{
	return _sFileTitle;
}

void CPath::SetTitle(CString val)
{
    _sFileTitle = val;
}

CString CPath::GetFileName()
{
    return _sFileTitle.IsEmpty() == TRUE ? _T("") :_sFileTitle+ _T(".")+GetExt();
}

CString CPath::GetExt()
{
	return _sExtName;
}

void	CPath::SetExt(CString val)
{
    _sExtName = val;
}

BOOL CPath::GetFileSize(__int64 &nSize)
{
	BOOL bResult;

	bResult = FillFileInfoStruct();
	nSize = ((__int64)_fis.nFileSizeHigh * (__int64)MAXDWORD) + (__int64)_fis.nFileSizeLow;
	return bResult;
}

BOOL CPath::GetFileTime(CTime &time, DWORD dwType)
{
	BOOL bResult;
	FILETIME *pTime = NULL;

	bResult = FillFileInfoStruct();
	switch (dwType)
	{
	case FILE_CREATION:	pTime = &_fis.ftCreationTime;	break;
	case FILE_WRITE:	pTime = &_fis.ftLastWriteTime;	break;
	case FILE_ACCESS:	
	default:			pTime = &_fis.ftLastAccessTime;	break;
	}

	if (pTime != NULL) time = CTime(*pTime);
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Private methods

// This function must be called whenever _aDir array is needed, since this
// method is the one which parses _sDir and fill _aDir
void CPath::FillDirArray()
{
	if (_sDir.IsEmpty() || (_aDir.GetSize() > 0)) return;

	int nFrom, nTo;

	// nFrom: 0 - relative / 1 - local / 2 - network
	nFrom = IsLocalPath() ? 1 : (IsRelativePath() ? 0 : 2);

	while ((nTo = _sDir.Find('\\', nFrom)) != -1)
	{
		_aDir.Add(_sDir.Mid(nFrom, nTo - nFrom));
		nFrom = nTo + 1;
	}
}

BOOL CPath::FillFileInfoStruct()
{
	HANDLE	hFile;
	BOOL	bResult;

	::memset(&_fis, 0, sizeof(_fis));

	hFile = CreateFile(GetPath(), GENERIC_READ, FILE_SHARE_READ, NULL, 
						OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN |
						FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	bResult = GetFileInformationByHandle(hFile, &_fis);

	CloseHandle(hFile);

	return bResult;
}

CString CPath::AddBackSlash(LPCTSTR szFolderPath, BOOL bInverted)
{
	CString	sResult(szFolderPath);
	int		nLastChar = sResult.GetLength() - 1;

	if (nLastChar >= 0)
	{
		if ((sResult[nLastChar] != '\\') && (sResult[nLastChar] != '/'))
			sResult += bInverted ? '/' : '\\';
	}

	return sResult;
}

CString CPath::RemoveBackSlash(LPCTSTR szFolderPath)
{
	CString	sResult(szFolderPath);
	int		nLastChar = sResult.GetLength() - 1;

	if (nLastChar >= 0)
	{
		if ((sResult[nLastChar] == '\\') || (sResult[nLastChar] == '/'))
			sResult = sResult.Left(nLastChar);
	}

	return sResult;
}

CPath::operator LPCTSTR ()
{
	_sLPCTSTRPath = GetPath();
	return _sLPCTSTRPath;
}

const CPath& CPath::operator = (LPCTSTR szPath)
{
	SetPath(szPath);
	return *this;
}

const CPath& CPath::operator = (CPath &ref)
{
	_aDir.RemoveAll();
	_aDir=ref._aDir;
	
	_bIsRelative = ref._bIsRelative;

	_fis = ref._fis;

	_sDir = ref._sDir;
	_sDrive = ref._sDrive;
	_sDriveLabel = ref._sDriveLabel;
	_sExtName = ref._sExtName;
	_sFileTitle = ref._sFileTitle;
	_sOriginalPath = ref._sOriginalPath;
	return *this;
}

BOOL IsDots(WIN32_FIND_DATA * pFindData)
{
    BOOL bResult = FALSE;
    if (pFindData != NULL && pFindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        if (pFindData->cFileName[0] == '.')
        {
            if (pFindData->cFileName[1] == '\0' ||
                (pFindData->cFileName[1] == '.' &&
                pFindData->cFileName[2] == '\0'))
            {
                bResult = TRUE;
            }
        }
    }
    return bResult;
}

BOOL CPath::GetAllFilesFromFolder(CString strSourceFolder, BOOL bRecursively, CStringArray &strList,LPCTSTR ext)
{
    strSourceFolder=AddBackSlash(strSourceFolder);

    CString strExt(ext== NULL ? _T("*.*") : ext);
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = FindFirstFile((strSourceFolder + strExt), &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return FALSE;
    do
    {
        if(IsDots(&FindFileData))
            continue;

        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(bRecursively)
                GetAllFilesFromFolder(CString(strSourceFolder + FindFileData.cFileName + _T("\\")), bRecursively, strList);
        }
        else
            strList.Add(strSourceFolder + FindFileData.cFileName);
    }
    while (FindNextFile(hFind, &FindFileData));
    FindClose(hFind);
    return strList.GetSize()!=0;
}

CString CPath::GetAppPath()
{
    return CPath(GetAppName()).GetLocation();
}

CString CPath::GetAppName()
{
    TCHAR file[_MAX_PATH]; 
    ::GetModuleFileName(NULL, file, _MAX_PATH);
    return file;
}

void CPath::AddDir(CString val)
{
    _sDir = AddBackSlash(_sDir);
    _sDir +=val;
    _sDir = AddBackSlash(_sDir);
}

void CPath::SetCurDir()
{
    _tchdir(GetLocation());
}

void CPath::Empty()
{
    _sOriginalPath.Empty();
    _sDrive.Empty();
    _sDriveLabel.Empty();
    _aDir.RemoveAll();
    _sDir.Empty();
    _sFileTitle.Empty();
    _sExtName.Empty();
    _sLPCTSTRPath.Empty();
}