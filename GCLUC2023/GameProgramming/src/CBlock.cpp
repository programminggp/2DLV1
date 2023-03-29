#include "CBlock.h"
#include "CApplication.h"

#define TEXCOORD 0,0,0,0//22, 22, 22, 22

//�R���X�g���N�^
CBlock::CBlock(float x, float y, float w, float h, CTexture* pt)
	:CCharacter((int)ETaskPriority::EBLOCK)
{
	Set(x, y, w, h* 5);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK;
}

//�Փ˔���2
void CBlock::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

//�Փ˔���4
void CBlock::Collision(CCharacter* m, CCharacter* o)
{
	////�߂荞�ݒ����ϐ���錾����
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		if (CRectangle::Collision(o))
		{
		}
		break;
	}
}

//�X�V����
void CBlock::Update()
{
	CCharacter::Update();
}