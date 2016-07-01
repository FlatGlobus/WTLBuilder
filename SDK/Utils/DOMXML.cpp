/********************************************************************
*
* Copyright (C) 2001 Sven Wiegand
* 
* This file is free software; you can redistribute it and/or
* modify, but leave the headers intact and do not remove any 
* copyrights from the source.
*
* If you have further questions, suggestions or bug fixes, please
* let me know
*
*    sven.wiegand@web.de
*
********************************************************************/

#include "stdafx.h"
#include "DOMXML.h"
#include "InterfaceWrapperTools.h"

static GUID LIBID = {0xf5078f18, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};

//#import "MSXML3.dll" named_guids


#define LIBVER_MAJOR 4
#define LIBVER_MINOR 0

//--------------------------------------------------------------------
// class CXMLDOMDocument
//--------------------------------------------------------------------

CXMLDOMDocument::CXMLDOMDocument()
:	CInterfaceCallingWrapper<IXMLDOMDocument>()
{}


CXMLDOMDocument::CXMLDOMDocument(IXMLDOMDocument *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMDocument>(p, bIncrementRefCount)
{}


CXMLDOMDocument::CXMLDOMDocument(const CXMLDOMDocument &o)
:	CInterfaceCallingWrapper<IXMLDOMDocument>(o)
{}


CString CXMLDOMDocument::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMDocument::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMDocument::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMDocument::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMDocument::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMDocument::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMDocument::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMDocument::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocument::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocument::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMDocument::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMDocument::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMDocument::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMDocument::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMDocument::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMDocument::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMDocument::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocument::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocument::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CXMLDOMDocumentType CXMLDOMDocument::GetDoctype()
{
	IXMLDOMDocumentType* o;

	HRESULT	hr = P()->get_doctype(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMImplementation CXMLDOMDocument::GetImplementation()
{
	IXMLDOMImplementation* o;

	HRESULT	hr = P()->get_implementation(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMElement CXMLDOMDocument::GetDocumentElement()
{
	IXMLDOMElement* o;

	HRESULT	hr = P()->get_documentElement(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument::SetRefDocumentElement(IXMLDOMElement* rhs)
{

	HRESULT	hr = P()->putref_documentElement(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


CXMLDOMElement CXMLDOMDocument::CreateElement(LPCTSTR tagName)
{
	CString	strtagName(tagName);
	BSTR	bstrtagName = strtagName.AllocSysString();
	IXMLDOMElement* o;

	HRESULT	hr = P()->createElement(bstrtagName, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtagName);
	return o;
}


CXMLDOMDocumentFragment CXMLDOMDocument::CreateDocumentFragment()
{
	IXMLDOMDocumentFragment* o;

	HRESULT	hr = P()->createDocumentFragment(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMText CXMLDOMDocument::CreateTextNode(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMText* o;

	HRESULT	hr = P()->createTextNode(bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
	return o;
}


CXMLDOMComment CXMLDOMDocument::CreateComment(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMComment* o;

	HRESULT	hr = P()->createComment(bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
	return o;
}


CXMLDOMCDATASection CXMLDOMDocument::CreateCDATASection(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMCDATASection* o;

	HRESULT	hr = P()->createCDATASection(bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
	return o;
}


CXMLDOMProcessingInstruction CXMLDOMDocument::CreateProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	CString	strtarget(target);
	BSTR	bstrtarget = strtarget.AllocSysString();
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMProcessingInstruction* o;

	HRESULT	hr = P()->createProcessingInstruction(bstrtarget, bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtarget);
	SysFreeString(bstrdata);
	return o;
}


CXMLDOMAttribute CXMLDOMDocument::CreateAttribute(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMAttribute* o;

	HRESULT	hr = P()->createAttribute(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMEntityReference CXMLDOMDocument::CreateEntityReference(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMEntityReference* o;

	HRESULT	hr = P()->createEntityReference(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMNodeList CXMLDOMDocument::GetElementsByTagName(LPCTSTR tagName)
{
	CString	strtagName(tagName);
	BSTR	bstrtagName = strtagName.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->getElementsByTagName(bstrtagName, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtagName);
	return o;
}


CXMLDOMNode CXMLDOMDocument::CreateNode(_variant_t type, LPCTSTR name, LPCTSTR namespaceURI)
{
	VARIANT	vartype = type.Detach();
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->createNode(vartype, bstrname, bstrnamespaceURI, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&vartype);
	SysFreeString(bstrname);
	SysFreeString(bstrnamespaceURI);
	return o;
}


CXMLDOMNode CXMLDOMDocument::NodeFromID(LPCTSTR idString)
{
	CString	stridString(idString);
	BSTR	bstridString = stridString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->nodeFromID(bstridString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstridString);
	return o;
}


BOOL CXMLDOMDocument::Load(_variant_t xmlSource)
{
	VARIANT	varxmlSource = xmlSource.Detach();
	short	o;

	HRESULT	hr = P()->load(varxmlSource, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varxmlSource);
	return o;
}


long CXMLDOMDocument::GetReadyState()
{
	long o;

	HRESULT	hr = P()->get_readyState(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMParseError CXMLDOMDocument::GetParseError()
{
	IXMLDOMParseError* o;

	HRESULT	hr = P()->get_parseError(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocument::GetUrl()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_url(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


BOOL CXMLDOMDocument::GetAsync()
{
	short	o;

	HRESULT	hr = P()->get_async(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument::SetAsync(BOOL rhs)
{

	HRESULT	hr = P()->put_async(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMDocument::Abort()
{

	HRESULT	hr = P()->abort();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CXMLDOMDocument::LoadXML(LPCTSTR bstrXML)
{
	CString	strbstrXML(bstrXML);
	BSTR	bstrbstrXML = strbstrXML.AllocSysString();
	short	o;

	HRESULT	hr = P()->loadXML(bstrbstrXML, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrXML);
	return o;
}


void CXMLDOMDocument::Save(_variant_t destination)
{
	VARIANT	vardestination = destination.Detach();

	HRESULT	hr = P()->save(vardestination);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&vardestination);
}


BOOL CXMLDOMDocument::GetValidateOnParse()
{
	short	o;

	HRESULT	hr = P()->get_validateOnParse(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument::SetValidateOnParse(BOOL rhs)
{

	HRESULT	hr = P()->put_validateOnParse(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CXMLDOMDocument::GetResolveExternals()
{
	short	o;

	HRESULT	hr = P()->get_resolveExternals(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument::SetResolveExternals(BOOL rhs)
{

	HRESULT	hr = P()->put_resolveExternals(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CXMLDOMDocument::GetPreserveWhiteSpace()
{
	short	o;

	HRESULT	hr = P()->get_preserveWhiteSpace(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument::SetPreserveWhiteSpace(BOOL rhs)
{

	HRESULT	hr = P()->put_preserveWhiteSpace(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMDocument::SetOnreadystatechange(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_onreadystatechange(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


void CXMLDOMDocument::SetOndataavailable(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_ondataavailable(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


void CXMLDOMDocument::SetOntransformnode(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_ontransformnode(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}




//--------------------------------------------------------------------
// class CXMLDOMDocument2
//--------------------------------------------------------------------

CXMLDOMDocument2::CXMLDOMDocument2()
:	CInterfaceCallingWrapper<IXMLDOMDocument2>()
{}


CXMLDOMDocument2::CXMLDOMDocument2(IXMLDOMDocument2 *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMDocument2>(p, bIncrementRefCount)
{}


CXMLDOMDocument2::CXMLDOMDocument2(const CXMLDOMDocument2 &o)
:	CInterfaceCallingWrapper<IXMLDOMDocument2>(o)
{}


CString CXMLDOMDocument2::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMDocument2::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument2::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMDocument2::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMDocument2::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMDocument2::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMDocument2::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMDocument2::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMDocument2::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocument2::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument2::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocument2::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMDocument2::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocument2::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMDocument2::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument2::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMDocument2::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument2::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMDocument2::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument2::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMDocument2::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMDocument2::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMDocument2::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocument2::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument2::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocument2::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocument2::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CXMLDOMDocumentType CXMLDOMDocument2::GetDoctype()
{
	IXMLDOMDocumentType* o;

	HRESULT	hr = P()->get_doctype(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMImplementation CXMLDOMDocument2::GetImplementation()
{
	IXMLDOMImplementation* o;

	HRESULT	hr = P()->get_implementation(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMElement CXMLDOMDocument2::GetDocumentElement()
{
	IXMLDOMElement* o;

	HRESULT	hr = P()->get_documentElement(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument2::SetRefDocumentElement(IXMLDOMElement* rhs)
{

	HRESULT	hr = P()->putref_documentElement(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


CXMLDOMElement CXMLDOMDocument2::CreateElement(LPCTSTR tagName)
{
	CString	strtagName(tagName);
	BSTR	bstrtagName = strtagName.AllocSysString();
	IXMLDOMElement* o;

	HRESULT	hr = P()->createElement(bstrtagName, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtagName);
	return o;
}


CXMLDOMDocumentFragment CXMLDOMDocument2::CreateDocumentFragment()
{
	IXMLDOMDocumentFragment* o;

	HRESULT	hr = P()->createDocumentFragment(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMText CXMLDOMDocument2::CreateTextNode(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMText* o;

	HRESULT	hr = P()->createTextNode(bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
	return o;
}


CXMLDOMComment CXMLDOMDocument2::CreateComment(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMComment* o;

	HRESULT	hr = P()->createComment(bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
	return o;
}


CXMLDOMCDATASection CXMLDOMDocument2::CreateCDATASection(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMCDATASection* o;

	HRESULT	hr = P()->createCDATASection(bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
	return o;
}


CXMLDOMProcessingInstruction CXMLDOMDocument2::CreateProcessingInstruction(LPCTSTR target, LPCTSTR data)
{
	CString	strtarget(target);
	BSTR	bstrtarget = strtarget.AllocSysString();
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();
	IXMLDOMProcessingInstruction* o;

	HRESULT	hr = P()->createProcessingInstruction(bstrtarget, bstrdata, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtarget);
	SysFreeString(bstrdata);
	return o;
}


CXMLDOMAttribute CXMLDOMDocument2::CreateAttribute(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMAttribute* o;

	HRESULT	hr = P()->createAttribute(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMEntityReference CXMLDOMDocument2::CreateEntityReference(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMEntityReference* o;

	HRESULT	hr = P()->createEntityReference(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMNodeList CXMLDOMDocument2::GetElementsByTagName(LPCTSTR tagName)
{
	CString	strtagName(tagName);
	BSTR	bstrtagName = strtagName.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->getElementsByTagName(bstrtagName, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtagName);
	return o;
}


CXMLDOMNode CXMLDOMDocument2::CreateNode(_variant_t type, LPCTSTR name, LPCTSTR namespaceURI)
{
	VARIANT	vartype = type.Detach();
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->createNode(vartype, bstrname, bstrnamespaceURI, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&vartype);
	SysFreeString(bstrname);
	SysFreeString(bstrnamespaceURI);
	return o;
}


CXMLDOMNode CXMLDOMDocument2::NodeFromID(LPCTSTR idString)
{
	CString	stridString(idString);
	BSTR	bstridString = stridString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->nodeFromID(bstridString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstridString);
	return o;
}


BOOL CXMLDOMDocument2::Load(_variant_t xmlSource)
{
	VARIANT	varxmlSource = xmlSource.Detach();
	short	o;

	HRESULT	hr = P()->load(varxmlSource, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);
    //IXMLDOMParseError *error;
    //P()->get_parseError(&error);
    //BSTR str;
    //error->get_srcText(&str);
    //long errcode;
    //error->get_errorCode(&errcode);
    //BSTR reason;
    //error->get_reason(&reason);
	VariantClear(&varxmlSource);
	return o;
}


long CXMLDOMDocument2::GetReadyState()
{
	long o;

	HRESULT	hr = P()->get_readyState(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMParseError CXMLDOMDocument2::GetParseError()
{
	IXMLDOMParseError* o;

	HRESULT	hr = P()->get_parseError(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocument2::GetUrl()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_url(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


BOOL CXMLDOMDocument2::GetAsync()
{
	short	o;

	HRESULT	hr = P()->get_async(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument2::SetAsync(BOOL rhs)
{

	HRESULT	hr = P()->put_async(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMDocument2::Abort()
{

	HRESULT	hr = P()->abort();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CXMLDOMDocument2::LoadXML(LPCTSTR bstrXML)
{
	CString	strbstrXML(bstrXML);
	BSTR	bstrbstrXML = strbstrXML.AllocSysString();
	short	o;

	HRESULT	hr = P()->loadXML(bstrbstrXML, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrXML);
	return o;
}


void CXMLDOMDocument2::Save(_variant_t destination)
{
    CComBSTR bstrXML( L"" );
    HRESULT	 hr = P()->get_xml( &bstrXML );
    // вставляем переводы строки
    CString sXml = CW2CT( bstrXML );
    sXml.Replace( _T("><"), _T(">\n<") );
    bstrXML = sXml.GetBuffer( 0 );

    // загружаем взад
    VARIANT_BOOL bSuccess;
    hr = P()->loadXML( bstrXML, &bSuccess );

	VARIANT	vardestination = destination.Detach();

	/*HRESULT*/	hr = P()->save(vardestination);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&vardestination);
}


BOOL CXMLDOMDocument2::GetValidateOnParse()
{
	short	o;

	HRESULT	hr = P()->get_validateOnParse(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument2::SetValidateOnParse(BOOL rhs)
{

	HRESULT	hr = P()->put_validateOnParse(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CXMLDOMDocument2::GetResolveExternals()
{
	short	o;

	HRESULT	hr = P()->get_resolveExternals(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument2::SetResolveExternals(BOOL rhs)
{

	HRESULT	hr = P()->put_resolveExternals(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CXMLDOMDocument2::GetPreserveWhiteSpace()
{
	short	o;

	HRESULT	hr = P()->get_preserveWhiteSpace(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument2::SetPreserveWhiteSpace(BOOL rhs)
{

	HRESULT	hr = P()->put_preserveWhiteSpace(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMDocument2::SetOnreadystatechange(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_onreadystatechange(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


void CXMLDOMDocument2::SetOndataavailable(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_ondataavailable(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


void CXMLDOMDocument2::SetOntransformnode(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_ontransformnode(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


CXMLDOMSchemaCollection CXMLDOMDocument2::GetNamespaces()
{
	IXMLDOMSchemaCollection* o;

	HRESULT	hr = P()->get_namespaces(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMDocument2::GetSchemas()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_schemas(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocument2::SetRefSchemas(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->putref_schemas(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


CXMLDOMParseError CXMLDOMDocument2::Validate()
{
	IXMLDOMParseError* o;

	HRESULT	hr = P()->validate(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMDocument2::SetProperty(LPCTSTR name, _variant_t value)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	VARIANT	varvalue = value.Detach();

	HRESULT	hr = P()->setProperty(bstrname, varvalue);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	VariantClear(&varvalue);
}


VARIANT CXMLDOMDocument2::GetProperty(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->getProperty(bstrname, &varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	_variant_t	o(varO, false);
	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMNamedNodeMap
//--------------------------------------------------------------------

CXMLDOMNamedNodeMap::CXMLDOMNamedNodeMap()
:	CInterfaceCallingWrapper<IXMLDOMNamedNodeMap>()
{}


CXMLDOMNamedNodeMap::CXMLDOMNamedNodeMap(IXMLDOMNamedNodeMap *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMNamedNodeMap>(p, bIncrementRefCount)
{}


CXMLDOMNamedNodeMap::CXMLDOMNamedNodeMap(const CXMLDOMNamedNodeMap &o)
:	CInterfaceCallingWrapper<IXMLDOMNamedNodeMap>(o)
{}


CXMLDOMNode CXMLDOMNamedNodeMap::GetNamedItem(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->getNamedItem(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMNode CXMLDOMNamedNodeMap::SetNamedItem(IXMLDOMNode* newItem)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->setNamedItem(newItem, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNamedNodeMap::RemoveNamedItem(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeNamedItem(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMNode CXMLDOMNamedNodeMap::GetItem(long index)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_item(index, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


long CXMLDOMNamedNodeMap::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNamedNodeMap::GetQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI)
{
	CString	strbaseName(baseName);
	BSTR	bstrbaseName = strbaseName.AllocSysString();
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->getQualifiedItem(bstrbaseName, bstrnamespaceURI, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbaseName);
	SysFreeString(bstrnamespaceURI);
	return o;
}


CXMLDOMNode CXMLDOMNamedNodeMap::RemoveQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI)
{
	CString	strbaseName(baseName);
	BSTR	bstrbaseName = strbaseName.AllocSysString();
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeQualifiedItem(bstrbaseName, bstrnamespaceURI, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbaseName);
	SysFreeString(bstrnamespaceURI);
	return o;
}


CXMLDOMNode CXMLDOMNamedNodeMap::NextNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->nextNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMNamedNodeMap::Reset()
{

	HRESULT	hr = P()->reset();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


IUnknown* CXMLDOMNamedNodeMap::Get_newEnum()
{
	IUnknown* o;

	HRESULT	hr = P()->get__newEnum(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMNode
//--------------------------------------------------------------------

CXMLDOMNode::CXMLDOMNode()
:	CInterfaceCallingWrapper<IXMLDOMNode>()
{}


CXMLDOMNode::CXMLDOMNode(IXMLDOMNode *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMNode>(p, bIncrementRefCount)
{}


CXMLDOMNode::CXMLDOMNode(const CXMLDOMNode &o)
:	CInterfaceCallingWrapper<IXMLDOMNode>(o)
{}


CString CXMLDOMNode::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMNode::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMNode::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMNode::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMNode::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMNode::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMNode::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMNode::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMNode::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMNode::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNode::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMNode::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMNode::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNode::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMNode::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMNode::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMNode::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMNode::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMNode::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNode::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMNode::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMNode::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMNode::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMNode::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNode::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNode::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMNode::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}




//--------------------------------------------------------------------
// class CXMLDOMNodeList
//--------------------------------------------------------------------

CXMLDOMNodeList::CXMLDOMNodeList()
:	CInterfaceCallingWrapper<IXMLDOMNodeList>()
{}


CXMLDOMNodeList::CXMLDOMNodeList(IXMLDOMNodeList *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMNodeList>(p, bIncrementRefCount)
{}


CXMLDOMNodeList::CXMLDOMNodeList(const CXMLDOMNodeList &o)
:	CInterfaceCallingWrapper<IXMLDOMNodeList>(o)
{}


CXMLDOMNode CXMLDOMNodeList::GetItem(long index)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_item(index, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


long CXMLDOMNodeList::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNodeList::NextNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->nextNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMNodeList::Reset()
{

	HRESULT	hr = P()->reset();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


IUnknown* CXMLDOMNodeList::Get_newEnum()
{
	IUnknown* o;

	HRESULT	hr = P()->get__newEnum(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMParseError
//--------------------------------------------------------------------

CXMLDOMParseError::CXMLDOMParseError()
:	CInterfaceCallingWrapper<IXMLDOMParseError>()
{}


CXMLDOMParseError::CXMLDOMParseError(IXMLDOMParseError *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMParseError>(p, bIncrementRefCount)
{}


CXMLDOMParseError::CXMLDOMParseError(const CXMLDOMParseError &o)
:	CInterfaceCallingWrapper<IXMLDOMParseError>(o)
{}


long CXMLDOMParseError::GetErrorCode()
{
	long o;

	HRESULT	hr = P()->get_errorCode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMParseError::GetUrl()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_url(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMParseError::GetReason()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_reason(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMParseError::GetSrcText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_srcText(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


long CXMLDOMParseError::GetLine()
{
	long o;

	HRESULT	hr = P()->get_line(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


long CXMLDOMParseError::GetLinepos()
{
	long o;

	HRESULT	hr = P()->get_linepos(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


long CXMLDOMParseError::GetFilepos()
{
	long o;

	HRESULT	hr = P()->get_filepos(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXMLHTTPRequest
//--------------------------------------------------------------------

CXMLHTTPRequest::CXMLHTTPRequest()
:	CInterfaceCallingWrapper<IXMLHTTPRequest>()
{}


CXMLHTTPRequest::CXMLHTTPRequest(IXMLHTTPRequest *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLHTTPRequest>(p, bIncrementRefCount)
{}


CXMLHTTPRequest::CXMLHTTPRequest(const CXMLHTTPRequest &o)
:	CInterfaceCallingWrapper<IXMLHTTPRequest>(o)
{}


void CXMLHTTPRequest::Open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, _variant_t varAsync, _variant_t bstrUser, _variant_t bstrPassword)
{
	CString	strbstrMethod(bstrMethod);
	BSTR	bstrbstrMethod = strbstrMethod.AllocSysString();
	CString	strbstrUrl(bstrUrl);
	BSTR	bstrbstrUrl = strbstrUrl.AllocSysString();
	VARIANT	varvarAsync = varAsync.Detach();
	VARIANT	varbstrUser = bstrUser.Detach();
	VARIANT	varbstrPassword = bstrPassword.Detach();

	HRESULT	hr = P()->open(bstrbstrMethod, bstrbstrUrl, varvarAsync, varbstrUser, varbstrPassword);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrMethod);
	SysFreeString(bstrbstrUrl);
	VariantClear(&varvarAsync);
	VariantClear(&varbstrUser);
	VariantClear(&varbstrPassword);
}


void CXMLHTTPRequest::SetRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue)
{
	CString	strbstrHeader(bstrHeader);
	BSTR	bstrbstrHeader = strbstrHeader.AllocSysString();
	CString	strbstrValue(bstrValue);
	BSTR	bstrbstrValue = strbstrValue.AllocSysString();

	HRESULT	hr = P()->setRequestHeader(bstrbstrHeader, bstrbstrValue);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrHeader);
	SysFreeString(bstrbstrValue);
}


CString CXMLHTTPRequest::GetResponseHeader(LPCTSTR bstrHeader)
{
	CString	strbstrHeader(bstrHeader);
	BSTR	bstrbstrHeader = strbstrHeader.AllocSysString();
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->getResponseHeader(bstrbstrHeader, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrHeader);
	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLHTTPRequest::GetAllResponseHeaders()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->getAllResponseHeaders(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLHTTPRequest::Send(_variant_t varBody)
{
	VARIANT	varvarBody = varBody.Detach();

	HRESULT	hr = P()->send(varvarBody);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varvarBody);
}


void CXMLHTTPRequest::Abort()
{

	HRESULT	hr = P()->abort();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


long CXMLHTTPRequest::GetStatus()
{
	long o;

	HRESULT	hr = P()->get_status(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLHTTPRequest::GetStatusText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_statusText(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


IDispatch* CXMLHTTPRequest::GetResponseXML()
{
	IDispatch* o;

	HRESULT	hr = P()->get_responseXML(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLHTTPRequest::GetResponseText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_responseText(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLHTTPRequest::GetResponseBody()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_responseBody(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


VARIANT CXMLHTTPRequest::GetResponseStream()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_responseStream(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


long CXMLHTTPRequest::GetReadyState()
{
	long o;

	HRESULT	hr = P()->get_readyState(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLHTTPRequest::SetOnreadystatechange(IDispatch* rhs)
{

	HRESULT	hr = P()->put_onreadystatechange(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}




//--------------------------------------------------------------------
// class CServerXMLHTTPRequest
//--------------------------------------------------------------------

CServerXMLHTTPRequest::CServerXMLHTTPRequest()
:	CInterfaceCallingWrapper<IServerXMLHTTPRequest>()
{}


CServerXMLHTTPRequest::CServerXMLHTTPRequest(IServerXMLHTTPRequest *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IServerXMLHTTPRequest>(p, bIncrementRefCount)
{}


CServerXMLHTTPRequest::CServerXMLHTTPRequest(const CServerXMLHTTPRequest &o)
:	CInterfaceCallingWrapper<IServerXMLHTTPRequest>(o)
{}


void CServerXMLHTTPRequest::Open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, _variant_t varAsync, _variant_t bstrUser, _variant_t bstrPassword)
{
	CString	strbstrMethod(bstrMethod);
	BSTR	bstrbstrMethod = strbstrMethod.AllocSysString();
	CString	strbstrUrl(bstrUrl);
	BSTR	bstrbstrUrl = strbstrUrl.AllocSysString();
	VARIANT	varvarAsync = varAsync.Detach();
	VARIANT	varbstrUser = bstrUser.Detach();
	VARIANT	varbstrPassword = bstrPassword.Detach();

	HRESULT	hr = P()->open(bstrbstrMethod, bstrbstrUrl, varvarAsync, varbstrUser, varbstrPassword);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrMethod);
	SysFreeString(bstrbstrUrl);
	VariantClear(&varvarAsync);
	VariantClear(&varbstrUser);
	VariantClear(&varbstrPassword);
}


void CServerXMLHTTPRequest::SetRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue)
{
	CString	strbstrHeader(bstrHeader);
	BSTR	bstrbstrHeader = strbstrHeader.AllocSysString();
	CString	strbstrValue(bstrValue);
	BSTR	bstrbstrValue = strbstrValue.AllocSysString();

	HRESULT	hr = P()->setRequestHeader(bstrbstrHeader, bstrbstrValue);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrHeader);
	SysFreeString(bstrbstrValue);
}


CString CServerXMLHTTPRequest::GetResponseHeader(LPCTSTR bstrHeader)
{
	CString	strbstrHeader(bstrHeader);
	BSTR	bstrbstrHeader = strbstrHeader.AllocSysString();
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->getResponseHeader(bstrbstrHeader, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbstrHeader);
	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CServerXMLHTTPRequest::GetAllResponseHeaders()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->getAllResponseHeaders(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CServerXMLHTTPRequest::Send(_variant_t varBody)
{
	VARIANT	varvarBody = varBody.Detach();

	HRESULT	hr = P()->send(varvarBody);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varvarBody);
}


void CServerXMLHTTPRequest::Abort()
{

	HRESULT	hr = P()->abort();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


long CServerXMLHTTPRequest::GetStatus()
{
	long o;

	HRESULT	hr = P()->get_status(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CServerXMLHTTPRequest::GetStatusText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_statusText(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


IDispatch* CServerXMLHTTPRequest::GetResponseXML()
{
	IDispatch* o;

	HRESULT	hr = P()->get_responseXML(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CServerXMLHTTPRequest::GetResponseText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_responseText(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CServerXMLHTTPRequest::GetResponseBody()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_responseBody(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


VARIANT CServerXMLHTTPRequest::GetResponseStream()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_responseStream(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


long CServerXMLHTTPRequest::GetReadyState()
{
	long o;

	HRESULT	hr = P()->get_readyState(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CServerXMLHTTPRequest::SetOnreadystatechange(IDispatch* rhs)
{

	HRESULT	hr = P()->put_onreadystatechange(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CServerXMLHTTPRequest::SetTimeouts(long resolveTimeout, long connectTimeout, long sendTimeout, long receiveTimeout)
{

	HRESULT	hr = P()->setTimeouts(resolveTimeout, connectTimeout, sendTimeout, receiveTimeout);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


BOOL CServerXMLHTTPRequest::WaitForResponse(_variant_t timeoutInSeconds)
{
	VARIANT	vartimeoutInSeconds = timeoutInSeconds.Detach();
	short	o;

	HRESULT	hr = P()->waitForResponse(vartimeoutInSeconds, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&vartimeoutInSeconds);
	return o;
}


VARIANT CServerXMLHTTPRequest::GetOption(SERVERXMLHTTP_OPTION option)
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->getOption(option, &varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CServerXMLHTTPRequest::SetOption(SERVERXMLHTTP_OPTION option, _variant_t value)
{
	VARIANT	varvalue = value.Detach();

	HRESULT	hr = P()->setOption(option, varvalue);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varvalue);
}




//--------------------------------------------------------------------
// class CXMLDOMAttribute
//--------------------------------------------------------------------

CXMLDOMAttribute::CXMLDOMAttribute()
:	CInterfaceCallingWrapper<IXMLDOMAttribute>()
{}


CXMLDOMAttribute::CXMLDOMAttribute(IXMLDOMAttribute *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMAttribute>(p, bIncrementRefCount)
{}


CXMLDOMAttribute::CXMLDOMAttribute(const CXMLDOMAttribute &o)
:	CInterfaceCallingWrapper<IXMLDOMAttribute>(o)
{}


CString CXMLDOMAttribute::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMAttribute::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMAttribute::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMAttribute::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMAttribute::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMAttribute::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMAttribute::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMAttribute::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMAttribute::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMAttribute::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMAttribute::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMAttribute::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMAttribute::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMAttribute::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMAttribute::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMAttribute::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMAttribute::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMAttribute::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMAttribute::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMAttribute::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMAttribute::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMAttribute::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMAttribute::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMAttribute::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMAttribute::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMAttribute::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMAttribute::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMAttribute::GetName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_name(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMAttribute::GetValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_value(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMAttribute::SetValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_value(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}




//--------------------------------------------------------------------
// class CXMLDOMCDATASection
//--------------------------------------------------------------------

CXMLDOMCDATASection::CXMLDOMCDATASection()
:	CInterfaceCallingWrapper<IXMLDOMCDATASection>()
{}


CXMLDOMCDATASection::CXMLDOMCDATASection(IXMLDOMCDATASection *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMCDATASection>(p, bIncrementRefCount)
{}


CXMLDOMCDATASection::CXMLDOMCDATASection(const CXMLDOMCDATASection &o)
:	CInterfaceCallingWrapper<IXMLDOMCDATASection>(o)
{}


CString CXMLDOMCDATASection::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMCDATASection::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMCDATASection::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMCDATASection::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMCDATASection::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMCDATASection::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMCDATASection::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMCDATASection::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMCDATASection::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMCDATASection::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCDATASection::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCDATASection::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMCDATASection::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCDATASection::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMCDATASection::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMCDATASection::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMCDATASection::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMCDATASection::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMCDATASection::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCDATASection::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMCDATASection::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMCDATASection::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMCDATASection::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMCDATASection::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCDATASection::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCDATASection::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCDATASection::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMCDATASection::GetData()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_data(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCDATASection::SetData(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_data(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


long CXMLDOMCDATASection::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMCDATASection::SubstringData(long offset, long count)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->substringData(offset, count, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCDATASection::AppendData(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->appendData(bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMCDATASection::InsertData(long offset, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->insertData(offset, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMCDATASection::DeleteData(long offset, long count)
{

	HRESULT	hr = P()->deleteData(offset, count);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMCDATASection::ReplaceData(long offset, long count, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->replaceData(offset, count, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


CXMLDOMText CXMLDOMCDATASection::SplitText(long offset)
{
	IXMLDOMText* o;

	HRESULT	hr = P()->splitText(offset, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMCharacterData
//--------------------------------------------------------------------

CXMLDOMCharacterData::CXMLDOMCharacterData()
:	CInterfaceCallingWrapper<IXMLDOMCharacterData>()
{}


CXMLDOMCharacterData::CXMLDOMCharacterData(IXMLDOMCharacterData *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMCharacterData>(p, bIncrementRefCount)
{}


CXMLDOMCharacterData::CXMLDOMCharacterData(const CXMLDOMCharacterData &o)
:	CInterfaceCallingWrapper<IXMLDOMCharacterData>(o)
{}


CString CXMLDOMCharacterData::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMCharacterData::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMCharacterData::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMCharacterData::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMCharacterData::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMCharacterData::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMCharacterData::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMCharacterData::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMCharacterData::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMCharacterData::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCharacterData::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCharacterData::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMCharacterData::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMCharacterData::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMCharacterData::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMCharacterData::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMCharacterData::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMCharacterData::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMCharacterData::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCharacterData::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMCharacterData::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMCharacterData::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMCharacterData::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMCharacterData::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCharacterData::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMCharacterData::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCharacterData::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMCharacterData::GetData()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_data(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCharacterData::SetData(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_data(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


long CXMLDOMCharacterData::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMCharacterData::SubstringData(long offset, long count)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->substringData(offset, count, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMCharacterData::AppendData(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->appendData(bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMCharacterData::InsertData(long offset, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->insertData(offset, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMCharacterData::DeleteData(long offset, long count)
{

	HRESULT	hr = P()->deleteData(offset, count);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMCharacterData::ReplaceData(long offset, long count, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->replaceData(offset, count, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}




//--------------------------------------------------------------------
// class CXMLDOMComment
//--------------------------------------------------------------------

CXMLDOMComment::CXMLDOMComment()
:	CInterfaceCallingWrapper<IXMLDOMComment>()
{}


CXMLDOMComment::CXMLDOMComment(IXMLDOMComment *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMComment>(p, bIncrementRefCount)
{}


CXMLDOMComment::CXMLDOMComment(const CXMLDOMComment &o)
:	CInterfaceCallingWrapper<IXMLDOMComment>(o)
{}


CString CXMLDOMComment::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMComment::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMComment::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMComment::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMComment::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMComment::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMComment::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMComment::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMComment::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMComment::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMComment::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMComment::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMComment::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMComment::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMComment::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMComment::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMComment::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMComment::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMComment::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMComment::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMComment::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMComment::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMComment::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMComment::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMComment::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMComment::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMComment::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMComment::GetData()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_data(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMComment::SetData(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_data(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


long CXMLDOMComment::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMComment::SubstringData(long offset, long count)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->substringData(offset, count, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMComment::AppendData(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->appendData(bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMComment::InsertData(long offset, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->insertData(offset, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMComment::DeleteData(long offset, long count)
{

	HRESULT	hr = P()->deleteData(offset, count);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMComment::ReplaceData(long offset, long count, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->replaceData(offset, count, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}




//--------------------------------------------------------------------
// class CXMLDOMDocumentFragment
//--------------------------------------------------------------------

CXMLDOMDocumentFragment::CXMLDOMDocumentFragment()
:	CInterfaceCallingWrapper<IXMLDOMDocumentFragment>()
{}


CXMLDOMDocumentFragment::CXMLDOMDocumentFragment(IXMLDOMDocumentFragment *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMDocumentFragment>(p, bIncrementRefCount)
{}


CXMLDOMDocumentFragment::CXMLDOMDocumentFragment(const CXMLDOMDocumentFragment &o)
:	CInterfaceCallingWrapper<IXMLDOMDocumentFragment>(o)
{}


CString CXMLDOMDocumentFragment::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMDocumentFragment::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocumentFragment::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMDocumentFragment::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMDocumentFragment::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMDocumentFragment::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMDocumentFragment::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMDocumentFragment::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocumentFragment::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentFragment::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocumentFragment::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMDocumentFragment::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMDocumentFragment::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocumentFragment::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMDocumentFragment::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocumentFragment::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMDocumentFragment::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentFragment::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMDocumentFragment::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMDocumentFragment::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMDocumentFragment::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocumentFragment::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentFragment::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentFragment::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocumentFragment::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}




//--------------------------------------------------------------------
// class CXMLDOMDocumentType
//--------------------------------------------------------------------

CXMLDOMDocumentType::CXMLDOMDocumentType()
:	CInterfaceCallingWrapper<IXMLDOMDocumentType>()
{}


CXMLDOMDocumentType::CXMLDOMDocumentType(IXMLDOMDocumentType *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMDocumentType>(p, bIncrementRefCount)
{}


CXMLDOMDocumentType::CXMLDOMDocumentType(const CXMLDOMDocumentType &o)
:	CInterfaceCallingWrapper<IXMLDOMDocumentType>(o)
{}


CString CXMLDOMDocumentType::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMDocumentType::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocumentType::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMDocumentType::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMDocumentType::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMDocumentType::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMDocumentType::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMDocumentType::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMDocumentType::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocumentType::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentType::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocumentType::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMDocumentType::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMDocumentType::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMDocumentType::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocumentType::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMDocumentType::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMDocumentType::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMDocumentType::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentType::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMDocumentType::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMDocumentType::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMDocumentType::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMDocumentType::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentType::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMDocumentType::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMDocumentType::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMDocumentType::GetName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_name(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNamedNodeMap CXMLDOMDocumentType::GetEntities()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_entities(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMDocumentType::GetNotations()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_notations(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMElement
//--------------------------------------------------------------------

CXMLDOMElement::CXMLDOMElement()
:	CInterfaceCallingWrapper<IXMLDOMElement>()
{}


CXMLDOMElement::CXMLDOMElement(IXMLDOMElement *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMElement>(p, bIncrementRefCount)
{}


CXMLDOMElement::CXMLDOMElement(const CXMLDOMElement &o)
:	CInterfaceCallingWrapper<IXMLDOMElement>(o)
{}


CString CXMLDOMElement::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMElement::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMElement::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMElement::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMElement::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMElement::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMElement::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMElement::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMElement::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMElement::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMElement::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMElement::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMElement::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMElement::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMElement::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMElement::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMElement::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMElement::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMElement::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMElement::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMElement::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMElement::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMElement::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMElement::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMElement::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMElement::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMElement::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMElement::GetTagName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_tagName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMElement::GetAttribute(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->getAttribute(bstrname, &varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMElement::SetAttribute(LPCTSTR name, _variant_t value)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	VARIANT	varvalue = value.Detach();

	HRESULT	hr = P()->setAttribute(bstrname, varvalue);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	VariantClear(&varvalue);
}


void CXMLDOMElement::RemoveAttribute(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();

	HRESULT	hr = P()->removeAttribute(bstrname);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
}


CXMLDOMAttribute CXMLDOMElement::GetAttributeNode(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	IXMLDOMAttribute* o;

	HRESULT	hr = P()->getAttributeNode(bstrname, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	return o;
}


CXMLDOMAttribute CXMLDOMElement::SetAttributeNode(IXMLDOMAttribute* DOMAttribute)
{
	IXMLDOMAttribute* o;

	HRESULT	hr = P()->setAttributeNode(DOMAttribute, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMAttribute CXMLDOMElement::RemoveAttributeNode(IXMLDOMAttribute* DOMAttribute)
{
	IXMLDOMAttribute* o;

	HRESULT	hr = P()->removeAttributeNode(DOMAttribute, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMElement::GetElementsByTagName(LPCTSTR tagName)
{
	CString	strtagName(tagName);
	BSTR	bstrtagName = strtagName.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->getElementsByTagName(bstrtagName, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrtagName);
	return o;
}


void CXMLDOMElement::Normalize()
{

	HRESULT	hr = P()->normalize();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}




//--------------------------------------------------------------------
// class CXMLDOMEntity
//--------------------------------------------------------------------

CXMLDOMEntity::CXMLDOMEntity()
:	CInterfaceCallingWrapper<IXMLDOMEntity>()
{}


CXMLDOMEntity::CXMLDOMEntity(IXMLDOMEntity *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMEntity>(p, bIncrementRefCount)
{}


CXMLDOMEntity::CXMLDOMEntity(const CXMLDOMEntity &o)
:	CInterfaceCallingWrapper<IXMLDOMEntity>(o)
{}


CString CXMLDOMEntity::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMEntity::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMEntity::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMEntity::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMEntity::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMEntity::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMEntity::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMEntity::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMEntity::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMEntity::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntity::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMEntity::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMEntity::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntity::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMEntity::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMEntity::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMEntity::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMEntity::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMEntity::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntity::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMEntity::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMEntity::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMEntity::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMEntity::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntity::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntity::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMEntity::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


VARIANT CXMLDOMEntity::GetPublicId()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_publicId(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


VARIANT CXMLDOMEntity::GetSystemId()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_systemId(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


CString CXMLDOMEntity::GetNotationName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_notationName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMEntityReference
//--------------------------------------------------------------------

CXMLDOMEntityReference::CXMLDOMEntityReference()
:	CInterfaceCallingWrapper<IXMLDOMEntityReference>()
{}


CXMLDOMEntityReference::CXMLDOMEntityReference(IXMLDOMEntityReference *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMEntityReference>(p, bIncrementRefCount)
{}


CXMLDOMEntityReference::CXMLDOMEntityReference(const CXMLDOMEntityReference &o)
:	CInterfaceCallingWrapper<IXMLDOMEntityReference>(o)
{}


CString CXMLDOMEntityReference::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMEntityReference::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMEntityReference::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMEntityReference::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMEntityReference::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMEntityReference::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMEntityReference::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMEntityReference::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMEntityReference::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMEntityReference::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntityReference::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMEntityReference::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMEntityReference::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMEntityReference::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMEntityReference::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMEntityReference::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMEntityReference::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMEntityReference::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMEntityReference::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntityReference::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMEntityReference::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMEntityReference::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMEntityReference::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMEntityReference::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntityReference::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMEntityReference::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMEntityReference::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}




//--------------------------------------------------------------------
// class CXMLDOMImplementation
//--------------------------------------------------------------------

CXMLDOMImplementation::CXMLDOMImplementation()
:	CInterfaceCallingWrapper<IXMLDOMImplementation>()
{}


CXMLDOMImplementation::CXMLDOMImplementation(IXMLDOMImplementation *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMImplementation>(p, bIncrementRefCount)
{}


CXMLDOMImplementation::CXMLDOMImplementation(const CXMLDOMImplementation &o)
:	CInterfaceCallingWrapper<IXMLDOMImplementation>(o)
{}


BOOL CXMLDOMImplementation::HasFeature(LPCTSTR feature, LPCTSTR version)
{
	CString	strfeature(feature);
	BSTR	bstrfeature = strfeature.AllocSysString();
	CString	strversion(version);
	BSTR	bstrversion = strversion.AllocSysString();
	short	o;

	HRESULT	hr = P()->hasFeature(bstrfeature, bstrversion, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrfeature);
	SysFreeString(bstrversion);
	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMNotation
//--------------------------------------------------------------------

CXMLDOMNotation::CXMLDOMNotation()
:	CInterfaceCallingWrapper<IXMLDOMNotation>()
{}


CXMLDOMNotation::CXMLDOMNotation(IXMLDOMNotation *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMNotation>(p, bIncrementRefCount)
{}


CXMLDOMNotation::CXMLDOMNotation(const CXMLDOMNotation &o)
:	CInterfaceCallingWrapper<IXMLDOMNotation>(o)
{}


CString CXMLDOMNotation::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMNotation::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMNotation::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMNotation::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMNotation::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMNotation::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMNotation::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMNotation::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMNotation::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMNotation::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNotation::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMNotation::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMNotation::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMNotation::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMNotation::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMNotation::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMNotation::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMNotation::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMNotation::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNotation::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMNotation::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMNotation::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMNotation::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMNotation::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNotation::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMNotation::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMNotation::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


VARIANT CXMLDOMNotation::GetPublicId()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_publicId(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


VARIANT CXMLDOMNotation::GetSystemId()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_systemId(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}




//--------------------------------------------------------------------
// class CXMLDOMProcessingInstruction
//--------------------------------------------------------------------

CXMLDOMProcessingInstruction::CXMLDOMProcessingInstruction()
:	CInterfaceCallingWrapper<IXMLDOMProcessingInstruction>()
{}


CXMLDOMProcessingInstruction::CXMLDOMProcessingInstruction(IXMLDOMProcessingInstruction *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMProcessingInstruction>(p, bIncrementRefCount)
{}


CXMLDOMProcessingInstruction::CXMLDOMProcessingInstruction(const CXMLDOMProcessingInstruction &o)
:	CInterfaceCallingWrapper<IXMLDOMProcessingInstruction>(o)
{}


CString CXMLDOMProcessingInstruction::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMProcessingInstruction::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMProcessingInstruction::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMProcessingInstruction::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMProcessingInstruction::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMProcessingInstruction::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMProcessingInstruction::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMProcessingInstruction::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMProcessingInstruction::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMProcessingInstruction::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMProcessingInstruction::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMProcessingInstruction::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMProcessingInstruction::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMProcessingInstruction::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMProcessingInstruction::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMProcessingInstruction::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMProcessingInstruction::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMProcessingInstruction::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMProcessingInstruction::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMProcessingInstruction::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMProcessingInstruction::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMProcessingInstruction::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMProcessingInstruction::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMProcessingInstruction::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMProcessingInstruction::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMProcessingInstruction::GetTarget()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_target(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMProcessingInstruction::GetData()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_data(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMProcessingInstruction::SetData(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_data(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}




//--------------------------------------------------------------------
// class CXMLDOMSchemaCollection
//--------------------------------------------------------------------

CXMLDOMSchemaCollection::CXMLDOMSchemaCollection()
:	CInterfaceCallingWrapper<IXMLDOMSchemaCollection>()
{}


CXMLDOMSchemaCollection::CXMLDOMSchemaCollection(IXMLDOMSchemaCollection *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMSchemaCollection>(p, bIncrementRefCount)
{}


CXMLDOMSchemaCollection::CXMLDOMSchemaCollection(const CXMLDOMSchemaCollection &o)
:	CInterfaceCallingWrapper<IXMLDOMSchemaCollection>(o)
{}


void CXMLDOMSchemaCollection::Add(LPCTSTR namespaceURI, _variant_t var)
{
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();
	VARIANT	varvar = var.Detach();

	HRESULT	hr = P()->add(bstrnamespaceURI, varvar);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrnamespaceURI);
	VariantClear(&varvar);
}


CXMLDOMNode CXMLDOMSchemaCollection::Get(LPCTSTR namespaceURI)
{
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->get(bstrnamespaceURI, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrnamespaceURI);
	return o;
}


void CXMLDOMSchemaCollection::Remove(LPCTSTR namespaceURI)
{
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();

	HRESULT	hr = P()->remove(bstrnamespaceURI);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrnamespaceURI);
}


long CXMLDOMSchemaCollection::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMSchemaCollection::GetNamespaceURI(long index)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(index, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMSchemaCollection::AddCollection(IXMLDOMSchemaCollection* otherCollection)
{

	HRESULT	hr = P()->addCollection(otherCollection);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


IUnknown* CXMLDOMSchemaCollection::Get_newEnum()
{
	IUnknown* o;

	HRESULT	hr = P()->get__newEnum(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}
//--------------------------------------------------------------------
// class CXMLDOMSelection
//--------------------------------------------------------------------

CXMLDOMSelection::CXMLDOMSelection()
:	CInterfaceCallingWrapper<IXMLDOMSelection>()
{}


CXMLDOMSelection::CXMLDOMSelection(IXMLDOMSelection *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMSelection>(p, bIncrementRefCount)
{}


CXMLDOMSelection::CXMLDOMSelection(const CXMLDOMSelection &o)
:	CInterfaceCallingWrapper<IXMLDOMSelection>(o)
{}


CXMLDOMNode CXMLDOMSelection::GetItem(long index)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_item(index, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


long CXMLDOMSelection::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMSelection::NextNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->nextNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMSelection::Reset()
{

	HRESULT	hr = P()->reset();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


IUnknown* CXMLDOMSelection::Get_newEnum()
{
	IUnknown* o;

	HRESULT	hr = P()->get__newEnum(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMSelection::GetExpr()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_expr(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMSelection::SetExpr(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_expr(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CXMLDOMNode CXMLDOMSelection::GetContext()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_context(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMSelection::SetRefContext(IXMLDOMNode* rhs)
{

	HRESULT	hr = P()->putref_context(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


CXMLDOMNode CXMLDOMSelection::PeekNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->peekNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMSelection::Matches(IXMLDOMNode* pNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->matches(pNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMSelection::RemoveNext()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeNext(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXMLDOMSelection::RemoveAll()
{

	HRESULT	hr = P()->removeAll();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


CXMLDOMSelection CXMLDOMSelection::Clone()
{
	IXMLDOMSelection* o;

	HRESULT	hr = P()->clone(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMSelection::GetProperty(LPCTSTR name)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->getProperty(bstrname, &varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMSelection::SetProperty(LPCTSTR name, _variant_t value)
{
	CString	strname(name);
	BSTR	bstrname = strname.AllocSysString();
	VARIANT	varvalue = value.Detach();

	HRESULT	hr = P()->setProperty(bstrname, varvalue);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrname);
	VariantClear(&varvalue);
}




//--------------------------------------------------------------------
// class CXMLDOMText
//--------------------------------------------------------------------

CXMLDOMText::CXMLDOMText()
:	CInterfaceCallingWrapper<IXMLDOMText>()
{}


CXMLDOMText::CXMLDOMText(IXMLDOMText *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXMLDOMText>(p, bIncrementRefCount)
{}


CXMLDOMText::CXMLDOMText(const CXMLDOMText &o)
:	CInterfaceCallingWrapper<IXMLDOMText>(o)
{}


CString CXMLDOMText::GetNodeName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


VARIANT CXMLDOMText::GetNodeValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMText::SetNodeValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


DOMNodeType CXMLDOMText::GetNodeType()
{
	DOMNodeType o;

	HRESULT	hr = P()->get_nodeType(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::GetParentNode()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_parentNode(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNodeList CXMLDOMText::GetChildNodes()
{
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->get_childNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::GetFirstChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_firstChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::GetLastChild()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_lastChild(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::GetPreviousSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_previousSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::GetNextSibling()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_nextSibling(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNamedNodeMap CXMLDOMText::GetAttributes()
{
	IXMLDOMNamedNodeMap* o;

	HRESULT	hr = P()->get_attributes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::InsertBefore(IXMLDOMNode* newChild, _variant_t refChild)
{
	VARIANT	varrefChild = refChild.Detach();
	IXMLDOMNode* o;

	HRESULT	hr = P()->insertBefore(newChild, varrefChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrefChild);
	return o;
}


CXMLDOMNode CXMLDOMText::ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->replaceChild(newChild, oldChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::RemoveChild(IXMLDOMNode* childNode)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->removeChild(childNode, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::AppendChild(IXMLDOMNode* newChild)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->appendChild(newChild, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


BOOL CXMLDOMText::HasChildNodes()
{
	short	o;

	HRESULT	hr = P()->hasChildNodes(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMDocument CXMLDOMText::GetOwnerDocument()
{
	IXMLDOMDocument* o;

	HRESULT	hr = P()->get_ownerDocument(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::CloneNode(BOOL deep)
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->cloneNode(deep, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMText::GetNodeTypeString()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_nodeTypeString(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMText::GetText()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_text(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMText::SetText(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_text(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


BOOL CXMLDOMText::GetSpecified()
{
	short	o;

	HRESULT	hr = P()->get_specified(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXMLDOMNode CXMLDOMText::GetDefinition()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_definition(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


VARIANT CXMLDOMText::GetNodeTypedValue()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_nodeTypedValue(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMText::SetNodeTypedValue(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_nodeTypedValue(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXMLDOMText::GetDataType()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_dataType(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


void CXMLDOMText::SetDataType(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_dataType(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


CString CXMLDOMText::GetXml()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_xml(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMText::TransformNode(IXMLDOMNode* stylesheet)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->transformNode(stylesheet, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CXMLDOMNodeList CXMLDOMText::SelectNodes(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNodeList* o;

	HRESULT	hr = P()->selectNodes(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


CXMLDOMNode CXMLDOMText::SelectSingleNode(LPCTSTR queryString)
{
	CString	strqueryString(queryString);
	BSTR	bstrqueryString = strqueryString.AllocSysString();
	IXMLDOMNode* o;

	HRESULT	hr = P()->selectSingleNode(bstrqueryString, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrqueryString);
	return o;
}


BOOL CXMLDOMText::GetParsed()
{
	short	o;

	HRESULT	hr = P()->get_parsed(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMText::GetNamespaceURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_namespaceURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMText::GetPrefix()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_prefix(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXMLDOMText::GetBaseName()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_baseName(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMText::TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject)
{
	VARIANT	varoutputObject = outputObject.Detach();

	HRESULT	hr = P()->transformNodeToObject(stylesheet, varoutputObject);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varoutputObject);
}


CString CXMLDOMText::GetData()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_data(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMText::SetData(LPCTSTR rhs)
{
	CString	strrhs(rhs);
	BSTR	bstrrhs = strrhs.AllocSysString();

	HRESULT	hr = P()->put_data(bstrrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrrhs);
}


long CXMLDOMText::GetLength()
{
	long o;

	HRESULT	hr = P()->get_length(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CString CXMLDOMText::SubstringData(long offset, long count)
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->substringData(offset, count, &bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXMLDOMText::AppendData(LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->appendData(bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMText::InsertData(long offset, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->insertData(offset, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


void CXMLDOMText::DeleteData(long offset, long count)
{

	HRESULT	hr = P()->deleteData(offset, count);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


void CXMLDOMText::ReplaceData(long offset, long count, LPCTSTR data)
{
	CString	strdata(data);
	BSTR	bstrdata = strdata.AllocSysString();

	HRESULT	hr = P()->replaceData(offset, count, bstrdata);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrdata);
}


CXMLDOMText CXMLDOMText::SplitText(long offset)
{
	IXMLDOMText* o;

	HRESULT	hr = P()->splitText(offset, &o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXSLProcessor
//--------------------------------------------------------------------

CXSLProcessor::CXSLProcessor()
:	CInterfaceCallingWrapper<IXSLProcessor>()
{}


CXSLProcessor::CXSLProcessor(IXSLProcessor *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXSLProcessor>(p, bIncrementRefCount)
{}


CXSLProcessor::CXSLProcessor(const CXSLProcessor &o)
:	CInterfaceCallingWrapper<IXSLProcessor>(o)
{}


void CXSLProcessor::SetInput(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_input(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXSLProcessor::GetInput()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_input(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


CXSLTemplate CXSLProcessor::GetOwnerTemplate()
{
	IXSLTemplate* o;

	HRESULT	hr = P()->get_ownerTemplate(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXSLProcessor::SetStartMode(LPCTSTR mode, LPCTSTR namespaceURI)
{
	CString	strmode(mode);
	BSTR	bstrmode = strmode.AllocSysString();
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();

	HRESULT	hr = P()->setStartMode(bstrmode, bstrnamespaceURI);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrmode);
	SysFreeString(bstrnamespaceURI);
}


CString CXSLProcessor::GetStartMode()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_startMode(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


CString CXSLProcessor::GetStartModeURI()
{
	BSTR	bstrO = NULL;

	HRESULT	hr = P()->get_startModeURI(&bstrO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	CString	o((LPCTSTR)_bstr_t(bstrO, false));
	return o;
}


void CXSLProcessor::SetOutput(_variant_t rhs)
{
	VARIANT	varrhs = rhs.Detach();

	HRESULT	hr = P()->put_output(varrhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	VariantClear(&varrhs);
}


VARIANT CXSLProcessor::GetOutput()
{
	VARIANT	varO;
	VariantInit(&varO);

	HRESULT	hr = P()->get_output(&varO);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	_variant_t	o(varO, false);
	return o;
}


BOOL CXSLProcessor::Transform()
{
	short	o;

	HRESULT	hr = P()->transform(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXSLProcessor::Reset()
{

	HRESULT	hr = P()->reset();
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


long CXSLProcessor::GetReadyState()
{
	long o;

	HRESULT	hr = P()->get_readyState(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


void CXSLProcessor::AddParameter(LPCTSTR baseName, _variant_t parameter, LPCTSTR namespaceURI)
{
	CString	strbaseName(baseName);
	BSTR	bstrbaseName = strbaseName.AllocSysString();
	VARIANT	varparameter = parameter.Detach();
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();

	HRESULT	hr = P()->addParameter(bstrbaseName, varparameter, bstrnamespaceURI);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrbaseName);
	VariantClear(&varparameter);
	SysFreeString(bstrnamespaceURI);
}


void CXSLProcessor::AddObject(IDispatch* obj, LPCTSTR namespaceURI)
{
	CString	strnamespaceURI(namespaceURI);
	BSTR	bstrnamespaceURI = strnamespaceURI.AllocSysString();

	HRESULT	hr = P()->addObject(obj, bstrnamespaceURI);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	SysFreeString(bstrnamespaceURI);
}


CXMLDOMNode CXSLProcessor::GetStylesheet()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_stylesheet(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CXSLTemplate
//--------------------------------------------------------------------

CXSLTemplate::CXSLTemplate()
:	CInterfaceCallingWrapper<IXSLTemplate>()
{}


CXSLTemplate::CXSLTemplate(IXSLTemplate *p, BOOL bIncrementRefCount /*= FALSE*/)
:	CInterfaceCallingWrapper<IXSLTemplate>(p, bIncrementRefCount)
{}


CXSLTemplate::CXSLTemplate(const CXSLTemplate &o)
:	CInterfaceCallingWrapper<IXSLTemplate>(o)
{}


void CXSLTemplate::SetRefStylesheet(IXMLDOMNode* rhs)
{

	HRESULT	hr = P()->putref_stylesheet(rhs);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

}


CXMLDOMNode CXSLTemplate::GetStylesheet()
{
	IXMLDOMNode* o;

	HRESULT	hr = P()->get_stylesheet(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}


CXSLProcessor CXSLTemplate::CreateProcessor()
{
	IXSLProcessor* o;

	HRESULT	hr = P()->createProcessor(&o);
	if (!SUCCEEDED(hr)) AfxThrowComException(hr);

	return o;
}




//--------------------------------------------------------------------
// class CDOMDocumentClass
//--------------------------------------------------------------------

const CLSID CDOMDocumentClass::m_ClsId = {0xf6d90f11, 0x9c73, 0x11d3, {0xb3, 0x2e, 0x00, 0xc0, 0x4f, 0x99, 0x0b, 0xb4}};


CXMLDOMDocument2 CDOMDocumentClass::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CDOMDocumentClass::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CDOMDocument26Class
//--------------------------------------------------------------------

const CLSID CDOMDocument26Class::m_ClsId = {0xf5078f1b, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLDOMDocument2 CDOMDocument26Class::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CDOMDocument26Class::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CDOMDocument30Class
//--------------------------------------------------------------------

const CLSID CDOMDocument30Class::m_ClsId = {0xf5078f32, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLDOMDocument2 CDOMDocument30Class::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CDOMDocument30Class::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CDOMDocument40Class
//--------------------------------------------------------------------

const CLSID CDOMDocument40Class::m_ClsId = {0x88d969c0, 0xf192, 0x11d4, {0xa6, 0x5f, 0x00, 0x40, 0x96, 0x32, 0x51, 0xe5}};


CXMLDOMDocument2 CDOMDocument40Class::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CDOMDocument40Class::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CFreeThreadedDOMDocumentClass
//--------------------------------------------------------------------

const CLSID CFreeThreadedDOMDocumentClass::m_ClsId = {0xf6d90f12, 0x9c73, 0x11d3, {0xb3, 0x2e, 0x00, 0xc0, 0x4f, 0x99, 0x0b, 0xb4}};


CXMLDOMDocument2 CFreeThreadedDOMDocumentClass::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CFreeThreadedDOMDocumentClass::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CFreeThreadedDOMDocument26Class
//--------------------------------------------------------------------

const CLSID CFreeThreadedDOMDocument26Class::m_ClsId = {0xf5078f1c, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLDOMDocument2 CFreeThreadedDOMDocument26Class::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CFreeThreadedDOMDocument26Class::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CFreeThreadedDOMDocument30Class
//--------------------------------------------------------------------

const CLSID CFreeThreadedDOMDocument30Class::m_ClsId = {0xf5078f33, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLDOMDocument2 CFreeThreadedDOMDocument30Class::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CFreeThreadedDOMDocument30Class::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CFreeThreadedDOMDocument40Class
//--------------------------------------------------------------------

const CLSID CFreeThreadedDOMDocument40Class::m_ClsId = {0x88d969c1, 0xf192, 0x11d4, {0xa6, 0x5f, 0x00, 0x40, 0x96, 0x32, 0x51, 0xe5}};


CXMLDOMDocument2 CFreeThreadedDOMDocument40Class::CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMDocument2 *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMDocument2), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}


XMLDOMDocumentEvents* CFreeThreadedDOMDocument40Class::CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	XMLDOMDocumentEvents *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(XMLDOMDocumentEvents), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLSchemaCacheClass
//--------------------------------------------------------------------

const CLSID CXMLSchemaCacheClass::m_ClsId = {0x373984c9, 0xb845, 0x449b, {0x91, 0xe7, 0x45, 0xac, 0x83, 0x03, 0x6a, 0xde}};


CXMLDOMSchemaCollection CXMLSchemaCacheClass::CreateXMLDOMSchemaCollection(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMSchemaCollection *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMSchemaCollection), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLSchemaCache26Class
//--------------------------------------------------------------------

const CLSID CXMLSchemaCache26Class::m_ClsId = {0xf5078f1d, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLDOMSchemaCollection CXMLSchemaCache26Class::CreateXMLDOMSchemaCollection(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMSchemaCollection *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMSchemaCollection), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLSchemaCache30Class
//--------------------------------------------------------------------

const CLSID CXMLSchemaCache30Class::m_ClsId = {0xf5078f34, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLDOMSchemaCollection CXMLSchemaCache30Class::CreateXMLDOMSchemaCollection(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLDOMSchemaCollection *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLDOMSchemaCollection), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXSLTemplateClass
//--------------------------------------------------------------------

const CLSID CXSLTemplateClass::m_ClsId = {0x2933bf94, 0x7b36, 0x11d2, {0xb2, 0x0e, 0x00, 0xc0, 0x4f, 0x98, 0x3e, 0x60}};


CXSLTemplate CXSLTemplateClass::CreateXSLTemplate(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXSLTemplate *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXSLTemplate), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXSLTemplate26Class
//--------------------------------------------------------------------

const CLSID CXSLTemplate26Class::m_ClsId = {0xf5078f21, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXSLTemplate CXSLTemplate26Class::CreateXSLTemplate(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXSLTemplate *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXSLTemplate), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXSLTemplate30Class
//--------------------------------------------------------------------

const CLSID CXSLTemplate30Class::m_ClsId = {0xf5078f36, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXSLTemplate CXSLTemplate30Class::CreateXSLTemplate(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXSLTemplate *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXSLTemplate), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXSLTemplate40Class
//--------------------------------------------------------------------

const CLSID CXSLTemplate40Class::m_ClsId = {0x88d969c3, 0xf192, 0x11d4, {0xa6, 0x5f, 0x00, 0x40, 0x96, 0x32, 0x51, 0xe5}};


CXSLTemplate CXSLTemplate40Class::CreateXSLTemplate(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXSLTemplate *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXSLTemplate), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLHTTPClass
//--------------------------------------------------------------------

const CLSID CXMLHTTPClass::m_ClsId = {0xf6d90f16, 0x9c73, 0x11d3, {0xb3, 0x2e, 0x00, 0xc0, 0x4f, 0x99, 0x0b, 0xb4}};


CXMLHTTPRequest CXMLHTTPClass::CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLHTTPRequest *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLHTTPRequest), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLHTTP26Class
//--------------------------------------------------------------------

const CLSID CXMLHTTP26Class::m_ClsId = {0xf5078f1e, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLHTTPRequest CXMLHTTP26Class::CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLHTTPRequest *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLHTTPRequest), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLHTTP30Class
//--------------------------------------------------------------------

const CLSID CXMLHTTP30Class::m_ClsId = {0xf5078f35, 0xc551, 0x11d3, {0x89, 0xb9, 0x00, 0x00, 0xf8, 0x1f, 0xe2, 0x21}};


CXMLHTTPRequest CXMLHTTP30Class::CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLHTTPRequest *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLHTTPRequest), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}




//--------------------------------------------------------------------
// class CXMLHTTP40Class
//--------------------------------------------------------------------

const CLSID CXMLHTTP40Class::m_ClsId = {0x88d969c5, 0xf192, 0x11d4, {0xa6, 0x5f, 0x00, 0x40, 0x96, 0x32, 0x51, 0xe5}};


CXMLHTTPRequest CXMLHTTP40Class::CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter /*= NULL*/, DWORD dwClsContext /*= CLSCTX_ALL*/)
{
	IXMLHTTPRequest *p;
	HRESULT	hr = CoCreateInstance(m_ClsId, pUnkOuter, dwClsContext, __uuidof(IXMLHTTPRequest), (LPVOID*)&p);
	if (hr != S_OK) AfxThrowComException(hr);
	return p;
}

//using namespace MSXML2;
//_bstr_t Format(MSXML2::IXMLDOMDocumentPtr doc)
//{
//    //MXXMLWriter
  //  MSXML2::IMXWriterPtr writer;
    //writer.CreateInstance(__uuidof(MSXML2::MXXMLWriter));
    //writer->indent = VARIANT_TRUE;
    //MSXML2::ISAXXMLReaderPtr reader;
    //reader.CreateInstance(__uuidof(MSXML2::SAXXMLReader));
    //MSXML2::ISAXContentHandlerPtr handler = writer;
    //reader->putContentHandler(handler);
    //reader->parse(doc.GetInterfacePtr());
    //return writer->output;
//}
