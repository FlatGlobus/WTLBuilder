// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeFrameWindowClassDeclaration(form)
{
    var declStr="";
    var codegen=form.Code;
    if ( form.Item("WindowClass") == true )
    {
        declStr="\tDECLARE_FRAME_WND_CLASS_EX("+MakeCString(form.Item("WindowClass.ClassName"))+",";
        declStr+=form.Item("WindowClass.CommonResID")+",";
        declStr+=MakeWindowClassStyle(form)+","+form.Item("Color")+")\n";
    }
    else
    {
        declStr = codegen.Format(form, "\tDECLARE_FRAME_WND_CLASS(NULL, [!WindowClass.CommonResID])\n");
    }
    return declStr;
}