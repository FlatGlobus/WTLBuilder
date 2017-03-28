// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
function MakeButtonStyle(component)
{
    var BS_DEFPUSHBUTTON=    0x00000001;
    var BS_CHECKBOX=         0x00000002;
    var BS_AUTOCHECKBOX=     0x00000003;
    var BS_RADIOBUTTON=      0x00000004;
    var BS_3STATE=           0x00000005;
    var BS_AUTO3STATE=       0x00000006;
    var BS_GROUPBOX=         0x00000007;
    var BS_USERBUTTON=       0x00000008;
    var BS_AUTORADIOBUTTON=  0x00000009;
    var BS_OWNERDRAW=        0x0000000B;
    var BS_LEFTTEXT=         0x00000020;
    var BS_ICON=             0x00000040;
    var BS_BITMAP=           0x00000080;
    var BS_LEFT=             0x00000100;
    var BS_RIGHT=            0x00000200;
    var BS_CENTER=           0x00000300;
    var BS_TOP=              0x00000400;
    var BS_BOTTOM=           0x00000800;
    var BS_VCENTER=          0x00000C00;
    var BS_PUSHLIKE=         0x00001000;
    var BS_MULTILINE=        0x00002000;
    var BS_NOTIFY=           0x00004000;
    var BS_FLAT=             0x00008000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);
    
    if ( (style & 0x0000000F) == BS_DEFPUSHBUTTON )
        styleStr+="|BS_DEFPUSHBUTTON";

    if ( (style & 0x0000000F)== BS_CHECKBOX )
        styleStr+="|BS_CHECKBOX";

    if ( (style & 0x0000000F)== BS_AUTOCHECKBOX )
        styleStr+="|BS_AUTOCHECKBOX";

    if ( (style & 0x0000000F)== BS_RADIOBUTTON )
        styleStr+="|BS_RADIOBUTTON";

    if ( (style & 0x0000000F)== BS_3STATE )
        styleStr+="|BS_3STATE";

    if ( (style & 0x0000000F)== BS_AUTO3STATE )
        styleStr+="|BS_AUTO3STATE";

    if ( (style & 0x0000000F)== BS_GROUPBOX )
        styleStr+="|BS_GROUPBOX";

    if ( (style & 0x0000000F)== BS_USERBUTTON )
        styleStr+="|BS_USERBUTTON";

    if ( (style & 0x0000000F)== BS_AUTORADIOBUTTON )
        styleStr+="|BS_AUTORADIOBUTTON";

    if ( (style & 0x0000000F)== BS_OWNERDRAW )
        styleStr+="|BS_OWNERDRAW";

    if ( (style & 0x000000F0)==BS_LEFTTEXT )
        styleStr+="|BS_LEFTTEXT";

    if ( (style & BS_ICON)==BS_ICON )
        styleStr+="|BS_ICON";
    else
        if ( (style & BS_BITMAP)==BS_BITMAP )
        styleStr+="|BS_BITMAP";
    else
        styleStr+="|BS_TEXT";
    
    if ( (style & BS_CENTER)==BS_CENTER )
        styleStr+="|BS_CENTER";
    else
        if ( (style & BS_RIGHT)==BS_RIGHT )
        styleStr+="|BS_RIGHT";
    else
        styleStr+="|BS_LEFT";
    
    if ( (style & BS_VCENTER)==BS_VCENTER )
        styleStr+="|BS_VCENTER";
    else
        if ( (style & BS_TOP)==BS_TOP )
        styleStr+="|BS_TOP";
    else
        styleStr+="|BS_BOTTOM";
    
    if ( (style & BS_PUSHLIKE)!=0 )
        styleStr+="|BS_PUSHLIKE";

    if ( (style & BS_MULTILINE)!=0 )
        styleStr+="|BS_MULTILINE";

    if ( (style & BS_NOTIFY)!=0 )
        styleStr+="|BS_NOTIFY";

    if ( (style & BS_FLAT)!=0 )
        styleStr+="|BS_FLAT";

    return styleStr;
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CButton(form,component)
{
    var codegen=form.Code;
    
    CheckComponent(form, component);

    var headerStr=codegen.Format(component,"\tCButton\t[!Name];\n"); 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);

    var sourceStr=codegen.Format(component,"\t[!Name].Create([!ParentName],");    
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Caption"),component)+","+
               MakeButtonStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);  
    sourceStr+=MakeToolTip(component);  
    
    if ( component.Item("Style")=="BS_BITMAP" )
    {
        CheckProperty(form, component, "Image.ID", "");
        headerStr+=codegen.Format(component,"\tCBitmap\t[!Name]Bitmap;\n"); 
        sourceStr+=codegen.Format(component,"\t[!Name]Bitmap.LoadBitmap([!Image.ID]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetBitmap([!Name]Bitmap);\n");
    }
    else
        if ( component.Item("Style")=="BS_ICON" )
        {
            CheckProperty(form, component, "Image.ID", "");
            headerStr+=codegen.Format(component,"\tHICON\t[!Name]Icon;\n"); 
            sourceStr+=codegen.Format(component,"\t[!Name]Icon=AtlLoadIcon([!Image.ID]);\n");
            sourceStr+=codegen.Format(component,"\t[!Name].SetIcon([!Name]Icon);\n");
            var destructionStr=codegen.Format(component,"\tif([!Name]Icon!=NULL)\n");
            destructionStr+=codegen.Format(component,"\t\t::DeleteObject([!Name]Icon);\n");
            codegen.Insert(endMemberDestruction,destructionStr);
        }
    sourceStr+="\n";

    MakeSetFocus(form,component);
    MakeContained(form,component);
    
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CCheckBox(form,component)
{
    StdCtl_CButton(form,component);
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CRadioButton(form,component)
{
    StdCtl_CButton(form,component);
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CGroupBox(form,component)
{
    StdCtl_CButton(form,component);
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CButtonLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Caption")!="" )
        str=ID + codegen.Format(component," = [!Caption]\n");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CCheckBoxLocalize(form,component)
{
    StdCtl_CButtonLocalize(form,component);
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CRadioButtonLocalize(form,component)
{
    StdCtl_CButtonLocalize(form,component);
}
////////////////////////////////////////////////////////////////////////////////
function StdCtl_CGroupBoxLocalize(form,component)
{
    StdCtl_CButtonLocalize(form,component);
}
