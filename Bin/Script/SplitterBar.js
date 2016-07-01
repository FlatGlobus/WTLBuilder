// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function ViksoeCtrl_CVertSplitterCtrl(form, component)
{
  var codegen = form.Code;
  var cmpName = component.Item("Name");
  var headerStr = "\t" + "CVertSplitterCtrl" + "\t" + cmpName + ";\n";
  headerStr += MakeContainedDecl(form, component);

  var sourceStr = "\t" + cmpName + ".Create(" + component.Item("ParentName") + ",";
  sourceStr += MakeRect(component) + ",NULL," + MakeWindowStyle(component) + "," +
    MakeExWindowStyle(component) + "," + component.Item("ID") + ");\n";
  sourceStr += "\n";

  var postSource = "";

  if (component.Item("LeftPane") != "" && component.Item("RightPane") != "")
    postSource = codegen.Format(component, "\t[!Name].SetSplitterPanes([!LeftPane],[!RightPane]);\n");

  MakeContained(form, component);
  codegen.Insert(endMemberDecl, headerStr);
  codegen.Insert(endMemberCreation, sourceStr);
  codegen.Insert(endCtrlIDDecl, MakeControlID(component));
  codegen.Insert(endPostCreation, postSource);
}
