#include "stdafx.h"
//////////////////////////////////////////////////////////////////////////
#define BUFF_SIZE 4096
CString LoadString(const CString & fileName)
{
	CString str;
	FILE *file = NULL;
	if (file = fopen(fileName, "rt"))
	{
		char buf[BUFF_SIZE + 1];
		memset(buf, 0, (BUFF_SIZE + 1) * sizeof(char));
		UINT nRead;
		while ((nRead = fread(buf, 1, BUFF_SIZE, file)) > 0)
		{
			buf[nRead] = '\0';
			str += buf;
		}
		fclose(file);
	}
	return str;
}

BOOL SaveString(const CString & fileName,CString &source)
{
	FILE *file=NULL;
	if(file = fopen(fileName,"wt"))
	{
		if (!source.IsEmpty())
		{
			fwrite((LPCTSTR)source, 1, source.GetLength(), file);
		}
		fclose(file);
		return TRUE;
	}
	return FALSE;
}