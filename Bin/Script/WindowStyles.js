// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
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
/////////////////////////////////////////////////////////////////////////////////////////
function MakeCommonControlStyle(component, styleStr)
{
    var CCS_TOP = 0x00000001;
    var CCS_NOMOVEY = 0x00000002;
    var CCS_BOTTOM = 0x00000003;
    var CCS_NORESIZE = 0x00000004;
    var CCS_NOPARENTALIGN = 0x00000008;
    var CCS_ADJUSTABLE = 0x00000020;
    var CCS_NODIVIDER = 0x00000040;
    var CCS_VERT = 0x00000080;

    var style = parseInt(component.Item("InternalWindowStyle"), 10);

    if ((style & (CCS_VERT | CCS_TOP)) == (CCS_VERT | CCS_TOP))
        styleStr += "|CCS_LEFT";

    if ((style & (CCS_VERT | CCS_TOP)) == CCS_TOP)
        styleStr += "|CCS_TOP";

    if ((style & (CCS_VERT | CCS_BOTTOM)) == (CCS_VERT | CCS_BOTTOM))
        styleStr += "|CCS_RIGHT";

    if ((style & (CCS_VERT | CCS_BOTTOM)) == CCS_BOTTOM)
        styleStr += "|CCS_BOTTOM";

    if ((style & (CCS_VERT | CCS_NOMOVEY)) == (CCS_VERT | CCS_NOMOVEY))
        styleStr += "|CCS_NOMOVEX";

    if ((style & (CCS_VERT | CCS_NOMOVEY)) == CCS_NOMOVEY)
        styleStr += "|CCS_NOMOVEY";

    if ((style & (CCS_VERT | CCS_TOP | CCS_BOTTOM | CCS_NOMOVEY)) == CCS_VERT)
        styleStr += "|CCS_VERT";

    if ((style & CCS_NORESIZE) == CCS_NORESIZE)
        styleStr += "|CCS_NORESIZE";

    if ((style & CCS_NOPARENTALIGN) == CCS_NOPARENTALIGN)
        styleStr += "|CCS_NOPARENTALIGN";

    if ((style & CCS_ADJUSTABLE) == CCS_ADJUSTABLE)
        styleStr += "|CCS_ADJUSTABLE";

    if ((style & CCS_NODIVIDER) == CCS_NODIVIDER)
        styleStr += "|CCS_NODIVIDER";
    
    if ( styleStr.charAt(0)=='|' )
         styleStr=styleStr.substr(1,styleStr.length);
    return styleStr;
}
///////////////////////////////////////////////////////////////////////////////////////
function MakeWindowClassStyle(component)
{
    var CS_VREDRAW = 0x0001;
    var CS_HREDRAW = 0x0002;
    var CS_DBLCLKS = 0x0008;
    var CS_OWNDC = 0x0020;
    var CS_CLASSDC = 0x0040;
    var CS_PARENTDC = 0x0080;
    var CS_NOCLOSE = 0x0200;
    var CS_SAVEBITS = 0x0800;
    var CS_BYTEALIGNCLIENT = 0x1000;
    var CS_BYTEALIGNWINDOW = 0x2000;
    var CS_GLOBALCLASS = 0x4000;
    var CS_IME = 0x00010000;
    var CS_DROPSHADOW = 0x00020000;

    var style = parseInt(component.Item("WindowClassStyle"), 10);
    var styleStr = "";

    if ((style & CS_VREDRAW) == CS_VREDRAW)
        styleStr += "|CS_VREDRAW";

    if ((style & CS_HREDRAW) == CS_HREDRAW)
        styleStr += "|CS_HREDRAW";

    if ((style & CS_DBLCLKS) == CS_DBLCLKS)
        styleStr += "|CS_DBLCLKS";

    if ((style & CS_OWNDC) == CS_OWNDC)
        styleStr += "|CS_OWNDC";

    if ((style & CS_CLASSDC) == CS_CLASSDC)
        styleStr += "|CS_CLASSDC";

    if ((style & CS_PARENTDC) == CS_PARENTDC)
        styleStr += "|CS_PARENTDC";

    if ((style & CS_NOCLOSE) == CS_NOCLOSE)
        styleStr += "|CS_NOCLOSE";

    if ((style & CS_SAVEBITS) == CS_SAVEBITS)
        styleStr += "|CS_SAVEBITS";

    if ((style & CS_BYTEALIGNCLIENT) == CS_BYTEALIGNCLIENT)
        styleStr += "|CS_BYTEALIGNCLIENT";

    if ((style & CS_BYTEALIGNWINDOW) == CS_BYTEALIGNWINDOW)
        styleStr += "|CS_BYTEALIGNWINDOW";

    if ((style & CS_GLOBALCLASS) == CS_GLOBALCLASS)
        styleStr += "|CS_GLOBALCLASS";

    if ((style & CS_IME) == CS_IME)
        styleStr += "|CS_IME";

    if ((style & CS_DROPSHADOW) == CS_DROPSHADOW)
        styleStr += "|CS_DROPSHADOW";

    if (styleStr.length == 0)
        styleStr = "0";
    else
        if (styleStr.charAt(0) == '|')
            styleStr = styleStr.substr(1, styleStr.length);

    return styleStr;

}
