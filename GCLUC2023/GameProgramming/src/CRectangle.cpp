#include "CRectangle.h"
#include <stdio.h>
#include "glut.h"

#define COLLISIONZ 75
//コンストラクタ
CRectangle::CRectangle()
	:mX(0.0f)
	,mY(0.0f)
	,mZ(0.0f)
	,mW(0.0f)
	,mH(0.0f)
	,maz(0.0f)
{
	printf("インスタンスが生まれました\n");
}

//デストラクタ
CRectangle::~CRectangle()
{
	printf("インスタンスが破棄されました\n");
}

bool CRectangle::Collision(CRectangle* r)
{
	float distX = mX - r->mX;
	if (distX < 0.0f)
		distX = -distX;
	if (distX >= mW + r->mW)
		return false;
	float distY = mY - r->mY;
	if (distY < 0.0f)
		distY = -distY;
	if (distY >= mH + r->mH)
		return false;
	return true;
}

bool CRectangle::Collision(CRectangle* r, float* ax, float* ay)
{
	//初期化
	*ax = 0;
	*ay = 0;

	//奥行当たり判定
	if (mZ > r->mZ)
		maz = mZ - r->mZ;
	if (r->mZ > mZ)
		maz = r->mZ - mZ;

	//mazを絶対値にする
	if (maz < 0.0f)
		maz = -maz;
	//定数と比較(mazが0～100の間ならCollision)
	if (0 < maz && maz <= COLLISIONZ)
	{
		//X軸当たり判定
		if (mX  < r->mX)
			*ax = r->mX - mX - mW - r->mW;
		else
			*ax = mX - r->mX - mW - r->mW;
		//0以上は衝突しない
		if (*ax >= 0.0f)
			return false;

		//Y軸当たり判定
		if (mY < r->mY)
			*ay = r->mY - mY - mH - r->mH;
		else
			*ay = mY - r->mY - mH - r->mH;
		//0以上は衝突しない
		if (*ay >= 0.0f)
			return false;

		//Yが短いか判定
		if (*ax < *ay)
		{//Y修正、Xは0
			*ax = 0.0f;
			//下の時
			*ay = *ay / 3;
			//上の時
			if (mY > r->mY)
				*ay = -*ay / 3;
			else if (mY < r->mY)
				*ay = *ay / 3;
		}
		else
		{//X修正、Yは0
			*ay = 0.0f;
			//左の時
			*ax = *ax / 2;
			//右の時
			if (mX > r->mX)
				*ax = -*ax / 2;
		}
		return true;
	}
	return false;
}


void CRectangle::Render()
{
	Render(mX, mY, mW, mH);
}

void CRectangle::Render(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
	glVertex2f(x - w, y - h);
	glVertex2f(x + w, y - h);
	glVertex2f(x + w, y + h);
	glVertex2f(x - w, y + h);
	glEnd();
}

void CRectangle::Set(float x, float y, float w, float h)
{
	mX = x;
	mY = y;
	mW = w;
	mH = h;
}

float CRectangle::X()
{
	return mX;
}

float CRectangle::Y()
{
	return mY;
}

float CRectangle::Z()
{
	mZ = mY - mH;
	return mZ;
}

float CRectangle::W()
{
	return mW;
}

float CRectangle::H()
{
	return mH;
}

void CRectangle::Y(float y)
{
	mY = y;
}

void CRectangle::X(float x)
{
	mX = x;
}