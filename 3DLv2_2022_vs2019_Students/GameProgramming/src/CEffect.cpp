#include "CEffect.h"

CMaterial CEffect::sMaterial; //�}�e���A��.�e�N�X�`��

CEffect::CEffect(const CVector& pos, float w, float h, char* texture, int row, int col, int fps)
	: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0), mFadeCount(0)
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
CEffect::CEffect(const CVector& pos, float w, float h, int row, int col, int fps, EType type, int frame)
	: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(frame), mType(type), mFadeCount(0)
{
}

void CEffect::Update() {
	switch (mType)
	{
	case EANIMATION:
		Animation();
		break;
	case EFADE:
		Fade();
		break;
	}
}

void CEffect::Animation()
{
	//�R�}���̌v�Z
	int frame = mFrame++ / mFps;
	if (frame == mRows * mCols)
	{
		mEnabled = false;
		return;
	}
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
	mT[0].SetUv(CVector(right, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, bot, 0.0f));
	mT[1].SetUv(CVector(left, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, top, 0.0f));
	//�r���{�[�h�X�V
	CBillBoard::Update();
}

void CEffect::Fade()
{
	mFadeCount++;
	if (mFadeCount > mFps)
	{
		mEnabled = false;
		return;
	}
	//�R�}���̌v�Z
	int frame = mFrame;
	//UV��
	float left = 1.0f / mCols * (frame % mCols);
	//UV�E
	float right = left + 1.0f / mCols;
	//UV��
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV��
	float bot = top - 1.0f / mRows;
	//�e�N�X�`���}�b�s���O
	mT[0].SetUv(CVector(right, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, bot, 0.0f));
	mT[1].SetUv(CVector(left, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, top, 0.0f));
	//�r���{�[�h�X�V
	CBillBoard::Update();
}

void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST); //�[�x�e�X�g����
	CBillBoard::Render(&sMaterial);
	glEnable(GL_DEPTH_TEST); //�[�x�e�X�g�L��
}

void CEffect::Render(CMaterial* material)
{
	if (mType == EFADE)
	{
		material->Diffuse()[3] = 1.0f - ((float)mFadeCount / mFps);
	}
	glDisable(GL_DEPTH_TEST); //�[�x�e�X�g����
	CBillBoard::Render(material);
	glEnable(GL_DEPTH_TEST); //�[�x�e�X�g�L��
}

#define DARKNESS17 "effects\\tktk_Darkness_17L.png"
CMaterial CEffectDarkness17::sMaterial; //�}�e���A��.�e�N�X�`��

CEffectDarkness17::CEffectDarkness17(const CVector& pos, float w, float h, int row, int col, int fps)
	: CEffect(pos, w, h, row, col, fps)
{
	//�e�N�X�`����ǂ�łȂ��ꍇ�͓ǂ�
	if (sMaterial.Texture()->Id() == 0)
	{
		sMaterial.Texture()->Load(DARKNESS17);
		sMaterial.Diffuse()[0] = 1.0f;
		sMaterial.Diffuse()[1] = 1.0f;
		sMaterial.Diffuse()[2] = 1.0f;
		sMaterial.Diffuse()[3] = 1.0f;
	}
}

void CEffectDarkness17::Render()
{
	CEffect::Render(&sMaterial);
}

#define FIRE7 "effects\\tktk_Fire_7L.png"
CMaterial CEffectFire7::sMaterial; //�}�e���A��.�e�N�X�`��

CEffectFire7::CEffectFire7(const CVector& pos, float w, float h, int row, int col, int fps, EType type, int frame)
	: CEffect(pos, w, h, row, col, fps, type, frame)
{
	//�e�N�X�`����ǂ�łȂ��ꍇ�͓ǂ�
	if (sMaterial.Texture()->Id() == 0)
	{
		sMaterial.Texture()->Load(FIRE7);
		sMaterial.Diffuse()[0] = 1.0f;
		sMaterial.Diffuse()[1] = 1.0f;
		sMaterial.Diffuse()[2] = 1.0f;
		sMaterial.Diffuse()[3] = 1.0f;
	}
	sMaterial.Diffuse()[3] = 1.0f;
}

void CEffectFire7::Render()
{
	CEffect::Render(&sMaterial);
}
