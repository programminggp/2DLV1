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
	mSky.Load("sky.obj", "sky.mtl");
	//3Dモデルファイルの読み込み
	CRes::sModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
	mPlayer.Init(&CRes::sModelX);
	//敵の初期設定
	mEnemy.Init(&CRes::sModelX);
	//敵の配置
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
	mEnemy.mScale = CVector(1.0f, 1.0f, 1.0f);

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
}


void CSceneGame::Update() {
	////歩くアニメーションに切り替える
	//if (mPlayer.mAnimationFrame >= mPlayer.mAnimationFrameSize) {
	//	mPlayer.ChangeAnimation(mPlayer.mAnimationIndex + 1, true, 60);
	//}

	//キャラクタークラスの更新
	mPlayer.Update();
	//敵の更新
	mEnemy.Update();
	//衝突処理
	CollisionManager.Collision();

//	//最初のアニメーションの現在時間を45にする
//	CRes::sModelX.mAnimationSet[0]->mTime += 1.0f;
//	CRes::sModelX.mAnimationSet[0]->mTime =
//		(int)CRes::sModelX.mAnimationSet[0]->mTime %
//		(int)(CRes::sModelX.mAnimationSet[0]->mMaxTime + 1);
////	CRes::sModelX.mAnimationSet[0]->mTime = 0;
//
//	//最初のアニメーションの重みを1.0（100%)にする
//	CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
//	//フレームの変換行列をアニメーションで更新する
//	CRes::sModelX.AnimateFrame();
//	//フレームの合成行列を計算する
//	CRes::sModelX.mFrame[0]->AnimateCombined(&CMatrix());
//
//
//	//頂点にアニメーションを適用する
//	CRes::sModelX.AnimateVertex();


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

	mSky.Render(CMatrix());

	//モデル描画
//	CRes::sModelX.Render();
	mPlayer.Render();
	//敵描画
	mEnemy.Render();
	//コライダの描画
	CollisionManager.Render();

	//テクスチャテスト
//	CRes::sModelX.mMaterial[0]->mpTexture->DrawImage(-5, 5, -5, 5, 0, 128, 128, 0);

	//2D描画開始
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D描画終了
	End2D();

	return;
}

