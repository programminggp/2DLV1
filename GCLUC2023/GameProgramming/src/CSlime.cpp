#include "CSlime.h"
#include "CSlimeAttackBox.h"
#include "CApplication.h"
#include "CCharacter.h"

//無
#define MU 0,0,0,0
//立ち絵
#define SLIMENTL 37,164,179,63
#define SLIMENTR 164,37,179,63
//ジャンプ
#define SLIMEJPL 629,775,189,29
#define SLIMEJPR 775,629,189,29
//降下
#define SLIMEDWL 1036,1175,190,5
#define SLIMEDWR 1175,1036,190,5
//ダメージ
#define SLIMEDAL 230,369,179,62
#define SLIMEDAR 369,230,179,62
//攻撃
#define SLIMEATL 408,593,188,18
#define SLIMEATR 593,408,188,18
//死亡
#define SLIMEDTL 812,990,190,89
#define SLIMEDTR 990,812,190,89
#define SLIMEDTL2 812,990,190,69
#define SLIMEDTR2 990,812,190,69
#define SLIMEDTL3 812,990,190,49
#define SLIMEDTR3 990,812,190,49
#define SLIMEDTL4 812,990,190,29
#define SLIMEDTR4 990,812,190,29
#define SLIMEDTL5 812,990,190,9
#define SLIMEDTR5 990,812,190,9

#define GRAVITY (TIPSIZE / 250.0f)	
#define GRAVITY2 (TIPSIZE / 120.0f)//重力加速度
#define JUMPV0 (TIPSIZE / 8.0f)	//ジャンプの初速

#define SLIMEHP 100 //スライムのHP

int CSlime::sNum = 0;

CSlime* CSlime::spInstance2 = nullptr;

CSlime* CSlime::Instance2()
{
	return spInstance2;
}

int CSlime::SEhp()
{
	return sSEhp;
}

void CSlime::Num(int num)
{
	sNum = num;
}

int CSlime::Num()
{
	return sNum;
}

void CSlime::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

void CSlime::Collision(CCharacter* m, CCharacter* o)
{
	//めり込み調整変数を宣言する
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		/*if (mState != EState::EDEATH)
		{
			if (CRectangle::Collision(o, &x, &y))
			{
				if (mSlimeInvincible <= 0)
				{
					mSlimeInvincible = 60;
					if (mState != EState::EDAMAGE)
					{
						mSlimeTime = 60;
						if (mSVx < 0) { Texture(Texture(), MU); }
						if (mSVx > 0) { Texture(Texture(), MU); }
						sSEhp = sSEhp - 100;
						if (sSEhp <= 0)
						{
							mSlimeTime4 = 40;
							mState = EState::EDEATH;
						}
						if (mState != EState::EATTACK)
						{
							mState = EState::EDAMAGE;
						}
					}
				}
			}*/
		break;
	case ETag::EBULLET: //仮の魔法
		if (mState != EState::EDEATH)
		{
			if (CRectangle::Collision(o, &x, &y))
			{
				if (mSlimeInvincible <= 0)
				{
					mSlimeInvincible = 60;
					if (mState != EState::EDAMAGE)
					{
						if (mSVx < 0) { Texture(Texture(), MU); }
						if (mSVx > 0) { Texture(Texture(), MU); }
						mSlimeTime = 60;
						sSEhp = sSEhp - 100;
						if (sSEhp <= 0)
						{
							mSlimeTime4 = 40;
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
			//break;
			//case ETag::EDAGEKI: //仮の打撃
			// /*if (mState != EState::EDEATH)
			//{
		//	if (CRectangle::Collision(o, &x, &y))
		//	{
		//		if (mSlimeInvincible <= 0)
		//		{
		//			mSlimeInvincible = 60;
		//			if (mState != EState::EDAMAGE)
		//			{
		// if (mSVx < 0) { Texture(Texture(), MU); }
				//if (mSVx > 0) { Texture(Texture(), MU); }
		//				mSlimeTime = 60;
		//				sSEhp = sSEhp - 25;
		// if (sSEhp <= 0)
				/*{
					mSlimeTime4 = 40;
					mState = EState::EDEATH;
				}*/
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

CSlime::CSlime(float x, float y, float w, float h, CTexture* pt)
	: CCharacter((int)ETaskPriority::ECharacter)
{
	mTexture6.Load("スライム3.png");
	Set(x, y, w, h);
	Texture(pt, SLIMENTL); //テスト用の開始時の立ち絵
	mState = EState::EMOVE;
	mTag = ETag::EENEMY;
	sSEhp = SLIMEHP;
	//XとY軸速度の初期値を移動速度にする
	mSVx = SLIMEX;
	mSVy = SLIMEY;
	spInstance2 = this;
	sNum++;
}

void CSlime::Update()
{
	if (mSlimeTime > 0)
	{
		mSlimeTime--;
	}
	if (mSlimeTime4 >= 0)
	{
		mSlimeTime4--;
	}
	if (mSlimeTime3 > 0)
	{
		mSlimeTime3--;
	}
	if (mSlimeEattack > 0)
	{
		mSlimeEattack--;
		if (mSlimeEattack <= 0)
		{
			delete mpSlimeAttackBox;;
		}
	}
	CCharacter::Update();
	if (mSlimeInvincible >= 0)
	{
		mSlimeInvincible--;
	}
	switch (mState)
	{
		if (mSlimeEattack > 0)
		{
			mSlimeEattack--;
			if (mSlimeEattack <= 0)
			{
				delete mpSlimeAttackBox;;
			}
		}
	case EState::EDEATH: //死亡時
		if (mSlimeTime4 == 39)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMEDTL); }
			if (mSVx > 0) { Texture(Texture(), SLIMEDTR); }
		}
		if (mSlimeTime4 == 29)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMEDTL2); }
			if (mSVx > 0) { Texture(Texture(), SLIMEDTR2); }
		}
		if (mSlimeTime4 == 19)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMEDTL3); }
			if (mSVx > 0) { Texture(Texture(), SLIMEDTR3); }
		}
		if (mSlimeTime4 == 9)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMEDTL4); }
			if (mSVx > 0) { Texture(Texture(), SLIMEDTR4); }
		}
		if (mSlimeTime4 == 4)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMEDTL5); }
			if (mSVx > 0) { Texture(Texture(), SLIMEDTR5); }
		}
		if (mSlimeTime4 == 0)
		{
			Y(Y() + 1000);
			Texture(Texture(), 0, 0, 0, 0);//仮
			sNum--;
		}
		break;
	case EState::EATTACK: //攻撃時
		if (mSlimeTime3 == 59)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMENTL); }
			if (mSVx > 0) { Texture(Texture(), SLIMENTR); }
		}
		if (mSlimeTime3 == 30)
		{
			if (mSVx < 0)
			{
				Texture(Texture(), SLIMEATL);
				mpSlimeAttackBox = new CSlimeAttackBox(X() - 125, Z() + 60, 80.0f, 60.0f, CSlime::Texture6());
				mSlimeEattack = 30;
			}
			if (mSVx > 0)
			{
				Texture(Texture(), SLIMEATR);
				mpSlimeAttackBox = new CSlimeAttackBox(X() + 125, Z() + 60, 80.0f, 60.0f, CSlime::Texture6());
				mSlimeEattack = 30;
			}
		}
		if (mSlimeTime3 == 20)
		{
			if (mSVx < 0)
			{
				Texture(Texture(), SLIMEATL);
			}
			if (mSVx > 0)
			{
				Texture(Texture(), SLIMEATR);
			}
		}
		if (mSlimeTime3 == 10)
		{
			if (mSVx < 0)
			{
				Texture(Texture(), SLIMEATL);
			}
			if (mSVx > 0)
			{
				Texture(Texture(), SLIMEATR);
			}
		}
		if (mSlimeTime3 <= 0)
		{
			mState = EState::EMOVE;
		}
		break;
	case EState::EDAMAGE: //ダメージ時
		if (sSEhp <= 0)
		{
			mSlimeTime4 = 40;
			mState = EState::EDEATH;
		}
		if (mSlimeTime == 29)
		{
		}
		if (mSlimeTime == 59)
		{
			if (mSVx < 0) { Texture(Texture(), SLIMEDAL); }
			if (mSVx > 0) { Texture(Texture(), SLIMEDAR); }
		}
		if (mSlimeTime <= 0)
		{
			mState = EState::EMOVE;
		}
		break;
	case EState::EMOVE2:
		mSlimeTime2--;
		X(X() + mSVx);
		if (X() != CPlayer::Instance()->X())
		{
			Y(Y() + mSVy);
			if (mSlimeTime2 > 0)
			{
				mSVy -= GRAVITY2;
			}
			if (mSlimeTime2 < 0)
			{
				mSlimeTime2 = 40;
				mState = EState::EMOVE;
			}
			if (mSVy > 0)
			{
				if (mSVx < 0.0f)
				{
					Texture(Texture(), SLIMEJPL);
				}
				if (mSVx > 0.0f)
				{
					Texture(Texture(), SLIMEJPR);
				}
			}
			if (mSVy < 0)
			{
				if (mSVx < 0.0f)
				{
					Texture(Texture(), SLIMEDWL);
				}
				if (mSVx > 0.0f)
				{
					Texture(Texture(), SLIMEDWR);
				}
			}
		}
		break;
	case EState::EMOVE:
		mSlimeTime2--;
		X(X() + mSVx);
		if (X() > CPlayer::Instance()->X() - 125 && X() < CPlayer::Instance()->X() + 125)
		{
			if (Z() > CPlayer::Instance()->Z() - 50 && Z() < CPlayer::Instance()->Z() + 50)
			{
				if (mSlimeTime3 <= 0)
				{
					mSlimeTime3 = 60;
					mState = EState::EATTACK;
				}
			}
		}
		if (X() != CPlayer::Instance()->X())
		{
			Y(Y() + mSVy);
			if (X() < CPlayer::Instance()->X())
			{
				if (mSVx < 0)
					mSVx = -mSVx;
				Texture(Texture(), SLIMEDWR);
			}
			else
			{
				if (mSVx > 0)
					mSVx = -mSVx;
				Texture(Texture(), SLIMEDWL);
			}
			if (Z() < CPlayer::Instance()->Z())
			{
				if (CPlayer::Instance()->State() != EState::EJUMP)
				{
				if (mSVy < 0)
				{
					mSVy = -mSVy;
				}
			}
				else
				{
					if (mSVy > 0)
					{
						mSVy = JUMPV0;
						mSVy = -mSVy;
					}
				}
			}
			if (mState != EState::EMOVE2 && mSlimeTime2 < 30)
			{
				mSVy = JUMPV0;
				mState = EState::EMOVE2;
			}
		}
	}
}

CTexture* CSlime::Texture6()
{
	return &mTexture6;
}
CTexture CSlime::mTexture6;
