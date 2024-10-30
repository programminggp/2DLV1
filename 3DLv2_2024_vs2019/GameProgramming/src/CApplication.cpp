#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"
#include "CTransform.h"

#include "CCollisionManager.h"

#include "CBillBoard.h"
#include "CEnemy3.h"

#include "CCamera.h"

#include "CMap.h"
#include "CZombie.h"

//クラスのstatic変数
CTexture CApplication::mTexture;

//CCamera CApplication::mCamera;

CUi* CApplication::spUi = nullptr;
CApplication::~CApplication()
{
	delete spUi;	//インスタンスUiの削除
}
CUi* CApplication::Ui()
{
	return spUi;
}

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//敵輸送機モデル
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"

//背景モデルデータの指定
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"


//CTaskManager CApplication::mTaskManager;

//CTaskManager* CApplication::TaskManager()
//{
//	return &mTaskManager;
//}

//CCamera* CApplication::Camera()
//{
//	return &mCamera;
//}

CMatrix CApplication::mModelViewInverse;

const CMatrix& CApplication::ModelViewInverse()
{
	return mModelViewInverse;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//カメラの設定
	mActionCamera.Set(2.5f, -15.0f, 180.0f);

	//mKnight.Load("res\\knight\\knight_low.x");
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
	//mKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
	//mKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	//mKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
	//mKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
	//mKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン

	//3Dモデルファイルの読み込み
//	mModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
//	mXPlayer.Init(&mModelX);

	mFont.Load("FontG.png", 1, 4096 / 64);

	//mXEnemy.Init(&mKnight);
	//mXEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	//mXEnemy.ChangeAnimation(2, true, 200);

	mpPaladin = new CPaladin(CVector(-1.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CZombie(CVector(1.0f, 0.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f));

	new CMap();
}

void CApplication::Update()
{
	CTaskManager::Instance()->Update();

	mActionCamera.Position(mpPaladin->Position()
		+ CVector(0.0f, 2.0f, 0.0f));
	mActionCamera.Update();
	mActionCamera.Render();

	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//逆行列の取得
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	//衝突処理
	CTaskManager::Instance()->Collision();
//	CCollisionManager::Instance()->Collision();

	CTaskManager::Instance()->Render();

	//コライダの描画
	CCollisionManager::Instance()->Render();

	//2D描画開始
	CCamera::Start(0, 800, 0, 600);

	mFont.Draw(20, 20, 10, 12, "3D PROGRAMMING");

	CVector screen;
	//Enemyの座標をスクリーン座標へ変換します
	if (CActionCamera::Instance()->WorldToScreen(&screen, mpPaladin->Position()))
	{
		//変換先の座標に文字列を出力する
		mFont.Draw(screen.X(), screen.Y() - 25, 7, 14, "PLAYER");
	}

	//2Dの描画終了
	CCamera::End();
}
