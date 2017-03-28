// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

var beginCtrlIDDecl = "//{{WTLBUILDER_CONTROL_ID_DECLARATION";
var endCtrlIDDecl = "//}}WTLBUILDER_CONTROL_ID_DECLARATION";

var beginMemberDecl = "//{{WTLBUILDER_MEMBER_DECLARATION";
var endMemberDecl = "//}}WTLBUILDER_MEMBER_DECLARATION";

var beginMemberCreation = "//{{WTLBUILDER_MEMBER_CREATION";
var endMemberCreation = "//}}WTLBUILDER_MEMBER_CREATION";

var beginMemberDestruction = "//{{WTLBUILDER_MEMBER_DESTRUCTION";
var endMemberDestruction = "//}}WTLBUILDER_MEMBER_DESTRUCTION";

var beginPostCreation = "//{{WTLBUILDER_POST_CREATION";
var endPostCreation = "//}}WTLBUILDER_POST_CREATION";

var beginWindowStyle = "//{{WTLBUILDER_WINDOW_STYLE";
var endWindowStyle = "//}}WTLBUILDER_WINDOW_STYLE";

var beginCtrlToClip = "//{{WTLBUILDER_CTRLTOCLIP";
var endCtrlToClip = "//}}WTLBUILDER_CTRLTOCLIP";

var beginAttachCtrls = "//{{WTLBUILDER_ATTACH_CONTROLS";
var endAttachCtrls = "//}}WTLBUILDER_ATTACH_CONTROLS";
    
var beginInitLayout = "//{{WTLBUILDER_INITLAYOUT";
var endInitLayout = "//}}WTLBUILDER_INITLAYOUT";

var beginConstructor = "//{{WTLBUILDER_CONSTRUCTOR";
var endConstructor = "//}}WTLBUILDER_CONSTRUCTOR";

var beginWinClassDecl = "//{{WTLBUILDER_WINCLASS_DECLARATION";
var endWinClassDecl = "//}}WTLBUILDER_WINCLASS_DECLARATION";

var beginIncludeDecl = "//{{WTLBUILDER_INCLUDE_DECLARATION";
var endIncludeDecl = "//}}WTLBUILDER_INCLUDE_DECLARATION";

var beginTabStop="//{{WTLBUILDER_TABSTOP";
var endTabStop=  "//}}WTLBUILDER_TABSTOP";

var beginBaseClass="//{{WTLBUILDER_BASE_CLASS";
var endBaseClass=  "//}}WTLBUILDER_BASE_CLASS";

var beginMsgMap="//{{WTLBUILDER_MSG_MAP";
var endMsgMap="//}}WTLBUILDER_MSG_MAP";

////////////////////////////////////////////////////////////////////////////////
function RemoveGenerated(form)
{              
    var codegen=form.Code;
    if(codegen != null)
    {
        codegen.ClearBetween(beginCtrlIDDecl,endCtrlIDDecl);
        codegen.ClearBetween(beginMemberDecl,endMemberDecl);
        codegen.ClearBetween(beginMemberCreation,endMemberCreation);
        codegen.ClearBetween(beginPostCreation,endPostCreation);
        codegen.ClearBetween(beginWindowStyle,endWindowStyle);
        codegen.ClearBetween(beginCtrlToClip,endCtrlToClip);
        codegen.ClearBetween(beginAttachCtrls,endAttachCtrls);
        codegen.ClearBetween(beginInitLayout,endInitLayout);
        codegen.ClearBetween(beginMemberDestruction,endMemberDestruction);
        codegen.ClearBetween(beginConstructor,endConstructor);
        codegen.ClearBetween(beginWinClassDecl,endWinClassDecl);
        codegen.ClearBetween(beginIncludeDecl,endIncludeDecl);
        codegen.ClearBetween(beginTabStop,endTabStop);
        codegen.ClearBetween(beginBaseClass,endBaseClass);
        codegen.ClearBetween(beginMsgMap,endMsgMap);
    }   
//    else 
//   {
//       Output.Put="Error: RemoveGenerated: form is NULL";
//   }
}
////////////////////////////////////////////////////////////////////////////////
