#include "CApplication.h"
#include "CRectangle.h"

//ƒNƒ‰ƒX‚Ìstatic•Ï”
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	mFont.Load("FontWhite.png", 1, 64);
	mState = EState::EPLAY;
	mGame.Start();

	/*mpEnemy = new CEnemy(26.0f, 500.0f, 44.0f, 26.0f, 1604, 1808, 680, 472, &mTexture);
	mCharacterManager.Add(mpEnemy);
	mpEnemy = new CEnemy(26.0f, 426.0f, 44.0f, 26.0f, 1604, 1808, 680, 472, &mTexture);
	mCharacterManager.Add(mpEnemy);
	mpPlayer = new CPlayer();
	mpEnemy = new CEnemy(26.0f, 574.0f, 44.0f, 26.0f, 1604, 1808, 680, 472, &mTexture);
	mpMiss = new CMiss();
	mpPlayer->Set(400.0f, 44.0f, 26.0f, 44.0f);
	mpPlayer->Texture(&mTexture, 740, 876, 1236, 1016);
	mpMiss->Set(400.0f, 630.0f, 400.0f, 10.0f);
	mCharacterManager.Add(mpPlayer);
	mCharacterManager.Add(mpEnemy);
	mCharacterManager.Add(mpMiss);*/
}

void CApplication::Update()
{

	switch (mState)
	{
	case EState::EPLAY:

		mGame.Update();

		//mCharacterManager.Update();
		//mCharacterManager.Collision();
		//mCharacterManager.Delete();
		//mCharacterManager.Render();

		break;
	case EState::ECLEAR:

		mCharacterManager.Render();

		mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, "HIT");
		mFont.Draw(370.0f, 240.0f, 15.0f, 30.0f, "PUSH");
		mFont.Draw(370.0f, 180.0f, 15.0f, 30.0f, "ENTER");
		if (mInput.Key(VK_RETURN))
		{
			mState = EState::ESTART;
		}
		break;
	case EState::EOVER:

		mCharacterManager.Render();

		mFont.Draw(370.0f, 300.0f, 15.0f, 30.0f, "MISS");
		mFont.Draw(370.0f, 240.0f, 15.0f, 30.0f, "PUSH");
		mFont.Draw(370.0f, 180.0f, 15.0f, 30.0f, "ENTER");
		if (mInput.Key(VK_RETURN))
		{
			mState = EState::ESTART;
		}
		break;
	default:
		mState = EState::EPLAY;
		break;
	}
}
