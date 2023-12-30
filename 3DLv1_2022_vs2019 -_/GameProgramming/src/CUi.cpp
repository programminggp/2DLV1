#include <stdio.h>
#include "CUi.h"
#include "CCamera.h"

void CUi::Clear()
{
	mFont.Draw(36, 300, 18, 36, "GAME CLEAR!!");
	mFont.Draw(36, 200, 18, 36, "PUSH ENTER KEY!");
}

void CUi::Over()
{
	mFont.Draw(36, 300, 18, 36, "GAME OVER!!");
	mFont.Draw(36, 200, 18, 36, "PUSH ENTER KEY!");
}

void CUi::Start()
{
	mFont.Draw(36, 300, 18, 36, "START PUSH ENTER KEY!");
}

void CUi::Enemy(int enemy)
{
	mEnemy = enemy;
}

CUi::CUi()
	: mHp(0)
	, mTime(0)
	, mEnemy(0)
	, mPosY(0.0f)
	, mRotX(0.0f)
	, mRotY(0.0f)
{
	mFont.Load("FontWhite.png", 1, 64);
}

void CUi::Hp(int hp)
{
	mHp = hp;
}

void CUi::Time(int time)
{
	mTime = time;
}

void CUi::PosY(float f)
{
	mPosY = f;
}

void CUi::RotX(float f)
{
	mRotX = f;
}

void CUi::RotY(float f)
{
	mRotY = f;
}

void CUi::Render()
{
	//CCamera::Start(0, 800, 0, 600); //QD`ĉJn
	////`ĉFÌŬè
	//glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	////ĥñÒWGAÌìĴ
	//char buf[64];

	////YÀWÌ\Ĥ
	////ĥñÌŬè
	//sprintf(buf, "PY:%7.2f", mPosY);
	////ĥñÌ`ĉ
	//mFont.Draw(500, 330, 8, 16, buf);

	////X²ñ]lÌ\Ĥ
	////ĥñÌŬè
	//sprintf(buf, "RX:%7.2f", mRotX);
	////ĥñÌ`ĉ
	//mFont.Draw(500, 300, 8, 16, buf);

	////Y²ñ]lÌ\Ĥ
	////ĥñÌŬè
	//sprintf(buf, "RY:%7.2f", mRotY);
	////ĥñÌ`ĉ
	//mFont.Draw(500, 200, 8, 16, buf);
	CCamera::End(); //QD`ĉIı
}
