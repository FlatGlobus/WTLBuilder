#include "stdafx.h"
#include "Config.h"
#include "path.h"

static CConfig cfg;

//////////////////////////////////////////////////////////////////////////
CConfig::CConfig()
{
    RegisterEvent(evCfgSetBOOLVal, this, &CConfig::SetBOOLValue);
    RegisterEvent(evCfgGetBOOLVal, this, &CConfig::GetBOOLValue);
    RegisterEvent(evCfgSetINTVal, this, &CConfig::SetINTValue);
    RegisterEvent(evCfgGetINTVal, this, &CConfig::GetINTValue);
    RegisterEvent(evCfgSetSTRVal, this, &CConfig::SetSTRTValue);
    RegisterEvent(evCfgGetSTRVal, this, &CConfig::GetSTRValue);

    CString cfgFileName = CPath::GetAppPath() + _T("wtlbuilder.cfg");
    cfgFile.SetPathName(cfgFileName);
}


CConfig::~CConfig()
{
}

void CConfig::SetBOOLValue(LPCTSTR section, LPCTSTR key, BOOL val)
{
    cfgFile.WriteBool(section, key, val);
}

void CConfig::GetBOOLValue(LPCTSTR section, LPCTSTR key, BOOL *val)
{
    if(val != NULL)
        *val = cfgFile.GetBool(section, key, FALSE);
}

void CConfig::SetINTValue(LPCTSTR section, LPCTSTR key, BOOL val)
{
    cfgFile.WriteInt(section, key, val);
}

void CConfig::GetINTValue(LPCTSTR section, LPCTSTR key, BOOL *val)
{
    if (val != NULL)
        *val = cfgFile.GetInt(section, key, 0);
}

void CConfig::SetSTRTValue(LPCTSTR section, LPCTSTR key, LPCTSTR val)
{
    cfgFile.WriteString(section, key, val);
}

void CConfig::GetSTRValue(LPCTSTR section, LPCTSTR key, LPTSTR val, int sz)
{
    if (val != NULL)
        cfgFile.GetString(section, key, val, sz, "");
}
