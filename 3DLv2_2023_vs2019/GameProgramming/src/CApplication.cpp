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

//クラスのstatic変数
CTexture CApplication::mTexture;

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
	//29
	mActionCamera.Set(5.0f, -15.0f, 180.0f);

	mBackGround.Load("res\\sky.obj", "res\\sky.mtl");

//	mColliderMesh.Set(nullptr, nullptr, &mBackGround);

	mKnight.Load("res\\knight\\knight_low.x");
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
	mKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
	mKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	mKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
	mKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
	mKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン

	//3Dモデルファイルの読み込み
	mModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
	mXPlayer.Init(&mModelX);
//	mXPlayer.Position(CVector(1, 1, 1));

	mFont.Load("FontG.png", 1, 4096 / 64);
	//敵の初期設定
	mXEnemy.Init(&mKnight);
	//敵の配置
	mXEnemy.Position(CVector(7.0f, 0.0f, 0.0f));

	mXEnemy.ChangeAnimation(2, true, 200);

	mpPaladin = new CPaladin();
	mpPaladin->Position(CVector(-1.0f, 0.0f, 5.0f));

	//アニメーションを切り替えて確認
	mpPaladin->ChangeAnimation(1, true, 60);
}

void CApplication::Update()
{
	//キャラクタークラスの更新
	mXPlayer.Update();
	//敵の更新
	mXEnemy.Update();

	mpPaladin->Update();

	//衝突処理
	CCollisionManager::Instance()->Collision();

/*
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);
	//カメラの設定
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
*/
	// カメラ設定
	mActionCamera.Position(mXPlayer.Position() + CVector(0.0f, 2.0f, 0.0f));
	mActionCamera.Update();
	mActionCamera.Render();

	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewInverse.M());
	//逆行列の取得
	mModelViewInverse = mModelViewInverse.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);

	/*
	//X軸＋回転
	if (mInput.Key('K')) {
		mMatrix = mMatrix * CMatrix().RotateX(1);
	}
	//Y軸＋回転
	if (mInput.Key('L')) {
		mMatrix = mMatrix * CMatrix().RotateY(1);
	}
	if (mInput.Key('I')) {
		mMatrix = mMatrix * CMatrix().RotateX(-1);
	}
	//Y軸＋回転
	if (mInput.Key('J')) {
		mMatrix = mMatrix * CMatrix().RotateY(-1);
	}
	//行列設定
	glMultMatrixf(mMatrix.M());
	*/

//	mBackGround.Render(mMatrix);
	//モデル描画
//	mModelX.Render();

	mXPlayer.Render();
	//敵描画
	mXEnemy.Render();

	mpPaladin->Render();

	//コライダの描画
	CCollisionManager::Instance()->Render();

	//2D描画開始
	CCamera::Start(0, 800, 0, 600);

	mFont.Draw(20, 20, 10, 12, "3D PROGRAMMING");

	CVector screen;
	//Enemyの座標をスクリーン座標へ変換します
	if (CActionCamera::Instance()->WorldToScreen(&screen, mXEnemy.Position()))
	{
		//変換先の座標に文字列を出力する
		mFont.Draw(screen.X(), screen.Y(), 7, 14,"ENEMY");
	}

	//2Dの描画終了
	CCamera::End();
}
