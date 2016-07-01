// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function DecorativeCtrl_CWtlEditBrowserCtrl(form, component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CWtlEditBrowserCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Text"),component)+","+
               MakeEditStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";
    sourceStr+="\t"+cmpName+".SetRecipient(*this);\n";
    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);       
    MakeContained(form,component);
    
    var codegen=form.Code;
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"WtlEditBrowserCtrl.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function DecorativeCtrl_CWtlEditBrowserCtrlLocalize(form,component)
{
    var codegen=form.Code;

    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Text")!="" )
        str=ID + codegen.Format(component," = [!Text]\n");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
