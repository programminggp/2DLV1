#include "CFire.h"

void CFire::SetSize(float w, float h) {
	//mT[0].SetVertex(-w, -h, 0.0f, w, -h, 0.0f, w, h, 0.0f);
	//mT[1].SetVertex(-w, -h, 0.0f, w, h, 0.0f, -w, h, 0.0f);
	//mT[0].SetNormal(0.0f, 0.0f, 1.0f);
	//mT[1].SetNormal(0.0f, 0.0f, 1.0f);
	mT[0].SetVertex(0.0f, -h, -w, 0.0f, -h, w, 0.0f, h, w);
	mT[1].SetVertex(0.0f, -h, -w, 0.0f, h, w, 0.0f, h, -w);
	mT[0].SetNormal(-1.0f, 0.0f, 0.0f);
	mT[1].SetNormal(-1.0f, 0.0f, 0.0f);
}

void CFire::Render() {
	mMaterial.SetMaterial();
	mT[0].Render(mMatrix);
	mT[1].Render(mMatrix);
	mMaterial.UnSetMaterial();
}

void CFire::SetTexture(char *tga) {
	mMaterial.mTexture.Load(tga);

	mT[0].mUv[0].mX = 0.0f;
	mT[0].mUv[0].mY = 0.0f;
	mT[0].mUv[1].mX = 1.0f;
	mT[0].mUv[1].mY = 0.0f;
	mT[0].mUv[2].mX = 1.0f;
	mT[0].mUv[2].mY = 1.0f;

	mT[1].mUv[0].mX = 0.0f;
	mT[1].mUv[0].mY = 0.0f;
	mT[1].mUv[1].mX = 1.0f;
	mT[1].mUv[1].mY = 1.0f;
	mT[1].mUv[2].mX = 0.0f;
	mT[1].mUv[2].mY = 1.0f;
}

void CFire::SetDiffuse(float r, float g, float b, float a) {
	mMaterial.mDiffuse[0] = r;
	mMaterial.mDiffuse[1] = g;
	mMaterial.mDiffuse[2] = b;
	mMaterial.mDiffuse[3] = a;
}

CFire::CFire() {
	SetSize(1.0f, 1.0f);
	SetDiffuse(10.f, 1.0f, 1.0f, 1.0);
}
