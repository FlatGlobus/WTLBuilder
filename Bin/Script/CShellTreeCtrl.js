// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function ViksoeCtrl_CShellTreeCtrl(form, component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CShellTreeCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeTreeViewCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeShellCtrlStyle(component);           
    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

//    var postSource=codegen.Format(component,"\t[!Name].Populate(_T(\"\"));\n");
    var postSource=codegen.Format(component,"\t[!Name].Populate("+MakeCString(component.Item("Path"))+");\n");


    MakeSetFocus(form,component);            
    MakeContained(form,component);

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
    codegen.Insert(endPostCreation,postSource);

    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"atlshellextbase.h");
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"atlshellext.h");
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"ShellCtrls.h");
}
////////////////////////////////////////////////////////////////////////////////////////////////
