#include "CSceneGame.h"
#include "CUI.h"
#include "CEnemy.h"
#include "CShootBoss.h"

std::vector<CCharacter*> CSceneGame::mCharacters;

//メソッド（プログラム）の定義
CTexture TexPlayer;
CTexture TexEnemy;
CTexture TexShoot;
CTexture TexBackGround;
CTexture TexExplosion;


CSceneGame::CSceneGame() 
{
	TexBackGround.Load("BackGround.tga");
	TexShoot.Load("Shoot.tga");
	TexEnemy.Load("Enemy.tga");
	TexPlayer.Load("Player.tga");
	TexExplosion.Load("BossExplosion.tga");

	int enemyPos[][2] = {
		{ -300, 300 },
		{ -150, 300 },
		{ 0, 300 },
		{ 150, 300 },
		{ 300, 300 },

		{ -250, 200 },
		{ -100, 200 },
//		{ -50, 200 },
//		{ 50, 200 },
		{ 100, 200 },
		{ 250, 200 },
	};
	mBackGround.Set(400, 300, 640, 512);
	mPlayer.Set(400, 100, 32, 32);
	for (int i = 0; i < 10; i++) {
		mEnemy[i].Set(enemyPos[i][0] + 400, enemyPos[i][1] + 300, 24, 36);
	}
}

CSceneGame::~CSceneGame() {
	//無効なキャラ削除
	std::vector<CCharacter*>::iterator itr = mCharacters.begin();
	while (itr != mCharacters.end()) {
		delete *itr;
		itr = mCharacters.erase(itr);
	}
}


void CSceneGame::Init() {
	mFrame = 0;
	CUI::mFont.Set("Font.tga", 1, 64, 16, 33);
}

void CSceneGame::Update() {
	//更新処理
	mPlayer.Update();
	for (int i = 0; i < 10; i++) {
		mEnemy[i].Update();
	}
	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Update();
	}
	//衝突処理
	for (int i = 0; i < mCharacters.size(); i++) {
		mPlayer.Collision(&mPlayer, mCharacters[i]);
		mCharacters[i]->Collision(mCharacters[i], &mPlayer);
		for (int j = 0; j < 10; j++) {
			mEnemy[j].Collision(&mEnemy[j], mCharacters[i]);
			mCharacters[i]->Collision(mCharacters[i], &mEnemy[j]);
		}
		for (int j = i + 1; j < mCharacters.size(); j++) {
			mCharacters[i]->Collision(mCharacters[i], mCharacters[j]);
			mCharacters[j]->Collision(mCharacters[j], mCharacters[i]);
		}
	}
	//無効なキャラ削除
	std::vector<CCharacter*>::iterator itr = mCharacters.begin();
	while ( itr != mCharacters.end() ) {
		if ((*itr)->mState == CCharacter::EENABLED) {
			itr++;
		}
		else {
			delete *itr;
			itr = mCharacters.erase(itr);
		}
	}
}

void CSceneGame::Render() {
	mCamera.Camera2D(400.0f, 300.0f, 400.0f, 300.0f);
	//描画処理
	mBackGround.Render();
	mPlayer.Render();
	for (int i = 0; i < 10; i++) {
		mEnemy[i].Render();
	}
	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Render();
	}

	CUI::Render();
}
