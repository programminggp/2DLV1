#include "CBossAttackBox2.h"
#include "CBoss.h"

#define MU 0, 200, 0, 0�@//��
#define WOLFNTL 1206,1796,433,133 //��
#define BOSSALL 3913,4174,451,164
#define BOSSALR 4174,3913,451,164

//�R���X�g���N�^
CBossAttackBox2::CBossAttackBox2(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mTag = ETag::EATTACK;
}

//�f�X�g���N�^
CBossAttackBox2::~CBossAttackBox2()
{
}

//�X�V����
void CBossAttackBox2::Update()
{
	if (CBoss::Instance4()->mVx >= 0)
	{
		Texture(Texture(), BOSSALL);
		mVx = -VELOCITY - 10;
		X(X() + mVx);
	}
	else
	{
		Texture(Texture(), BOSSALR);
		mVx = VELOCITY + 10;
		X(X() + mVx);
	}
	CCharacter::Update();
}