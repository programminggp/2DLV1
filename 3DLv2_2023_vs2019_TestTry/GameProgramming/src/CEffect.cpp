#include "CEffect.h"
CMaterial CEffect::sMaterial; //�}�e���A��.�e�N�X�`��

#define PRIORITY 100 //�D��x

CEffect::CEffect(const CVector& pos, float w, float h, char* texture
	, int row, int col, int fps)
	: CBillBoard(pos, w, h, PRIORITY), mRows(row), mCols(col), mFps(fps), mFrame(0),mIndex(0),mDispframe(0)
{
	//�e�N�X�`����ǂ�łȂ��ꍇ�͓ǂ�
	if (sMaterial.Texture()->Id() == 0)
	{
		sMaterial.Texture()->Load(texture);
		sMaterial.Diffuse()[0] = 1.0f;
		sMaterial.Diffuse()[1] = 1.0f;
		sMaterial.Diffuse()[2] = 1.0f;
		sMaterial.Diffuse()[3] = 1.0f;
	}
}

void CEffect::Update() {
	//�R�}���̌v�Z
	int frame = mFrame++ / mFps;
	frame %= (mRows * mCols);
	//UV��
	float left = 1.0f / mCols * (frame % mCols);
	//UV�E
	float right = left + 1.0f / mCols;
	//UV��
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV��
	float bot = top - 1.0f / mRows;
	//�e�N�X�`���}�b�s���O
	mT[0].UV(CVector(right, top, 0.0f), CVector(left, bot, 0.0f),
		CVector(right, bot, 0.0f));
	mT[1].UV(CVector(left, top, 0.0f), CVector(left, bot, 0.0f),
		CVector(right, top, 0.0f));
	//�r���{�[�h�X�V
	CBillBoard::Update();

	if (mFrame >= mRows * mCols * mFps)
	{
		mEnabled = false;
	}
}

void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST); //�[�x�e�X�g����
	CBillBoard::Render(&sMaterial);
	glEnable(GL_DEPTH_TEST); //�[�x�e�X�g�L��
}

CEffect2::CEffect2(const CVector& pos, float w, float h, CMaterial* material, int row, int col, int fps, int index, int dispframe)
	: CBillBoard(pos, w, h, PRIORITY), mpMaterial(material), mRows(row), mCols(col), mFps(fps), mFrame(0), mIndex(index), mDispframe(dispframe)
{
	mDiffuse[0] = mDiffuse[1] = mDiffuse[2] = mDiffuse[3] = 1.0f;
	mDiffuse[3] = 0.5f;
}

void CEffect2::Update()
{
	mpMaterial->Diffuse()[0] = mDiffuse[0];
	mpMaterial->Diffuse()[1] = mDiffuse[1];
	mpMaterial->Diffuse()[2] = mDiffuse[2];
	mpMaterial->Diffuse()[3] = mDiffuse[3];
	if (mFps)
	{
		//�R�}���̌v�Z
		int frame = mFrame++ / mFps;
		frame %= (mRows * mCols);
		//UV��
		float left = 1.0f / mCols * (frame % mCols);
		//UV�E
		float right = left + 1.0f / mCols;
		//UV��
		float top = 1.0f - 1.0f / mRows * (frame / mCols);
		//UV��
		float bot = top - 1.0f / mRows;
		//�e�N�X�`���}�b�s���O
		mT[0].UV(CVector(right, top, 0.0f), CVector(left, bot, 0.0f),
			CVector(right, bot, 0.0f));
		mT[1].UV(CVector(left, top, 0.0f), CVector(left, bot, 0.0f),
			CVector(right, top, 0.0f));
		//�r���{�[�h�X�V
		CBillBoard::Update();

		if (mFrame >= mRows * mCols * mFps)
		{
			mEnabled = false;
		}

	}
	else
	{
		//�R�}���̌v�Z
		int frame = mIndex;
		frame %= (mRows * mCols);
		//UV��
		float left = 1.0f / mCols * (frame % mCols);
		//UV�E
		float right = left + 1.0f / mCols;
		//UV��
		float top = 1.0f - 1.0f / mRows * (frame / mCols);
		//UV��
		float bot = top - 1.0f / mRows;
		//�e�N�X�`���}�b�s���O
		mT[0].UV(CVector(right, top, 0.0f), CVector(left, bot, 0.0f),
			CVector(right, bot, 0.0f));
		mT[1].UV(CVector(left, top, 0.0f), CVector(left, bot, 0.0f),
			CVector(right, top, 0.0f));
		//�r���{�[�h�X�V
		CBillBoard::Update();
		mDiffuse[3] -= 0.5f / mDispframe;
		if (mDiffuse[3] < 0.0f)
		{
			mEnabled = false;
		}
	}
}

void CEffect2::Render()
{
	glDisable(GL_DEPTH_TEST); //�[�x�e�X�g����
	CBillBoard::Render(mpMaterial);
	glEnable(GL_DEPTH_TEST); //�[�x�e�X�g�L��
}

