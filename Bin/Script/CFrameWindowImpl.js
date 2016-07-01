// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function Form_CFrameWindowImpl(form)
{
    //remove previously generated code
    RemoveGenerated(form);
    //get CodeGenerator object    
    var codegen=form.Code;
    //creating declaration of CFont member that contains a specification of frame window font
    var headerStr="\tCFont\tm_formFont;\n";
    //creating font of the frame window
    var sourceStr=MakeFormFont(form);
    var postSource="";
    //declare variable that contains code called while frame window closed
    var destructionStr="";
    //setting font in frame window
    sourceStr+="\tSetFont((HFONT)m_formFont);\n";
    //setting ClientWidth and ClientHeight of the frame window 
    sourceStr+=codegen.Format(form,"\tResizeClient([!ClientWidth],[!ClientHeight]);\n");

    if ( form.Item("Caption")!="" )
        sourceStr+="\tSetWindowText("+MakeLocalizedCString(form.Item("Caption"),form)+");\n";

    sourceStr+="\n";

    //if ( form.Item("Menu")!="" )
    //    postSource+=codegen.Format(form,"\tSetMenu([!Menu]);\n");
    
    //if ( form.Item("WndClient")!="" )
    //   postSource+=codegen.Format(form,"\tm_hWndClient=(HWND)[!WndClient];\n");

    //if ( form.Item("WndToolBar")!="" )
    //    postSource+=codegen.Format(form,"\tm_hWndToolBar=(HWND)[!WndToolBar];\n");

    //if ( form.Item("WndStatusBar")!="" )
    //    postSource+=codegen.Format(form,"\tm_hWndStatusBar=(HWND)[!WndStatusBar];\n");
        
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
    
    LocalizeFrameWindow(form);
}
////////////////////////////////////////////////////////////////////////////////
function Form_CFrameWindowImplLocalize(form)
{
    MakeLocalizeFormHeader(form);
}
////////////////////////////////////////////////////////////////////////////////
