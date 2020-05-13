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
	//4
	mPlayer.mpModel = &mRover;
	//07
	new CRock(&mRock, CVector(-20.0f, 0.0f, 10.0f), CVector());
	new CRock(&mRock, CVector(10.0f, 0.0f, 20.0f), CVector());
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
	e = CVector(-2.0f, 10.0f, -30.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

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

	//2D描画開始
	Start2D(0, 800, 0, 600);

	CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D描画終了
	End2D();

	return;
}

