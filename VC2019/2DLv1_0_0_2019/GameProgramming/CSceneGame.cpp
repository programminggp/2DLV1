#include "CSceneGame.h"
#include "CUI.h"
#include "CShootBoss.h"
#include "CEnemyShot.h"
#include "CEffect.h"

//メソッド（プログラム）の定義
CTexture TexPlayer;
CTexture TexEnemy;
CTexture TexShot;
CTexture TexBackGround;
CTexture TexExplosion;
CTexture TexBoss;

CSceneGame::CSceneGame() 
{
	TexBackGround.Load("BackGround.tga");
	TexShot.Load("Shoot.tga");
	TexEnemy.Load("Enemy.tga");
//	TexPlayer.Load("Player.tga");
	TexPlayer.Load("4_fighters_sprites.tga");
	TexExplosion.Load("Explosion.tga");
	TexBoss.Load("Boss.tga");

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
	mBackGround.mpTexture = &TexBackGround;

	mPlayer.Set(400, 100, 32, 32);
	mPlayer.mpTexture = &TexPlayer;
	mPlayer.mEffect.mpTexture = &TexExplosion;

	mEnemy.Set(500, 300, 24, 36);
	mEnemy.mpTexture = &TexEnemy;
	mEnemy.mEffect.mpTexture = &TexExplosion;

	mBoss.Set(300, 450, 80, 120);
	mBoss.mpTexture = &TexBoss;

	for (int i = 0; i < 5; i++) {
		CPlayerShot::mShot[i].mpTexture = &TexShot;
		CEnemyShot::mShot[i].mpTexture = &TexShot;
	}

//	CUI::mFont.Set("Font.tga", 1, 64, 16, 33);
}

CSceneGame::~CSceneGame() {
}


void CSceneGame::Init() {
}

void CSceneGame::Update() {
	//更新処理
	mPlayer.Update();
	mEnemy.Update();
	mBoss.Update();
	for (int i = 0; i < 5; i++) {
		CPlayerShot::mShot[i].Update();
		CEnemyShot::mShot[i].Update();
//		CEffect::mEffect[i].Update();
	}

	mPlayer.Collision(&mPlayer, &mEnemy);
	for (int i = 0; i < 5; i++) {
		mPlayer.Collision(&mPlayer, &CEnemyShot::mShot[i]);
		mEnemy.Collision(&mEnemy, &CPlayerShot::mShot[i]);
	}

}

void CSceneGame::Render() {
	mCamera.Camera2D(400.0f, 300.0f, 400.0f, 300.0f);
	//描画処理
	mBackGround.Render();
	mPlayer.Render();
	mEnemy.Render();
	mBoss.Render();
	for (int i = 0; i < 5; i++) {
		CPlayerShot::mShot[i].Render();
		CEnemyShot::mShot[i].Render();
//		CEffect::mEffect[i].Render();
	}
	//	CUI::Render();
}
