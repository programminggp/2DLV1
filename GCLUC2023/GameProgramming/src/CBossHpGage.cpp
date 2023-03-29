#include "CBossHpGage.h"
#include "CApplication.h"

CBossHpGage::CBossHpGage(float x, float y, float w, float h, CTexture* pt)
	: mLeft(0)
	, mRight(749)
	, mBottom(49)
	, mTop(0)
{
	Set(x, y, w, h);
	mpTexture = pt;
}

void CBossHpGage::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop);
}