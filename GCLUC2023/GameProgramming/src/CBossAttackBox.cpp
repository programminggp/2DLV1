#include "CBossAttackBox.h"

#define MU 0, 200, 0, 0�@//��
#define WOLFNTL 0,0,0,0 //��

//�R���X�g���N�^
CBossAttackBox::CBossAttackBox(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::ECharacter)
{
	Set(x, y, w, h);
	Texture(pt, WOLFNTL);
	mTag = ETag::EATTACK2;
}

//�f�X�g���N�^
CBossAttackBox::~CBossAttackBox()
{
}

//�X�V����
void CBossAttackBox::Update()
{
	CCharacter::Update();
}