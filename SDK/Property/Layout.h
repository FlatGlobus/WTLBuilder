// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __LAYOUT_H__
#define __LAYOUT_H__
//////////////////////////////////////////////////////////////////////////
#include "Property.h"
class CProperties;
class PROPERTY_API CLayout
{
	BOOL attachNone,attachForm,attachOppositeForm,
		 attachChild,attachOppositeChild,attachPosition,attachSelf;
	CString child;
	Component * component;
	long position;
	void DefineLayout();
	CString propName;
public:
	CLayout(Component *);
	~CLayout(void);

	void set_AttachNone(BOOL val);
	BOOL get_AttachNone(void);
	void set_AttachForm(BOOL val);
	BOOL get_AttachForm(void);
	void set_AttachOppositeForm(BOOL val);
	BOOL get_AttachOppositeForm(void);
	void set_AttachChild(BOOL val);
	BOOL get_AttachChild(void);
	void set_AttachOppositeChild(BOOL val);
	BOOL get_AttachOppositeChild(void);
	void set_AttachPosition(BOOL val);
	BOOL get_AttachPosition(void);
	void set_AttachSelf(BOOL val);
	BOOL get_AttachSelf(void);

	void set_Position(long val);
	long get_Position(void);

	void set_Child(CString);
	CString get_Child(void);

	void AddProperty(LPCTSTR Name,LPCTSTR SubName,CProperties & objprop);
};
//////////////////////////////////////////////////////////////////////////
#endif