// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function DecorativeCtrl_CPanel(form, component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"Panel::CPanel"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL"+","+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);
    if(component.Item("RoundCorners")==false)
    {
        sourceStr+=codegen.Format(component,"\t[!Name].SetInnerBorder([!InnerBorder]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetOuterBorder([!OuterBorder]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetEdgeType([!EdgeType]);\n");
    }
    else
    {
        sourceStr+=codegen.Format(component,"\t[!Name].SetRoundCorners(TRUE);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetCornerParam(CPoint([!RoundCorners.x],[!RoundCorners.y]));\n");
        sourceStr+="\t"+cmpName+".SetBorderColor("+MakeColor(component.Item("BorderColor"))+");\n";
    }
    
    if(component.Item("Theme")==true)
    {
        sourceStr+=codegen.Format(component,"\t[!Name].SetTheme(TRUE);\n");
    }
    else
    {
        if(component.Item("Gradient")==false)
        {
            sourceStr+="\t"+cmpName+".SetBkColor("+MakeColor(component.Item("BkColor"))+");\n";
        }
        else
        {
            sourceStr+="\t"+cmpName+".SetStartColor("+MakeColor(component.Item("Gradient.StartColor"))+");\n";
            sourceStr+="\t"+cmpName+".SetEndColor("+MakeColor(component.Item("Gradient.EndColor"))+");\n";
            sourceStr+=codegen.Format(component,"\t[!Name].SetGradientType([!GradientType]);\n");
            sourceStr+=codegen.Format(component,"\t[!Name].SetGradientType([!TransformationType]);\n");
        }
    }    
    sourceStr+="\t"+cmpName+".SetTextColor("+MakeColor(component.Item("TextColor"))+");\n";
    sourceStr+=codegen.Format(component,"\t[!Name].SetHorizTextAlign([!HorizTextAlign]);\n");
    sourceStr+=codegen.Format(component,"\t[!Name].SetVertTextAlign([!VertTextAlign]);\n");
    sourceStr+=codegen.Format(component,"\t[!Name].SetSingleLine([!SingleLine]);\n");
    if(component.Item("Caption").length != 0)
        sourceStr+="\t"+cmpName+".SetCaption("+MakeLocalizedCString(component.Item("Caption"),component)+");\n";
    
    sourceStr+=MakeToolTip(component);
    
    if ( component.Item("Hosted")==true )
        sourceStr+="\t"+component.Item("ParentName")+".AddPanel(&"+cmpName+");\n";

    sourceStr+="\n";

    MakeSetFocus(form,component);
    MakeContained(form,component);       

    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"Panel.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function DecorativeCtrl_CPanelHost(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    var headerStr="\t"+"Panel::CPanelHost"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);

    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+",";
    sourceStr+="NULL"+","+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);

    if(component.Item("RoundCorners")==false)
    {
        sourceStr+=codegen.Format(component,"\t[!Name].SetInnerBorder([!InnerBorder]);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetOuterBorder([!OuterBorder]);\n");
    }
    else
    {
        sourceStr+=codegen.Format(component,"\t[!Name].SetRoundCorners(TRUE);\n");
        sourceStr+=codegen.Format(component,"\t[!Name].SetCornerParam(CPoint([!RoundCorners.x],[!RoundCorners.y]));\n");
        sourceStr+="\t"+cmpName+".SetBorderColor("+MakeColor(component.Item("BorderColor"))+");\n";
    }

    if(component.Item("Theme")==true)
    {
        sourceStr+=codegen.Format(component,"\t[!Name].SetTheme(TRUE);\n");
    }
    
    sourceStr+="\t"+cmpName+".SetBkColor("+MakeColor(component.Item("BkColor"))+");\n";
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";
    
    var postSourceStr="";
    if(component.Item("CurrentPage").length !=0 )
        postSourceStr=codegen.Format(component,"\t[!Name].SetCurrent(&[!CurrentPage]);\n");
    
    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"Panel.h");   
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endPostCreation,postSourceStr);

    MakeSetFocus(form,component);       
    MakeContained(form,component);

    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}
////////////////////////////////////////////////////////////////////////////////////////////////
function DecorativeCtrl_CPanelLocalize(form,component)
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

function DecorativeCtrl_CPanelHostLocalize(form,component)
{
    var codegen=form.Code;
    var str="";
    var ID=MakeControlNameID(component);
    if ( component.Item("EnableToolTip")==true )
        str+=ID + codegen.Format(component,".t = [!ToolTip]\n");
    codegen.Localize+=str;
}
