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
