#include "CBullet.h"

CBullet::CBullet(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, l, r, b, t);
	mState = EState::EMOVE;
}

CBullet::CBullet()
{
	mState = EState::ESTOP;
}

void CBullet::Update()
{
	if (mState == EState::EMOVE)
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

//void CBullet::Render()
//{
//	glColor3f(1.0f, 1.0f, 0.0f);
//	CRectangle::Render();
//	glColor3f(1.0f, 1.0f, 1.0f);
//}

bool CBullet::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))
	{
		mState = EState::ESTOP;
		return true;
	}
	return false;
}

//void CBullet::Collision()
//{
//}
