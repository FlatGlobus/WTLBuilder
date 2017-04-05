// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

/////////////////////////////////////////////////////////////////////////////////
function Form_CDialogImpl(form)
{
    //remove previously generated code
    RemoveGenerated(form);
    //get CodeGenerator object
    var codegen=form.Code;
    //declare variable that contains code called while dialog closed
    var destructionStr="";
    //creating declaration of CFont member that contains a specification of from font
    var headerStr="\tCFont\tm_formFont;\n";
    //creating font of the dialog
    var sourceStr=MakeFormFont(form);
    //setting font in dialog
    sourceStr+="\tSetFont((HFONT)m_formFont);\n";
    //setting window styles
    sourceStr+="\tModifyStyle(GetStyle()," + MakeWindowStyle(form) + ");\n";
    //sourceStr+="\tModifyStyleEx(GetExStyle()," + MakeExWindowStyle(form) + ");\n";
    
    //setting ClientWidth and ClientHeight of the dialog 
    sourceStr+=codegen.Format(form, "\tResizeClient([!ClientWidth],[!ClientHeight]);\n");
    //setting caption of the dialog
    if ( form.Item("Caption")!="" && form.Item("CaptionBar") == true)
        sourceStr+="\tSetWindowText("+MakeLocalizedCString(form.Item("Caption"),form)+");\n";
    //setting icon of the dialog
    if ( form.Item("Icon.ID") != "" )
    {
        //if Icon for the dialog defined
        //generate code for setting Icon image
        sourceStr+=codegen.Format(form, "\tHICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE([!Icon.ID]),\n"); 
        sourceStr+="\t   IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);\n";
        sourceStr+="\tSetIcon(hIcon, TRUE);\n";

        sourceStr+=codegen.Format(form, "\tHICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE([!Icon.ID]),\n"); 
        sourceStr+="\t   IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);\n";
        sourceStr+="\tSetIcon(hIconSmall, TRUE);\n";   
    }
    sourceStr+="\n";
    
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endMemberDestruction,destructionStr);
    codegen.Insert(endCtrlToClip,MakeControlsToClip(form));
    codegen.Insert(endAttachCtrls,MakeDefineLayout(form));
    codegen.Insert(endInitLayout,MakeInitLayout(form));
    codegen.Insert(endTabStop,TabStopControls(form));
    LocalizeWindow(form);
}
////////////////////////////////////////////////////////////////////////////////
function Form_CDialogImplLocalize(form)
{
    MakeLocalizeFormHeader(form);
}