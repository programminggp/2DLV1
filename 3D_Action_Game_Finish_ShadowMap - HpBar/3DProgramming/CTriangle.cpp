#include "CTriangle.h"
//#include "../Camera/CCamera.h"
//#include "../Convenient/CConvenient.h"
#include <cassert>


/*�R���X�g���N�^*/
CTriangle::CTriangle()
: mpTexture(0), r(1.0f), g(1.0f), b(1.0f), a(1.0f), mEnabled(false),mFlagSaveTex(false){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			mUv[i][j] = 0.0f;
		}
	}
}



//�J���[��ݒ�
void CTriangle::SetDiffuse(float cr, float cg, float cb, float ca){
	r = cr;
	g = cg;
	b = cb;
	a = ca;
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

/*�@���ݒ�*/
void CTriangle::SetNormal(float x, float y, float z){
	mNormal.x = x;
	mNormal.y = y;
	mNormal.z = z;
}

/*
SetUv
left	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̍��̍��W�l
top		�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̏�̍��W�l
right	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̉E�̍��W�l
bottom	�摜�̍���[�����_(0,0)�Ƃ��A�\��t�������̈�̉��̍��W�l
*/
void CTriangle::SetUv(CTexture *t, int left, int top, int right, int bottom) {
	mpTexture = t;
	mUv[0][0] = (float)left / mpTexture->header.width;
	mUv[0][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
	mUv[1][0] = (float)left / mpTexture->header.width;
	mUv[1][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[2][0] = (float)right / mpTexture->header.width;
	mUv[2][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[3][0] = (float)right / mpTexture->header.width;
	mUv[3][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;

	/*�e�N�X�`���̒l�ۑ�*/
	if (!mFlagSaveTex){
		mSaveInitTexVer[E_TOP] = top;
		mSaveInitTexVer[E_BOTTOM] = bottom;
		mSaveInitTexVer[E_LEFT] = left;
		mSaveInitTexVer[E_RIGHT] = right;
		mFlagSaveTex = true;
	}
	mSaveTexVer[E_TOP] = top;
	mSaveTexVer[E_BOTTOM] = bottom;
	mSaveTexVer[E_LEFT] = left;
	mSaveTexVer[E_RIGHT] = right;
}
/*��]������悤*/
void CTriangle::SetUvRot() {

	float saveUv0[2] = { mUv[0][0], mUv[0][1] };
	mUv[0][0] = mUv[3][0];
	mUv[0][1] = mUv[3][1];

	float saveUv2[2] = { mUv[2][2], mUv[2][1] };
	mUv[2][0] = mUv[1][0];
	mUv[2][1] = mUv[1][1];

	mUv[1][0] = saveUv0[0];
	mUv[1][1] = saveUv0[1];

	mUv[3][0] = saveUv2[0];
	mUv[3][1] = saveUv2[1];
}
/*
SetVertex
v0�`v3�F���_�P�`�S�܂ł̍��W
*/
void CTriangle::SetVertex(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2) {
	mEnabled = true;//�ݒ肳�ꂽ
	mVertex[E_LEFT_TOP] = v0;
	mVertex[E_LEFT_BOTTOM] = v1;
	mVertex[E_RIGHT_BOTTOM] = v2;
}



//�`�悷��
void CTriangle::Render() {
	if (mpTexture == 0) {
		////�`��F��ݒ�
		glColor4f(r, g, b, a);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glNormal3f(mNormal.x, mNormal.y, mNormal.z);
		//�O�p�`�̕`��
		glBegin(GL_TRIANGLES);	//�O�p�`�̒��_�w��J�n
		glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);	//���_�̎w��
		glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);	//���_�̎w��
		glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);	//���_�̎w��

		glEnd();	//���_�w��I��

	}
	else {
		//�e�N�X�`����L���ɂ���
		glEnable(GL_TEXTURE_2D);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//�e�N�X�`�����w��
		glBindTexture(GL_TEXTURE_2D, mpTexture->id);


		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glNormal3f(mNormal.x, mNormal.y, mNormal.z);

		glBegin(GL_TRIANGLES);	//�O�p�`�̒��_�w��J�n

		glTexCoord2fv(mUv[0]);	//���_�̃e�N�X�`���}�b�s���O
		glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);	//���_�̎w��
		glTexCoord2fv(mUv[1]);	//���_�̃e�N�X�`���}�b�s���O
		glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);	//���_�̎w��
		glTexCoord2fv(mUv[2]);	//���_�̃e�N�X�`���}�b�s���O
		glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);	//���_�̎w��

		glEnd();	//���_�w��I��

		//�e�N�X�`�������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���𖳌�
		glDisable(GL_TEXTURE_2D);
	}
}


/*�t�F�[�h�֐�*/
#define SET_C3 r,g,b //���̎l�p�`rgb


void CTriangle::Fade(float speed, float alaha){
	float mFade4 = a + speed;		//�t�F�[�h�֐��Ŏg��
	mFade4 += speed;
	if (mFade4 >= alaha){
		mFade4 = alaha;
	}
	SetDiffuse(SET_C3, mFade4);
}

/*�t�F�[�h�֐�*/
void CTriangle::FadeOut(float speed, float alaha){
	float mFade4 = a - speed;		//�t�F�[�h�֐��Ŏg��
	mFade4 -= speed;
	if (mFade4 <= alaha){
		mFade4 = alaha;
	}
	SetDiffuse(SET_C3, mFade4);
}


/*�e�N�X�`�����X�N���[���֐�*/
void CTriangle::TexSideScroll(float speed){
	float left, top, right, bottom;
	/*�ۑ�*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	right = mSaveTexVer[E_RIGHT];
	bottom = mSaveTexVer[E_BOTTOM];
	/*�v�Z*/
	//CConvenient::LoopPlus(&left, speed, mSaveInitTexVer[E_RIGHT], mSaveInitTexVer[E_LEFT]);
	//CConvenient::LoopPlus(&right, speed, mSaveInitTexVer[E_RIGHT], mSaveInitTexVer[E_LEFT]);
	SetUv(mpTexture, left, top, right, bottom);
		
}


/*�e�N�X�`���c�X�N���[���֐�*/
void CTriangle::TexVerticalScroll(float speed){
	float left, top, right, bottom;
	/*�ۑ�*/
	left = mSaveTexVer[E_LEFT];
	top = mSaveTexVer[E_TOP];
	right = mSaveTexVer[E_RIGHT];
	bottom = mSaveTexVer[E_BOTTOM];
	/*�v�Z*/
	//CConvenient::LoopPlus(&top, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	//CConvenient::LoopPlus(&bottom, speed, mSaveInitTexVer[E_TOP], mSaveInitTexVer[E_BOTTOM]);
	SetUv(mpTexture, left, top, right, bottom);

}