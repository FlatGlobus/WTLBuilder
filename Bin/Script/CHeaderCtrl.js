// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
function MakeHeaderCtrlStyle(component)
{
    var HDS_HORZ=                0x0000;
    var HDS_BUTTONS=             0x0002;
    var HDS_HOTTRACK=            0x0004;
    var HDS_HIDDEN=              0x0008;
    var HDS_DRAGDROP=            0x0040;
    var HDS_FULLDRAG=            0x0080;
    var HDS_FILTERBAR=           0x0100;
    var HDS_FLAT=                0x0200;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    
    var styleStr=MakeWindowStyle(component);

//  if((style & HDS_HORZ)==HDS_HORZ)
//      styleStr+="|HDS_HORZ";

    if ( (style & HDS_BUTTONS)==HDS_BUTTONS )
        styleStr+="|HDS_BUTTONS";

    if ( (style & HDS_HOTTRACK)==HDS_HOTTRACK )
        styleStr+="|HDS_HOTTRACK";

    if ( (style & HDS_HIDDEN)==HDS_HIDDEN )
        styleStr+="|HDS_HIDDEN";

    if ( (style & HDS_DRAGDROP)==HDS_DRAGDROP )
        styleStr+="|HDS_DRAGDROP";

    if ( (style & HDS_FULLDRAG)==HDS_FULLDRAG )
        styleStr+="|HDS_FULLDRAG";

    if ( (style & HDS_FILTERBAR)==HDS_FILTERBAR )
        styleStr+="|HDS_FILTERBAR";

    if ( (style & HDS_FLAT)==HDS_FLAT )
        styleStr+="|HDS_FLAT";

    return styleStr;
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CHeaderCtrl(form,component)
{
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr = "\t" + "CHeaderCtrl" + "\t" + cmpName + ";\n";
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeHeaderCtrlStyle(component)+","+
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
////////////////////////////////////////////////////////////////////////////////

