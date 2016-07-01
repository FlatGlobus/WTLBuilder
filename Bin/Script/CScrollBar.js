// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeScrollBarStyle(component)
{
    var SBS_HORZ=                    0x0000;
    var SBS_VERT=                    0x0001;
    var SBS_TOPALIGN=                0x0002;
    var SBS_LEFTALIGN=               0x0002;
    var SBS_BOTTOMALIGN=             0x0004;
    var SBS_RIGHTALIGN=              0x0004;
    var SBS_SIZEBOXTOPLEFTALIGN=     0x0002;
    var SBS_SIZEBOXBOTTOMRIGHTALIGN= 0x0004;
    var SBS_SIZEBOX=                 0x0008;
    var SBS_SIZEGRIP=                0x0010;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & 0x0000000F)==SBS_HORZ )
    {
        styleStr+="|SBS_HORZ";
        
        if ( (style & SBS_BOTTOMALIGN)==SBS_BOTTOMALIGN )
            styleStr+="|SBS_BOTTOMALIGN";

        if ( (style & SBS_TOPALIGN)==SBS_TOPALIGN )
            styleStr+="|SBS_TOPALIGN";
    }
    else
        if ( (style & 0x0000000F)==SBS_VERT )
    {
        styleStr+="|SBS_VERT";
        
        if ( (style & SBS_LEFTALIGN)==SBS_LEFTALIGN )
            styleStr+="|SBS_LEFTALIGN";

        if ( (style & SBS_RIGHTALIGN)==SBS_RIGHTALIGN )
            styleStr+="|SBS_RIGHTALIGN";
    }

    return styleStr;
}

function StdCtl_CScrollBar(form,component)
{
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CScrollBar"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL"+","+
               MakeScrollBarStyle(component)+","+
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

function StdCtl_CHScrollBar(form,component)
{
    StdCtl_CScrollBar(form,component);
}

function StdCtl_CVScrollBar(form,component)
{
    StdCtl_CScrollBar(form,component);
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CHScrollBarLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}

function StdCtl_CVScrollBarLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
