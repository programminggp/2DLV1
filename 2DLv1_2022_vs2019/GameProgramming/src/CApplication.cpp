#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
	mRectangle.Set(400.0f, 300.0f, 200.0f, 100.0f);
	mTexture.Load("22302021.png");
}

void CApplication::Update()
{
	mRectangle.Render();
//	mTexture.DrawImage(0.0f, 400.0f, 580.0f, 600.0f, 0, 300, 20, 0);
	mTexture.DrawImage(0.0f, 52.0f, 0.0f, 88.0f, 740, 876, 1236, 1016);
}

