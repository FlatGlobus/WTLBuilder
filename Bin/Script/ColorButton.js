// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function DecorativeCtrl_CColorButton(form,component)
{
    var codegen=form.Code;
    //var cmpName=component.Item("Name");
    
    CheckComponent(form, component);

    var headerStr=codegen.Format(component,"\tCColorButton\t[!Name];\n"); 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);

    var sourceStr=codegen.Format(component,"\t[!Name].Create([!ParentName],");    
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Caption"),component)+","+
               MakeWindowStyle(component)+"|BS_OWNERDRAW,"+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);  
    sourceStr+=MakeToolTip(component);  
    sourceStr+="\n";

    MakeSetFocus(form,component);               
    MakeContained(form,component);

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function DecorativeCtrl_CColorButtonLocalize(form,component)
{
//   var codegen=form.Code;

//   var str="";
//   var ID=MakeControlNameID(component);

//   if(component.Item("Caption")!="")
//      str=ID + codegen.Format(component," = [!Caption]\n");

//  if(component.Item("EnableToolTip")==true)
//      str+=ID + codegen.Format(component,"_ToolTip = [!ToolTip]\n");
    
//   codegen.Localize+=str;
}
