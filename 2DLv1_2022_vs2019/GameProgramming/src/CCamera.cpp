#include "CCamera.h"
#include "glut.h"

void CCamera::Start(double left, double right, double bottom, double top)
{
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//�\���G���A�̐ݒ�
	gluOrtho2D(left, right, bottom, top);
}

void CCamera::End()
{
	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
}
