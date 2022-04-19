#include "CTank.h"
#include "CKey.h"

#define OBJTANK1 "res\\tank1.obj"	//モデルのファイル
#define MTLTANK1 "res\\tank1.mtl"	//モデルのマテリアルファイル
#define ROTATEY CVector(0.0f, 1.0f, 0.0f) //回転速度
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //移動速度

CModel CTank::mModel;	//モデルデータ作成

CTank::CTank()
{
	//モデルが読まれてない時は読む
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK1, MTLTANK1);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
}

CTank::CTank(const CVector& position, const CVector& rotation,
	const CVector& scale)
	: CTank()
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
	new CTank2(this);

}

void CTank::Update()
{
	//Aキー入力で左回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation = mRotation + ROTATEY;
	}
	//Dキー入力で右回転
	if (CKey::Push('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATEY;
	}
	//Wキー入力で前進
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//Sキー入力で後退
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	CTransform::Update();
}

#define OBJTANK2 "res\\tank2.obj"	//モデルのファイル
#define MTLTANK2 "res\\tank2.mtl"	//モデルのマテリアルファイル
CModel CTank2::mModel;	//モデルデータ作成

CTank2::CTank2(CCharacter* parent)
	: mpParent(parent)
{
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJTANK2, MTLTANK2);
	}
	mpModel = &mModel;
	mScale.Set(1.0f, 1.0f, 1.0f);	
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
	//自身の行列×親の行列
	mMatrix = mMatrix * mpParent->Matrix();
}
