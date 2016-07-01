// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeDateTimePickerCtrlStyle(component)
{
    var DTS_UPDOWN         = 0x0001; 
    var DTS_SHOWNONE       = 0x0002;
    var DTS_SHORTDATEFORMAT= 0x0000;
    var DTS_LONGDATEFORMAT = 0x0004;
    var DTS_TIMEFORMAT     = 0x0009;
    var DTS_APPCANPARSE    = 0x0010;
    var DTS_RIGHTALIGN     = 0x0020;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr=MakeWindowStyle(component);

    if ( (style & DTS_UPDOWN)==DTS_UPDOWN )
        styleStr+="|DTS_UPDOWN";

    if(component.Item("ShowNone") == true)
    //if ( (style & DTS_SHOWNONE)==DTS_SHOWNONE )
        styleStr+="|DTS_SHOWNONE";

    if ( (style & DTS_SHORTDATEFORMAT)==DTS_SHORTDATEFORMAT )
        styleStr+="|DTS_SHORTDATEFORMAT";

    if ( (style & DTS_LONGDATEFORMAT)==DTS_LONGDATEFORMAT )
        styleStr+="|DTS_LONGDATEFORMAT";

    if ( (style & DTS_TIMEFORMAT)==DTS_TIMEFORMAT )
        styleStr+="|DTS_TIMEFORMAT";

    if ( (style & DTS_APPCANPARSE)==DTS_APPCANPARSE )
        styleStr+="|DTS_APPCANPARSE";

    if ( (style & DTS_RIGHTALIGN)==DTS_RIGHTALIGN )
        styleStr+="|DTS_RIGHTALIGN";

    return styleStr;
}

function StdCtl_CDateTimePickerCtrl(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CDateTimePickerCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeDateTimePickerCtrlStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    
    if ( component.Item("Form")==true )
        sourceStr+="\t"+component.Item("Name")+"Font"+".CreateFont("+
                   component.Item("Font.Height")+","+
                   "0"+","+//component.Item("Font.Width")+","+
                   "0"+","+//component.Item("Font.Escapement")+","+
                   "0"+","+//component.Item("Font.Orientation")+","+
                   (component.Item("Font.Bold")==true ? "FW_BOLD":"FW_NORMAL")+","+
                   component.Item("Font.Italic")+","+
                   component.Item("Font.Underline")+","+
                   component.Item("Font.StrikeOut")+","+
                   component.Item("Font.CharSet")+","+
                   "OUT_DEFAULT_PRECIS"+","+//component.Item("Font.OutPrecision")+","+
                   "CLIP_DEFAULT_PRECIS"+","+//component.Item("Font.ClipPrecision")+","+
                   "DEFAULT_QUALITY"+","+//component.Item("Font.Quality")+","+
                   "DEFAULT_PITCH|FF_DONTCARE"+","+//component.Item("Font.PitchAndFamily")+","+
                   MakeCString(component.Item("Font.FaceName"))+");\n"+
                   "\t"+component.Item("Name")+".SetMonthCalFont((HFONT)"+component.Item("Name")+"Font);\n";
    else
        sourceStr+="\t"+component.Item("Name")+".SetMonthCalFont((HFONT)m_formFont);\n";    


    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);        
    MakeContained(form,component);

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CDateTimePickerCtrlLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
