//プレイヤークラスのインクルード
#include"CPlayer.h"
//キー入力クラスのインクルード
#include"CKey.h"
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,0.1f)//移動速度

//デフォルトコンストラクタ
CPlayer::CPlayer()
:mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f)),
mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f)),
mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
{
}

//更新処理
void CPlayer::Update() {
	//スペースキーを入力で弾を発射
	//スペースキーを入力で弾を発射
	if (CKey::Push(VK_SPACE)){
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
	//TaskManager.Add(bullet);
		
	}
	//Dキー入力で回転
	if (CKey::Push('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATION_YV;
	}
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation = mRotation + ROTATION_YV;
	}
	//Iキー入力で前進
	if (CKey::Push('I')){
		//Z軸方向の値を回転させ移動させる
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//Sキー入力で上向き
	if (CKey::Push('S'))
	{
		//X軸の回転値を減算
		mRotation = mRotation - ROTATION_XV;
	}
	//Wキー入力で下向き
	if (CKey::Push('W'))
	{
		//X軸の回転値を加算
		mRotation = mRotation + ROTATION_XV;
	}
	//変換行列の更新
	CTransform::Update();
}

//衝突処理
void CPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()){
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE){
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}
		break;
	}
}