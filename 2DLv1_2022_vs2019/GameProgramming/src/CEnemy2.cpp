#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//�e�N�X�`���}�b�s���O
#define TEXCRY 196, 216, 190, 160	//�e�N�X�`���}�b�s���O

void CEnemy2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CEnemy2::Collision(CCharacter* m, CCharacter* o)
{
	//�߂荞�ݒ����ϐ���錾����
	float x, y;
	switch (o->Tag())
	{
	case ETag::ETURN:
		//�܂�Ԃ��ɓ���������
		if (CRectangle::Collision(o, &x, &y))
		{
			//�߂荞�܂Ȃ��ʒu�܂Ŗ߂�
			X(X() + x);
			Y(Y() + y);
			//X�����x�𔽓]������
			mVx = -mVx;
		}
		break;
	case ETag::EENEMY:
		break;
	case ETag::EPLAYER:
		if (CRectangle::Collision(o))
		{
			if (o->State() == EState::EJUMP)
			{
				mState = EState::ECRY;
			}
		}
		break;
	}
}

CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EENEMY;
	//X�����x�̏����l���ړ����x�ɂ���
	mVx = VELOCITY;
}

void CEnemy2::Update()
{
	switch (mState)
	{
	case EState::ECRY:
		//�����摜��ݒ�
		Texture(Texture(), TEXCRY);
		break;
	case EState::EMOVE:
		//X�����x���AX���W���X�V����
		X(X() + mVx);
		break;
	}
}
