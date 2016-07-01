// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "property.h"
#include <DOMxml.h>
//#include "Component.h"
//////////////////////////////////////////////////////////////////////////
BOOL PROPERTY_API PreReadForm(const CString &fn,CString &page,CString &cmpName)
{
	try
	{
		CXMLDOMDocument2	Doc;
		//Doc = CDOMDocument40Class::CreateXMLDOMDocument2();
        Doc = CDOMDocument30Class::CreateXMLDOMDocument2();
		if(Doc.Load((LPCTSTR)fn)==FALSE)
			return FALSE;
		CXMLDOMNode formNode(Doc.SelectSingleNode(_T("Form")));
		if(formNode==NULL)
			return FALSE;
		cmpName=formNode.GetAttributes().GetNamedItem(_T("Class")).GetText();
		page=formNode.GetAttributes().GetNamedItem(_T("Page")).GetText();
	}
	catch (CComException *pE)
	{
		pE->Delete();
		return FALSE;
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}