//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"
//バレットクラスのインクルード
#include "CBullet.h"
//22extern CBullet Bullet;
//タスクマネージャのインクルード
#include "CTaskManager.h"
//?
#include "CMissile.h"
#include "CRes.h"
//?
#include "CBillBoard.h"

#define VELOCITY_INIT 1.0f
#define POWER_UP 0.02f

CPlayer::CPlayer()
:mCollider(this,  CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.8f)
, mFireMissile(0)
, mFireBullet(0)
, mSearch(this, CVector(0.0f, 0.0f, 400.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 40.0f)
, mpTarget(0)
, mVelocity(VELOCITY_INIT)
{
	mTag = EPLAYER;//種類はプレイヤー
	mCollider.mTag = CCollider::EBODY;//種類は機体
	mSearch.mTag = CCollider::ESEARCH;

	//線分コライダの設定
	//前後
	mLine[0].SetLine(this, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f));
	//上下
	mLine[1].SetLine(this, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f));
	//左
	mLine[2].SetLine(this, CVector(0.0f, 0.0f, -8.0f), CVector(9.0f, 0.0f, -8.0f));
	//右
	mLine[3].SetLine(this, CVector(0.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f));
}

//更新処理
void CPlayer::Update() {
	if (mFireMissile > 0) {
		mFireMissile--;
	}
	if (mFireBullet > 0) {
		mFireBullet--;
	}
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation.mY += 1;
	}
	//Iキー入力で前進
	if (CKey::Push('U')) {
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 5.0f) * mMatrix;
	}
	//Iキー入力で前進
	if (CKey::Push('I')) {
		//Z軸方向に1進んだ値を回転移動させる
		mVelocity += POWER_UP;
		if (mVelocity > VELOCITY_INIT * 3) {
			mVelocity = VELOCITY_INIT * 3;
		}
	}
	if (CKey::Push('K')) {
		//Z軸方向に1進んだ値を回転移動させる
		mVelocity -= POWER_UP;
		if (mVelocity < VELOCITY_INIT) {
			mVelocity = VELOCITY_INIT;
		}
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
	if (CKey::Push(VK_SPACE) && mFireBullet == 0) {
		mFireBullet = 10;
		CBullet *bullet = new CBullet();
		bullet->Set(0.05f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 20.0f) * mMatrix;
 		bullet->mRotation = mRotation;
		bullet->mTag = EBULLET;
//		TaskManager.Add(bullet);
	}
	//スペースキー入力で弾発射
	if (CKey::Push('M') && mFireMissile == 0) {
		mFireMissile = 60;
		if (mpTarget) {
			CMissile *m = new CMissile(&CRes::sMissileM, CVector(6.0f, -2.0f, 0.0f) * mMatrix, mRotation, CVector(0.2f, 0.2f, 0.2f));
			m->mpPoint = mpTarget;
		}
		else {
			new CMissile(&CRes::sMissileM, CVector(6.0f, -2.0f, 0.0f) * mMatrix, mRotation, CVector(0.2f, 0.2f, 0.2f));
		}
		//		TaskManager.Add(bullet);
	}
	//CCharacterの更新
	CCharacter::Update();
	mPosition = CVector(0.0f, 0.0f, mVelocity) * mMatrix;
	mpTarget = 0;

}

//衝突処理
void CPlayer::Collision(CCollider *m, CCollider *y) {
	//自身のコライダタイプの判定
	switch (m->mType) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(y, m, &adjust);
			//位置の更新
			mPosition = mPosition - adjust * -1;
			//行列の更新
			CCharacter::Update();
		}
		break;
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが球コライダの時
		if (y->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, y)) {
				switch (m->mTag) {
				case CCollider::ESEARCH:
					if (y->mpParent->mTag == EENEMY) {
						CBillBoard b(y->mpParent->mPosition,1.0f, 1.0f);
						if (mpTarget == 0) {
							mpTarget = y->mpParent;
							b.mMaterial.mDiffuse[0] = 1.0f;
							b.mMaterial.mDiffuse[1] = 0.0f;
							b.mMaterial.mDiffuse[2] = 0.0f;
							b.mMaterial.mDiffuse[3] = 0.5f;
							b.Update();
							b.Render();
						}
						else if (mpTarget == y->mpParent) {
							b.mMaterial.mDiffuse[0] = 1.0f;
							b.mMaterial.mDiffuse[1] = 0.0f;
							b.mMaterial.mDiffuse[2] = 0.0f;
							b.mMaterial.mDiffuse[3] = 0.5f;
							b.Update();
							b.Render();
						}
						else {
							b.mMaterial.mDiffuse[0] = 0.0f;
							b.mMaterial.mDiffuse[1] = 1.0f;
							b.mMaterial.mDiffuse[2] = 0.0f;
							b.mMaterial.mDiffuse[3] = 0.5f;
							b.Update();
							b.Render();
						}
					}
					break;
				}
			}
		}
		break;
	}
}
