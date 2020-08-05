#include "CMissile.h"
//エフェクトクラスのインクルード
#include "CEffect.h"
//スマートポインタの外部参照
extern std::shared_ptr<CTexture> TextureExp;

#define MISSILE_VELOCITY 0.6f	//ミサイル速さ
#define TURN_DEG 1.5f

//コンストラクタ
//CAirBase(モデル, 位置, 回転, 拡縮)
CMissile::CMissile(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.1f)
, mLife(180)
, mpPoint(0)
{
	mCollider.mTag = CCollider::EBODY;
	mTag = EMISSILE;
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CCharacter::Update();
}

//衝突処理
void CMissile::Collision(CCollider *m, CCollider *y) {
	//共に球コライダの時
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		if (y->mTag == CCollider::EBODY) {
			if (CCollider::Collision(m, y)) {
				if (y->mpParent->mTag != EPLAYER) {
					//エフェクト生成
					new CEffect(y->mPosition * y->mMatrix * y->mpParent->mMatrix, 5.0f, 5.0f, TextureExp, 4, 4, 1);
					mEnabled = false;
				}
			}
		}
	}
}

void CMissile::Update() {
	if (mpPoint) {
		//ポイントへのベクトルを求める
		CVector dir = mpPoint->mPosition - mPosition;

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
			mRotation.mY += TURN_DEG;
		}
		else if (left.Dot(dir) < 0.0f) {
			mRotation.mY -= TURN_DEG;
		}
		//上下の回転処理（X軸）
		if (up.Dot(dir) > 0.0f) {
			if (z.Dot(dir) > 0.0) {
				mRotation.mX -= TURN_DEG;
			}
		}
		else if (up.Dot(dir) < 0.0f) {
			if (z.Dot(dir) > 0.0) {
				mRotation.mX += TURN_DEG;
			}
		}

	}

	mPosition = mPosition + CVector(0.0f, 0.0f, MISSILE_VELOCITY) * mMatrixRotate;
	CCharacter::Update();
	if (mLife-- < 0) {
		mEnabled = false;
	}
}
