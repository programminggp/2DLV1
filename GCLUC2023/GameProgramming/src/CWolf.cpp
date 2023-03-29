#include "CWolf.h"
#include "CApplication.h"
#include "CCharacter.h"

//��
#define MU 0,0,0,0
//�����G
#define WOLFNTL 2,200,200,12
#define WOLFNTR 200,2,200,12
//�ړ��P
#define WOLFMOVEL 1003,1188,197,18
#define WOLFMOVER 1188,1003,197,18
//�ړ��Q�@//�ړ��P�̌�Ɉړ��Q��\������
#define WOLFMOVEL2 1210,1393,198,28
#define WOLFMOVER2 1393,1210,198,28
//�_���[�W
#define WOLFDAL 205,407,200,35
#define WOLFDAR 407,205,200,35
//�U���O
#define WOLFATL 801,996,200,23
#define WOLFATR 996,801,200,23
//�U���P
#define WOLFATL2 408,608,200,15
#define WOLFATR2 608,408,200,15
//�U���Q�@//�U���P�̌�ɍU���Q��\������
#define WOLFATL3 608,799,200,15
#define WOLFATR3 799,608,200,15
//���S
#define WOLFDTL 1412,1593,198,27
#define WOLFDTR 1593,1412,198,27

#define WOLFHP 300 

int CWolf::sNum = 0;

CWolf* CWolf::spInstance3 = nullptr;

CWolf* CWolf::Instance3()
{
	return spInstance3;
}

int CWolf::WEhp()
{
	return sWEhp;
}

void CWolf::Num(int num)
{
	sNum = num;
}

int CWolf::Num()
{
	return sNum;
}

void CWolf::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

void CWolf::Collision(CCharacter* m, CCharacter* o)
{
	////�߂荞�ݒ����ϐ���錾����
	float x, y;
	switch (o->Tag())
	{
		/*case ETag::EPLAYER:
			if (mState != EState::EDEATH)
			{
				if (CRectangle::Collision(o, &x, &y))
				{
					if (mWolfInvincible <= 0)
					{
						mWolfInvincible = 60;
						if (mState != EState::EDAMAGE)
						{
							if (mWVx < 0) { Texture(Texture(), MU); }
							if (mWVx > 0) { Texture(Texture(), MU); }
							mWolfTime = 60;
							sWEhp = sWEhp - 100;
							if (sWEhp <= 0)
							{
								mWolfTime3 = 20;
								mState = EState::EDEATH;
							}
							if (mState != EState::EATTACK)
							{
								mState = EState::EDAMAGE;
							}
						}
					}
				}
				break;*/
	case ETag::EBULLET: //���̖��@
		if (mState != EState::EDEATH)
		{
			if (CRectangle::Collision(o, &x, &y))
			{
				if (mWolfInvincible <= 0)
				{
					mWolfInvincible = 50;
					if (mState != EState::EDAMAGE)
					{
						if (mWVx < 0) { Texture(Texture(), MU); }
						if (mWVx > 0) { Texture(Texture(), MU); }
						mWolfTime = 40;
						sWEhp = sWEhp - 100;
						if (sWEhp <= 0)
						{
							mWolfTime3 = 20;
							mState = EState::EDEATH;
						}
						if (mState != EState::EATTACK)
						{
							mState = EState::EDAMAGE;
						}
					}
				}
			}
			break;
	case ETag::EENEMY:
		if (mState != EState::EATTACK)
		{
			if (CRectangle::Collision(o, &x, &y))
			{
				X(X() + x);
				Y(Y() + y);
			}
		}
		break;
	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
		}
			//case ETag::EDAGEKI: //���̑Ō�
			// // if (mState != EState::EDEATH)
			//{
		//	if (CRectangle::Collision(o, &x, &y))
		//	{
		//		if (mWolfInvincible <= 0)
		//		{
		//			mWolfInvincible = 60;
		//			if (mState != EState::EDAMAGE)
		//			{
		// //	//     if (mWVx < 0) { Texture(Texture(), MU); }
			//	//	   if (mWVx > 0) { Texture(Texture(), MU); }
		//				mWolfTime = 60;
		//				sWEhp = sWEhp - 25;
		//  if (sWEhp <= 0)
			//	/*{
			//		mWolfTime3 = 20;
			//		mState = EState::EDEATH;
			//	}*/
		//				if (mState != EState::EATTACK)
		//				{
		//					mState = EState::EDAMAGE;
		//				}
		//			}
		//		}
		//	}
		//}
		}
	}
}

CWolf::CWolf(float x, float y, float w, float h, CTexture* pt)
	: CCharacter((int)ETaskPriority::ECharacter)
{
	mTexture7.Load("�q�T2.png");
	Set(x, y, w, h);
	Texture(pt, WOLFMOVEL); //�J�n���̗����G
	mState = EState::EMOVE;
	mTag = ETag::EENEMY;
	sWEhp = WOLFHP; //�I�I�J�~��HP
	//X��Y�����x�̏����l���ړ����x�ɂ���
	mWVx = WOLFX;
	mWVy = WOLFY;
	spInstance3 = this;
	sNum++;
}

void CWolf::Update()
{
	if (mWolfTime2 >= 0)
	{
		mWolfTime2--;
	}
	if (mWolfTime3 >= 0)
	{
		mWolfTime3--;
	}
	if (mWolfTime > 0)
	{
		mWolfTime--;
	}
	if (mWolfEattack > 0)
	{
		mWolfEattack--;
		if (mWolfEattack <= 0)
		{
			delete mpWolfAttackBox;
		}
	}
	CCharacter::Update();
	if (mWolfInvincible >= 0)
	{
		mWolfInvincible--;
	}
	switch (mState)
	{
	case EState::EDEATH: //���S��
		//HP���O�ɂȂ������b��ɏ��ł�����
		if (mWolfTime3 == 19)
		{
			if (mWVx < 0) { Texture(Texture(), WOLFDAL); }
			if (mWVx > 0) { Texture(Texture(), WOLFDAR); }
		}
		if (mWolfTime3 == 9)
		{
			if (mWVx < 0) { Texture(Texture(), WOLFDTL); }
			if (mWVx > 0) { Texture(Texture(), WOLFDTR); }
		}
		if (mWolfTime3 == 0)
		{
			Y(Y() + 1000);
			Texture(Texture(), 0, 0, 0, 0); //��
			sNum--;
		}
		break;
	case EState::EATTACK: //�U����
		if (mWolfTime2 == 29)
		{
			if (mWVx < 0) { Texture(Texture(), WOLFATL); }
			if (mWVx > 0) { Texture(Texture(), WOLFATR); }
		}
		if (mWolfTime2 == 22)
		{
			if (mWVx < 0) { Texture(Texture(), WOLFATL); }
			if (mWVx > 0) { Texture(Texture(), WOLFATR); }
		}
		if (mWolfTime2 == 14)
		{
			if (mWVx < 0) { Texture(Texture(), WOLFATL2); }
			if (mWVx > 0) { Texture(Texture(), WOLFATR2); }
		}
		if (mWolfTime2 == 4)
		{
			if (mWVx < 0)
			{
				Texture(Texture(), WOLFATL3);
				mpWolfAttackBox = new CWolfAttackBox(X() - 125, Z() + 40, 60.0f, 40.0f, CWolf::Texture7());
				mWolfEattack = 4;
			}
			if (mWVx > 0)
			{
				Texture(Texture(), WOLFATR3);
				mpWolfAttackBox = new CWolfAttackBox(X() + 125, Z() + 40, 60.0f, 40.0f, CWolf::Texture7());
				mWolfEattack = 4;
			}
		}
		if (mWolfTime2 == 0)
		{
			mState = EState::EMOVE;
		}
		break;
	case EState::EDAMAGE: //�_���[�W��
		if (sWEhp == 0)
		{
			mWolfTime3 = 20;
			mState = EState::EDEATH;
		}
		if (mWolfTime == 39)
		{
			if (mWVx < 0) { Texture(Texture(), WOLFDAL); }
			if (mWVx > 0) { Texture(Texture(), WOLFDAR); }
		}
		if (mWolfTime == 0)
		{
			mState = EState::EMOVE;
		}
		break;
	case EState::EMOVE:
		if (X() < CPlayer::Instance()->X())
		{
			mWLR = 1;
		}
		else
		{
			mWLR = 2;
		}

		//�v���C���[��ǔ�����
		if (mWLR == 1)
		{
			if (X() < CPlayer::Instance()->X() - 125)
			{
				X(X() + mWVx);
				if (X() < CPlayer::Instance()->X())
				{
					if (mWVx < 0)
						mWVx = -mWVx;
				}
			}
		}
		if (mWLR == 2)
		{
			if (X() > CPlayer::Instance()->X() + 125)
			{
				X(X() + mWVx);
				if (X() > CPlayer::Instance()->X())
				{
					if (mWVx > 0)
						mWVx = -mWVx;
				}
			}
		}
		if (X() > CPlayer::Instance()->X() - 150 && X() < CPlayer::Instance()->X() + 150)
		{
			if (Z() > CPlayer::Instance()->Z() - 25 && Z() < CPlayer::Instance()->Z() + 25)
			{
				if (mWolfTime2 <= 0)
				{
					mWolfTime2 = 30;
					mState = EState::EATTACK;
				}
			}
		}
		if (Z() != CPlayer::Instance()->Z())
		{
			if (CPlayer::Instance()->State() != EState::EJUMP)
			{
				Y(Y() + mWVy);
				if (Z() < CPlayer::Instance()->Z())
				{
					if (mWVy < 0)
						mWVy = -mWVy;
				}
				else
				{
					if (mWVy > 0)
						mWVy = -mWVy;
				}
			}
		}
		const int PITCH = 64;//�摜��؂�ւ���Ԋu
		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mWVx < 0)
			{
				Texture(Texture(), WOLFMOVEL);
			}
			else
			{
				Texture(Texture(), WOLFMOVER2);
			}
		}
		else
		{
			if (mWVx > 0)
			{
				Texture(Texture(), WOLFMOVER);
			}
			else
			{
				Texture(Texture(), WOLFMOVEL2);
			}
		}
	}
}

CTexture* CWolf::Texture7()
{
	return &mTexture7;
}
CTexture CWolf::mTexture7;