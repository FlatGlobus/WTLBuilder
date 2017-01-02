// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeToolBarCtrlStyle(component)
{
    var BTNS_BUTTON=         0x0000;
    var BTNS_SEP=            0x0001;
    var BTNS_CHECK=          0x0002;
    var BTNS_GROUP=          0x0004;
    var BTNS_DROPDOWN=       0x0008;
    var BTNS_AUTOSIZE=       0x0010;
    var BTNS_NOPREFIX=       0x0020;
    var BTNS_SHOWTEXT=       0x0040;
    var BTNS_WHOLEDROPDOWN=  0x0080;
    var TBSTYLE_TOOLTIPS=     0x0100;
    var TBSTYLE_WRAPABLE=     0x0200;
    var TBSTYLE_ALTDRAG=      0x0400;
    var TBSTYLE_FLAT=         0x0800;
    var TBSTYLE_LIST=         0x1000;
    var TBSTYLE_CUSTOMERASE=  0x2000;
    var TBSTYLE_REGISTERDROP= 0x4000;
    var TBSTYLE_TRANSPARENT=  0x8000;
    var TBSTYLE_EX_DRAWDDARROWS= 0x00000001;

    
    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & BTNS_BUTTON)==BTNS_BUTTON )
        styleStr+="|BTNS_BUTTON";

    if ( (style & BTNS_SEP)==BTNS_SEP )
        styleStr+="|BTNS_SEP";

    if ( (style & BTNS_CHECK)==BTNS_CHECK )
        styleStr+="|BTNS_CHECK";

    if ( (style & BTNS_GROUP)==BTNS_GROUP )
        styleStr+="|BTNS_GROUP";

    if ( (style & BTNS_DROPDOWN)==BTNS_DROPDOWN )
        styleStr+="|BTNS_DROPDOWN";

    if ( (style & BTNS_AUTOSIZE)==BTNS_AUTOSIZE )
        styleStr+="|BTNS_AUTOSIZE";

    if ( (style & BTNS_NOPREFIX)==BTNS_NOPREFIX )
        styleStr+="|BTNS_NOPREFIX";

    if ( (style & BTNS_SHOWTEXT)==BTNS_SHOWTEXT )
        styleStr+="|BTNS_SHOWTEXT";

    if ( (style & BTNS_WHOLEDROPDOWN)==BTNS_WHOLEDROPDOWN )
        styleStr+="|BTNS_WHOLEDROPDOWN";

    if ( (style & TBSTYLE_TOOLTIPS)==TBSTYLE_TOOLTIPS )
        styleStr+="|TBSTYLE_TOOLTIPS";

    if ( (style & TBSTYLE_WRAPABLE)==TBSTYLE_WRAPABLE )
        styleStr+="|TBSTYLE_WRAPABLE";

    if ( (style & TBSTYLE_ALTDRAG)==TBSTYLE_ALTDRAG )
        styleStr+="|TBSTYLE_ALTDRAG";

    if ( (style & TBSTYLE_FLAT)==TBSTYLE_FLAT )
        styleStr+="|TBSTYLE_FLAT";

    if ( (style & TBSTYLE_LIST)==TBSTYLE_LIST )
        styleStr+="|TBSTYLE_LIST";

    if ( (style & TBSTYLE_CUSTOMERASE)==TBSTYLE_CUSTOMERASE )
        styleStr+="|TBSTYLE_CUSTOMERASE";

    if ( (style & TBSTYLE_REGISTERDROP)==TBSTYLE_REGISTERDROP )
        styleStr+="|TBSTYLE_REGISTERDROP";

    if ( (style & TBSTYLE_TRANSPARENT)==TBSTYLE_TRANSPARENT )
        styleStr+="|TBSTYLE_TRANSPARENT";

    if ( (style & TBSTYLE_EX_DRAWDDARROWS)==TBSTYLE_EX_DRAWDDARROWS )
        styleStr+="|TBSTYLE_EX_DRAWDDARROWS";

    return styleStr;
}

function StdCtl_CToolBarCtrl(form,component)
{
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CToolBarCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeCommonControlStyle(component, MakeToolBarCtrlStyle(component)) + "," +
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
