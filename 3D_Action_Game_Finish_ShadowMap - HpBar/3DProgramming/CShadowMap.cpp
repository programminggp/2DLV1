#include "main.h"
#include "CTask.h"
#include "CShadowMap.h"

void CShadowMap::SetLight(const CVector3& pos, const CVector3& center, float fov) {
	mLightPosition = pos;
	mLightCenter = center;
	mFov = fov;
}

void CShadowMap::SetTextureSize(float width, float height) {
	mDepthTextureHeight = height;
	mDepthTextureWidth = width;
}

void CShadowMap::Init(float width, float height) {
	//�e�N�X�`���T�C�Y�ݒ�
	SetTextureSize(width, height);
	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE1);
	/* �e�N�X�`���I�u�W�F�N�g�𐶐����Č������� */
	glGenTextures(1, &mTex);
	glBindTexture(GL_TEXTURE_2D, mTex);

	//�f�v�X�e�N�X�`���̊��蓖��
	/* �e�N�X�`���̊��蓖�� */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mDepthTextureWidth, mDepthTextureHeight, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/* �e�N�X�`���̌J��Ԃ����@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	/* �������ރ|���S���̃e�N�X�`�����W�l�̂q�ƃe�N�X�`���Ƃ̔�r���s���悤�ɂ��� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	/* �����q�̒l���e�N�X�`���̒l�ȉ��Ȃ�^�i�܂�����j */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	/* ��r�̌��ʂ��P�x�l�Ƃ��ē��� */
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

	/* �e�N�X�`���I�u�W�F�N�g�̌������������� */
	glBindTexture(GL_TEXTURE_2D, 0);

	/* �t���[���o�b�t�@�I�u�W�F�N�g�𐶐����Č������� */
	glGenFramebuffersEXT(1, &mFb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFb);

	/* �t���[���o�b�t�@�I�u�W�F�N�g�Ƀf�v�X�o�b�t�@�p�̃e�N�X�`������������ */
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
		GL_TEXTURE_2D, mTex, 0);

	/* �J���[�o�b�t�@�������̂œǂݏ������Ȃ� */
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	/* �t���[���o�b�t�@�I�u�W�F�N�g�̌������������� */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	/* �e�N�X�`�����j�b�g0�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE0);

}

void CShadowMap::RenderInit() {
	/*
	** ��P�X�e�b�v�F�f�v�X�e�N�X�`���̍쐬
	*/

	/* �t���[���o�b�t�@�I�u�W�F�N�g�ւ̃����_�����O�J�n */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFb);

	/* �f�v�X�o�b�t�@���N���A���� */
	glClear(GL_DEPTH_BUFFER_BIT);

	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ肷�� */
	glViewport(0, 0, mDepthTextureWidth, mDepthTextureHeight);

	/* ���݂̓����ϊ��s���ۑ����Ă��� */
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	/* �����ϊ��s���P�ʍs��ɐݒ肷�� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* �����ʒu�����_�Ƃ��V�[��������Ɏ��܂�悤���f���r���[�ϊ��s���ݒ肷�� */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//�����ϊ��s��ݒ�
	gluPerspective(mFov, (GLdouble)mDepthTextureWidth / (GLdouble)mDepthTextureHeight, 1.0, 1000.0);
	//�J�����̐ݒ�
	//CVector3 vec = CLight::getLight(0)->getPosition();
	//gluLookAt(vec.x, vec.y, vec.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(mLightPosition.x, mLightPosition.y, mLightPosition.z, mLightCenter.x, mLightCenter.y, mLightCenter.z, 0.0, 1.0, 0.0);

	/* �ݒ肵�������ϊ��s��~���f���r���[�ϊ��s���ۑ����Ă��� */
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	/* �f�v�X�o�b�t�@�̓��e�������擾����̂Ńt���[���o�b�t�@�ɂ͏������܂Ȃ� */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* ���������ĉA�e�t�����s�v�Ȃ̂Ń��C�e�B���O���I�t�ɂ��� */
	glDisable(GL_LIGHTING);

	/* �f�v�X�o�b�t�@�ɂ͔w�ʂ̃|���S���̉��s�����L�^����悤�ɂ��� */
	glCullFace(GL_FRONT);
}

void CShadowMap::RenderBegin() {
	/* �t���[���o�b�t�@�I�u�W�F�N�g�ւ̃����_�����O�I�� */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	/**�S�̂̕`��**/
	/* �ʏ�̕`��̐ݒ�ɖ߂� */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projection);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/* �t���[���o�b�t�@�ƃf�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE1);

	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* �e�N�X�`�����W�� [-1,1] �͈̔͂� [0,1] �͈̔͂Ɏ��߂� */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);

	/* �e�N�X�`���̃��f���r���[�ϊ��s��Ɠ����ϊ��s��̐ς������� */
	glMultMatrixd(modelview);

	/* ���f���r���[�ϊ��s��ɖ߂� */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* �e�N�X�`���I�u�W�F�N�g���������� */
	glBindTexture(GL_TEXTURE_2D, mTex);

	/* �e�N�X�`���}�b�s���O��L���ɂ��� */
	glEnable(GL_TEXTURE_2D);

	/* �e�N�X�`�����j�b�g0�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE0);
}

void CShadowMap::RenderEnd() {
	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE1);
	/* �e�N�X�`���I�u�W�F�N�g�̌������������� */
	glBindTexture(GL_TEXTURE_2D, 0);
	/* �e�N�X�`���}�b�s���O�𖳌��ɂ��� */
	glDisable(GL_TEXTURE_2D);
	/* �e�N�X�`�����j�b�g0�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE0);
}
