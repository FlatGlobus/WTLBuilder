// GradientRender.cpp: implementation of the CGradientRender class.
// http://www.codeproject.com/bitmap/CGradientRender.asp
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GradientRender.h"
#include "math.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef __WTLBUILDER__
#include "PropertyListEdit.h"
static void RegisterGradientRenderTypes();
#endif
CGradientRender::CGradientRender()
{
#ifdef __WTLBUILDER__
    RegisterGradientRenderTypes();
#endif
	m_Data = NULL;
}

CGradientRender::~CGradientRender()
{
	if ( m_Data != NULL )
		delete [] m_Data;
}

void CGradientRender::DrawGradient( HDC hDC, RECT& rect, COLORREF startColor, COLORREF endColor, GradientType gradientType, TransformationType transformationType)
{
	int i, j, y, x1, y1;
	double r, d, n1;

	// Calculate image size
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int size = height*width*4;
	double radius = sqrt( pow(height/2.0,2) + pow(width/2.0,2) );
	double k = double(rect.bottom-rect.top)/double(rect.right-rect.left);
	if ( gradientType == GRADIENT_BDIAGONAL )
		k = double(rect.bottom-rect.top)/double(rect.left-rect.right);
	if ( ( gradientType == GRADIENT_FDIAGONAL ) || ( gradientType == GRADIENT_BDIAGONAL ) )
		gradientType = GRADIENT_DIAGONAL;
	double n = 0.0;
	double k1 = -1/k;

	// Create data buffer
	m_Data = new unsigned char[size];
	
	// Create gradient
	for ( i=0; i<height; i++ )
	{
		for ( j=0; j<width; j++ )
		{
			switch (gradientType)
			{
				// Horizontal gradient
				case GRADIENT_HORIZONTAL:
				{
					m_Data[i*width*4 + j*4] = (unsigned char)(((double)j/(double)width)*GetBValue(endColor) + (1-(double)j/(double)width)*GetBValue(startColor));
					m_Data[i*width*4 + j*4+1] = (unsigned char)(((double)j/(double)width)*GetGValue(endColor) + (1-(double)j/(double)width)*GetGValue(startColor));
					m_Data[i*width*4 + j*4+2] = (unsigned char)(((double)j/(double)width)*GetRValue(endColor) + (1-(double)j/(double)width)*GetRValue(startColor));
				}
				break;

				// Vertical gradient
				case GRADIENT_VERTICAL:
				{
					m_Data[i*width*4 + j*4] = (unsigned char)(((double)i/(double)height)*GetBValue(endColor) + (1-(double)i/(double)height)*GetBValue(startColor));
					m_Data[i*width*4 + j*4+1] = (unsigned char)(((double)i/(double)height)*GetGValue(endColor) + (1-(double)i/(double)height)*GetGValue(startColor));
					m_Data[i*width*4 + j*4+2] = (unsigned char)(((double)i/(double)height)*GetRValue(endColor) + (1-(double)i/(double)height)*GetRValue(startColor));
				}
				break;

				// Radial gradient
				case GRADIENT_RADIAL:
				{
					r = sqrt( pow(double(i-height/2)/radius,2) + pow(double(j-width/2)/radius,2) );
					if ( r <= 1.0 )
					{
						m_Data[i*width*4 + j*4] = (unsigned char)(r*GetBValue(endColor) + (1-r)*GetBValue(startColor));
						m_Data[i*width*4 + j*4+1] = (unsigned char)(r*GetGValue(endColor) + (1-r)*GetGValue(startColor));
						m_Data[i*width*4 + j*4+2] = (unsigned char)(r*GetRValue(endColor) + (1-r)*GetRValue(startColor));
					}
					else
					{
						m_Data[i*width*4 + j*4] = GetBValue(endColor);
						m_Data[i*width*4 + j*4+1] = GetGValue(endColor);
						m_Data[i*width*4 + j*4+2] = GetRValue(endColor);
					}
				}
				break;

				// Diagonal gradient
				case GRADIENT_DIAGONAL:
				{
					y = int(k*(j-width/2) + n);
					n1 = int((i-height/2) - k1*(j-width/2));
					x1 = int((n1-n)/(k-k1));
					y1 = int(k1*x1 + n1);
					d = sqrt( pow((double)(j-width/2)-x1,2) + pow((double)(i-height/2)-y1,2) ) / (2*radius);
					if ( (i-height/2) > y )
					{
						m_Data[i*width*4 + j*4] = (unsigned char)((0.5-d)*GetBValue(endColor) + (0.5+d)*GetBValue(startColor));
						m_Data[i*width*4 + j*4+1] = (unsigned char)((0.5-d)*GetGValue(endColor) + (0.5+d)*GetGValue(startColor));
						m_Data[i*width*4 + j*4+2] = (unsigned char)((0.5-d)*GetRValue(endColor) + (0.5+d)*GetRValue(startColor));
					}
					else
					{
						m_Data[i*width*4 + j*4] = (unsigned char)((0.5-d)*GetBValue(startColor) + (0.5+d)*GetBValue(endColor));
						m_Data[i*width*4 + j*4+1] = (unsigned char)((0.5-d)*GetGValue(startColor) + (0.5+d)*GetGValue(endColor));
						m_Data[i*width*4 + j*4+2] = (unsigned char)((0.5-d)*GetRValue(startColor) + (0.5+d)*GetRValue(endColor));
					}
				}
				break;
			}
		}
	}

	if ( transformationType != TRANSFORMATION_NONE )
		ApplyTransformation( width, height, transformationType );

	// Create temporary bitmap
	HBITMAP hBitmap = (HBITMAP)CreateBitmap( width, height, 1, 32, m_Data );

	// Create temporary device context
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );

	// Blit gradient bitmap
	BitBlt( hDC, rect.left, rect.top, width, height, hMemDC, 0, 0, SRCCOPY );

	// Free memory
	SelectObject( hMemDC, hOldBitmap );
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
	delete [] m_Data;
	m_Data = NULL;
}

void CGradientRender::ApplyTransformation(int width, int height, TransformationType transformationType)
{
	int X, Y;
	double r, fi;
	double R = sqrt( pow(width/4.0,2) + pow(height/4.0,2) );
	double FI = atan( double(height)/double(width) );

	int size = height*width*4;
	unsigned char* newBuffer = new unsigned char[size];
	memcpy( newBuffer, m_Data, size );

	for ( int i=0; i<height; i++ )
	{
		for ( int j=0; j<width; j++ )
		{
			switch (transformationType)
			{
				case TRANSFORMATION_CHARICATURE:
				{
					fi = atan((i-height/2.0)/(j-width/2.0));
					r = sqrt( pow((i-height/2.0),2) + pow((j-width/2.0),2) );
					X = int(sqrt(r*R*2)*cos(fi));
					Y = int(fabs(sqrt(r*R*2)*sin(fi)));
					newBuffer[i*width*4 + j*4] = m_Data[Y*width*4 + X*4];
					newBuffer[i*width*4 + j*4+1] = m_Data[Y*width*4 + X*4+1];
					newBuffer[i*width*4 + j*4+2] = m_Data[Y*width*4 + X*4+2];
				}
				break;

				case TRANSFORMATION_FISHEYE:
				{
					fi = atan((i-height/2.0)/(j-width/2.0));
					r = sqrt( pow((i-height/2.0),2) + pow((j-width/2.0),2) );
					X = int((pow(r,2)/R)*cos(fi));
					Y = int(fabs((pow(r,2)/R)*sin(fi))) % height;
					newBuffer[i*width*4 + j*4] = m_Data[Y*width*4 + X*4];
					newBuffer[i*width*4 + j*4+1] = m_Data[Y*width*4 + X*4+1];
					newBuffer[i*width*4 + j*4+2] = m_Data[Y*width*4 + X*4+2];
				}
				break;

				case TRANSFORMATION_SWIRLED:
				{
					fi = atan(double(i-height/2)/double(j-width/2));
					r = sqrt( pow((i-height/2.0),2) + pow((j-width/2.0),2) );
					X = int(fabs(r*cos(fi+r/8)));
					Y = int(fabs(r*sin(fi+r/8)));
					newBuffer[i*width*4 + j*4] = m_Data[Y*width*4 + X*4];
					newBuffer[i*width*4 + j*4+1] = m_Data[Y*width*4 + X*4+1];
					newBuffer[i*width*4 + j*4+2] = m_Data[Y*width*4 + X*4+2];
				}
				break;

				case TRANSFORMATION_CYLINDER:
				{
					fi = atan(double(i-height/2)/double(j-width/2));
					r = sqrt( pow((i-height/2.0),2) + pow((j-width/2.0),2) );
					X = abs((j-width/2) + int(fi+r/10)%32 - 8);
					Y = i;
					newBuffer[i*width*4 + j*4] = m_Data[Y*width*4 + X*4];
					newBuffer[i*width*4 + j*4+1] = m_Data[Y*width*4 + X*4+1];
					newBuffer[i*width*4 + j*4+2] = m_Data[Y*width*4 + X*4+2];
				}
				break;

				case TRANSFORMATION_SHIFT:
				{
					fi = atan(double(i-height/2)/double(j-width/2));
					r = sqrt( pow((i-height/2.0),2) + pow((j-width/2.0),2) );
					X = int(fabs(r*cos(fi)));
					Y = int(fabs(r*sin(fi)));
					newBuffer[i*width*4 + j*4] = m_Data[Y*width*4 + X*4];
					newBuffer[i*width*4 + j*4+1] = m_Data[Y*width*4 + X*4+1];
					newBuffer[i*width*4 + j*4+2] = m_Data[Y*width*4 + X*4+2];
				}
				break;
			}
		}
	}

	memcpy( m_Data, newBuffer, size );
	delete [] newBuffer;
}
#ifdef __WTLBUILDER__
void CGradientRender::AddProperty(LPCTSTR Name,CProperties & objprop)
{
    BEGIN_SUB_PROPERTY(Name,CGradientRender)
        DEFINE_SUB_PROPERTY(StartColor,CColorref,CGradientRender,RGB(0,0,0))
        DEFINE_SUB_PROPERTY(EndColor,CColorref,CGradientRender,RGB(0xFF,0xFF,0xFF))
        DEFINE_SUB_PROPERTY(GradientType,GradientType,CGradientRender,GRADIENT_HORIZONTAL)
        DEFINE_SUB_PROPERTY(TransformationType,TransformationType,CGradientRender,TRANSFORMATION_NONE)
    END_SUB_PROPERTY
}

void CGradientRender::set_StartColor(CColorref val)
{
    startColor = val;
    change(this);
}

CColorref CGradientRender::get_StartColor()
{
    return startColor;
}

void CGradientRender::set_EndColor(CColorref val)
{
    endColor = val;
    change(this);
}

CColorref CGradientRender::get_EndColor()
{
    return endColor;
}

void CGradientRender::set_GradientType(GradientType val)
{
    gradientType = val;
    change(this);
}

GradientType CGradientRender::get_GradientType(void)
{
    return gradientType;
}

void CGradientRender::set_TransformationType(TransformationType val)
{
    transformationType = val;
    change(this);
}

TransformationType CGradientRender::get_TransformationType(void)
{
    return transformationType;
}

BEGIN_LIST_PROPERTY(GradientType)
    LIST_ITEM(GRADIENT_HORIZONTAL,Horizontal)
    LIST_ITEM(GRADIENT_VERTICAL,Vertical)
    LIST_ITEM(GRADIENT_RADIAL,Radial)
    LIST_ITEM(GRADIENT_DIAGONAL,Diagonal)
    LIST_ITEM(GRADIENT_FDIAGONAL,FDiagonal)
    LIST_ITEM(GRADIENT_BDIAGONAL,BDiagonal)
END_LIST_ITEM(GradientType)

BEGIN_LIST_PROPERTY(TransformationType) 
    LIST_ITEM(TRANSFORMATION_NONE,None)
    LIST_ITEM(TRANSFORMATION_CHARICATURE,Charicature)
    LIST_ITEM(TRANSFORMATION_FISHEYE,FishEye)
    LIST_ITEM(TRANSFORMATION_SWIRLED,Swirled)
    LIST_ITEM(TRANSFORMATION_CYLINDER,Cylinder)
    LIST_ITEM(TRANSFORMATION_SHIFT,Shift)
END_LIST_ITEM(TransformationType)

static void RegisterGradientRenderTypes()
{
    static BOOL IsInited=FALSE;
    if(IsInited==TRUE)
        return;

    REGISTER_LIST_PROPERTY(GradientType)
    REGISTER_LIST_PROPERTY(TransformationType)
    IsInited=TRUE;
}
#endif