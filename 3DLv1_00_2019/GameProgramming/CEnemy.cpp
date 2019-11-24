#include "CEnemy.h"
//エフェクトクラスのインクルード
#include "CEffect.h"

//スマートポインタの外部参照
extern std::shared_ptr<CTexture> TextureExp;

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.8f),
//?SearchEnemy
mSearch1(this, CVector(0.0f, 0.0f, 100.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 5.0f),
mSearch2(this, CVector(0.0f, 0.0f, 200.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 10.0f),
mHp(20),
mRx(-0.1f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	//?SearchEnemy
	mCollider.mTag = CCollider::EBODY;
	mSearch1.mTag = CCollider::ESEARCH;
	mSearch2.mTag = CCollider::ESEARCH;
	mPoint[0].Set(CVector(35.0f, 5.0f, -150.0f));
	mPoint[1].Set(CVector(-100.0f, 60.0f, 0.0f));
	mPoint[2].Set(CVector(0.0f, 30.0f, 100.0f));
	mTarget = mPoint[0].mPosition;
}
//更新処理
void CEnemy::Update() {
	CVector dir = mTarget - mPosition;
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);

	if (left.Dot(dir) > 0.0f) {
		mRotation.mY += 0.2f;
	}
	else if (left.Dot(dir) < 0.0f) {
		mRotation.mY -= 0.2f;
	}
	if (up.Dot(dir) > 0.0f) {
		mRotation.mX -= 0.2f;
	}
	else if (up.Dot(dir) < 0.0f) {
		mRotation.mX += 0.2f;
	}

	//行列を更新
	CCharacter::Update();
	//位置を移動
	mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;

	if (mHp >= 0) {
		//if (mRotation.mX < -45.0f) {
		//	mRx *= -1.0f;
		//}
		//else if(mRotation.mX > 45.0f){
		//	mRx *= -1.0f;
		//}
		//mRotation.mX += mRx;

		////回転させる
		//mRotation.mY += 0.2f;
		//if (mRotation.mY > 360.0f) {
		//	mRotation.mY -= 360.0f;
		//}
	}
	else {
		mHp--;
		mRotation.mX = 20;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 1.5f, 1.5f, TextureExp, 4, 4, 2);
		}
	}
}

void CEnemy::Collision(CCollider *m, CCollider *y) {
	if (y->mTag == CCollider::ESEARCH) return;
	if (y->mTag == CCollider::EPOINT) return;
	if (CCollider::Collision(m, y)) {
		//エフェクト生成
		new CEffect(mPosition, 1.0f, 1.0f, TextureExp, 4, 4, 1);
		mHp--;
//削除		mEnabled = false;
	}
}
