// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "StdAfx.h"
#include "richeditctrl.h" 
#include "resource.h"
#include "PropertyListEdit.h"
//////////////////////////////////////////////////////////////////////////
class CInitRichEdit
{
	HMODULE hInstRich;
public:
	CInitRichEdit();
	~CInitRichEdit();
};

CInitRichEdit::CInitRichEdit()
{
	hInstRich = ::LoadLibrary(CRichEditCtrl::GetLibraryName());
}

CInitRichEdit::~CInitRichEdit()
{
    ::FreeLibrary(hInstRich);
}

static CInitRichEdit initRichEdit;
//////////////////////////////////////////////////////////////////////////
static void RegisterRichEditCtrlStyles();
typedef long EditAlignText;
namespace StdCtrl
{
	REGISTER_COMPONENT(CRichEditCtrl,StdCtl,IDB_RICHEDITCTRL)

    CRichEditCtrl::CRichEditCtrl(LPTSTR _name):ControlComponent<StdCtrl::CRichEditCtrl>(_name),readOnly(FALSE),
            richText(TRUE),multiLevelUndo(TRUE),multiCodePage(TRUE),undoLimit(100),limitText(0),autoURLDetect(FALSE)

	{
		SetDefaultSize(100,100);
		RegisterRichEditCtrlStyles();
	}

	CRichEditCtrl::~CRichEditCtrl(void)
	{
	}

	BOOL CRichEditCtrl::CreateComponent(Component * _Parent)
	{
        SetComponentParent(_Parent);
		CWindowImpl<StdCtrl::CRichEditCtrl,WTL::CRichEditCtrl>::Create((HWND)_Parent->GetHandle(),GetBoundsRect(),get_Text(),get_InternalWindowStyle(),get_InternalWindowStyleEx());
		return ::IsWindow(m_hWnd);
	}

	void CRichEditCtrl::InitProperty(void)
	{
		ControlComponent<StdCtrl::CRichEditCtrl>::InitProperty();
        DEFINE_PROPERTY(Text,Text,CRichEditCtrl,_T(""))
    	DEFINE_PROPERTY(AutoHScroll,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(AutoVScroll,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(MultiLine,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(LowerCase,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(NoHideSel,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(Number,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(OemConvert,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(Password,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(ReadOnly,BOOL,CRichEditCtrl,readOnly)
	    DEFINE_PROPERTY(UpperCase,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(WantReturn,BOOL,CRichEditCtrl,FALSE)
	    DEFINE_PROPERTY(TextAlign,EditAlignText,CRichEditCtrl,ES_LEFT)
        DEFINE_PROPERTY(AutoWordSel,BOOL,CRichEditCtrl,FALSE)
        DEFINE_PROPERTY(BkColor,CColorref,CRichEditCtrl,::GetSysColor(COLOR_WINDOW))
        DEFINE_PROPERTY(LimitText,long,CRichEditCtrl,limitText)
        DEFINE_PROPERTY(AutoURLDetect,BOOL,CRichEditCtrl,autoURLDetect)

        BEGIN_SUB_PROPERTY(_T("EventMask"),CRichEditCtrl)
		    DEFINE_SUB_PROPERTY(ENM_CHANGE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_UPDATE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_SCROLL,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_SCROLLEVENTS,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_DRAGDROPDONE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_PARAGRAPHEXPANDED,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_PAGECHANGE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_KEYEVENTS,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_MOUSEEVENTS,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_REQUESTRESIZE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_SELCHANGE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_DROPFILES,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_PROTECTED,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_IMECHANGE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_LANGCHANGE,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_OBJECTPOSITIONS,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_LINK,BOOL,CRichEditCtrl,FALSE)
		    DEFINE_SUB_PROPERTY(ENM_LOWFIRTF,BOOL,CRichEditCtrl,FALSE)
    	END_SUB_PROPERTY

        BEGIN_SUB_PROPERTY(_T("TextMode"),CRichEditCtrl)
            DEFINE_SUB_PROPERTY(RichText,BOOL,CRichEditCtrl,TRUE)
            DEFINE_SUB_PROPERTY(MultiLevelUndo,BOOL,CRichEditCtrl,TRUE)
            DEFINE_SUB_PROPERTY(MultiCodePage,BOOL,CRichEditCtrl,TRUE)
            DEFINE_SUB_PROPERTY(UndoLimit,long,CRichEditCtrl,undoLimit)
        END_SUB_PROPERTY

        BEGIN_SUB_PROPERTY(_T("EditStyle"),CRichEditCtrl)
            DEFINE_SUB_PROPERTY(SES_EMULATESYSEDIT,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_BEEPONMAXTEXT,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_EXTENDBACKCOLOR,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_MAPCPS,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_EMULATE10,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_USECRLF,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_USEAIMM,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_NOIME,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_ALLOWBEEPS,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_UPPERCASE,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_LOWERCASE,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_NOINPUTSEQUENCECHK,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_BIDI,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_SCROLLONKILLFOCUS,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_XLTCRCRLFTOCR,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_DRAFTMODE,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_USECTF,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_HIDEGRIDLINES,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_USEATFONT,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_CUSTOMLOOK,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_LBSCROLLNOTIFY,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_CTFALLOWEMBED,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_CTFALLOWSMARTTAG,BOOL,CRichEditCtrl,FALSE)
            DEFINE_SUB_PROPERTY(SES_CTFALLOWPROOFING,BOOL,CRichEditCtrl,FALSE)
        END_SUB_PROPERTY

    	PUBLIC_PROPERTY(VScroll,TRUE)
	    PUBLIC_PROPERTY(HScroll,TRUE)
	}

    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,AutoHScroll,(ES_AUTOHSCROLL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,AutoVScroll,(ES_AUTOVSCROLL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,MultiLine,(ES_MULTILINE))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,LowerCase,(ES_LOWERCASE))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,NoHideSel,(ES_NOHIDESEL))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,Number,(ES_NUMBER))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,OemConvert,(ES_OEMCONVERT))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,Password,(ES_PASSWORD))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,UpperCase,(ES_UPPERCASE))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,WantReturn,(ES_WANTRETURN))
    IMPLEMENT_WINSTYLE_BOOL_PROPERTY(CRichEditCtrl,SelectionBar,(ES_SELECTIONBAR))
    IMPLEMENT_WINSTYLE_PROPERTY(CRichEditCtrl,TextAlign,(ES_LEFT|ES_CENTER|ES_RIGHT))

    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_CHANGE,ENM_CHANGE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_UPDATE,ENM_UPDATE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_SCROLL,ENM_SCROLL)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_SCROLLEVENTS,ENM_SCROLLEVENTS)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_DRAGDROPDONE,ENM_DRAGDROPDONE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_PARAGRAPHEXPANDED,ENM_PARAGRAPHEXPANDED)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_PAGECHANGE,ENM_PAGECHANGE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_KEYEVENTS,ENM_KEYEVENTS)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_MOUSEEVENTS,ENM_MOUSEEVENTS)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_REQUESTRESIZE,ENM_REQUESTRESIZE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_SELCHANGE,ENM_SELCHANGE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_DROPFILES,ENM_DROPFILES)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_PROTECTED,ENM_PROTECTED)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_IMECHANGE,ENM_IMECHANGE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_LANGCHANGE,ENM_LANGCHANGE)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_OBJECTPOSITIONS,ENM_OBJECTPOSITIONS)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_LINK,ENM_LINK)
    IMPLEMENT_EVENT_MASK_PROPERTY(CRichEditCtrl,ENM_LOWFIRTF,ENM_LOWFIRTF)

    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_EMULATESYSEDIT,SES_EMULATESYSEDIT)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_BEEPONMAXTEXT,SES_BEEPONMAXTEXT)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_EXTENDBACKCOLOR,SES_EXTENDBACKCOLOR)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_MAPCPS,SES_MAPCPS)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_EMULATE10,SES_EMULATE10)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_USECRLF,SES_USECRLF)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_USEAIMM,SES_USEAIMM)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_NOIME,SES_NOIME)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_ALLOWBEEPS,SES_ALLOWBEEPS)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_UPPERCASE,SES_UPPERCASE)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_LOWERCASE,SES_LOWERCASE)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_NOINPUTSEQUENCECHK,SES_NOINPUTSEQUENCECHK)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_BIDI,SES_BIDI)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_SCROLLONKILLFOCUS,SES_SCROLLONKILLFOCUS)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_XLTCRCRLFTOCR,SES_XLTCRCRLFTOCR)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_DRAFTMODE,SES_DRAFTMODE)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_USECTF,SES_USECTF)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_HIDEGRIDLINES,SES_HIDEGRIDLINES)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_USEATFONT,SES_USEATFONT)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_CUSTOMLOOK,SES_CUSTOMLOOK)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_LBSCROLLNOTIFY,SES_LBSCROLLNOTIFY)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_CTFALLOWEMBED,SES_CTFALLOWEMBED)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_CTFALLOWSMARTTAG,SES_CTFALLOWSMARTTAG)
    IMPLEMENT_EDIT_STYLE_PROPERTY(CRichEditCtrl,SES_CTFALLOWPROOFING,SES_CTFALLOWPROOFING)


    void CRichEditCtrl::set_Text(Text str)
    {
	    text.Empty();
	    text=(LPCTSTR)str;
	    if(IsWindow())
		    SetWindowText((LPCTSTR)text);
        SetModified();
    }

    Text CRichEditCtrl::get_Text(void)
    {
	    if(state.GetBit(csLoading))
	    {
		    text= GET_PROP_VALUE(CString, Text)
	    }
	    return text;
    }

    void CRichEditCtrl::set_AutoWordSel(BOOL val)
    {
        SetOptions(val == TRUE ? ECOOP_SET: ECOOP_XOR,ECO_AUTOWORDSELECTION);
        SetModified();
    }

    BOOL CRichEditCtrl::get_AutoWordSel()
    {
        return (GetOptions() & ECO_AUTOWORDSELECTION) == ECO_AUTOWORDSELECTION;
    }

    void CRichEditCtrl::set_BkColor(CColorref val)
    {
        bkColor=val;
        SetBackgroundColor(bkColor);
        SetModified();
    }

    CColorref CRichEditCtrl::get_BkColor(void)
    {
        return bkColor;
    }

    void CRichEditCtrl::set_ReadOnly(BOOL val)
    {
        readOnly = val;
        SetReadOnly(readOnly);
        SetModified();
    }

    BOOL CRichEditCtrl::get_ReadOnly()
    {
        return readOnly;
    }

    void CRichEditCtrl::set_UndoLimit(long val)
    {
        undoLimit=val;
        SetModified();
    }

    long CRichEditCtrl::get_UndoLimit()
    {
        return undoLimit;
    }


    void CRichEditCtrl::set_RichText(BOOL val)
    {
        SetWindowText(_T(""));
        richText=val;
        SetTextMode();
        SetWindowText(text);
        SetModified();
    }

    BOOL CRichEditCtrl::get_RichText()
    {
        return richText;
    }

    void CRichEditCtrl::set_MultiLevelUndo(BOOL val)
    {
        SetWindowText(_T(""));
        multiLevelUndo=val;
        SetTextMode();
        SetWindowText(text);
        SetModified();
    }

    BOOL CRichEditCtrl::get_MultiLevelUndo()
    {
        return multiLevelUndo;
    }

    void CRichEditCtrl::set_MultiCodePage(BOOL val)
    {
        SetWindowText(_T(""));
        multiCodePage=val;
        SetTextMode();
        SetWindowText(text);
        SetModified();
    }

    BOOL CRichEditCtrl::get_MultiCodePage()
    {
        return multiCodePage;
    }

    void CRichEditCtrl::SetTextMode()
    {
        DWORD textMode;
        textMode = richText ? TM_RICHTEXT : TM_PLAINTEXT;
        textMode |= multiLevelUndo ? TM_MULTILEVELUNDO : TM_SINGLELEVELUNDO;
        textMode |= multiCodePage ? TM_MULTICODEPAGE : TM_SINGLECODEPAGE;
        WTL::CRichEditCtrl::SetTextMode((TEXTMODE)textMode);
    }

    void CRichEditCtrl::set_LimitText(long val)
    {
        limitText=val;
        SetModified();
    }

    long CRichEditCtrl::get_LimitText()
    {
        return limitText;
    }

    void CRichEditCtrl::set_AutoURLDetect(BOOL val)
    {
        autoURLDetect=val;
        SetAutoURLDetect(autoURLDetect);
        SetModified();
    }

    BOOL CRichEditCtrl::get_AutoURLDetect()
    {
        return autoURLDetect;
    }

}
//////////////////////////////////////////////////////////////////////////
BEGIN_LIST_PROPERTY(EditAlignText)
	LIST_ITEM_DECORATE(ES_LEFT,ES_LEFT,Left)
	LIST_ITEM_DECORATE(ES_CENTER,ES_CENTER,Center)
	LIST_ITEM_DECORATE(ES_RIGHT,ES_RIGHT,Right)
END_LIST_ITEM(EditAlignText)


static void RegisterRichEditCtrlStyles()
{
	static BOOL IsInited=FALSE;
	if(IsInited==TRUE)
		return;

	REGISTER_LIST_PROPERTY(EditAlignText)
    
	IsInited=TRUE;
}
