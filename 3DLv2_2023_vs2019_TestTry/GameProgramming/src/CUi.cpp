#include <stdio.h>
#include "CUi.h"
#include "CCamera.h"

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

void CUi::Render()
{
	CCamera::Start(0, 800, 0, 600);
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "PY:%7.2f", mPosY);
	//文字列の描画
	mFont.Draw(500, 330, 8, 16, buf);

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "RX:%7.2f", mRotX);
	//文字列の描画
	mFont.Draw(500, 300, 8, 16, buf);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "RY:%7.2f", mRotY);
	//文字列の描画
	mFont.Draw(500, 200, 8, 16, buf);
	CCamera::End();
}
