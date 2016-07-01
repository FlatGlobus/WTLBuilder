// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function WTLBuilderCtrl_CPropertyList(form, component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CPropertyList"+"\t*"+cmpName+";\n"; 
    
    var sourceStr="\t"+cmpName+"=CreatePropertyList("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+","+component.Item("ID")+");\n";     
    sourceStr+="\n";
    
    var codegen=form.Code;
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
