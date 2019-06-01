#include "CSceneGame.h"
#include "CUI.h"
#include "CEnemy.h"
#include "CShootBoss.h"

//メソッド（プログラム）の定義

void CSceneGame::Init() {
	mFrame = 0;
	mBoss.SetXYWH(-300, 200, 179, 240);
	mPlayer.SetXYWH(0, -200, 64, 64);
	mBackGround.SetXYWH(0, 0, 1280, 1024);
	CUI::mFont.Set("Font.tga", 1, 64, 16, 33);
}

void CSceneGame::Update() {
	mFrame++;
	mFrame %= 60;
	if (mFrame == 0) {
		CEnemy *e = new CEnemy();
		e->SetPosition(0, 300);
		e->SetSize(48, 72);
	}
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Collision();
	CTaskManager::Get()->Remove();
}

void CSceneGame::Render() {
	CTaskManager::Get()->Render();
	CUI::Render();
}
