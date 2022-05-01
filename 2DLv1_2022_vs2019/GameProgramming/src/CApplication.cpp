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
	mBullet.Set(400.0f, -98.0f, 3.0f, 10.0f);
	mFont.Load("FontWhite.png", 1, 64);
	mMiss.Set(400.0f, 630.0f, 400.0f, 10.0f);
}

void CApplication::Update()
{
	if (mInput.Key(VK_SPACE))
	{
		mBullet.Set(mPlayer.X(), mPlayer.Y() + mPlayer.H() + mBullet.H(), 3.0f, 10.0f);
		mBullet.Move();
	}
	mPlayer.Update();
	mBullet.Update();
	mEnemy.Update();
	mPlayer.Render();
	mEnemy.Render();
	mBullet.Render();
	mEnemy.Collision(&mBullet);
	if (mBullet.Collision(&mEnemy))
	{
		mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, 'H');
		mFont.Draw(400.0f, 300.0f, 15.0f, 30.0f, 'I');
		mFont.Draw(430.0f, 300.0f, 15.0f, 30.0f, 'T');
		mFont.Draw(370.0f, 240.0f, 15.0f, 30.0f, "PUSH");
		mFont.Draw(370.0f, 180.0f, 15.0f, 30.0f, "ENTER");
	}
	if (mBullet.Collision(&mMiss))
	{
		mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, "MISS");
	}
	//if (mEnemy.Collision(&mBullet))
	//{
	//	//”š”­‚Ì‰æ‘œ
	//	mEnemy.Texture(&mTexture, 1946, 2172, 920, 664);
	//}
	//else
	//{
	//	mEnemy.Texture(&mTexture, 1604, 1808, 680, 472);
	//}
}

