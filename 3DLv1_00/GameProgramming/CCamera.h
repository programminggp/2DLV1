#ifndef CCAMERA
#define CCAMERA

#include "CVector.h"

class CCamera {
public:
	CVector mEye;
	CVector mCenter;
	CVector mUp;

	CCamera();
	void Render();
};


#endif
