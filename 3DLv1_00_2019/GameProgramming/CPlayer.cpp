//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"
//バレットクラスのインクルード
#include "CBullet.h"
//22extern CBullet Bullet;
//タスクマネージャのインクルード
#include "CTaskManager.h"

CPlayer::CPlayer()
//:mCollider(this,  CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f),
//CVector(5.0f, 5.0f, 5.0f), 0.8f)
{
	mTag = EPLAYER;//種類はプレイヤー
	//線分コライダの設定
	//前後
	mLine[0].SetLine(this, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f));
	//上下
	mLine[1].SetLine(this, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f));
	//左
	mLine[2].SetLine(this, CVector(0.0f, 0.0f, -8.0f), CVector(9.0f, 0.0f, -8.0f));
	//右
	mLine[3].SetLine(this, CVector(0.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f));
	//	mCollider.mTag = CCollider::EBODY;//種類は機体
}

//更新処理
void CPlayer::Update() {
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation.mY += 1;
	}
	//Iキー入力で前進
	if (CKey::Push('I')) {
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//Dキー入力で回転
	if (CKey::Push('D')) {
		//Y軸の回転値を減算
		mRotation.mY -= 1;
	}
	//Sキー入力で上向き
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		mRotation.mX -= 1;
	}
	//Wキー入力で上向き
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		mRotation.mX += 1;
	}
	//スペースキー入力で弾発射
	if (CKey::Push(VK_SPACE)) {
		CBullet *bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
 		bullet->mRotation = mRotation;
//		TaskManager.Add(bullet);
	}
	//CCharacterの更新
	CCharacter::Update();
}
