#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CKey.h"
#include "CMatrix.h"
#include "CTaskManager.h"
#include "CUtil.h"
//
#include "CCollisionManager.h"
//
#include "CCamera.h"


//モデルデータの指定
#define MODEL_X "res\\knight\\knight_low.X"

CMatrix Matrix;

CModelX ModelSample;

void CSceneGame::Init() {
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	Camera.Set(CVector(1.0f, 2.0f, 10.0f), CVector(), CVector(0.0f, 1.0f, 0.0f));
	ModelSample.Load(MODEL_X);
	//最初のアニメーションの現在時間を45にする
	ModelSample.mAnimationSet[0]->mTime = 45;
	//最初のアニメーションの重みを1.0（100%)にする
	ModelSample.mAnimationSet[0]->mWeight = 1.0f;
}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
	CTaskManager::Get()->TaskCollision();

	Camera.Render();

	//X軸＋回転
	if (CKey::Push('K')) {
		Matrix = Matrix * CMatrix().RotateX(1);
	}
	//Y軸＋回転
	if (CKey::Push('L')) {
		Matrix = Matrix * CMatrix().RotateY(1);
	}


	ModelSample.mAnimationSet[0]->mTime += 1.0f;
	ModelSample.mAnimationSet[0]->mTime =
		(int)ModelSample.mAnimationSet[0]->mTime %
		(int)(ModelSample.mAnimationSet[0]->mMaxTime + 1);
	//フレームの変換行列をアニメーションで更新する
	ModelSample.AnimateFrame();
	//フレームの合成行列を計算する
	ModelSample.mFrame[0]->AnimateCombined(&Matrix);

	//頂点にアニメーションを適用する
	ModelSample.AnimateVertex();
	ModelSample.Render();

	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//CTaskManager::Get()->Render();

#ifdef _DEBUG
	//コライダの描画
	//CCollisionManager::Get()->Render();
#endif

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();
}

