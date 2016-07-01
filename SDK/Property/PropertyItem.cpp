// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "PropertyList.h"
#include "PropertyItem.h"
#include "PropertyTextEdit.h"
#include "PropertyBoolEdit.h"
#include "PropertyListEdit.h"
#include "ComponentList.h"
#include "FontList.h"
#include "atldlgs.h"
#include "atltheme.h"
#include "_util.h"
#include <algorithm>
#include <cfile.h>
#include "CTextEditDlg.h"
#include <string>
//////////////////////////////////////////////////////////////////////////
CTheme buttonTheme;
void RegisterThemes();
/////////////////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API void DrawPropertyValueText(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx=-1);
PROPERTY_API void DrawPropertyValueBool(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx=-1);
PROPERTY_API void DrawPropertyValuebool(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx=-1);
PROPERTY_API void DrawPropertyValueColor(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx=-1);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API LPCTSTR DecorateName(LPCTSTR n)
{
    static CString name;
    name=n;
    int idx=name.ReverseFind('.');
    if(idx!=-1)
        name.Delete(0,idx+1);
    return name;
}
///////////////////////////////////////////////////////////////////////////////////////////////
class CConversion
{
public:
	CConversion(void);
	CConversion(const CConversion &);
	CConversion(LPCTSTR,ValToStr,StrToVal,CCustomVal *cv=NULL,ValToStr vds=NULL,StrToVal dsv=NULL);
	int Find(long);
	int Find(LPCTSTR);
	int DecorateFind(LPCTSTR);
	
	CString type;
	ValToStr valtostr;
	StrToVal strtoval;

	ValToStr valtodecstr;
	StrToVal decstrtoval;

	CCustomVal * customval;
};

inline CConversion::CConversion(void):valtostr(NULL),strtoval(NULL),customval(NULL),valtodecstr(NULL),
decstrtoval(NULL)
{
}

inline CConversion::CConversion(LPCTSTR t,ValToStr vs,StrToVal sv,CCustomVal * cv,ValToStr vds,StrToVal dsv):type(t),valtostr(vs),strtoval(sv),customval(cv),
valtodecstr(vds),decstrtoval(dsv)
{
	if(valtodecstr==NULL)
		valtodecstr=valtostr;
	if(decstrtoval==NULL)
		decstrtoval=strtoval;
}

inline CConversion::CConversion(const CConversion & c):type(c.type),valtostr(c.valtostr),strtoval(c.strtoval),customval(c.customval),
valtodecstr(c.valtodecstr),decstrtoval(c.decstrtoval)
{
}

int CConversion::Find(long id)
{
	if(customval)
	{
		for(register int i = 0; customval[i].id!=-1; i++ )
			if(customval[i].id==id)
				return i;
	}
	return -1;
}

int CConversion::Find(LPCTSTR name)
{
	if(customval)
	{
		for(register int i = 0; customval[i].id!=-1; i++ )
			if(customval[i].name==name)
				return i;
	}
	return -1;
}

int CConversion::DecorateFind(LPCTSTR name)
{
	if(customval)
	{
		for(register int i = 0; customval[i].id!=-1; i++ )
			if(customval[i].decorate==name)
				return i;
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEditor
{
public:
	CEditor(void);
	CEditor(const CEditor &);
	CEditor(LPCTSTR,InPropEdit,ExPropEdit=NULL);
	
	CString type;
	InPropEdit	internal;
	ExPropEdit	external;
};

inline CEditor::CEditor(void):internal(NULL),external(NULL)
{
}

inline CEditor::CEditor(LPCTSTR t,InPropEdit i,ExPropEdit e):type(t),internal(i),
				external(e)
{
}

inline CEditor::CEditor(const CEditor& c):type(c.type),internal(c.internal),external(c.external)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////
typedef CSimpleArray<CEditor> CCEditorArray;
class CEditorContainer
{
public:
	CEditorContainer(void);
	virtual InPropEdit GetInPropEdit(LPCTSTR type);
	virtual ExPropEdit GetExPropEdit(LPCTSTR type);
	virtual void AddEditor(LPCTSTR type,InPropEdit,ExPropEdit=NULL);
protected:
	int FindEditor(LPCTSTR str);

	CCEditorArray editors;
};

static CEditorContainer editorcontainer;

CEditorContainer::CEditorContainer(void)
{
}

int CEditorContainer::FindEditor(LPCTSTR str)
{
	for(register int i = 0; i < editors.GetSize() ; i++)
		if(editors[i].type==str)
			return i;
	return -1;
}

void CEditorContainer::AddEditor(LPCTSTR type,InPropEdit i,ExPropEdit e)
{
	if(FindEditor(type)==-1)
	{
		CEditor temp(type,i,e);
		editors.Add(temp);
	}
}

InPropEdit CEditorContainer::GetInPropEdit(LPCTSTR type)
{
	int idx=FindEditor(type);
	if(idx!=-1)
		return editors[idx].internal;
	return NULL;
}

ExPropEdit CEditorContainer::GetExPropEdit(LPCTSTR type)
{
	int idx=FindEditor(type);
	if(idx!=-1)
		return editors[idx].external;
	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////////
class CDrawer
{
public:
	CDrawer(void);
	CDrawer(const CDrawer &);
	CDrawer(LPCTSTR,DrawPropertyValue);
	
	CString type;
	DrawPropertyValue drawer;
};

inline CDrawer::CDrawer(void):drawer(NULL)
{
}

inline CDrawer::CDrawer(LPCTSTR t,DrawPropertyValue dp):type(t),drawer(dp)
{
}

inline CDrawer::CDrawer(const CDrawer& c):type(c.type),drawer(c.drawer)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////
typedef CSimpleArray<CDrawer> CCDrawerArray;
class CDrawerContainer
{
public:
	CDrawerContainer(void);
	void Add(LPCTSTR type,DrawPropertyValue);
	DrawPropertyValue Get(LPCTSTR type);
protected:
	int Find(LPCTSTR str);
	
	CCDrawerArray drawers;
};

static CDrawerContainer darwercontainer;

CDrawerContainer::CDrawerContainer(void)
{
}

int CDrawerContainer::Find(LPCTSTR str)
{
	for(register int i = 0; i < drawers.GetSize() ; i++)
		if(drawers[i].type==str)
			return i;
		return -1;
}

void CDrawerContainer::Add(LPCTSTR type,DrawPropertyValue dp)
{
	if(Find(type)==-1)
	{
		CDrawer temp(type,dp);
		drawers.Add(temp);
	}
}

DrawPropertyValue CDrawerContainer::Get(LPCTSTR type)
{
	int idx=Find(type);
	if(idx!=-1)
		return drawers[idx].drawer;
	return DrawPropertyValueText;
}
////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::map<CString,CConversion> CConversionArray;
typedef std::map<CString,CConversion>::iterator ConversionIterator;
typedef std::pair<CString,CConversion> Conversion_Pair;
class ConversionContainer
{
public:
	ConversionContainer(void);
	LPCTSTR ValueToString(LPCTSTR type,void * val);
	void * StringToValue(const LPCTSTR type,LPCTSTR str);

	LPCTSTR ValueToDecorateString(LPCTSTR type,void * val);
	void * DecorateStringToValue(LPCTSTR type,LPCTSTR str);

	void AddConversion(LPCTSTR type,ValToStr,StrToVal,CCustomVal *cv=NULL,ValToStr vds=NULL,StrToVal dsv=NULL);
	CCustomVal * GetCustomVal(LPCTSTR type);
	long GetCustomValCount(LPCTSTR type); 
protected:
	CConversion * FindConversion(LPCTSTR str);

	CConversionArray conversions;
};

static ConversionContainer conversioncontainer;

ConversionContainer::ConversionContainer(void)
{
}

CConversion * ConversionContainer::FindConversion(LPCTSTR str)
{
	ConversionIterator idx=conversions.find(str);
	if(idx!=conversions.end())
	{
		return &idx->second;
	}
	return NULL;
}

void ConversionContainer::AddConversion(LPCTSTR type,ValToStr vs,StrToVal sv,CCustomVal *cv,ValToStr vds,StrToVal dsv)
{
	if(FindConversion(type)==NULL)
		conversions.insert(Conversion_Pair(type,CConversion(type,vs,sv,cv,vds,dsv)));
}

LPCTSTR ConversionContainer::ValueToString(LPCTSTR type,void * val)
{
	CConversion * idx=FindConversion(type);
	if(idx!=NULL)
		return idx->valtostr(val);

	return _T("");
}

void * ConversionContainer::StringToValue(LPCTSTR type,LPCTSTR str)
{
	CConversion * idx=FindConversion(type);
	if(idx!=NULL)
		return idx->strtoval(str);
	return 0;
}

LPCTSTR ConversionContainer::ValueToDecorateString(LPCTSTR type,void * val)
{
	CConversion * idx=FindConversion(type);
	if(idx!=NULL)
		return idx->valtodecstr(val);
	return NULL;
}

void * ConversionContainer::DecorateStringToValue(LPCTSTR type,LPCTSTR str)
{
	CConversion * idx=FindConversion(type);
	if(idx!=NULL)
		return idx->decstrtoval(str);
	return NULL;
}

CCustomVal * ConversionContainer::GetCustomVal(LPCTSTR type)
{
	CConversion * idx=FindConversion(type);
	if(idx!=NULL)
		return idx->customval;
	return NULL;
}

long ConversionContainer::GetCustomValCount(LPCTSTR type)
{
	CConversion * idx=FindConversion(type);
	if(idx!=NULL)
	{
		CCustomVal * values=idx->customval;
		long i;
		for(i = 0; values[i].name!=NULL; i++)
			;
		return i;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
void EndlToStr(CString & str)
{
	int pos=str.Find(_T("\\n"));
	for(;pos < str.GetLength() && pos!=-1;)
	{
		if(pos!=-1)
		{
			str.Delete(pos,2);
			str.Insert(pos,_T('\n'));
            
		}
		pos=str.Find(_T("\\n"),pos);
	}
}

void StrToEndl(CString & str)
{
	int pos=str.Find(_T('\n'));
	for(;pos < str.GetLength() && pos!=-1;)
	{
		if(pos!=-1)
		{
			str.Delete(pos,1);
			str.Insert(pos,_T("\\n"));
		}
		pos=str.Find(_T('\n'),pos);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API LPCTSTR CharPtrToString(LPCTSTR* val)
{
   return *val;
}

PROPERTY_API LPTSTR* StringToCharPtr(LPCTSTR val)
{
	static CString str;
	str=val;
	static LPTSTR temp;
	temp=(LPTSTR)(LPCTSTR)str;
    return &temp;
}
//////////////////////////////////////////////////////////////////////////
PROPERTY_API LPCTSTR StrToString(CString *val)
{
	static CString str;
	str.Empty();
	str=(LPCTSTR)*val;
	StrToEndl(str);
    return str;
}

PROPERTY_API CString *  StringToStr(LPCTSTR val)
{
	static CString str;
	str.Empty();
	str=val;
	EndlToStr(str);
    return &str;
}

PROPERTY_API LPCTSTR PathToString(CString *val)
{
    static CString str;
    str.Empty();
    str=(LPCTSTR)*val;
    return str;
}

PROPERTY_API CString *  StringToPath(LPCTSTR val)
{
    static CString str;
    str.Empty();
    str=val;
    return &str;
}

//////////////////////////////////////////////////////////////////////////
PROPERTY_API LPCTSTR  IntToString(int *val)
{
    static CString str;
    str.Format(_T("%d"), *val);
    return str;
}

PROPERTY_API long * StringToInt(LPCTSTR str)
{
	static long val;
    val=_tstoi(str);
	return &val;
}

PROPERTY_API LPCTSTR  DWORDToString(DWORD *val)
{
	static CString str;
	str.Format(_T("%u"), *val);
	return str;
}

PROPERTY_API DWORD * StringToDWORD(LPCTSTR str)
{
	static DWORD val;
	val = std::stoul(str, nullptr, 0);
	return &val;
}

PROPERTY_API LPCTSTR FloatToString(float *val)
{
	static CString str;
	str.Format(_T("%f"),*val);
	return str;
}

PROPERTY_API float * StringToFloat(const CString & str)
{
	static float val;
    val=(float)_tstof(str);
	return &val;
}

PROPERTY_API LPCTSTR DoubleToString(double * val)
{
	static CString str;
	str.Format(_T("%f"),*val);
	return str;
}

PROPERTY_API double * StringToDouble(const CString &str)
{
	static double val;
    val=_tstof(str);
	return &val;
}

PROPERTY_API LPCTSTR BoolToString(BOOL * val)
{
    static CString str;
	if (*val)
		str=_T("true");
	else
		str = _T("false");
	
    return str;
}

PROPERTY_API BOOL * StringToBool(LPCTSTR _str)
{
	static BOOL val;
	CString str(_str);
	if (str.CompareNoCase(_T("true"))==0)
		val=TRUE;
	else
		val= FALSE;
	return &val;
}

PROPERTY_API LPCTSTR boolToString(bool * val)
{
    static CString str;
    if (*val)
        str=_T("true");
    else
        str = _T("false");

    return str;
}

PROPERTY_API bool * StringTobool(LPCTSTR _str)
{
    static bool val;
    CString str(_str);
    if (str.CompareNoCase(_T("true"))==0)
        val=true;
    else
        val= false;
    return &val;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
PropertyBase::PropertyBase(LPCTSTR n,LPCTSTR t):
level(0),expand(FALSE),name(n),type(t),published(TRUE),readOnly(FALSE), inited(false)
{
}

PropertyBase::PropertyBase(const PropertyBase & prop):
level(prop.level),
expand(prop.expand),
name(prop.name),
type(prop.type),
published(prop.published),
readOnly(prop.readOnly),
inited(prop.inited)
{
}

PropertyBase::~PropertyBase(void)
{
    if(HasChild()) {
        PropertyVectorIter iter;
        for ( iter = child.begin( ); iter != child.end( ); iter++ )
        {
            if(*iter!=NULL)
                delete *iter;
        }
    }
	child.clear();
}

LPCTSTR PropertyBase::GetName(void)
{
	return name;
}

LPCTSTR PropertyBase::GetType(void)
{
	return type;
}

BOOL  PropertyBase::GetExpand(void)	
{
	return expand;
}

void  PropertyBase::SetExpand(BOOL b)
{
	expand=b;
}

long  PropertyBase::GetLevel(void)
{
	return level;
}

void  PropertyBase::SetLevel(long l)
{
	level=l;
}

BOOL PropertyBase::HasChild(void)
{
	return child.empty()==false;
}

PropertyVector & PropertyBase::GetChild(void)
{
	return child;
}

void PropertyBase::SetPublished(BOOL p)
{
	published=p;
}

BOOL PropertyBase::GetPublished(void)
{
	return published;
}

void PropertyBase::SetReadOnly(BOOL p)
{
    readOnly=p;
}

BOOL PropertyBase::GetReadOnly(void)
{
    return readOnly;
}

void PropertyBase::AddChild(PropertyBase * p)
{
    child.push_back(p);
	CString str;
	str.Format(_T("%s.%s"),GetName(),p->GetName());
	p->name=str;
}

void PropertyBase::DrawProperty(HDC hDC,const CRect & DrawRc,int idx)
{
	DrawPropertyValue dp=GetDrawProperty(type);
	if(dp)
		dp(hDC,DrawRc,this,idx);
}

LPCTSTR PropertyBase::ToString()
{
	return ValueToString(type,GetValue(true));
}

void  PropertyBase::FromString(LPCTSTR str)
{
	SetValue(StringToValue(type,str), true);
}

void PropertyBase::Update()
{
	if (inited)
		Set();//set loaded value to component
	else
		Get();//get default value from component

    if(HasChild())
    {
        PropertyVectorIter iter;
        for ( iter = child.begin( ); iter != child.end( ); iter++ )
            (*iter)->Update();
    }
	inited = true;
}

void PropertyBase::Sort()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
CProperties::~CProperties(void)
{
    PropertyVectorIter iter;
    for ( iter = properties.begin( ); iter != properties.end( ); iter++ )
        if(*iter != NULL)
            delete *iter;
	properties.clear();
}

CProperties::CProperties(Component * c):className(NULL),component(c),topIndex(0)
{
}

CProperties::CProperties(LPCTSTR classname,Component * c):className(classname),
component(c),topIndex(0)
{
}

CProperties::CProperties(const CProperties &prop):properties(prop.properties),className(prop.className),component(prop.component),
topIndex(prop.topIndex)
{
    *this=prop;
}

CProperties  & CProperties::operator =(LPCTSTR n)
{
   className=n;
   return *this;
}

CProperties  & CProperties::operator =(const CProperties& p)
{
    className=p.className;
    topIndex=p.topIndex;
    for (PropertyVectorIter iter = ((CProperties&)p).properties.begin( ); iter != p.properties.end( ); iter++ )
    {
		PropertyBase * prop=FindByName((*iter)->GetName());
		if(prop)
			prop->FromString((*iter)->ToString());

		if((*iter)->HasChild())
            CopyChild(*iter);
    }

    return *this;
}

void CProperties::CopyChild(PropertyBase * parent)
{
    PropertyVectorIter iter;
    for ( iter = parent->GetChild().begin( ); iter != parent->GetChild().end( ); iter++ )
    {
        PropertyBase * prop=FindByName((*iter)->GetName());
        if(prop)
            prop->FromString((*iter)->ToString());
        
        if((*iter)->HasChild())
            CopyChild(*iter);
    }
}

LPCTSTR CProperties::GetClassName(void)
{
   return className;
}

BOOL CProperties::IsEmpty(void)
{
   return properties.empty()==false;
}

void CProperties::Add(PropertyBase * p)
{
    if(FindByName(p->GetName()))
    {
        AtlMessageBox(NULL,(LPCTSTR)MakeString(_T("Property \"%s\" is already defined."),p->GetName()),_T("WTLBuilder"));
        return;
    }
    p->objprop=this;
    properties.push_back(p);
	propMap.insert(Property_Pair(p->GetName(),p));
}

void CProperties::AddChild(LPCTSTR Parent,PropertyBase *Prop)
{
	PropertyBase * prop=FindByName(Parent);	
	if(prop)
	{
		prop->AddChild(Prop);
        Prop->objprop=this;
		propMap.insert(Property_Pair(Prop->GetName(),Prop));
	}
}

void CProperties::AddChild(PropertyBase *Parent,PropertyBase *Prop)
{
	if(Parent && Prop)
	{
		Parent->AddChild(Prop);
        Prop->objprop=this;
		propMap.insert(Property_Pair(Prop->GetName(),Prop));
	}
}

void CProperties::Load(CXMLDOMNode &Node)
{
	long Count=Node.GetAttributes().GetLength();
	for(long i=0; i < Count; i++)
	{
		CString propName=Node.GetAttributes().GetItem(i).GetNodeName();
		if(propName.IsEmpty())
			continue;
		PropertyBase * prop=FindByName(propName);
		if(prop)
			prop->Load(Node.GetAttributes().GetItem(i));
		
	}

	CXMLDOMNodeList Childs=Node.GetChildNodes();
	if(Childs!=NULL)
	{
		long Count=Childs.GetLength();
		for(long i=0; i < Count; i++)
		{
			CXMLDOMNode Child=Childs.GetItem(i);
			CString propName=Child.GetNodeName();
			if(propName.IsEmpty())
				continue;
			PropertyBase * prop=FindByName(propName);
			if(prop)
			{
				if(prop->HasChild())
					LoadChild(Child,prop,propName);
			}
		}

	}
}

void CProperties::Save(CXMLDOMNode &Node)
{
	CString cmpPage;
	CString cmpName;
	ExtractName(className,cmpPage,cmpName);

	CXMLDOMAttribute PageAttr(Node.GetOwnerDocument().CreateAttribute(_T("Page")));
	PageAttr.SetText(cmpPage);
	Node.GetAttributes().SetNamedItem(PageAttr);

	CXMLDOMAttribute TypeAttr(Node.GetOwnerDocument().CreateAttribute(_T("Class")));
	TypeAttr.SetText(cmpName);
	Node.GetAttributes().SetNamedItem(TypeAttr);

    PropertyVectorIter iter;
    for ( iter = properties.begin( ); iter != properties.end( ); iter++ )
	{
		(*iter)->Save(Node);
		if((*iter)->HasChild())
			SaveChild(Node,*iter);
	}
}

void CProperties::LoadChild(CXMLDOMNode &Node,PropertyBase * Parentprop,CString &_fullName)
{
	if(Parentprop==NULL && Node==NULL)
		return;
	long Count=Node.GetAttributes().GetLength();
	for(long i=0; i < Count; i++)
	{
		CString propName=Node.GetAttributes().GetItem(i).GetNodeName();
        CString fullName=_fullName;
        fullName+=_T(".")+propName;
		PropertyBase * prop=FindByName(fullName);
		if(prop)
			prop->Load(Node.GetAttributes().GetItem(i));
	}

	CXMLDOMNodeList Childs=Node.GetChildNodes();
	if(Childs!=NULL)
	{
		long Count=Childs.GetLength();
		for(long i=0; i < Count; i++)
		{
            CString fullName=_fullName;
			CXMLDOMNode Child=Childs.GetItem(i);
			CString propName=Child.GetNodeName();
			if(propName.IsEmpty())
				continue;
            fullName+=_T(".")+propName;
			PropertyBase * prop=FindByName(fullName);
			if(prop)
			{
				if(prop->HasChild())
					LoadChild(Child,prop,fullName);
			}
		}
	}
}

void CProperties::SaveChild(CXMLDOMNode &Node,PropertyBase * Parentprop)
{
	if(Parentprop==NULL)
		return;
    CXMLDOMNode Item(Node.GetOwnerDocument().CreateNode(_variant_t((long)NODE_ELEMENT),DecorateName(Parentprop->GetName()),NULL));
	Node.AppendChild(Item);

    PropertyVectorIter iter;
    for ( iter = Parentprop->GetChild().begin( ); iter != Parentprop->GetChild().end( ); iter++ )
	{
		(*iter)->Save(Item);
		if((*iter)->HasChild())
			SaveChild(Item,*iter);
	}
}

//надо искать и в субпропертях !!
PropertyBase * CProperties::FindByName(LPCTSTR n)
{
	//PropertyNameDecorator propName(n);
	//CString str(propName.Name());
	//for(PropertyBase * temp=head; temp; temp=temp->GetNext())
	//{
	//	if(temp->GetName() == str)
	//	{
	//		if(propName.Eof())
	//			return temp;
	//		else
	//		{
	//			if(temp->HasSub())
	//				return temp->FindByName(propName);
	//		}
	//	}
	//}

    /*list <PropertyBase *>::iterator iter;
    for ( iter = properties.begin( ); iter != properties.end( ); iter++ )
	{
		if(_tcscmp((*iter)->GetName(),n))
		{
			if((*iter)->HasChild())
			{
				PropertyBase * temp1=(*iter)->FindByName(n);
				if(temp1)
					return temp1;
			}
		}
		else
			return *iter;
	}*/

	propertyMapIter idx=propMap.find(CString(n));
	if(idx!=propMap.end())
		return idx->second;

	return NULL;
}

void CProperties::SetPublished(LPCTSTR name,BOOL p)
{
	PropertyBase * prop=FindByName(name);
	if(prop)
		prop->SetPublished(p);
}

void CProperties::SetReadOnly(LPCTSTR name,BOOL p)
{
    PropertyBase * prop=FindByName(name);
    if(prop)
        prop->SetReadOnly(p);
}

void CProperties::Remove(PropertyBase *p)
{
	if(p!=NULL)
	{
        PropertyVectorIter iter=std::find(properties.begin(),properties.end(),p);
        if(iter!=properties.end())
            properties.erase(iter);
        propMap.erase(p->GetName());
		delete p;
	}
}

void CProperties::Remove(LPCTSTR n)	
{
	Remove(FindByName(n));
}

LPCTSTR CProperties::GetPropValueStr(LPCTSTR name)
{
	PropertyBase * prop=FindByName(name);
	if(prop)
		return prop->ToString();
	return NULL;
}

void CProperties::Update()
{
	Sort();
    PropertyVectorIter iter;
    for ( iter = properties.begin( ); iter != properties.end( ); iter++ )
		(*iter)->Update();
}

void CProperties::setPropValue(LPCTSTR name,void * val)
{
	PropertyBase * prop=FindByName(name);
	if(prop)
		prop->SetValue(val, false);
}

void *CProperties::getPropValue(LPCTSTR name)
{
	PropertyBase * prop=FindByName(name);
	if(prop)
		return prop->GetValue(false);
	return NULL;
}

long CProperties::Count()
{
	return (long)properties.size();
}

void CProperties::Sort()
{
	std::sort(properties.begin(), properties.end(), compare);
}

void CProperties::SetTopIndex(int index)
{
    if(index != -1)
        topIndex=index;
    else
        topIndex=0;
}
int CProperties::GetTopIndex()
{
    return topIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API LPCTSTR ValueToString(LPCTSTR type,void * val)
{
	return conversioncontainer.ValueToString(type,val);
}

PROPERTY_API void * StringToValue(LPCTSTR type,LPCTSTR str)
{
	return conversioncontainer.StringToValue(type,str);
}

PROPERTY_API LPCTSTR ValueToDecorateString(LPCTSTR type,void * val)
{
	return conversioncontainer.ValueToDecorateString(type,val);
}

PROPERTY_API void * DecorateStringToValue(LPCTSTR type,LPCTSTR str)
{
	return conversioncontainer.DecorateStringToValue(type,str);
}

PROPERTY_API CCustomVal * GetCustomVal(LPCTSTR type)
{
	return conversioncontainer.GetCustomVal(type); 
}

PROPERTY_API long GetCustomValCount(LPCTSTR type)
{
	return conversioncontainer.GetCustomValCount(type); 
}

PROPERTY_API void RegisterConversion(LPCTSTR type,ValToStr vs,StrToVal sv,CCustomVal *cv,ValToStr vds,StrToVal dsv)
{
	conversioncontainer.AddConversion(type,vs,sv,cv,vds,dsv);
}

PROPERTY_API InPropEdit GetInPropEdit(LPCTSTR type)
{
	return editorcontainer.GetInPropEdit(type);
}

PROPERTY_API ExPropEdit GetExPropEdit(LPCTSTR type)
{
	return editorcontainer.GetExPropEdit(type);
}

PROPERTY_API void RegisterEdit(LPCTSTR type,InPropEdit i,ExPropEdit e)
{
	editorcontainer.AddEditor(type,i,e);
}

PROPERTY_API void RegisterDrawProperty(LPCTSTR type,DrawPropertyValue dp)
{
	darwercontainer.Add(type,dp);
}

PROPERTY_API DrawPropertyValue GetDrawProperty(LPCTSTR type)
{
	return darwercontainer.Get(type);
}
//standart property/////////////////////////////////////////////////////////////////////////////
//printer property
BEGIN_LIST_PROPERTY(Orientation)
	LIST_ITEM(1,Portrait)
	LIST_ITEM(2,Landscape)
END_LIST_ITEM(Orientation)

BEGIN_LIST_PROPERTY(PaperSize)
	LIST_ITEM(DMPAPER_LETTER,Letter)
	LIST_ITEM(DMPAPER_LEGAL,Legal)
	LIST_ITEM(DMPAPER_A4,A4)
	LIST_ITEM(DMPAPER_CSHEET,C)
	LIST_ITEM(DMPAPER_DSHEET,D)
	LIST_ITEM(DMPAPER_ESHEET,E)
	LIST_ITEM(DMPAPER_LETTERSMALL,LetterSmall)
	LIST_ITEM(DMPAPER_TABLOID,Tabloid)
	LIST_ITEM(DMPAPER_LEDGER,Ledger)
	LIST_ITEM(DMPAPER_STATEMENT,Statement)
	LIST_ITEM(DMPAPER_EXECUTIVE,Executive)
	LIST_ITEM(DMPAPER_A3,A3)
	LIST_ITEM(DMPAPER_A4SMALL,A4Small)
	LIST_ITEM(DMPAPER_A5,A5)
	LIST_ITEM(DMPAPER_B4,B4)
	LIST_ITEM(DMPAPER_B5,B5)
	LIST_ITEM(DMPAPER_FOLIO,Folio)
	LIST_ITEM(DMPAPER_QUARTO,Quarto)
	LIST_ITEM(DMPAPER_10X14,10-by14-inch) 
	LIST_ITEM(DMPAPER_11X17,11-by17-inch)
	LIST_ITEM(0xFFFF,Custom)
END_LIST_ITEM(PaperSize)

BEGIN_LIST_PROPERTY(CommonCtrlAlign)
	LIST_ITEM_DECORATE(0,0,None)
	LIST_ITEM_DECORATE(CCS_BOTTOM,CCS_BOTTOM,Bottom)
	LIST_ITEM_DECORATE(CCS_TOP,CCS_TOP,Top)
	LIST_ITEM_DECORATE(CCS_LEFT,CCS_LEFT,Left)
	LIST_ITEM_DECORATE(CCS_RIGHT,CCS_RIGHT,Right)
END_LIST_ITEM(CommonCtrlAlign)

BEGIN_LIST_PROPERTY(WindowBorderStyle)
	LIST_ITEM_DECORATE(0,0,None)
    LIST_ITEM_DECORATE(WS_BORDER,WS_BORDER,Thin)
	LIST_ITEM_DECORATE(WS_THICKFRAME,WS_THICKFRAME,Resizing)
	LIST_ITEM_DECORATE(WS_DLGFRAME,WS_DLGFRAME,Dialog Frame)
END_LIST_ITEM(WindowBorderStyle)

BEGIN_LIST_PROPERTY(WindowStyle)
	LIST_ITEM_DECORATE(WS_CHILD,WS_CHILD,Child)
	LIST_ITEM_DECORATE(WS_POPUP,WS_POPUP,Popup)
	LIST_ITEM_DECORATE(WS_OVERLAPPED,WS_OVERLAPPED,Overlapped)
END_LIST_ITEM(WindowStyle)


BEGIN_LIST_PROPERTY(CColorref)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_SCROLLBAR,COLOR_SCROLLBAR,Scrollbar)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_BACKGROUND,COLOR_BACKGROUND,BackGround)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_ACTIVECAPTION,COLOR_ACTIVECAPTION,ActiveCaption)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_INACTIVECAPTION,COLOR_INACTIVECAPTION,InactiveCaption)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_MENU,COLOR_MENU,Menu)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_WINDOW,COLOR_WINDOW,Window)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_WINDOWFRAME,COLOR_WINDOWFRAME,WindowFrame)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_MENUTEXT,COLOR_MENUTEXT,MenuText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_WINDOWTEXT,COLOR_WINDOWTEXT,WindowText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_CAPTIONTEXT,COLOR_CAPTIONTEXT,CaptionText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_ACTIVEBORDER,COLOR_ACTIVEBORDER,ActiveBorder)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_INACTIVEBORDER,COLOR_INACTIVEBORDER,InactiveBorder)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_APPWORKSPACE,COLOR_APPWORKSPACE,AppWorkSpace)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_HIGHLIGHT,COLOR_HIGHLIGHT,HighLight)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_HIGHLIGHTTEXT,COLOR_HIGHLIGHTTEXT,HighLightText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_BTNFACE,COLOR_BTNFACE,BtnFace)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_BTNSHADOW,COLOR_BTNSHADOW,BtnShadow)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_GRAYTEXT,COLOR_GRAYTEXT,GrayText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_BTNTEXT,COLOR_BTNTEXT,BtnText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_INACTIVECAPTIONTEXT,COLOR_INACTIVECAPTIONTEXT,InactiveCaptionText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_BTNHIGHLIGHT,COLOR_BTNHIGHLIGHT,BtnHighLight)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_3DDKSHADOW,COLOR_3DDKSHADOW,3DdkShadow)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_3DLIGHT,COLOR_3DLIGHT,3DLight)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_INFOTEXT,COLOR_INFOTEXT,InfoText)
	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_INFOBK,COLOR_INFOBK,InfoBK)
//	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_HOTLIGHT,COLOR_HOTLIGHT,HotLight)
//	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_GRADIENTACTIVECAPTION,COLOR_GRADIENTACTIVECAPTION,GradientActiveCaption)
//	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_GRADIENTINACTIVECAPTION,COLOR_GRADIENTINACTIVECAPTION,GradientInactiveCaption)
//	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_MENUHILIGHT,COLOR_MENUHILIGHT,MenuHILight)
//	LIST_ITEM_DECORATE(SYSCOLOR_SIGN|COLOR_MENUBAR,COLOR_MENUBAR,MenuBar)           
	LIST_ITEM_DECORATE(CLR_DEFAULT,CLR_DEFAULT,Default)           
	LIST_ITEM_DECORATE(CLR_NONE,CLR_NONE,None)           
END_LIST_ITEM(CColorref)


BEGIN_LIST_PROPERTY(SystemColor)
	LIST_ITEM_DECORATE(COLOR_SCROLLBAR,COLOR_SCROLLBAR,Scrollbar)
	LIST_ITEM_DECORATE(COLOR_BACKGROUND,COLOR_BACKGROUND,BackGround)
	LIST_ITEM_DECORATE(COLOR_ACTIVECAPTION,COLOR_ACTIVECAPTION,ActiveCaption)
	LIST_ITEM_DECORATE(COLOR_INACTIVECAPTION,COLOR_INACTIVECAPTION,InactiveCaption)
	LIST_ITEM_DECORATE(COLOR_MENU,COLOR_MENU,Menu)
	LIST_ITEM_DECORATE(COLOR_WINDOW,COLOR_WINDOW,Window)
	LIST_ITEM_DECORATE(COLOR_WINDOWFRAME,COLOR_WINDOWFRAME,WindowFrame)
	LIST_ITEM_DECORATE(COLOR_MENUTEXT,COLOR_MENUTEXT,MenuText)
	LIST_ITEM_DECORATE(COLOR_WINDOWTEXT,COLOR_WINDOWTEXT,WindowText)
	LIST_ITEM_DECORATE(COLOR_CAPTIONTEXT,COLOR_CAPTIONTEXT,CaptionText)
	LIST_ITEM_DECORATE(COLOR_ACTIVEBORDER,COLOR_ACTIVEBORDER,ActiveBorder)
	LIST_ITEM_DECORATE(COLOR_INACTIVEBORDER,COLOR_INACTIVEBORDER,InactiveBorder)
	LIST_ITEM_DECORATE(COLOR_APPWORKSPACE,COLOR_APPWORKSPACE,AppWorkSpace)
	LIST_ITEM_DECORATE(COLOR_HIGHLIGHT,COLOR_HIGHLIGHT,HighLight)
	LIST_ITEM_DECORATE(COLOR_HIGHLIGHTTEXT,COLOR_HIGHLIGHTTEXT,HighLightText)
	LIST_ITEM_DECORATE(COLOR_BTNFACE,COLOR_BTNFACE,BtnFace)
	LIST_ITEM_DECORATE(COLOR_BTNSHADOW,COLOR_BTNSHADOW,BtnShadow)
	LIST_ITEM_DECORATE(COLOR_GRAYTEXT,COLOR_GRAYTEXT,GrayText)
	LIST_ITEM_DECORATE(COLOR_BTNTEXT,COLOR_BTNTEXT,BtnText)
	LIST_ITEM_DECORATE(COLOR_INACTIVECAPTIONTEXT,COLOR_INACTIVECAPTIONTEXT,InactiveCaptionText)
	LIST_ITEM_DECORATE(COLOR_BTNHIGHLIGHT,COLOR_BTNHIGHLIGHT,BtnHighLight)
	LIST_ITEM_DECORATE(COLOR_3DDKSHADOW,COLOR_3DDKSHADOW,3DdkShadow)
	LIST_ITEM_DECORATE(COLOR_3DLIGHT,COLOR_3DLIGHT,3DLight)
	LIST_ITEM_DECORATE(COLOR_INFOTEXT,COLOR_INFOTEXT,InfoText)
	LIST_ITEM_DECORATE(COLOR_INFOBK,COLOR_INFOBK,InfoBK)
//	LIST_ITEM_DECORATE(COLOR_HOTLIGHT,COLOR_HOTLIGHT,HotLight)
//	LIST_ITEM_DECORATE(COLOR_GRADIENTACTIVECAPTION,COLOR_GRADIENTACTIVECAPTION,GradientActiveCaption)
//	LIST_ITEM_DECORATE(COLOR_GRADIENTINACTIVECAPTION,COLOR_GRADIENTINACTIVECAPTION,GradientInactiveCaption)
//	LIST_ITEM_DECORATE(COLOR_MENUHILIGHT,COLOR_MENUHILIGHT,MenuHILight)
//	LIST_ITEM_DECORATE(COLOR_MENUBAR,COLOR_MENUBAR,MenuBar)           
	LIST_ITEM_DECORATE(CLR_DEFAULT,CLR_DEFAULT,Default)           
	LIST_ITEM_DECORATE(CLR_NONE,CLR_NONE,None)           
END_LIST_ITEM(SystemColor)

//LIST_ITEM_DECORATE(WS_BORDER,WS_BORDER,Sizing)
///////////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API void ExColorEdit(HWND parent,PropertyBase *prop,LPARAM)
{
	CColorref color=0;
	if(prop)
	{
		color=*((CColorref *)prop->GetValue(true));
		CColorDialog Dlg(color,CC_ANYCOLOR|CC_RGBINIT,parent);
		if(Dlg.DoModal(GetDesktopWindow())==IDOK)
		{
			color=Dlg.GetColor();
			prop->SetValue(&color, true);
			::UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
		}
	}
}
PROPERTY_API LPCTSTR ColorToStringDec(CColorref * color)
{
    static CString _cs;
	for(int i=0;i < (sizeof(CColorrefTable)/sizeof(CCustomVal)-1); i++)
		if(*color==(CColorref&)CColorrefTable[i].id)
			return CColorrefTable[i].decorate;

	_cs.Format(_T("RGB(0x%02X,0x%02X,0x%02X)"), color->GetRed(),color->GetGreen(),color->GetBlue());
	return _cs;
}

PROPERTY_API CColorref * StringToColorDec(LPCTSTR _str)
{
	static CColorref cr=0;
	for(int i=0;i < (sizeof(CColorrefTable)/sizeof(CCustomVal)-1); i++)
		if(_tcscmp(_str,CColorrefTable[i].decorate)==0)
			return (CColorref *)&CColorrefTable[i].id;
		

	int r = 0, g = 0, b = 0;
	CString str(_str);
	CString cs1;
	cs1 = str.Mid(6,2);
    _stscanf_s(cs1, _T("%02X"), &r);
	cs1 = str.Mid(11,2);
	_stscanf_s(cs1, _T("%02X"), &g);
	cs1 = str.Mid(16,2);
	_stscanf_s(cs1, _T("%02X"), &b);
	cr = RGB(r,g,b);
	return &cr;
}

PROPERTY_API LPCTSTR ColorToString(CColorref * color)
{
    static CString _cs;
	for(int i=0;i < (sizeof(CColorrefTable)/sizeof(CCustomVal)-1); i++)
		if(*color==(CColorref&)CColorrefTable[i].id)
			return CColorrefTable[i].name;
	
    _cs.Format(_T("RGB(0x%02X,0x%02X,0x%02X)"), color->GetRed(),color->GetGreen(),color->GetBlue());
	return _cs;
}

PROPERTY_API CColorref * StringToColor(LPCTSTR _str)
{
	static CColorref cr=0;
	for(int i=0;i < (sizeof(CColorrefTable)/sizeof(CCustomVal)-1); i++)
		if(_tcscmp(_str,CColorrefTable[i].name)==0)
			return (CColorref *)&CColorrefTable[i].id;
		

	int r = 0, g = 0, b = 0;
	CString str(_str);
	CString cs1;
	cs1 = str.Mid(6,2);
	_stscanf_s(cs1, _T("%02X"), &r);
	cs1 = str.Mid(11,2);
	_stscanf_s(cs1, _T("%02X"), &g);
	cs1 = str.Mid(16,2);
	_stscanf_s(cs1, _T("%02X"), &b);
	cr = RGB(r,g,b);
	return &cr;
}
//////////////////////////////////////////////////////////////////////////
inline int ArraySize(_TCHAR * array[])
{
    int size = 0;
    if(array!=NULL)
    {
        for(;;size++)
        {
            if(array[size] == NULL)
                break;
        }
    }
    //return size !=0 ? size+1 : 0;
	return size;
}
//extFilter = ico not *.ico
PROPERTY_API void ExFileDialogEditor(HWND parent,PropertyBase *prop, _TCHAR * fileFilter[],_TCHAR * extFilter[])
{
    int fileFilterSize = ArraySize(fileFilter);
    int extFilterSize = ArraySize(extFilter);
    if(prop && fileFilterSize != 0 && extFilterSize != 0)
    {
        Component *comp=NULL;
        SendEvent(evGetActiveForm,&comp);
        CString formPath;
        SendEvent(evGetFormFileName,comp,&formPath);
        CPath location(formPath);
        location.SetCurDir();
        location.AddDir(_T("res"));
        CString str=location.GetLocation();
        CPath imageFile(*(CString *)prop->GetValue(true));
        CString ext(extFilter[0]);
        _TCHAR *FileFilter=fileFilter[0];

        if(imageFile.IsFilePath() == TRUE)
        {
            for(int i =0; i < extFilterSize ; i++)
                if(imageFile.GetExt().CompareNoCase(extFilter[i]) == 0)
                {
                    ext = extFilter[i];
                    FileFilter=fileFilter[i];
                    break;
                }
        }
        ext.Insert(0,_T("*."));
        CFileDialog dlg(TRUE,ext,imageFile.GetFileName(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,FileFilter);
        dlg.m_ofn.lpstrInitialDir=(LPCTSTR)str;
        if(dlg.DoModal(GetDesktopWindow())==IDOK)
        {
            str=dlg.m_szFileName;
            _TCHAR relativePath[MAX_PATH];
            PathRelativePathTo(relativePath,(LPCTSTR)formPath,0,(LPCTSTR)str,0);
            str=relativePath;

            prop->SetValue(&str, true);
            UpdateProperty(prop->GetName());
            SendEvent(evAddUndo,NULL);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API CString ExFileDialogEditor(HWND parent,_TCHAR * fileFilter[],_TCHAR * extFilter[])
{
    int fileFilterSize = ArraySize(fileFilter);
    int extFilterSize = ArraySize(extFilter);
    if(fileFilterSize != 0 && extFilterSize != 0)
    {
        Component *comp=NULL;
        SendEvent(evGetActiveForm,&comp);
        CString formPath;
        SendEvent(evGetFormFileName,comp,&formPath);
        CPath location(formPath);
        location.SetCurDir();
        location.AddDir(_T("res"));
        CString str=location.GetLocation();
        CString ext(extFilter[0]);
        ext.Insert(0,_T("*."));
        _TCHAR *FileFilter=fileFilter[0];
        CFileDialog dlg(TRUE,ext,_T(""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,FileFilter);
        dlg.m_ofn.lpstrInitialDir=(LPCTSTR)str;
        if(dlg.DoModal(GetDesktopWindow())==IDOK)
        {
            str=dlg.m_szFileName;
            _TCHAR relativePath[MAX_PATH];
            PathRelativePathTo(relativePath,(LPCTSTR)formPath,0,(LPCTSTR)str,0);
            str=relativePath;
            SendEvent(evAddUndo,NULL);
            return str;
        }
    }
    return "";
}
////////////////////////////////////////////////////////////////////////////////////////////////////

PROPERTY_API void ExImageBmpIcoFile(HWND parent,PropertyBase *prop)
{
    static _TCHAR * fileFilter[] = {
        _T("Bitmap Files (*.bmp)\0*.bmp\0Icon Files (*.ico)\0*.ico\0"),
        _T("Icon Files (*.ico)\0*.ico\0Bitmap Files (*.bmp)\0*.bmp\0"),
        NULL};

    static _TCHAR * extFilter[] = {
            _T("bmp"),
            _T("ico"),
            NULL};

    ExFileDialogEditor(GetDesktopWindow()/*parent*/,prop,fileFilter,extFilter);
}

PROPERTY_API void ExImageBmpFile(HWND parent,PropertyBase *prop)
{
    static _TCHAR * fileFilter[] = {
        _T("Bitmap Files (*.bmp)\0*.bmp\0Icon Files (*.ico)\0*.ico\0"),
        NULL};

        static _TCHAR * extFilter[] = {
            _T("bmp"),
            NULL};
    ExFileDialogEditor(GetDesktopWindow()/*parent*/,prop,fileFilter,extFilter);
}

PROPERTY_API void ExImageIcoFile(HWND parent,PropertyBase *prop)
{
    static _TCHAR * fileFilter[] = {
        _T("Icon Files (*.ico)\0*.ico\0Bitmap Files (*.bmp)\0*.bmp\0"),
        NULL};

    static _TCHAR * extFilter[] = {
            _T("ico"),
            NULL};

    ExFileDialogEditor(GetDesktopWindow()/*parent*/,prop,fileFilter,extFilter);
}

PROPERTY_API void ExTextFile(HWND parent,PropertyBase *prop)
{
    if(prop == NULL)
        return;
    static _TCHAR * fileFilter[] = {
        _T("Text Files (*.txt)\0*.txt\0Text Files (*.txt)\0*.txt\0"),
        _T("All Files (*.*)\0*.*\0All Files (*.*)\0*.*\0"),
        NULL};

    static _TCHAR * extFilter[] = {
            _T("txt"),
            _T("*"),
            NULL};

    CString path = ExFileDialogEditor(GetDesktopWindow()/*parent*/,fileFilter,extFilter);
    if(path.IsEmpty() == FALSE)
    {
        CString str = LoadString(path);
        prop->SetValue(&str, true);
        UpdateProperty(prop->GetName());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterLang();
void InitProperty(void)
{
    //CString with ext loading text file
	RegisterConversion(_T("Text"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("Text"),CInplaceTextEdit::CreateEdit,(ExPropEdit)CTextEditDlg::TextEditDlg);
	RegisterDrawProperty(_T("Text"),DrawPropertyValueText);

	RegisterConversion(_T("CString"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("CString"),CInplaceTextEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("CString"),DrawPropertyValueText);

    RegisterConversion(_T("Path"),(ValToStr)PathToString,(StrToVal)StringToPath,NULL);
    RegisterEdit(_T("Path"),CInplaceTextEdit::CreateEdit,NULL);
    RegisterDrawProperty(_T("Path"),DrawPropertyValueText);

	RegisterConversion(_T("LPTSTR"),(ValToStr)CharPtrToString,(StrToVal)StringToCharPtr,NULL);
	RegisterEdit(_T("LPTSTR"),CInplaceTextEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("LPTSTR"),DrawPropertyValueText);

	RegisterConversion(_T("LPCTSTR"),(ValToStr)CharPtrToString,(StrToVal)StringToCharPtr,NULL);
	RegisterEdit(_T("LPCTSTR"),CInplaceTextEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("LPCTSTR"),DrawPropertyValueText);

	RegisterConversion(_T("int"),(ValToStr)IntToString,(StrToVal)StringToInt,NULL);
	RegisterEdit(_T("int"),CInplaceIntEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("int"),DrawPropertyValueText);
	
	RegisterConversion(_T("long"),(ValToStr)IntToString,(StrToVal)StringToInt,NULL);
	RegisterEdit(_T("long"),CInplaceIntEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("long"),DrawPropertyValueText);

	RegisterConversion(_T("DWORD"),(ValToStr)DWORDToString,(StrToVal)StringToDWORD,NULL);
	RegisterEdit(_T("DWORD"),CInplaceIntEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("DWORD"),DrawPropertyValueText);

	RegisterConversion(_T("BOOL"),(ValToStr)BoolToString,(StrToVal)StringToBool,NULL);
	RegisterEdit(_T("BOOL"),CInplaceBoolEdit::CreateEdit,NULL);
	RegisterDrawProperty(_T("BOOL"),DrawPropertyValueBool);

    RegisterConversion(_T("bool"),(ValToStr)boolToString,(StrToVal)StringTobool,NULL);
    RegisterEdit(_T("bool"),CInplaceboolEdit::CreateEdit,NULL);
    RegisterDrawProperty(_T("bool"),DrawPropertyValuebool);

	RegisterConversion(_T("ComponentName"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
    RegisterEdit(_T("ComponentName"),CComponentListEdit::CreateInplaceEdit,NULL);
	RegisterDrawProperty(_T("ComponentName"),DrawPropertyValueText);

	RegisterConversion(_T("PageName"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	//RegisterEdit("ComponentName",CComponentListEdit::CreateInplaceEdit,NULL); see it in Panel.cpp
	RegisterDrawProperty(_T("PageName"),DrawPropertyValueText);

	RegisterConversion(_T("FontFaceName"),(ValToStr)StrToString,(StrToVal)StringToStr,NULL);
	RegisterEdit(_T("FontFaceName"),CFontListEdit::CreateEdit,NULL); 
	RegisterDrawProperty(_T("FontFaceName"),DrawPropertyValueText);

	RegisterConversion(_T("ImageBmpIcoFileNameType"),(ValToStr)PathToString,(StrToVal)StringToPath,NULL);
	RegisterEdit(_T("ImageBmpIcoFileNameType"),CInplaceTextEdit::CreateEdit,(ExPropEdit)ExImageBmpIcoFile);
	RegisterDrawProperty(_T("ImageBmpIcoFileNameType"),DrawPropertyValueText);

    RegisterConversion(_T("ImageBmpFileNameType"),(ValToStr)PathToString,(StrToVal)StringToPath,NULL);
    RegisterEdit(_T("ImageBmpFileNameType"),CInplaceTextEdit::CreateEdit,(ExPropEdit)ExImageBmpFile);
    RegisterDrawProperty(_T("ImageBmpFileNameType"),DrawPropertyValueText);

    RegisterConversion(_T("ImageIcoFileNameType"),(ValToStr)PathToString,(StrToVal)StringToPath,NULL);
    RegisterEdit(_T("ImageIcoFileNameType"),CInplaceTextEdit::CreateEdit,(ExPropEdit)ExImageIcoFile);
    RegisterDrawProperty(_T("ImageIcoFileNameType"),DrawPropertyValueText);
    
	REGISTER_LIST_PROPERTY(PaperSize)
	REGISTER_LIST_PROPERTY(CommonCtrlAlign)
	REGISTER_LIST_PROPERTY(WindowBorderStyle)
	REGISTER_LIST_PROPERTY(WindowStyle)
	REGISTER_LIST_PROPERTY_2(CColorref,ColorToString,StringToColor,ColorToStringDec,StringToColorDec,ExColorEdit)
    REGISTER_LIST_PROPERTY(SystemColor)
	RegisterGDIProp();
	RegisterLang();
}
///////////////////////////////////////////////////////////////////////////////////////////////
PROPERTY_API void DrawPropertyValueText(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx)
{
	 CDCHandle dc(hDC);
	 CRect rc(DrawRc);
	 rc.bottom-=1;
	 rc.top-=1;
	 LPCTSTR text=ValueToDecorateString(prop->GetType(),prop->GetValue(true));
	 dc.DrawText(text,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}

PROPERTY_API void DrawPropertyValueColor(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx)
{
	 CDCHandle dc(hDC);
	 CRect rc(DrawRc);
	 rc.DeflateRect(1,1);	
	 dc.FillSolidRect(rc,*((CColorref *)prop->GetValue(true)));
}

PROPERTY_API void DrawPropertyValueBool(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx)
{
	 CDCHandle dc(hDC);
	 CRect rc(DrawRc);
     
  	 rc.bottom-=2;
	 rc.top+=1;
	 rc.right=rc.left+(rc.bottom-rc.top);
     if(buttonTheme.IsThemeNull())
	     dc.DrawFrameControl(&rc,DFC_BUTTON|DFCS_BUTTONCHECK,*((BOOL *)prop->GetValue(true))? DFCS_CHECKED : 0);
     else
         buttonTheme.DrawThemeBackground(dc,BP_CHECKBOX,
             (*((BOOL *)prop->GetValue(true))? CBS_CHECKEDNORMAL:CBS_UNCHECKEDNORMAL),&rc,NULL);

	 LPCTSTR text=ValueToDecorateString(prop->GetType(),prop->GetValue(true));
	 rc=DrawRc;
	 //rc.bottom-=1;
	 //rc.top-=1;
	 rc.left=rc.left+(rc.bottom-rc.top);//+2;
     dc.DrawText(text,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}

PROPERTY_API void DrawPropertyValuebool(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx)
{
    CDCHandle dc(hDC);
    CRect rc(DrawRc);

    rc.bottom-=2;
    rc.top+=1;
    rc.right=rc.left+(rc.bottom-rc.top);
    if(buttonTheme.IsThemeNull())
        dc.DrawFrameControl(&rc,DFC_BUTTON|DFCS_BUTTONCHECK,*((bool *)prop->GetValue(true))? DFCS_CHECKED : 0);
    else
        buttonTheme.DrawThemeBackground(dc,BP_CHECKBOX,
        (*((BOOL *)prop->GetValue(true))? CBS_CHECKEDNORMAL:CBS_UNCHECKEDNORMAL),&rc,NULL);

    LPCTSTR text=ValueToDecorateString(prop->GetType(),prop->GetValue(true));
    rc=DrawRc;
    rc.bottom-=1;
    rc.top-=1;
    rc.left=rc.left+(rc.bottom-rc.top);//+2;
    dc.DrawText(text,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}

PROPERTY_API void DrawPropertyValueListText(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx)
{
	CDCHandle dc(hDC);
	CRect rc(DrawRc);
	rc.bottom-=1;
	rc.top-=1;

	LPCTSTR text;
	if(idx==-1)
		text=ValueToDecorateString(prop->GetType(),prop->GetValue(true));
	else
	{
		CCustomVal * values=GetCustomVal(prop->GetType());
		if(values && idx < GetCustomValCount(prop->GetType()))
			text=values[idx].decorate;
	}
	dc.DrawText(text,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}

//////////////////////////////////////////////////////////////////////////
void RegisterThemes()
{
    static BOOL Initialized=FALSE;
    if(Initialized==FALSE)
    {
        //buttonTheme.OpenThemeData(GetDesktopWindow(),L"BUTTON");
        buttonTheme.OpenThemeData(NULL,L"BUTTON");

        Initialized=TRUE;
    }
}