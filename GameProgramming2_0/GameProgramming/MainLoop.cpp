#include "glut.h"

/*�Q�D
* �O�p�`�̃v���O����
* CTriangle�v���O�����i�N���X�j���`����
*/
class CTriangle
{
public:
	//�Q�DRender�����i���\�b�h�j��錾����
	void Render();
};
//�Q�DRender�����i���\�b�h�j���`����
void CTriangle::Render()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 100.0f);
	glVertex2f(-100.0f, -100.0f);
	glVertex2f(100.0f, -100.0f);
	glEnd();
}
//�Q�DCTriangle�N���X�̕ϐ��i�C���X�^���X�j���쐬����
CTriangle Triangle;

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
}
//MailLoop�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void MainLoop() {
	//�Q�D�ϐ�Triangle��Render�������Ăяo��
	Triangle.Render();
}
