// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CScriptEditor.h"
#include "cfile.h"
#include "_util.h"
#include "Path.h"
//////////////////////////////////////////////////////////////////////////
const UINT CScriptEditor::_controlsToClip[] =
{
//{{WTLBUILDER_CTRLTOCLIP
//}}WTLBUILDER_CTRLTOCLIP
	0
};
//////////////////////////////////////////////////////////////////////////
CScriptEditor::CScriptEditor(void):scriptError(NULL)
//{{WTLBUILDER_CONSTRUCTOR
//}}WTLBUILDER_CONSTRUCTOR
{
}

CScriptEditor::~CScriptEditor(void)
{
//{{WTLBUILDER_MEMBER_DESTRUCTION
//}}WTLBUILDER_MEMBER_DESTRUCTION
}

BOOL CScriptEditor::PreTranslateMessage(MSG* pMsg)
{
	m_toolTip.RelayEvent(pMsg);
	return thisClass::PreTranslateMessage(pMsg);
}

LRESULT CScriptEditor::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_toolTip.Create(m_hWnd);

//{{WTLBUILDER_MEMBER_CREATION
	m_formFont.CreateFont(-12,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,_TEXT("MS Sans Serif"));
	SetFont((HFONT)m_formFont);
	ResizeClient(675,513);
	SetWindowText(_TEXT("FrameWindowImpl0"));

	m_edit.Create(m_hWnd,CRect(0,0,675,490),_TEXT(""),WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_TABSTOP|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL|ES_WANTRETURN,0,IDC_EDIT);
	m_edit.SetFont((HFONT)m_formFont);

	m_statusbarctrl1.Create(m_hWnd,CRect(0,490,675,513),NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,0,IDC_CSCRIPTEDITOR_STATUSBARCTRL1);
	m_statusbarctrl1.SetFont((HFONT)m_formFont);

	Menu2.LoadMenu(IDR_SCRIPT_EDITOR);
//}}WTLBUILDER_MEMBER_CREATION

//{{WTLBUILDER_POST_CREATION
	SetMenu(Menu2);
	m_hWndClient=(HWND)m_edit;
	m_hWndStatusBar=(HWND)m_statusbarctrl1;
	m_edit.SetFocus();
//}}WTLBUILDER_POST_CREATION

//{{WTLBUILDER_TABSTOP
//}}WTLBUILDER_TABSTOP
	//m_hAccel = AtlLoadAccelerators(IDR_SCRIPT_EDITOR);
	InitLayout();

	return 0;
}

BOOL CScriptEditor::Create(HWND Parent,CScriptError *se)
{
    thisClass::Create(Parent);
    if(se)
    {
		scriptError = se;
		SetWindowText(MakeString("Script Editor - [ %s ]",(LPCTSTR)scriptError->GetFile()));
        CString text = LoadString(scriptError->GetFile());
        int count = text.Replace("\n","\r\n");
        m_edit.SetWindowText(text);
		int idx = m_edit.LineIndex(scriptError->GetLine()-1);
		idx+=scriptError->GetPos();
		m_edit.SetSel(idx,idx);
    }
    return TRUE;
}

void CScriptEditor::DefineLayout()
{
//{{WTLBUILDER_ATTACH_CONTROLS
//}}WTLBUILDER_ATTACH_CONTROLS
}

void CScriptEditor::InitLayout()
{
//{{WTLBUILDER_INITLAYOUT
	_minClientSize.cx = 675;
	_minClientSize.cy = 513;
	_prevClientSize = _minClientSize;

	_minWindowSize.cx = 683;
	_minWindowSize.cy = 567;

	SetNPositions(1);
	DefineLayout();
//}}WTLBUILDER_INITLAYOUT
	//SetScrollSize(_minClientSize);
}

void CScriptEditor::GetDialogRect(LPRECT r)
{
	GetClientRect(r);	
	if (r->right < m_sizeAll.cx)
	{
		r->right = m_sizeAll.cx;
	}
	if (r->bottom < m_sizeAll.cy)
	{
		r->bottom = m_sizeAll.cy;
	}
}

void CScriptEditor::GetOffset(LPPOINT offset)
{
	*offset = m_ptOffset;
}

void CScriptEditor::DoPaint(CDCHandle /*dc*/)
{

}

LRESULT CScriptEditor::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    bHandled = FALSE;
    return TRUE;
}

LRESULT CScriptEditor::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    bHandled = TRUE;
    return 0;
}

LRESULT CScriptEditor::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DestroyWindow();
	return 0;
}

LRESULT CScriptEditor::OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString text;
	m_edit.GetWindowText(text);
	SaveString(scriptError->GetFile(),text);
	return 0;
}

LRESULT CScriptEditor::OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static _TCHAR Filter[] = _T("JScript Files (*.js)\0*.js\0");	
	CPath fn((LPCTSTR)scriptError->GetFile());
	CFileDialog filedlg(FALSE,_T("*.js"),(LPCTSTR)fn,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,Filter);
	if(filedlg.DoModal(GetDesktopWindow())!=IDOK)
		return 0;

	CString text;
	m_edit.GetWindowText(text);
	SaveString(filedlg.m_szFileName,text);
	return 0;
}
