// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function Grid_CGridCtrl(form, component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CGridCtrl"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    headerStr+=MakeFontDeclaration(component);
    
    var sourceStr="\t"+cmpName+".Create("+component.Item("ParentName")+",";
    sourceStr+=MakeRect(component)+","+
	           component.Item("ID")+","+
               MakeWindowStyle(component)+","+
               MakeExWindowStyle(component)+");\n";
	sourceStr+=MakeControlFont(component);    

	if(component.Item("VirtualMode") == true)
		sourceStr+="\t"+cmpName+".SetVirtualMode("+component.Item("VirtualMode")+");\n";
		
	sourceStr+="\t"+cmpName+".SetGridBkColor("+MakeColor(component.Item("GridColors.BkColor"))+");\n";
	sourceStr+="\t"+cmpName+".SetGridLineColor("+MakeColor(component.Item("GridColors.LineColor"))+");\n";
    sourceStr+="\t"+cmpName+".SetTitleTipBackClr("+MakeColor(component.Item("GridColors.TitleTipBackColor"))+");\n";
    sourceStr+="\t"+cmpName+".SetTitleTipTextClr("+MakeColor(component.Item("GridColors.TitleTipTextColor"))+");\n";	
    sourceStr+="\t"+cmpName+".SetTextColor("+MakeColor(component.Item("GridColors.TextColor"))+");\n";	
    sourceStr+="\t"+cmpName+".SetTextBkColor("+MakeColor(component.Item("GridColors.TextBkColor"))+");\n";	
    sourceStr+="\t"+cmpName+".SetFixedTextColor("+MakeColor(component.Item("GridColors.FixedTextColor"))+");\n";	
    sourceStr+="\t"+cmpName+".SetFixedBkColor("+MakeColor(component.Item("GridColors.FixedBkColor"))+");\n";	
    
    sourceStr+="\t"+cmpName+".SetDefCellMargin("+component.Item("Cell.DefCellMargin")+");\n";	
    sourceStr+="\t"+cmpName+".SetDefCellHeight("+component.Item("Cell.DefCellHeight")+");\n";	
    sourceStr+="\t"+cmpName+".SetDefCellWidth("+component.Item("Cell.DefCellWidth")+");\n";	
    sourceStr+="\t"+cmpName+".SetRowCount("+component.Item("Cell.Rows")+");\n";	
    sourceStr+="\t"+cmpName+".SetColumnCount("+component.Item("Cell.Columns")+");\n";	
    sourceStr+="\t"+cmpName+".SetFixedRowCount("+component.Item("Cell.FixedRows")+");\n";	
    sourceStr+="\t"+cmpName+".SetFixedColumnCount("+component.Item("Cell.FixedColumns")+");\n";	

	sourceStr+="\t"+cmpName+".SetEditable("+component.Item("Editable")+");\n";	    
	    
	var gridLines="";
	if(component.Item("GridLines.Horiz") == true)
		gridLines="GVL_HORZ";
	if(component.Item("GridLines.Vert") == true)
	{
		gridLines+="|GVL_VERT";
		gridLines=RemoveFirstOr(gridLines);
	}
	if(gridLines.length != 0)	
		sourceStr+="\t"+cmpName+".SetGridLines("+gridLines+");\n";
	
	sourceStr+="\t"+cmpName+".SetListMode("+component.Item("ListMode")+");\n";	
	
	sourceStr+="\t"+cmpName+".SetSingleColSelection("+component.Item("EnableSelection.SingleCol")+");\n";	
	sourceStr+="\t"+cmpName+".SetSingleRowSelection("+component.Item("EnableSelection.SingleRow")+");\n";	
    sourceStr+="\t"+cmpName+".SetFixedColumnSelection("+component.Item("EnableSelection.FixedCol")+");\n";	
    sourceStr+="\t"+cmpName+".SetFixedRowSelection("+component.Item("EnableSelection.FixedRow")+");\n";		
	
	sourceStr+="\t"+cmpName+".EnableDragAndDrop("+component.Item("EnableDragAndDrop")+");\n";		
	
	sourceStr+="\t"+cmpName+".SetRowResize("+component.Item("Resize.RowResize")+");\n";		
	sourceStr+="\t"+cmpName+".SetColumnResize("+component.Item("Resize.ColResize")+");\n";		
	
	sourceStr+="\t"+cmpName+".SetHeaderSort("+component.Item("HeaderSort")+");\n";		
	sourceStr+="\t"+cmpName+".SetHandleTabKey("+component.Item("HandleTabKey")+");\n";		
	sourceStr+="\t"+cmpName+".EnableTitleTips("+component.Item("TitleTips")+");\n";		
	
	sourceStr+="\t"+cmpName+".SetSortColumn("+component.Item("Sort.SortCol")+");\n";		
	sourceStr+="\t"+cmpName+".SetSortAscending("+component.Item("Sort.SortAscending")+");\n";		
	
	sourceStr+="\t"+cmpName+".SetTrackFocusCell("+component.Item("TrackFocusCell")+");\n";		
	sourceStr+="\t"+cmpName+".SetFrameFocusCell("+component.Item("FrameFocusCell")+");\n";		
	
	sourceStr+="\t"+cmpName+".SetFrameFocusCell("+component.Item("Autosize.Header")+");\n";		
	
	var autosize="";
	if(component.Item("Autosize.Header") == true)
		autosize="GVS_HEADER";
	if(component.Item("Autosize.Data") == true)
	{
		autosize+="|GVS_DATA";
		autosize=RemoveFirstOr(autosize);
	}
	if(autosize.length != 0)	
		sourceStr+="\t"+cmpName+".SetAutoSizeStyle("+autosize+");\n";
		
	if(parseInt(component.Item("FocusCell.Row")) != -1 && parseInt(component.Item("FocusCell.Col")) != -1)
		sourceStr+="\t"+cmpName+".SetFocusCell("+component.Item("FocusCell.Row")+","+component.Item("FocusCell.Col")+");\n";
	
    sourceStr+=MakeToolTip(component);
    sourceStr+="\n";

    MakeSetFocus(form,component);       
    MakeContained(form,component);

    codegen.AddInclude(endIncludeDecl,CorrectPath(component.Item("IncludePath"))+"GridCtrl.h");
    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
    codegen.Insert(endCtrlIDDecl,MakeControlID(component));
}

