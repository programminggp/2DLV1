#include "CBullet.h"

CBullet::CBullet()
{
	mState = ESTOP;
}

void CBullet::Update()
{
	if (mState == EMOVE)
	{
		float y = Y() + H();
		if (y > 620.0f)
		{
			y = 0.0f;
		}
		/*if (y > 600)
		{
			y = 700.0f;
		}*/
		Y(y);
	}
}

void CBullet::Render()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	CRectangle::Render();
	glColor3f(1.0f, 1.0f, 1.0f);
}

bool CBullet::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))
	{
		mState = ESTOP;
		return true;
	}
	return false;
}
