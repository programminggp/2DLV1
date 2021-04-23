#include "CScene.h"
//OpenGL
#include "glut.h"

//2D�`��X�^�[�g
//Start2D(�����W, �E���W, �����W, ����W)
void CScene::Start2D(float left, float right, float bottom, float top) {
	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();

	//���f���r���[�s�񂩂�
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(left, right, bottom, top);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
}

//2D�`��I��
void CScene::End2D() {
	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
void CScene::Camera3D(float ex, float ey, float ez, float cx, float cy, float cz, float tx, float ty, float tz) {
	gluLookAt(ex, ey, ez, cx, cy, cz, tx, ty, tz);
}
