
#include "Arrow.h"
#include <math.h>
//https://www.codeproject.com/Articles/3274/Drawing-Arrows
// ArrowTo()
//

void ArrowTo(HDC hDC, POINT ptTo, ARROWSTRUCT *pA)
{
    ArrowTo(hDC, &ptTo, pA);
}

void ArrowTo(HDC hDC, int x, int y, ARROWSTRUCT *pA) {

    POINT ptTo = {x, y};

    ArrowTo(hDC, &ptTo, pA);
}

// ArrowTo()
//
void ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA) {

    POINT pFrom;
    POINT pBase;
    POINT aptPoly[3];
    float vecLine[2];
    float vecLeft[2];
    float fLength;
    float th;
    float ta;

    // get from point
    MoveToEx(hDC, 0, 0, &pFrom);

    // set to point
    aptPoly[0].x = lpTo->x;
    aptPoly[0].y = lpTo->y;

    // build the line vector
    vecLine[0] = (float) aptPoly[0].x - pFrom.x;
    vecLine[1] = (float) aptPoly[0].y - pFrom.y;

    // build the arrow base vector - normal to the line
    vecLeft[0] = -vecLine[1];
    vecLeft[1] = vecLine[0];

    // setup length parameters
    fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
    th = pA->nWidth / (2.0f * fLength);
    ta = pA->nWidth / (2.0f * (tanf(pA->fTheta) / 2.0f) * fLength);

    // find the base of the arrow
    pBase.x = (int) (aptPoly[0].x + -ta * vecLine[0]);
    pBase.y = (int) (aptPoly[0].y + -ta * vecLine[1]);

    // build the points on the sides of the arrow
    aptPoly[1].x = (int) (pBase.x + th * vecLeft[0]);
    aptPoly[1].y = (int) (pBase.y + th * vecLeft[1]);
    aptPoly[2].x = (int) (pBase.x + -th * vecLeft[0]);
    aptPoly[2].y = (int) (pBase.y + -th * vecLeft[1]);

    MoveToEx(hDC, pFrom.x, pFrom.y, NULL);

    // draw we're fillin'...
    if(pA->bFill) {
        LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
        Polygon(hDC, aptPoly, 3);
    }

    // ... or even jes chillin'...
    else {
        LineTo(hDC, pBase.x, pBase.y);
        LineTo(hDC, aptPoly[1].x, aptPoly[1].y);
        LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
        LineTo(hDC, aptPoly[2].x, aptPoly[2].y);
        LineTo(hDC, pBase.x, pBase.y);
        MoveToEx(hDC, aptPoly[0].x, aptPoly[0].y, NULL);
    }
}

