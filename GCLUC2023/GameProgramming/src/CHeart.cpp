#include "CHeart.h"
#include "CApplication.h"

#define Texture100 0,49,49,0

void CHeart::Update()
{
}

CHeart::CHeart(float x, float y, float w, float h, CTexture* pt)
	: mLeft(0)
	, mRight(50)
	, mBottom(50)
	, mTop(0)
{
	Set(x, y, w, h);
	mpTexture = pt;
}

void CHeart::Render()
{
	mpTexture->DrawImage(
		X() - W(),
		X() + W(),
		Y() - H(),
		Y() + H(),
		mLeft, mRight, mBottom, mTop);
}