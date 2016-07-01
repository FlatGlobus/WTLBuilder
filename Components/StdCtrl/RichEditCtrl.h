// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __RICHEDITCTRL_H
#define __RICHEDITCTRL_H
//////////////////////////////////////////////////////////////////////////
namespace StdCtrl
{

#define DECLARE_EVENT_MASK_PROPERTY(Name)\
public:\
	void set_##Name(BOOL n);\
	BOOL get_##Name(void);

#define IMPLEMENT_EVENT_MASK_PROPERTY(Class,Name,Event)\
	void Class::set_##Name(BOOL val)\
{\
	DWORD eventMask = val == TRUE ? (GetEventMask() | (Event)): (GetEventMask() & ~(Event));\
	SetEventMask(eventMask);\
    SetModified();\
}\
	BOOL Class::get_##Name(void)\
{\
	DWORD val=GetEventMask();\
	return (val & (Event))==Event;\
}

#define DECLARE_EDIT_STYLE_PROPERTY(Name)\
public:\
	void set_##Name(BOOL n);\
	BOOL get_##Name(void);

#define IMPLEMENT_EDIT_STYLE_PROPERTY(Class,Name,Style)\
	void Class::set_##Name(BOOL val)\
{\
	int editStyle = val == TRUE ? (GetEditStyle() | (Style)): (GetEditStyle() & ~(Style));\
	SetEditStyle(editStyle);\
    SetModified();\
}\
	BOOL Class::get_##Name(void)\
{\
	int val=GetEditStyle();\
	return (val & (Style))==Style;\
}

	class CRichEditCtrl:public CWindowImpl<StdCtrl::CRichEditCtrl,WTL::CRichEditCtrl>,public ControlComponent<StdCtrl::CRichEditCtrl>
	{
        CString text;
        CColorref bkColor;
        BOOL readOnly;
        BOOL richText;
        BOOL multiLevelUndo;
        BOOL multiCodePage;
        long undoLimit;
        long limitText;
        BOOL autoURLDetect;
	public:
		CRichEditCtrl(LPTSTR _name=NULL);
		~CRichEditCtrl(void);
		virtual BOOL CreateComponent(Component *);
		BEGIN_MSG_MAP(StdCtrl::CRichEditCtrl)
			CHAIN_MSG_MAP(ControlComponent<StdCtrl::CRichEditCtrl>)
			REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

		virtual void InitProperty(void);
        DECLARE_PROPERTY(Text,Text)
        DECLARE_WINSTYLE_BOOL_PROPERTY(AutoHScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(AutoVScroll)
		DECLARE_WINSTYLE_BOOL_PROPERTY(MultiLine)
		DECLARE_WINSTYLE_BOOL_PROPERTY(LowerCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(NoHideSel)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Number)
		DECLARE_WINSTYLE_BOOL_PROPERTY(OemConvert)
		DECLARE_WINSTYLE_BOOL_PROPERTY(Password)
		DECLARE_WINSTYLE_BOOL_PROPERTY(UpperCase)
		DECLARE_WINSTYLE_BOOL_PROPERTY(WantReturn)
		DECLARE_WINSTYLE_PROPERTY(TextAlign)
        DECLARE_WINSTYLE_BOOL_PROPERTY(SelectionBar)

        DECLARE_PROPERTY(AutoWordSel,BOOL)
        DECLARE_PROPERTY(BkColor,CColorref)
        DECLARE_PROPERTY(ReadOnly,BOOL)

        DECLARE_PROPERTY(RichText,BOOL)
        DECLARE_PROPERTY(MultiLevelUndo,BOOL)
        DECLARE_PROPERTY(MultiCodePage,BOOL)
        DECLARE_PROPERTY(UndoLimit,long)
        DECLARE_PROPERTY(LimitText,long)
        DECLARE_PROPERTY(AutoURLDetect,BOOL)


        DECLARE_EVENT_MASK_PROPERTY(ENM_CHANGE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_UPDATE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_SCROLL)
        DECLARE_EVENT_MASK_PROPERTY(ENM_SCROLLEVENTS)
        DECLARE_EVENT_MASK_PROPERTY(ENM_DRAGDROPDONE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_PARAGRAPHEXPANDED)
        DECLARE_EVENT_MASK_PROPERTY(ENM_PAGECHANGE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_KEYEVENTS)
        DECLARE_EVENT_MASK_PROPERTY(ENM_MOUSEEVENTS)
        DECLARE_EVENT_MASK_PROPERTY(ENM_REQUESTRESIZE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_SELCHANGE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_DROPFILES)
        DECLARE_EVENT_MASK_PROPERTY(ENM_PROTECTED)
        DECLARE_EVENT_MASK_PROPERTY(ENM_IMECHANGE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_LANGCHANGE)
        DECLARE_EVENT_MASK_PROPERTY(ENM_OBJECTPOSITIONS)
        DECLARE_EVENT_MASK_PROPERTY(ENM_LINK)
        DECLARE_EVENT_MASK_PROPERTY(ENM_LOWFIRTF)
        
        DECLARE_EDIT_STYLE_PROPERTY(SES_EMULATESYSEDIT)
        DECLARE_EDIT_STYLE_PROPERTY(SES_BEEPONMAXTEXT)
        DECLARE_EDIT_STYLE_PROPERTY(SES_EXTENDBACKCOLOR)
        DECLARE_EDIT_STYLE_PROPERTY(SES_MAPCPS)
        DECLARE_EDIT_STYLE_PROPERTY(SES_EMULATE10)
        DECLARE_EDIT_STYLE_PROPERTY(SES_USECRLF)
        DECLARE_EDIT_STYLE_PROPERTY(SES_USEAIMM)
        DECLARE_EDIT_STYLE_PROPERTY(SES_NOIME)
        DECLARE_EDIT_STYLE_PROPERTY(SES_ALLOWBEEPS)
        DECLARE_EDIT_STYLE_PROPERTY(SES_UPPERCASE)
        DECLARE_EDIT_STYLE_PROPERTY(SES_LOWERCASE)
        DECLARE_EDIT_STYLE_PROPERTY(SES_NOINPUTSEQUENCECHK)
        DECLARE_EDIT_STYLE_PROPERTY(SES_BIDI)
        DECLARE_EDIT_STYLE_PROPERTY(SES_SCROLLONKILLFOCUS)
        DECLARE_EDIT_STYLE_PROPERTY(SES_XLTCRCRLFTOCR)
        DECLARE_EDIT_STYLE_PROPERTY(SES_DRAFTMODE)
        DECLARE_EDIT_STYLE_PROPERTY(SES_USECTF)
        DECLARE_EDIT_STYLE_PROPERTY(SES_HIDEGRIDLINES)
        DECLARE_EDIT_STYLE_PROPERTY(SES_USEATFONT)
        DECLARE_EDIT_STYLE_PROPERTY(SES_CUSTOMLOOK)
        DECLARE_EDIT_STYLE_PROPERTY(SES_LBSCROLLNOTIFY)
        DECLARE_EDIT_STYLE_PROPERTY(SES_CTFALLOWEMBED)
        DECLARE_EDIT_STYLE_PROPERTY(SES_CTFALLOWSMARTTAG)
        DECLARE_EDIT_STYLE_PROPERTY(SES_CTFALLOWPROOFING)

        void SetTextMode();

//	BOOL SetParaFormat(PARAFORMAT& pf)
//	{
//		ATLASSERT(::IsWindow(m_hWnd));
//		pf.cbSize = sizeof(PARAFORMAT);
//		return (BOOL)::SendMessage(m_hWnd, EM_SETPARAFORMAT, 0, (LPARAM)&pf);
//	}

//void ShowScrollBar(int nBarType, BOOL bVisible = TRUE) EM_SHOWSCROLLBAR
	//BOOL SetDefaultCharFormat(CHARFORMAT& cf)
//	{
//		ATLASSERT(::IsWindow(m_hWnd));
//		cf.cbSize = sizeof(CHARFORMAT);
	//	return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
//	}

	};
}
//////////////////////////////////////////////////////////////////////////
#endif
