#ifndef CDENGEKI_H
#define CDENGEKI_H

#include "CTask.h"
#include "CVector.h"
#include "CMaterial.h"
#include "CInput.h"

class CDengeki : public CTask
{
public:
	CDengeki();
	void Set(const CVector& startPoint, const CVector& endPoint, float size);

	void Update();

	void Render();

private:
	CVector mStartPoint;
	CVector mEndPoint;
	float mSize;
	static CMaterial sMaterial;
	int mState;
	CInput mInput;
	float mUV[4][4];
};

#endif
