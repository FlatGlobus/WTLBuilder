// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeUpDownCtrlStyle(component)
{
	var  UDS_WRAP=                0x0001;
	var  UDS_SETBUDDYINT=         0x0002;
	var  UDS_ALIGNRIGHT=          0x0004;
	var  UDS_ALIGNLEFT=           0x0008;
	var  UDS_AUTOBUDDY=           0x0010;
	var  UDS_ARROWKEYS=           0x0020;
	var  UDS_HORZ=                0x0040;
	var  UDS_NOTHOUSANDS=         0x0080;
	var  UDS_HOTTRACK=            0x0100;

	var style=parseInt(component.Item("InternalWindowStyle"),10);
	var styleStr=MakeWindowStyle(component);

	if((style & UDS_WRAP)==UDS_WRAP)
		styleStr+="|UDS_WRAP";
	
	if((style & UDS_SETBUDDYINT)==UDS_SETBUDDYINT)
		styleStr+="|UDS_SETBUDDYINT";
	
	if((style & UDS_ALIGNRIGHT)==UDS_ALIGNRIGHT)
		styleStr+="|UDS_ALIGNRIGHT";
	
	if((style & UDS_ALIGNLEFT)==UDS_ALIGNLEFT)
		styleStr+="|UDS_ALIGNLEFT";
	
	if((style & UDS_AUTOBUDDY)==UDS_AUTOBUDDY)
		styleStr+="|UDS_AUTOBUDDY";
	
	if((style & UDS_ARROWKEYS)==UDS_ARROWKEYS)
		styleStr+="|UDS_ARROWKEYS";
	
	if((style & UDS_HORZ)==UDS_HORZ)
		styleStr+="|UDS_HORZ";
	
	if((style & UDS_NOTHOUSANDS)==UDS_NOTHOUSANDS)
		styleStr+="|UDS_NOTHOUSANDS";
	
	if((style & UDS_HOTTRACK)==UDS_HOTTRACK)
		styleStr+="|UDS_HOTTRACK";
		
	return styleStr;
}

function StdCtl_CUpDownCtrl(form,component)
{
	var cmpName=component.Item("Name");
	var headerStr="\t"+"CUpDownCtrl"+"\t"+cmpName+";\n"; 
	headerStr+=MakeContainedDecl(form,component);
	headerStr+=MakeFontDeclaration(component);
			
	var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
	sourceStr+=MakeRect(component)+",NULL,"+
	MakeUpDownCtrlStyle(component)+","+
	MakeExWindowStyle(component)+","+
	component.Item("ID")+");\n"; 	
	
	sourceStr+="\t"+cmpName+".SetBase("+component.Item("Base")+");\n";
	sourceStr+="\t"+cmpName+".SetRange("+component.Item("Lover")+","+
	+component.Item("Upper")+");\n";
	sourceStr+="\t"+cmpName+".SetPos("+component.Item("Pos")+");\n";
	sourceStr+="\n";
	
	var postSource="";
	if(component.Item("Buddy") != "NULL")
		postSource="\t"+cmpName+".SetBuddy("+component.Item("Buddy")+");\n";
	
	MakeSetFocus(form,component);			
	MakeContained(form,component);

	var codegen=form.Code;
	codegen.Insert(endMemberDecl,headerStr);
 	codegen.Insert(endMemberCreation,sourceStr);
 	codegen.Insert(endCtrlIDDecl,MakeControlID(component));
 	if(postSource != "")
 		codegen.Insert(endPostCreation,postSource);
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CUpDownCtrlLocalize(form,component)
{
	var codegen=form.Code;
	var str="";
	var ID=MakeControlNameID(component);
	if(component.Item("EnableToolTip")=="true")
      str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
	codegen.Localize+=str;
}
