#include "CEnemy2.h"
#include "CTaskManager.h"
#include "CEffect.h"
#include "CCollisionManager.h"
#include "CPlayer.h"
#include "CBullet.h"

#define OBJ "res\\f16.obj"	//モデルのファイル
#define MTL "res\\f16.mtl"	//モデルのマテリアルファイル
#define HP 3	//耐久値
#define VELOCITY 0.11f	//速度

CModel CEnemy2::sModel;	//モデルデータ作成

//デフォルトコンストラクタ
CEnemy2::CEnemy2()
	: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
	, mHp(HP)
{
	//モデルが無いときは読み込む
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &sModel;
}

//コンストラクタ
//CEnemy(位置, 回転, 拡縮)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation,
	const CVector& scale)
	: CEnemy2()	//デフォルトコンストラクタを実行する
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する
	//目標地点の設定
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//更新処理
void CEnemy2::Update() 
{
	//左向き（X軸）のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//上向き（Y軸）のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前方向（Z軸）のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//プレイヤーのポインタが0以外の時
	CPlayer* player = CPlayer::Get();
	if (player != nullptr)
	{
		//プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - mPosition;
		float dx = vp.Dot(vx);	//左ベクトルとの内積を求める
		float dy = vp.Dot(vy);	//上ベクトルとの内積を求める
		float dz = vp.Dot(vz);	//前ベクトルとの内積を求める
		//X軸のズレが2.0以下
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y軸のズレが2.0以下
			if (-2.0f < dy && dy < 2.0f)
			{
				if (0.0f < dz && dz <= 30.0f)
				{
					//弾を発射します
					CBullet* bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->Position(
						CVector(0.0f, 0.0f, 10.0f) * mMatrix);
					bullet->Rotation(mRotation);
					bullet->Update();
				}
			}
		}
	}
	//HPが0以下の時　撃破
	if (mHp <= 0)
	{
		mHp--;
		//15フレーム毎にエフェクト
		if (mHp % 15 == 0)
		{
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//下降させる
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}

	//目標地点までのベクトルを求める
	CVector vp = mPoint - mPosition;
	//課題
	float dx = vp.Dot(vx);	//左ベクトルとの内積を求める

	float dy = vp.Dot(vy);	//上ベクトルとの内積を求める
	float margin = 0.1f;
	//左右方向へ回転
	if (dx > margin)
	{
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //左へ回転
	}
	else if (dx < -margin)
	{
		//課題
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f); //右へ回転
	}
	//上下方向へ回転
	if (dy > margin)
	{
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //上へ回転
	}
	else if (dy < -margin)
	{
		//課題
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f); //下へ回転
	}
	//移動する
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();	//行列更新
		//およそ3秒毎に目標地点を更新
	int r = rand() % 180;	//rand()は整数の乱数を返す
				//% 180 は180で割った余りを求める
	if (r == 0)
	{
		if (player != nullptr)
		{
			mPoint = player->Position();
		}
		else
		{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

}

//衝突処理
//Collision(コライダ1, コライダ2)
void CEnemy2::Collision(CCollider* m, CCollider* o) 
{
	CVector adjust;
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE: //球コライダの時
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突している時は無効にする
			//mEnabled = false;
			mHp--;	//ヒットポイントの減算
		}
		break;
	case CCollider::ETRIANGLE:
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//撃破で地面に衝突すると無効
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}

void CEnemy2::TaskCollision()
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
