#include "glut.h"

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
}
//MailLoop�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void MainLoop() {
	//�P�D�O�p�`��`�悷��
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 100.0f);
	glVertex2f(-100.0f, -100.0f);
	glVertex2f(100.0f, -100.0f);
	glEnd();
}
