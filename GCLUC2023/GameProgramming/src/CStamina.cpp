#include "CStamina.h"
#include "CApplication.h"

void CStamina::Update()
{
}

CStamina::CStamina(float x, float y, float w, float h, CTexture* pt)
	: mLeft(20)
	, mRight(29)
	, mBottom(39)
	, mTop(11)
{
	Set(x, y, w, h);
	mpTexture = pt;
}

void CStamina::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop);
}