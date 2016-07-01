// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#include "stdafx.h"
#include <Path.h>
#include <CFile.h>

//////////////////////////////////////////////////////////////////////////
HBITMAP DIBToDDB( HANDLE hDIB );
BOOL WriteDIB( LPCTSTR szFile, HANDLE hDIB);
HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression,CPalette &);
void SaveFormImage(HWND wnd,CString & fileName)
{
	CPath fn(fileName);
	fn.SetExt(_T("bmp"));
	CBitmap bitmap;
	CRect rc;
	GetWindowRect(wnd,&rc);
	CWindowDC dc(wnd);
	if(bitmap.CreateCompatibleBitmap(dc,rc.Width(),rc.Height()))
	{
		CDC printDC;
		printDC.CreateCompatibleDC(dc);
		CBitmap oldBitmap = printDC.SelectBitmap(bitmap);
		::SendMessage(wnd,WM_PRINT,(WPARAM)(HDC)printDC,PRF_CHILDREN|PRF_CLIENT|PRF_NONCLIENT|PRF_CHECKVISIBLE);

		CPalette pal;
		if( printDC.GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
		{
			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
			LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
			pLP->palVersion = 0x300;

			pLP->palNumEntries =GetSystemPaletteEntries(printDC, 0, 255, pLP->palPalEntry );
			pal.CreatePalette( pLP );
			delete[] pLP;
		}
		CBitmap image;
		image.CreateCompatibleBitmap(dc,20,20);
		CDC imageDC;
		imageDC.CreateCompatibleDC(dc);
		imageDC.SelectBitmap(image);
		imageDC.StretchBlt(0,0,20,20,printDC,0,0,rc.Width(),rc.Height(),SRCCOPY);

		printDC.SelectBitmap(oldBitmap);
		HANDLE hImage=DDBToDIB(image,BI_RGB,pal);
		WriteDIB((LPCTSTR)fn,hImage);
		::DeleteObject(hImage);
	}
}
//////////////////////////////////////////////////////////////////////////
HBITMAP DIBToDDB( HANDLE hDIB )
{
	LPBITMAPINFOHEADER lpbi;
	HBITMAP hbm;
	CPalette pal;
	CPalette pOldPal;
	CClientDC dc(NULL);

	if (hDIB == NULL)
		return NULL;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = lpbi->biClrUsed ? lpbi->biClrUsed :
	1 << lpbi->biBitCount;

	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors +
		bmInfo.bmiHeader.biClrUsed) +
		((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	// Create and select a logical palette if needed
	if( nColors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
			pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		pal.CreatePalette( pLP );

		delete[] pLP;

		// Select and realize the palette
		pOldPal = dc.SelectPalette( pal, FALSE );
		dc.RealizePalette();
	}


	hbm = CreateDIBitmap(dc,// handle to device context
		(LPBITMAPINFOHEADER)lpbi,// pointer to bitmap info header
		(LONG)CBM_INIT,// initialization flag
		lpDIBBits,// pointer to initialization data
		(LPBITMAPINFO)lpbi,// pointer to bitmap info
		DIB_RGB_COLORS );// color-data usage

	if (pal.IsNull()==FALSE)
		dc.SelectPalette(pOldPal,FALSE);

	return hbm;
}
//////////////////////////////////////////////////////////////////////////
BOOL WriteDIB( LPCTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER hdr;
	LPBITMAPINFOHEADER lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;

	// Fill in the fields of the file header
	hdr.bfType= ((WORD) ('M' << 8) | 'B');// is always "BM"
	hdr.bfSize= (DWORD)GlobalSize(hDIB) + sizeof( hdr );
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits= (DWORD) (sizeof( hdr ) + lpbi->biSize +
		nColors * sizeof(RGBQUAD));

	// Write the file header
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits
	file.Write( lpbi, (UINT)GlobalSize(hDIB) );

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression,CPalette &pPal )
{
	BITMAP bm;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	DWORD dwLen;
	HANDLE hDIB;
	HANDLE handle;
	HDC hDC;
	HPALETTE hPal;

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;
	hPal = (HPALETTE)pPal;
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	// Get bitmap information
	::GetObject((HBITMAP)bitmap,sizeof(bm),(LPTSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize= sizeof(BITMAPINFOHEADER);
	bi.biWidth= bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression= dwCompression;
	bi.biSizeImage= 0;
	bi.biXPelsPerMeter= 0;
	bi.biYPelsPerMeter= 0;
	bi.biClrUsed= 0;
	bi.biClrImportant= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 )
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver
	// will calculate the biSizeImage field
	GetDIBits(hDC, (HBITMAP)bitmap,0L, (DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi,(DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)
			* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap,
		0L,// Start scan line
		(DWORD)bi.biHeight,// # of scan lines
		(LPBYTE)lpbi // address for bitmap bits
		+ (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi,// address of bitmapinfo
		(DWORD)DIB_RGB_COLORS);// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);

		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	ReleaseDC(NULL,hDC);
	return hDIB;
}