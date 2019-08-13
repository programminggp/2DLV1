#include "CSceneGame.h"
#include "CUI.h"
#include "CBlock.h"
#include "CBackGround.h"

std::vector<CCharacter*> CSceneGame::mCharacters;

CTexture TexBomberman;


//メソッド（プログラム）の定義

CSceneGame::CSceneGame() 
{
	TexBomberman.Load("Bomberman.tga");
	int map[11][13] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++) {
			int x = j * CHIPSIZE * 2 + CHIPSIZE;
			int y = (-i - 1) * CHIPSIZE * 2 + CHIPSIZE;
			switch (map[i][j]) {
			case 0:
			case 2:
				new CBackGround(x, y, CHIPSIZE, CHIPSIZE);
				break;
			case 1:
				new CBlock(x, y, CHIPSIZE, CHIPSIZE);
				break;
			}
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++) {
			int x = j * CHIPSIZE * 2 + CHIPSIZE;
			int y = (-i - 1) * CHIPSIZE * 2 + CHIPSIZE;
			if (map[i][j] == 2) {
				new CPlayer(x, y, CHIPSIZE, CHIPSIZE);
			}
		}
	}
	mCamera.Camera2D(400.0f, -300.0f, 400.0f, 300.0f);
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
