#include "CRectangle.h"
#include <stdio.h>
#include "glut.h"


CRectangle::CRectangle()
{
	printf("インスタンスが生まれました\n");
	//glBegin(GL_QUADS);
	//glVertex2f(0.0f, 0.0f);
	//glVertex2f(400.0f, 0.0f);
	//glVertex2f(400.0f, 300.0f);
	//glVertex2f(0.0f, 300.0f);
	//glEnd();
}

void CRectangle::Render()
{
	Render(mX, mY, mW, mH);
}

CRectangle::~CRectangle()
{
	printf("インスタンスが破棄されました\n");
	//glBegin(GL_QUADS);
	//glVertex2f(400.0f, 300.0f);
	//glVertex2f(800.0f, 300.0f);
	//glVertex2f(800.0f, 600.0f);
	//glVertex2f(400.0f, 600.0f);
	//glEnd();
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
	if (mX < r->mX)
		*ax = r->mX - mX - mW - r->mW;
	else
		*ax = mX - r->mX - mW - r->mW;
	//0以上は衝突しない
	if (*ax >= 0.0f)
		return false;

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
		//上の時
		if (mY > r->mY)
			*ay = -*ay;
	}
	else
	{//X修正、Yは0
		*ay = 0.0f;
		//右の時
		if (mX > r->mX)
			*ax = -*ax;
	}
	return true;
}
