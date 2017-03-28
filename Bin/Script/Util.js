// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
/////////////////////////////////////////////////////////////////////////////////
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

