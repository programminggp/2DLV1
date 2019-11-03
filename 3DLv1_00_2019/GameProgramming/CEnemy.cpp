#include "CEnemy.h"

//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//CEnemy(ƒ‚ƒfƒ‹, ˆÊ’u, ‰ñ“], Šgk)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.8f)
{
	//ƒ‚ƒfƒ‹AˆÊ’uA‰ñ“]AŠgk‚ðÝ’è‚·‚é
	mpModel = model;	//ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position;	//ˆÊ’u‚ÌÝ’è
	mRotation = rotation;	//‰ñ“]‚ÌÝ’è
	mScale = scale;	//Šgk‚ÌÝ’è
}
//XVˆ—
void CEnemy::Update() {
	//s—ñ‚ðXV
	CCharacter::Update();
	//ˆÊ’u‚ðˆÚ“®
	mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	//‰ñ“]‚³‚¹‚é
	mRotation.mY += 0.5f;
}

void CEnemy::Collision(CCollider *m, CCollider *y) {
	CVector mpos = CVector() * m->mMatrix * m->mpParent->mMatrix;
	CVector ypos = CVector() * y->mMatrix * y->mpParent->mMatrix;
	mpos = mpos - ypos;
	if (m->mRadius + y->mRadius > mpos.Length()) {
		mEnabled = false;
		printf("CEnemy Hit!\n");
	}
}