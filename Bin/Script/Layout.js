// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function MakeControlsToClip(form)
{
    var components=form.Components;
    var str="";
    
    for ( i=0; i <components.Count; i++ ) {
        if (components.Item(i).Item("Generate") == true )//&& components.Item(i).Item("Layout") == true)
            str += "\t" + components.Item(i).Item("ID") + ",\n";
    }
    
    return str;
}

function MakeDefineLayout(form)
{
    var components=form.Components;
    var str="";
    for ( i=0; i <components.Count; i++ )
    {
        var component=components.Item(i);
        
        if ( component != null )//&& component.Item("Layout")==true )
        {
            if ( component.Item("Layout.Left.AttachForm")==true )
                str+="\tAttachForm("+component.Item("Name")+",ATTACH_LEFT);\n";
            else
                if ( component.Item("Layout.Left.AttachOppositeForm")==true )
                str+="\tAttachOppositeForm("+component.Item("Name")+",ATTACH_LEFT);\n";
            else
                if ( component.Item("Layout.Left.AttachChild")==true && component.Item("Layout.Left.Child") != "NULL")
                str+="\tAttachWidget("+component.Item("Name")+",ATTACH_LEFT,"+component.Item("Layout.Left.Child")+");\n";
            else
                if ( component.Item("Layout.Left.AttachOppositeChild")==true && component.Item("Layout.Left.Child") != "NULL")
                str+="\tAttachOppositeWidget("+component.Item("Name")+",ATTACH_LEFT,"+component.Item("Layout.Left.Child")+");\n";
            else
                if ( component.Item("Layout.Left.AttachPosition")==true)
                str+="\tAttachPosition("+component.Item("Name")+",ATTACH_LEFT,"+component.Item("Layout.Left.Position")+");\n";
            else
                if ( component.Item("Layout.Left.AttachSelf")==true )
                str+="\tAttachSelf("+component.Item("Name")+",ATTACH_LEFT);\n";
            else
                //if ( component.Item("Layout.Left.AttachNone")==true )
                str+="\tAttachNone("+component.Item("Name")+",ATTACH_LEFT);\n";

///
            if ( component.Item("Layout.Top.AttachForm")==true )
                str+="\tAttachForm("+component.Item("Name")+",ATTACH_TOP);\n";
            else
                if ( component.Item("Layout.Top.AttachOppositeForm")==true )
                str+="\tAttachOppositeForm("+component.Item("Name")+",ATTACH_TOP);\n";
            else
                if ( component.Item("Layout.Top.AttachChild")==true && component.Item("Layout.Top.Child") != "NULL")
                str+="\tAttachWidget("+component.Item("Name")+",ATTACH_TOP,"+component.Item("Layout.Top.Child")+");\n";
            else
                if ( component.Item("Layout.Top.AttachOppositeChild")==true && component.Item("Layout.Top.Child") != "NULL")
                str+="\tAttachOppositeWidget("+component.Item("Name")+",ATTACH_TOP,"+component.Item("Layout.Top.Child")+");\n";
            else
                if ( component.Item("Layout.Top.AttachPosition")==true)
                str+="\tAttachPosition("+component.Item("Name")+",ATTACH_TOP,"+component.Item("Layout.Top.Position")+");\n";
            else
                if ( component.Item("Layout.Top.AttachSelf")==true )
                str+="\tAttachSelf("+component.Item("Name")+",ATTACH_TOP);\n";
            else
                //if ( component.Item("Layout.Top.AttachNone")==true )
                str+="\tAttachNone("+component.Item("Name")+",ATTACH_TOP);\n";

///                     
            if ( component.Item("Layout.Right.AttachForm")==true )
                str+="\tAttachForm("+component.Item("Name")+",ATTACH_RIGHT);\n";
            else
                if ( component.Item("Layout.Right.AttachOppositeForm")==true )
                str+="\tAttachOppositeForm("+component.Item("Name")+",ATTACH_RIGHT);\n";
            else
                if ( component.Item("Layout.Right.AttachChild")==true && component.Item("Layout.Right.Child") != "NULL")
                str+="\tAttachWidget("+component.Item("Name")+",ATTACH_RIGHT,"+component.Item("Layout.Right.Child")+");\n";
            else
                if ( component.Item("Layout.Right.AttachOppositeChild")==true && component.Item("Layout.Right.Child") != "NULL")
                str+="\tAttachOppositeWidget("+component.Item("Name")+",ATTACH_RIGHT,"+component.Item("Layout.Right.Child")+");\n";
            else
                if ( component.Item("Layout.Right.AttachPosition")==true )
                str+="\tAttachPosition("+component.Item("Name")+",ATTACH_RIGHT,"+component.Item("Layout.Right.Position")+");\n";
            else
                if ( component.Item("Layout.Right.AttachSelf")==true )
                str+="\tAttachSelf("+component.Item("Name")+",ATTACH_RIGHT);\n";
            else
                //if ( component.Item("Layout.Right.AttachNone")==true )
                str+="\tAttachNone("+component.Item("Name")+",ATTACH_RIGHT);\n";

///                     
            if ( component.Item("Layout.Bottom.AttachForm")==true )
                str+="\tAttachForm("+component.Item("Name")+",ATTACH_BOTTOM);\n";
            else
                if ( component.Item("Layout.Bottom.AttachOppositeForm")==true )
                str+="\tAttachOppositeForm("+component.Item("Name")+",ATTACH_BOTTOM);\n";
            else
                if ( component.Item("Layout.Bottom.AttachChild")==true && component.Item("Layout.Bottom.Child") != "NULL")
                str+="\tAttachWidget("+component.Item("Name")+",ATTACH_BOTTOM,"+component.Item("Layout.Bottom.Child")+");\n";
            else
                if ( component.Item("Layout.Bottom.AttachOppositeChild")==true && component.Item("Layout.Bottom.Child") != "NULL")
                str+="\tAttachOppositeWidget("+component.Item("Name")+",ATTACH_BOTTOM,"+component.Item("Layout.Bottom.Child")+");\n";
            else
                if ( component.Item("Layout.Bottom.AttachPosition")==true )
                str+="\tAttachPosition("+component.Item("Name")+",ATTACH_BOTTOM,"+component.Item("Layout.Bottom.Position")+");\n";
            else
                if ( component.Item("Layout.Bottom.AttachSelf")==true )
                str+="\tAttachSelf("+component.Item("Name")+",ATTACH_BOTTOM);\n";
            else
                //if ( component.Item("Layout.Bottom.AttachNone")==true )
                str+="\tAttachNone("+component.Item("Name")+",ATTACH_BOTTOM);\n";

///                     
            if ( component.Item("Layout.HCenter.AttachForm")==true )
                str+="\tAttachForm("+component.Item("Name")+",ATTACH_HCENTER);\n";
            else
                if ( component.Item("Layout.HCenter.AttachOppositeForm")==true )
                str+="\tAttachOppositeForm("+component.Item("Name")+",ATTACH_HCENTER);\n";
            else
                if ( component.Item("Layout.HCenter.AttachChild")==true && component.Item("Layout.HCenter.Child") != "NULL")
                str+="\tAttachWidget("+component.Item("Name")+",ATTACH_HCENTER,"+component.Item("Layout.HCenter.Child")+");\n";
            else
                if ( component.Item("Layout.HCenter.AttachOppositeChild")==true && component.Item("Layout.HCenter.Child") != "NULL")
                str+="\tAttachOppositeWidget("+component.Item("Name")+",ATTACH_HCENTER,"+component.Item("Layout.HCenter.Child")+");\n";
            else
                if ( component.Item("Layout.HCenter.AttachPosition")==true )
                str+="\tAttachPosition("+component.Item("Name")+",ATTACH_HCENTER,"+component.Item("Layout.HCenter.Position")+");\n";
            else
                if ( component.Item("Layout.HCenter.AttachSelf")==true )
                str+="\tAttachSelf("+component.Item("Name")+",ATTACH_HCENTER);\n";
///                     
            if ( component.Item("Layout.VCenter.AttachForm")==true )
                str+="\tAttachForm("+component.Item("Name")+",ATTACH_VCENTER);\n";
            else
                if ( component.Item("Layout.VCenter.AttachOppositeForm")==true )
                str+="\tAttachOppositeForm("+component.Item("Name")+",ATTACH_VCENTER);\n";
            else
                if ( component.Item("Layout.VCenter.AttachChild")==true && component.Item("Layout.VCenter.Child") != "NULL")
                str+="\tAttachWidget("+component.Item("Name")+",ATTACH_VCENTER,"+component.Item("Layout.VCenter.Child")+");\n";
            else
                if ( component.Item("Layout.VCenter.AttachOppositeChild")==true && component.Item("Layout.VCenter.Child") != "NULL")
                str+="\tAttachOppositeWidget("+component.Item("Name")+",ATTACH_VCENTER,"+component.Item("Layout.VCenter.Child")+");\n";
            else
                if ( component.Item("Layout.VCenter.AttachPosition")==true )
                str+="\tAttachPosition("+component.Item("Name")+",ATTACH_VCENTER,"+component.Item("Layout.VCenter.Position")+");\n";
            else
                if ( component.Item("Layout.VCenter.AttachSelf")==true )
                str+="\tAttachSelf("+component.Item("Name")+",ATTACH_VCENTER);\n";

        }
    }   
    return str;
}

function MakeInitLayout(form)
{
    var str="";
    if(form.Item("EnableLayout") == true)
    {
        str="\t_minClientSize.cx = "+form.Item("ClientWidth")+";\n";
        str+="\t_minClientSize.cy = "+form.Item("ClientHeight")+";\n";
        str+="\t_prevClientSize = _minClientSize;\n\n";
        str+="\t_minWindowSize.cx = "+form.Item("Width")+";\n";
        str+="\t_minWindowSize.cy = "+form.Item("Height")+";\n\n";
        str+="\tSetNPositions("+form.Item("EnableLayout.NPositions")+");\n";
        str+="\tShowHandle("+form.Item("EnableLayout.ShowHandle").toString()+");\n";
        str+="\tDefineLayout();\n";
    }
    return str;
}
