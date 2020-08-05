#include "CEnemy.h"
#include "CEffect.h"
#include "CPlayer.h"
#include "CBullet.h"

#include "Define.h"

//スマートポインタの外部参照
extern std::shared_ptr<CTexture> TextureExp;

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.4f)
, mSearch(this, CVector(0.0f, 0.0f, 200.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 20.0f)
, mHp(2)
, mPointCnt(0)
, mpTarget(0)
, mFireBullet(0)
, mVelocity(ENEMY_POWER)
{
	mCollider.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	mTag = EENEMY;
	mpTarget = &CPlayer::sPlayer->mPosition;
}
//更新処理
void CEnemy::Update() {
	//ポイントへのベクトルを求める
	CVector dir;

	if (mFireBullet > 0) {
		mFireBullet--;
	}

	if (mPointCnt > 0) {
		mPointCnt--;
	}
	else {
		if (mpTarget) {
			mPoint = *mpTarget;
		}
		else {
			mPoint = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
		}
		mPointCnt = ENEMY_POINTCOUNT;
	}
	dir = mPoint - mPosition;

	mVelocity = dir.Length() / 100.0f;
	if (mVelocity > ENEMY_POWER) {
		mVelocity = ENEMY_POWER;
	}
	else if (mVelocity < ENEMY_VELOCITY_LOW) {
		mVelocity = ENEMY_VELOCITY_LOW;
	}

	//左方向のベクトルを求める
	CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrix - CVector() * mMatrix;
	left = left.Normalize();
	//上方向のベクトルを求める
	CVector up = CVector(0.0f, 1.0f, 0.0f) * mMatrix - CVector() * mMatrix;
	up = up.Normalize();
	CVector z = CVector(0.0f, 0.0f, 1.0f) * mMatrix - CVector() * mMatrix;
	z = z.Normalize();

	//左右の回転処理（Y軸）
	if (left.Dot(dir) > 0.0f) {
		mRotation.mY += ENEMY_TURN_DEG;
	}
	else if (left.Dot(dir) < 0.0f) {
		mRotation.mY -= ENEMY_TURN_DEG;
	}
	//上下の回転処理（X軸）
	if (up.Dot(dir) > 0.0f) {
		if (z.Dot(dir) > 0.0) {
			mRotation.mX -= ENEMY_TURN_DEG;
		}
	}
	else if (up.Dot(dir) < 0.0f) {
		if (z.Dot(dir) > 0.0) {
			mRotation.mX += ENEMY_TURN_DEG;
		}
	}

	//行列を更新
	CCharacter::Update();
	//位置を移動
	mPosition = mPosition + CVector(0.0f, 0.0f, mVelocity) * mMatrixRotate;

	if (mHp < 0) {
		mHp--;
		mRotation.mX = 55;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 2.5f, 2.5f, TextureExp, 4, 4, 2);
		}
		if (mHp < -500) {
			mEnabled = false;
		}
	}
}

void CEnemy::Collision(CCollider *m, CCollider *y) {
	//共に球コライダの時
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		if (CCollider::Collision(m, y)) {
			//コライダがサーチか判定
			if (m->mTag == CCollider::ESEARCH) {
				//衝突したコライダの親の種類を判定
				switch (y->mpParent->mTag) {
				case EAIRBASE://空軍基地
				case EPLAYER://プレイヤーの時
					if (y->mTag == CCollider::EBODY) 
					{
						if (mFireBullet == 0)
						{
							CBullet *bullet = new CBullet();
							bullet->Set(0.1f, 1.5f);
							bullet->mPosition = CVector(0.0f, 0.0f, 20.0f) * mMatrix;
							bullet->mRotation = mRotation;
							bullet->mTag = EBULLET;
							mFireBullet = 15;
						}
					}
					break;
				}
			}
			else  {
				//衝突したコライダの親の種類を判定
				switch (y->mpParent->mTag) {
				case EMISSILE:
					mHp -= 10;
				case EBULLET:
					if (y->mTag == CCollider::EBODY) {
						//エフェクト生成
						new CEffect(mPosition, 2.0f, 2.0f, TextureExp, 4, 4, 1);
						mHp--;
					}
				}
			}
		}
	}
}
