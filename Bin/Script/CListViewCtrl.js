// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeListViewCtrlStyle(component)
{
    var LVS_ICON=                0x0000;
    var LVS_REPORT=              0x0001;
    var LVS_SMALLICON=           0x0002;
    var LVS_LIST=                0x0003;
    var LVS_TYPEMASK=        0x0003;
    var LVS_SINGLESEL=           0x0004;
    var LVS_SHOWSELALWAYS=       0x0008;
    var LVS_SORTASCENDING=       0x0010;
    var LVS_SORTDESCENDING=      0x0020;
    var LVS_SHAREIMAGELISTS=     0x0040;
    var LVS_NOLABELWRAP=         0x0080;
    var LVS_AUTOARRANGE=         0x0100;
    var LVS_EDITLABELS=          0x0200;
    var LVS_OWNERDATA=           0x1000;
    var LVS_NOSCROLL=            0x2000;
    var LVS_TYPESTYLEMASK=       0xfc00;
    var LVS_ALIGNTOP=            0x0000;
    var LVS_ALIGNLEFT=           0x0800;
    var LVS_ALIGNMASK=           0x0c00;
    var LVS_OWNERDRAWFIXED=      0x0400;
    var LVS_NOCOLUMNHEADER=      0x4000;
    var LVS_NOSORTHEADER=        0x8000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & LVS_TYPEMASK)==LVS_ICON )
        styleStr+="|LVS_ICON";

    if ( (style & LVS_TYPEMASK)==LVS_REPORT )
        styleStr+="|LVS_REPORT";

    if ( (style & LVS_TYPEMASK)==LVS_SMALLICON )
        styleStr+="|LVS_SMALLICON";

    if ( (style & LVS_TYPEMASK)==LVS_LIST )
        styleStr+="|LVS_LIST";

    if ( (style & LVS_SINGLESEL)==LVS_SINGLESEL )
        styleStr+="|LVS_SINGLESEL";

    if ( (style & LVS_SHOWSELALWAYS)==LVS_SHOWSELALWAYS )
        styleStr+="|LVS_SHOWSELALWAYS";

    if ( (style & LVS_SORTASCENDING)==LVS_SORTASCENDING )
        styleStr+="|LVS_SORTASCENDING";

    if ( (style & LVS_SORTDESCENDING)==LVS_SORTDESCENDING )
        styleStr+="|LVS_SORTDESCENDING";

    if ( (style & LVS_SHAREIMAGELISTS)==LVS_SHAREIMAGELISTS )
        styleStr+="|LVS_SHAREIMAGELISTS";

    if ( (style & LVS_NOLABELWRAP)==LVS_NOLABELWRAP )
        styleStr+="|LVS_NOLABELWRAP";

    if ( (style & LVS_AUTOARRANGE)==LVS_AUTOARRANGE )
        styleStr+="|LVS_AUTOARRANGE";

    if ( (style & LVS_EDITLABELS)==LVS_EDITLABELS )
        styleStr+="|LVS_EDITLABELS";

    if ( (style & LVS_OWNERDATA)==LVS_OWNERDATA )
        styleStr+="|LVS_OWNERDATA";

    if ( (style & LVS_NOSCROLL)==LVS_NOSCROLL )
        styleStr+="|LVS_NOSCROLL";

    if ( (style & LVS_ALIGNMASK)==LVS_ALIGNTOP )
        styleStr+="|LVS_ALIGNTOP";

    if ( (style & LVS_ALIGNMASK)==LVS_ALIGNLEFT )
        styleStr+="|LVS_ALIGNLEFT";

    if ( (style & LVS_OWNERDRAWFIXED)==LVS_OWNERDRAWFIXED )
        styleStr+="|LVS_OWNERDRAWFIXED";

    if ( (style & LVS_NOCOLUMNHEADER)==LVS_NOCOLUMNHEADER )
        styleStr+="|LVS_NOCOLUMNHEADER";

    if ( (style & LVS_NOSORTHEADER)==LVS_NOSORTHEADER )
        styleStr+="|LVS_NOSORTHEADER";

    return styleStr;
}

function MakeListViewCtrlStyleEx(component)
{
    var styleStr="";


    if ( component.Item("GridLines")==true )
        styleStr+="|LVS_EX_GRIDLINES";

    if ( component.Item("SubItemImages")==true )
        styleStr+="|LVS_EX_SUBITEMIMAGES";

    if ( component.Item("CheckBoxes")==true )
        styleStr+="|LVS_EX_CHECKBOXES";

    if ( component.Item("TrackSelect")==true )
        styleStr+="|LVS_EX_TRACKSELECT";

    if ( component.Item("HeaderDragAndDrop")==true )
        styleStr+="|LVS_EX_HEADERDRAGDROP";

    if ( component.Item("FullRowSelect")==true )
        styleStr+="|LVS_EX_FULLROWSELECT";

    if ( component.Item("OneClickActivate")==true )
        styleStr+="|LVS_EX_ONECLICKACTIVATE";

    if ( component.Item("TwoClickActivate")==true )
        styleStr+="|LVS_EX_TWOCLICKACTIVATE";

    if ( component.Item("FlatSB")==true )
        styleStr+="|LVS_EX_FLATSB";

    if ( component.Item("Regional")==true )
        styleStr+="|LVS_EX_REGIONAL";

    if ( component.Item("InfoTip")==true )
        styleStr+="|LVS_EX_INFOTIP";

    if ( component.Item("UnderLineHot")==true )
        styleStr+="|LVS_EX_UNDERLINEHOT";

    if ( component.Item("UnderLineCold")==true )
        styleStr+="|LVS_EX_UNDERLINECOLD";

    if ( component.Item("MultiWorkAreas")==true )
        styleStr+="|LVS_EX_MULTIWORKAREAS";

    if ( styleStr!="" )
    {
        if ( styleStr.charAt(0)=='|' )
            styleStr=styleStr.substr(1,styleStr.length);

        return "\t"+component.Item("Name")+".SetExtendedListViewStyle("+styleStr+",0);\n";
    }

    return "";

}

function StdCtl_CListViewCtrl(form,component)
{
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CListViewCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeListViewCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    sourceStr+=MakeToolTip(component);

    sourceStr+=MakeListViewCtrlStyleEx(component);
    sourceStr+="\n";
    
    MakeSetFocus(form,component);        
    MakeContained(form,component);   
    
    var codegen=form.Code;
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
