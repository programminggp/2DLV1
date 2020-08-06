//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"
//バレットクラスのインクルード
#include "CBullet.h"
//タスクマネージャのインクルード
#include "CTaskManager.h"
#include "CRes.h"
#include "CMissile.h"
#include "CBillBoard.h"
#include "CEffect.h"
#include "Define.h"

CPlayer *CPlayer::sPlayer = 0;
//スマートポインタの外部参照
extern std::shared_ptr<CTexture> TextureExp;

CPlayer::CPlayer()
:mCollider(this,  CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.8f)
, mFireMissile(0)
, mFireBullet(0)
, mSearch(this, CVector(0.0f, 0.0f, 400.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 40.0f)
, mpTarget(0)
, mVelocity(PLAYER_POWER_MIN)
{
	sPlayer = this;

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
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//3
		//Y軸の回転値を増加
		mRotation.mY += 1;
	}
	//Dキー入力で回転
	if (CKey::Push('D')) {
		//3
		//Y軸の回転値を減算
		mRotation.mY -= 1;
	}
	//Wキー入力で上向き
	if (CKey::Push('W')) {
		//3
		//X軸の回転値を加算
		mRotation.mX += 1;
	}
	//Sキー入力で上向き
	if (CKey::Push('S')) {
		//3
		//X軸の回転値を減算
		mRotation.mX -= 1;
	}
	//7
	//Iキー入力で出力UP
	if (CKey::Push('I')) {
		mVelocity += POWER_UP;
		if (mVelocity > PLAYER_POWER_MAX) {
			mVelocity = PLAYER_POWER_MAX;
		}
	}
	//Kキー入力で出力DOWN
	if (CKey::Push('K')) {
		mVelocity -= POWER_UP;
		if (mVelocity < PLAYER_POWER_MIN) {
			mVelocity = PLAYER_POWER_MIN;
		}
	}

	//攻撃
	//スペースキー入力で弾発射
	if (mFireBullet > 0) {
		mFireBullet--;
	}
	else {
		//8
		//スペースキー入力で弾発射
		if (CKey::Push(VK_SPACE)) {
			new CBullet(CVector(0.0f, 0.0f, 20.0f) * mMatrix, mRotation);
			mFireBullet = PLAYER_BULLET_INTERVAL;
		}
	}
	//Mキーでミサイル発射
	if (mFireMissile > 0) {
		mFireMissile--;
	}
	else {
		//9
		//Mキー入力でミサイル発射
		if (CKey::Push('M')) {
			new CMissile(&CRes::sMissileM, CVector(6.0f, -2.0f, 0.0f) * mMatrix, mRotation, CVector(0.2f, 0.2f, 0.2f));
			mFireMissile = PLAYER_MISSILE_INTERVAL;
		}
	}

	//CCharacterの更新
	CCharacter::Update();
	//4
	//移動させる
	mPosition = mPosition + CVector(0.0f, 0.0f, mVelocity) * mMatrixRotate;
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
				case CCollider::EBODY:
					if (y->mpParent->mTag == EBULLET) {
						//敵の弾に当たった時
						//エフェクト生成
						new CEffect(mPosition, 1.0f, 1.0f, TextureExp, 4, 4, 1);
						CVector v =  y->mpParent->mPosition - mPosition;
						v = v.Normalize();
						mPosition = mPosition + v;
						CCharacter::Update();
					}
					break;
				case CCollider::ESEARCH:
					return;
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
