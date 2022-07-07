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
	mState = EState::ESTART;
	mpGame = new CGame();
}

void CApplication::Update()
{
	switch (mState)
	{
	case EState::ESTART:
		mpGame->Start();
		if (mInput.Key(VK_RETURN))
		{
			mState = EState::EPLAY;
		}
		break;
	case EState::EPLAY:
		mpGame->Update();
		if (mpGame->IsOver())
		{
			mState = EState::EOVER;
		}
		if (mpGame->IsClear())
		{
			mState = EState::ECLEAR;
		}
		break;
	case EState::EOVER:
		mpGame->Over();
		if (mInput.Key(VK_RETURN))
		{
			delete mpGame;
			mpGame = new CGame();
			mState = EState::ESTART;
		}
		break;
	case EState::ECLEAR:
		mpGame->Clear();
		if (mInput.Key(VK_RETURN))
		{
			delete mpGame;
			mpGame = new CGame();
			mState = EState::ESTART;
		}
		break;
	}
}
