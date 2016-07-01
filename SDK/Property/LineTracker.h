// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#pragma once

class CLineTracker  
{
public:
	CLineTracker(void);
	virtual ~CLineTracker();

	void	SetPos(int);
	int		GetPos(void);

	void	MouseUp(const CPoint &);
	void	MouseMove(const CPoint &);
	void	MouseDown(const CPoint &);
	void	SetParent(HWND);
	BOOL	CheckPos(const CPoint &);
protected:
    void	Draw(int);
	CRect   GetParentDim(void);

	HWND 	m_Parent;
	HCURSOR m_Cursor;
	HCURSOR m_OldCursor;
	BOOL	m_Pressed;
	int		m_Pos;
};

