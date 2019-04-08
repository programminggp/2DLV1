#include "CSceneGame.h"
#include "CUI.h"
#include "CEnemy.h"
#include "CTextureManager.h"

//メソッド（プログラム）の定義

void CSceneGame::Init() {
	mFrame = 0;
	mBoss.SetPosition(-300, 200);
	mBoss.SetSize(180, 240);
	mPlayer.SetPosition(0, -200);
	mPlayer.SetSize(64, 64);
	mBackGround.SetPosition(0, 0);
	mBackGround.SetSize(1280, 1024);
	CUI::mFont.Set("Font.tga", 1, 64, 16, 33);
	CTextureManager::mEnemy.Load("Enemy.tga");
//	CTextureManager::mPlayer.Load("Player.tga");
//	mPlayer.SetTexture(&CTextureManager::mPlayer);
	CTextureManager::mEffect.Load("BossExplosion.tga");
	CTextureManager::mEffect.SetParts(4, 5);
	CTextureManager::mShootPlayer.Load("ShootPlayer.tga");
}

void CSceneGame::Update() {
	mFrame++;
	mFrame %= 60;
	if (mFrame == 0) {
		new CEnemy();
	}
}

void CSceneGame::Render() {
	CUI::Render();
}
