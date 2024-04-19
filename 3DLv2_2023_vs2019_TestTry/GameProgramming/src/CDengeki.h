#ifndef CDENGEKI_H
#define CDENGEKI_H

#include "CTask.h"
#include "CVector.h"
#include "CMaterial.h"

class CDengeki : public CTask
{
public:
	CDengeki(const CVector& startPoint, const CVector& endPoint, float size);

	void Update();

	void Render();

private:
	CVector mStartPoint;
	CVector mEndPoint;
	float mSize;
	static CMaterial sMaterial;
};



#endif
