#include "CEattack.h"

#define MU 0, 200, 0, 0�@//��
#define WOLFNTL 1206,1796,433,133 //��

//�R���X�g���N�^
CEattack::CEattack(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mState = EState::EATTACK;
}

//�f�X�g���N�^
CEattack::~CEattack()
{
}

//�X�V����
void CEattack::Update()
{
	CCharacter::Update();
}