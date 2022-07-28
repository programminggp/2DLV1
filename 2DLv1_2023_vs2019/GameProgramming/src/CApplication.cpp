#include "CApplication.h"
#include "CRectangle.h"

//クラスのstatic変数
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル

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
	//Sound
	mSoundBgm.Load(SOUND_BGM);
	mSoundOver.Load(SOUND_OVER);

	mFont.Load("FontWhite.png", 1, 64);
	mState = EState::ESTART;
	mpGame = new CGame();
}

void CApplication::Update()
{
	switch (mState)
	{
	case EState::ESTART:	//状態がスタート
		mpGame->Start();	//スタート画面表示
		//Enterキーが押されたら
		if (mInput.Key(VK_RETURN))
		{	//状態をプレイ中にする
			mState = EState::EPLAY;
			//BGMリピート再生
			mSoundBgm.Repeat();
		}
		break;
	case EState::EPLAY:
		mpGame->Update();
		//ゲームオーバーか判定
		if (mpGame->IsOver())
		{	//状態をゲームオーバーにする
			mState = EState::EOVER;
			//BGMストップ
			mSoundBgm.Stop();
			//ゲームオーバー
			mSoundOver.Play();
		}
		//ゲームクリアか判定
		if (mpGame->IsClear())
		{	//状態をゲームクリアにする
			mState = EState::ECLEAR;
		}
		break;
	case EState::EOVER:
		//ゲームオーバー処理
		mpGame->Over();
		//エンターキー入力時
		if (mInput.Key(VK_RETURN))
		{	//ゲームのインスタンス削除
			delete mpGame;
			//ゲームのインスタンス生成
			mpGame = new CGame();
			//状態をスタートにする
			mState = EState::ESTART;
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
		}
		break;
	}
}
