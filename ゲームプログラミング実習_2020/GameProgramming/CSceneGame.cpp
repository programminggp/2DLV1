#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"
//4
#include "CTaskManager.h"
//06
#include "CCollisionManager.h"
//07
#include "CRock.h"
//10
#include "CObj.h"

CSceneGame::~CSceneGame() {

}


void CSceneGame::Init() {
	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	//1
	mSky.Load("sky.obj", "sky.mtl");
	mRock.Load("Rock1.obj", "Rock1.mtl");
	mRover.Load("Rover1.obj", "Rover1.mtl");
	//10
	mCube.Load("cube.obj", "cube.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	//4
	mPlayer.mpModel = &mRover;
	//07
	//岩の生成　モデルmRock　位置|-20.0 0.0 20.0|
	//回転|0.0 0.0 0.0|　拡大|5.0 5.0 5.0|
	new CRock(&mRock, CVector(-20.0f, 0.0f, 20.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//岩の生成　モデルmRock　位置|20.0 0.0 40.0|
	//回転|0.0 0.0 0.0|　拡大|5.0 5.0 5.0|
	new CRock(&mRock, CVector(20.0f, 0.0f, 40.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//10
	new CObj(&mCube, CVector(0.0f, 0.0f, 60.0f), CVector(), CVector(10.0f, 10.0f, 1.0f));
	//12
	new CObj(&mPlane, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f));
}


void CSceneGame::Update() {
	//4
	TaskManager.Update();
	//06
	CollisionManager.Collision();
	//07
	TaskManager.Delete();


	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	//09
	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	//注視点を求める
	c = CVector() * mPlayer.mMatrix;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.mMatrixRotate;

	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);


	//1
	mSky.Render();
//	mRock.Render(CMatrix().Scale(5.0f, 5.0f, 5.0f));
//	mRover.Render(CMatrix().Translate(-20.0f, 0.0f, 10.0f));

	//4
	TaskManager.Render();
	//06
	CollisionManager.Render();

	////10
	//mCube.Render(CMatrix().Translate(15, 0, 0));
	//mCube.Render(CMatrix().Scale(100, 0.1, 100));
	//mSphere.Render(CMatrix().Translate(15, 10, 0));

	//2D描画開始
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D描画終了
	End2D();

	return;
}

