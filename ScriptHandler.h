#ifndef __SCRIPTHANDLER_H
#define __SCRIPTHANDLER_H

#include "atldispa.h"
#include "atlscript.h"
#include <map>
#include <vector>
#include "path.h"
#include "ScriptError.h"
#include <string>

#define DEF_SCRIPT_EXT _T("*.js")
#define LANG_ENGLISH_NEUTRAL (MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL))
#define LOCALE_SCRIPT_DEFAULT (MAKELCID(LANG_ENGLISH_NEUTRAL, SORT_DEFAULT))

using namespace std;
//////////////////////////////////////////////////////////////////////////
class str_lower : public binary_function<std::wstring, std::wstring, bool> {
public:
	bool operator()(const std::wstring& x, const std::wstring& y) const
	{
		//return (x.compare( y.c_str() ) < 0);
        return (x.compare(y) < 0);
	}
};

class CScriptlet 
{
	wstring file;
	wstring code;
public:
	CScriptlet()
	{
	}

	CScriptlet(BSTR _file,BSTR _code):file(_file),code(_code)
	{
	}
	
	CComBSTR getCode()
	{
		return CComBSTR(code.c_str());
	}

	CComBSTR getFile()
	{
		return CComBSTR(file.c_str());
	}
};

typedef map<wstring, LPUNKNOWN, str_lower> IUnknownPtrMap;
typedef vector<CScriptError *> CScriptErrorVector;
typedef vector<CScriptlet> CScriptletVector;

class ATL_NO_VTABLE CScriptHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IActiveScriptSiteImpl<CScriptHandler>,
	public IActiveScriptSiteWindowImpl<CScriptHandler>
{
	IUnknownPtrMap m_mapNamedItems;
	CScriptErrorVector errors;
	CScriptletVector scriplets;
	CString scriptsDir;
	size_t currScriplet;
	CString calledFunc;
public:

	HWND m_hWnd;

	CScriptHandler()
	{
		RegisterEvent(evInvokeFunc,this,&CScriptHandler::Execute);	
	}

	~CScriptHandler()
	{
		UnRegisterEvent(this);
	}

	void Init(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	BOOL Execute(LPCWSTR pstrFunc,VARIANT* Params, LONG Count, VARIANT* RetValue,BOOL * retFlag)
	{
		calledFunc = pstrFunc;
		*retFlag=TRUE;
		if( ::lstrlenW(pstrFunc) == 0 )
			return *retFlag=FALSE;
		
		errors.clear();

		CComPtr<IActiveScript> spScript;
		HRESULT Hr = spScript.CoCreateInstance(L"jscript");
		if( FAILED(Hr) ) {
			AtlMessageBox(m_hWnd, _T("Missing JS Script Interpreter?"), _T("Script Parse Error"), MB_ICONERROR);
			return *retFlag=FALSE; 
		}

		CComQIPtr<IActiveScriptSite> spPass = this;
		if( spPass == NULL )
			return *retFlag=FALSE;

		Hr = spScript->SetScriptSite(spPass);
		if( FAILED(Hr) )
			return *retFlag=FALSE;

		CComQIPtr<IActiveScriptParse> spParse = spScript;
		if( spParse == NULL )
			return *retFlag=FALSE;

		spParse->InitNew();

		for(IUnknownPtrMap::iterator iter=m_mapNamedItems.begin();iter!=m_mapNamedItems.end(); iter++)
		{
			if( FAILED( spScript->AddNamedItem(iter->first.c_str(), SCRIPTITEM_ISVISIBLE | SCRIPTITEM_GLOBALMEMBERS) ) )
				return *retFlag=FALSE;
		}

		if(scriplets.size() == 0 && scriptsDir.IsEmpty() == FALSE)
		{
			if(LoadScriptsFromDir(scriptsDir) == FALSE)
				return *retFlag=FALSE;
		}

		for(currScriplet = 0; currScriplet < scriplets.size(); currScriplet++)
		{
			EXCEPINFO ei = { 0 };
			if(FAILED(spParse->ParseScriptText(scriplets[currScriplet].getCode(), 0, 0, 0, 0, 0, 
				SCRIPTTEXT_ISPERSISTENT|SCRIPTTEXT_ISVISIBLE,0, &ei)))
				return *retFlag=FALSE;
		}

		// Start the scripting engine...
		m_spIActiveScript = spScript;
		Hr = spScript->SetScriptState(SCRIPTSTATE_STARTED);
		if(FAILED(Hr))
			return *retFlag=FALSE;

		// Run the script...
		CComBSTR bstrScript = pstrFunc;
		DISPID dispid=0;
		LPDISPATCH pDisp = NULL;
		DISPPARAMS dispparams = { Params, NULL, Count, 0};

		Hr = spScript->GetScriptDispatch(0, &pDisp);
		if (SUCCEEDED(Hr))
			Hr = pDisp->GetIDsOfNames(IID_NULL, (LPOLESTR*)&bstrScript, 1, LOCALE_SCRIPT_DEFAULT, &dispid);
		if (SUCCEEDED(Hr))
		{
			Hr = pDisp->Invoke(dispid, IID_NULL, LOCALE_SCRIPT_DEFAULT, DISPATCH_METHOD, &dispparams, RetValue, NULL, NULL);
			pDisp->Release();
			*retFlag = TRUE;
		}
		else
		{
			//called function doesn't exist
			*retFlag = FALSE;
		}

		spScript->SetScriptState(SCRIPTSTATE_CLOSED);

		return *retFlag;
	}

	void AddScriptItem(BSTR pstrNamedItem, LPUNKNOWN lpUnknown)
	{
		if (lpUnknown != NULL)
		{
			wstring sNamedItem = pstrNamedItem;
			m_mapNamedItems.insert(IUnknownPtrMap::value_type(sNamedItem,lpUnknown) );
		}
	}

	BOOL AddScriptFromFile(LPCSTR fileName)
	{
		USES_CONVERSION;
		BOOL bRet = LoadScriptFromFile(CComBSTR(fileName));
		if(bRet==FALSE)
		{
			LPCTSTR lpText = fileName;
			for(size_t i =0; i < errors.size(); i++)
			{
				errors[i]->SetFile(lpText);
			//	SendEvent(evScriptError,GetError(i));
			}
			errors.clear();
		}
		return bRet;
	}

	BOOL LoadScriptFromFile(BSTR fileName)
	{
		WCHAR * code=ReadTextFileHelper(fileName);
		BOOL ret=FALSE;
		if(code)
		{
			scriplets.push_back(CScriptlet(fileName,code));
			DestroyDataHelper(code);
		}
		return ret;
	}

	void AddScript(BSTR code)
	{
		scriplets.push_back(CScriptlet(NULL,code));
	}

	WCHAR*	ReadTextFileHelper(LPCOLESTR strFileName)
	{
		WCHAR *pwszResult = NULL;
		CHAR szFileNameA[MAX_PATH];
		if (wcstombs(szFileNameA, strFileName, MAX_PATH) == -1)
			return pwszResult;

		HANDLE hfile = CreateFileA(szFileNameA, GENERIC_READ,
			FILE_SHARE_READ, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, 0);
		if (hfile != INVALID_HANDLE_VALUE)
		{
			DWORD cch = GetFileSize(hfile, 0);
			LPVOID psz = (LPVOID)CoTaskMemAlloc(cch + 1);

			if (psz)
			{
				DWORD cb;
				ReadFile(hfile, psz, cch, &cb, 0);
				pwszResult = (WCHAR*)CoTaskMemAlloc((cch + 1)*sizeof(WCHAR));
				if (pwszResult)
					mbstowcs(pwszResult, (const char *)psz, cch + 1);
				pwszResult[cch] = 0;
				CoTaskMemFree(psz);
			}
			CloseHandle(hfile);
		}
		return pwszResult;
	}

	void DestroyDataHelper(LPVOID lpvData)
	{
		CoTaskMemFree(lpvData);
	}

	BOOL LoadScriptsFromDir(LPCSTR dir)
	{
		if(scriptsDir.IsEmpty())
			scriptsDir = dir;
		CString path=CPath::GetAppPath()+dir;
		CStringArray scriptList;
		CPath::GetAllFilesFromFolder(path,TRUE,scriptList,DEF_SCRIPT_EXT);

		if(scriptList.GetSize()==0)
			return FALSE;

		for(int i= 0; i < (int)scriptList.GetSize();i++)
			LoadScriptFromFile(CComBSTR((LPCSTR)scriptList[i]));

		return TRUE;
	}

	BEGIN_COM_MAP(CScriptHandler)
		COM_INTERFACE_ENTRY(IActiveScriptSite)
		COM_INTERFACE_ENTRY(IActiveScriptSiteWindow)
	END_COM_MAP()

	STDMETHOD(GetItemInfo)(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown** ppUnk, ITypeInfo** ppti)
	{
		ATLASSERT(pstrName);
		if( (dwReturnMask & SCRIPTINFO_ITYPEINFO) != 0 ) {
			*ppti = NULL;
			return E_FAIL;
		}
		if( (dwReturnMask & SCRIPTINFO_IUNKNOWN) == 0 ) return E_FAIL;
		if( ppUnk == NULL ) return E_POINTER;
		*ppUnk = NULL;

		wstring sNamedItem = pstrName;
		IUnknownPtrMap::iterator iter = m_mapNamedItems.find( sNamedItem );
		if ( iter != m_mapNamedItems.end())
			*ppUnk = (*iter).second;

		return *ppUnk == NULL ? E_FAIL : S_OK;
	}

	STDMETHOD(GetDocVersionString)(BSTR* pbstrVersion)
	{
		if( pbstrVersion == NULL ) return E_POINTER;
		CComBSTR bstr = L"NewFileScript";
		*pbstrVersion = bstr.Detach();
		return S_OK;
	}

	STDMETHOD(OnScriptError)(IActiveScriptError* pse)
	{
		USES_CONVERSION;
		EXCEPINFO e;
		DWORD dwContext;
		ULONG ulLine;
		LONG lPos;
		BSTR text=NULL;
		pse->GetExceptionInfo(&e);
		pse->GetSourcePosition(&dwContext, &ulLine, &lPos);
		pse->GetSourceLineText(&text);
        CString scriptFile = scriplets.size() < currScriplet ? CString(OLE2CT(scriplets[currScriplet].getFile())) : _T("");
		CScriptError *se = new CScriptError(scriptFile,CString(OLE2CT(text)), CString(OLE2CT(e.bstrDescription)), calledFunc, ulLine+2, lPos);
		errors.push_back(se);
		PostEvent(evScriptError,se);
		scriplets.clear();
		return S_OK;
	}
};

#endif