#include "CBoss.h"
#include "CApplication.h"

#define MU 0,0,0,0
//à⁄ìÆÅAóßÇøäG
#define BOSSNTL 2570,3127,523,25
#define BOSSNTR 3127,2570,523,25
//ëñÇË
#define BOSSRUNL 3184,3779,523,10
#define BOSSRUNR 3779,3184,523,10
//çUåÇéû
#define BOSSAT1L 151,728,534,46
#define BOSSAT1R 728,151,534,46
#define BOSSAT2L 756,1327,523,48
#define BOSSAT2R 1327,756,523,48
//ëÂçUåÇ
#define BOSSAT3L 626,1182,488,23
#define BOSSAT3R 1182,626,488,23
//É_ÉÅÅ[ÉW
#define BOSSDAL 1965,2527,524,25
#define BOSSDAR 2527,1965,524,25
//éÄñS
#define BOSSDTL 1350,1939,470,153
#define BOSSDTR 1939,1350,470,153
//ôÙöK
#define BOSSALL 3913,4174,451,164
#define BOSSALR 4174,3913,451,164

#define BOSSHP 1300

int CBoss::sBEhp = 0;

int CBoss::sNum = 0;

CBoss* CBoss::spInstance4 = nullptr;

CBoss* CBoss::Instance4()
{
	return spInstance4;
}

int CBoss::BEhp()
{
	return sBEhp;
}

void CBoss::Num(int num)
{
	sNum = num;
}

int CBoss::Num()
{
	return sNum;
}

void CBoss::Collision()
{
	//CApplication::CharacterManager()->Collision(this);
}

void CBoss::Collision(CCharacter* m, CCharacter* o)
{
	//ÇﬂÇËçûÇ›í≤êÆïœêîÇêÈåæÇ∑ÇÈ
	float x, y;
	switch (o->Tag())
	{
		//case ETag::EPLAYER:
		//	//ê‹ÇËï‘ÇµÇ…ìñÇΩÇ¡ÇΩéû
		//	if (mState != EState::EDEATH)
		//	{
		//		if (CRectangle::Collision(o, &x, &y))
		//		{
		//			if (mBossInvincible <= 0)
		//			{
		//				mBossInvincible = 60;
		//				if (mState != EState::EDAMAGE)
		//				{
		//					mBossTime2 = 60;
		//					if (mBVx < 0) { Texture(Texture(), MU); }
		//					if (mBVx > 0) { Texture(Texture(), MU); }
		//					sBEhp = sBEhp - 100;
		//					if (sBEhp <= 0)
		//					{
		//						mBossTime3 = 40;
		//						mState = EState::EDEATH;
		//					}
		//					if (mState != EState::EATTACK && mState != EState::EATTACK2)
		//					{
		//						mState = EState::EDAMAGE;
		//					}
		//				}
		//			}
		//		}
		break;
		//}
	case ETag::EBULLET:
		if (mState != EState::EDEATH && mState != EState::EATTACK2)
		{
			if (CRectangle::Collision(o, &x, &y))
			{
				if (mBossInvincible <= 0)
				{
					mBossInvincible = 60;
					if (mState != EState::EDAMAGE)
					{
						mBossTime2 = 30;
						if (mBVx < 0) { Texture(Texture(), MU); }
						if (mBVx > 0) { Texture(Texture(), MU); }
						sBEhp = sBEhp - 100;
						if (sBEhp <= 0)
						{
							mBossTime3 = 40;
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
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
		}
		break;
	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
		}
		}
	}
}

CBoss::CBoss(float x, float y, float w, float h, CTexture* pt)
	: CCharacter((int)ETaskPriority::ECharacter)
{
	mTexture8.Load("É{ÉX3.png");
	Set(x, y, w, h);
	Texture(pt, BOSSNTL);
	mState = EState::EMOVE;
	mTag = ETag::EENEMY;
	sBEhp = BOSSHP;
	//XÇ∆Yé≤ë¨ìxÇÃèâä˙ílÇà⁄ìÆë¨ìxÇ…Ç∑ÇÈ
	mBVx = BOSSX;
	mBVy = BOSSY;
	mFlg1 = 0;
	mFlg2 = 0;
	mFlg3 = 0;
	mFlg4 = 0;
	spInstance4 = this;
	sNum++;
}

void CBoss::Update()
{
	if (mBossInvincible > 0)
	{
		mBossInvincible--;
	}
	if (mBossTime2 >= 0)
	{
		mBossTime2--;
	}
	if (mBossTime4 >= 0)
	{
		mBossTime4--;
	}
	if (mBossTime >= 0)
	{
		mBossTime--;
	}
	if (mBossTime3 >= 0)
	{
		mBossTime3--;
	}
	if (mFlg1 != 1 && sBEhp <= 750)
	{
		mFlg1 = 1;
		mBossTime4 = 120;
		mState = EState::EATTACK2;
	}
	if (mBossEattack > 0)
	{
		mBossEattack--;
		if (mBossEattack <= 0)
		{
			delete mpBossAttackBox;
		}
	}
	if (mBossEattack2 > 0)
	{
		mBossEattack2--;
		if (mBossEattack2 <= 0)
		{
			delete mpBossAttackBox2;
		}
	}
	CCharacter::Update();
	switch (mState)
	{
	case EState::EDEATH://éÄñSéû
		/*if (mBossTime3 >= 0)
		{
			mBossTime3--;
		}*/
		if (mBossTime3 == 39)
		{
			if (mBVx < 0) { Texture(Texture(), BOSSDTL); }
			if (mBVx > 0) { Texture(Texture(), BOSSDTR); }
		}
		if (mBossTime3 == 0)
		{
			Y(Y() + 1000);
			Texture(Texture(), 0, 0, 0, 0);//âº
			sNum--;
		}
		break;
	case EState::EATTACK: //çUåÇéû
		/*if (mBossTime >= 0)
		{
			mBossTime--;
		}*/
		if (mBossTime == 59)
		{
			if (mBVx < 0)
			{
				Texture(Texture(), BOSSAT1L);
			}
			if (mBVx > 0)
			{
				Texture(Texture(), BOSSAT1R);
			}
		}
		if (mBossTime == 30)
		{
			if (mBVx < 0)
			{
				Texture(Texture(), BOSSAT2L);
				mpBossAttackBox = new CBossAttackBox(X() - 300, Y(), 200.0f, 240.0f, CBoss::Texture8());
				mBossEattack = 30;
			}
			if (mBVx > 0)
			{
				Texture(Texture(), BOSSAT2R);
				mpBossAttackBox = new CBossAttackBox(X() + 300, Y(), 200.0f, 240.0f, CBoss::Texture8());
				mBossEattack = 30;
			}
		}
		if (mBossTime == 20)
		{
			if (mBVx < 0)
			{
				Texture(Texture(), BOSSAT2L);
			}
			if (mBVx > 0)
			{
				Texture(Texture(), BOSSAT2R);
			}
		}
		if (mBossTime == 10)
		{
			if (mBVx < 0)
			{
				Texture(Texture(), BOSSAT2L);
			}
			if (mBVx > 0)
			{
				Texture(Texture(), BOSSAT2R);
			}
		}
		if (mBossTime == 0)
		{
			//delete mpEattack;
			if (mFlg4 != 1 && mFlg1 != 0 && sBEhp <= 750)
			{
				if (mFlg2 != 0)
				{
					if (mFlg3 != 0)
					{
						mFlg4 = 1;
					}
					mFlg3 = 1;
					mState = EState::EMOVE;
				}
				mFlg2 = 1;
				mState = EState::EMOVE;
			}
			if (sBEhp > 750)
			{
				mState = EState::EMOVE;
			}
		}
		if (mFlg4 == 1)
		{
			mState = EState::EATTACK2;
			mBossTime4 = 120;
		}
		break;
	case EState::EATTACK2:
		/*if (mBossTime4 >= 0)
		{
			mBossTime4--;
		}*/
		if (sBEhp <= 750)
		{
			if (mBossTime4 >= 90)
			{
				if (X() > CPlayer::Instance()->X() - 650 && X() < CPlayer::Instance()->X() + 650)
				{
					X(X() + mBVx);
					mBVx = BOSSXXR;
					if (mBVx > 0)
					{
						Texture(Texture(), BOSSRUNR);
					}
					if (mBVx < 0)
					{
						Texture(Texture(), BOSSRUNL);
					}
				}
			}
			if (mBossTime4 == 89)
			{
				if (mBVx > 0)
				{
					Texture(Texture(), BOSSNTL);
				}
				if (mBVx < 0)
				{
					Texture(Texture(), BOSSNTR);
				}
				//ï`âÊ
			}
			if (mBossTime4 == 59)
			{
				if (mBVx > 0)
				{
					Texture(Texture(), BOSSAT1L);
					mpBossAttackBox2 = new CBossAttackBox2(X() - 300, Y(), 160.0f, 240.0f, CBoss::Texture8());
					mBossEattack2 = 59;
				}
				if (mBVx < 0)
				{
					Texture(Texture(), BOSSAT1R);
					mpBossAttackBox2 = new CBossAttackBox2(X() + 300, Y(), 160.0f, 240.0f, CBoss::Texture8());
					mBossEattack2 = 59;
				}
			}
			if (mBossTime4 == 39)
			{
				if (mBVx > 0)
				{
					Texture(Texture(), BOSSNTL);
				}
				if (mBVx < 0)
				{
					Texture(Texture(), BOSSNTR);
				}
			}
			if (mBossTime4 < 0)
			{
				mBVx = BOSSX;
				mBVy = BOSSY;
				mFlg2 = 0;
				mFlg3 = 0;
				mFlg4 = 0;
				mState = EState::EMOVE;
			}
		}
		break;
	case EState::EDAMAGE: //É_ÉÅÅ[ÉWéû
		if (sBEhp <= 0)
		{
			mBossTime3 = 40;
			mState = EState::EDEATH;
		}
		/*if (mBossTime2 >= 0)
		{
			mBossTime2--;
		}*/
		if (mBossTime2 == 29)
		{
			if (mBVx < 0) { Texture(Texture(), BOSSDAL); }
			if (mBVx > 0) { Texture(Texture(), BOSSDAR); }
		}
		if (mBossTime2 == 0)
		{
			mState = EState::EMOVE;
		}
		break;
	case EState::EMOVE: //à⁄ìÆ
		CCharacter::Update();
		if (X() > CPlayer::Instance()->X() - 300 && X() < CPlayer::Instance()->X() + 300)
		{
			if (Z() > CPlayer::Instance()->Z() - 125 && Z() < CPlayer::Instance()->Z() + 125)
			{
				if (mBossTime <= 0)
				{
					mBossTime = 60;
					mState = EState::EATTACK;
				}
			}
		}
		if (X() < CPlayer::Instance()->X())
		{
			mBLR = 1;
		}
		else
		{
			mBLR = 2;
		}

		//ÉvÉåÉCÉÑÅ[Çí«îˆÇ∑ÇÈ
		if (mBLR == 1)
		{
			if (X() < CPlayer::Instance()->X() - 250)
			{
				X(X() + mBVx);
				if (X() < CPlayer::Instance()->X())
				{
					if (mBVx < 0)
						mBVx = -mBVx;
				}
			}
		}
		if (mBLR == 2)
		{
			if (X() > CPlayer::Instance()->X() + 250)
			{
				X(X() + mBVx);
				if (X() > CPlayer::Instance()->X())
				{
					if (mBVx > 0)
						mBVx = -mBVx;
				}
			}
		}
		if (Z() != CPlayer::Instance()->Z())
		{
			if (CPlayer::Instance()->State() != EState::EJUMP)
			{
				Y(Y() + mBVy);
				if (Z() < CPlayer::Instance()->Z())
				{
					if (mBVy < 0)
						mBVy = -mBVy;
				}
				else
				{
					if (mBVy > 0)
						mBVy = -mBVy;
				}
			}
		}
		const int PITCH = 64;//âÊëúÇêÿÇËë÷Ç¶ÇÈä‘äu
		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mBVx < 0)
			{
				Texture(Texture(), BOSSNTL);
			}
			else
			{
				Texture(Texture(), BOSSRUNR);
			}
		}
		else
		{
			if (mBVx > 0)
			{
				Texture(Texture(), BOSSNTR);
			}
			else
			{
				Texture(Texture(), BOSSRUNL);
			}
		}
	}
}

CTexture* CBoss::Texture8()
{
	return &mTexture8;
}
CTexture CBoss::mTexture8;