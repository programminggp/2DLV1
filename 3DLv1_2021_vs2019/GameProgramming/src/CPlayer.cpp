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
//
#include "CEffect.h"

CPlayer *CPlayer::spThis = 0;

#define FIRECOUNT 15	//発射間隔

#define ROTATION_YV	CVector(0.0f, 1.0f, 0.0f) //回転速度
#define ROTATION_XV	CVector(1.0f, 0.0f, 0.0f) //回転速度
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //移動速度

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f))
, mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f)
, mFireCount(0)
{
	mTag = EPLAYER;	//タグの設定
	spThis = this;
	//テクスチャファイルの読み込み（1行64列）
	mText.LoadTexture("FontWhite.tga", 1, 64);
}

//更新処理
void CPlayer::Update() {
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation = mRotation + ROTATION_YV;
	}
	if (CKey::Push('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATION_YV;
	}
	//Iキー入力で前進
	if (CKey::Push('I')) {
		//Z軸方向の値を回転させ移動させる
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//Sキー入力で上向き
	if (CKey::Push('S')) {
		//X軸の回転値を減算
		mRotation = mRotation - ROTATION_XV;
	}
	//Wキー入力で上向き
	if (CKey::Push('W')) {
		//X軸の回転値を加算
		mRotation = mRotation + ROTATION_XV;
	}

	if (mFireCount > 0)
	{
		mFireCount--;
	}

	//スペースキー入力で弾発射
	if (CKey::Push(VK_SPACE) && mFireCount == 0) {
		mFireCount = FIRECOUNT;
		CBullet *bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
//		TaskManager.Add(bullet);
	}

	//CTransformの更新
	CTransform::Update();
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
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
	case CCollider::ESPHERE:
		//相手のコライダが球コライダの時
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				//エフェクト生成
				new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			}
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
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//親の描画処理
	CCharacter::Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 1.0f, 0.0f, 0.99f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "PY:%7.2f", mPosition.Y());
	//文字列の描画
	mText.DrawString(buf, 100, 30, 8, 16);

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "RX:%7.2f", mRotation.X());
	//文字列の描画
	mText.DrawString(buf, 100, 0, 8, 16);
	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "FX:%7.2f", (CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate).GetRotationX(CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate));
	//文字列の描画
	mText.DrawString(buf, 100, -20, 8, 16);



	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "RY:%7.2f", mRotation.Y());
	//文字列の描画
	mText.DrawString(buf, 100, -100, 8, 16);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "FY:%7.2f", (CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate).GetRotationY());
	//文字列の描画
	mText.DrawString(buf, 100, -120, 8, 16);


	//2Dの描画終了
	CUtil::End2D();

}