#include "glew.h"
#include "CShadowMap.h"

CShadowMap::~CShadowMap()
{
}

void CShadowMap::Init(GLuint width, GLuint height)
{
	//Depth�e�N�X�`���̕��ƍ�����ۑ�
	mTextureWidth = width;
	mTextureHeight = height;
	/* �e�N�X�`�����j�b�g�P��Depth�e�N�X�`���Ŏg�p */
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &mDepthTextureID);
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);

	/* Depth�e�N�X�`���̊��蓖�� */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
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
	//�e�N�X�`�����j�b�g��0�ɖ߂�
	glActiveTexture(GL_TEXTURE0);
}

void CShadowMap::Step1Init(const CVector& lightPosition)
{
	/*
	** ��P�X�e�b�v�F�f�v�X�e�N�X�`���̍쐬
	*/

	/* �f�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ肷�� */
	glViewport(0, 0, mTextureWidth, mTextureHeight);

	/* �����ϊ��s���ݒ肷�� */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glOrtho(
	//	mPlayer->mPosition.mX - TEXWIDTH, mPlayer->mPosition.mX + TEXWIDTH,
	//	mPlayer->mPosition.mZ - TEXHEIGHT, mPlayer->mPosition.mZ + TEXHEIGHT,
	//	-10000.0f, 10000.0f
	//);
	/* Depth�e�N�X�`���̓����ϊ��s���ۑ����Ă��� */
	gluPerspective(75.0, (GLdouble)mTextureWidth / (GLdouble)mTextureHeight, 1.0, 100000.0);
	glGetFloatv(GL_PROJECTION_MATRIX, projection.mM[0]);

	GLfloat lightpos[] = { lightPosition.mX, lightPosition.mY, lightPosition.mZ, 0.0f };

	/* �����ʒu�����_�Ƃ��V�[��������Ɏ��܂�悤���f���r���[�ϊ��s���ݒ肷�� */
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(lightpos[0], lightpos[1], lightpos[2], lightpos[0] - 1, 0, lightpos[2] - 1, 0.0, 1.0, 0.0);

	/* �ݒ肵�����f���r���[�ϊ��s���ۑ����Ă��� */
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.mM[0]);

	/* �f�v�X�o�b�t�@�̓��e�������擾����̂Ńt���[���o�b�t�@�ɂ͏������܂Ȃ� */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* ���������ĉA�e�t�����s�v�Ȃ̂Ń��C�e�B���O���I�t�ɂ��� */
	glDisable(GL_LIGHTING);

	/* �f�v�X�o�b�t�@�ɂ͔w�ʂ̃|���S���̉��s�����L�^����悤�ɂ��� */
	glCullFace(GL_FRONT);

}

void CShadowMap::Step2Begin()
{
	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);
	/* �f�v�X�o�b�t�@�̓��e���e�N�X�`���������ɓ]������ */
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, mTextureWidth, mTextureHeight);

	/* �ʏ�̕`��̐ݒ�ɖ߂� */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glCullFace(GL_BACK);

	/*
	** ��Q�X�e�b�v�F�S�̂̕`��
	*/

	/* �t���[���o�b�t�@�ƃf�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���f���r���[�ϊ��s��̐ݒ� */
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	/* ���f���r���[�ϊ��s���ۑ����Ă��� */
	CMatrix modelviewCamera;
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewCamera.mM[0]);

	/* �����̈ʒu��ݒ肷�� */
	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	/* �e�N�X�`�����W�� [-1,1] �͈̔͂� [0,1] �͈̔͂Ɏ��߂� */
	glTranslated(0.5, 0.5, 0.5);
	glScaled(0.5, 0.5, 0.5);
	/* �e�N�X�`���̃��f���r���[�ϊ��s��Ɠ����ϊ��s��̐ς������� */
	glMultMatrixf(projection.mM[0]);
	glMultMatrixf(modelview.mM[0]);

	/* ���݂̃��f���r���[�ϊ��̋t�ϊ��������Ă��� */
	glMultMatrixf(modelviewCamera.GetInverse().mM[0]);

	/* ���f���r���[�ϊ��s��ɖ߂� */
	glMatrixMode(GL_MODELVIEW);

	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎���������L���ɂ��� */
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);

	const GLfloat lightcol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	/* �����̖��邳������̕����ł̖��邳�ɐݒ� */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
}

void CShadowMap::Step3End()
{
	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎��������𖳌��ɂ��� */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glActiveTexture(GL_TEXTURE0);
}

//void CShadowMap::Init()
//{
//	mRover.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");//�v���C���[
//	//�n�ʂ̓ǂݍ���
//	mPlane.Load("plane.obj", "plane.mtl");
//
//	mpPlayer = new CObj(&mRover, CVector(50.0f, 10.0f, 30.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
//	mpGround = new CObj(&mPlane, CVector(), CVector(), CVector(70.0f, 1.0f, 70.0f));
//
//	//Shadow Map
//
///* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
////	glActiveTexture(GL_TEXTURE1);
//	glGenTextures(1, &dtex);
//	glBindTexture(GL_TEXTURE_2D, dtex);
//
//	/* �e�N�X�`���̊��蓖�� */
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TEXWIDTH, TEXHEIGHT, 0,
//		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
//
//	/* �e�N�X�`�����g��E�k��������@�̎w�� */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	/* �e�N�X�`���̌J��Ԃ����@�̎w�� */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	/* �������ރ|���S���̃e�N�X�`�����W�l�̂q�ƃe�N�X�`���Ƃ̔�r���s���悤�ɂ��� */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//
//	/* �����q�̒l���e�N�X�`���̒l�ȉ��Ȃ�^�i�܂�����j */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//
//	/* ��r�̌��ʂ��P�x�l�Ƃ��ē��� */
//	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
//
//	if (true)
//	{
//		/* �e�N�X�`�����W�Ɏ��_���W�n�ɂ����镨�̂̍��W�l��p���� */
//		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//
//		/* ���������e�N�X�`�����W�����̂܂� (S, T, R, Q) �Ɏg�� */
//		static const GLdouble genfunc[][4] = {
//		  { 1.0, 0.0, 0.0, 0.0 },
//		  { 0.0, 1.0, 0.0, 0.0 },
//		  { 0.0, 0.0, 1.0, 0.0 },
//		  { 0.0, 0.0, 0.0, 1.0 },
//		};
//
//		glTexGendv(GL_S, GL_EYE_PLANE, genfunc[0]);
//		glTexGendv(GL_T, GL_EYE_PLANE, genfunc[1]);
//		glTexGendv(GL_R, GL_EYE_PLANE, genfunc[2]);
//		glTexGendv(GL_Q, GL_EYE_PLANE, genfunc[3]);
//
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		//	glActiveTexture(GL_TEXTURE0);
//	}
//
//	//	glDisable(GL_TEXTURE_2D);
//}
//
//void CShadowMap::Update()
//{
//
//	mpPlayer->mRotation.mY++;
//
//	CTaskManager::Get()->Update();
//	Camera3D(90.0f, 50.0f, 90.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//
//	//Shadow Map
//
//	const int FRAMES(600);
//	GLint viewport[4];       /* �r���[�|�[�g�̕ۑ��p�@�@�@�@ */
//	//GLdouble modelview[16];  /* ���f���r���[�ϊ��s��̕ۑ��p */
//	CMatrix modelview;  /* ���f���r���[�ϊ��s��̕ۑ��p */
////	GLdouble modelviewCamera[16];  /* ���f���r���[�ϊ��s��̕ۑ��p */
//	CMatrix modelviewCamera;  /* ���f���r���[�ϊ��s��̕ۑ��p */
////	GLdouble projection[16]; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
//	CMatrix projection; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
//	//GLdouble projectionDepth[16]; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
//	CMatrix projectionDepth; /* �����ϊ��s��̕ۑ��p�@�@�@�@ */
//	static int frame = 0;    /* �t���[�����̃J�E���g�@�@�@�@ */
//	double t = (double)frame / (double)FRAMES; /* �o�ߎ��ԁ@ */
//
//	if (++frame >= FRAMES) frame = 0;
//
//	/*
//	 ** ��P�X�e�b�v�F�f�v�X�e�N�X�`���̍쐬
//	 */
//
//	 /* �f�v�X�o�b�t�@���N���A���� */
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
//	glGetIntegerv(GL_VIEWPORT, viewport);
//
//	/* �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ肷�� */
//	glViewport(0, 0, TEXWIDTH, TEXHEIGHT);
//
//	/* ���݂̓����ϊ��s���ۑ����Ă��� */
////	glGetDoublev(GL_PROJECTION_MATRIX, projectionDepth.mM[0]);
//	glGetFloatv(GL_PROJECTION_MATRIX, projection.mM[0]);
//
//	/* �����ϊ��s���P�ʍs��ɐݒ肷�� */
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//gluPerspective(60.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 100000.0);
//	//gluPerspective(75.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 100000.0);
//	//	glGetDoublev(GL_PROJECTION_MATRIX, projection);
//
//	glOrtho(
//		mpPlayer->mPosition.mX - TEXWIDTH / 4, mpPlayer->mPosition.mX + TEXWIDTH / 4,
//		mpPlayer->mPosition.mZ - TEXHEIGHT / 4, mpPlayer->mPosition.mZ + TEXHEIGHT / 4,
//		-10000.0f, 10000.0f
//		);
//
//	glGetFloatv(GL_PROJECTION_MATRIX, projectionDepth.mM[0]);
//
//	GLfloat lightpos[] = { 0.0f, 600.0f, 100.0f, 0.0f };
//
//	//	glGetDoublev(GL_MODELVIEW_MATRIX, modelviewCamera);
//	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewCamera.mM[0]);
//
//	/* �����ʒu�����_�Ƃ��V�[��������Ɏ��܂�悤���f���r���[�ϊ��s���ݒ肷�� */
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glLoadIdentity();
//	gluLookAt(lightpos[0], lightpos[1], lightpos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//	/* �ݒ肵�����f���r���[�ϊ��s���ۑ����Ă��� */
////	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
//	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.mM[0]);
//
//	if (false)
//	{
//		// �������ꂽ�ϊ��s����擾����B
//		float m[16];
//		glGetFloatv(GL_MODELVIEW_MATRIX, m);
//		{
//			//float vs[] = { m[0], m[4], m[8],  m[12] };
//			//float vt[] = { m[1], m[5], m[9],  m[13] };
//			//float vr[] = { m[2], m[6], m[10], m[14] };
//			//float vq[] = { m[3], m[7], m[11], m[15] };
//
//			float vs[] = { m[0], m[1], m[2],  m[3] };
//			float vt[] = { m[4], m[5], m[6],  m[7] };
//			float vr[] = { m[8], m[9], m[10], m[11] };
//			float vq[] = { m[12], m[13], m[14], m[15] };
//
//			// ���������ϊ��s����I�u�W�F�N�g�̒��_�Ɋ|����Ή�ʂ𕢂��悤��UV�������v�Z�����B
//			glTexGenfv(GL_S, GL_OBJECT_PLANE, vs);
//			glTexGenfv(GL_T, GL_OBJECT_PLANE, vt);
//			glTexGenfv(GL_R, GL_OBJECT_PLANE, vr);
//			glTexGenfv(GL_Q, GL_OBJECT_PLANE, vq);
//		}
//
//		// UV�̎���������L��������B
//		glEnable(GL_TEXTURE_GEN_S);
//		glEnable(GL_TEXTURE_GEN_T);
//		glEnable(GL_TEXTURE_GEN_R);
//		glEnable(GL_TEXTURE_GEN_Q);
//
//		// ���������̌v�Z���ɃI�u�W�F�N�g��Ԃ̒��_���W���g���B
//		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//	}
//
//	/* �f�v�X�o�b�t�@�̓��e�������擾����̂Ńt���[���o�b�t�@�ɂ͏������܂Ȃ� */
//	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//
//	/* ���������ĉA�e�t�����s�v�Ȃ̂Ń��C�e�B���O���I�t�ɂ��� */
//	glDisable(GL_LIGHTING);
//
//	/* �f�v�X�o�b�t�@�ɂ͔w�ʂ̃|���S���̉��s�����L�^����悤�ɂ��� */
//	glCullFace(GL_FRONT);
//
//	CTaskManager::Get()->Render();
//
//	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
////	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, dtex);
//	/* �f�v�X�o�b�t�@�̓��e���e�N�X�`���������ɓ]������ */
//	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, TEXWIDTH, TEXHEIGHT);
//
//	/* �ʏ�̕`��̐ݒ�ɖ߂� */
//	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
//	glMatrixMode(GL_PROJECTION);
//	//	glLoadMatrixd(projection);
//	glLoadMatrixf(projection.mM[0]);
//
//	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//	glEnable(GL_LIGHTING);
//	glCullFace(GL_BACK);
//
//	/*
//	** ��Q�X�e�b�v�F�S�̂̕`��
//	*/
//
//	/* �t���[���o�b�t�@�ƃf�v�X�o�b�t�@���N���A���� */
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	/* ���f���r���[�ϊ��s��̐ݒ� */
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	/* �����̈ʒu��ݒ肷�� */
////	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
//
//	/* �e�N�X�`���ϊ��s���ݒ肷�� */
//	glMatrixMode(GL_TEXTURE);
//	glLoadIdentity();
//
//	/* �e�N�X�`�����W�� [-1,1] �͈̔͂� [0,1] �͈̔͂Ɏ��߂� */
//	glTranslated(0.5, 0.5, 0.5);
//	glScaled(0.5, 0.5, 0.5);
//
//	/* �e�N�X�`���̃��f���r���[�ϊ��s��Ɠ����ϊ��s��̐ς������� */
//	glMultMatrixf(projectionDepth.mM[0]);
//	glMultMatrixf(modelview.mM[0]);
//
//	/* ���݂̃��f���r���[�ϊ��̋t�ϊ��������Ă��� */
//	glMultMatrixf(modelviewCamera.GetInverse().mM[0]);
//
//	/* ���f���r���[�ϊ��s��ɖ߂� */
//	glMatrixMode(GL_MODELVIEW);
//	glPopMatrix();
//
//	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎���������L���ɂ��� */
//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_TEXTURE_GEN_S);
//	glEnable(GL_TEXTURE_GEN_T);
//	glEnable(GL_TEXTURE_GEN_R);
//	glEnable(GL_TEXTURE_GEN_Q);
//
//	const GLfloat lightcol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	/* �����̖��邳������̕����ł̖��邳�ɐݒ� */
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
//
//	CTaskManager::Get()->Render();
//
//	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎��������𖳌��ɂ��� */
//	glDisable(GL_TEXTURE_GEN_S);
//	glDisable(GL_TEXTURE_GEN_T);
//	glDisable(GL_TEXTURE_GEN_R);
//	glDisable(GL_TEXTURE_GEN_Q);
//	glDisable(GL_TEXTURE_2D);
//
//	//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//
//	/* �e�N�X�`���ϊ��s���ݒ肷�� */
//	glMatrixMode(GL_TEXTURE);
//	glLoadIdentity();
//	glMatrixMode(GL_MODELVIEW);
//
//}
