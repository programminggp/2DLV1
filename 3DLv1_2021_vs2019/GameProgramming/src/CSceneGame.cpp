#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CKey.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CBullet.h"
#include "CTaskManager.h"
//CEnemyクラスのインクルード
#include "CEnemy.h"
#include "CEnemy2.h"
//
#include "CCollisionManager.h"
//
#include "CBillBoard.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CTank.h"

//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//背景モデルデータの指定
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"

void CSceneGame::Init() {
	mText.LoadTexture("FontWhite.tga",1,64);

	mBackGroundMatrix.Translate(0.0f, 1.0f, -500.0f);

	//三角コライダの確認
//	mColliderTriangle.Set(NULL, NULL, CVector(-50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f));
//	mColliderTriangle2.Set(NULL, NULL, CVector(50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, 50.0f));

	//C5モデルの読み込み
	mModelC5.Load("res\\c5.obj", "res\\c5.mtl");

	mEye = CVector(1.0f, 2.0f, 3.0f);
	//モデルファイルの入力
	mModel.Load(MODEL_OBJ);
	mBackGround.Load(MODEL_BACKGROUND);

	CMatrix matrix;
	matrix.Print();

	//

	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	//
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f) * mBackGroundMatrix);
	//mPlayer.mPosition = CVector(0.0f, 0.0f, -503.0f);
	mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));

	//敵機のインスタンス作成
	new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -600.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -630.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

//	new CEnemy2(CVector(-15.0f, 15.0f, -90.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
//	new CEnemy2(CVector(15.0f, 15.0f, -150.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy2(CVector(-5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy2(CVector(5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	//ビルボードの生成
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//背景モデルから三角コライダを生成
	//親インスタンスと行列はなし
	//mColliderMesh.Set(NULL, NULL, &mBackGround);
	//mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);
	CColliderTriangle::Mesh(nullptr, &mBackGroundMatrix, &mBackGround);

	//戦車の生成
	mpTank = new CTank(CVector(0.0f, -1.0f, -5.0f) * mBackGroundMatrix, CVector(), CVector(0.2f, 0.2f, 0.2f));
}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
//削除	CCollisionManager::Get()->Collision();
	CTaskManager::Get()->TaskCollision();

	if (CKey::Push('L'))
	{
//		mEye.mX += 0.1f;
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	if (CKey::Push('J'))
	{
//		mEye.mX -= 0.1f;
		mEye = mEye + CVector(-0.1f, 0.0f, 0.0f);
	}
	if (CKey::Push('I'))
	{
//		mEye.mZ -= 0.1f;
		mEye = mEye + CVector(0.0f, 0.0f, -0.1f);
	}
	if (CKey::Push('K'))
	{
//		mEye.mZ += 0.1f;
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}
	if (CKey::Push('O'))
	{
//		mEye.mY += 0.1f;
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}
	if (CKey::Push('M'))
	{
//		mEye.mY -= 0.1f;
		mEye = mEye + CVector(0.0f, -0.1f, 0.0f);
	}

	//視点の設定
	//gluLookAt(視点X, 視点Y, 視点Z, 中心X, 中心Y, 中心Z, 上向X, 上向Y, 上向Z)
	//gluLookAt(mEye.X(), mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

//	mPlayer.Update();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	if (CKey::Push(VK_RIGHT))
	{
//		Camera.mRotation.mY += 2.0f;
		Camera.mRotation = Camera.mRotation + CVector(0.0f, 2.0f, 0.0f);
	}
	if (CKey::Push(VK_LEFT))
	{
//		Camera.mRotation.mY -= 2.0f;
		Camera.mRotation = Camera.mRotation + CVector(0.0f, -2.0f, 0.0f);
	}
	//e = mPlayer.Position() + CVector(-0.2f, 1.0f, -3.0f) * mPlayer.MatrixRotate();
	e = mpTank->Position() + CVector(-0.2f, 1.0f, -1.5f) * mpTank->Tank()->MatrixRotate() * mpTank->MatrixRotate();
//	e = CVector(-2.0f, 10.0f, -30.0f) * CMatrix().RotateY(Camera.mRotation.Y()) * mPlayer.Matrix();
	//注視点を求める
//	c = mPlayer.Position();
	c = CVector(-0.2f, 0.0f, 3.0f) * 5.0f * mpTank->Tank()->Matrix();
	//上方向を求める
//	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.MatrixRotate();
	u = CVector(0.0f, 1.0f, 0.0f) * mpTank->MatrixRotate();
	//カメラの設定
	
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//カメラクラスの設定
	Camera.Set(e, c, u);
	//Camera.Render();
	//	mPlayer.Render();

	mBackGround.Render(mBackGroundMatrix);

//	mPlayer.bullet.Update();
//	mPlayer.bullet.Render();

	//タスクリストの削除
	CTaskManager::Get()->Delete();
	CTaskManager::Get()->Render();

#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif
	if (CEnemy::sCount == 0)
	{
		//2Dの描画開始
		CUtil::Start2D(-400, 400, -300, 300);
		//描画色の設定（緑色の半透明）
		glColor4f(239.0f / 256.0f, 175.0f / 256.0f, 0.0f, 1.0f);

		//文字列の描画
		mText.DrawString("MISSION CLEAR", -200, 100, 16, 32);

		//2Dの描画終了
		CUtil::End2D();
	}

}

