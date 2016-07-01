// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __BITVEC_H
#define __BITVEC_H
/////////////////////////////////////////////////////////////////////////////////////////
class PROPERTY_API CBitVect
{
	unsigned char * vect;
	short numbytes;
	unsigned short numbits;
public:
	CBitVect(const CBitVect&);
	CBitVect(unsigned short n);
	CBitVect(unsigned short n,short val);
	~CBitVect();

	void Reset(short val=0);

	short operator[](unsigned short inx)
	{
		return (vect[inx>>3]&(1<<(inx&7)))!=0;
		
	}
	
	short GetBit(unsigned short inx)
	{
		return (*this)[inx];
	}
	
	void SetBit(unsigned short inx,short val=1)
	{
		if(val)
			vect[inx>>3] |=(unsigned char)(1 << (inx & 7));
		else
			vect[inx>>3] &= (unsigned char)~(1 << (inx & 7));
	}
	
	void SetRange(unsigned short min,unsigned short max,short val=1);

	CBitVect& operator = (CBitVect& x);
	CBitVect  operator ~ ();
	CBitVect& operator |= (CBitVect& x);
	CBitVect& operator &= (CBitVect& x);
	CBitVect& operator -= (CBitVect& x);

	friend CBitVect operator | (CBitVect& x,CBitVect& y);
	friend CBitVect operator & (CBitVect& x,CBitVect& y);
	friend CBitVect operator - (CBitVect& x,CBitVect& y);
};
/////////////////////////////////////////////////////////////////////////////////////////
#endif
