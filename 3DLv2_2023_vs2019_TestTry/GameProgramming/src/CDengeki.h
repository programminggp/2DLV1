#ifndef CDENGEKI_H
#define CDENGEKI_H

#include "CTask.h"
#include "CVector.h"

class CDengeki : public CTask
{
public:
	CDengeki(const CVector& startPoint, const CVector& endPoint, float size);

private:
	CVector mStartPoint;
	CVector mEndPoint;
	float mSize;

};



#endif
