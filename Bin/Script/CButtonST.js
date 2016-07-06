// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function DecorativeCtrl_CButtonST(form, component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
    
    CheckComponent(form, component);

    var headerStr=codegen.Format(component,"\tCButtonST\t[!Name];\n"); 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);

    var sourceStr=codegen.Format(component,"\t[!Name].Create([!ParentName],");    
    sourceStr+=MakeRect(component)+",";
    sourceStr+=MakeLocalizedCString(component.Item("Caption"),component)+","+
               MakeWindowStyle(component)+"|BS_PUSHBUTTON,"+
               MakeExWindowStyle(component)+","+
               component.Item("ID")+");\n";    
    sourceStr+=MakeControlFont(component);  

    sourceStr+="\t"+cmpName+".SetFlat("+component.Item("Flat")+");\n";
    //sourceStr+="\t"+cmpName+".DrawTransparent("+component.Item("Transparent")+");\n";
    sourceStr+="\t"+cmpName+".SetAlign("+component.Item("Alignment")+");\n";
	if(component.Item("Caption").length)
	{
		sourceStr+="\t"+cmpName+".SetColor(CButtonST::BTNST_COLOR_FG_IN,"+MakeColor(component.Item("TextColorIn"))+");\n";
		sourceStr+="\t"+cmpName+".SetColor(CButtonST::BTNST_COLOR_FG_OUT,"+MakeColor(component.Item("TextColorOut"))+");\n";
	}		
	sourceStr+="\t"+cmpName+".SetColor(CButtonST::BTNST_COLOR_BK_IN,"+MakeColor(component.Item("BkColorIn"))+");\n";
	sourceStr+="\t"+cmpName+".SetColor(CButtonST::BTNST_COLOR_BK_OUT,"+MakeColor(component.Item("BkColorOut"))+");\n";

	if (component.Item("EnableToolTip") == true)
	{
	    CheckProperty(form, component, "ToolTip", "");
	    sourceStr += "\t" + cmpName + ".SetTooltipText(" + MakeLocalizedCStringEx(component.Item("ToolTip"), ".t", component) + ");\n";
	}
    
    imageFlag=false;
    if (component.Item("InImage.ImageType") == "Bitmap" && CheckProperty(form, component, "InImage.ID", "") == true)
    {
        if (component.Item("OutImage.ImageType") != "Bitmap")
        {
            sourceStr += codegen.Format(component, "\t[!Name].SetBitmaps([!InImage.ID],RGB(0,0,0),[!InImage.ID],RGB(0,0,0));\n");
        }
        else
        {
            sourceStr += codegen.Format(component, "\t[!Name].SetBitmaps([!InImage.ID],RGB(0,0,0),[!OutImage.ID],RGB(0,0,0));\n");
        }
        imageFlag = true;
    }

    if ( component.Item("InImage.ImageType")=="Icon" && CheckProperty(form, component, "InImage.ID", "") == true)
    {
        if (component.Item("OutImage.ImageType") != "Icon")
        {
            sourceStr += codegen.Format(component, "\t[!Name].SetIcon([!InImage.ID],[!InImage.ID]);\n");
        }
        else
        {
            if (CheckProperty(form, component, "OutImage.ID", "") == true)
            {
                sourceStr += codegen.Format(component, "\t[!Name].SetIcon([!InImage.ID],[!OutImage.ID]);\n");
            }
        }
        imageFlag = true;
    }
	
	if(component.Item("EnablePressed")==true)
	{
		sourceStr+="\t"+cmpName+".EnablePressedState(true);\n";
		if(component.Item("Pressed")==true)
			sourceStr+="\t"+cmpName+".SetPressed(true);\n";
	}
    sourceStr+="\n";

    MakeSetFocus(form,component);               
    MakeContained(form,component);
    
    if ( imageFlag == true )
        codegen.AddInclude(endIncludeDecl,"resource.h");

    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"ButtonST.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

function DecorativeCtrl_CButtonSTLocalize(form,component)
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
