#pragma once
//////////////////////////////////////////////////////////////////////////
#include "ini.h"

class CConfig
{
    CIni cfgFile;
public:
    CConfig();
    ~CConfig();

    void LoadConfig();
    void SaveConfig();

    void SetBOOLValue(LPCTSTR section, LPCTSTR key, BOOL val);
    void GetBOOLValue(LPCTSTR section, LPCTSTR key, BOOL *val);

    void SetINTValue(LPCTSTR section, LPCTSTR key, int val);
    void GetINTValue(LPCTSTR section, LPCTSTR key, int *val);

    void SetSTRTValue(LPCTSTR section, LPCTSTR key, LPCTSTR val);
    void GetSTRValue(LPCTSTR section, LPCTSTR key, LPTSTR val, int sz);
};
//////////////////////////////////////////////////////////////////////////
