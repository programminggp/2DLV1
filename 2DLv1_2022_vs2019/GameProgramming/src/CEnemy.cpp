#include "CEnemy.h"
#include "CApplication.h"

CEnemy::CEnemy()
{
	mTag = ETag::EENEMY;
}

void CEnemy::Update()
{
	if(mState == EState::EMOVE)
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
		mState = EState::ESTOP;
		return true;
	}
	return false;
}

bool CEnemy::Collision(CCharacter* m, CCharacter* o)
{
	if (CRectangle::Collision(o))
	{
		Texture(Texture(), 1946, 2172, 920, 664);
		mState = EState::ESTOP;
		CApplication::Get()->Clear();
		return true;
	}
	return false;
}
