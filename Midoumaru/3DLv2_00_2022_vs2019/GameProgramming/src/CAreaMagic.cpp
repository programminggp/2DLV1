#include "CAreaMagic.h"
#include "CCollisionManager.h"
#include"CCollision.h"

CAreaMagic::CAreaMagic(const CVector& position, const CVector& rotation, const CVector& scale)
	: AMagicLife(40)
	, mCollider(this, &mMatrix, CVector(0.0f, 2.0f, 0.0f), 0.8f)
{
	Position(position);
	Rotation(rotation);
	Scale(scale);
	//	Set(scale.X(), scale.Y());
	mTag = EAREAMAGIC;
	mCollider.Tag(CCollider::EPLAYERAMAGIC);
}

//幅と奥行きの設定
//Set(幅, 奥行)
void CAreaMagic::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定→3
	mT.Vertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//三角形の法線設定
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CAreaMagic::Update() {
	//生存時間の判定
	if (AMagicLife-- > 0) {
		CTransform::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 0.3f) * mMatrix;
	}
	else {
		//無効にする
		mEnabled = false;
	}
}

//描画
void CAreaMagic::Render() {
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画→12
	mT.Render(mMatrix);
	mCollider.Render();
}

//衝突処理
//Collision(コライダ1, コライダ2)
void CAreaMagic::Collision(CCollider* m, CCollider* o) {
	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mEnabled = false;
		}
		if (o->Tag() == CCollider::ECORE) {
			mEnabled = false;
		}
	}
}
void CAreaMagic::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}