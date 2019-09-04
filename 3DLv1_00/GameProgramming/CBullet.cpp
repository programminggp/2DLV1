#include "CBullet.h"

#define LIFE 120

CBullet::CBullet()
: mLife(LIFE)
{
}

void CBullet::Set(float x, float y, float z, float w, float h, float d) {
	mBox.Set(x, y, z, w, h, d);
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
	mBox.Render(mMatrix);
}
