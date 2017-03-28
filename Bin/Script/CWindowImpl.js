// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function Form_CWindowImpl(form)
{
    RemoveGenerated(form);
    
    var codegen=form.Code;
    var headerStr="\tCFont\tm_formFont;\n";
    var sourceStr=MakeFormFont(form);
    var postSource="";
    var destructionStr="";
    sourceStr+="\tSetFont((HFONT)m_formFont);\n";
    sourceStr+=codegen.Format(form,"\tResizeClient([!ClientWidth],[!ClientHeight]);\n");
    sourceStr+="\n";
    
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endWindowStyle,MakeWinTraits(form));
    codegen.Insert(endPostCreation,postSource);
    codegen.Insert(endCtrlToClip,MakeControlsToClip(form));
    codegen.Insert(endAttachCtrls,MakeDefineLayout(form));
    codegen.Insert(endInitLayout,MakeInitLayout(form));
    codegen.Insert(endWinClassDecl,MakeCWindowImplClassDeclaration(form));
    codegen.Insert(endMemberDestruction,destructionStr);
    codegen.Insert(endTabStop,TabStopControls(form));
    LocalizeWindow(form);
}

function MakeCWindowImplClassDeclaration(form)
{
    var declStr="";
    
    if ( form.Item("WindowClass")==true )
    {
        declStr="\tDECLARE_WND_CLASS_EX("+MakeCString(form.Item("WindowClass.ClassName"))+",";
        declStr+=MakeWindowClassStyle(form)+","+form.Item("Color")+")\n";
    }
    else
        declStr="\tDECLARE_WND_CLASS(NULL)\n";

    return declStr;
}

function Form_CWindowImplLocalize(form)
{
    var codegen=form.Code;
            
    var langId=GetLangID(form.Item("Localize.LangID"));
    var langIdStr="";
    if(langId != -1)
        langIdStr=parseInt(langId);
    var str="[LangInfo]\nLanguageID = "+langIdStr+"\n"+codegen.Format(form,"Language = [!Localize.LangID]\n\n[[!Localize.LocalizeName]]\n"); 
    codegen.Localize=str;
}
