#include "CPlayer.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 158, 128

#define GRAVITY 40.0f
#define JUMPV0 2.0f;


CPlayer::CPlayer(float x, float y, float w, float h, CTexture* pt)
	: mVy(0.0f)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EPLAYER;
}

void CPlayer::Update()
{
	if (mInput.Key(VK_SPACE))
	{
		CApplication::CharacterManager()->Add(
			new CBullet(X(), Y() + H() + 10.0f
				, 3.0f, 10.0f, 1396, 1420, 750, 592, CApplication::Texture()));
	}
	if (mInput.Key('A'))
	{
		float x = X() - 4.0f;
		X(x);
	}

	if (mInput.Key('D'))
	{
		float x = X() + 4.0f;
		X(x);
	}

	if (mInput.Key('J') 
		&& mState != EState::EJUMP
		&& mVy >= 0.0f)
	{
		mVy = H() / JUMPV0;
		mState = EState::EJUMP;
	}

	Y(Y() + mVy);
	mVy -= H() / GRAVITY;
}

void CPlayer::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CPlayer::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		break;
	default:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			if (x == 0.0f)
			{
				mVy = 0.0f;
				mState = EState::EMOVE;
			}
		}
	}
}
