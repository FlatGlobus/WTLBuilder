// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function StdCtl_CMenu(form, component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckProperty(form, component, "Name", "");
    CheckProperty(form, component, "ID", "");

    var headerStr="\t"+"CMenu"+"\t"+cmpName+";\n"; 
    var sourceStr="\t"+cmpName+".LoadMenu("+component.Item("ID")+");\n";
    sourceStr+="\n";
    
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
}