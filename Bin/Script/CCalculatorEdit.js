// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function DecorativeCtrl_CCalculatorEdit(form,component)
{
    CheckComponent(form, component);

    var cmpName=component.Item("Name");
    var headerStr="\t"+"CCalculatorEdit"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL,"+//MakeCString(component.Item("Caption"))+","+
               MakeWindowStyle(component)+"|SS_RIGHT,"+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";
    
    MakeSetFocus(form,component);       
    MakeContained(form,component);
    
    var codegen=form.Code;
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"CalculatorEdit.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function DecorativeCtrl_CCalculatorEditLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
