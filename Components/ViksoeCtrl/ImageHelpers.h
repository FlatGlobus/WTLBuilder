#if !defined(_WTL_IMAGEHELPERS_)
#define _WTL_IMAGEHELPERS_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")


ATLINLINE HBITMAP AtlLoadGdiplusImage(ATL::_U_STRINGorID bitmap, ATL::_U_STRINGorID type = (UINT) 0)
{
   USES_CONVERSION;
   static bool s_bInitied = false;
   if( !s_bInitied ) {
      s_bInitied = true;
      Gdiplus::GdiplusStartupInput gsi;
      Gdiplus::GdiplusStartupOutput gso;
      ULONG uToken = 0;
      Gdiplus::GdiplusStartup(&uToken, &gsi, &gso);
   }
   Gdiplus::Bitmap* pBitmap = NULL;
   if( HIWORD(bitmap.m_lpstr) != NULL ) {
      // Load from filename
      pBitmap = new Gdiplus::Bitmap(T2CW(bitmap.m_lpstr)); 
   }
   else if( type.m_lpstr != NULL && type.m_lpstr != RT_BITMAP ) {
      // Loading PNG, JPG resources etc
      WTL::CResource res;
      if( !res.Load(type, bitmap) ) return NULL;
      DWORD dwSize = res.GetSize();
      HANDLE hMemory = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
      if( hMemory == NULL ) return NULL;
      ::memcpy(::GlobalLock(hMemory), res.Lock(), dwSize);
      ::GlobalUnlock(hMemory);
      IStream* pStream = NULL; 
      if( FAILED( ::CreateStreamOnHGlobal(hMemory, TRUE, &pStream) ) ) {
         ::GlobalFree(hMemory);
         return FALSE;
      }
      pBitmap = new Gdiplus::Bitmap(pStream);
      pStream->Release();
   }
   else {
      // This only loads BMP resources
      pBitmap = new Gdiplus::Bitmap(_Module.GetResourceInstance(), (LPCWSTR) (UINT) bitmap.m_lpstr);
   }
   if( pBitmap == NULL ) return NULL;
   HBITMAP hBitmap = NULL;
   pBitmap->GetHBITMAP(NULL, &hBitmap); 
   delete pBitmap;
   return hBitmap;
}


ATLINLINE HBRUSH AtlGetBackgroundBrush(HWND hwndParent)
{
   CWindow wndParent = hwndParent;
   CRect rc;
   wndParent.GetWindowRect(&rc);
   CClientDC dc(hwndParent);
   CDC dcMem;
   dcMem.CreateCompatibleDC(dc);
   CBitmap bmp;
   bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
   HBITMAP hOldBitmap = dcMem.SelectBitmap(hOldBitmap);
   wndParent.SendMessage(WM_PRINTCLIENT, (WPARAM) (HDC) dcMem, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT));
   HBRUSH hBrush = ::CreatePatternBrush(bmp);
   dcMem.SelectBitmap(hOldBitmap);
   return hBrush;
}

ATLINLINE HBRUSH AtlGetBackgroundBrush(HWND hWnd, HWND hwndParent)
{
   CWindow wnd = hWnd;
   CWindow wndParent = hwndParent;
   CClientDC dcParent = wndParent;
   CRect rcParent;
   wndParent.GetWindowRect(&rcParent);
   CDC dcCompat1;
   dcCompat1.CreateCompatibleDC(dcParent);
   CBitmap bmpCompat1;
   bmpCompat1.CreateCompatibleBitmap(dcParent, rcParent.Width(), rcParent.Height());
   HBITMAP hOldBmp1 = dcCompat1.SelectBitmap(bmpCompat1);
   wndParent.SendMessage(WM_PRINTCLIENT, (WPARAM) (HDC) dcCompat1, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT));
   CRect rcWin;
   wnd.GetWindowRect(&rcWin);
   CDC dcCompat2;
   dcCompat2.CreateCompatibleDC();
   CBitmap bmpCompat2;
   bmpCompat2.CreateCompatibleBitmap(dcCompat1, rcWin.Width(), rcWin.Height());
   HBITMAP hOldBmp2 = dcCompat2.SelectBitmap(bmpCompat2);
   CRect rcSnap = rcWin;
   ::MapWindowPoints(NULL, wndParent, (LPPOINT) (LPRECT) &rcSnap, 2);
   dcCompat2.BitBlt(0, 0, rcWin.Width(), rcWin.Height(), dcCompat1, rcSnap.left, rcSnap.top, SRCCOPY);
   HBRUSH hBrush = ::CreatePatternBrush(bmpCompat2);
   dcCompat1.SelectBitmap(hOldBmp1);
   dcCompat2.SelectBitmap(hOldBmp2);
   return hBrush;
}

ATLINLINE BOOL AtlReplaceColorDib32(HDC hDC, HBITMAP hBitmap, DWORD dwKey, DWORD dwReplace = 0UL, DWORD dwShowColor = 0xFF000000)
{
   ::GdiFlush();
   BITMAP bm = { 0 };
   ::GetObject(hBitmap, sizeof(BITMAP), &bm);
   int cy = abs(bm.bmHeight);
   BITMAPINFO bmi = { 0 };
   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   BOOL bRes = ::GetDIBits(hDC, hBitmap, 0, cy, NULL, &bmi, DIB_RGB_COLORS);
   if( !bRes ) return FALSE;
   LPVOID pSrcBits = ::LocalAlloc(LPTR, bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * sizeof(DWORD));
   if( pSrcBits == NULL ) return FALSE;
   LPDWORD pBits = (LPDWORD) pSrcBits;
   bmi.bmiHeader.biBitCount = 32;  // Ask for ARGB codec
   bmi.bmiHeader.biCompression = BI_RGB;
   bRes = ::GetDIBits(hDC, hBitmap, 0, cy, pSrcBits, &bmi, DIB_RGB_COLORS);
   if( !bRes || bmi.bmiHeader.biBitCount != 32 ) {
      ::GlobalFree(pBits);
      return FALSE;
   }
   for( int y = 0; y < abs(bmi.bmiHeader.biHeight); y++ ) {
      for( int x = 0; x < bmi.bmiHeader.biWidth; x++ ) {
         if( *pBits != dwKey ) 
            *pBits = *pBits | dwShowColor; 
         else 
            *pBits = dwReplace;
         pBits++;
      }
   }
   bRes = ::SetDIBits(hDC, hBitmap, 0, cy, pSrcBits, &bmi, DIB_RGB_COLORS);
   ::GlobalFree(pBits);
   return bRes;
}

ATLINLINE HFONT AtlGetDefaultShellFont()
{
   static CFont s_font;
   if( s_font.IsNull() ) {
      CLogFont lf;
      lf.SetMessageBoxFont();
      s_font.CreateFontIndirect(&lf);
   }
   return s_font;
}


//////////////////////////////////////////////////////////////////////
// GDI+ ImageProperty helper function
//

#define PropertyTagExifRating            0x4746
#define PropertyTagExifRatingPercent     0x4746


#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)

ATLINLINE void GdipGetBitmapProperty(Gdiplus::Image* pImage, UINT uPropId, CString& sResult)
{
   ATLASSERT(pImage);
   UINT size = pImage->GetPropertyItemSize(uPropId);
   if( size == 0 ) return;
   Gdiplus::PropertyItem* pPropItem = (Gdiplus::PropertyItem*) malloc(size);
   ATLASSERT(pPropItem);
   pImage->GetPropertyItem(uPropId, size, pPropItem);
   if( pPropItem->type == PropertyTagTypeASCII ) sResult = (LPCSTR) pPropItem->value;
   free(pPropItem);
}

#endif   // _WTL_USE_CSTRING

ATLINLINE void GdipGetBitmapProperty(Gdiplus::Image* pImage, UINT uPropId, long& lResult)
{
   ATLASSERT(pImage);
   UINT size = pImage->GetPropertyItemSize(uPropId);
   if( size == 0 ) return;
   Gdiplus::PropertyItem* pPropItem = (Gdiplus::PropertyItem*) malloc(size);         
   ATLASSERT(pPropItem);
   pImage->GetPropertyItem(uPropId, size, pPropItem);
   if( pPropItem->type == PropertyTagTypeShort ) lResult = * (short*) pPropItem->value;
   if( pPropItem->type == PropertyTagTypeLong ) lResult = * (long*) pPropItem->value;
   free(pPropItem);
}

ATLINLINE Gdiplus::Status GdipCreateDIBFromGdiplusBitmap(Gdiplus::Bitmap* pBitmap, HBITMAP* hbmReturn)
{
   Gdiplus::Status status;
   UINT uWidth = pBitmap->GetWidth();
   UINT uHeight = pBitmap->GetHeight();
   Gdiplus::Rect rect(0, 0, uWidth, uHeight);
   Gdiplus::PixelFormat format = pBitmap->GetPixelFormat();
   int bits_per_pixel;
   switch( format ) {
   case PixelFormat1bppIndexed: bits_per_pixel = 1; break;
   case PixelFormat4bppIndexed: bits_per_pixel = 4; break;
   case PixelFormat8bppIndexed: bits_per_pixel = 8; break;
   case PixelFormat16bppARGB1555:
   case PixelFormat16bppGrayScale:
   case PixelFormat16bppRGB555:
   case PixelFormat16bppRGB565: bits_per_pixel = 16; break;
   case PixelFormat24bppRGB:    bits_per_pixel = 24; break;
   case PixelFormat32bppARGB:
   case PixelFormat32bppPARGB:
   case PixelFormat32bppRGB:    bits_per_pixel = 32; break;
   case PixelFormat48bppRGB:    bits_per_pixel = 48; break;
   case PixelFormat64bppARGB:
   case PixelFormat64bppPARGB:  bits_per_pixel = 64; break;
   default: return Gdiplus::InvalidParameter;
   }
   Gdiplus::BitmapData data;
   status = pBitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, format, &data);
   if( status != Gdiplus::Ok ) return status;
   HBITMAP ret = ::CreateBitmap(uWidth, uHeight, 1, bits_per_pixel, data.Scan0);
   status = pBitmap->UnlockBits(&data);
   if( ret == NULL ) return Gdiplus::Win32Error;
   if( status != Gdiplus::Ok ) {
      ::DeleteObject(ret);
      return status;
   }
   *hbmReturn = ret;
   return Gdiplus::Ok;
}

ATLINLINE Gdiplus::Bitmap* GdipGetPngBitmapFromResource(ATL::_U_STRINGorID bitmap, ATL::_U_STRINGorID type = (UINT) 0)
{
   CResource res;
   if( !res.Load(type, bitmap) ) return NULL;
   DWORD dwSize = res.GetSize();
   HANDLE hMemory = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
   if( hMemory == NULL ) return NULL;
   ::memcpy(::GlobalLock(hMemory), res.Lock(), dwSize);
   ::GlobalUnlock(hMemory);
   IStream* pStream = NULL; 
   if( FAILED( ::CreateStreamOnHGlobal(hMemory, TRUE, &pStream) ) ) {
      ::GlobalFree(hMemory);
      return FALSE;
   }
   Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(pStream);
   pStream->Release();
   return pBitmap;
}


#endif // !defined(_WTL_IMAGEHELPERS_)

