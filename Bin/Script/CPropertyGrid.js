// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function ViksoeCtrl_CPropertyGridCtrl(form,component)
{
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr = "\t" + "CPropertyGridCtrl" + "\t" + cmpName + ";\n";
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeListViewCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);

    sourceStr+=MakeListViewCtrlStyleEx(component);
    sourceStr+="\t"+cmpName+".SetFirstColor("+MakeColor(component.Item("FirstColor"))+");\n";   
    sourceStr+="\t"+cmpName+".SetSecondColor("+MakeColor(component.Item("SecondColor"))+");\n"; 

    sourceStr+="\n";
    
    MakeSetFocus(form,component);       
    MakeContained(form,component);
    
    var codegen=form.Code;
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function ViksoeCtrl_CPropertyGridCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
