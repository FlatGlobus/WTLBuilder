// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __PROPERTYDEF_H
#define __PROPERTYDEF_H
#pragma warning( disable:4251)  

#include "Property.h"
#include <atlframe.h>
#include <atlctrls.h>
#include "atldispa.h"
#include "DOMxml.h"
#include "atltheme.h"
#include <map>
#include <vector>

typedef CString ComponentName;
typedef CString Text;
typedef DWORD LangID;

class CColorref;
class Component;

typedef COLORREF SystemColor; 

class PROPERTY_API CCustomVal
{
public:
	long  id;
	LPTSTR name;
	LPTSTR decorate;//для представления в проперти контроле
};

class PROPERTY_API PropertyBase;
class CPropertyList;

typedef PROPERTY_API LPCTSTR (*ValToStr)(void *);
typedef PROPERTY_API void * (*StrToVal)(LPCTSTR);
typedef PROPERTY_API void  (*DrawProperty)(HDC hDC,const CRect & DrawRc,PropertyBase *);
typedef PROPERTY_API HWND  (*InPropEdit)(HWND parent,CRect & place,PropertyBase *,CPoint& mouse,LPARAM data);//inplace property edit
typedef PROPERTY_API void  (*ExPropEdit)(HWND parent,PropertyBase *,LPARAM data);//external property edit
typedef PROPERTY_API void  (*DrawPropertyValue)(HDC hDC,const CRect & DrawRc,PropertyBase *,int idx);//idx is used for drawing CCustomVal//idx=-1

PROPERTY_API LPCTSTR ValueToString(LPCTSTR type,void *val);
PROPERTY_API void * StringToValue(LPCTSTR type,LPCTSTR str);

PROPERTY_API LPCTSTR ValueToDecorateString(LPCTSTR type,void * val);
PROPERTY_API void *DecorateStringToValue(LPCTSTR type,LPCTSTR str);

PROPERTY_API void RegisterConversion(LPCTSTR type,ValToStr,StrToVal,CCustomVal *cv=NULL,ValToStr vds=NULL,StrToVal dsv=NULL);
PROPERTY_API CCustomVal * GetCustomVal(LPCTSTR type);
PROPERTY_API long GetCustomValCount(LPCTSTR type);

PROPERTY_API void RegisterEdit(LPCTSTR type,InPropEdit,ExPropEdit);
PROPERTY_API InPropEdit GetInPropEdit(LPCTSTR type);
PROPERTY_API ExPropEdit GetExPropEdit(LPCTSTR type);

PROPERTY_API void RegisterDrawProperty(LPCTSTR type,DrawPropertyValue);
PROPERTY_API DrawPropertyValue GetDrawProperty(LPCTSTR type);
PROPERTY_API void DrawPropertyValueListText(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx);
PROPERTY_API LPCTSTR DecorateName(LPCTSTR n);

typedef std::vector<PropertyBase *> PropertyVector;
typedef std::vector<PropertyBase *>::iterator PropertyVectorIter; 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PROPERTY_API PropertyBase
{
public:
	PropertyBase(LPCTSTR,LPCTSTR);
    PropertyBase(const PropertyBase &);
	virtual ~PropertyBase(void);
	virtual void Load(CXMLDOMNode &){};
	virtual void Save(CXMLDOMNode &){};
	   
	friend class CProperties;

	void DrawProperty(HDC hDC,const CRect & DrawRc,int idx=-1);
	
	LPCTSTR ToString();
	void  FromString(LPCTSTR);

	LPCTSTR GetName(void);
	LPCTSTR GetType(void);

	BOOL  GetExpand(void);	
	void  SetExpand(BOOL);

	long  GetLevel(void);
	void  SetLevel(long);

	virtual void Get(void){};
	virtual void Set(void){};

	virtual void * GetValue(bool native){return NULL;};
	virtual void SetValue(void *val,bool native){};
	virtual void *Self(void){return NULL;};

	BOOL HasChild(void);
    PropertyVector & GetChild();
	void AddChild(PropertyBase *);
	void SetPublished(BOOL);
	BOOL GetPublished(void);

    void SetReadOnly(BOOL);
    BOOL GetReadOnly(void);

	void Update();
    CProperties* GetProperties() {return objprop; }
    void Sort();
    inline bool operator<( const PropertyBase & p ) const {return name < p.name; } 
    inline bool operator>( const PropertyBase & p ) const {return name > name; }
protected:
    PropertyVector  child;
    CString			name;
	CString		  	type;
	long			level;
	BOOL			expand;
	BOOL			published;
    BOOL            readOnly;
    CProperties*    objprop;
	bool inited; // true если значение было установлено в компонент, устанавливается в компонент после  вызова update
};

inline bool compare( const PropertyBase* l, const PropertyBase* r ) { return *l < *r; }

template <class Object,class Value>
class PROPERTY_API Property:public PropertyBase
{
public:
	typedef Value (Object::*GetMethod)(void);
	typedef void  (Object::*SetMethod)(Value);
protected:
	Object * self;
	GetMethod	getmethod;
	SetMethod	setmethod;
	Value value;
public:
	Property(LPCTSTR _name, LPCTSTR _type, GetMethod _get, SetMethod _set, Object * _self, Value defValue):PropertyBase(_name, _type)
		, getmethod(_get), setmethod(_set), self(_self), value(defValue)
	{
		inited = true;
	}

	Property(LPCTSTR _name, LPCTSTR _type, GetMethod _get, SetMethod _set, Object * _self):PropertyBase(_name, _type)
		, getmethod(_get), setmethod(_set), self(_self)
	{
		inited = false;
		memset(&value, 0, sizeof(Value));
	}

    Property(const Property & prop):PropertyBase(prop), value(prop.value), getmethod(prop.getmethod), setmethod(prop.setmethod), self(prop.self)
    {
    }

	virtual void * GetValue(bool native)
	{
		if(inited == true && native == true)
			Get();
		return (void *)&value;
	}
	
	virtual void SetValue(void * v, bool native)
	{
		if(v)
		{
			value=(Value &)*((Value *)v);
			if(inited == true && native == true)
				Set();
		}
	}

	virtual void Get(void)
	{
		if(self && getmethod)
			value=(self->*(getmethod))();
	}

	virtual void  Set(void)
	{
		if(self && setmethod)
			(self->*(setmethod))(value);
	}

	virtual void *Self(void)
	{
		return static_cast<void *>(self);
	}

	virtual void Load(CXMLDOMNode & Node)
	{
		inited = true;
		SetValue(StringToValue(type,Node.GetText()),false);
	}

	virtual void Save(CXMLDOMNode & Node)
	{
		CXMLDOMAttribute PageAttr(Node.GetOwnerDocument().CreateAttribute(DecorateName(name)));
		PageAttr.SetText(ValueToString(type,GetValue(true)));
		Node.GetAttributes().SetNamedItem(PageAttr);
	}

};
//////////////////////////////////////////////////////////////////////////////////////////////
typedef std::map<CString,PropertyBase *> PropertyMap;
typedef std::map<CString,PropertyBase *>::iterator propertyMapIter;
typedef std::pair<CString,PropertyBase *> Property_Pair;

class PROPERTY_API CProperties
{
private:
	void setPropValue(LPCTSTR, void *);
	void *getPropValue(LPCTSTR name);
public:
	CProperties(Component *);
	CProperties(LPCTSTR,Component *);
    CProperties(const CProperties &);

	virtual ~CProperties(void);
	void Add(PropertyBase *);

	void Remove(PropertyBase *);
	void Remove(LPCTSTR);	

	void AddChild(LPCTSTR Parent,PropertyBase *Prop);
	void AddChild(PropertyBase *Parent,PropertyBase *Prop);
	virtual void Load(CXMLDOMNode &);
	virtual void Save(CXMLDOMNode &);

	PropertyBase * FindByName(LPCTSTR);
	PropertyBase * operator [](LPCTSTR str)	{return FindByName(str);}
	CProperties  & operator =(LPCTSTR);
    CProperties  & operator =(const CProperties& p);

	BOOL IsEmpty(void);
	LPCTSTR GetClassName(void);
	void SetPublished(LPCTSTR,BOOL);
    void SetReadOnly(LPCTSTR,BOOL);
	LPCTSTR GetPropValueStr(LPCTSTR name);
	void Update();
	long Count();
    virtual Component * GetComponent()      {return component;}
    PropertyVectorIter begin() {return properties.begin();}
    PropertyVectorIter end()   {return properties.end();}
    void Sort();
    void SetTopIndex(int);
    int GetTopIndex();

	template <typename T> void SetPropValue(LPCTSTR name, T val)
	{
		setPropValue(name, (void*)&val);
	}

	template <typename T> T GetPropValue(LPCTSTR name)
	{
		T ret; //I know...
		void * val = getPropValue(name);

		if (val != NULL)
			ret = *(T*)val;
		return ret;
	}

protected:
	void LoadChild(CXMLDOMNode &Node,PropertyBase * Parentprop,CString &);
	void SaveChild(CXMLDOMNode &Node,PropertyBase * Parentprop);
    void CopyChild(PropertyBase * child);

	PropertyVector properties;
	PropertyMap          propMap; //just for speed
	LPCTSTR className;
    Component * component;
    int topIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_PROPERTY(Name, Type, Class,DefaultValue)\
{\
typedef Type (Class::*GetMethod)(void);\
typedef void (Class::*SetMethod)(Type);\
objprop.Add(new Property<Class,Type>(_T(#Name), _T(#Type),(GetMethod)&Class::get_##Name,(SetMethod)&Class::set_##Name,this,DefaultValue));\
}

#define DEFINE_PROPERTY_2(Name, Type, Class,DefaultValue)\
	objprop.Add(new Property<Class,Type>(_T(#Name), _T(#Type), NULL,NULL,this,DefaultValue));

#define DEFINE_WIN_PROPERTY(Name, Class)\
{\
typedef BOOL (Class::*GetMethod)(void);\
typedef void (Class::*SetMethod)(BOOL);\
	objprop.Add(new Property<Class,BOOL>(_T(#Name), _T("BOOL"), (GetMethod)&Class::get_##Name,(SetMethod)&Class::set_##Name,this));\
}

#define BEGIN_SUB_PROPERTY(Name, Type)\
{\
	PropertyBase * ParentProp=objprop.FindByName(Name);\
	if(ParentProp==NULL)\
		objprop.Add(ParentProp=new PropertyBase(Name, _T(#Type)));

#define BEGIN_SUB_PROPERTY_EX(Name)\
objprop.AddChild(ParentProp,new PropertyBase(Name,_T("")));

#define DEFINE_SUB_PROPERTY(Name, Type, Class,DefaultValue)\
objprop.AddChild(ParentProp,new Property<Class,Type>(_T(#Name), _T(#Type), &Class::get_##Name,&Class::set_##Name,this,DefaultValue));

#define DEFINE_SUB_PROPERTY_2(Name, Type, Class,DefaultValue)\
objprop.AddChild(ParentProp,new Property<Class,Type>(_T(#Name), _T(#Type), NULL,NULL,this,DefaultValue));

#define END_SUB_PROPERTY }

#define PUBLIC_PROPERTY(Name,Flag)\
objprop.SetPublished(_T(#Name),Flag);

#define HIDE_PROPERTY(Name)\
    objprop.SetPublished(_T(#Name),FALSE);

#define PUBLIC_PROPERTY_STR(Name,Flag)\
objprop.SetPublished(_T(#Name),Flag);

#define HIDE_PROPERTY_STR(Name)\
    objprop.SetPublished(_T(#Name),FALSE);

#define READONLY_PROPERTY(Name,Flag)\
	objprop.SetReadOnly(_T(#Name),Flag);

#define READONLY_PROPERTY_STR(Name,Flag)\
    objprop.SetReadOnly(_T(#Name),Flag);

#define REMOVE_PROPERTY(Name)\
    objprop.Remove(_T(#Name));

#define REMOVE_PROPERTY_STR(Name)\
    objprop.Remove(_T(#Name));

//changes value in case if previously value was set
#define SET_PROP_VALUE(Name, Value) objprop.SetPropValue(_T(#Name),Value);
#define GET_PROP_VALUE(T, Name) objprop.GetPropValue<T>(_T(#Name));
////////////////////////////////////////////////////////////////////////////////////////////////
//LIST PROPERTY
#define BEGIN_LIST_PROPERTY(Type)\
	static CCustomVal Type##Table[]={

#define LIST_ITEM_DECORATE(Value,Name,Decorate) {Value,_T(#Name),_T(#Decorate)},

#define LIST_ITEM(Value,Name) {Value,_T(#Name),_T(#Name)},

#define END_LIST_ITEM(Type)\
{-1,			NULL}};\
static LPCTSTR Type##ToString(DWORD *value)\
{\
	for(register int i=0;i < sizeof(Type##Table)/sizeof(CCustomVal)-1; i++)\
		if(*value==(DWORD)Type##Table[i].id)\
			return Type##Table[i].name;\
	return NULL;\
}\
static DWORD * StringTo##Type(LPCTSTR str)\
{\
	for(register int i=0;i < sizeof(Type##Table)/sizeof(CCustomVal)-1; i++)\
		if(_tcscmp(str,Type##Table[i].name)==0)\
			return (DWORD *)&Type##Table[i].id;\
	return 0;\
}\
static LPCTSTR Type##ToDecorateString(DWORD *value)\
{\
	for(register int i=0;i < sizeof(Type##Table)/sizeof(CCustomVal)-1; i++)\
		if(*value==(DWORD)Type##Table[i].id)\
			return Type##Table[i].decorate;\
	return NULL;\
}\
static DWORD * DecorateStringTo##Type(LPCTSTR str)\
{\
	for(register int i=0;i < sizeof(Type##Table)/sizeof(CCustomVal)-1; i++)\
		if(_tcscmp(str,Type##Table[i].decorate)==0)\
			return (DWORD*)&Type##Table[i].id;\
	return 0;\
}

#define REGISTER_LIST_PROPERTY(Type)\
	RegisterConversion(_T(#Type),(ValToStr)Type##ToString,(StrToVal)StringTo##Type,Type##Table,(ValToStr)Type##ToDecorateString,(StrToVal)DecorateStringTo##Type);\
	RegisterEdit(_T(#Type),CInplaceListEdit::CreateEdit,NULL);\
	RegisterDrawProperty(_T(#Type),DrawPropertyValueListText);	

#define REGISTER_LIST_PROPERTY_2(Type,TypeToString,StringToType,TypeToDecorateString,DecorateStringToType,ExternalEdit)\
	RegisterConversion(_T(#Type),(ValToStr)TypeToString,(StrToVal)StringToType,Type##Table,(ValToStr)TypeToDecorateString,(StrToVal)DecorateStringToType);\
	RegisterEdit(_T(#Type),CInplaceListEdit::CreateEdit,ExternalEdit);\
	RegisterDrawProperty(_T(#Type),DrawPropertyValueListText);	

#define DECLARE_PROPERTY(Name,Type)\
public:\
    virtual void set_##Name(Type n);\
    virtual Type get_##Name(void);

#define DECLARE_WINSTYLE_PROPERTY(Name)\
public:\
    virtual void set_##Name(long n);\
    virtual long get_##Name(void);

//////////////////////////////////////////////////////////////////////////////////////////////////
//common data conversion function
PROPERTY_API LPCTSTR CharPtrToString(LPCTSTR* val);
PROPERTY_API LPTSTR* StringToCharPtr(LPCTSTR val);
PROPERTY_API LPCTSTR StrToString(CString *val);
PROPERTY_API CString *  StringToStr(LPCTSTR val);
PROPERTY_API LPCTSTR  IntToString(int *val);
PROPERTY_API long * StringToInt(LPCTSTR str);
PROPERTY_API LPCTSTR FloatToString(float *val);
PROPERTY_API float * StringToFloat(const CString & str);
PROPERTY_API LPCTSTR DoubleToString(double * val);
PROPERTY_API double * StringToDouble(const CString &str);
PROPERTY_API LPCTSTR BoolToString(BOOL * val);
PROPERTY_API BOOL * StringToBool(LPCTSTR str);
PROPERTY_API LPCTSTR boolToString(bool * val);
PROPERTY_API bool * StringTobool(LPCTSTR str);
PROPERTY_API LPCTSTR ColorToStringDec(CColorref * color);
PROPERTY_API CColorref * StringToColorDec(LPCTSTR str);
PROPERTY_API LPCTSTR ColorToString(CColorref * color);
PROPERTY_API CColorref * StringToColor(LPCTSTR str);
PROPERTY_API LPCTSTR PathToString(CString *val);
PROPERTY_API CString *  StringToPath(LPCTSTR val);

PROPERTY_API void DrawPropertyValueText(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx);
PROPERTY_API void DrawPropertyValueColor(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx);
PROPERTY_API void DrawPropertyValueBool(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx);
PROPERTY_API void DrawPropertyValuebool(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx);
PROPERTY_API void DrawPropertyValueListText(HDC hDC,const CRect & DrawRc,PropertyBase * prop,int idx);

PROPERTY_API void ExImageBmpIcoFile(HWND parent,PropertyBase *prop);
PROPERTY_API void ExImageBmpFile(HWND parent,PropertyBase *prop);
PROPERTY_API void ExImageIcoFile(HWND parent,PropertyBase *prop);
PROPERTY_API void ExTextFile(HWND parent,PropertyBase *prop);

PROPERTY_API void ExColorEdit(HWND parent,PropertyBase *prop,LPARAM);
//////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" PROPERTY_API CPropertyList * CreatePropertyList(HWND Parent, WTL::CRect &rc,UINT id);
extern "C" PROPERTY_API void ShowProperties(CProperties * p);
extern "C" PROPERTY_API void RemoveProperties(void);
extern "C" PROPERTY_API void UpdateProperty(const CString & p);
//////////////////////////////////////////////////////////////////////////////////////////////////
#endif