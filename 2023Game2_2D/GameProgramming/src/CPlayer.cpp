#include "CPlayer.h"
#include "CApplication.h"
//#include "CGame.h"

#define TEXCOORD 168, 188, 158, 128	//�e�N�X�`���}�b�s���O
#define GRAVITY (TIPSIZE / 20.0f)	//�d�͉����x
#define JUMPV0 (TIPSIZE / 1.4f)		//�W�����v�̏���

CPlayer::CPlayer(float x, float y, float w, float h, CTexture* pt)
	: mVy(0.0f)
	, mCountShot(0)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EPLAYER;
}

void CPlayer::Update()
{
	if (mCountShot++ > 40)
	{
		mCountShot = 40;
		if (mInput.Key(VK_SPACE))
		{
			mCountShot = 0;
			CApplication::CharacterManager()->Add(
				new CBullet(X(), Y() + H() + 10.0f
					, 3.0f, 10.0f, 1396, 1420, 750, 592, nullptr));
		}
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

	//if (mInput.Key('J') 
	//	&& mState != EState::EJUMP
	//	&& mVy >= 0.0f)
	//{
	//	mVy = JUMPV0;
	//	mState = EState::EJUMP;
	//}

	//Y(Y() + mVy);
	//mVy -= GRAVITY;
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
	case ETag::EENEMY:
	case ETag::EEBULLET:
		if (CRectangle::Collision(o))
		{
			o->Collision(o, m);
		}
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
