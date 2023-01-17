#include "CSingleMagic.h"
#include "CCollisionManager.h"
#include"CCollision.h"

#define MODEL_FireBall "res\\FireBall.obj","res\\FireBall.mtl"

CSingleMagic::CSingleMagic(const CVector& position, const CVector& rotation, const CVector& scale)
	: SMagicLife(45)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.9f, 0.0f), 1.0f)
{
	if (mFireBall.Triangles().size() == 0){
		mFireBall.Load(MODEL_FireBall);
	}
	
	mpModel = &mFireBall;
	Position(position);
	Rotation(rotation);
	Scale(scale);

	mTag = ESINGLEMAGIC;
	mCollider.Tag(CCollider::EPLAYERSMAGIC);
}

//幅と奥行きの設定
//Set(幅, 奥行)
void CSingleMagic::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

//更新
void CSingleMagic::Update() {
	CTransform::Update();
	//生存時間の判定
	if (SMagicLife-- > 0) {
		CTransform::Update();
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 0.4f) * mMatrix;
	}
	else {
		//無効にする
		mEnabled = false;
	}
}

//描画
void CSingleMagic::Render() {
	CCharacter::Render();
	return;
	////DIFFUSE黄色設定
	//float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	////三角形描画→12
	//mT.Render(mMatrix);
	//mCollider.Render();
}

//衝突処理
//Collision(コライダ1, コライダ2)
void CSingleMagic::Collision(CCollider* m, CCollider* o) {
	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mEnabled = false;
		}
		if (o->Tag()==CCollider::ECORE){
			mEnabled = false;
		}
	}
}
void CSingleMagic::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

