#include "CEffect.h"
#include "CTaskManager.h"

CEffect::CEffect(const CVector &pos, float w, float h, std::shared_ptr<CTexture> texture, int row, int col, int fps, int blendtype)
: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0)
{
	mMaterial.mpTexture = texture;
	SetPriority(0);
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
	CBillBoard::mBlendType = blendtype;
}

void CEffect::Update() {
	//�R�}���̌v�Z
	int frame = mFrame++ / mFps;
	if (frame >= mRows * mCols)
		SetEnabled(false);
	frame %= (mRows * mCols);
	//UV��
	float left = 1.0f / mCols * (frame % mCols);
	//UV�E
	float righ = left + 1.0f / mCols;
	//UV��
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV��
	float bot = top - 1.0f / mRows;
	//�e�N�X�`���}�b�s���O
	mT[0].mUv[0] = CVector(righ, top, 0.0f);
	mT[0].mUv[1] = CVector(left, bot, 0.0f);
	mT[0].mUv[2] = CVector(righ, bot, 0.0f);
	mT[1].mUv[0] = CVector(left, top, 0.0f);
	mT[1].mUv[1] = CVector(left, bot, 0.0f);
	mT[1].mUv[2] = CVector(righ, top, 0.0f);
	//�r���{�[�h�X�V
	CBillBoard::Update();
	//�I������
	if (mFrame >= mFps * mRows * mCols) {
		SetEnabled(false);
	}
}
