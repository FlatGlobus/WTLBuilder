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

#ifndef __DOMXML_H__
#define __DOMXML_H__

#include "InterfaceWrapper.h"
#include "msxml2.h"

// forward declarations
class CSAXXMLReaderClass;
class CXMLHTTP40Class;
class CXMLHTTPClass;
class CFreeThreadedDOMDocument40Class;
class CXSLProcessor;
class CXMLHTTP30Class;
class CFreeThreadedDOMDocument30Class;
class CXMLDOMText;
class CXMLDOMAttribute;
class CSAXXMLReader40Class;
class CXSLTemplate40Class;
class CXSLTemplateClass;
class CXMLHTTPRequest;
class CMXXMLWriter40Class;
class CSAXXMLReader30Class;
class CServerXMLHTTPClass;
class CXSLTemplate30Class;
class CXMLDOMSelection;
class CXMLDOMNotation;
class CXMLDOMEntityReference;
class CMXXMLWriter30Class;
class CDOMDocumentClass;
class CXMLDOMEntity;
class CXMLDOMCharacterData;
class CMXWriter;
class CDOMDocument40Class;
class CXMLDOMNode;
class CXMLSchemaCache40Class;
class CDOMDocument30Class;
class CXMLDOMDocumentFragment;
class CXMLDOMDocument;
class CXMLSchemaCache30Class;
class CXMLDOMProcessingInstruction;
class CXMLDOMParseError;
class CXMLDOMDocument2;
class CXMLHTTP26Class;
class CFreeThreadedDOMDocument26Class;
class CSAXAttributesClass;
class CMXXMLWriterClass;
class CServerXMLHTTP40Class;
class CFreeThreadedDOMDocumentClass;
class CXMLDOMElement;
class CXMLDOMDocumentType;
class CVBSAXLocator;
class CMXAttributes;
class CServerXMLHTTP30Class;
class CXSLTemplate26Class;
class CXMLDOMImplementation;
class CServerXMLHTTPRequest;
class CDOMDocument26Class;
class CXSLTemplate;
class CXMLDOMComment;
class CSAXAttributes40Class;
class CVBSAXAttributes;
class CXMLSchemaCache26Class;
class CXMLDOMSchemaCollection;
class CXMLDOMCDATASection;
class CXMLDOMNodeList;
class CSAXAttributes30Class;
class CVBSAXXMLReader;
class CXMLDOMNamedNodeMap;
class CXMLDOMSchemaCollection2;
class CXMLSchemaCacheClass;

class  CXMLDOMDocument : public CInterfaceCallingWrapper<IXMLDOMDocument>
{
// construction/destruction
public:
	CXMLDOMDocument();
	CXMLDOMDocument(IXMLDOMDocument *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMDocument(const CXMLDOMDocument &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** node corresponding to the DOCTYPE */
	CXMLDOMDocumentType GetDoctype();

	/** info on this DOM implementation */
	CXMLDOMImplementation GetImplementation();

	/** the root of the tree */
	CXMLDOMElement GetDocumentElement();

	/** the root of the tree */
	void SetRefDocumentElement(IXMLDOMElement* rhs);

	/** create an Element node */
	CXMLDOMElement CreateElement(LPCTSTR tagName);

	/** create a DocumentFragment node */
	CXMLDOMDocumentFragment CreateDocumentFragment();

	/** create a text node */
	CXMLDOMText CreateTextNode(LPCTSTR data);

	/** create a comment node */
	CXMLDOMComment CreateComment(LPCTSTR data);

	/** create a CDATA section node */
	CXMLDOMCDATASection CreateCDATASection(LPCTSTR data);

	/** create a processing instruction node */
	CXMLDOMProcessingInstruction CreateProcessingInstruction(LPCTSTR target, LPCTSTR data);

	/** create an attribute node */
	CXMLDOMAttribute CreateAttribute(LPCTSTR name);

	/** create an entity reference node */
	CXMLDOMEntityReference CreateEntityReference(LPCTSTR name);

	/** build a list of elements by name */
	CXMLDOMNodeList GetElementsByTagName(LPCTSTR tagName);

	/** create a node of the specified node type and name */
	CXMLDOMNode CreateNode(_variant_t type, LPCTSTR name, LPCTSTR namespaceURI);

	/** retrieve node from it's ID */
	CXMLDOMNode NodeFromID(LPCTSTR idString);

	/** load document from the specified XML source */
	BOOL Load(_variant_t xmlSource);

	/** get the state of the XML document */
	long GetReadyState();

	/** get the last parser error */
	CXMLDOMParseError GetParseError();

	/** get the URL for the loaded XML document */
	CString GetUrl();

	/** flag for asynchronous download */
	BOOL GetAsync();

	/** flag for asynchronous download */
	void SetAsync(BOOL rhs);

	/** abort an asynchronous download */
	void Abort();

	/** load the document from a string */
	BOOL LoadXML(LPCTSTR bstrXML);

	/** save the document to a specified destination */
	void Save(_variant_t destination);

	/** indicates whether the parser performs validation */
	BOOL GetValidateOnParse();

	/** indicates whether the parser performs validation */
	void SetValidateOnParse(BOOL rhs);

	/** indicates whether the parser resolves references to external DTD/Entities/Schema */
	BOOL GetResolveExternals();

	/** indicates whether the parser resolves references to external DTD/Entities/Schema */
	void SetResolveExternals(BOOL rhs);

	/** indicates whether the parser preserves whitespace */
	BOOL GetPreserveWhiteSpace();

	/** indicates whether the parser preserves whitespace */
	void SetPreserveWhiteSpace(BOOL rhs);

	/** register a readystatechange event handler */
	void SetOnreadystatechange(_variant_t rhs);

	/** register an ondataavailable event handler */
	void SetOndataavailable(_variant_t rhs);

	/** register an ontransformnode event handler */
	void SetOntransformnode(_variant_t rhs);

};



class  CXMLDOMDocument2 : public CInterfaceCallingWrapper<IXMLDOMDocument2>
{
// construction/destruction
public:
	CXMLDOMDocument2();
	CXMLDOMDocument2(IXMLDOMDocument2 *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMDocument2(const CXMLDOMDocument2 &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** node corresponding to the DOCTYPE */
	CXMLDOMDocumentType GetDoctype();

	/** info on this DOM implementation */
	CXMLDOMImplementation GetImplementation();

	/** the root of the tree */
	CXMLDOMElement GetDocumentElement();

	/** the root of the tree */
	void SetRefDocumentElement(IXMLDOMElement* rhs);

	/** create an Element node */
	CXMLDOMElement CreateElement(LPCTSTR tagName);

	/** create a DocumentFragment node */
	CXMLDOMDocumentFragment CreateDocumentFragment();

	/** create a text node */
	CXMLDOMText CreateTextNode(LPCTSTR data);

	/** create a comment node */
	CXMLDOMComment CreateComment(LPCTSTR data);

	/** create a CDATA section node */
	CXMLDOMCDATASection CreateCDATASection(LPCTSTR data);

	/** create a processing instruction node */
	CXMLDOMProcessingInstruction CreateProcessingInstruction(LPCTSTR target, LPCTSTR data);

	/** create an attribute node */
	CXMLDOMAttribute CreateAttribute(LPCTSTR name);

	/** create an entity reference node */
	CXMLDOMEntityReference CreateEntityReference(LPCTSTR name);

	/** build a list of elements by name */
	CXMLDOMNodeList GetElementsByTagName(LPCTSTR tagName);

	/** create a node of the specified node type and name */
	CXMLDOMNode CreateNode(_variant_t type, LPCTSTR name, LPCTSTR namespaceURI);

	/** retrieve node from it's ID */
	CXMLDOMNode NodeFromID(LPCTSTR idString);

	/** load document from the specified XML source */
	BOOL Load(_variant_t xmlSource);

	/** get the state of the XML document */
	long GetReadyState();

	/** get the last parser error */
	CXMLDOMParseError GetParseError();

	/** get the URL for the loaded XML document */
	CString GetUrl();

	/** flag for asynchronous download */
	BOOL GetAsync();

	/** flag for asynchronous download */
	void SetAsync(BOOL rhs);

	/** abort an asynchronous download */
	void Abort();

	/** load the document from a string */
	BOOL LoadXML(LPCTSTR bstrXML);

	/** save the document to a specified destination */
	void Save(_variant_t destination);

	/** indicates whether the parser performs validation */
	BOOL GetValidateOnParse();

	/** indicates whether the parser performs validation */
	void SetValidateOnParse(BOOL rhs);

	/** indicates whether the parser resolves references to external DTD/Entities/Schema */
	BOOL GetResolveExternals();

	/** indicates whether the parser resolves references to external DTD/Entities/Schema */
	void SetResolveExternals(BOOL rhs);

	/** indicates whether the parser preserves whitespace */
	BOOL GetPreserveWhiteSpace();

	/** indicates whether the parser preserves whitespace */
	void SetPreserveWhiteSpace(BOOL rhs);

	/** register a readystatechange event handler */
	void SetOnreadystatechange(_variant_t rhs);

	/** register an ondataavailable event handler */
	void SetOndataavailable(_variant_t rhs);

	/** register an ontransformnode event handler */
	void SetOntransformnode(_variant_t rhs);

	/** A collection of all namespaces for this document */
	CXMLDOMSchemaCollection GetNamespaces();

	/** The associated schema cache */
	VARIANT GetSchemas();

	/** The associated schema cache */
	void SetRefSchemas(_variant_t rhs);

	/** perform runtime validation on the currently loaded XML document */
	CXMLDOMParseError Validate();

	/** set the value of the named property */
	void SetProperty(LPCTSTR name, _variant_t value);

	/** get the value of the named property */
	VARIANT GetProperty(LPCTSTR name);

};



class  CXMLDOMNamedNodeMap : public CInterfaceCallingWrapper<IXMLDOMNamedNodeMap>
{
// construction/destruction
public:
	CXMLDOMNamedNodeMap();
	CXMLDOMNamedNodeMap(IXMLDOMNamedNodeMap *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMNamedNodeMap(const CXMLDOMNamedNodeMap &o);

// method wrappers
public:
	/** lookup item by name */
	CXMLDOMNode GetNamedItem(LPCTSTR name);

	/** set item by name */
	CXMLDOMNode SetNamedItem(IXMLDOMNode* newItem);

	/** remove item by name */
	CXMLDOMNode RemoveNamedItem(LPCTSTR name);

	/** collection of nodes */
	CXMLDOMNode GetItem(long index);

	/** number of nodes in the collection */
	long GetLength();

	/** lookup the item by name and namespace */
	CXMLDOMNode GetQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI);

	/** remove the item by name and namespace */
	CXMLDOMNode RemoveQualifiedItem(LPCTSTR baseName, LPCTSTR namespaceURI);

	/** get next node from iterator */
	CXMLDOMNode NextNode();

	/** reset the position of iterator */
	void Reset();

	IUnknown* Get_newEnum();

};



class  CXMLDOMNode : public CInterfaceCallingWrapper<IXMLDOMNode>
{
// construction/destruction
public:
	CXMLDOMNode();
	CXMLDOMNode(IXMLDOMNode *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMNode(const CXMLDOMNode &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

};



class  CXMLDOMNodeList : public CInterfaceCallingWrapper<IXMLDOMNodeList>
{
// construction/destruction
public:
	CXMLDOMNodeList();
	CXMLDOMNodeList(IXMLDOMNodeList *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMNodeList(const CXMLDOMNodeList &o);

// method wrappers
public:
	/** collection of nodes */
	CXMLDOMNode GetItem(long index);

	/** number of nodes in the collection */
	long GetLength();

	/** get next node from iterator */
	CXMLDOMNode NextNode();

	/** reset the position of iterator */
	void Reset();

	IUnknown* Get_newEnum();

};



class  CXMLDOMParseError : public CInterfaceCallingWrapper<IXMLDOMParseError>
{
// construction/destruction
public:
	CXMLDOMParseError();
	CXMLDOMParseError(IXMLDOMParseError *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMParseError(const CXMLDOMParseError &o);

// method wrappers
public:
	/** the error code */
	long GetErrorCode();

	/** the URL of the XML document containing the error */
	CString GetUrl();

	/** the cause of the error */
	CString GetReason();

	/** the data where the error occurred */
	CString GetSrcText();

	/** the line number in the XML document where the error occurred */
	long GetLine();

	/** the character position in the line containing the error */
	long GetLinepos();

	/** the absolute file position in the XML document containing the error */
	long GetFilepos();

};



class  CXMLHTTPRequest : public CInterfaceCallingWrapper<IXMLHTTPRequest>
{
// construction/destruction
public:
	CXMLHTTPRequest();
	CXMLHTTPRequest(IXMLHTTPRequest *p, BOOL bIncrementRefCount = FALSE);
	CXMLHTTPRequest(const CXMLHTTPRequest &o);

// method wrappers
public:
	/** Open HTTP connection */
	void Open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, _variant_t varAsync, _variant_t bstrUser, _variant_t bstrPassword);

	/** Add HTTP request header */
	void SetRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue);

	/** Get HTTP response header */
	CString GetResponseHeader(LPCTSTR bstrHeader);

	/** Get all HTTP response headers */
	CString GetAllResponseHeaders();

	/** Send HTTP request */
	void Send(_variant_t varBody);

	/** Abort HTTP request */
	void Abort();

	/** Get HTTP status code */
	long GetStatus();

	/** Get HTTP status text */
	CString GetStatusText();

	/** Get response body */
	IDispatch* GetResponseXML();

	/** Get response body */
	CString GetResponseText();

	/** Get response body */
	VARIANT GetResponseBody();

	/** Get response body */
	VARIANT GetResponseStream();

	/** Get ready state */
	long GetReadyState();

	/** Register a complete event handler */
	void SetOnreadystatechange(IDispatch* rhs);

};



class  CServerXMLHTTPRequest : public CInterfaceCallingWrapper<IServerXMLHTTPRequest>
{
// construction/destruction
public:
	CServerXMLHTTPRequest();
	CServerXMLHTTPRequest(IServerXMLHTTPRequest *p, BOOL bIncrementRefCount = FALSE);
	CServerXMLHTTPRequest(const CServerXMLHTTPRequest &o);

// method wrappers
public:
	/** Open HTTP connection */
	void Open(LPCTSTR bstrMethod, LPCTSTR bstrUrl, _variant_t varAsync, _variant_t bstrUser, _variant_t bstrPassword);

	/** Add HTTP request header */
	void SetRequestHeader(LPCTSTR bstrHeader, LPCTSTR bstrValue);

	/** Get HTTP response header */
	CString GetResponseHeader(LPCTSTR bstrHeader);

	/** Get all HTTP response headers */
	CString GetAllResponseHeaders();

	/** Send HTTP request */
	void Send(_variant_t varBody);

	/** Abort HTTP request */
	void Abort();

	/** Get HTTP status code */
	long GetStatus();

	/** Get HTTP status text */
	CString GetStatusText();

	/** Get response body */
	IDispatch* GetResponseXML();

	/** Get response body */
	CString GetResponseText();

	/** Get response body */
	VARIANT GetResponseBody();

	/** Get response body */
	VARIANT GetResponseStream();

	/** Get ready state */
	long GetReadyState();

	/** Register a complete event handler */
	void SetOnreadystatechange(IDispatch* rhs);

	/** Specify timeout settings (in milliseconds) */
	void SetTimeouts(long resolveTimeout, long connectTimeout, long sendTimeout, long receiveTimeout);

	/** Wait for asynchronous send to complete, with optional timeout (in seconds) */
	BOOL WaitForResponse(_variant_t timeoutInSeconds);

	/** Get an option value */
	VARIANT GetOption(SERVERXMLHTTP_OPTION option);

	/** Set an option value */
	void SetOption(SERVERXMLHTTP_OPTION option, _variant_t value);

};



class  CXMLDOMAttribute : public CInterfaceCallingWrapper<IXMLDOMAttribute>
{
// construction/destruction
public:
	CXMLDOMAttribute();
	CXMLDOMAttribute(IXMLDOMAttribute *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMAttribute(const CXMLDOMAttribute &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** get name of the attribute */
	CString GetName();

	/** string value of the attribute */
	VARIANT GetValue();

	/** string value of the attribute */
	void SetValue(_variant_t rhs);

};



class  CXMLDOMCDATASection : public CInterfaceCallingWrapper<IXMLDOMCDATASection>
{
// construction/destruction
public:
	CXMLDOMCDATASection();
	CXMLDOMCDATASection(IXMLDOMCDATASection *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMCDATASection(const CXMLDOMCDATASection &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** value of the node */
	CString GetData();

	/** value of the node */
	void SetData(LPCTSTR rhs);

	/** number of characters in value */
	long GetLength();

	/** retrieve substring of value */
	CString SubstringData(long offset, long count);

	/** append string to value */
	void AppendData(LPCTSTR data);

	/** insert string into value */
	void InsertData(long offset, LPCTSTR data);

	/** delete string within the value */
	void DeleteData(long offset, long count);

	/** replace string within the value */
	void ReplaceData(long offset, long count, LPCTSTR data);

	/** split the text node into two text nodes at the position specified */
	CXMLDOMText SplitText(long offset);

};



class  CXMLDOMCharacterData : public CInterfaceCallingWrapper<IXMLDOMCharacterData>
{
// construction/destruction
public:
	CXMLDOMCharacterData();
	CXMLDOMCharacterData(IXMLDOMCharacterData *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMCharacterData(const CXMLDOMCharacterData &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** value of the node */
	CString GetData();

	/** value of the node */
	void SetData(LPCTSTR rhs);

	/** number of characters in value */
	long GetLength();

	/** retrieve substring of value */
	CString SubstringData(long offset, long count);

	/** append string to value */
	void AppendData(LPCTSTR data);

	/** insert string into value */
	void InsertData(long offset, LPCTSTR data);

	/** delete string within the value */
	void DeleteData(long offset, long count);

	/** replace string within the value */
	void ReplaceData(long offset, long count, LPCTSTR data);

};



class  CXMLDOMComment : public CInterfaceCallingWrapper<IXMLDOMComment>
{
// construction/destruction
public:
	CXMLDOMComment();
	CXMLDOMComment(IXMLDOMComment *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMComment(const CXMLDOMComment &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** value of the node */
	CString GetData();

	/** value of the node */
	void SetData(LPCTSTR rhs);

	/** number of characters in value */
	long GetLength();

	/** retrieve substring of value */
	CString SubstringData(long offset, long count);

	/** append string to value */
	void AppendData(LPCTSTR data);

	/** insert string into value */
	void InsertData(long offset, LPCTSTR data);

	/** delete string within the value */
	void DeleteData(long offset, long count);

	/** replace string within the value */
	void ReplaceData(long offset, long count, LPCTSTR data);

};



class  CXMLDOMDocumentFragment : public CInterfaceCallingWrapper<IXMLDOMDocumentFragment>
{
// construction/destruction
public:
	CXMLDOMDocumentFragment();
	CXMLDOMDocumentFragment(IXMLDOMDocumentFragment *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMDocumentFragment(const CXMLDOMDocumentFragment &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

};



class  CXMLDOMDocumentType : public CInterfaceCallingWrapper<IXMLDOMDocumentType>
{
// construction/destruction
public:
	CXMLDOMDocumentType();
	CXMLDOMDocumentType(IXMLDOMDocumentType *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMDocumentType(const CXMLDOMDocumentType &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** name of the document type (root of the tree) */
	CString GetName();

	/** a list of entities in the document */
	CXMLDOMNamedNodeMap GetEntities();

	/** a list of notations in the document */
	CXMLDOMNamedNodeMap GetNotations();

};



class  CXMLDOMElement : public CInterfaceCallingWrapper<IXMLDOMElement>
{
// construction/destruction
public:
	CXMLDOMElement();
	CXMLDOMElement(IXMLDOMElement *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMElement(const CXMLDOMElement &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** get the tagName of the element */
	CString GetTagName();

	/** look up the string value of an attribute by name */
	VARIANT GetAttribute(LPCTSTR name);

	/** set the string value of an attribute by name */
	void SetAttribute(LPCTSTR name, _variant_t value);

	/** remove an attribute by name */
	void RemoveAttribute(LPCTSTR name);

	/** look up the attribute node by name */
	CXMLDOMAttribute GetAttributeNode(LPCTSTR name);

	/** set the specified attribute on the element */
	CXMLDOMAttribute SetAttributeNode(IXMLDOMAttribute* DOMAttribute);

	/** remove the specified attribute */
	CXMLDOMAttribute RemoveAttributeNode(IXMLDOMAttribute* DOMAttribute);

	/** build a list of elements by name */
	CXMLDOMNodeList GetElementsByTagName(LPCTSTR tagName);

	/** collapse all adjacent text nodes in sub-tree */
	void Normalize();

};



class  CXMLDOMEntity : public CInterfaceCallingWrapper<IXMLDOMEntity>
{
// construction/destruction
public:
	CXMLDOMEntity();
	CXMLDOMEntity(IXMLDOMEntity *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMEntity(const CXMLDOMEntity &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** the public ID */
	VARIANT GetPublicId();

	/** the system ID */
	VARIANT GetSystemId();

	/** the name of the notation */
	CString GetNotationName();

};



class  CXMLDOMEntityReference : public CInterfaceCallingWrapper<IXMLDOMEntityReference>
{
// construction/destruction
public:
	CXMLDOMEntityReference();
	CXMLDOMEntityReference(IXMLDOMEntityReference *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMEntityReference(const CXMLDOMEntityReference &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

};



class  CXMLDOMImplementation : public CInterfaceCallingWrapper<IXMLDOMImplementation>
{
// construction/destruction
public:
	CXMLDOMImplementation();
	CXMLDOMImplementation(IXMLDOMImplementation *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMImplementation(const CXMLDOMImplementation &o);

// method wrappers
public:
	BOOL HasFeature(LPCTSTR feature, LPCTSTR version);

};



class  CXMLDOMNotation : public CInterfaceCallingWrapper<IXMLDOMNotation>
{
// construction/destruction
public:
	CXMLDOMNotation();
	CXMLDOMNotation(IXMLDOMNotation *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMNotation(const CXMLDOMNotation &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** the public ID */
	VARIANT GetPublicId();

	/** the system ID */
	VARIANT GetSystemId();

};



class  CXMLDOMProcessingInstruction : public CInterfaceCallingWrapper<IXMLDOMProcessingInstruction>
{
// construction/destruction
public:
	CXMLDOMProcessingInstruction();
	CXMLDOMProcessingInstruction(IXMLDOMProcessingInstruction *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMProcessingInstruction(const CXMLDOMProcessingInstruction &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** the target */
	CString GetTarget();

	/** the data */
	CString GetData();

	/** the data */
	void SetData(LPCTSTR rhs);

};



class  CXMLDOMSchemaCollection : public CInterfaceCallingWrapper<IXMLDOMSchemaCollection>
{
// construction/destruction
public:
	CXMLDOMSchemaCollection();
	CXMLDOMSchemaCollection(IXMLDOMSchemaCollection *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMSchemaCollection(const CXMLDOMSchemaCollection &o);

// method wrappers
public:
	/** add a new schema */
	void Add(LPCTSTR namespaceURI, _variant_t var);

	/** lookup schema by namespaceURI */
	CXMLDOMNode Get(LPCTSTR namespaceURI);

	/** remove schema by namespaceURI */
	void Remove(LPCTSTR namespaceURI);

	/** number of schemas in collection */
	long GetLength();

	/** Get namespaceURI for schema by index */
	CString GetNamespaceURI(long index);

	/** copy & merge other collection into this one */
	void AddCollection(IXMLDOMSchemaCollection* otherCollection);

	IUnknown* Get_newEnum();

};



//class  CXMLDOMSchemaCollection2 : public CInterfaceCallingWrapper<IXMLDOMSchemaCollection2>
//{
// construction/destruction
//public:
//	CXMLDOMSchemaCollection2();
//	CXMLDOMSchemaCollection2(IXMLDOMSchemaCollection2 *p, BOOL bIncrementRefCount = FALSE);
//	CXMLDOMSchemaCollection2(const CXMLDOMSchemaCollection2 &o);

// method wrappers
//public:
	/** add a new schema */
//	void Add(LPCTSTR namespaceURI, _variant_t var);

	/** lookup schema by namespaceURI */
//	CXMLDOMNode Get(LPCTSTR namespaceURI);

	/** remove schema by namespaceURI */
//	void Remove(LPCTSTR namespaceURI);

	/** number of schemas in collection */
//	long GetLength();

	/** Get namespaceURI for schema by index */
//	CString GetNamespaceURI(long index);

	/** copy & merge other collection into this one */
//	void AddCollection(IXMLDOMSchemaCollection* otherCollection);

//	IUnknown* Get_newEnum();

//	void Validate();

//	void SetValidateOnLoad(BOOL rhs);

//	BOOL GetValidateOnLoad();

//	ISchema* GetSchema(LPCTSTR namespaceURI);

//	ISchemaItem* GetDeclaration(IXMLDOMNode* node);

//};



class  CXMLDOMSelection : public CInterfaceCallingWrapper<IXMLDOMSelection>
{
// construction/destruction
public:
	CXMLDOMSelection();
	CXMLDOMSelection(IXMLDOMSelection *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMSelection(const CXMLDOMSelection &o);

// method wrappers
public:
	/** collection of nodes */
	CXMLDOMNode GetItem(long index);

	/** number of nodes in the collection */
	long GetLength();

	/** get next node from iterator */
	CXMLDOMNode NextNode();

	/** reset the position of iterator */
	void Reset();

	IUnknown* Get_newEnum();

	/** selection expression */
	CString GetExpr();

	/** selection expression */
	void SetExpr(LPCTSTR rhs);

	/** nodes to apply selection expression to */
	CXMLDOMNode GetContext();

	/** nodes to apply selection expression to */
	void SetRefContext(IXMLDOMNode* rhs);

	/** gets the next node without advancing the list position */
	CXMLDOMNode PeekNode();

	/** checks to see if the node matches the pattern */
	CXMLDOMNode Matches(IXMLDOMNode* pNode);

	/** removes the next node */
	CXMLDOMNode RemoveNext();

	/** removes all the nodes that match the selection */
	void RemoveAll();

	/** clone this object with the same position and context */
	CXMLDOMSelection Clone();

	/** get the value of the named property */
	VARIANT GetProperty(LPCTSTR name);

	/** set the value of the named property */
	void SetProperty(LPCTSTR name, _variant_t value);

};



class  CXMLDOMText : public CInterfaceCallingWrapper<IXMLDOMText>
{
// construction/destruction
public:
	CXMLDOMText();
	CXMLDOMText(IXMLDOMText *p, BOOL bIncrementRefCount = FALSE);
	CXMLDOMText(const CXMLDOMText &o);

// method wrappers
public:
	/** name of the node */
	CString GetNodeName();

	/** value stored in the node */
	VARIANT GetNodeValue();

	/** value stored in the node */
	void SetNodeValue(_variant_t rhs);

	/** the node's type */
	DOMNodeType GetNodeType();

	/** parent of the node */
	CXMLDOMNode GetParentNode();

	/** the collection of the node's children */
	CXMLDOMNodeList GetChildNodes();

	/** first child of the node */
	CXMLDOMNode GetFirstChild();

	/** last child of the node */
	CXMLDOMNode GetLastChild();

	/** left sibling of the node */
	CXMLDOMNode GetPreviousSibling();

	/** right sibling of the node */
	CXMLDOMNode GetNextSibling();

	/** the collection of the node's attributes */
	CXMLDOMNamedNodeMap GetAttributes();

	/** insert a child node */
	CXMLDOMNode InsertBefore(IXMLDOMNode* newChild, _variant_t refChild);

	/** replace a child node */
	CXMLDOMNode ReplaceChild(IXMLDOMNode* newChild, IXMLDOMNode* oldChild);

	/** remove a child node */
	CXMLDOMNode RemoveChild(IXMLDOMNode* childNode);

	/** append a child node */
	CXMLDOMNode AppendChild(IXMLDOMNode* newChild);

	BOOL HasChildNodes();

	/** document that contains the node */
	CXMLDOMDocument GetOwnerDocument();

	CXMLDOMNode CloneNode(BOOL deep);

	/** the type of node in string form */
	CString GetNodeTypeString();

	/** text content of the node and subtree */
	CString GetText();

	/** text content of the node and subtree */
	void SetText(LPCTSTR rhs);

	/** indicates whether node is a default value */
	BOOL GetSpecified();

	/** pointer to the definition of the node in the DTD or schema */
	CXMLDOMNode GetDefinition();

	/** get the strongly typed value of the node */
	VARIANT GetNodeTypedValue();

	/** get the strongly typed value of the node */
	void SetNodeTypedValue(_variant_t rhs);

	/** the data type of the node */
	VARIANT GetDataType();

	/** the data type of the node */
	void SetDataType(LPCTSTR rhs);

	/** return the XML source for the node and each of its descendants */
	CString GetXml();

	/** apply the stylesheet to the subtree */
	CString TransformNode(IXMLDOMNode* stylesheet);

	/** execute query on the subtree */
	CXMLDOMNodeList SelectNodes(LPCTSTR queryString);

	/** execute query on the subtree */
	CXMLDOMNode SelectSingleNode(LPCTSTR queryString);

	/** has sub-tree been completely parsed */
	BOOL GetParsed();

	/** the URI for the namespace applying to the node */
	CString GetNamespaceURI();

	/** the prefix for the namespace applying to the node */
	CString GetPrefix();

	/** the base name of the node (nodename with the prefix stripped off) */
	CString GetBaseName();

	/** apply the stylesheet to the subtree, returning the result through a document or a stream */
	void TransformNodeToObject(IXMLDOMNode* stylesheet, _variant_t outputObject);

	/** value of the node */
	CString GetData();

	/** value of the node */
	void SetData(LPCTSTR rhs);

	/** number of characters in value */
	long GetLength();

	/** retrieve substring of value */
	CString SubstringData(long offset, long count);

	/** append string to value */
	void AppendData(LPCTSTR data);

	/** insert string into value */
	void InsertData(long offset, LPCTSTR data);

	/** delete string within the value */
	void DeleteData(long offset, long count);

	/** replace string within the value */
	void ReplaceData(long offset, long count, LPCTSTR data);

	/** split the text node into two text nodes at the position specified */
	CXMLDOMText SplitText(long offset);

};



class  CXSLProcessor : public CInterfaceCallingWrapper<IXSLProcessor>
{
// construction/destruction
public:
	CXSLProcessor();
	CXSLProcessor(IXSLProcessor *p, BOOL bIncrementRefCount = FALSE);
	CXSLProcessor(const CXSLProcessor &o);

// method wrappers
public:
	/** XML input tree to transform */
	void SetInput(_variant_t rhs);

	/** XML input tree to transform */
	VARIANT GetInput();

	/** template object used to create this processor object */
	CXSLTemplate GetOwnerTemplate();

	/** set XSL mode and it's namespace */
	void SetStartMode(LPCTSTR mode, LPCTSTR namespaceURI);

	/** starting XSL mode */
	CString GetStartMode();

	/** namespace of starting XSL mode */
	CString GetStartModeURI();

	/** custom stream object for transform output */
	void SetOutput(_variant_t rhs);

	/** custom stream object for transform output */
	VARIANT GetOutput();

	/** start/resume the XSL transformation process */
	BOOL Transform();

	/** reset state of processor and abort current transform */
	void Reset();

	/** current state of the processor */
	long GetReadyState();

	/** set <xsl:param> values */
	void AddParameter(LPCTSTR baseName, _variant_t parameter, LPCTSTR namespaceURI);

	/** pass object to stylesheet */
	void AddObject(IDispatch* obj, LPCTSTR namespaceURI);

	/** current stylesheet being used */
	CXMLDOMNode GetStylesheet();

};



class  CXSLTemplate : public CInterfaceCallingWrapper<IXSLTemplate>
{
// construction/destruction
public:
	CXSLTemplate();
	CXSLTemplate(IXSLTemplate *p, BOOL bIncrementRefCount = FALSE);
	CXSLTemplate(const CXSLTemplate &o);

// method wrappers
public:
	/** stylesheet to use with processors */
	void SetRefStylesheet(IXMLDOMNode* rhs);

	/** stylesheet to use with processors */
	CXMLDOMNode GetStylesheet();

	/** create a new processor object */
	CXSLProcessor CreateProcessor();

};



class  CDOMDocumentClass
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CDOMDocument26Class
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CDOMDocument30Class
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CDOMDocument40Class
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CFreeThreadedDOMDocumentClass
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CFreeThreadedDOMDocument26Class
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CFreeThreadedDOMDocument30Class
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CFreeThreadedDOMDocument40Class
{
// static operations
public:
	static CXMLDOMDocument2 CreateXMLDOMDocument2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
	static XMLDOMDocumentEvents* CreateXMLDOMDocumentEvents(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLSchemaCacheClass
{
// static operations
public:
	static CXMLDOMSchemaCollection CreateXMLDOMSchemaCollection(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLSchemaCache26Class
{
// static operations
public:
	static CXMLDOMSchemaCollection CreateXMLDOMSchemaCollection(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLSchemaCache30Class
{
// static operations
public:
	static CXMLDOMSchemaCollection CreateXMLDOMSchemaCollection(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLSchemaCache40Class
{
// static operations
public:
	static CXMLDOMSchemaCollection2 CreateXMLDOMSchemaCollection2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXSLTemplateClass
{
// static operations
public:
	static CXSLTemplate CreateXSLTemplate(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXSLTemplate26Class
{
// static operations
public:
	static CXSLTemplate CreateXSLTemplate(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXSLTemplate30Class
{
// static operations
public:
	static CXSLTemplate CreateXSLTemplate(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXSLTemplate40Class
{
// static operations
public:
	static CXSLTemplate CreateXSLTemplate(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLHTTPClass
{
// static operations
public:
	static CXMLHTTPRequest CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLHTTP26Class
{
// static operations
public:
	static CXMLHTTPRequest CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLHTTP30Class
{
// static operations
public:
	static CXMLHTTPRequest CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



class  CXMLHTTP40Class
{
// static operations
public:
	static CXMLHTTPRequest CreateXMLHTTPRequest(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
public:
	static const CLSID m_ClsId;
};



//class  CServerXMLHTTPClass
//{
// static operations
//public:
//	static IServerXMLHTTPRequest2* CreateServerXMLHTTPRequest2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
//public:
//	static const CLSID m_ClsId;
//};



//class  CServerXMLHTTP30Class
//{
// static operations
//public:
//	static IServerXMLHTTPRequest2* CreateServerXMLHTTPRequest2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
//public:
	//static const CLSID m_ClsId;
//};



//class  CServerXMLHTTP40Class
//{
// static operations
//public:
//	static IServerXMLHTTPRequest2* CreateServerXMLHTTPRequest2(LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);

// static attributes
//public:
//	static const CLSID m_ClsId;
//};



#endif
