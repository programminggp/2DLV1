#include "CBullet.h"
#include "CApplication.h"

CBullet::CBullet(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, l, r, b, t);
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
			y = 0.0f;
		}
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
	switch (mTag)
	{
	case ETag::EENEMY:
	case ETag::EMISS:
		if (CRectangle::Collision(rect))
		{
			mState = EState::ESTOP;
			return true;
		}
		break;
	}
	return false;
}

bool CBullet::Collision(CCharacter* m, CCharacter* o)
{
	switch (o->Tag())
	{
	case ETag::EENEMY:
		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;
			mEnabled = false;
			return true;
		}
		break;
	case ETag::EMISS:
		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;
			mEnabled = false;
			CApplication::Get()->Over();
			return true;
		}
		break;
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

