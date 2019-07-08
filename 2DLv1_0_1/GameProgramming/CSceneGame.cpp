#include "CSceneGame.h"
#include "CUI.h"
#include "CShootBoss.h"
#include "CEnemyShot.h"
#include "CEffect.h"

//テクスチャの変数を作成
CTexture TexPlayer;	//プレイヤー
CTexture TexEnemy;	//敵
CTexture TexShot;	//ショット
CTexture TexBackGround;	//背景
CTexture TexExplosion;	//爆発
CTexture TexBoss;	//ボス

/*
デフォルトコンストラクタ
インスタンスの初期処理
*/
CSceneGame::CSceneGame() 
{
	//カメラの設定
	mCamera.Camera2D(400.0f, 300.0f, 400.0f, 300.0f);
	//テクスチャの読み込み
	TexBackGround.Load("BackGround.tga");	//背景
	TexShot.Load("Shoot.tga");	//ショット
	TexEnemy.Load("Enemy.tga");	//敵
	TexPlayer.Load("Player.tga");	//プレイヤー
	TexExplosion.Load("Explosion.tga");	//爆発
	TexBoss.Load("Boss.tga");	//ボス

	//オブジェクトの配置とテクスチャの設定
	//背景
	mBackGround.Set(400, 300, 640, 512);
	mBackGround.mpTexture = &TexBackGround;
	//プレイヤー
	mPlayer.Set(400, 100, 32, 32);
	mPlayer.mpTexture = &TexPlayer;
	mPlayer.mEffect.mpTexture = &TexExplosion;
	//敵
	mEnemy.Set(500, 300, 24, 36);
	mEnemy.mpTexture = &TexEnemy;
	mEnemy.mEffect.mpTexture = &TexExplosion;
	//ボス
	mBoss.Set(300, 450, 80, 120);
	mBoss.mpTexture = &TexBoss;
	mBoss.mEffect.mpTexture = &TexExplosion;
	//ショット
	for (int i = 0; i < 5; i++) {
		CPlayerShot::mShot[i].mpTexture = &TexShot;
		CEnemyShot::mShot[i].mpTexture = &TexShot;
	}
}

/*
Updateメソッド
1フレームの更新処理を行う
*/
void CSceneGame::Update() {
	//更新処理
	mPlayer.Update();
	mEnemy.Update();
	mBoss.Update();
	for (int i = 0; i < 5; i++) {
		CPlayerShot::mShot[i].Update();
		CEnemyShot::mShot[i].Update();
	}
	//衝突処理
	mPlayer.Collision(&mPlayer, &mEnemy);
	for (int i = 0; i < 5; i++) {
		mPlayer.Collision(&mPlayer, &CEnemyShot::mShot[i]);
		mEnemy.Collision(&mEnemy, &CPlayerShot::mShot[i]);
		mBoss.Collision(&mBoss, &CPlayerShot::mShot[i]);
	}
}

/*
Renderメソッド
1フレームの描画を行う
*/
void CSceneGame::Render() {
	//カメラ設定
	mCamera.Camera2D();
	//描画処理
	mBackGround.Render();
	mPlayer.Render();
	mEnemy.Render();
	mBoss.Render();
	for (int i = 0; i < 5; i++) {
		CPlayerShot::mShot[i].Render();
		CEnemyShot::mShot[i].Render();
	}
}
