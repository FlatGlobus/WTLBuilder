// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.
/////////////////////////////////////////////////////////////////////////////////////////////
//проверка на наличие необходимой информации
function CheckProperty(form, comp, prop, errVal)
{
    var component = comp.Class;

    if (comp.Item(prop) == errVal)
    {
        Output.Err = "Form \"" + form.Item("Name") + "\", Component \"" + component + "\" has incorrect value. Property name \"" + prop + "\". Value \"" + errVal + "\"";
        return false;
    }
    return true;
}


function CheckComponent(form, comp)
{
    CheckProperty(form, comp, "Name", "");
    CheckProperty(form, comp, "ID", "");
    CheckProperty(form, comp, "Width", "0");
    CheckProperty(form, comp, "Height", "0");
    if (comp.Item("EnableToolTip") == true)
    {
        CheckProperty(form, comp, "ToolTip", "");
    }
}
