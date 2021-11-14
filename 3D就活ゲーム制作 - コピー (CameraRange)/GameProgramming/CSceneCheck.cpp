#include "glew.h"

#include "CSceneCheck.h"
//
#include "CCamera.h"
//
#include "CText.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
//
#include "CKey.h"
//
#include "CRoadManager.h"


//画面サイズは800x600を想定
#define SCREENSIZE_X 800
#define SCREENSIZE_Y 600
//描画エリアの指定(左端のX座標,下端のY座標,幅,高さ)
#define MINIMAP_AREA 590,10,200,150
#define BACKMIRROR_FRAME_AREA 286,491,229,154
#define BACKMIRROR_VIEW_AREA 288,493,225,150
#define BACKMIRROR_EXTRAFRAME_AREA 286,598,228,5

#define TEXWIDTH (800)
#define TEXHEIGHT (600)

#define OPENINGTIME 5*60

CSceneCheck::~CSceneCheck() {
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}


void CSceneCheck::Init() {

	//テキストフォントの読み込みと設定
	CText::mFont.Load("font\\FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);
	CText::mFont2.Load("font\\font2nd.tga");
	CText::mFont2.SetRowCol(8, 256 / 16);
	CText::mFont3.Load("font\\FontDIY.tga");
	CText::mFont3.SetRowCol(8, 176 / 11);
	
	mCource01.Load("material\\racing_mat\\CourceNew01.obj", "material\\racing_mat\\CourceNew01.mtl");//路面
	new CRoadManager(&mCource01, CVector(-360.0f, 5.0f - 33.0f, 230.0f), CVector(), CVector(50.0f, 2.0f, 50.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, -1.0f), 120.0f);//



	mScene = CScene::ETITLE;
}


void CSceneCheck::Update() {
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	if (CKey::Push(VK_LEFT))
	{
		mCameraRotation.mY++;
	}
	if (CKey::Push(VK_RIGHT))
	{
		mCameraRotation.mY--;
	}
	if (CKey::Push(VK_UP))
	{
		mCameraRotation.mX--;
	}
	if (CKey::Push(VK_DOWN))
	{
		mCameraRotation.mX++;
	}
	CVector v;
	CMatrix r;
	r = CMatrix().RotateX(mCameraRotation.mX) * CMatrix().RotateY(mCameraRotation.mY);
	if (CKey::Push('W'))
	{
		v = CVector(0.0f, 0.0f, 1.0f) * r;
	}
	if (CKey::Push('S'))
	{
		v = CVector(0.0f, 0.0f, -1.0f) * r;
	}
	mEye = mEye + v;
	e = mEye;
	c = mEye + CVector(0.0f, 0.0f, 1.0f) * r;
	u = CVector(0.0f, 1.0f, 0.0f) * r;//*mPlayer->mMatrixRotate;
	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	Camera.mEye = e;

	//タスクマネージャの更新・描画
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Render();	
	CollisionManager.Render();

	return;
}

//次のシーンの取得
CScene::EScene CSceneCheck::GetNextScene(){
	return mScene;
}