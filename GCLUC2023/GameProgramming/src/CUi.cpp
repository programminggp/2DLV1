#include <stdio.h>
#include "CUi.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "CApplication.h"

//コンストラクタ
CUi::CUi()
	: mHp(0)
	, mTime(0)
	, mEnemy(0)
	, mBEhp(0)
	, mHeart(20, 770, 24, 24, &mTexture100)
	, mGage(20, 700, 24, 24, &mTexture101)
	, mStamina(20, 700, 24, 24, &mTexture102)
	, mBossHp(20,20,24,24,&mTexture103)
	, mBossHpGage(20,20,24,24,&mTexture104)
{
	mFont.Load("いろはマル.png", 1, 64);
	mFont2.Load("FontWhite.png",1,64);
	mTexture100.Load("プレイヤーHP.png");
	mTexture101.Load("MPゲージ.png");
	mTexture102.Load("プレイヤーMP.png");
	mTexture103.Load("ボスHP.png");
	mTexture104.Load("ボスHP枠.png");
}

//デストラクタ
CUi::~CUi()
{
}

//クリア表示
void CUi::Clear()
{
	char str[32];
	sprintf(str, "%03d", mTime);
	mFont.Draw(1200, 500, 16, 28, str);
}

//ゲームオーバー表示
void CUi::Over()
{
	/*mFont.Draw(36, 300, 18, 36, "GAME OVER!!");
	mFont.Draw(36, 200, 18, 36, "PUSH ENTER KEY!");*/
}

//スタート表示
void CUi::Start()
{
	//mFont.Draw(36, 300, 18, 36, "START PUSH ENTER KEY!");
}

void CUi::Enemy(int enemy)
{
	mEnemy = enemy;
}

void CUi::Hp(int hp)
{
	mHp = hp;
}

void CUi::Stamina(int stamina)
{
	mStaminagage = stamina;
}

void CUi::BEhp(int behp)
{
	mBEhp = behp;
}

void CUi::Time(int time)
{
	mTime = time;
}

void CUi::DrawResult()
{
	char str[32];
	sprintf(str, "%03d", mTime);
	mFont.Draw(600, 195, 40, 40, str);
}

void CUi::Render()
{
	char str[32];
	sprintf(str, "%03d", mTime);
	mFont.Draw(1200, 770, 16, 28, str);
	sprintf(str, "ATTACK:K KEY");
	mFont2.Draw(600, 770, 16, 28, str);
	sprintf(str, "JUMP:J KEY");
	mFont2.Draw(600, 700, 16, 28, str);

	if (mHp == 10)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
		mHeart.X(280);
		mHeart.Render();
		mHeart.X(330);
		mHeart.Render();
		mHeart.X(380);
		mHeart.Render();
		mHeart.X(430);
		mHeart.Render();
		mHeart.X(480);
		mHeart.Render();
	}
	if (mHp == 9)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
		mHeart.X(280);
		mHeart.Render();
		mHeart.X(330);
		mHeart.Render();
		mHeart.X(380);
		mHeart.Render();
		mHeart.X(430);
		mHeart.Render();
	}
	if (mHp == 8)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
		mHeart.X(280);
		mHeart.Render();
		mHeart.X(330);
		mHeart.Render();
		mHeart.X(380);
		mHeart.Render();
	}
	if (mHp == 7)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
		mHeart.X(280);
		mHeart.Render();
		mHeart.X(330);
		mHeart.Render();
	}
	if (mHp == 7)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
		mHeart.X(280);
		mHeart.Render();
		mHeart.X(330);
		mHeart.Render();
	}
	if (mHp == 6)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
		mHeart.X(280);
		mHeart.Render();
	}
	if (mHp == 5)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
		mHeart.X(230);
		mHeart.Render();
	}
	if (mHp == 4)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
		mHeart.X(180);
		mHeart.Render();
	}
	if (mHp == 3)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
		mHeart.X(130);
		mHeart.Render();
	}
	if (mHp == 2)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
		mHeart.X(80);
		mHeart.Render();
	}
	if (mHp == 1)
	{
		mHeart.Set(30, 770, 24, 24);
		mHeart.Render();
	}
	//スタミナゲージ
	if (mStaminagage == 100)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
		mStamina.X(290);
		mStamina.Render();
		mStamina.X(308);
		mStamina.Render();
		mStamina.X(326);
		mStamina.Render();
		mStamina.X(344);
		mStamina.Render();
		mStamina.X(362);
		mStamina.Render();
		mStamina.X(380);
		mStamina.Render();
	}
	if (96 <= mStaminagage && mStaminagage <= 99)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
		mStamina.X(290);
		mStamina.Render();
		mStamina.X(308);
		mStamina.Render();
		mStamina.X(326);
		mStamina.Render();
		mStamina.X(344);
		mStamina.Render();
		mStamina.X(362);
		mStamina.Render();
	}
	if (91 <= mStaminagage && mStaminagage <= 95)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
		mStamina.X(290);
		mStamina.Render();
		mStamina.X(308);
		mStamina.Render();
		mStamina.X(326);
		mStamina.Render();
		mStamina.X(344);
		mStamina.Render();
	}
	if (86 <= mStaminagage && mStaminagage <= 90)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
		mStamina.X(290);
		mStamina.Render();
		mStamina.X(308);
		mStamina.Render();
		mStamina.X(326);
		mStamina.Render();
	}
	if (81 <= mStaminagage && mStaminagage <= 85)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
		mStamina.X(290);
		mStamina.Render();
		mStamina.X(308);
		mStamina.Render();
	}
	if (76 <= mStaminagage && mStaminagage <= 80)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
		mStamina.X(290);
		mStamina.Render();
	}
	if (71 <= mStaminagage && mStaminagage <= 75)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
		mStamina.X(272);
		mStamina.Render();
	}
	if (66 <= mStaminagage && mStaminagage <= 70)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
		mStamina.X(254);
		mStamina.Render();
	}
	if (61 <= mStaminagage && mStaminagage <= 65)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
		mStamina.X(236);
		mStamina.Render();
	}
	if (56 <= mStaminagage && mStaminagage <= 60)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
		mStamina.X(218);
		mStamina.Render();
	}
	if (51 <= mStaminagage && mStaminagage <= 55)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
		mStamina.X(200);
		mStamina.Render();
	}
	if (46 <= mStaminagage && mStaminagage <= 50)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
		mStamina.X(182);
		mStamina.Render();
	}
	if (41 <= mStaminagage && mStaminagage <= 45)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
	}
	if (36 <= mStaminagage && mStaminagage <= 40)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
		mStamina.X(164);
		mStamina.Render();
	}
	if (31 <= mStaminagage && mStaminagage <= 35)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
		mStamina.X(146);
		mStamina.Render();
	}
	if (26 <= mStaminagage && mStaminagage <= 30)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
		mStamina.X(128);
		mStamina.Render();
	}
	if (21 <= mStaminagage && mStaminagage <= 25)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
		mStamina.X(110);
		mStamina.Render();
	}
	if (16 <= mStaminagage && mStaminagage <= 20)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
		mStamina.X(92);
		mStamina.Render();
	}
	if (11 <= mStaminagage && mStaminagage <= 15)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
		mStamina.X(74);
		mStamina.Render();
	}
	if (6 <= mStaminagage && mStaminagage <= 10)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
		mStamina.X(56);
		mStamina.Render();
	}
	if (1 <= mStaminagage && mStaminagage <= 5)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
		mStamina.Set(38, 701, 10, 18);
		mStamina.Render();
	}
	if (mStaminagage == 0)
	{
		mGage.Set(209, 700, 198, 30);
		mGage.Render();
	}
	//ボスHP
	if (CApplication::Bd() == 1)
	{
		if (CBoss::BEhp() == 1300)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(690, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(750, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(810, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(870, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(930, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(990, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 1200)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(690, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(750, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(810, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(870, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(930, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 1100)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(690, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(750, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(810, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(870, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 1000)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(690, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(750, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(810, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 900)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(690, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(750, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 800)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(690, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 700)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(630, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 600)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(570, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 500)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(510, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 400)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(450, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 300)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(390, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 200)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
			mBossHp.Set(330, 30, 30, 18);
			mBossHp.Render();
		}
		if (CBoss::BEhp() == 100)
		{
			mBossHpGage.Set(630, 30, 415, 30);
			mBossHpGage.Render();
			mBossHp.Set(270, 30, 30, 18);
			mBossHp.Render();
		}
		if (CApplication::Bd() == 1)
		{
			if (CBoss::BEhp() == 0)
			{
				mBossHpGage.Set(630, 30, 415, 30);
				mBossHpGage.Render();
			}
		}
	}
}
