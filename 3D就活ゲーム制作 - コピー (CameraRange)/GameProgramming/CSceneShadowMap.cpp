#include "glew.h"
#include "CSceneShadowMap.h"

#define TEXWIDTH (800)
#define TEXHEIGHT (600)

CSceneShadowMap::~CSceneShadowMap()
{
	delete mpPlayer;
	delete mpGround;
}

void CSceneShadowMap::Init()
{
	mRover.Load("Rover1.obj", "material\\racing_mat\\single_color\\white.mtl");//�v���C���[
	//�n�ʂ̓ǂݍ���
	mPlane.Load("plane.obj", "plane.mtl");

	mpPlayer = new CObj(&mRover, CVector(50.0f, 10.0f, 30.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	mpGround = new CObj(&mPlane, CVector(), CVector(), CVector(70.0f, 1.0f, 70.0f));

	//Shadow Map ************************************

	/* �e�N�X�`�����j�b�g�P��Depth�e�N�X�`���Ŏg�p */
	glActiveTexture(GL_TEXTURE1);
	//�e�N�X�`���̐���
	glGenTextures(1, &mDepthTextureID);
	//�g�p����e�N�X�`���̃o�C���h
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);

	/* Depth�e�N�X�`���̊��蓖�� */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, TEXWIDTH, TEXHEIGHT, 0,
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

	//************************************ Shadow Map

}

void CSceneShadowMap::Update()
{
	mpPlayer->mRotation.mY++;
	CTaskManager::Get()->Update();
	Camera3D(90.0f, 50.0f, 90.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Shadow Map ************************************

	GLint	viewport[4]; //�r���[�|�[�g�̕ۑ��p
	CMatrix	modelview; //���f���r���[�ϊ��s��̕ۑ��p
	CMatrix	projection; //�����ϊ��s��̕ۑ��p

	/*
	** ��P�X�e�b�v�F�f�v�X�e�N�X�`���̍쐬
	*/

	/* �f�v�X�o�b�t�@���N���A���� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);

	/* �r���[�|�[�g���e�N�X�`���̃T�C�Y�ɐݒ肷�� */
	glViewport(0, 0, TEXWIDTH, TEXHEIGHT);

	/* �����ϊ��s���ݒ肷�� */
	glMatrixMode(GL_PROJECTION); //�����ϊ��s��ɐ؂�ւ�
	glPushMatrix(); //���݂̐ݒ�̓X�^�b�N�ɕۑ�
	glLoadIdentity(); //�s��̏�����

	/* Depth�e�N�X�`���̓����ϊ��s���ۑ����Ă��� */
	gluPerspective(75.0, (GLdouble)TEXWIDTH / (GLdouble)TEXHEIGHT, 1.0, 100000.0);
	glGetFloatv(GL_PROJECTION_MATRIX, projection.mM[0]); //�����ϊ��s��̕ۑ�

	GLfloat lightpos[] = { 0.0f, 200.0f, 200.0f, 0.0f }; //���C�g�̈ʒu�f�[�^
	/* �����ʒu�����_�Ƃ��V�[��������Ɏ��܂�悤���f���r���[�ϊ��s���ݒ肷�� */
	glMatrixMode(GL_MODELVIEW); //���f���r���[�s��ɐ؂�ւ�
	glPushMatrix(); //���݂̐ݒ�̓X�^�b�N�ɕۑ�
	glLoadIdentity(); //�s��̏�����
	//���C�g�ʒu���猩��悤�ɍs���ݒ肷��
	gluLookAt(lightpos[0], lightpos[1], lightpos[2], lightpos[0] - 1, 0, lightpos[2] - 1, 0.0, 1.0, 0.0);
	/* �ݒ肵�����f���r���[�ϊ��s���ۑ����Ă��� */
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview.mM[0]);

	/* �f�v�X�o�b�t�@�̓��e�������擾����̂Ńt���[���o�b�t�@�ɂ͏������܂Ȃ� */
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/* ���������ĉA�e�t�����s�v�Ȃ̂Ń��C�e�B���O���I�t�ɂ��� */
	glDisable(GL_LIGHTING);

	/* �f�v�X�o�b�t�@�ɂ͔w�ʂ̃|���S���̉��s�����L�^����悤�ɂ��� */
	glCullFace(GL_FRONT);
	//************************************ Shadow Map

	//Depth�e�N�X�`�����쐬����`��
	CTaskManager::Get()->Render();

	//Shadow Map ************************************
	/* �e�N�X�`�����j�b�g�P�ɐ؂�ւ��� */
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mDepthTextureID);
	/* �f�v�X�o�b�t�@�̓��e���e�N�X�`���������ɓ]������ */
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, TEXWIDTH, TEXHEIGHT);

	/* �ʏ�̕`��̐ݒ�ɖ߂� */
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

	glMatrixMode(GL_PROJECTION); //�����ϊ��s��ɐ؂�ւ�
	glPopMatrix(); //�ݒ���X�^�b�N����߂�

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
	glPopMatrix(); //�X�^�b�N���猳�ɖ߂�
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
	//************************************ Shadow Map

	//�e�̕`��
	mpGround->Render();

	//Shadow Map ************************************
	/* �e�N�X�`���}�b�s���O�ƃe�N�X�`�����W�̎��������𖳌��ɂ��� */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	glDisable(GL_TEXTURE_2D);
	//�e�N�X�`������������
	glBindTexture(GL_TEXTURE_2D, 0);
	/* �e�N�X�`���ϊ��s���ݒ肷�� */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	glActiveTexture(GL_TEXTURE0);
	//************************************ Shadow Map

	//�S�̂̕`��
	CTaskManager::Get()->Render();
}
