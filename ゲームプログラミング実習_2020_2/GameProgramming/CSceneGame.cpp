#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
//
#include "CRes.h"

#include "glut.h"
#include <Windows.h>
#include "CMaterial.h"
//
#include "CCollisionManager.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	//3Dモデルファイルの読み込み
	CRes::sKnight.Load("knight\\knight_low.x");
	//3Dモデルファイルの読み込み
	CRes::sModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
	mPlayer.Init(&CRes::sModelX);
	//敵の初期設定
//	mEnemy.Init(&CRes::sModelX);
	mEnemy.Init(&CRes::sKnight);
	//敵の配置
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
	mEnemy.mScale = CVector(1.0f, 1.0f, 1.0f);
	mEnemy.mAnimationFrameSize = 1024;

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
}


void CSceneGame::Update() {

	//キャラクタークラスの更新
	mPlayer.Update();
	//敵の更新
	mEnemy.Update();
	//衝突処理
	CollisionManager.Collision();

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//X軸＋回転
	if (GetKeyState('K') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateX(1);
	}
	//Y軸＋回転
	if (GetKeyState('L') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateY(1);
	}
	//X軸-回転
	if (GetKeyState('I') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateX(-1);
	}
	//Y軸-回転
	if (GetKeyState('J') & 0x8000) {
		Matrix = Matrix * CMatrix().RotateY(-1);
	}

	//行列設定
	glMultMatrixf(Matrix.mF);

	mPlayer.Render();
	//敵描画
	mEnemy.Render();
	//コライダの描画
	CollisionManager.Render();


	//2D描画開始
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D描画終了
	End2D();

	return;
}

