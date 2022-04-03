#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
	mRectangle.Set(400.0f, 44.0f, 26.0f, 44.0f);
	mRectangle.Texture(&mTexture, 740, 876, 1236, 1016);
	mTexture.Load("22302021.png");
	mCharacter.Set(26.0f, 574.0f, 44.0f, 26.0f);
	mCharacter.Texture(&mTexture, 1604, 1808, 680, 472);
	mBullet.Set(400.0f, 98.0f, 3.0f, 10.0f);
}

void CApplication::Update()
{
	mBullet.Update();
	mCharacter.Update();
	mRectangle.Render();
	mCharacter.Render();
	mBullet.Render();
}

