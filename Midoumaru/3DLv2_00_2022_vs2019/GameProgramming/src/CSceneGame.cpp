#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include"CMatrix.h"
#include "CUtil.h"
#include"CModelX.h"
#include"CKey.h"
#include"CXCharacter.h"
#include"CCollisionManager.h"
#include"CColliderMesh.h"
#include"CColliderTriangle.h"
#include"CTaskManager.h"
#include"CInput.h"
#include"CActionCamera.h"
#include"CBillBoard.h"

//#define MODEL_P_TURNR "res\\PaladinTurnRight.x"
//#define MODEL_P_TURNL "res\\PaladinTurnLeft.x"
//#define MODEL_P_ROLL1 "res\\PaladinRoll1.x"
//#define MODEL_P_ROLL2 "res\\PaladinRoll2.x"
//#define MODEL_P_SHIELD2 "res\\PaladinShield2.x"

CModelX Player;
CModelX Mutant;
CMatrix gMatrix;
CModelX gKnight;
CVector mEye;
CMatrix matrix;
CMatrix UndergroundMatrix;
CColliderMesh mColliderMesh;

CSceneGame::CSceneGame()
	: mActionCamera(6.0f, -15.0f, 180.0f)
	, mPlayer(0)
	, mMutant(0)
{
}

void CSceneGame::Init() {

	UndergroundMatrix.Translate(0.0f, 0.0f, -50.0f);
	UndergroundMatrix.Scale(7.0f, 7.0f, 7.0f);

	//3Dモデルファイルを読み込み
	Player.Load("res\\PaladinStand1.x");
	//アニメーションの追加
	Player.AddAnimationSet("res\\PaladinStand1.x");//1
	Player.AddAnimationSet("res\\PaladinStand2.x");//2
	Player.AddAnimationSet("res\\PaladinRun.x");//3
	Player.AddAnimationSet("res\\PaladinSlash1.x");//4
	Player.AddAnimationSet("res\\PaladinSlash2.x");//5
	Player.AddAnimationSet("res\\PaladinSlash3.x");//6
	Player.AddAnimationSet("res\\PaladinDeath.x");//7
	Player.AddAnimationSet("res\\PaladinBack.x");//8
	Player.AddAnimationSet("res\\PaladinShield1.x");//9
	Player.AddAnimationSet("res\\PaladinMagic1.x");//10
	Player.AddAnimationSet("res\\PaladinMagic2.x");//11
	Player.AddAnimationSet("res\\PaladinMagicStand.x");//12

	//Player.AddAnimationSet(MODEL_P_SHIELD2);
	//Player.AddAnimationSet(MODEL_P_ROLL1); //33
	//Player.AddAnimationSet(MODEL_P_ROLL2);
	//Player.AddAnimationSet(MODEL_P_TURNR); //23
	//Player.AddAnimationSet(MODEL_P_TURNL); //26

	Mutant.Load("res\\MutantStand.x");
	Mutant.AddAnimationSet("res\\MutantStand.x");//1
	Mutant.AddAnimationSet("res\\MutantRun.x");//2
	Mutant.AddAnimationSet("res\\MutantAttack.x");//3
	Mutant.AddAnimationSet("res\\MutantDeath.x");//4

	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	mPlayer = new CXPlayer();
	mPlayer->Init(&Player);
	mPlayer->Position(CVector(-38.0f, 1.5f, -45.0f));
	mPlayer->Scale(CVector(2.0f, 2.0f, 2.0f));

	mMutant = new CXMutant();
	mMutant->Init(&Mutant);
	mMutant->Position(CVector(-38.0f, 1.5f, -30.0f));
	mMutant->Rotation(CVector(1.0f, 200.0f, 0.0f));
	mMutant->Scale(CVector(2.1f, 2.1f, 2.1f));


    Underground.Load("res\\Underground.obj", "res\\Underground.mtl");
	//ビルボードの生成
//	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	new CBillBoard(CVector(-36.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	mColliderMesh.Set(nullptr, &UndergroundMatrix, &Underground);
	
	matrix.Print();
	//敵の初期設定
	//敵の配置
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	gKnight.Load("res\\knight\\knight_low.X");
	mEnemy.Init(&gKnight);
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
	mEnemy.ChangeAnimation(2, true, 200);

}

void CSceneGame::Update() {
	/*拡大縮小・回転など
	mTransform.Update();
	glMultMatrixf(mTransform.Matrix().M());*/
	/*歩くアニメーションに切り替える
	mCharacter.ChangeAnimation(1, false, 60);
	if (mCharacter.IsAnimationFinished() == true)
	{
		mCharacter.ChangeAnimation(mCharacter.AnimationIndex()+1,true, 60);
	}*/

	CTaskManager::Get()->Update();
	//キャラクタークラスの更新
	//mPlayer->Update();
	//敵の更新
	//mEnemy.Update();
	//ミュータントの更新
	//mMutant->Update();

	/*最初のアニメーションの現在時間を45にする
	gModelX.AnimationSet()[0]->Time(gModelX.AnimationSet()[0]->Time() + 1.0f);
	gModelX.AnimationSet()[0]->Time((int)gModelX.AnimationSet()[0]->Time() % (int)(gModelX.AnimationSet()[0]->MaxTime() + 1));
	最初のアニメーションの重みを1.0(100%)にする
	gModelX.AnimationSet()[0]->Weight(1.0f);
	フレームの変換行列をアニメーションで更新する
	gModelX.AnimateFrame();
	フレームの合成行列を計算する
	gModelX.Frames()[0]->AnimateCombined(&gMatrix);*/

	CActionCamera::Instance()->Position(mPlayer->Position() + (CVector(0.0f, 3.0f, 0.0f)));
	CActionCamera::Instance()->Update();
	CActionCamera::Instance()->Render();


	////X軸+回転
	//if (CKey::Push('K')) {
	//	gMatrix = gMatrix * CMatrix().RotateX(1);
	//}
	////Y軸+回転
	//if (CKey::Push('L')) {
	//	gMatrix = gMatrix * CMatrix().RotateY(1);
	//}
	////X軸-回転
	//if (CKey::Push('I')) {
	//	gMatrix = gMatrix * CMatrix().RotateX(-1);
	//}
	////Y軸-回転
	//if (CKey::Push('J')) {
	//	gMatrix = gMatrix * CMatrix().RotateY(-1);
	//}
	//行列設定
//	glMultMatrixf(gMatrix.M());

	//頂点にアニメーションを適用する
	//gModelX.AnimateVertex();
	//モデル描画
	//gModelX.Render();
	//gModelX Render
	// 
	//タスクリストの削除

	//タスクリストの削除
	CTaskManager::Get()->Delete();

	//背景描画
	Underground.Render(UndergroundMatrix);
	//プレイヤー描画
	//mPlayer->Render();
	//敵描画
	//mEnemy.Render();
	//タスクマネージャの描画	
	CTaskManager::Get()->Render();
	 
	
	//コライダ描画
	CCollisionManager::Get()->Render();

	//衝突処理
	CTaskManager::Get()->TaskCollision();

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();
}

