#include "CApplication.h"
#include "CRectangle.h"

CTexture CApplication::mTexture;

CApplication::CApplication()
	:mRb(0)
	, mMc(0)
	, mEs(0)
	, mNc(0)
{
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	mTexture.Load("PlayerImage.png");
	mTexture2.Load("背景(仮) .png");
	mTexture3.Load("タイトル画面 .png");
	mTexture4.Load("ゲームオーバー.png");
	mTexture5.Load("ゲームクリア.png");
	mTexture6.Load("背景.png");
	mTexture7.Load("背景2.png");
	mTexture8.Load("背景3.png");
	mTexture9.Load("アイテム.png");
	mTexture100.Load("プレイヤーHP.png");
	mTexture101.Load("MPゲージ.png");
	mTexture102.Load("プレイヤーMP.png");
	mFont.Load("FontWhite.png", 1, 64);
	mState = EState::ESTART;
	mpGame = new CGame();
}

void CApplication::Update()
{
	mMm--;
	mRb--;
	switch (mState)
	{
	case EState::ESTART:	//状態がスタート
		mpGame->Start();	//スタート画面表示
		if (mRb < 0)
		{
			if (mInput.Key(VK_RETURN))
			{	//状態をプレイ中にする
				mState = EState::ESTAGE1;
			}
		}
		break;
	case EState::ESTAGE1:
		mpGame->Stage1();
		mState = EState::EPLAY;
	break;
	case EState::ESTAGE2:
		mpGame->Stage2();
		mState = EState::EPLAY;
		break;
	case EState::EBOSS:
		mpGame->Boss();
		mState = EState::EPLAY;
		break;
	case EState::EPLAY:
		mpGame->Update();
		if (CPlayer::HP() <= 0)
		{
			mpGame->Over();
			mState = EState::EOVER;
		}
		if (CItem::Ih() == 1)
		{
			if (mMc == 1)
			{
				mMc = 2;
			}

		}
		if (mMc == 2)
		{
			CApplication::mMm = 300;
			CApplication::mMu = 0;
			mMc = 3;
			mEs = 2;
		}
		if (mEs == 2)
		{
			if (CApplication::mMm < 0)
			{
				mState = EState::EBOSS;
				mMc = 3;
				mNc = 2;
				mEs = 3;
			}
		}
		if (mMu == 1)
		{
			if (CGame::Num() == 0)
			{
				mSi = 1;
			}
		}
		if (CGame::Id() == 1)
		{
			mSi = 2;
		}
		if (CGame::Num() == 0)
		{
			if (mMc == 0)
			{
				CApplication::mMm = 400;
				mEs = 1;
				mMc = 1;
			}
			if (mEs == 1)
			{
				if (CApplication::mMm == 0)
				{
					CApplication::mMu = 1;

					mState = EState::ESTAGE2;
				}
			}

		}
		if (mBd == 1)
		{
			if (CBoss::BEhp() <= 0)
			{
				mState = EState::ECLEAR;
			}
		}
		if (mMc == 3)
		{
			if (CBoss::Num() == 1)
			{
				mBd = 1;
			}
		}
		break;

	case EState::EOVER:
		//ゲームオーバー処理
		mpGame->Over();
		//エンターキー入力時
		if (mInput.Key('N'))
		{	//ゲームのインスタンス削除
			delete mpGame;
			//ゲームのインスタンス生成
			mpGame = new CGame();
			//状態をスタートにする
			mState = EState::ESTART;
			mRb = 10;
			mMc = 0;
			mNc = 0;
			mEs = 0;
			mMu = 0;
			mBd = 0;
			mDi = 1;
		}
		else if (mInput.Key('Y'))
		{
			//ゲームのインスタンス削除
			delete mpGame;
			//ゲームのインスタンス生成
			mpGame = new CGame();
			//状態をスタートにする
			mState = EState::ESTAGE1;
			mRb = 10;
			mMc = 0;
			mNc = 0;
			mEs = 0;
			mMu = 0;
			mBd = 0;
			mDi = 1;
		}
		break;

	case EState::ECLEAR:
		//ゲームクリア処理
		mpGame->Clear();
		if (mInput.Key(VK_RETURN))
		{
			delete mpGame;
			mpGame = new CGame();
			mState = EState::ESTART;
			mRb = 10;
			mMc = 0;
			mNc = 0;
			mEs = 0;
			mMu = 0;
			mBd = 0;
			mDi = 1;
		}
		break;
	}
}
CTexture CApplication::mTexture2;
CTexture* CApplication::Texture2()
{
	return &mTexture2;
}
CTexture CApplication::mTexture3;
CTexture* CApplication::Texture3()
{
	return &mTexture3;
}
CTexture CApplication::mTexture4;
CTexture* CApplication::Texture4()
{
	return &mTexture4;
}
CTexture CApplication::mTexture5;
CTexture* CApplication::Texture5()
{
	return &mTexture5;
}
CTexture CApplication::mTexture6;
CTexture* CApplication::Texture6()
{
	return &mTexture6;
}
CTexture CApplication::mTexture7;
CTexture* CApplication::Texture7()
{
	return &mTexture7;
}
CTexture CApplication::mTexture8;
CTexture* CApplication::Texture8()
{
	return &mTexture8;
}
CTexture CApplication::mTexture9;
CTexture* CApplication::Texture9()
{
	return &mTexture9;
}
CTexture CApplication::mTexture100;
CTexture* CApplication::Texture100()
{
	return &mTexture100;
}
CTexture CApplication::mTexture101;
CTexture* CApplication::Texture101()
{
	return &mTexture101;
}
CTexture CApplication::mTexture102;
CTexture* CApplication::Texture102()
{
	return &mTexture102;
}
int CApplication::mMm = 0;
int CApplication::Mm()
{
	return mMm;
}
int CApplication::mMu = 0;
int CApplication::Mu()
{
	return mMu;
}
int CApplication::mSi = 0;
int CApplication::Si()
{
	return mSi;
}
int CApplication::mDi = 0;
int CApplication::Di()
{
	return mDi;
}
int CApplication::mBd = 0;
int CApplication::Bd()
{
	return mBd;
}
