#include "CBullet.h"
//
#include "CTaskManager.h"

//幅と奥行きの設定
//Set(幅, 奥行)
void CBullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
	//
	CCharacter::Update();
}

//更新
void CBullet::Update() {
	//生存時間の判定
	if (mLife-- > 0) {
		CCharacter::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 0.7f) * mMatrix;
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
	//三角形描画
	mT.Render(mMatrix);
//	mCollider.Render();
}
//22
CBullet::CBullet()
: mLife(70)
, mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{
	//?
	//
	mCollider.mTag = CCollider::EBODY;
	mTag = EBULLET;
	Set(0.05f, 1.5f);
}

CBullet::CBullet(CVector &pos, CVector &rot)
: CBullet()
{
	mPosition = pos;
	mRotation = rot;
	Set(0.05f, 1.5f);
}

//衝突処理
//Collision(コライダ1, コライダ2)
void CBullet::Collision(CCollider *m, CCollider *y) {
	//共に球コライダの時
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, y)) {
			//機体の時
			if (y->mTag == CCollider::EBODY) {
				//衝突している時は無効にする
				mEnabled = false;
			}
		}
	}
}