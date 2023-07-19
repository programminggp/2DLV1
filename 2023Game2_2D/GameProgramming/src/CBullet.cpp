#include "CBullet.h"
#include "CApplication.h"

CBullet::CBullet(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt)
{
	Set(x, y, w, h);
//	Texture(pt, l, r, b, t);
	mState = EState::EMOVE;
	mTag = ETag::EBULLET;
}

CBullet::CBullet()
{
	mState = EState::ESTOP;
	mTag = ETag::EBULLET;
}

void CBullet::Update()
{
	if (mState == EState::EMOVE)
	{
		float y = Y() + H();
		if (y > 620.0f)
		{
			mEnabled = false;
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

void CBullet::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CBullet::Collision(CCharacter* m, CCharacter* o)
{
	switch (o->Tag())
	{
	case ETag::EBULLET:
		break;
	default:
		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;
			mEnabled = false;
		}
	}
}

CEBullet::CEBullet(float x, float y, float w, float h, float tx, float ty)
{
	Set(x, y, w, h);
	mState = EState::EMOVE;
	mTag = ETag::EEBULLET;
	mVx = tx - x;
	mVy = ty - y;
	float length = sqrtf(mVx * mVx + mVy * mVy);
	mVx /= length;
	mVy /= length;
}

CEBullet::CEBullet()
{
	mState = EState::ESTOP;
	mTag = ETag::EEBULLET;
}

void CEBullet::Update()
{
	if (mState == EState::EMOVE)
	{
		float x = X() + H() * mVx * 0.8f;
		float y = Y() + H() * mVy * 0.8f;
		X(x);
		Y(y);
		if (y < -20.0f)
		{
			mEnabled = false;
		}
	}
}

void CEBullet::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CEBullet::Collision(CCharacter* m, CCharacter* o)
{
	switch (o->Tag())
	{
	case ETag::EEBULLET:
	case ETag::EENEMY:
		break;
	default:
		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;
			mEnabled = false;
		}
	}
}


