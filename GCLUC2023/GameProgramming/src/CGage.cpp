#include "CGage.h"
#include "CApplication.h"

CGage::CGage(float x, float y, float w, float h, CTexture* pt)
	: mLeft(0)
	, mRight(164)
	, mBottom(50)
	, mTop(0)
{
	Set(x, y, w, h);
	mpTexture = pt;
}

void CGage::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop);
}