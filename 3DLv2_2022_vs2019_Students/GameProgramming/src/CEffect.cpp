#include "CEffect.h"

CMaterial CEffect::sMaterial; //マテリアル.テクスチャ

CEffect::CEffect(const CVector& pos, float w, float h, char* texture, int row, int col, int fps)
	: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0), mFadeCount(0)
{
	//テクスチャを読んでない場合は読む
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
	//コマ数の計算
	int frame = mFrame++ / mFps;
	if (frame == mRows * mCols)
	{
		mEnabled = false;
		return;
	}
	frame %= (mRows * mCols);
	//UV左
	float left = 1.0f / mCols * (frame % mCols);
	//UV右
	float right = left + 1.0f / mCols;
	//UV上
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV下
	float bot = top - 1.0f / mRows;
	//テクスチャマッピング
	mT[0].SetUv(CVector(right, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, bot, 0.0f));
	mT[1].SetUv(CVector(left, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, top, 0.0f));
	//ビルボード更新
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
	//コマ数の計算
	int frame = mFrame;
	//UV左
	float left = 1.0f / mCols * (frame % mCols);
	//UV右
	float right = left + 1.0f / mCols;
	//UV上
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV下
	float bot = top - 1.0f / mRows;
	//テクスチャマッピング
	mT[0].SetUv(CVector(right, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, bot, 0.0f));
	mT[1].SetUv(CVector(left, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, top, 0.0f));
	//ビルボード更新
	CBillBoard::Update();
}

void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST); //深度テスト無効
	CBillBoard::Render(&sMaterial);
	glEnable(GL_DEPTH_TEST); //深度テスト有効
}

void CEffect::Render(CMaterial* material)
{
	if (mType == EFADE)
	{
		material->Diffuse()[3] = 1.0f - ((float)mFadeCount / mFps);
	}
	glDisable(GL_DEPTH_TEST); //深度テスト無効
	CBillBoard::Render(material);
	glEnable(GL_DEPTH_TEST); //深度テスト有効
}

#define DARKNESS17 "effects\\tktk_Darkness_17L.png"
CMaterial CEffectDarkness17::sMaterial; //マテリアル.テクスチャ

CEffectDarkness17::CEffectDarkness17(const CVector& pos, float w, float h, int row, int col, int fps)
	: CEffect(pos, w, h, row, col, fps)
{
	//テクスチャを読んでない場合は読む
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
CMaterial CEffectFire7::sMaterial; //マテリアル.テクスチャ

CEffectFire7::CEffectFire7(const CVector& pos, float w, float h, int row, int col, int fps, EType type, int frame)
	: CEffect(pos, w, h, row, col, fps, type, frame)
{
	//テクスチャを読んでない場合は読む
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
