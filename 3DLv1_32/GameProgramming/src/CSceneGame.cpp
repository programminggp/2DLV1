//シーンゲームクラスのインクルード
#include "CSceneGame.h"
//OpenGL
#include"glut.h"
//ベクトルクラスのインクルード
#include"CVector.h"
//三角形クラスのインクルード
#include"CTriangle.h"
//キークラスのインクルード
#include"CKey.h"
//マトリックスクラスのインクルード
#include"CMatrix.h"
//トランスフォームクラスのインクルード
#include"CTransform.h"
//キャラクタクラスのインクルード
#include"CCharacter.h"
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"
//敵のクラスのインクルード
#include"CEnemy.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"
//ビルボードクラスのインクルード
#include"CBillBoard.h"
//カメラクラスのインクルード
#include"CCamera.h"
//三角コライダクラスのインクルード
#include"CColliderTriangle.h"
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj","res\\f14.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"
//カメラの視点の変数
CVector mEye;

//マトリックスの変数
CMatrix matrix;

//三角コライダの作成1
CColliderTriangle mColliderTriangle;
//三角コライダの作成2
CColliderTriangle mColliderTriangle2;

void CSceneGame::Init() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//モデルファイルの入力
	mModel.Load(MODEL_OBJ);
	//背景モデルファイルの入力
	mBackGround.Load(MODEL_BACKGROUND);
	//敵のモデルの読み込み
	mModelC5.Load("res\\C5.obj","res\\C5.mtl");
	//マトリックスの描画変数
	matrix.Print();
	//プレイヤーのモデルポインタ
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f,0.0f));
	//敵機のインスタンス作成
	new CEnemy(&mModelC5,CVector(0.0f, 10.0f, -100.0f),
		CVector(),CVector(0.1f,0.1f,0.1f));
	new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	//ビルボードの生成
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//三角コライダの確認1
	mColliderTriangle.Set(NULL, NULL, CVector(-50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f));
	//三角コライダの確認2
	mColliderTriangle2.Set(NULL, NULL, CVector(50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f));
}

void CSceneGame::Update() {
	//タスクマネージャの更新
	CTaskManager::Get()->Update();
	//コリジョンマネージャの更新
	CCollisionManager::Get()->Collision();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点,注視点,上方向
	//視点を求める
	e = mPlayer.Position() + CVector(-0.2f,1.0f,-3.0f) * mPlayer.MatirixRotate();
	//注視点を求める
	c = mPlayer.Position();
	//上方向を求める
	u = CVector(0.0f,1.0f,0.0f) * mPlayer.MatirixRotate();
	//カメラの設定
	//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();
	
	

	
	
	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//タスクマネージャの描画	
	CTaskManager::Get()->Render();
	//背景モデルの描画
	mBackGround.Render(CMatrix());
	//コリジョンマネージャのコライダ描画
	CCollisionManager::Get()->Render();
}
	


