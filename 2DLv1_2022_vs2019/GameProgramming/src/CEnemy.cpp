#include "CEnemy.h"

void CEnemy::Update()
{
	if(mState == EMOVE)
	{
		float x = X() + 8;
		if (x > 800.0f)
		{
			x = 0.0f;
		}
		X(x);
	}
}

bool CEnemy::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))
	{
		Texture(Texture(), 1946, 2172, 920, 664);
		mState = ESTOP;
		return true;
	}
	return false;
}
