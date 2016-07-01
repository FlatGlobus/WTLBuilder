// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
function MakeAnimateCtrlStyle(component)
{
    var ACS_CENTER=         0x0001;
    var ACS_TRANSPARENT=    0x0002;
    var ACS_AUTOPLAY=       0x0004;
    var ACS_TIMER=          0x0008;

    CheckComponent(form, component);

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & ACS_CENTER)==ACS_CENTER )
        styleStr+="|ACS_CENTER";

    if ( (style & ACS_TRANSPARENT)==ACS_TRANSPARENT )
        styleStr+="|ACS_TRANSPARENT";

    if ( (style & ACS_AUTOPLAY)==ACS_AUTOPLAY )
        styleStr+="|ACS_AUTOPLAY";

    if ( (style & ACS_TIMER)==ACS_TIMER )
        styleStr+="|ACS_TIMER";
        
    return styleStr;
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CAnimateCtrl(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CAnimateCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeAnimateCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    
    if ( component.Item("Image.ID")!="" )
        sourceStr+=codegen.Format(component,"\t[!Name].Open([!Image.ID]);\n");
    else
        if ( component.Item("Image.FileName")!="" )
        sourceStr+="\t"+cmpName+".Open("+MakeCString(component.Item("Image.FileName"))+");\n";

    if ( component.Item("Play")==true )
        sourceStr+=codegen.Format(component,"\t[!Name].Play(0,-1,-1);\n");

    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);        
    MakeContained(form,component);

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function StdCtl_CAnimateCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,"_ToolTip = [!ToolTip]\n");
    codegen.Localize+=str;
}
