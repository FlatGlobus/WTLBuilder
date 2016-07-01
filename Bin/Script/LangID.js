// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

function GetLangID(langName)
{
    var count = ValueList.GetValCount("LangID");
    for(i = 0; i < count;i++)
    {
        if(ValueList.GetValName("LangID",i)==langName)
            return ValueList.GetValID("LangID",i);
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////