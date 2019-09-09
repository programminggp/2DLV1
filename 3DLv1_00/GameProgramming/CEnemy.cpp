#include "CEnemy.h"
#include "CSceneGame.h"
#include "CFire.h"

#define VELOCITY_ENEMY 0.3f

CEnemy::CEnemy(CModel *model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) {
	Init(model, px, py, pz, rx, ry, rz, sx, sy, sz);
	TaskManager.Add(this);
	mCollider.mpParent = this;
	mCollider.mRadius = 1.0f;
}

void CEnemy::Update() {
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY_ENEMY) * mMatrixRotation;
	mRotation.mY += 0.5f;
	CCharacter::Update();
}

void CEnemy::Collision(CCollider *m, CCollider *y) {
	if (CCollider::Collision(m, y)) {
		CFire *f = new CFire();
		f->mPosition = y->mpParent->mPosition;
		f->SetTexture("fire.tga");
		TaskManager.Add(f);
	}
}
