// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function Form_CMDIChildWindowImpl(form)
{
    RemoveGenerated(form);
    
    var codegen=form.Code;
    var headerStr="\tCFont\tm_formFont;\n";
    var sourceStr=MakeFormFont(form);
    var postSource="";
    var destructionStr="";
    sourceStr+="\tSetFont((HFONT)m_formFont);\n";
    
    sourceStr+=codegen.Format(form,"\tResizeClient([!ClientWidth],[!ClientHeight]);\n");
    if ( form.Item("Caption")!="" )
        sourceStr+="\tSetWindowText("+MakeLocalizedCString(form.Item("Caption"),form)+");\n";

    sourceStr+="\n";

    if ( form.Item("Icon.ID")!="NULL" )
    {
        sourceStr+=codegen.Format(form,"\tHICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE([!Icon.ID]),\n"); 
        sourceStr+="\t  IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);\n";
        sourceStr+="\tSetIcon(hIcon, TRUE);\n";

        sourceStr+=codegen.Format(form,"\tHICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE([!Icon.ID]),\n"); 
        sourceStr+="\t  IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);\n";
        sourceStr+="\tSetIcon(hIconSmall, TRUE);\n";   
        codegen.AddInclude(endIncludeDecl,"resource.h");
    }

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endWindowStyle,MakeWinTraits(form));
    codegen.Insert(endPostCreation,postSource);
    codegen.Insert(endCtrlToClip,MakeControlsToClip(form));
    codegen.Insert(endAttachCtrls,MakeDefineLayout(form));
    codegen.Insert(endInitLayout,MakeInitLayout(form));
    codegen.Insert(endWinClassDecl,MakeFrameWindowClassDeclaration(form));
    codegen.Insert(endMemberDestruction,destructionStr);
    codegen.Insert(endTabStop,TabStopControls(form));
    LocalizeWindow(form);
}

function Form_CMDIChildWindowImplLocalize(form)
{
    MakeLocalizeFormHeader(form);
}
