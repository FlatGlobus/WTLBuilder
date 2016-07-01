// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function StdCtl_CPaneContainer(form, component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    
    CheckComponent(form, component);

    var headerStr="";
    headerStr=codegen.Format(component,"\tCPaneContainer\t[!Name];\n"); 
    headerStr+=MakeContainedDecl(form,component);

    var sourceStr="";
    sourceStr=codegen.Format(component,"\t[!Name].Create([!ParentName],");    
    sourceStr+=MakeLocalizedCString(component.Item("Title"),component)+","+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";
                   
    if(component.Item("CloseButton")==false || component.Item("Vertical")==true)
    {
		var extStyle=codegen.Format(component,"\t[!Name].SetPaneContainerExtendedStyle(");
		if(component.Item("CloseButton")==false)
			extStyle+="PANECNT_NOCLOSEBUTTON";
		if(component.Item("Vertical")==true)
			extStyle+="|PANECNT_VERTICAL";
		extStyle=RemoveFirstOr(extStyle)+",";
		extStyle+=",0);\n";
		sourceStr+=extStyle;
	}
	sourceStr+=codegen.Format(component,"\t[!Name].EnableCloseButton([!EnableCloseButton]);\n");
    sourceStr+="\n";
    
    MakeContained(form,component);
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CPaneContainerLocalize(form,component)
{
    var codegen=form.Code;

    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Title")!="" )
        str=ID + codegen.Format(component," = [!Title]\n");
    codegen.Localize+=str;
}
