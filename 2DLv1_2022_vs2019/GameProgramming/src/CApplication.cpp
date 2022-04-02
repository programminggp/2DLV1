#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
	mRectangle.Set(400.0f, 44.0f, 26.0f, 44.0f);
	mTexture.Load("22302021.png");
}

void CApplication::Update()
{
	mTexture.DrawImage(
		mRectangle.X() - mRectangle.W(),
		mRectangle.X() + mRectangle.W(),
		mRectangle.Y() - mRectangle.H(),
		mRectangle.Y() + mRectangle.H(),
		740, 876, 1236, 1016);
}

