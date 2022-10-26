#include "CSceneTest.h"
#include "CInput.h"
#include "CKey.h"

//モデルのファイル名
//#define MODELX_FILE "res\\felguard\\felguard-X.X"
//#define MODELX_FILE "res\\paladin\\Paladin.X"
#define MODELX_FILE "res\\paladin\\Paladin WProp J Nordstrom@Idle.fbx.x"
//アニメーションデータ追加
#define ANIMATION_ATTACKSP1 "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Attack.x"
#define ANIMATION_ATTACK "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Slash.fbx.x"
#define ANIMATION_JUMP "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Jump.fbx.x"
#define ANIMATION_RUN "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Run.fbx.x"
#define ANIMATION_WALK "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Walk.fbx.x"
//地形モデルデータ
#define MODEL_GROUND "res\\forest-terrain\\TerrainNew1000.obj","res\\forest-terrain\\TerrainNew1000.mtl"

void CSceneTest::Init() {
	//モデルデータ読み込み
	mModelX.Load(MODELX_FILE);
	//モデルデータ設定
	mXCharacter.Init(&mModelX);
	//スケールを等倍に設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	mTransform.Scale(mScale);
	//マウス操作系変数の初期化
	mPushFlg = false;
	mOldMousePosX = 0;

	//アニメーションの追加ANIMATION_RUN
	mModelX.AddAnimationSet(ANIMATION_WALK);
	mModelX.AddAnimationSet(ANIMATION_RUN);
	mModelX.AddAnimationSet(ANIMATION_ATTACK);
	mModelX.AddAnimationSet(ANIMATION_ATTACKSP1);
	mModelX.AddAnimationSet(ANIMATION_JUMP);
	//アニメーションを切り替え
	mXCharacter.ChangeAnimation(1, true, 120);

	//地形データ読み込み
	mGround.Load(MODEL_GROUND);
}

void CSceneTest::Update() 
{
	//Mouse Right Drag Turn
	float x, y;
	//マウスカーソル座標の取得
	CInput::GetMousePosWin(&x, &y);
	if (mPushFlg)
	{
		//マウス右ボタンクリック
		if (CKey::Push(VK_RBUTTON))
		{
			if (mOldMousePosX < x)
			{
				//Turn Right
				CVector v = mTransform.Rotation();
				v.Y(v.Y() + x - mOldMousePosX);
				mTransform.Rotation(v);
				mOldMousePosX = x;
			}
			else if(x < mOldMousePosX)
			{
				//Turn Left
				CVector v = mTransform.Rotation();
				v.Y(v.Y() - mOldMousePosX + x);
				mTransform.Rotation(v);
				mOldMousePosX = x;
			}
		}
		else
		{
			mPushFlg = false;
		}
	}
	else
	{
		//マウス右ボタンクリック
		if (CKey::Push(VK_RBUTTON))
		{
			mPushFlg = true;
			mOldMousePosX = x;
		}
	}

	//Wheel Change Scale
	//マウスホイール状態の取得
	//-1:下へ回転　0:回転なし　1:上に回転
	int w = CInput::Wheel();
	if (w != 0)
	{
		if (w > 0)
		{
			//Big
			mScale.X(mScale.X() + 0.1f);
			mScale.Y(mScale.Y() + 0.1f);
			mScale.Z(mScale.Z() + 0.1f);
		}
		else
		{
			//Small
			mScale.X(mScale.X() - 0.1f);
			mScale.Y(mScale.Y() - 0.1f);
			mScale.Z(mScale.Z() - 0.1f);
		}
		mTransform.Scale(mScale);
	}

	//カメラ設定
	gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);


	//回転など
	mTransform.Update();
	glMultMatrixf(mTransform.Matrix().M());

//	mGround.Render(CMatrix().Scale(150, 150, 150) * CMatrix().Translate(-150, 0, -250));
	//地形データ描画
	mGround.Render(CMatrix().Scale(150, 150, 150) * CMatrix().Translate(0, 0, -10));

	//キャラクタ更新・描画
	mXCharacter.Update();
	mXCharacter.Render();
}

