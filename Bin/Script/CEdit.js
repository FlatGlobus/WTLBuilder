// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeEditStyle(component)
{
    var ES_CENTER=           0x0001;
    var ES_RIGHT=            0x0002;
    var ES_MULTILINE=        0x0004;
    var ES_UPPERCASE=        0x0008;
    var ES_LOWERCASE=        0x0010;
    var ES_PASSWORD=         0x0020;
    var ES_AUTOVSCROLL=      0x0040;
    var ES_AUTOHSCROLL=      0x0080;
    var ES_NOHIDESEL=        0x0100;
    var ES_OEMCONVERT=       0x0400;
    var ES_READONLY=         0x0800;
    var ES_WANTRETURN=       0x1000;
    var ES_NUMBER=           0x2000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & ES_CENTER)==ES_CENTER )
        styleStr+="|ES_CENTER";

    if ( (style & ES_RIGHT)==ES_RIGHT )
        styleStr+="|ES_RIGHT";

    if ( (style & ES_MULTILINE)==ES_MULTILINE )
        styleStr+="|ES_MULTILINE";

    if ( (style & ES_UPPERCASE)==ES_UPPERCASE )
        styleStr+="|ES_UPPERCASE";

    if ( (style & ES_LOWERCASE)==ES_LOWERCASE )
        styleStr+="|ES_LOWERCASE";

    if ( (style & ES_PASSWORD)==ES_PASSWORD )
        styleStr+="|ES_PASSWORD";

    if ( (style & ES_AUTOVSCROLL)==ES_AUTOVSCROLL )
        styleStr+="|ES_AUTOVSCROLL";

    if ( (style & ES_AUTOHSCROLL)==ES_AUTOHSCROLL )
        styleStr+="|ES_AUTOHSCROLL";

    if ( (style & ES_NOHIDESEL)==ES_NOHIDESEL )
        styleStr+="|ES_NOHIDESEL";

    if ( (style & ES_OEMCONVERT)==ES_OEMCONVERT )
        styleStr+="|ES_OEMCONVERT";

    if ( (style & ES_READONLY)==ES_READONLY )
        styleStr+="|ES_READONLY";

    if ( (style & ES_WANTRETURN)==ES_WANTRETURN )
        styleStr+="|ES_WANTRETURN";

    if ( (style & ES_NUMBER)==ES_NUMBER )
        styleStr+="|ES_NUMBER";

    return styleStr;
}

function StdCtl_CEdit(form,component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CEdit"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Text"),component)+","+
               MakeEditStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);       
    MakeContained(form,component);
    
    var codegen=form.Code;
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CEditLocalize(form,component)
{
    var codegen=form.Code;

    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Text")!="" )
        str=ID + codegen.Format(component," = [!Text]\n");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
