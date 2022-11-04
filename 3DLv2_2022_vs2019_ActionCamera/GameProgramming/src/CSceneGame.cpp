#include "CSceneGame.h"
#include "CModelX.h"
#include "CCollisionManager.h"

//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CActionCamera.h"
#include "CUtil.h"

#include "CKey.h"
#include "CXTest.h"

//確認用インスタンス
CModelX gModelX;
CMatrix gMatrix;

CModelX gKnight;

void CSceneGame::Init() {
	gKnight.Load("res\\knight\\knight_low.X");
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
	gKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
	gKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	gKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
	gKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン

	//3Dモデルファイルの読み込み
	gModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
	mPlayer.Init(&gModelX);

	mFont.LoadTexture("FontG.png", 1, 4096 / 64);
	//敵の初期設定
//	mEnemy.Init(&gModelX);
	mEnemy.Init(&gKnight);
	//敵の配置
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	mEnemy.ChangeAnimation(2, true, 200);

	new CXTest();
//	new CActionCamera(5.0f, -15.0f, 180.0f);
}

void CSceneGame::Update() {

	//更新
	CTaskManager::Get()->Update();
	CActionCamera::Instance()->Update();

	//衝突処理
	CCollisionManager::Get()->Collision();

	CActionCamera::Instance()->Render();
	CTaskManager::Get()->Render();

	//コライダの描画
	CCollisionManager::Get()->Render();

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();
}

