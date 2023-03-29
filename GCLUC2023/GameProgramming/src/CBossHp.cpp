#include "CBossHp.h"
#include "CApplication.h"

CBossHp::CBossHp(float x, float y, float w, float h, CTexture* pt)
	: mLeft(4)
	, mRight(42)
	, mBottom(32)
	, mTop(4)
{
	Set(x, y, w, h);
	mpTexture = pt;
}

void CBossHp::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop);
}