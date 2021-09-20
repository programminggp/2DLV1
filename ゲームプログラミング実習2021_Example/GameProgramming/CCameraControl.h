#ifndef CCAMERACONTROL_H
#define CCAMERACONTROL_H

#include "CCharacter.h"
#include "CCamera.h"

class CCameraControl : public CCharacter
{
	CCamera mCamera;
public:
	CCameraControl();
	void Update();
	void Render();
};



#endif

