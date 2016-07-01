// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeComboBoxStyle(component)
{
    var CBS_SIMPLE=            0x0001;
    var CBS_DROPDOWN=          0x0002;
    var CBS_DROPDOWNLIST=      0x0003;
    var CBS_OWNERDRAWFIXED=    0x0010;
    var CBS_OWNERDRAWVARIABLE= 0x0020;
    var CBS_AUTOHSCROLL=       0x0040;
    var CBS_OEMCONVERT=        0x0080;
    var CBS_SORT=              0x0100;
    var CBS_HASSTRINGS=        0x0200;
    var CBS_NOINTEGRALHEIGHT=  0x0400;
    var CBS_DISABLENOSCROLL=   0x0800;
    var CBS_UPPERCASE=         0x2000;
    var CBS_LOWERCASE=         0x4000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & CBS_DROPDOWNLIST)==CBS_DROPDOWNLIST )
        styleStr+="|CBS_DROPDOWNLIST";
    else
        if ( (style & CBS_SIMPLE)==CBS_SIMPLE )
        styleStr+="|CBS_SIMPLE";
    else
        if ( (style & CBS_DROPDOWN)==CBS_DROPDOWN )
        styleStr+="|CBS_DROPDOWN";

    if ( (style & CBS_OWNERDRAWFIXED)==CBS_OWNERDRAWFIXED )
        styleStr+="|CBS_OWNERDRAWFIXED";

    if ( (style & CBS_OWNERDRAWVARIABLE)==CBS_OWNERDRAWVARIABLE )
        styleStr+="|CBS_OWNERDRAWVARIABLE";

    if ( (style & CBS_AUTOHSCROLL)==CBS_AUTOHSCROLL )
        styleStr+="|CBS_AUTOHSCROLL";

    if ( (style & CBS_OEMCONVERT)==CBS_OEMCONVERT )
        styleStr+="|CBS_OEMCONVERT";

    if ( (style & CBS_SORT)==CBS_SORT )
        styleStr+="|CBS_SORT";

    if ( (style & CBS_HASSTRINGS)==CBS_HASSTRINGS )
        styleStr+="|CBS_HASSTRINGS";

    if ( (style & CBS_NOINTEGRALHEIGHT)==CBS_NOINTEGRALHEIGHT )
        styleStr+="|CBS_NOINTEGRALHEIGHT";

    if ( (style & CBS_DISABLENOSCROLL)==CBS_DISABLENOSCROLL )
        styleStr+="|CBS_DISABLENOSCROLL";

    if ( (style & CBS_UPPERCASE)==CBS_UPPERCASE )
        styleStr+="|CBS_UPPERCASE";

    if ( (style & CBS_LOWERCASE)==CBS_LOWERCASE )
        styleStr+="|CBS_LOWERCASE";

    return styleStr;
}

function StdCtl_CComboBox(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CComboBox"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeComboBoxStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    
    sourceStr+=MakeControlFont(component);
    
    sourceStr+=MakeStrings(component);
    
    if ( component.Item("Style")!="DropDownList" )//CBS_DROPDOWNLIST
    {
        sourceStr+=codegen.Format(component,"\t[!Name].LimitText([!LimitText]);\n"); 
        sourceStr+=codegen.Format(component,"\t[!Name].SetItemHeight(-1,[!EditHeight]);\n");  
    }

    if ( component.Item("CurSel")!="-1" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetCurSel([!CurSel]);\n");

    sourceStr+=codegen.Format(component,"\t[!Name].SetItemHeight(0,[!ItemHeight]);\n");
    
    if ( component.Item("DroppedWidth")!="0" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetDroppedWidth([!DroppedWidth]);\n");

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
///////////////////////////////////////////////////////////////////////////////////////////////

function StdCtl_CComboBoxLocalize(form,component)
{
    var codegen=form.Code;

    var ID=MakeControlNameID(component);
    var str=MakeLocStrings(component,ID,"Strings");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
