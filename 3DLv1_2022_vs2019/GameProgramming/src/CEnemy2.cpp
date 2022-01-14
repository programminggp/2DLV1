#include "CEnemy2.h"
#include "CEffect.h"

#define OBJ "res\\f16.obj"	//モデルのファイル
#define MTL "res\\f16.mtl"	//モデルのマテリアルファイル

CModel CEnemy2::mModel;	//モデルデータ作成

//デフォルトコンストラクタ
CEnemy2::CEnemy2()
	: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	//モデルが無いときは読み込む
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
}


//CEnemy(位置, 回転, 拡縮)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation,
	const CVector& scale)
	: CEnemy2()
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
}

//更新処理
void CEnemy2::Update() {
}

//衝突処理
//Collision(コライダ1, コライダ2)
void CEnemy2::Collision(CCollider* m, CCollider* o)
{
	//コライダのmとoが衝突しているかの判定
	if (CCollider::Collision(m, o)) {
		//エフェクト生成
		new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		//衝突している時は無効にする
		//削除mEnabled = false;
	}
}
