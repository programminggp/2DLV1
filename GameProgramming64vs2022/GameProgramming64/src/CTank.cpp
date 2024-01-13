#include "CTank.h"
#include "CKey.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"

#include "CBullet.h"

#define OBJTANK1 "res\\tank1.obj"	//モデルのファイル
#define MTLTANK1 "res\\tank1.mtl"	//モデルのマテリアルファイル
#define OBJTANK2 "res\\tank2.obj"	//モデルのファイル
#define MTLTANK2 "res\\tank2.mtl"	//モデルのマテリアルファイル
#define OBJTANK3 "res\\tank3.obj"	//モデルのファイル
#define MTLTANK3 "res\\tank3.mtl"	//モデルのマテリアルファイル

#define ROTATEY CVector(0.0f, 1.0f, 0.0f)
#define ROTATEX CVector(1.0f, 0.0f, 0.0f)
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //回転速度
#define CANNON_TIP CVector(0.0f, 1.7f, 7.0f)

#define HP 3	//耐久値
//#define VELOCITY 0.11f	//速度

CModel CTank::mModel;	//モデルデータ作成
CModel CTank2::mModel;	//モデルデータ作成
CModel CTank3::mModel;	//モデルデータ作成


#define FIRECOUNT 15	//発射間隔


CTank::CTank()
	: mCollider(this, &mMatrix, CVector(0.0f, 1.0f, 0.0f), 0.0f /*0.2f*/)
	, mHp(HP)
	, mFireCount(0)
{
	mTag = EPLAYER;
	//モデルが読まれてない時は読む
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK1, MTLTANK1);
		//モデルのポインタ設定
		mpModel = &mModel;
	}
	mpTank2 = new CTank2(this);
}

CTank::CTank(const CVector& position, const CVector& rotation, const CVector& scale)
	: CTank()
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
	//優先度を2に変更する
	mPriority = 2;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する
}

void CTank::Update()
{
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation = mRotation + ROTATEY;
	}
	if (CKey::Push('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATEY;
	}
	//Sキー入力で上向き
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//Wキー入力で上向き
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	CTransform::Update();
}

void CTank::Collision(CCollider* m, CCollider* o)
{
}

void CTank::TaskCollision()
{
}

CTank2* CTank::Tank()
{
	return mpTank2;
}

#define OFFSETTANK2 0.0f, -1.2f, 0.34f //砲塔のオフセット

CTank2::CTank2(CTank* parent)
	: mpParent(parent)
{
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK2, MTLTANK2);
		mpModel = &mModel;
	}
	mScale.Set(1.0f, 1.0f, 1.0f);
	new CTank3(this);
	//オフセット行列の設定
	mOffset.Translate(OFFSETTANK2);
	//移動量にオフセットの反対向きを設定
	mPosition = CVector(OFFSETTANK2) * -1.0f;
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する
}

void CTank2::Update()
{
	if (CKey::Push('J'))
	{
		mRotation = mRotation + ROTATEY;
	}
	if (CKey::Push('L'))
	{
		mRotation = mRotation - ROTATEY;
	}
	CTransform::Update();
	//自身の行列の前にオフセット行列を掛ける
	mMatrix = mOffset * mMatrix * mpParent->Matrix();
}


#define OFFSETTANK3 0.0f, -1.7f, -0.43f

CTank3::CTank3(CTank2* parent)
	: mpParent(parent)
{
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK3, MTLTANK3);
		mpModel = &mModel;
	}
	mScale.Set(1.0f, 1.0f, 1.0f);
	mOffset.Translate(OFFSETTANK3);
	mPosition = CVector(OFFSETTANK3) * -1.0f;
}

void CTank3::Update()
{
	int mFireCount = 0;
	if (CKey::Push('K'))
	{
		mRotation = mRotation + ROTATEX;
	}
	if (CKey::Push('I'))
	{
		mRotation = mRotation - ROTATEX;
	}
	CTransform::Update();
	mMatrix = mOffset * mMatrix * mpParent->Matrix();
	if (CKey::Push(VK_SPACE) && mFireCount == 0) {
		mFireCount = FIRECOUNT;
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 0.5f);
		//CVector f = CVector(0.0f, 0.0f, 1.0f) * mMatrix - CVector(0.0f, 0.0f, 0.0f) * mMatrix;
		//CVector u = CVector(0.0f, 1.0f, 0.0f) * mMatrix - CVector(0.0f, 0.0f, 0.0f) * mMatrix;
		//f.Set(f.GetRotationX(u), f.GetRotationY(), 0.0f);
		//Rotation()追加
		//mpParentエラー対応
		//座標の設定
		bullet->Position(CANNON_TIP * mMatrix);
		//回転値の設定
		CVector rotation = mpParent->mpParent->Rotation() + mpParent->Rotation() + Rotation();
		bullet->Rotation(rotation);
		bullet->Update();
	}
}
