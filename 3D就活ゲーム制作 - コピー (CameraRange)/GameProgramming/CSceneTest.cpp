#include "CSceneTest.h"
//#include "CRectangle.h"
#include "CCollisionManager.h"
#include "CRoadManager.h"
#include "CSceneTitle.h"

#define PLAYER_POSITION CVector(-3831.5f, 13.5f, 16011.5f)

//次のシーンの取得
CScene::EScene CSceneTest::GetNextScene(){
	return mScene;
}

//初期化処理のオーバーライド
void CSceneTest::Init() {
	//テクスチャファイルを読み込む
	//フォントの設定
	CText::mFont.Load("font\\font2nd.tga");
	CText::mFont.SetRowCol(8, 256 / 16);
	CText::mFont2.Load("font\\FontG.tga");
	CText::mFont2.SetRowCol(1, 4096 / 64);
	CText::mFont3.Load("font\\FontDIY.tga");//自作フォント
	CText::mFont3.SetRowCol(8, 176 / 11);
	
	//シーンの設定
	mScene = ETEST;

	mCource05Road.Load("material\\racing_mat\\stage5\\cource05road2.obj", "material\\racing_mat\\stage5\\cource05road2.mtl");

	//コース全体のサイズ感を設定
	float mtsize = 35.0f;
	float height = 11.0f;
	CSceneTitle::mCource = CSceneTitle::ECOURCE5;
	new CRoadManager(&mCource05Road, CVector(0.0f, 21.0f, 0.0f), CVector(), CVector(mtsize, height, mtsize), PLAYER_POSITION, CVector(0.0f, 0.0f, -1.0f), 320.0f, 640.0f);//

}
//更新処理のオーバーライド
void CSceneTest::Update() {

	CTaskManager::Get()->Update();

	Render();//テキスト等の描画

	if (CKey::Once(VK_RETURN))
	{
		CSceneTitle::mMode = CSceneTitle::EMODE_GRANDPRIX;
		CSceneTitle::mCource = CSceneTitle::ECOURCE5;
		mScene = CScene::ERACE5;
	}
}

#define CAMERA_V 100.0f

void CSceneTest::Render(){

	if (CKey::Push('W'))
	{
		e.mZ += CAMERA_V;
		c.mZ += CAMERA_V;
	}
	if (CKey::Push('S'))
	{
		e.mZ -= CAMERA_V;
		c.mZ -= CAMERA_V;
	}
	if (CKey::Push('A'))
	{
		e.mX += CAMERA_V;
		c.mX += CAMERA_V;
	}
	if (CKey::Push('D'))
	{
		e.mX -= CAMERA_V;
		c.mX -= CAMERA_V;
	}
	if (CKey::Push(VK_UP))
	{
		e.mY += CAMERA_V;
		c.mY += CAMERA_V;
	}
	if (CKey::Push(VK_DOWN))
	{
		e.mY -= CAMERA_V;
		c.mY -= CAMERA_V;
	}




	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);


	CTaskManager::Get()->Render();//タスク	

			//衝突判定の描画
	CollisionManager.Render();


	//2D描画開始
	Start2D(0, 800, 0, 600);	
	float col[] = { 1.0f, 1.0f, 1.0f, 1.0f };//{ R,G,B,α }
	glColor4fv(col);
	//文字列の描画
//	CText::DrawString("3D-RACE", 190, 430, 36, 36);
//	CText::DrawString("Push Enter Key", 200, 177, 16, 16);
	//2D描画終了
	End2D();
}

CSceneTest::~CSceneTest()
{
	CTaskManager::Get()->Disabled();
	CTaskManager::Get()->Delete();
}
