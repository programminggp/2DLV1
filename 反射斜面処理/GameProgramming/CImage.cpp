#include "CImage.h"

CImage::CImage(std::shared_ptr<CTexture> texture, const CVector &pos, const CVector &rot, const CVector &sca)
: CBillBoard(pos, sca.mX, sca.mY)
{
	mMaterial.mpTexture = texture;
	mPosition = pos;
	mRotation = rot;
	mScale = sca;
	SetUv(0.0f, mMaterial.mpTexture->mHeader.width, mMaterial.mpTexture->mHeader.height, 0.0f);
	CCharacter::Update();
}

void CImage::SetUv(float left, float right, float bottom, float top) {
	left = left / mMaterial.mpTexture->mHeader.width;
	right = right / mMaterial.mpTexture->mHeader.width;
	bottom = 1.0f - bottom / mMaterial.mpTexture->mHeader.height;
	top = 1.0f - top / mMaterial.mpTexture->mHeader.height;
	mT[0].mUv[0] = CVector(right, top, 0.0f);
	mT[0].mUv[1] = CVector(left, bottom, 0.0f);
	mT[0].mUv[2] = CVector(right, bottom, 0.0f);
	mT[1].mUv[0] = CVector(left, top, 0.0f);
	mT[1].mUv[1] = CVector(left, bottom, 0.0f);
	mT[1].mUv[2] = CVector(right, top, 0.0f);
}

void CImage::Update() {
	CCharacter::Update();
}
