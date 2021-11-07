#ifndef CCAMERACONTROL_H
#define CCAMERACONTROL_H

#include "CCharacter.h"
#include "CCamera.h"

class CCameraControl : public CCharacter
{
	CCamera mCamera;
	CVector mDistance;
public:
	CCameraControl();
	CCameraControl(const CVector& pos, const CVector& rot, float dis);
	void Update();
	void Render();
};

#endif

