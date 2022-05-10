#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
	mPlayer.Set(400.0f, 44.0f, 26.0f, 44.0f);
	mPlayer.Texture(&mTexture, 740, 876, 1236, 1016);
	mTexture.Load("22302021.png");
	mEnemy.Set(26.0f, 574.0f, 44.0f, 26.0f);
	mEnemy.Texture(&mTexture, 1604, 1808, 680, 472);
	mEnemy2.Set(26.0f, 500.0f, 44.0f, 26.0f);
	mEnemy2.Texture(&mTexture, 1604, 1808, 680, 472);
//	mBullet.Set(400.0f, -98.0f, 3.0f, 10.0f);
	mFont.Load("FontWhite.png", 1, 64);
	mMiss.Set(400.0f, 630.0f, 400.0f, 10.0f);
	mState = EState::EPLAY;
	mCharacterManager.Add(&mPlayer);
	mCharacterManager.Add(&mEnemy);
	mCharacterManager.Add(&mEnemy2);
	mCharacterManager.Add(&mMiss);
	//mCharacters.push_back(&mPlayer);
	//mCharacters.push_back(&mEnemy);
	//mCharacters.push_back(&mEnemy2);
	//mCharacters.push_back(&mMiss);
//	std::_Erase_remove(mCharacters, mCharacters[1]);
//	std::_Erase_remove(mCharacters, &mEnemy);
}

void CApplication::Update()
{
	switch (mState)
	{
	case EState::EPLAY:
		if (mInput.Key(VK_SPACE))
		{
			CBullet* pBullet = new CBullet();
			pBullet->Set(mPlayer.X(), mPlayer.Y() + mPlayer.H() + 10.0f, 3.0f, 10.0f);
			pBullet->Move();
			mCharacterManager.Add(pBullet);
		}
		mCharacterManager.Update();
		mCharacterManager.Collision();
		mCharacterManager.Render();
		mCharacterManager.Delete();
		//for (size_t i = 0; i < mCharacters.size(); i++)
		//{
		//	mCharacters[i]->Update();
		//}
		//for (size_t i = 0; i < mCharacters.size(); i++)
		//{
		//	mCharacters[i]->Render();
		//}
		//for (size_t i = 0; i < mCharacters.size(); i++)
		//{
		//	if (mCharacters[i]->Tag() == CCharacter::ETag::EBULLET)
		//	{
		//		for (size_t j = 0; j < mCharacters.size(); j++)
		//		{
		//			if (mCharacters[i]->Collision(mCharacters[i], mCharacters[j]))
		//			{
		//				mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, 'H');
		//				mFont.Draw(400.0f, 300.0f, 15.0f, 30.0f, 'I');
		//				mFont.Draw(430.0f, 300.0f, 15.0f, 30.0f, 'T');
		//			}
		//		}
		//	}
		//}
		//for (size_t i = 0; i < mCharacters.size(); i++)
		//{
		//	if (mCharacters[i]->Tag() == CCharacter::ETag::EBULLET)
		//	{
		//		for (size_t j = 0; j < mCharacters.size(); j++)
		//		{
		//			if (mCharacters[i]->Collision(mCharacters[i], mCharacters[j]))
		//			{
		//				mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, 'H');
		//				mFont.Draw(400.0f, 300.0f, 15.0f, 30.0f, 'I');
		//				mFont.Draw(430.0f, 300.0f, 15.0f, 30.0f, 'T');
		//			}
		//		}
		//	}
		//}
		//{
		//	//イテレータの生成
		//	std::vector<CCharacter*>::iterator itr;
		//	//イテレータを先頭
		//	itr = mCharacters.begin();
		//	//最後まで繰り返し
		//	while (itr != mCharacters.end()) {
		//		if ((*itr)->Enabled()) {
		//			//次へ
		//			itr++;
		//		}
		//		else {
		//			//falseのインスタンスを削除
		//			delete* itr;
		//			//リストからも削除
		//			itr = mCharacters.erase(itr);
		//		}
		//	}
		//}

		//for (size_t i = 0; i < mCharacters.size(); i++)
		//{
		//	if (mCharacters[i]->Enabled() == false)
		//	{
		//		delete mCharacters[i];
		//		std::_Erase_remove(mCharacters, mCharacters[i]);
		//	}
		//}
//		mEnemy.Collision(&mBullet);
		//if (mBullet.Collision(&mEnemy))
		//{
		//	mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, 'H');
		//	mFont.Draw(400.0f, 300.0f, 15.0f, 30.0f, 'I');
		//	mFont.Draw(430.0f, 300.0f, 15.0f, 30.0f, 'T');
		//	mFont.Draw(370.0f, 240.0f, 15.0f, 30.0f, "PUSH");
		//	mFont.Draw(370.0f, 180.0f, 15.0f, 30.0f, "ENTER");
		//	mState = EState::ECLEAR;
		//}
		//if (mBullet.Collision(&mMiss))
		//{
		//	mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, "MISS");
		//	mState = EState::EOVER;
		//}
		break;
	case EState::ECLEAR:
		for (size_t i = 0; i < mCharacters.size(); i++)
		{
			mCharacters[i]->Render();
		}
		mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, "HIT");
		mFont.Draw(370.0f, 240.0f, 15.0f, 30.0f, "PUSH");
		mFont.Draw(370.0f, 180.0f, 15.0f, 30.0f, "ENTER");
		if (mInput.Key(VK_RETURN))
		{
			mState = EState::ESTART;
		}
		break;
	case EState::EOVER:
		for (size_t i = 0; i < mCharacters.size(); i++)
		{
			mCharacters[i]->Render();
		}
		mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, "MISS");
		mFont.Draw(370.0f, 240.0f, 15.0f, 30.0f, "PUSH");
		mFont.Draw(370.0f, 180.0f, 15.0f, 30.0f, "ENTER");
		if (mInput.Key(VK_RETURN))
		{
			mState = EState::ESTART;
		}
		break;
	default:
		mPlayer.Set(400.0f, 44.0f, 26.0f, 44.0f);
		mPlayer.Texture(&mTexture, 740, 876, 1236, 1016);
		mEnemy.Set(26.0f, 574.0f, 44.0f, 26.0f);
		mEnemy.Texture(&mTexture, 1604, 1808, 680, 472);
//		mBullet.Set(400.0f, -98.0f, 3.0f, 10.0f);
		mState = EState::EPLAY;	
		mEnemy.Move();
		break;
	}
}

