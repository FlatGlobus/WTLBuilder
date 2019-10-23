// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeShellCtrlStyle(component)
{
    var str = "";
    
    if(component.Item("ShellStyle.NoFolders") == true)
        str = "SCT_EX_NOFOLDERS";
        
    if(component.Item("ShellStyle.NoFiles") == true)
        str += "|SCT_EX_NOFILES";
        
    if(component.Item("ShellStyle.ShowHidden") == true)
        str += "|SCT_EX_SHOWHIDDEN";
        
    if(component.Item("ShellStyle.NoReadOnly") == true)
        str += "|SCT_EX_NOREADONLY";

    if(component.Item("ShellStyle.LocalComputer") == true)
        str += "|SCT_EX_LOCALCOMPUTER";

    if(component.Item("ShellStyle.FileSysytemOnly") == true)
        str += "|SCT_EX_FILESYSTEMONLY";
        
    if(component.Item("ShellStyle.NoRoot") == true)
        str += "|SCT_EX_NOROOT";
    
    if (str.length != 0)
    {
        if (str.charAt(0) == '|')
        {
            str = str.substr(1, str.length);
        }
    }
    else
    {
        str = "0";
    }

    str = "\t"+component.Item("Name")+".SetShellStyle("+str+");\n";
    return str;
}
/////////////////////////////////////////////////////////////////////////////////
function ViksoeCtrl_CShellComboCtrl(form,component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CShellComboCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",NULL,"+
               MakeComboBoxStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";  
                 
    sourceStr+=MakeShellCtrlStyle(component);
    
    sourceStr+=MakeControlFont(component);
    
    if ( component.Item("DroppedWidth")!="0" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetDroppedWidth([!DroppedWidth]);\n");

    if ( component.Item("HorizontalExtent")!="0" )
        sourceStr+=codegen.Format(component,"\t[!Name].SetHorizontalExtent([!HorizontalExtent]);\n");

    sourceStr+=MakeToolTip(component);

    var postSource = "";
    if(component.Item("Path") != "")
       postSource+="\t"+cmpName+".Populate("+MakeCString(component.Item("Path"))+");\n";
    else
       postSource+="\t"+cmpName+".Populate();\n";

    sourceStr+="\n";

    MakeSetFocus(form,component);
    MakeContained(form,component);        
    
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endPostCreation,postSource);

    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"atlshellext.h");
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"ShellCtrls.h");
}
///////////////////////////////////////////////////////////////////////////////////////////////
