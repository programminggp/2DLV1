#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "Ckey.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//テキストフォントの読み込みと設定
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);

}


void CSceneGame::Update() {
	//最初のアニメーションの現在時間を45にする
	//CRes::sModelX.mAnimationSet[0]->mTime = 0;
	CRes::sModelX.mAnimationSet[0]->mTime += 1.0f;
	CRes::sModelX.mAnimationSet[0]->mTime =
		(int)CRes::sModelX.mAnimationSet[0]->mTime %
		(int)(CRes::sModelX.mAnimationSet[0]->mMaxTime + 1);

	//最初のアニメーションの重みを1.0（100%)にする
	CRes::sModelX.mAnimationSet[0]->mWeight = 1.0f;
	//フレームの変換行列をアニメーションで更新する
	CRes::sModelX.AnimateFrame();
	//フレームの合成行列を計算する
	CRes::sModelX.mFrame[0]->AnimateCombined(&Matrix);

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//X軸＋回転
	if (CKey::Push('K')) {
		Matrix = Matrix * CMatrix().RotateX(1);
	}
	if (CKey::Push('I')) {
		Matrix = Matrix * CMatrix().RotateX(-1);
	}
	//Y軸＋回転
	if (CKey::Push('L')) {
		Matrix = Matrix * CMatrix().RotateY(1);
	}
	if (CKey::Push('J')) {
		Matrix = Matrix * CMatrix().RotateY(-1);
	}

	//行列設定
	glMultMatrixf(Matrix.mF);
	//頂点にアニメーションを適用する
	CRes::sModelX.AnimateVertex();
	//モデル描画
	CRes::sModelX.Render();

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

	return;
}

