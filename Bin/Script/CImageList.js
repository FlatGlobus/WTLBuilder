// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeImageListFlag(component)
{
    var ILC_MASK=                0x00000001;
    var ILC_COLOR=               0x00000000;
    var ILC_COLORDDB=            0x000000FE;
    var ILC_COLOR4=              0x00000004;
    var ILC_COLOR8=              0x00000008;
    var ILC_COLOR16=             0x00000010;
    var ILC_COLOR24=             0x00000018;
    var ILC_COLOR32=             0x00000020;


    var style=parseInt(component.Item("Flag"),10);
    var styleStr="";
    return styleStr;
}

function StdCtl_CImageList(form,component)
{
    var codegen=form.Code;
    var cmpName = component.Item("Name");

    CheckComponent(form, component);

    var headerStr="\t"+"CImageList"+"\t"+cmpName+";\n"; 
    headerStr+=MakeContainedDecl(form,component);
    
    var sourceStr="";
    
    if ( component.Item("Bitmap.ImageType")=="Bitmap" && component.Item("Bitmap.ID")!="" )
    {
        sourceStr="\t"+cmpName+".Create("+component.Item("Bitmap.ID")+","+
                  component.Item("ImageSize.cx")+","+component.Item("Grow")+","+
                  MakeColor(component.Item("Mask"))+");\n";
    }
    //else
    //  {
    //   sourceStr="\t"+cmpName+".Create("component.Item("ImageSize.cx")+","+
    //   component.Item("ImageSize.cy")+","+MakeImageListFlag(component)+","
    //   component.Item("ImageCount")+","+component.Item("Grow")+");\n";
    //sourceStr="\t"+cmpName+".Add("HBITMAP hBitmap, COLORREF crMask)"
    //  }

    codegen.Insert(endMemberDecl,headerStr);
    codegen.Insert(endMemberCreation,sourceStr);
}

