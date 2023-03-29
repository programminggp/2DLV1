#include "CMagicBullet.h"
#include "CPlayer.h"

#define MAGICBULLET 0, 200, 1400, 1200
#define MAGICBULLET2 200, 0, 1400, 1200 

//�R���X�g���N�^
CMagicBullet::CMagicBullet(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h );
	Texture(pt, MAGICBULLET);
	mTag = ETag::EBULLET;
	mState = EState::ENULL;
}

//�f�X�g���N�^
CMagicBullet::~CMagicBullet()
{
}

//�X�V����
void CMagicBullet::Update()
{
	if (CPlayer::Instance()->mVx >=  0)
	{
		mVx = VELOCITY + 10;
		X(X() + mVx);
	}
	else
	{
		Texture (Texture(),MAGICBULLET2);
		mVx = -VELOCITY - 10;
		X(X() + mVx);
	}
	CCharacter::Update();
}