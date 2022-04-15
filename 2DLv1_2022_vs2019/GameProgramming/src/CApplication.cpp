#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
//	mRectangle.Set(400.0f, 44.0f, 26.0f, 44.0f);
	mPlayer.Set(400.0f, 44.0f, 26.0f, 44.0f);
//	mRectangle.Texture(&mTexture, 740, 876, 1236, 1016);
	mPlayer.Texture(&mTexture, 740, 876, 1236, 1016);
	mTexture.Load("22302021.png");
	mEnemy.Set(26.0f, 574.0f, 44.0f, 26.0f);
	mEnemy.Texture(&mTexture, 1604, 1808, 680, 472);
	mBullet.Set(400.0f, 98.0f, 3.0f, 10.0f);
}

void CApplication::Update()
{
	mPlayer.Update();
	/*if (mInput.Key(VK_SPACE))
	{
		mBullet.Set(mRectangle.X(), mRectangle.Y() + mRectangle.H() + mBullet.H(), 3.0f, 10.0f);
	}
	if (mInput.Key('A'))
	{
		float x = mRectangle.X();
		x -= 4.0f;
		mRectangle.X(x);
	}
	if (mInput.Key('D'))
	{
		float x = mRectangle.X();
		x += 4.0f;
		mRectangle.X(x);
	}*/
	mBullet.Update();
	mEnemy.Update();
//	mRectangle.Render();
	mPlayer.Render();
	mEnemy.Render();
	mBullet.Render();
}

