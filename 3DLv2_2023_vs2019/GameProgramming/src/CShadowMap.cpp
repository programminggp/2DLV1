#include "glew.h"
#include "CShadowMap.h"
#include "CMatrix.h"

void CShadowMap::Init()
{
	/* �e�N�X�`�����j�b�g�P��Depth�e�N�X�`���Ŏg�p */
	glActiveTexture(GL_TEXTURE1);
	//�e�N�X�`���̐���
	glGenTextures(1, &mDepthTextureID);
	//�g�p����e�N�X�`���̃o�C���h
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);

	/* Depth�e�N�X�`���̊��蓖�� */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mTextureWidth, mTextureHeight, 0,
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

	/*��r�̌��ʂ��A���t�@�l�Ƃ��ē���*/
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_ALPHA);
	/* �A���t�@�e�X�g�̔�r�֐��i�������l�j */
	glAlphaFunc(GL_GEQUAL, 0.5f);

	/* �e�N�X�`�����W�Ɏ��_���W�n�ɂ����镨�̂̍��W�l��p���� */
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

	/* ���������e�N�X�`�����W�����̂܂� (S, T, R, Q) �Ɏg�� */
	static const GLdouble genfunc[][4] = {
	  { 1.0, 0.0, 0.0, 0.0 },
	  { 0.0, 1.0, 0.0, 0.0 },
	  { 0.0, 0.0, 1.0, 0.0 },
	  { 0.0, 0.0, 0.0, 1.0 },
	};
	glTexGendv(GL_S, GL_EYE_PLANE, genfunc[0]);
	glTexGendv(GL_T, GL_EYE_PLANE, genfunc[1]);
	glTexGendv(GL_R, GL_EYE_PLANE, genfunc[2]);
	glTexGendv(GL_Q, GL_EYE_PLANE, genfunc[3]);

	//�e�N�X�`���̉���
	glBindTexture(GL_TEXTURE_2D, 0);

	//�t���[���o�b�t�@�ǉ�
	//* �t���[���o�b�t�@�I�u�W�F�N�g�𐶐����Č������� 
	glGenFramebuffersEXT(1, &mFb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFb);

	//* �t���[���o�b�t�@�I�u�W�F�N�g�Ƀf�v�X�o�b�t�@�p�̃e�N�X�`������������ 
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
		GL_DEPTH_ATTACHMENT_EXT,
		GL_TEXTURE_2D, mDepthTextureID, 0);
	//* �J���[�o�b�t�@�������̂œǂݏ������Ȃ� 
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	//* �t���[���o�b�t�@�I�u�W�F�N�g�̌������������� 
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	//�e�N�X�`�����j�b�g��0�ɖ߂�
	glActiveTexture(GL_TEXTURE0);
}
void CShadowMap::Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[])
{
	mDepthTextureID = 0;
	mFb = 0;
	mTextureHeight = height;
	mTextureWidth = width;
	mpRender = funcRender;
	mShadowCol[0] = shadowCol[0];
	mShadowCol[1] = shadowCol[1];
	mShadowCol[2] = shadowCol[2];
	mShadowCol[3] = shadowCol[3];
	mLightPos[0] = lightPos[0];
	mLightPos[1] = lightPos[1];
	mLightPos[2] = lightPos[2];
	Init();
}

void CShadowMap::Render()
{
	//�����̃��C�g
	const GLfloat lightcol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLint	viewport[4]; //�r���[�|�[�g�̕ۑ��p
	CMatrix	modelviewLight; //���f���r���[�ϊ��s��̕ۑ��p
	CMatrix	projection; //�����ϊ��s��̕ۑ��p
	/* ���f���r���[�ϊ��s���ۑ����Ă��� */
	CMatrix modelviewCamera;
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewCamera.M());

	/*
	** ��P�X�e�b�v�F�f�v�X�e�N�X�`���̍쐬
	*/
	//* �t���[���o�b�t�@�I�u�W�F�N�g�ւ̃����_�����O�J�n
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFb);

	/* �f�v�X�o�b�t�@���N���A���� */
	glClear(GL_DEPTH_BUFFER_BIT);

	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ肷�� */
	glViewport(0, 0, mTextureWidth, mTextureHeight);

	/* ���݂̓����ϊ��s���ۑ����Ă��� */
	glGetFloatv(GL_PROJECTION_MATRIX, projection.M());

	/* �����ϊ��s���ݒ肷�� */
	glMatrixMode(GL_PROJECTION); //�����ϊ��s��ɐ؂�ւ�
	glLoadIdentity(); //�s��̏�����

	/* �����ʒu�����_�Ƃ��V�[��������Ɏ��܂�悤���f���r���[�ϊ��s���ݒ肷�� */
	glMatrixMode(GL_MODELVIEW); //���f���r���[�s��ɐ؂�ւ�
	glLoadIdentity(); //�s��̏�����
	//�����ʒu���猩��悤�ɍs���ݒ肷��
	gluPerspective(75.0, (GLdouble)mTextureWidth / (GLdouble)mTextureHeight, 1.0, 100000.0);
	gluLookAt(mLightPos[0], mLightPos[1], mLightPos[2], mLightPos[0] - 1, 0, mLightPos[2] - 1, 0.0, 1.0, 0.0);
	/* �ݒ肵�����f���r���[�ϊ��s���ۑ����Ă��� */
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewLight.M());

	/* �f�v�X�o�b�t�@�̓��e�������擾����̂Ńt���[���o�b�t�@�ɂ͏������܂Ȃ� */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* ���������ĉA�e�t�����s�v�Ȃ̂Ń��C�e�B���O���I�t�ɂ��� */
	glDisable(GL_LIGHTING);

	/* �f�v�X�o�b�t�@�ɂ͔w�ʂ̃|���S���̉��s�����L�^����悤�ɂ��� */
	glCullFace(GL_FRONT);

	//�f�v�X�e�N�X�`���ւ̕`��
	if (mpRender)
	{
		(*mpRender)();
	}

	/* �t���[���o�b�t�@�I�u�W�F�N�g�ւ̃����_�����O�I�� */
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	/* �ʏ�̕`��̐ݒ�ɖ߂� */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION); //�����ϊ��s��ɐ؂�ւ�
	glLoadMatrixf(projection.M());
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/*
	** ��Q�X�e�b�v�F�S�̂̕`��
	*/
	/* �t���[���o�b�t�@�ƃf�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���r���[�ϊ��s��̐ݒ� */
	glMatrixMode(GL_MODELVIEW); //���f���r���[�s��ɐ؂�ւ�
	glLoadIdentity();
	glMultMatrixf(modelviewCamera.M());

	/* �����̖��邳���e�̕����ł̖��邳�ɐݒ� */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mShadowCol);

	//�e�̕`��
	if (mpRender)
	{
		(*mpRender)();
	}

	//�f�v�X�e�N�X�`���̐ݒ�
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);

	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* �e�N�X�`�����W�� [-1,1] �͈̔͂� [0,1] �͈̔͂Ɏ��߂� */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);
	/* �e�N�X�`���̃��f���r���[�ϊ��s��Ɠ����ϊ��s��̐ς������� */
	glMultMatrixf(modelviewLight.M());

	/* ���݂̃��f���r���[�ϊ��̋t�ϊ��������Ă��� */
	CMatrix inverse = modelviewCamera.Transpose();
	inverse.M(0, 3, 0);
	inverse.M(1, 3, 0);
	inverse.M(2, 3, 0);
	inverse = CMatrix().Translate(-modelviewCamera.M(3,0), -modelviewCamera.M(3,1),
		-modelviewCamera.M(3,2)) * inverse;
	glMultMatrixf(inverse.M());

	/* ���f���r���[�ϊ��s��ɖ߂� */
	glMatrixMode(GL_MODELVIEW);

	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎���������L���ɂ��� */
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	/* �A���t�@�e�X�g��L���ɂ��ĉe�̕���������`�悷�� */
	glEnable(GL_ALPHA_TEST);
	///* �����̕��������Ƃ̐}�`�ɏd�˂ĕ`�����悤�ɉ��s���̔�r�֐���ύX���� */
	glDepthFunc(GL_LEQUAL);

	/* �����̖��邳������̕����ł̖��邳�ɐݒ� */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
	//�e�N�X�`�����j�b�g0�ɐ؂�ւ���
	glActiveTexture(GL_TEXTURE0);
	//�����̕`��
	if (mpRender)
	{
		(*mpRender)();
	}

	/* ���s���̔�r�֐������ɖ߂� */
	glDepthFunc(GL_LESS);
	/* �A���t�@�e�X�g�𖳌��ɂ��� */
	glDisable(GL_ALPHA_TEST);

	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎��������𖳌��ɂ��� */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);

	//�f�v�X�e�N�X�`������������
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glActiveTexture(GL_TEXTURE0);

	glMatrixMode(GL_MODELVIEW);

}

CShadowMap::CShadowMap()
	: mDepthTextureID(0)
	, mFb(0)
{
}

CShadowMap::~CShadowMap()
{
	if (mDepthTextureID)
	{
		glDeleteTextures(1, &mDepthTextureID);
		mDepthTextureID = 0;
	}
	if (mFb)
	{
		glDeleteFramebuffers(1, &mFb);
		mFb = 0;
	}
}
