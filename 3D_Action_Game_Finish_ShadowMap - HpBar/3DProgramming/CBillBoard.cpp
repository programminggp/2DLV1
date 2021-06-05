#include "CBillBoard.h"
#include "CMatrix44.h"
#include "CCamera.h"

CBillBoard::CBillBoard(const CVector3 &position, const CVector3 &scale)
: mPosition(position)
, mScale(scale)
, mColor(1.0f, 1.0f, 1.0f, 1.0f)
, mpTexture(0)
{
	mPriority = ENONE - 1;
	CTaskManager::Get()->Add(this);
}

void CBillBoard::SetTexture(CTexture *t) {
	mpTexture = t;
	mUv[0].x = 0.0f; mUv[1].y = 0.0f;
	mUv[1].x = 0.0f; mUv[0].y = t->header.height;
	mUv[2].x = t->header.width; mUv[2].y = 0.0f;
	mUv[3].x = t->header.width; mUv[3].y = t->header.height;
}

void CBillBoard::Render() {
	//シャドウマップ作成中は描画しない
	if (mShadowMap) return;
	CMatrix44 scale;
	mMatrix.identity();
	mMatrix.translate(mPosition);
	scale.m00 = mScale.x;
	scale.m11 = mScale.y;
	scale.m22 = mScale.z;
	mMatrix = mMatrix * CCamera::mCameraInverse * scale;
	glPushMatrix();
	glMultMatrixf(mMatrix.f);
	glColor4f(mColor.x, mColor.y, mColor.z, mColor.w);
	glDisable(GL_LIGHTING);
	if (mpTexture) {
		mpTexture->DrawImage(-1.0f, 1.0f, -1.0f, 1.0f, mUv[0].x, mUv[2].x, mUv[2].y, mUv[0].y);
	}
	else {
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		//glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);
		//glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);
		//glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);
		//glVertex3f(mVertex[3].x, mVertex[3].y, mVertex[3].z);
		glEnd();
	}
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

//ヒットエフェクトのテクスチャ
CTexture CEffectHit::mTexEffectHit;
#define EFFECT_HIT_LIFE 8 //8フレームで消滅
#define EFFECT_HIT_SCALE 1.1f //1.1倍で拡大していく
//コンストラクタ
//position :描画位置座標 
//scale : 大きさ
CEffectHit::CEffectHit(const CVector3 &position, const CVector3 &scale)
: CBillBoard(position, scale)
, mLife(EFFECT_HIT_LIFE)
{
	SetTexture(&mTexEffectHit);
}
//更新処理
void CEffectHit::Update() {
	//寿命がきたら無効にする
	if (mLife < 0) {
		mEnabled = false;
		return;
	}
	mLife--;
	//大きくしていく
	mScale = mScale * EFFECT_HIT_SCALE;
}
//描画処理
void CEffectHit::Render() {
	if (mEnabled) {
		//白色→黄色へ
		if (mLife > EFFECT_HIT_LIFE / 3)
			mColor = CVector4(1.0f, 1.0f, 1.0f, 0.4f);
		else
			mColor = CVector4(1.0f, 1.0f, 0.0f, 0.2f);
		//描画する
		CBillBoard::Render();
	}
}

//ヒットエフェクトのテクスチャ
CTexture CEffectHit2::mTexEffectHit;
//コンストラクタ
//position :描画位置座標 
//scale : 大きさ
CEffectHit2::CEffectHit2(const CVector3 &position, const CVector3 &scale)
: CBillBoard(position, scale)
, mLife(EFFECT_HIT_LIFE), mRows(0), mCols(0)
{
	SetTexture(&mTexEffectHit);
}
//コンストラクタ
//position :描画位置座標 
//scale : 大きさ
CEffectHit2::CEffectHit2(const CVector3 &position, const CVector3 &scale, int rows, int cols)
: CBillBoard(position, scale)
, mLife(rows * cols), mRows(rows), mCols(cols)
{
	SetTexture(&mTexEffectHit);
	int cnt = mRows * mCols - mLife;
	int row = cnt / mCols;
	int col = cnt % mCols;
	mUv[0].x = mTexEffectHit.header.width * col++ / mCols;
	mUv[0].y = mTexEffectHit.header.height * row++ / mRows;
	mUv[2].x = mTexEffectHit.header.width * col / mCols;
	mUv[2].y = mTexEffectHit.header.height * row / mRows;

}
//更新処理
void CEffectHit2::Update() {
	//寿命がきたら無効にする
	if (mLife < 0) {
		mEnabled = false;
		return;
	}
	int cnt = mRows * mCols - mLife;
	int row = cnt / mCols;
	int col = cnt % mCols;
	mUv[0].x = mTexEffectHit.header.width * col++ / mCols;
	mUv[0].y = mTexEffectHit.header.height * row++ / mRows;
	mUv[2].x = mTexEffectHit.header.width * col / mCols;
	mUv[2].y = mTexEffectHit.header.height * row / mRows;
	mLife--;
}
//描画処理
void CEffectHit2::Render() {
	if (mEnabled) {
		mColor = CVector4(1.0f, 1.0f, 1.0f, 1.0f);
		//描画する
		CBillBoard::Render();
	}
}

//ヒットエフェクトのテクスチャ
CTexture CEffectHit3::mTexEffectHit;
//コンストラクタ
//position :描画位置座標 
//scale : 大きさ
CEffectHit3::CEffectHit3(const CVector3 &position, const CVector3 &scale)
: CBillBoard(position, scale)
, mLife(EFFECT_HIT_LIFE), mRows(0), mCols(0)
{
	SetTexture(&mTexEffectHit);
}
//コンストラクタ
//position :描画位置座標 
//scale : 大きさ
CEffectHit3::CEffectHit3(const CVector3 &position, const CVector3 &scale, int rows, int cols)
: CBillBoard(position, scale)
, mLife(rows * cols), mRows(rows), mCols(cols)
{
	SetTexture(&mTexEffectHit);
	int cnt = mRows * mCols - mLife;
	int row = cnt / mCols;
	int col = cnt % mCols;
	mUv[0].x = mTexEffectHit.header.width * col++ / mCols;
	mUv[0].y = mTexEffectHit.header.height * row++ / mRows;
	mUv[2].x = mTexEffectHit.header.width * col / mCols;
	mUv[2].y = mTexEffectHit.header.height * row / mRows;

}
//更新処理
void CEffectHit3::Update() {
	//寿命がきたら無効にする
	if (mLife < 0) {
		mEnabled = false;
		return;
	}
	int cnt = mRows * mCols - mLife;
	int row = cnt / mCols;
	int col = cnt % mCols;
	mUv[0].x = mTexEffectHit.header.width * col++ / mCols;
	mUv[0].y = mTexEffectHit.header.height * row++ / mRows;
	mUv[2].x = mTexEffectHit.header.width * col / mCols;
	mUv[2].y = mTexEffectHit.header.height * row / mRows;
	mLife--;
}
//描画処理
void CEffectHit3::Render() {
	if (mEnabled) {
		mColor = CVector4(1.0f, 1.0f, 1.0f, 1.0f);
		//描画する
		CBillBoard::Render();
	}
}


