// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeStaticStyle(component)
{
    var SS_LEFT=             0x00000000;
    var SS_CENTER=           0x00000001;
    var SS_RIGHT=            0x00000002;
    var SS_ICON=             0x00000003;
    var SS_BLACKRECT=        0x00000004;
    var SS_GRAYRECT=         0x00000005;
    var SS_WHITERECT=        0x00000006;
    var SS_BLACKFRAME=       0x00000007;
    var SS_GRAYFRAME=        0x00000008;
    var SS_WHITEFRAME=       0x00000009;
    var SS_USERITEM=         0x0000000A;
    var SS_SIMPLE=           0x0000000B;
    var SS_LEFTNOWORDWRAP=   0x0000000C;
    var SS_OWNERDRAW=        0x0000000D;
    var SS_BITMAP=           0x0000000E;
    var SS_ENHMETAFILE=      0x0000000F;
    var SS_ETCHEDHORZ=       0x00000010;
    var SS_ETCHEDVERT=       0x00000011;
    var SS_ETCHEDFRAME=      0x00000012;
    var SS_TYPEMASK=         0x0000001F;
    var SS_REALSIZECONTROL=  0x00000040;
    var SS_NOPREFIX=         0x00000080; 
    var SS_NOTIFY=           0x00000100;
    var SS_CENTERIMAGE=      0x00000200;
    var SS_RIGHTJUST=        0x00000400;
    var SS_REALSIZEIMAGE=    0x00000800;
    var SS_SUNKEN=           0x00001000;
    var SS_ENDELLIPSIS=      0x00004000;
    var SS_PATHELLIPSIS=     0x00008000;
    var SS_WORDELLIPSIS=     0x0000C000;
    var SS_ELLIPSISMASK=     0x0000C000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    
    var styleStr=MakeWindowStyle(component);
    
    if ( (style & SS_LEFT)==SS_LEFT )
        styleStr+="|SS_LEFT";

    if ( (style & SS_CENTER)==SS_CENTER )
        styleStr+="|SS_CENTER";

    if ( (style & SS_RIGHT)==SS_RIGHT )
        styleStr+="|SS_RIGHT";

    if ( (style & SS_ICON)==SS_ICON )
        styleStr+="|SS_ICON";

    if ( (style & SS_BLACKRECT)==SS_BLACKRECT )
        styleStr+="|SS_BLACKRECT";

    if ( (style & SS_GRAYRECT)==SS_GRAYRECT )
        styleStr+="|SS_GRAYRECT";

    if ( (style & SS_WHITERECT)==SS_WHITERECT )
        styleStr+="|SS_WHITERECT";

    if ( (style & SS_BLACKFRAME)==SS_BLACKFRAME )
        styleStr+="|SS_BLACKFRAME";

    if ( (style & SS_GRAYFRAME)==SS_GRAYFRAME )
        styleStr+="|SS_GRAYFRAME";

    if ( (style & SS_WHITEFRAME)==SS_WHITEFRAME )
        styleStr+="|SS_WHITEFRAME";

    if ( (style & SS_USERITEM)==SS_USERITEM )
        styleStr+="|SS_USERITEM";

    if ( (style & SS_SIMPLE)==SS_SIMPLE )
        styleStr+="|SS_SIMPLE";

    if ( (style & SS_LEFTNOWORDWRAP)==SS_LEFTNOWORDWRAP )
        styleStr+="|SS_LEFTNOWORDWRAP";

    if ( (style & SS_OWNERDRAW)==SS_OWNERDRAW )
        styleStr+="|SS_OWNERDRAW";

    if ( (style & SS_BITMAP)==SS_BITMAP )
        styleStr+="|SS_BITMAP";

    if ( (style & SS_ENHMETAFILE)==SS_ENHMETAFILE )
        styleStr+="|SS_ENHMETAFILE";

    if ( (style & SS_ETCHEDHORZ)==SS_ETCHEDHORZ )
        styleStr+="|SS_ETCHEDHORZ";

    if ( (style & SS_ETCHEDVERT)==SS_ETCHEDVERT )
        styleStr+="|SS_ETCHEDVERT";

    if ( (style & SS_ETCHEDFRAME)==SS_ETCHEDFRAME )
        styleStr+="|SS_ETCHEDFRAME";

    if ( (style & SS_TYPEMASK)==SS_TYPEMASK )
        styleStr+="|SS_TYPEMASK";

    if ( (style & SS_REALSIZECONTROL)==SS_REALSIZECONTROL )
        styleStr+="|SS_REALSIZECONTROL";

    if ( (style & SS_NOPREFIX)==SS_NOPREFIX )
        styleStr+="|SS_NOPREFIX";

    if ( (style & SS_NOTIFY)==SS_NOTIFY )
        styleStr+="|SS_NOTIFY";

    if ( (style & SS_CENTERIMAGE)==SS_CENTERIMAGE )
        styleStr+="|SS_CENTERIMAGE";

    if ( (style & SS_RIGHTJUST)==SS_RIGHTJUST )
        styleStr+="|SS_RIGHTJUST";

    if ( (style & SS_REALSIZEIMAGE)==SS_REALSIZEIMAGE )
        styleStr+="|SS_REALSIZEIMAGE";

    if ( (style & SS_SUNKEN)==SS_SUNKEN )
        styleStr+="|SS_SUNKEN";

    if ( (style & SS_ENDELLIPSIS)==SS_ENDELLIPSIS )
        styleStr+="|SS_ENDELLIPSIS";

    if ( (style & SS_PATHELLIPSIS)==SS_PATHELLIPSIS )
        styleStr+="|SS_PATHELLIPSIS";

    if ( (style & SS_WORDELLIPSIS)==SS_WORDELLIPSIS )
        styleStr+="|SS_WORDELLIPSIS";

    if ( (style & SS_ELLIPSISMASK)==SS_ELLIPSISMASK )
        styleStr+="|SS_ELLIPSISMASK";

    return styleStr;
}

function StdCtl_CStatic(form,component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CStatic"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Caption"),component)+","+
               MakeStaticStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    


    if ( component.Item("Image.ImageType")=="Bitmap" && component.Item("Image.ID")!="" )
    {
        headerStr+=codegen.Format(component,"\tCBitmap\t[!Name]Bitmap;\n"); 
        sourceStr+=codegen.Format(component,"\t[!Name]Bitmap.LoadBitmap([!Image.ID]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetBitmap([!Name]Bitmap);\n");
    }
    else
        if ( component.Item("Image.ImageType")=="Icon" && component.Item("Image.ID")!="" )
    {
        headerStr+=codegen.Format(component,"\tHICON\t[!Name]Icon;\n"); 
        sourceStr+=codegen.Format(component,"\t[!Name]Icon=AtlLoadIconImage([!Image.ID],LR_DEFAULTCOLOR | LR_DEFAULTSIZE,32,32);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetIcon([!Name]Icon);\n");
        var destructionStr=codegen.Format(component,"\tif([!Name]Icon!=NULL)\n");
        destructionStr+=codegen.Format(component,"\t\t::DeleteObject([!Name]Icon);\n");
        codegen.Insert(endMemberDestruction,destructionStr);
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
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CStaticLocalize(form,component)
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
////////////////////////////////////////////////////////////////////////////////////////////////
function StdCtl_CPicture(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CStatic"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL,"+
               MakeStaticStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    

    if ( component.Item("Image.ImageType")=="Bitmap" && component.Item("Image.ID")!="" )
    {
        headerStr+=codegen.Format(component,"\tCBitmap\t[!Name]Bitmap;\n"); 
        sourceStr+=codegen.Format(component,"\t[!Name]Bitmap.LoadBitmap([!Image.ID]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetBitmap([!Name]Bitmap);\n");
    }
    else
        if ( component.Item("Image.ImageType")=="Icon" && component.Item("Image.ID")!="" )
    {
        headerStr+=codegen.Format(component,"\tHICON\t[!Name]Icon;\n"); 
        sourceStr+=codegen.Format(component,"\t[!Name]Icon=AtlLoadIconImage([!Image.ID],LR_DEFAULTCOLOR | LR_DEFAULTSIZE,[!Image.Width],[!Image.Height]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetIcon([!Name]Icon);\n");
        var destructionStr=codegen.Format(component,"\tif([!Name]Icon!=NULL)\n");
        destructionStr+=codegen.Format(component,"\t\t::DeleteObject([!Name]Icon);\n");
        codegen.Insert(endMemberDestruction,destructionStr);
    }
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";
    
    MakeSetFocus(form,component);        
    MakeContained(form,component);
    
    var codegen=form.Code;
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function StdCtl_CPictureLocalize(form,component)
{
    StdCtl_CStaticLocalize(form,component);
}