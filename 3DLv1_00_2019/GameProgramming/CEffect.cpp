#include "CEffect.h"

CEffect::CEffect() {
}

CEffect::CEffect(const CVector &pos, float w, float h, std::shared_ptr<CTexture> texture, int row, int col, int fps)
: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0)
{
	mMaterial.mpTexture = texture;
}

void CEffect::Update() {
	//
	int frame = mFrame++ / mFps;
	frame %= (mRows * mCols);
	float left = 1.0f / mCols * (frame % mCols);
	float righ = left + 1.0f / mCols;
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	float bot = top - 1.0f / mRows;
	//
	mT[0].mUv[0] = CVector(righ, top, 0.0f);
	mT[0].mUv[1] = CVector(left, bot, 0.0f);
	mT[0].mUv[2] = CVector(righ, bot, 0.0f);
	mT[1].mUv[0] = CVector(left, top, 0.0f);
	mT[1].mUv[1] = CVector(left, bot, 0.0f);
	mT[1].mUv[2] = CVector(righ, top, 0.0f);
	//
	CBillBoard::Update();
	//
	if (mFrame >= mFps * mRows * mCols) {
		mEnabled = false;
	}
}
