// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function DecorativeCtrl_CMaskEdit(form,component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CMaskEdit"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL"+","+//MakeCString(component.Item("Caption"))+","+
               MakeEditStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);

    sourceStr+="\t"+cmpName+".m_isTime="+component.Item("IsTime")+";\n";
    sourceStr+="\t"+cmpName+".m_isdate="+component.Item("IsDate")+";\n";
    sourceStr+="\t"+cmpName+".m_bUseMask="+component.Item("UseMask")+";\n";
    sourceStr+="\t"+cmpName+".m_strMask="+MakeCString(component.Item("Mask"))+";\n";
    sourceStr+="\t"+cmpName+".m_strLiteral="+MakeCString(component.Item("Literal"))+";\n";
    if ( component.Item("Caption")!="" )
        sourceStr+="\t"+cmpName+".m_str="+MakeLocalizedCString(component.Item("Caption"),component)+";\n";
    else
    {
        if ( component.Item("Literal")!="" )
            sourceStr+="\t"+cmpName+".m_str="+cmpName+".m_strLiteral"+";\n";;
    }
    sourceStr+="\t"+cmpName+".m_strMaskLiteral="+cmpName+".m_str"+";\n";
    sourceStr+="\t"+cmpName+".SetWindowText("+cmpName+".m_str);\n";

    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);       
    MakeContained(form,component);   

    var codegen=form.Code;
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"Masked.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function DecorativeCtrl_CDateEdit(form,component)
{
    var cmpName=component.Item("Name");
    var headerStr="\t"+"CDateEdit"+"\t"+cmpName+";\n"; 
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL"+","+//MakeCString(component.Item("Caption"))+","+
               MakeEditStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);

    sourceStr+="\t"+cmpName+".m_isTime="+component.Item("IsTime")+";\n";
    sourceStr+="\t"+cmpName+".m_isdate="+component.Item("IsDate")+";\n";
    sourceStr+="\t"+cmpName+".m_bUseMask="+component.Item("UseMask")+";\n";
    sourceStr+="\t"+cmpName+".m_strMask="+MakeCString(component.Item("Mask"))+";\n";
    sourceStr+="\t"+cmpName+".m_strLiteral="+MakeCString(component.Item("Literal"))+";\n";
    if ( component.Item("Caption")!="" )
        sourceStr+="\t"+cmpName+".m_str="+MakeLocalizedCString(component.Item("Caption"),component)+";\n";
    else
    {
        if ( component.Item("Literal")!="" )
            sourceStr+="\t"+cmpName+".m_str="+cmpName+".m_strLiteral"+";\n";;
    }
    sourceStr+="\t"+cmpName+".m_strMaskLiteral="+cmpName+".m_str"+";\n";
    sourceStr+="\t"+cmpName+".SetWindowText("+cmpName+".m_str);\n";

    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);       
    
    var codegen=form.Code;
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"Masked.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

////////////////////////////////////////////////////////////////////////////////////////////////
function DecorativeCtrl_CMaskEditLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Text")!="" )
        str=ID + codegen.Format(component," = [!Text]\n");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}

function DecorativeCtrl_CDateEditLocalize(form,component)
{
    var codegen=form.Code;

    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("Text")!="" )
        str=ID + codegen.Format(component," = [!Text]\n");
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
