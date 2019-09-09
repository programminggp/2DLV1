#include "CBullet.h"

#define LIFE 120

CBullet::CBullet()
: mLife(LIFE)
{
	mCollider.mpParent = this;
}

void CBullet::Set(float x, float y, float z, float w, float h, float d) {
	mT[0].mV[0] = CVector(x + w, y, z + d);
	mT[0].mV[1] = CVector(x + w, y, z - d);
	mT[0].mV[2] = CVector(x - w, y, z - d);
	mT[0].SetNormal(0.0f, 1.0f, 0.0f);
	mT[1].mV[0] = CVector(x + w, y, z + d);
	mT[1].mV[1] = CVector(x - w, y, z - d);
	mT[1].mV[2] = CVector(x - w, y, z + d);
	mT[1].SetNormal(0.0f, 1.0f, 0.0f);
	mBox.Set(x, y, z, w, h, d);
	mCollider.mRadius = d;
	mCollider.mV[0] = CVector(0.0f, 0.0f, 0.0f);
}

void CBullet::SetDiffuse(float r, float g, float b, float a) {
	mBox.mMaterial.mDiffuse[0] = r;
	mBox.mMaterial.mDiffuse[1] = g;
	mBox.mMaterial.mDiffuse[2] = b;
	mBox.mMaterial.mDiffuse[3] = a;
}

void CBullet::Update() {
	if (mLife > 0) {
		mLife--;
		CCharacter::Update();
		mPosition = mPosition + CVector(0.0f, 0.0f, 0.8f) * mMatrixRotation;
	}
	else {
		mEnabled = false;
	}
}

void CBullet::Render() {
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);

	mT[0].Render(mMatrix);
	mT[1].Render(mMatrix);
	//mBox.Render(mMatrix);
}
