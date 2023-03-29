#include "CPlayer.h"
#include "CApplication.h"

#define DEFAULT  0, 200, 400, 200   //�A�C�h�����O�e�N�X�`��(�E����)

#define JUMPV0 30               	//�W�����v�̏���
#define GRAVITY 2.0f	            //�d�͉����x

#define PLAYERHP 10                 //�v���C���[��HP
#define STAMINA 100                 //�v���C���[�̃X�^�~�i

//������
CPlayer* CPlayer::spinstance = nullptr;
int CPlayer::sHp = 0;
int CPlayer::sStamina = 0;
int CPlayer::sCoolTime = 0;

//�R���X�g���N�^
CPlayer::CPlayer(float x, float y, float w, float h, CTexture* pt)
	: CCharacter((int)ETaskPriority::ECharacter)
	, mInvincible(0)
	, mAnimationCount(0)
	, mJumpY(0.0f)
	, mpMagicBullet(nullptr)
{
	Set(x, y, w, h );
	Texture(pt, DEFAULT);
	mTag = ETag::EPLAYER;
	mState = EState::EIDLING;
	sHp = PLAYERHP;
	sStamina = STAMINA;
	spinstance = this; 
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
}

//�C���X�^���X�쐬
CPlayer* CPlayer::Instance()
{
	return spinstance;
}

//HP���擾
int CPlayer::HP()
{
	return sHp;
}

//�X�^�~�i���擾
int CPlayer::Stamina()
{
	return sStamina;
}

//�Փˏ���
void CPlayer::Collision(CCharacter* m, CCharacter* o)
{
	//�߂荞�ݒ����ϐ�
	float x, y;
	switch (o->Tag())
	{
	case ETag::EATTACK:
		if (CRectangle::Collision(o, &x, &y))
		{
			//���G��ԈȊO�̎�
			if (mState != EState::EJUMP && mState != EState::EDAMAGE)
			{
				sHp--;
				mState = EState::EDAMAGE;
			}
		}
		break;
	case ETag::EATTACK2:
		if (CRectangle::Collision(o, &x, &y))
		{
			if (mState != EState::EJUMP && mState != EState::EDAMAGE)
			{
				sHp = sHp - 2;
				mState = EState::EDAMAGE;
			}
		}
	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			Y(Y() + y);
		}
	case ETag::EENEMY:
		break;
	case ETag::EBULLET:
		break;
	case ETag::EPLAYER:
		break;
	case ETag::EZERO:
		break;
	}
}

//�X�V����
void CPlayer::Update()
{
	switch (State())
	{
		//�ړ����
	case EState::EMOVE: Move();
		sCoolTime++;
		if (sCoolTime >= 30)
			sStamina++;
		break;
		//�W�����v���
	case EState::EJUMP: Jump();
		sCoolTime = 0;
		break;
		//�A�C�h�����O���
	case EState::EIDLING: Idling();
		sCoolTime++;
		if (sCoolTime >= 30)
			sStamina++;
		break;
		//�U�����
	case EState::EATTACK: Attack();
		sCoolTime = 0;
		break;
		//��e���
	case EState::EDAMAGE: Damage();
		sCoolTime++;
		if (sCoolTime >= 40)
			sStamina++;
		break;
		//���S���
	case EState::EDEATH: Death();
		sCoolTime = 0;
		break;
	}

	//�f�o�b�O�p
	if (mInput.Key('L') == true)
	{
     	mVx = -VELOCITY - 1;
		X(X() + mVx);
	}
	//�f�o�b�O�p
	if (mInput.Key('M'))
	{
		if (mState != EState::EJUMP && mState != EState::EDAMAGE)
		{
			sHp--;
			mState = EState::EDAMAGE;
		}
	}

	//HP��0�ɂȂ�Ǝ��S��Ԃɂ���
	if (sHp <= 0)
	{
		if (mState != EState::EJUMP && mState != EState::EDEATH)
		{
			mState = EState::EDEATH;
		}
	}
	//�X�^�~�i�̏��
	if (sStamina >= 100)
	{
		sStamina = 100;
	}
	//�X�^�~�i�̉���
	else if (sStamina < 0)
	{
		sStamina = 0;
	}
	CCharacter::Update();
}

//�ړ�����
void CPlayer::Move()
{
	float left;
	float right;
	mAnimationCount %= 48;
	left = (mAnimationCount / 8) * 200;
	right = left + 200;
	mAnimationCount++;
	//�E����
	if (mVx >= 0)
	{
		Texture(Texture(), left, right, 200, 0);
	}
	if (mVx < 0) //������
	{
		Texture(Texture(), right, left, 200, 0);
	}
	//X�������ړ�
	if (mInput.Key('A'))
	{
		mVx = -VELOCITY - 1;
		X(X() + mVx);
	}
	if (mInput.Key('D'))
	{
		mVx = VELOCITY + 1;
		X(X() + mVx);
	}
	//Y�������ړ�
	if (mInput.Key('W'))
	{
		mVy = VELOCITY + 1;
		Y(Y() + mVy);
	}
	if (mInput.Key('S'))
	{
		mVy = VELOCITY - 1;
		Y(Y() - mVy);
	}
	//�U��
	if (mInput.Key('K'))
	{
		if (sStamina >= 20)
		{l
			mState = EState::EATTACK;
			mAnimationCount = 0;
		}
	}
	//�W�����v
	if (mState != EState::EJUMP)
	{
		if (mInput.Key('J') && sStamina >= 5)
		{
			mJumpY = Y();
			mVy = JUMPV0;
			mState = EState::EJUMP;
			mAnimationCount = 0;
			sStamina = sStamina - 5;
		}
	}
	//�������͂���Ă��Ȃ����A�C�h�����O��Ԃɂ���
	if (mInput.Key('W') == false && mInput.Key('A') == false &&
		mInput.Key('S') == false && mInput.Key('D') == false &&
		mInput.Key('J') == false && mInput.Key('K') == false)
	{
		mState = EState::EIDLING;
		mAnimationCount = 0;
	}
}

//�W�����v����
void CPlayer::Jump()
{
	float left;
	float right;
	//Y�����x�ɏd�͂����Z����
	mVy -= GRAVITY;
	Y(Y() + mVy);

	mAnimationCount++;
	mAnimationCount %= 30;
	left = (mAnimationCount / 15) * 200;
	right = left + 200;
	if (mVx >= 0)
	{
		Texture(Texture(), left, right, 800, 600);
	}
	else
	{
		Texture(Texture(), right, left, 800, 600);
	}
	//���n������A�C�h�����O��Ԃɂ���
	if (mJumpY >= Y())
	{
		mState = EState::EIDLING;
		mAnimationCount = 0;
	}
	//X�������ړ�
	if (mInput.Key('A'))
	{
		mVx = -VELOCITY;
		X(X() + mVx);
	}
	if (mInput.Key('D'))
	{
		mVx = VELOCITY;
		X(X() + mVx);
	}
}

//�A�C�h�����O����
void CPlayer::Idling()
{
	float left;
	float right;
	mAnimationCount++;
	mAnimationCount %= 40;
	left = (mAnimationCount / 20) * 200;
	right = left + 200;
	//�E����
	if (mVx >= 0)
	{
		Texture(Texture(), left, right, 400, 200);
	}
	else //������
	{
		Texture(Texture(), right, left, 400, 200);
	}

	//�L�[���͂Ŋe��ԂɈڍs����
	if (mInput.Key('W') || mInput.Key('A') ||
		mInput.Key('S') || mInput.Key('D'))
	{
		mState = EState::EMOVE;
		mAnimationCount = 0;
	}
	if (mInput.Key('K'))
	{
		if (sStamina >= 20)
		{
			mState = EState::EATTACK;
			mAnimationCount = 0;
		}
	}
	if (mInput.Key('J') && sStamina >= 5)
	{
		mJumpY = Y();
		mVy = JUMPV0;
		mState = EState::EJUMP;
		mAnimationCount = 0;
		sStamina = sStamina - 5;
	}
}

//�U������
void CPlayer::Attack()
{
	float left;
	float right;
	mAnimationCount++;
	left = (mAnimationCount / 15) * 200;
	right = left + 200;
	if (mVx >= 0)
	{
		Texture(Texture(), left, right, 600, 400);
	}
	else
	{
		Texture(Texture(), right, left, 600, 400);
	}
	//��Ԃ��A�C�h�����O�ɂ���
	if (mAnimationCount >= 29)
	{
		mState = EState::EIDLING;
		mAnimationCount = 0;
		delete mpMagicBullet;
	}
	//���������
	if (mAnimationCount == 10)
	{
		sStamina = sStamina - 20;
		//�E����
		if (mVx >= 0)
		{
			mpMagicBullet = new CMagicBullet(X() + 50, Y() - 50, 100, 100, CApplication::Texture());
		}
		else //�������̎�
		{
			mpMagicBullet = new CMagicBullet(X() - 50, Y() - 50, 100, 100, CApplication::Texture());
		}
	}
}

//��e����
void CPlayer::Damage()
{
	float left;
	float right;
	mAnimationCount++;
	mAnimationCount %= 10;
	left = (mAnimationCount / 5) * 200;
	right = left + 200;
	//�E����
	if (mVx >= 0)
	{
		Texture(Texture(), left, right, 1000, 800);
	}
	else //������
	{
		Texture(Texture(), right, left, 1000, 800);
	}
	//���G���Ԃ̐ݒ�
	if (mInvincible < 0)
	{
		mInvincible = 40;
	}
	mInvincible--;
	if (mInvincible == 0)
	{
		mState = EState::EIDLING;
		mAnimationCount = 0;
	}

	//X�������ړ�
	if (mInput.Key('A'))
	{
		mVx = -VELOCITY - 1;
		X(X() + mVx);
	}
	if (mInput.Key('D'))
	{
		mVx = VELOCITY + 1;
		X(X() + mVx);
	}
	//Y�������ړ�
	if (mInput.Key('W'))
	{
		mVy = VELOCITY + 1;
		Y(Y() + mVy);
	}
	if (mInput.Key('S'))
	{
		mVy = VELOCITY - 1;
		Y(Y() - mVy);
	}
}

//���S����
void CPlayer::Death()
{
	float left;
	float right;
	if (mAnimationCount <= 60)
	{
		mAnimationCount++;
	}
	left = (mAnimationCount / 60) * 200;
	right = left + 200;
	Texture(Texture(), left, right, 1200, 1000);
}