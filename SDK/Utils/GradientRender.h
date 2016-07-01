//http://www.codeproject.com/bitmap/CGradientRender.asp
// GradientRender.h: interface for the CGradientRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADIENTRENDER_H__9B3090DB_F7D0_4D23_8BDA_9CFAC9A64ABE__INCLUDED_)
#define AFX_GRADIENTRENDER_H__9B3090DB_F7D0_4D23_8BDA_9CFAC9A64ABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __WTLBUILDER__
#include "PropertyItem.h"
#include "GDIUtil.h"
#endif

enum GradientType {GRADIENT_HORIZONTAL, GRADIENT_VERTICAL, GRADIENT_RADIAL, GRADIENT_DIAGONAL, GRADIENT_FDIAGONAL, GRADIENT_BDIAGONAL};
enum TransformationType {TRANSFORMATION_NONE, TRANSFORMATION_CHARICATURE, TRANSFORMATION_FISHEYE, TRANSFORMATION_SWIRLED, TRANSFORMATION_CYLINDER, TRANSFORMATION_SHIFT};


class CGradientRender  
{
private:
	unsigned char* m_Data;
	GradientType m_Type;
	void ApplyTransformation(int width, int height,TransformationType transformationType);

#ifdef __WTLBUILDER__
    CColorref startColor;
    CColorref endColor;
    GradientType gradientType;
    TransformationType transformationType;
#endif

public:
	void DrawGradient( HDC hDC, RECT& rect, COLORREF startColor, COLORREF endColor, GradientType gradientType, TransformationType transformationType);
	CGradientRender();
	virtual ~CGradientRender();
#ifdef __WTLBUILDER__
    void AddProperty(LPCTSTR Name,CProperties & objprop);

    DECLARE_PROPERTY(StartColor,CColorref)
    DECLARE_PROPERTY(EndColor,CColorref)
    DECLARE_PROPERTY(GradientType,GradientType)
    DECLARE_PROPERTY(TransformationType,TransformationType)
    DECLARE_CALLBACK(Change,change)
#endif
};

#endif // !defined(AFX_GRADIENTRENDER_H__9B3090DB_F7D0_4D23_8BDA_9CFAC9A64ABE__INCLUDED_)
