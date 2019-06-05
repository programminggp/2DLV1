#include "CSceneGame.h"
#include "CUI.h"
#include "CEnemy.h"
#include "CShootBoss.h"
#include "CTextureManager.h"

std::vector<CCharacter*> CSceneGame::mCharacters;

//メソッド（プログラム）の定義

CSceneGame::CSceneGame() 
{
	CTextureManager::Load();
	mBackGround.Set(0, 0, 1280, 1024);
	mPlayer.Set(0, -200, 64, 64);
	for (int i = 0; i < 10; i++) {
		mEnemy[i].Set(i * 60 - 350, 250, 48, 72);
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
	//mFrame++;
	//mFrame %= 40;
	//if (mFrame == 0) {
	//	CEnemy *e = new CEnemy();
	//	e->SetPosition(-400, 250);
	//	e->SetSize(48, 72);
	//}
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
		if ((*itr)->mEnabled) {
			itr++;
		}
		else {
			delete *itr;
			itr = mCharacters.erase(itr);
		}
	}
}

void CSceneGame::Render() {
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
