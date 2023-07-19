#include "CEnemy.h"
#include "CApplication.h"

#define VELOCITY  (0.7f)

CEnemy::CEnemy(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt)
	: mVx(VELOCITY)
	, mCountTurn(w * 3)
	, mFx(x), mFy(y)
	, mCountShot(60)
{
	Set(x, y, w, h);
//	Texture(pt, l, r, b, t);
	mTag = ETag::EENEMY;
}

void CEnemy::Update()
{
	if (mCountTurn++ > W() * 6)
	{
		mVx = -mVx;
		mCountTurn = 0;
	}
	mFx += mVx;
	if(mState == EState::EMOVE)
	{
		X(mFx);
		Y(mFy);
	}
	else if (mState == EState::EFLY)
	{
		if (++mCountShot > 60)
		{
			mCountShot = 0;
			if (Y() > 200.0)
			{
				CApplication::CharacterManager()->Add(
					new CEBullet(X(), Y() - H() - 8.0f
						, 3.0f, 8.0f, mTx, mTy + 120.0f));
			}
		}
		if (mFy < Y())
		{
			mTx = mFx;
		}
		float dx = mTx - X();
		float dy = mTy - Y();
		float length = sqrtf(dx * dx + dy * dy);
		dx /= length;
		dy /= length;
		dx *= VELOCITY*2;
		dy *= VELOCITY*2;
		X(X() + dx);
		Y(Y() + dy);
		if (Y() < -20.0)
		{
			X(mFx);
			Y(600.0f);
			mTy = mFy;
		}
		if (abs(Y() - mFy) < 0.5)
		{
			mState = EState::EMOVE;
		}
	}
}

bool CEnemy::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))
	{
		Texture(Texture(), 1946, 2172, 920, 664);
		mState = EState::ESTOP;
		return true;
	}
	return false;
}

void CEnemy::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CEnemy::Collision(CCharacter* m, CCharacter* o)
{
	switch (o->Tag())
	{
	case ETag::EENEMY:
	case ETag::EEBULLET:
		break;
	default:
		if (CRectangle::Collision(o))
		{
			mState = EState::ESTOP;
			mEnabled = false;
		}
	}
}
