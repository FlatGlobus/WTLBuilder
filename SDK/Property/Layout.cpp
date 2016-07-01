// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "Component.h"
#include "layout.h"
#include "PropertyListEdit.h"
#include "ComponentList.h"
//////////////////////////////////////////////////////////////////////////
CLayout::CLayout(Component *cmp):component(cmp),
attachNone(FALSE),attachForm(FALSE),attachOppositeForm(FALSE),
attachChild(FALSE),attachOppositeChild(FALSE),attachPosition(FALSE),attachSelf(FALSE)
{
}

CLayout::~CLayout(void)
{

}

void CLayout::set_AttachNone(BOOL val)
{
	attachNone=val;
	if(val==TRUE)
	{
		attachForm=attachOppositeForm=attachChild=
		attachOppositeChild=attachPosition=attachSelf=FALSE;
	}
	DefineLayout();
}

BOOL CLayout::get_AttachNone(void)
{
	return attachNone;
}

void CLayout::set_AttachForm(BOOL val)
{
	attachForm=val;
	if(val==TRUE)
	{
		attachNone=attachOppositeForm=attachChild=
		attachOppositeChild=attachPosition=attachSelf=FALSE;
	}
	DefineLayout();
}

BOOL CLayout::get_AttachForm(void)
{
	return attachForm;
}

void CLayout::set_AttachOppositeForm(BOOL val)
{

	attachOppositeForm=val;
	if(val==TRUE)
	{
		attachNone=attachForm=attachChild=
		attachOppositeChild=attachPosition=attachSelf=FALSE;
	}

	DefineLayout();
}

BOOL CLayout::get_AttachOppositeForm(void)
{
	return attachOppositeForm;
}

void CLayout::set_AttachChild(BOOL val)
{
	attachChild=val;
	if(val==TRUE)
	{
		attachNone=attachForm=attachOppositeForm=
		attachOppositeChild=attachPosition=attachSelf=FALSE;
	}

	DefineLayout();
}

BOOL CLayout::get_AttachChild(void)
{
	return attachChild;
}

void CLayout::set_AttachOppositeChild(BOOL val)
{
	attachOppositeChild=val;
	if(val==TRUE)
	{
		attachNone=attachForm=attachOppositeForm=attachChild=
		attachPosition=attachSelf=FALSE;
	}

	DefineLayout();
}

BOOL CLayout::get_AttachOppositeChild(void)
{
	return attachOppositeChild;
}

void CLayout::set_AttachPosition(BOOL val)
{
	attachPosition=val;
	if(val==TRUE)
	{
		attachNone=attachForm=attachOppositeForm=attachChild=
		attachOppositeChild=attachSelf=FALSE;
	}

	DefineLayout();
}

BOOL CLayout::get_AttachPosition(void)
{
	return attachPosition;
}

void CLayout::set_Child(CString val)
{
	child=val;
	DefineLayout();
}

CString CLayout::get_Child(void)
{
    CComponentListEdit::SetComponentKind(_T(""));
	if(component->GetComponentParent()->GetState(csLoading)==FALSE && component->GetComponents()->Find(child)==NULL)
		child=_T("None");
	return child;
}

void CLayout::set_AttachSelf(BOOL val)
{
	attachSelf=val;
	if(val==TRUE)
	{
		attachNone=attachForm=attachOppositeForm=attachChild=
		attachOppositeChild=attachPosition=FALSE;
	}
	DefineLayout();
}

BOOL CLayout::get_AttachSelf(void)
{
	return attachSelf;
}

void CLayout::set_Position(long val)
{
	position=val;
	DefineLayout();
}

long CLayout::get_Position(void)
{
	return position;
}

void CLayout::DefineLayout()
{
	if(component->GetState(csCreating)==FALSE &&  component->GetState(csLoading)==FALSE)
	{
        ::UpdateProperty(propName+_T(".AttachNone"));
		::UpdateProperty(propName+_T(".AttachForm"));
		::UpdateProperty(propName+_T(".AttachOppositeForm"));
		::UpdateProperty(propName+_T(".AttachChild"));
		::UpdateProperty(propName+_T(".AttachOppositeChild"));
		::UpdateProperty(propName+_T(".AttachPosition"));
		::UpdateProperty(propName+_T(".AttachSelf"));
		::PostMessage((HWND)component->GetDesigner()->GetParentForm()->GetHandle(),WM_UPDATELAYOUT,0,0);
        component->SetModified();
	}
}

void CLayout::AddProperty(LPCTSTR Name,LPCTSTR SubName,CProperties & objprop)
{
	propName.Format(_T("%s.%s"),Name,SubName);
	BEGIN_SUB_PROPERTY(Name,CLayout)
		BEGIN_SUB_PROPERTY_EX(SubName)
	END_SUB_PROPERTY

	BEGIN_SUB_PROPERTY(propName,CLayout)
		DEFINE_SUB_PROPERTY(AttachForm,BOOL,CLayout,FALSE)
		DEFINE_SUB_PROPERTY(AttachOppositeForm,BOOL,CLayout,FALSE)
		DEFINE_SUB_PROPERTY(AttachChild,BOOL,CLayout,FALSE)
		DEFINE_SUB_PROPERTY(AttachOppositeChild,BOOL,CLayout,FALSE)
		DEFINE_SUB_PROPERTY(AttachPosition,BOOL,CLayout,FALSE)
		DEFINE_SUB_PROPERTY(AttachSelf,BOOL,CLayout,FALSE)
        DEFINE_SUB_PROPERTY(AttachNone,BOOL,CLayout,FALSE)
		DEFINE_SUB_PROPERTY(Child,ComponentName,CLayout,_T("None"))
		DEFINE_SUB_PROPERTY(Position,long,CLayout,0)
	END_SUB_PROPERTY
}
