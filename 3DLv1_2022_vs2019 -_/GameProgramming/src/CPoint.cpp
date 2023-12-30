#include "CPoint.h"

CPoint::CPoint(float x, float y, float w, float h, ETag t)
{
	Set(x, y, w, h);
	mTag = t;
}
