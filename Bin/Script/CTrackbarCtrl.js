// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeTrackBarCtrlStyle(component)
{
    var  TBS_AUTOTICKS=           0x0001;
    var  TBS_VERT=                0x0002;
    var  TBS_HORZ=                0x0000;
    var  TBS_TOP=                 0x0004;
    var  TBS_BOTTOM=              0x0000;
    var  TBS_LEFT=                0x0004;
    var  TBS_RIGHT=               0x0000;
    var  TBS_BOTH=                0x0008;
    var  TBS_NOTICKS=             0x0010;
    var  TBS_ENABLESELRANGE=      0x0020;
    var  TBS_FIXEDLENGTH=         0x0040;
    var  TBS_NOTHUMB=             0x0080;
    var  TBS_TOOLTIPS=            0x0100;
    var  TBS_REVERSED=            0x0200;
    var  TBS_DOWNISLEFT=          0x0400;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);
    
    if ( (style & TBS_AUTOTICKS)==TBS_AUTOTICKS )
        styleStr+="|TBS_AUTOTICKS";

    if ( (style & TBS_VERT)==TBS_VERT )
        styleStr+="|TBS_VERT";

    if ( (style & TBS_HORZ)==TBS_HORZ )
        styleStr+="|TBS_HORZ";

    if ( (style & TBS_TOP)==TBS_TOP )
        styleStr+="|TBS_TOP";

    if ( (style & TBS_BOTTOM)==TBS_BOTTOM )
        styleStr+="|TBS_BOTTOM";

    if ( (style & TBS_LEFT)==TBS_LEFT )
        styleStr+="|TBS_LEFT";

    if ( (style & TBS_RIGHT)==TBS_RIGHT )
        styleStr+="|TBS_RIGHT";

    if ( (style & TBS_BOTH)==TBS_BOTH )
        styleStr+="|TBS_BOTH";

    if ( (style & TBS_NOTICKS)==TBS_NOTICKS )
        styleStr+="|TBS_NOTICKS";

    if ( (style & TBS_ENABLESELRANGE)==TBS_ENABLESELRANGE )
        styleStr+="|TBS_ENABLESELRANGE";

    if ( (style & TBS_FIXEDLENGTH)==TBS_FIXEDLENGTH )
        styleStr+="|TBS_FIXEDLENGTH";

    if ( (style & TBS_NOTHUMB)==TBS_NOTHUMB )
        styleStr+="|TBS_NOTHUMB";

    if ( (style & TBS_TOOLTIPS)==TBS_TOOLTIPS )
        styleStr+="|TBS_TOOLTIPS";

    if ( (style & TBS_REVERSED)==TBS_REVERSED )
        styleStr+="|TBS_REVERSED";

    if ( (style & TBS_DOWNISLEFT)==TBS_DOWNISLEFT )
        styleStr+="|TBS_DOWNISLEFT";

    return styleStr;
}

function StdCtl_CTrackBarCtrl(form,component)
{
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CTrackBarCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeTrackBarCtrlStyle(component)+","+
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
function StdCtl_CTrackBarCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
