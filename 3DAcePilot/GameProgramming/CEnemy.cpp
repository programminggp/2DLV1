#include "CEnemy.h"
//エフェクトクラスのインクルード
#include "CEffect.h"
//
#include "CSceneGame.h"
//
#include "CBullet.h"

//スマートポインタの外部参照
extern std::shared_ptr<CTexture> TextureExp;

//誘導ポイント
//CPoint *CEnemy::mPoint;
//int CEnemy::mPointSize = 0;

#define TURN_DEG 0.4f

#define VELOCITY 4.4f

#define POINTTIME 120

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.4f)
, mSearch(this, CVector(0.0f, 0.0f, 200.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 20.0f)
, mHp(20)
, mPointCnt(0)
, mpPoint(0)
, mFireBullet(0)
{
	//
	mCollider.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	mTag = EENEMY;
	mpPoint = &CPlayer::sPlayer->mPosition;

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
		if (mpPoint) {
			mPoint = *mpPoint;
		}
		else {
			mPoint = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
		}
//		mPointCnt = rand() % 120;
		mPointCnt = POINTTIME;
	}
	dir = mPoint - mPosition;

	//左方向のベクトルを求める
//	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrix - CVector() * mMatrix;
	left = left.Normalize();
	//上方向のベクトルを求める
//	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
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
		//if (z.Dot(dir) > 0.0) {
		//	mRotation.mX += TURN_DEG;
		//}
		//else {
		//	mRotation.mX -= TURN_DEG;
		//}
	}
	else if (up.Dot(dir) < 0.0f) {
		if (z.Dot(dir) > 0.0) {
			mRotation.mX += TURN_DEG;
		}
		//if (z.Dot(dir) > 0.0) {
		//	mRotation.mX -= TURN_DEG;
		//}
		//else {
		//	mRotation.mX += TURN_DEG;
		//}
	}

	//行列を更新
	CCharacter::Update();
	//位置を移動
	mPosition = CVector(0.0f, 0.0f, VELOCITY) * mMatrix;
	//回転させる
//	mRotation.mY += 0.5f;

	if (mHp < 0) {
		mHp--;
		mRotation.mX = 25;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 2.5f, 2.5f, TextureExp, 4, 4, 2);
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
//					mEnabled = false;
				case EBULLET:
					if (y->mTag == CCollider::EBODY) {
						//エフェクト生成
						new CEffect(mPosition, 2.0f, 2.0f, TextureExp, 4, 4, 1);
						mHp--;
					}
				}
			}
			//削除		mEnabled = false;
		}
	}
}
