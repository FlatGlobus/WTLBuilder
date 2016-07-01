// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeTabCtrlStyle(component)
{
    var  TCS_SCROLLOPPOSITE=      0x0001;
    var  TCS_BOTTOM=              0x0002;
    var  TCS_RIGHT=               0x0002;
    var  TCS_MULTISELECT=         0x0004;
    var  TCS_FLATBUTTONS=         0x0008;
    var  TCS_FORCEICONLEFT=       0x0010;
    var  TCS_FORCELABELLEFT=      0x0020;
    var  TCS_HOTTRACK=            0x0040;
    var  TCS_VERTICAL=            0x0080;
    var  TCS_TABS=                0x0000;
    var  TCS_BUTTONS=             0x0100;
    var  TCS_SINGLELINE=          0x0000;
    var  TCS_MULTILINE=           0x0200;
    var  TCS_RIGHTJUSTIFY=        0x0000;
    var  TCS_FIXEDWIDTH=          0x0400;
    var  TCS_RAGGEDRIGHT=         0x0800;
    var  TCS_FOCUSONBUTTONDOWN=   0x1000;
    var  TCS_OWNERDRAWFIXED=      0x2000;
    var  TCS_TOOLTIPS=            0x4000;
    var  TCS_FOCUSNEVER=          0x8000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & TCS_SCROLLOPPOSITE)==TCS_SCROLLOPPOSITE )
        styleStr+="|TCS_SCROLLOPPOSITE";

    if ( (style & TCS_BOTTOM)==TCS_BOTTOM )
        styleStr+="|TCS_BOTTOM";

    if ( (style & TCS_RIGHT)==TCS_RIGHT )
        styleStr+="|TCS_RIGHT";

    if ( (style & TCS_MULTISELECT)==TCS_MULTISELECT )
        styleStr+="|TCS_MULTISELECT";
    else
        styleStr+="|TCS_SINGLELINE";
    
    if ( (style & TCS_FLATBUTTONS)==TCS_FLATBUTTONS )
        styleStr+="|TCS_FLATBUTTONS";

    if ( (style & TCS_FORCEICONLEFT)==TCS_FORCEICONLEFT )
        styleStr+="|TCS_FORCEICONLEFT";

    if ( (style & TCS_FORCELABELLEFT)==TCS_FORCELABELLEFT )
        styleStr+="|TCS_FORCELABELLEFT";

    if ( (style & TCS_HOTTRACK)==TCS_HOTTRACK )
        styleStr+="|TCS_HOTTRACK";

    if ( (style & TCS_VERTICAL)==TCS_VERTICAL )
        styleStr+="|TCS_VERTICAL";

    if ( (style & TCS_TABS)==TCS_TABS )
        styleStr+="|TCS_TABS";

    if ( (style & TCS_BUTTONS)==TCS_BUTTONS )
        styleStr+="|TCS_BUTTONS";

    if ( (style & TCS_MULTILINE)==TCS_MULTILINE )
        styleStr+="|TCS_MULTILINE";

    if ( (style & TCS_RIGHTJUSTIFY)==TCS_RIGHTJUSTIFY )
        styleStr+="|TCS_RIGHTJUSTIFY";

    if ( (style & TCS_FIXEDWIDTH)==TCS_FIXEDWIDTH )
        styleStr+="|TCS_FIXEDWIDTH";

    if ( (style & TCS_RAGGEDRIGHT)==TCS_RAGGEDRIGHT )
        styleStr+="|TCS_RAGGEDRIGHT";

    if ( (style & TCS_FOCUSONBUTTONDOWN)==TCS_FOCUSONBUTTONDOWN )
        styleStr+="|TCS_FOCUSONBUTTONDOWN";

    if ( (style & TCS_OWNERDRAWFIXED)==TCS_OWNERDRAWFIXED )
        styleStr+="|TCS_OWNERDRAWFIXED";

    if ( (style & TCS_TOOLTIPS)==TCS_TOOLTIPS )
        styleStr+="|TCS_TOOLTIPS";

    if ( (style & TCS_FOCUSNEVER)==TCS_FOCUSNEVER )
        styleStr+="|TCS_FOCUSNEVER";

    return styleStr;
}

function StdCtl_CTabCtrl(form,component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CTabCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeTabCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";
    var pages=component.Item("Pages");
    if ( pages.length )
    {
        //sourceStr+="\tTCITEM "+cmpName+"Item = { 0 };\n";
        //sourceStr+="\t"+cmpName+"Item.mask = TCIF_TEXT;\n";
        var pageName="";
        var itemCount=0;
        var curSel=0;
        for ( idx=0; idx < pages.length;idx++ )
        {
            if ( pages.charAt(idx)=='\\' && pages.charAt(idx+1)=='n' )
            {
                sourceStr+="\t"+cmpName+".InsertItem("+itemCount +", "+ MakeLocalizedCStringEx(pageName,"."+itemCount,component)+");\n";
                if ( pageName==component.Item("CurSel") )
                    curSel=itemCount;

                pageName="";
                idx+=1;
                itemCount+=1;
            }
            else
                pageName+=pages.charAt(idx);
        }
        sourceStr+="\t"+cmpName+".SetCurSel("+curSel+");\n"
    }
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
///////////////////////////////////////////////////////////////////////////////////////////////
function MakeTabLocStrings(component)
{
    var strings=component.Item("Pages");
    var sourceStr="";
    var str="";
    for ( idx=0; idx < strings.length;idx++ )
    {
        if ( strings.charAt(idx)=='\\' && strings.charAt(idx+1)=='n' )
        {
            sourceStr+=","+str;
            str="";
            idx+=1;
        }
        else
            str+=strings.charAt(idx);
    }

    if ( sourceStr.charAt(0)==',' )
        sourceStr=sourceStr.substr(1,sourceStr.length);

    return sourceStr;
}

function StdCtl_CTabCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var ID=MakeControlNameID(component);
    var str=MakeLocStrings(component,ID,"Pages");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}

