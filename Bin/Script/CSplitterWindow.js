// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeSplitterStyle(component)
{
    var extStyleStr="";

    if ( component.Item("Proportional")==true )
        extStyleStr="SPLIT_PROPORTIONAL";

    if ( component.Item("NonInteractive")==true )
        extStyleStr="|SPLIT_NONINTERACTIVE";

    if ( component.Item("RightAligned")==true )
        extStyleStr="|SPLIT_RIGHTALIGNED";

    if ( extStyleStr.charAt(0)=='|' )
        extStyleStr=extStyleStr.substr(1,extStyleStr.length);

    return extStyleStr;
}

function StdCtl_CSplitterWindow(form,component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CSplitterWindow"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";
    sourceStr+="\n";

    var postSource=codegen.Format(component,"\t[!Name].SetSplitterPanes([!LeftPane],[!RightPane]);\n");
    if ( component.Item("Proportional")==true || component.Item("NonInteractive")==true ||
         component.Item("RightAligned")==true )
        postSource+="\t"+cmpName+".SetSplitterExtendedStyle("+MakeSplitterStyle(component)+",0);\n";

    postSource+=codegen.Format(component,"\t[!Name].SetSplitterPos([!Pos]);\n");

    if ( component.Item("SinglePaneMode")!="SPLIT_PANE_NONE" )
        postSource+=codegen.Format(component,"\t[!Name].SetSinglePaneMode([!SinglePaneMode]);\n");

    if ( component.Item("ActivePane")!="SPLIT_PANE_NONE" )
        postSource+=codegen.Format(component,"\t[!Name].SetActivePane([!ActivePane]);\n");


    MakeContained(form,component);
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"atlsplit.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
    codegen.Insert(endPostCreation,postSource);
}

function StdCtl_CHorSplitterWindow(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CHorSplitterWindow"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+="\n";

    var postSource=codegen.Format(component,"\t[!Name].SetSplitterPanes([!TopPane],[!BottomPane]);\n");
    if ( component.Item("Proportional")==true || component.Item("NonInteractive")==true ||
         component.Item("RightAligned")==true )
        postSource+="\t"+cmpName+".SetSplitterExtendedStyle("+MakeSplitterStyle(component)+",0);\n";

    postSource+=codegen.Format(component,"\t[!Name].SetSplitterPos([!Pos]);\n");

    if ( component.Item("SinglePaneMode")!="SPLIT_PANE_NONE" )
        postSource+=codegen.Format(component,"\t[!Name].SetSinglePaneMode([!SinglePaneMode]);\n");

    if ( component.Item("ActivePane")!="SPLIT_PANE_NONE" )
        postSource+=codegen.Format(component,"\t[!Name].SetActivePane([!ActivePane]);\n");


    MakeContained(form,component);
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"atlsplit.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
    codegen.Insert(endPostCreation,postSource);
}
