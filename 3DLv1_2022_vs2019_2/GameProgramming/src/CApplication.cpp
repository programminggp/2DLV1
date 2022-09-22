#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CMatrix.h"
#include "CTransform.h"

//クラスのstatic変数
CTexture CApplication::mTexture;
CCharacterManager CApplication::mCharacterManager;

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav" //ゲームオーバー音声ファイル
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl"
//背景モデルデータの指定
#define MODEL_BACKGROUND  "res\\sky.obj", "res\\sky.mtl"

CCharacterManager* CApplication::CharacterManager()
{
	return &mCharacterManager;
}

CTexture* CApplication::Texture()
{
	return &mTexture;
}

void CApplication::Start()
{
	//モデルファイルの入力
	mModel.Load(MODEL_OBJ);
	mBackGround.Load(MODEL_BACKGROUND);
	CMatrix matrix;
	matrix.Print();

	mEye = CVector(1.0f, 2.0f, 3.0f);

	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));

}

void CApplication::Update()
{
	//頂点1､頂点2､頂点3,法線データの作成
	CVector v0, v1, v2, n;
	//法線を上向きで設定する
	n.Set(0.0f, 1.0f, 0.0f);
	//頂点1の座標を設定する
	v0.Set(0.0f, 0.0f, 0.5f);
	//頂点2の座標を設定する
	v1.Set(1.0f, 0.0f, 0.0f);
	//頂点3の座標を設定する
	v2.Set(0.0f, 0.0f, -0.5f);

	if (mInput.Key('J'))
	{
		mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('L'))
	{
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	if (mInput.Key('I'))
	{
		mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	}
	if (mInput.Key('K'))
	{
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}	
	if (mInput.Key('O'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}
	if (mInput.Key('M'))
	{
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}

	mPlayer.Update();

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(0.0f, 10.0f, -30.0f) * mPlayer.Matrix();
	//注視点を求める
	c = mPlayer.Position();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.MatrixRotate();
	//カメラの設定
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

	mPlayer.Render();

	mBackGround.Render(CMatrix());

	mPlayer.bullet.Update();
	mPlayer.bullet.Render();
}
