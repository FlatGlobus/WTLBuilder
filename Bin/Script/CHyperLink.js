// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function StdCtl_CHyperLink(form, component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    
    var headerStr=codegen.Format(component,"\tCHyperLink\t[!Name];\n"); 
    headerStr+=MakeContainedDecl(form,component);
    //headerStr+=MakeFontDeclaration(component);

    var sourceStr=codegen.Format(component,"\t[!Name].Create([!ParentName],");    
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    //sourceStr+=MakeControlFont(component);    

    sourceStr+="\t"+cmpName+".SetLabel("+MakeCString(component.Item("Label"))+");\n";
    sourceStr+="\t"+cmpName+".SetHyperLink("+MakeCString(component.Item("HyperLink"))+");\n";
    sourceStr+="\t"+cmpName+".m_bPaintLabel="+component.Item("PaintLabel")+";\n";
    sourceStr+="\t"+cmpName+".m_clrLink="+MakeColor(component.Item("ColorLink"))+";\n";
    sourceStr+="\t"+cmpName+".m_clrVisited="+MakeColor(component.Item("ColorVisited"))+";\n";
    
    sourceStr+=MakeToolTip(component);  
    sourceStr+="\n";

    MakeSetFocus(form,component);        
    MakeContained(form,component);
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"atlctrlx.h");	
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
