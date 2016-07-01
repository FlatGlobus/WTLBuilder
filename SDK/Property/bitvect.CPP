// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include "bitvect.h"
#include <memory.h>
//////////////////////////////////////////////////////////////////////////
CBitVect::CBitVect(const CBitVect& x)
{
	numbytes = x.numbytes;
	numbits = x.numbits;
	vect = new unsigned char[numbytes];
	memcpy(vect, x.vect, numbytes);
}
//////////////////////////////////////////////////////////////////////////
CBitVect::CBitVect(unsigned short NumElms): numbits(NumElms)
{
	numbytes = (numbits+7) >> 3;
	vect = new unsigned char[numbytes];
	memset(vect,0,numbytes);
}
//////////////////////////////////////////////////////////////////////////
CBitVect::CBitVect(unsigned short NumElms, short val): numbits(NumElms)
{
	numbytes = (numbits+7) >> 3;
	vect = new unsigned char[numbytes];
	memset(vect, (val) ? 0xff : 0, numbytes);
}
//////////////////////////////////////////////////////////////////////////
CBitVect::~CBitVect()
{
	if(vect) delete[] vect;
}
//////////////////////////////////////////////////////////////////////////
void CBitVect::Reset(short val)
{
	memset(vect,val,numbytes);
}
//////////////////////////////////////////////////////////////////////////
void  CBitVect::SetRange(unsigned short min,unsigned short max, short on)
{
	unsigned short truemin, truemax;
	
	truemin = (min < max) ? min : max;
	truemax = (max > min) ? max : min;
	for (unsigned short i = truemin; i <= truemax; i++)
		SetBit(i, on);
}
//////////////////////////////////////////////////////////////////////////
CBitVect  CBitVect::operator~()
{
	CBitVect ret(numbits);
	unsigned char * src = vect;
	unsigned char * dst = ret.vect;
	for (short cnt = numbytes; cnt--; src++, dst++)
		*dst = ~*src;
	return ret;
}
//////////////////////////////////////////////////////////////////////////
CBitVect&  CBitVect::operator|= (CBitVect& x)
{
	unsigned char * src = x.vect;
	unsigned char * dst = vect;
	for (short cnt = numbytes; cnt--; src++, dst++)
		*dst |= *src;
	return *this;
}
//////////////////////////////////////////////////////////////////////////
CBitVect&  CBitVect::operator = (CBitVect& x)
{
	numbytes = x.numbytes;
	numbits = x.numbits;
	if(vect) delete [] vect;
	vect = new unsigned char[numbytes];
	memcpy(vect, x.vect, numbytes);
	return *this;
}
//////////////////////////////////////////////////////////////////////////
CBitVect&  CBitVect::operator&= (CBitVect& x)
{
	unsigned char * src = x.vect;
	unsigned char * dst = vect;
	for (short cnt = numbytes; cnt--; src++, dst++)
		*dst &= *src;
	return *this;
}
//////////////////////////////////////////////////////////////////////////
CBitVect&  CBitVect::operator-= (CBitVect& x)
{
	for (unsigned short i = 0; i < numbits; i++)
		if (x.GetBit(i))
			SetBit(i, 0);
		return *this;
}
//////////////////////////////////////////////////////////////////////////
CBitVect  operator| (CBitVect& x,CBitVect& y)
{
  CBitVect ret(x);
  ret |=y;
  return ret;
}
//////////////////////////////////////////////////////////////////////////
CBitVect  operator& (CBitVect& x,CBitVect& y)
{
  CBitVect ret(x);
  ret &= y;
  return ret;
}
//////////////////////////////////////////////////////////////////////////
CBitVect  operator- (CBitVect& x,CBitVect& y)
{
  CBitVect ret(x);
  ret -= y;
  return ret;
}
//////////////////////////////////////////////////////////////////////////



