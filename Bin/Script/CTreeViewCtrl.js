// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeTreeViewCtrlStyle(component)
{
    var  TVS_HASBUTTONS=          0x0001;
    var  TVS_HASLINES=            0x0002;
    var  TVS_LINESATROOT=         0x0004;
    var  TVS_EDITLABELS=          0x0008;
    var  TVS_DISABLEDRAGDROP=     0x0010;
    var  TVS_SHOWSELALWAYS=       0x0020;
    var  TVS_RTLREADING=          0x0040;
    var  TVS_NOTOOLTIPS=          0x0080;
    var  TVS_CHECKBOXES=          0x0100;
    var  TVS_TRACKSELECT=         0x0200;
    var  TVS_SINGLEEXPAND=        0x0400;
    var  TVS_INFOTIP=             0x0800;
    var  TVS_FULLROWSELECT=       0x1000;
    var  TVS_NOSCROLL=            0x2000;
    var  TVS_NONEVENHEIGHT=       0x4000;
    var  TVS_NOHSCROLL=           0x8000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & TVS_HASBUTTONS)==TVS_HASBUTTONS )
        styleStr+="|TVS_HASBUTTONS";

    if ( (style & TVS_HASLINES)==TVS_HASLINES )
        styleStr+="|TVS_HASLINES";

    if ( (style & TVS_LINESATROOT)==TVS_LINESATROOT )
        styleStr+="|TVS_LINESATROOT";

    if ( (style & TVS_EDITLABELS)==TVS_EDITLABELS )
        styleStr+="|TVS_EDITLABELS";

    if ( (style & TVS_DISABLEDRAGDROP)==TVS_DISABLEDRAGDROP )
        styleStr+="|TVS_DISABLEDRAGDROP";

    if ( (style & TVS_SHOWSELALWAYS)==TVS_SHOWSELALWAYS )
        styleStr+="|TVS_SHOWSELALWAYS";

    if ( (style & TVS_RTLREADING)==TVS_RTLREADING )
        styleStr+="|TVS_RTLREADING";

    if ( (style & TVS_NOTOOLTIPS)==TVS_NOTOOLTIPS )
        styleStr+="|TVS_NOTOOLTIPS";

    if ( (style & TVS_CHECKBOXES)==TVS_CHECKBOXES )
        styleStr+="|TVS_CHECKBOXES";

    if ( (style & TVS_TRACKSELECT)==TVS_TRACKSELECT )
        styleStr+="|TVS_TRACKSELECT";

    if ( (style & TVS_SINGLEEXPAND)==TVS_SINGLEEXPAND )
        styleStr+="|TVS_SINGLEEXPAND";

    if ( (style & TVS_INFOTIP)==TVS_INFOTIP )
        styleStr+="|TVS_INFOTIP";

    if ( (style & TVS_FULLROWSELECT)==TVS_FULLROWSELECT )
        styleStr+="|TVS_FULLROWSELECT";

    if ( (style & TVS_NOSCROLL)==TVS_NOSCROLL )
        styleStr+="|TVS_NOSCROLL";

    if ( (style & TVS_NONEVENHEIGHT)==TVS_NONEVENHEIGHT )
        styleStr+="|TVS_NONEVENHEIGHT";

    if ( (style & TVS_NOHSCROLL)==TVS_NOHSCROLL )
        styleStr+="|TVS_NOHSCROLL";

    return styleStr;
}

function StdCtl_CTreeViewCtrl(form,component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CTreeViewCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeTreeViewCtrlStyle(component)+","+
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
function StdCtl_CTreeViewCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}

