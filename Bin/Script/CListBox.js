// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeListBoxStyle(component)
{
    var LBS_NOTIFY=            0x0001;
    var LBS_SORT=              0x0002;
    var LBS_NOREDRAW=          0x0004;
    var LBS_MULTIPLESEL=       0x0008;
    var LBS_OWNERDRAWFIXED=    0x0010;
    var LBS_OWNERDRAWVARIABLE= 0x0020;
    var LBS_HASSTRINGS=        0x0040;
    var LBS_USETABSTOPS=       0x0080;
    var LBS_NOINTEGRALHEIGHT=  0x0100;
    var LBS_MULTICOLUMN=       0x0200;
    var LBS_WANTKEYBOARDINPUT= 0x0400;
    var LBS_EXTENDEDSEL=       0x0800;
    var LBS_DISABLENOSCROLL=   0x1000;
    var LBS_NODATA=            0x2000;
    var LBS_NOSEL=             0x4000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);
    
    if ( (style & LBS_NOTIFY)==LBS_NOTIFY )
        styleStr+="|LBS_NOTIFY";

    if ( (style & LBS_SORT)==LBS_SORT )
        styleStr+="|LBS_SORT";

    if ( (style & LBS_NOREDRAW)==LBS_NOREDRAW )
        styleStr+="|LBS_NOREDRAW";

    if ( (style & LBS_MULTIPLESEL)==LBS_MULTIPLESEL )
        styleStr+="|LBS_MULTIPLESEL";

    if ( (style & LBS_OWNERDRAWFIXED)==LBS_OWNERDRAWFIXED )
        styleStr+="|LBS_OWNERDRAWFIXED";

    if ( (style & LBS_OWNERDRAWVARIABLE)==LBS_OWNERDRAWVARIABLE )
        styleStr+="|LBS_OWNERDRAWVARIABLE";

    if ( (style & LBS_HASSTRINGS)==LBS_HASSTRINGS )
        styleStr+="|LBS_HASSTRINGS";

    if ( (style & LBS_USETABSTOPS)==LBS_USETABSTOPS )
        styleStr+="|LBS_USETABSTOPS";

    if ( component.Item("NoIntegralHeight")==true )
        styleStr+="|LBS_NOINTEGRALHEIGHT";

    if ( (style & LBS_MULTICOLUMN)==LBS_MULTICOLUMN )
        styleStr+="|LBS_MULTICOLUMN";

    if ( (style & LBS_WANTKEYBOARDINPUT)==LBS_WANTKEYBOARDINPUT )
        styleStr+="|LBS_WANTKEYBOARDINPUT";

    if ( (style & LBS_EXTENDEDSEL)==LBS_EXTENDEDSEL )
        styleStr+="|LBS_EXTENDEDSEL";

    if ( (style & LBS_DISABLENOSCROLL)==LBS_DISABLENOSCROLL )
        styleStr+="|LBS_DISABLENOSCROLL";

    if ( (style & LBS_NODATA)==LBS_NODATA )
        styleStr+="|LBS_NODATA";

    if ( (style & LBS_NOSEL)==LBS_NOSEL )
        styleStr+="|LBS_NOSEL";

    return styleStr;
}

function StdCtl_CListBox(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CListBox"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeListBoxStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    
    sourceStr+=MakeStrings(component);
    
    sourceStr+=codegen.Format(component,"\t[!Name].SetItemHeight(0,[!ItemHeight]);\n");
    if ( component.Item("CurSel")!="-1" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetCurSel([!CurSel]);\n");

    if ( component.Item("HorizontalExtent")!="0" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetHorizontalExtent([!HorizontalExtent]);\n");

    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";
    
    MakeSetFocus(form,component);        
    MakeContained(form,component);        

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
///////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CListBoxLocalize(form,component)
{
    var codegen=form.Code;
    var ID=MakeControlNameID(component);
    var str=MakeLocStrings(component,ID,"Strings");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}

