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
	//�V���h�E�}�b�v�쐬���͕`�悵�Ȃ�
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

//�q�b�g�G�t�F�N�g�̃e�N�X�`��
CTexture CEffectHit::mTexEffectHit;
#define EFFECT_HIT_LIFE 8 //8�t���[���ŏ���
#define EFFECT_HIT_SCALE 1.1f //1.1�{�Ŋg�債�Ă���
//�R���X�g���N�^
//position :�`��ʒu���W 
//scale : �傫��
CEffectHit::CEffectHit(const CVector3 &position, const CVector3 &scale)
: CBillBoard(position, scale)
, mLife(EFFECT_HIT_LIFE)
{
	SetTexture(&mTexEffectHit);
}
//�X�V����
void CEffectHit::Update() {
	//�����������疳���ɂ���
	if (mLife < 0) {
		mEnabled = false;
		return;
	}
	mLife--;
	//�傫�����Ă���
	mScale = mScale * EFFECT_HIT_SCALE;
}
//�`�揈��
void CEffectHit::Render() {
	if (mEnabled) {
		//���F�����F��
		if (mLife > EFFECT_HIT_LIFE / 3)
			mColor = CVector4(1.0f, 1.0f, 1.0f, 0.4f);
		else
			mColor = CVector4(1.0f, 1.0f, 0.0f, 0.2f);
		//�`�悷��
		CBillBoard::Render();
	}
}

//�q�b�g�G�t�F�N�g�̃e�N�X�`��
CTexture CEffectHit2::mTexEffectHit;
//�R���X�g���N�^
//position :�`��ʒu���W 
//scale : �傫��
CEffectHit2::CEffectHit2(const CVector3 &position, const CVector3 &scale)
: CBillBoard(position, scale)
, mLife(EFFECT_HIT_LIFE), mRows(0), mCols(0)
{
	SetTexture(&mTexEffectHit);
}
//�R���X�g���N�^
//position :�`��ʒu���W 
//scale : �傫��
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
//�X�V����
void CEffectHit2::Update() {
	//�����������疳���ɂ���
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
//�`�揈��
void CEffectHit2::Render() {
	if (mEnabled) {
		mColor = CVector4(1.0f, 1.0f, 1.0f, 1.0f);
		//�`�悷��
		CBillBoard::Render();
	}
}

//�q�b�g�G�t�F�N�g�̃e�N�X�`��
CTexture CEffectHit3::mTexEffectHit;
//�R���X�g���N�^
//position :�`��ʒu���W 
//scale : �傫��
CEffectHit3::CEffectHit3(const CVector3 &position, const CVector3 &scale)
: CBillBoard(position, scale)
, mLife(EFFECT_HIT_LIFE), mRows(0), mCols(0)
{
	SetTexture(&mTexEffectHit);
}
//�R���X�g���N�^
//position :�`��ʒu���W 
//scale : �傫��
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
//�X�V����
void CEffectHit3::Update() {
	//�����������疳���ɂ���
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
//�`�揈��
void CEffectHit3::Render() {
	if (mEnabled) {
		mColor = CVector4(1.0f, 1.0f, 1.0f, 1.0f);
		//�`�悷��
		CBillBoard::Render();
	}
}


