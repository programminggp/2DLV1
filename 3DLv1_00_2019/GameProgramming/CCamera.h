#ifndef CCAMERA_H
#define CCAMERA_H

#include "CVector.h"

class CCamera {
public:
	CVector mEye;
	CVector mCenter;
	CVector mUp;

	void Set(const CVector &eye, const CVector &center, const CVector &up);

	void Render();

};

//
extern CCamera Camera;

#endif
