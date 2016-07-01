// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeRect(component)
{
    var left=parseInt(component.Item("Left"));
    var top=parseInt(component.Item("Top"));
    var right=parseInt(component.Item("Width"))+left;
    var bottom=parseInt(component.Item("Height"))+top;
    return "CRect("+left.toString(10)+","+top.toString(10)+","+
        right.toString(10)+","+bottom.toString(10)+")";
}
/////////////////////////////////////////////////////////////////////////////////
function MakeCString(str)
{
    if ( str.length==0 )
        return "_T(\"\")";

    if ( str=="NULL" )
        return str;

    var ret="_T(\"";
    var ch='';
    for ( i=0; i < str.length; i++ )
    {
        ch=str.charAt(i);
        if ( ch=='\\' )
            ret+='\\';
        ret+=ch;
    }
    ret+="\")"; 
    return ret;
}
/////////////////////////////////////////////////////////////////////////////////
function MakeLocalizedCString(str, component)
{
    if(component.IsControl() == true)
    {
        if(component.Form.Item("Localize") == true && component.Item("Localize") == true)
            return "Translate(" + MakeCString(MakeControlNameID(component)) + "," + MakeCString(str)+")";
    }
    if(component.IsForm() == true)
    {
        if(component.Item("Localize") == true)
            return "Translate(" + MakeCString("Caption") + "," + MakeCString(str)+")";
    }
    return MakeCString(str);
}
/////////////////////////////////////////////////////////////////////////////////
function MakeLocalizedCStringEx(str, ext, component)
{
    if(component.IsControl() == true)
    {
        if(component.Form.Item("Localize") == true && component.Item("Localize") == true)
            return "Translate(" + MakeCString(MakeControlNameID(component) + ext) + "," + MakeCString(str)+")";
    }
    if(component.IsForm() == true)
    {
        if(component.Item("Localize") == true)
            return "Translate(" + MakeCString("Caption" + ext) + "," + MakeCString(str)+")";
    }
    return MakeCString(str);
}
/////////////////////////////////////////////////////////////////////////////////
function MakeFontDeclaration(component)
{
    if ( component.Item("Font")==true )
        return "\tCFont\t"+component.Item("Name")+"Font;\n";
    else
        return "";  
}
/////////////////////////////////////////////////////////////////////////////////
function MakeControlFont(component)
{
    if ( component.Item("Font")==true )
        return "\t"+component.Item("Name")+"Font"+".CreateFont("+
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
        "\t"+component.Item("Name")+".SetFont((HFONT)"+component.Item("Name")+"Font);\n";
    else
        return "\t"+component.Item("Name")+".SetFont((HFONT)m_formFont);\n";    
}
/////////////////////////////////////////////////////////////////////////////////
function MakeFormFont(component)
{
    return "\tm_formFont.CreateFont("+
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
    MakeCString(component.Item("Font.FaceName"))+");\n";
}
/////////////////////////////////////////////////////////////////////////////////
function MakeNamedFontDeclaration(fontName,component)
{
    return "\tCFont\t"+component.Item("Name")+fontName+";\n";
}
/////////////////////////////////////////////////////////////////////////////////
function MakeNamedFont(fontName,component)
{
    return "\t"+component.Item("Name")+fontName+".CreateFont("+
    component.Item(fontName+".Height")+","+
    "0"+","+//component.Item("Font.Width")+","+
    "0"+","+//component.Item("Font.Escapement")+","+
    "0"+","+//component.Item("Font.Orientation")+","+
    (component.Item(fontName+".Bold")==true ? "FW_BOLD":"FW_NORMAL")+","+
    component.Item(fontName+".Italic")+","+
    component.Item(fontName+".Underline")+","+
    component.Item(fontName+".StrikeOut")+","+
    component.Item(fontName+".CharSet")+","+
    "OUT_DEFAULT_PRECIS"+","+//component.Item("Font.OutPrecision")+","+
    "CLIP_DEFAULT_PRECIS"+","+//component.Item("Font.ClipPrecision")+","+
    "DEFAULT_QUALITY"+","+//component.Item("Font.Quality")+","+
    "DEFAULT_PITCH|FF_DONTCARE"+","+//component.Item("Font.PitchAndFamily")+","+
    MakeCString(component.Item(fontName+".FaceName"))+");\n";
}
/////////////////////////////////////////////////////////////////////////////////
function MakeWindowStyle(component)
{
    var WS_CHILD =           0x40000000;
    var WS_MINIMIZE=         0x20000000;
    var WS_VISIBLE=          0x10000000;
    var WS_DISABLED=         0x08000000;
    var WS_CLIPSIBLINGS=     0x04000000;
    var WS_CLIPCHILDREN=     0x02000000;
    var WS_MAXIMIZE=         0x01000000;
    var WS_CAPTION=          0x00C00000;
    var WS_BORDER=           0x00800000;
    var WS_DLGFRAME=         0x00400000;
    var WS_VSCROLL=          0x00200000;
    var WS_HSCROLL=          0x00100000;
    var WS_SYSMENU=          0x00080000;
    var WS_THICKFRAME=       0x00040000;
    var WS_GROUP=            0x00020000;
    var WS_TABSTOP=          0x00010000;
    var WS_MINIMIZEBOX =     0x00020000;
    var WS_MAXIMIZEBOX =     0x00010000;

    var style=parseInt(component.Item("InternalWindowStyle"),10);
    var styleStr = component.Item("WindowStyle");

    if (styleStr != "WS_CHILD" && (style & WS_CHILD) == WS_CHILD)
        styleStr += "|WS_CHILD";

    if (component.Item("Visible") == true)
        styleStr += "|WS_VISIBLE";

    if ( (style & WS_DISABLED)==WS_DISABLED )
        styleStr+="|WS_DISABLED";

    if ( (style & WS_CLIPSIBLINGS)==WS_CLIPSIBLINGS )
        styleStr+="|WS_CLIPSIBLINGS";

    if ( (style & WS_CLIPCHILDREN)==WS_CLIPCHILDREN )
        styleStr+="|WS_CLIPCHILDREN";

    // WS_CAPTION = WS_BORDER | WS_DLGFRAME
    if ( (style & WS_CAPTION)==WS_CAPTION )
        styleStr += "|WS_CAPTION";
    else
    {
        if ((style & WS_DLGFRAME) == WS_DLGFRAME)
            styleStr += "|WS_DLGFRAME";

        if ((style & WS_BORDER) == WS_BORDER)
            styleStr += "|WS_BORDER";
    }

    if ( (style & WS_VSCROLL)==WS_VSCROLL )
        styleStr+="|WS_VSCROLL";

    if ( (style & WS_HSCROLL)==WS_HSCROLL )
        styleStr+="|WS_HSCROLL";

    if ( (style & WS_SYSMENU)==WS_SYSMENU )
        styleStr+="|WS_SYSMENU";

    if ((style & WS_MINIMIZE) == WS_MINIMIZE)
        styleStr += "|WS_MINIMIZE";

    if ((style & WS_MAXIMIZE) == WS_MAXIMIZE)
        styleStr += "|WS_MAXIMIZE";

    if ((style & WS_THICKFRAME) == WS_THICKFRAME)
        styleStr += "|WS_THICKFRAME";

    if (component.IsControl == true)
    {
        if ((style & (WS_GROUP)) == WS_GROUP)
            styleStr += "|WS_GROUP";

        if ((style & WS_TABSTOP) == WS_TABSTOP)
            styleStr += "|WS_TABSTOP";
    }
    else
    {
        if ((style & WS_MINIMIZEBOX) == WS_MINIMIZEBOX)
            styleStr += "|WS_MINIMIZEBOX";

        if ((style & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX)
            styleStr += "|WS_MAXIMIZEBOX";
    }

    if ( styleStr.charAt(0)=='|' )
        styleStr=styleStr.substr(1,styleStr.length);

    return styleStr;
}
/////////////////////////////////////////////////////////////////////////////////
function MakeExWindowStyle(component)
{
    var WS_EX_DLGMODALFRAME=     0x00000001;
    var WS_EX_NOPARENTNOTIFY=    0x00000004;
    var WS_EX_TOPMOST=           0x00000008;
    var WS_EX_ACCEPTFILES=       0x00000010;
    var WS_EX_TRANSPARENT=       0x00000020;
    var WS_EX_MDICHILD=          0x00000040;
    var WS_EX_TOOLWINDOW=        0x00000080;
    var WS_EX_WINDOWEDGE=        0x00000100;
    var WS_EX_CLIENTEDGE=        0x00000200;
    var WS_EX_CONTEXTHELP=       0x00000400;
    var WS_EX_RIGHT=             0x00001000;
    var WS_EX_RTLREADING=        0x00002000;
    var WS_EX_LEFTSCROLLBAR=     0x00004000;
    var WS_EX_CONTROLPARENT=     0x00010000;
    var WS_EX_STATICEDGE=        0x00020000;
    var WS_EX_APPWINDOW=         0x00040000;
    var WS_EX_LAYERED=           0x00080000;
    var WS_EX_NOINHERITLAYOUT=   0x00100000;
    var WS_EX_LAYOUTRTL=         0x00400000; 
    var WS_EX_COMPOSITED=        0x02000000;
    var WS_EX_NOACTIVATE=        0x08000000;

    var style=parseInt(component.Item("InternalWindowStyleEx"),10);
    var styleStr="";
    
    if ( (style & WS_EX_DLGMODALFRAME)==WS_EX_DLGMODALFRAME )
        styleStr+="|WS_EX_DLGMODALFRAME";

    if ( (style & WS_EX_NOPARENTNOTIFY)==WS_EX_NOPARENTNOTIFY )
        styleStr+="|WS_EX_NOPARENTNOTIFY";

    if ( (style & WS_EX_TOPMOST)==WS_EX_TOPMOST )
        styleStr+="|WS_EX_TOPMOST";

    if ( (style & WS_EX_ACCEPTFILES)==WS_EX_ACCEPTFILES )
        styleStr+="|WS_EX_ACCEPTFILES";

    if ( (style & WS_EX_TRANSPARENT)==WS_EX_TRANSPARENT )
        styleStr+="|WS_EX_TRANSPARENT";

    if ( (style & WS_EX_MDICHILD)==WS_EX_MDICHILD )
        styleStr+="|WS_EX_MDICHILD";

    if ( (style & WS_EX_TOOLWINDOW)==WS_EX_TOOLWINDOW )
        styleStr+="|WS_EX_TOOLWINDOW";

    if ( (style & WS_EX_WINDOWEDGE)==WS_EX_WINDOWEDGE )
        styleStr+="|WS_EX_WINDOWEDGE";

    if ( (style & WS_EX_CLIENTEDGE)==WS_EX_CLIENTEDGE )
        styleStr+="|WS_EX_CLIENTEDGE";

    if ( (style & WS_EX_CONTEXTHELP)==WS_EX_CONTEXTHELP )
        styleStr+="|WS_EX_CONTEXTHELP";

    if ( (style & WS_EX_RIGHT)==WS_EX_RIGHT )
        styleStr+="|WS_EX_RIGHT";

    if ( (style & WS_EX_RTLREADING)==WS_EX_RTLREADING )
        styleStr+="|WS_EX_RTLREADING";

    if ( (style & WS_EX_LEFTSCROLLBAR)==WS_EX_LEFTSCROLLBAR )
        styleStr+="|WS_EX_LEFTSCROLLBAR";

    if ( (style & WS_EX_CONTROLPARENT)==WS_EX_CONTROLPARENT )
        styleStr+="|WS_EX_CONTROLPARENT";

    if ( (style & WS_EX_STATICEDGE)==WS_EX_STATICEDGE )
        styleStr+="|WS_EX_STATICEDGE";

    if ( (style & WS_EX_APPWINDOW)==WS_EX_APPWINDOW )
        styleStr+="|WS_EX_APPWINDOW";

    if ( (style & WS_EX_LAYERED)==WS_EX_LAYERED )
        styleStr+="|WS_EX_LAYERED";

    if ( (style & WS_EX_NOINHERITLAYOUT)==WS_EX_NOINHERITLAYOUT )
        styleStr+="|WS_EX_NOINHERITLAYOUT";

    if ( (style & WS_EX_LAYOUTRTL)==WS_EX_LAYOUTRTL )
        styleStr+="|WS_EX_LAYOUTRTL";

    if ( (style & WS_EX_COMPOSITED)==WS_EX_COMPOSITED )
        styleStr+="|WS_EX_COMPOSITED";

    if ( (style & WS_EX_NOACTIVATE)==WS_EX_NOACTIVATE )
        styleStr+="|WS_EX_NOACTIVATE";

    if ( styleStr.length==0 )
        styleStr="0";
    else
        if ( styleStr.charAt(0)=='|' )
        styleStr=styleStr.substr(1,styleStr.length);

    return  styleStr;
}
/////////////////////////////////////////////////////////////////////////////////
function MakeWindowClassStyle(component)
{
    var CS_VREDRAW          = 0x0001;
    var CS_HREDRAW          = 0x0002;
    var CS_DBLCLKS          = 0x0008;
    var CS_OWNDC            = 0x0020;
    var CS_CLASSDC          = 0x0040;
    var CS_PARENTDC         = 0x0080;
    var CS_NOCLOSE          = 0x0200;
    var CS_SAVEBITS         = 0x0800;
    var CS_BYTEALIGNCLIENT  = 0x1000;
    var CS_BYTEALIGNWINDOW  = 0x2000;
    var CS_GLOBALCLASS      = 0x4000;
    var CS_IME              = 0x00010000;
    var CS_DROPSHADOW       = 0x00020000;

    var style=parseInt(component.Item("WindowClassStyle"),10);
    var styleStr="";
    
    if ( (style & CS_VREDRAW)==CS_VREDRAW )
        styleStr+="|CS_VREDRAW";

    if ( (style & CS_HREDRAW)==CS_HREDRAW )
        styleStr+="|CS_HREDRAW";

    if ( (style & CS_DBLCLKS)==CS_DBLCLKS )
        styleStr+="|CS_DBLCLKS";

    if ( (style & CS_OWNDC)==CS_OWNDC )
        styleStr+="|CS_OWNDC";

    if ( (style & CS_CLASSDC)==CS_CLASSDC )
        styleStr+="|CS_CLASSDC";

    if ( (style & CS_PARENTDC)==CS_PARENTDC )
        styleStr+="|CS_PARENTDC";

    if ( (style & CS_NOCLOSE)==CS_NOCLOSE )
        styleStr+="|CS_NOCLOSE";

    if ( (style & CS_SAVEBITS)==CS_SAVEBITS )
        styleStr+="|CS_SAVEBITS";

    if ( (style & CS_BYTEALIGNCLIENT)==CS_BYTEALIGNCLIENT )
        styleStr+="|CS_BYTEALIGNCLIENT";

    if ( (style & CS_BYTEALIGNWINDOW)==CS_BYTEALIGNWINDOW )
        styleStr+="|CS_BYTEALIGNWINDOW";

    if ( (style & CS_GLOBALCLASS)==CS_GLOBALCLASS )
        styleStr+="|CS_GLOBALCLASS";

    if ((style & CS_IME) == CS_IME)
        styleStr += "|CS_IME";

    if ((style & CS_DROPSHADOW) == CS_DROPSHADOW)
        styleStr += "|CS_DROPSHADOW";

    if ( styleStr.length==0 )
        styleStr="0";
    else
        if ( styleStr.charAt(0)=='|' )
        styleStr=styleStr.substr(1,styleStr.length);

    return  styleStr;
    
}
/////////////////////////////////////////////////////////////////////////////////
function MakeControlID(component)
{
    if(CheckStandardID(component) == true)
        return "";
    return "#define\t"+component.Item("ID")+"\t"+MakeControlNameID(component)+"\n";
}
/////////////////////////////////////////////////////////////////////////////////
function MakeControlNameID(component)
{
    if(CheckStandardID(component) == true)
        return String(parseInt(component.Item("UniqueID"),10));
    return String(parseInt(component.Item("UniqueID"),10)+parseInt(component.Form.Item("BaseCtrlID"),10));
}
/////////////////////////////////////////////////////////////////////////////////
function CheckStandardID(component)
{
    var idName=component.Item("ID");
    
    if ( "IDOK"==idName ||
         "IDCANCEL"==idName ||
         "IDABORT"==idName ||
         "IDRETRY"==idName ||
         "IDIGNORE"==idName ||
         "IDYES"==idName ||
         "IDNO"==idName ||
         "IDCLOSE"==idName ||
         "IDHELP"==idName ||
         "IDTRYAGAIN"==idName ||
         "IDCONTINUE"==idName ||
         "ID_SEPARATOR"==idName ||
         "ID_DEFAULT_PANE"==idName ||
         "ATL_IDW_TOOLBAR"==idName ||
         "ATL_IDW_STATUS_BAR"==idName ||
         "ATL_IDW_COMMAND_BAR"==idName ||
         "ATL_IDW_CLIENT"==idName ||
         "ATL_IDW_PANE_FIRST"==idName ||
         "ATL_IDW_PANE_LAST"==idName ||
         "ATL_IDW_HSCROLL_FIRST"==idName ||
         "ATL_IDW_VSCROLL_FIRST"==idName ||
         "ATL_IDW_SIZE_BOX"==idName ||
         "ATL_IDW_PANE_SAVE"==idName ||
         "ATL_IDW_BAND_FIRST"==idName ||
         "ATL_IDW_BAND_LAST"==idName ||
         "ID_FILE_NEW"==idName ||
         "ID_FILE_OPEN"==idName ||
         "ID_FILE_CLOSE"==idName ||
         "ID_FILE_SAVE"==idName ||
         "ID_FILE_SAVEALL"==idName ||
         "ID_FILE_SAVE_AS"==idName ||
         "ID_FILE_PAGE_SETUP"==idName ||
         "ID_FILE_PRINT_SETUP"==idName ||
         "ID_FILE_PRINT"==idName ||
         "ID_FILE_PRINT_DIRECT"==idName ||
         "ID_FILE_PRINT_PREVIEW"==idName ||
         "ID_FILE_UPDATE"==idName ||
         "ID_FILE_SAVE_COPY_AS"==idName ||
         "ID_FILE_SEND_MAIL"==idName ||
         "ID_FILE_MRU_FIRST"==idName ||
         "ID_FILE_MRU_FILE1"==idName ||
         "ID_FILE_MRU_FILE2"==idName ||
         "ID_FILE_MRU_FILE3"==idName ||
         "ID_FILE_MRU_FILE4"==idName ||
         "ID_FILE_MRU_FILE5"==idName ||
         "ID_FILE_MRU_FILE6"==idName ||
         "ID_FILE_MRU_FILE7"==idName ||
         "ID_FILE_MRU_FILE8"==idName ||
         "ID_FILE_MRU_FILE9"==idName ||
         "ID_FILE_MRU_FILE10"==idName ||
         "ID_FILE_MRU_FILE11"==idName ||
         "ID_FILE_MRU_FILE12"==idName ||
         "ID_FILE_MRU_FILE13"==idName ||
         "ID_FILE_MRU_FILE14"==idName ||
         "ID_FILE_MRU_FILE15"==idName ||
         "ID_FILE_MRU_FILE16"==idName ||
         "ID_FILE_MRU_LAST"==idName ||
         "ID_EDIT_CLEAR"==idName ||
         "ID_EDIT_CLEAR_ALL"==idName ||
         "ID_EDIT_COPY"==idName ||
         "ID_EDIT_CUT"==idName ||
         "ID_EDIT_FIND"==idName ||
         "ID_EDIT_PASTE"==idName ||
         "ID_EDIT_PASTE_LINK"==idName ||
         "ID_EDIT_PASTE_SPECIAL"==idName ||
         "ID_EDIT_REPEAT"==idName ||
         "ID_EDIT_REPLACE"==idName ||
         "ID_EDIT_SELECT_ALL"==idName ||
         "ID_EDIT_UNDO"==idName ||
         "ID_EDIT_REDO"==idName ||
         "ID_WINDOW_NEW"==idName ||
         "ID_WINDOW_ARRANGE"==idName ||
         "ID_WINDOW_CASCADE"==idName ||
         "ID_WINDOW_TILE_HORZ"==idName ||
         "ID_WINDOW_TILE_VERT"==idName ||
         "ID_WINDOW_SPLIT"==idName ||
         "ATL_IDM_WINDOW_FIRST"==idName ||
         "ATL_IDM_WINDOW_LAST"==idName ||
         "ATL_IDM_FIRST_MDICHILD"==idName ||
         "ID_APP_ABOUT"==idName ||
         "ID_APP_EXIT"==idName ||
         "ID_HELP_INDEX"==idName ||
         "ID_HELP_FINDER"==idName ||
         "ID_HELP_USING"==idName ||
         "ID_CONTEXT_HELP"==idName ||
         "ID_HELP"==idName ||
         "ID_DEFAULT_HELP"==idName ||
         "ID_NEXT_PANE"==idName ||
         "ID_PREV_PANE"==idName ||
         "ID_PANE_CLOSE"==idName ||
         "ID_FORMAT_FONT"==idName ||
         "ID_SCROLL_UP"==idName ||
         "ID_SCROLL_DOWN"==idName ||
         "ID_SCROLL_PAGE_UP"==idName ||
         "ID_SCROLL_PAGE_DOWN"==idName ||
         "ID_SCROLL_TOP"==idName ||
         "ID_SCROLL_BOTTOM"==idName ||
         "ID_SCROLL_LEFT"==idName ||
         "ID_SCROLL_RIGHT"==idName ||
         "ID_SCROLL_PAGE_LEFT"==idName ||
         "ID_SCROLL_PAGE_RIGHT"==idName ||
         "ID_SCROLL_ALL_LEFT"==idName ||
         "ID_SCROLL_ALL_RIGHT"==idName ||
         "ID_OLE_INSERT_NEW"==idName ||
         "ID_OLE_EDIT_LINKS"==idName ||
         "ID_OLE_EDIT_CONVERT"==idName ||
         "ID_OLE_EDIT_CHANGE_ICON"==idName ||
         "ID_OLE_EDIT_PROPERTIES"==idName ||
         "ID_OLE_VERB_FIRST"==idName ||
         "ID_OLE_VERB_LAST"==idName ||
         "ID_VIEW_TOOLBAR"==idName ||
         "ID_VIEW_STATUS_BAR"==idName ||
         "ID_VIEW_REFRESH"==idName ||
         "IDC_STATIC"==idName ||
         "ATL_IDS_IDLEMESSAGE"==idName )
            return true;
            
       return false; 
}
/////////////////////////////////////////////////////////////////////////////////
function MakeToolTip(component)
{
    if ( component.Item("EnableToolTip")==true )
        return "\tm_toolTip.AddTool((HWND)"+component.Item("Name")+",(LPCTSTR)"+
            MakeLocalizedCStringEx(component.Item("ToolTip"), ".t", component)+");\n";
    return "";  
}
/////////////////////////////////////////////////////////////////////////////////
function MakeWinTraits(component)
{
    return "typedef CWinTraits<"+MakeWindowStyle(component)+","+
    MakeExWindowStyle(component)+">\t"+component.Item("Name")+"WinTraits;\n";
}
/////////////////////////////////////////////////////////////////////////////////
//makes RGB color
function MakeColor(color)
{
    if ( (color.indexOf("COLOR_")!=-1 || color.indexOf("CLR_")!=-1))
        return "GetSysColor("+color+")";
    return color;    
}
/////////////////////////////////////////////////////////////////////////////////
function MakeBitmapDeclaration(component)
{
    return "\tCBitmap\t"+component.Item("Name")+"Bitmap;\n";
}
/////////////////////////////////////////////////////////////////////////////////
function MakeIconDeclaration(component)
{
    return "\tCIcon\t"+component.Item("Name")+"Icon;\n";
}
/////////////////////////////////////////////////////////////////////////////////
//for CComboBox and CListBox
function MakeStrings(component)
{
    var strings=component.Item("Strings");
    var cmpName=component.Item("Name");
    var sourceStr="";
    var str="";
    var i=0;
    for ( idx=0; idx < strings.length;idx++ )
    {
        if ( strings.charAt(idx)=='\\' && strings.charAt(idx+1)=='n' )
        {
            sourceStr+="\t"+cmpName+".AddString("+MakeLocalizedCStringEx(str,"."+i,component)+");\n";
            str="";
            idx+=1;
            i+=1;
        }
        else
            str+=strings.charAt(idx);
    }
    return sourceStr;
}
/////////////////////////////////////////////////////////////////////////////////
function MakeSetFocus(form,component)
{
    if ( component.Item("Focus")==true )
    {
        var codegen=form.Code;
        postSourceStr="\t"+component.Item("Name")+".SetFocus();\n";
        codegen.Insert(endPostCreation,postSourceStr);
    }
}
/////////////////////////////////////////////////////////////////////////////////
function MakeContainedDecl(form,component)
{
    var headerStr="";
    if ( component.Item("DoContained")==true )
    {
        var codegen=form.Code;
        headerStr=codegen.Format(component,"\tCContainedWindow\t[!Name]_cw;\n"); 
    }

    return headerStr;
}
/////////////////////////////////////////////////////////////////////////////////
function MakeContained(form,component)
{
    if ( component.Item("DoContained")==true )
    {
        var str="";
        var codegen=form.Code;
        if ( codegen.IsEmptySource(beginConstructor,endConstructor) )
            str=codegen.Format(component,":[!Name]_cw(this,[!DoContained.MessageMapID])\n");
        else
            str=codegen.Format(component,",[!Name]_cw(this,[!DoContained.MessageMapID])\n"); 

        codegen.Insert(endConstructor,str);

        var postSourceStr=codegen.Format(component,"\t[!Name]_cw.SubclassWindow([!Name]);\n"); 
        codegen.Insert(endPostCreation,postSourceStr);
	//TODO UnSubclassWindow();!!!!!!!!! 
    }
}
/////////////////////////////////////////////////////////////////////////////////
function InsertToConstructor(form,str)
{
	var codegen=form.Code;
    if ( codegen.IsEmptySource(beginConstructor,endConstructor) )
		str=":"+str;
    else
		str=","+str;
    codegen.Insert(endConstructor,str);
}
/////////////////////////////////////////////////////////////////////////////////
function RemoveFirstOr(str)
{
    if ( str.charAt(0)=='|' )
        str=str.substr(1,str.length);
    return str;     
}
/////////////////////////////////////////////////////////////////////////////////
function TabStopControls(form)
{
	var codegen=form.Code;
	var components=form.Components;
	var current=1;
	var str="";
	var prevCtrl="";
	for( i=0; i < components.Count; i++ )
	{
		for( j=0; j < components.Count; j++)
		{
			if(current == parseInt(components.Item(j).Item("TabIndex"),10))
			{
				if(prevCtrl!="")
				{
					str+="\t"+components.Item(j).Item("Name")+
					".SetWindowPos("+prevCtrl+",0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);\n";
				}
				prevCtrl=components.Item(j).Item("Name");
				current++;
				break;
			}
		}
	}
	
	return str;
}
/////////////////////////////////////////////////////////////////////////////////
function MakeLocStrings(component,ID,propName)
{
    var strings=component.Item(propName);
    var sourceStr="";
    var str="";
    var i = 0;
    for ( idx=0; idx < strings.length;idx++ )
    {
        if ( strings.charAt(idx)=='\\' && strings.charAt(idx+1)=='n' )
        {
            sourceStr+=ID +"." + i.toString() + " = " + str + "\n";
            str="";
            idx+=1;
            i+=1;
        }
        else
            str+=strings.charAt(idx);
    }
    
    return sourceStr;
}
////////////////////////////////////////////////////////////////////////////////
function MakeLocalizeFormHeader(form)
{
    var codegen=form.Code;
            
    var langId=GetLangID(form.Item("Localize.LangID"));
    var langIdStr="";
    if(langId != -1)
        langIdStr=parseInt(langId);
    var str="[LangInfo]\nLanguageID ="+langIdStr+"\n"+codegen.Format(form,"Language =[!Localize.LangID]\n\n[[!Localize.LocalizeName]]\nCaption = [!Caption]\n"); 
    codegen.Localize=str;
}

function LocalizeFrameWindow(form)
{
    var codegen=form.Code;
    if(form.Item("Localize")==true)
    {
        codegen.AddInclude(endIncludeDecl,"LocalizationFunc.h");
        codegen.Insert(endBaseClass,codegen.Format(form,"\t,public CFrameWindowLocalization<[!Name]>\n"));
        codegen.Insert(endMsgMap,codegen.Format(form,"\t\tCHAIN_MSG_MAP(CFrameWindowLocalization<[!Name]>)\n"));
        codegen.Insert(endConstructor,codegen.Format(form,"\t:CFrameWindowLocalization(_T(\"[!Localize.LocalizeName]\"))\n"));
    }
}

function LocalizeWindow(form)
{
    var codegen=form.Code;
    if(form.Item("Localize")==true)
    {
        codegen.AddInclude(endIncludeDecl,"LocalizationFunc.h");
        codegen.Insert(endBaseClass,"\t,public CLocalization\n");
        codegen.Insert(endConstructor,codegen.Format(form,"\t:CLocalization(_T(\"[!Localize.LocalizeName]\"))\n"));
    }
}

function CorrectPath(str)
{
    if(str.length && str.charAt(str.lenght-1)!='\\')
        str+='\\';
    return str;    
}