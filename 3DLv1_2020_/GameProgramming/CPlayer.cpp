//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"
//
#include "CBullet.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
//
#include "CUtil.h"

CPlayer *CPlayer::spThis = 0;

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
{
	spThis = this;
	//
	mText.LoadTexture("FontWhite.tga", 1, 4096 / 64);
}

//更新処理
void CPlayer::Update() {
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation.mY += 1;
	}
	if (CKey::Push('D')) {
		//Y軸の回転値を増加
		mRotation.mY -= 1;
	}
	//上矢印キー入力で前進
	if (CKey::Push(VK_UP)) {
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
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
		bullet->Update();
//		TaskManager.Add(bullet);
	}

	//CTransformの更新
	CTransform::Update();
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
	//自身のコライダタイプの判定
	switch (m->mType) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition - adjust * -1;
			//行列の更新
			CTransform::Update();
		}
		break;
	}
}
//衝突処理
void CPlayer::TaskCollision()
{
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//親の描画処理
	CCharacter::Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//文字列編集エリアの作成
	char buf[64];

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "RX:%7.2f", mRotation.mX);
	//文字列の描画
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "RY:%7.2f", mRotation.mY);
	//文字列の描画
	mText.DrawString(buf, 100, -100, 8, 16);

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//文字列の描画
	mText.DrawString(buf, 100, 30, 8, 16);

	CUtil::End2D();

}