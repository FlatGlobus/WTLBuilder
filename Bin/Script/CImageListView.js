// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeImageListViewStyle(component)
{
	var style="";
	if(component.Item("Style.Transparent")==true)
		style+="ILD_TRANSPARENT";
	if(component.Item("Style.Mask")==true)
		style+="|ILD_MASK";
	if(component.Item("Style.Image")==true)
		style+="|ILD_IMAGE";
	if(component.Item("Style.Blend25")==true)
		style+="|ILD_BLEND25";
	if(component.Item("Style.Blend50")==true)
		style+="|ILD_BLEND50";
	if(component.Item("Style.OverlayMask")==true)
		style+="|ILD_OVERLAYMASK";
	if(component.Item("Style.PreserveAlpha")==true)
		style+="|ILD_PRESERVEALPHA";
	if(component.Item("Style.Scale")==true)
		style+="|ILD_SCALE";
	if(component.Item("Style.DPIScale")==true)
		style+="|ILD_DPISCALE";
		
    if(style.length==0)
        style="ILD_NORMAL";
	
	return RemoveFirstOr(style);
}


function DecorativeCtrl_CImageListView(form,component)
{
    var codegen=form.Code;
    var cmpName=component.Item("Name");
	
    CheckComponent(form, component);

	var szStr=codegen.Format(component,"[!Name]([!ImageSize.cx],[!ImageSize.cy])\n");
    InsertToConstructor(form, szStr);
	   
    var headerStr=codegen.Format(component,"\tCImageListView\t[!Name];\n"); 
    headerStr+=MakeContainedDecl(form,component);

    var sourceStr=codegen.Format(component,"\t[!Name].Create([!ParentName],");
    sourceStr+=MakeRect(component)+","+MakeImageListViewStyle(component)+","+ component.Item("ID")+");\n";    

	sourceStr+="\t"+cmpName+".SetImageBkColor("+MakeColor(component.Item("ImageBkColor"))+");\n";
	if(component.Item("Style.Mask")==true)
		sourceStr+="\t"+cmpName+".SetMaskColor("+MakeColor(component.Item("MaskColor"))+");\n";
	sourceStr+="\t"+cmpName+".SetBkColor("+MakeColor(component.Item("BkColor"))+");\n";
	
    sourceStr+=MakeToolTip(component);  
    imageFlag=false;
    if ( component.Item("Bitmap.ImageType")=="Bitmap" && component.Item("Bitmap.ID")!="" )
    {
        sourceStr+=codegen.Format(component,"\t[!Name].LoadBitmapImage([!Bitmap.ID]);\n");
        imageFlag=true;
    }
    
    sourceStr+="\n";

    MakeSetFocus(form,component);               
    MakeContained(form,component);
    
    if ( imageFlag == true )
        codegen.AddInclude(endIncludeDecl,"resource.h");

    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"ImageListView.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}