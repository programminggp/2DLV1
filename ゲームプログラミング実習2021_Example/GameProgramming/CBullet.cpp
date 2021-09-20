#include "CBullet.h"
#include "CCollisionManager.h"

CBullet::CBullet()
: mLife(50)
, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
{}

//幅と奥行きの設定
//Set(幅, 奥行)
void CBullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定→3
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update() {
	//生存時間の判定
	if (mLife-- > 0) {
		CTransform::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else {
		//無効にする
		mEnabled = false;
	}
}

//描画
void CBullet::Render() {
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画→12
	mT.Render(mMatrix);
//	mCollider.Render();
}

//衝突処理
//Collision(コライダ1, コライダ2)
void CBullet::Collision(CCollider *m, CCollider *o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}

	//コライダのmとyが衝突しているか判定
	if (CCollider::Collision(m, o)) {
		//衝突している時は無効にする
		mEnabled = false;
	}

	return;

	if (m->mType == CCollider::ESPHERE
		&& o->mType == CCollider::ESPHERE)
	{
		switch (o->mTag)
		{
		case CCollider::ESEARCH:
			break;
		default:
			//コライダのmとyが衝突しているか判定
			if (CCollider::Collision(m, o)) {
				//衝突している時は無効にする
				mEnabled = false;
			}
		}
	}
}
void CBullet::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

