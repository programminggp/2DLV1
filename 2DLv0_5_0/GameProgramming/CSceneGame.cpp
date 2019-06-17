#include "CSceneGame.h"
#include "CUI.h"
#include "CEnemy.h"
#include "CShootBoss.h"
#include "CTextureManager.h"
#include "CGround.h"

std::vector<CCharacter*> CSceneGame::mCharacters;

CTexture TexBG;
CTexture TexTile;
CTexture TexPlayer;

//メソッド（プログラム）の定義

CSceneGame::CSceneGame() 
{
	TexBG.Load("BG.tga");
	TexTile.Load("Tile.tga");
	TexPlayer.Load("Player2.tga");
	new CBackGround(0.0f, 0.0f, 800.0f, 600.0f);
	for (int i = -364; i < 472; i += 72) {
		new CGround( i, -264, 72.0f, 72.0f);
	}
	new CPlayer(0.0f, 0.0f, 72.0f, 72.0f);
}

CSceneGame::~CSceneGame() {
	//全てのキャラ削除
	std::vector<CCharacter*>::iterator itr = mCharacters.begin();
	while (itr != mCharacters.end()) {
		delete *itr;
		itr = mCharacters.erase(itr);
	}
}


void CSceneGame::Init() {
	CUI::mFont.Set("Font.tga", 1, 64, 16, 33);
}

void CSceneGame::Update() {
	//更新処理
	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Update();
	}
	//衝突処理
	for (int i = 0; i < mCharacters.size(); i++) {
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
	//描画処理
	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Render();
	}

	CUI::Render();
}
