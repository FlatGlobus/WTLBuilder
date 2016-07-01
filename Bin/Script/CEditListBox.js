// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeEditListBoxStyle(component)
{
    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);
    
    if ( component.Item("Browse")==true )
        styleStr+="|EDLS_BROWSE";

    if ( component.Item("MoveButtons")==false )
        styleStr+="|EDLS_NOMOVEBUTTONS";

    return styleStr;
}


function ViksoeCtrl_CEditListBox(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CEditListBox"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Caption"),component)+","+
               MakeEditListBoxStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";
    
    MakeSetFocus(form,component);       
    MakeContained(form,component);
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"EditListBox.h");         
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

////////////////////////////////////////////////////////////////////////////////////////////////
function ViksoeCtrl_CEditListBoxLocalize(form,component)
{
    var codegen=form.Code;

    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Caption")!="" )
        str=ID + codegen.Format(component," = [!Caption]\n");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
