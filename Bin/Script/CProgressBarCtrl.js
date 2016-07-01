// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeProgressBarCtrlStyle(component)
{
    var PBS_SMOOTH=              0x01;
    var PBS_VERTICAL=            0x04;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & PBS_SMOOTH)==PBS_SMOOTH )
        styleStr+="|PBS_SMOOTH";

    if ( (style & PBS_VERTICAL)==PBS_VERTICAL )
        styleStr+="|PBS_VERTICAL";

    return styleStr;
}

function StdCtl_CProgressBarCtrl(form,component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CProgressBarCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeProgressBarCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    
    if ( component.Item("BkColor")!="CLR_DEFAULT" )
        sourceStr+="\t"+cmpName+".SetBkColor("+MakeColor(component.Item("BkColor"))+");\n";

    if ( component.Item("BarColor")!="CLR_DEFAULT" )
        sourceStr+="\t"+cmpName+".SetBarColor("+MakeColor(component.Item("BarColor"))+");\n";

    if ( component.Item("Min")!="0" && component.Item("Max")!="100" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetRange32([!Min],[!Max]);\n");

    if ( component.Item("Pos")!="0" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetPos([!Pos]);\n");

    if ( component.Item("Pos")!="10" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetStep([!Step]);\n");

    if ( component.Item("OffsetPos")!="0" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetOffsetPos([!OffsetPos]);\n");

    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);            
    MakeContained(form,component);

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CProgressBarCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
