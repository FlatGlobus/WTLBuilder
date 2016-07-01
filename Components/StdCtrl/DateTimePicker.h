// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __DATETIMEPICKER_H
#define __DATETIMEPICKER_H
/////////////////////////////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{
class CDateTimePickerCtrl:public CWindowImpl<StdCtrl::CDateTimePickerCtrl,WTL::CDateTimePickerCtrl>,public ControlComponent<StdCtrl::CDateTimePickerCtrl>
{
    long format;
    BOOL showNone;
public:
    CDateTimePickerCtrl(LPTSTR _name=NULL);
    ~CDateTimePickerCtrl(void);
    
    virtual BOOL CreateComponent(Component *);
    BEGIN_MSG_MAP(StdCtrl::CDateTimePickerCtrl)
        CHAIN_MSG_MAP(ControlComponent<StdCtrl::CDateTimePickerCtrl>)
        REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
        
    virtual void InitProperty(void);
    DECLARE_WINSTYLE_BOOL_PROPERTY(AppCanParse)
    DECLARE_WINSTYLE_PROPERTY(Format)
    DECLARE_WINSTYLE_BOOL_PROPERTY(RightAlign)
    //DECLARE_WINSTYLE_BOOL_PROPERTY(ShowNone)
    DECLARE_PROPERTY(ShowNone,BOOL)
    DECLARE_WINSTYLE_BOOL_PROPERTY(UpDown)
};
}
/////////////////////////////////////////////////////////////////////////////////////////////////
#endif