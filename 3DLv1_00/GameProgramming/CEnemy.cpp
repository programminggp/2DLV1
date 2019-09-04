#include "CEnemy.h"
#include "CSceneGame.h"

#define VELOCITY_ENEMY 0.3f

CEnemy::CEnemy(CModel *model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) {
	Init(model, px, py, pz, rx, ry, rz, sx, sy, sz);
	TaskManager.Add(this);
}

void CEnemy::Update() {
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY_ENEMY) * mMatrixRotation;
	mRotation.mY += 0.5f;
	CCharacter::Update();
}