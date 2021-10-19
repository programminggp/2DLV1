#include "glut.h"

/*�Q�D
* �O�p�`�̃v���O����
* CTriangle�v���O�����i�N���X�j���`����
*/
class CTriangle
{
	//�R�D�ϐ���錾����
	float x0, y0, x1, y1, x2, y2;
public:
	//�R�D�f�t�H���g�R���X�g���N�^��錾����
	CTriangle();
	//�Q�DRender�����i���\�b�h�j��錾����
	void Render();
};
//�R�D�f�t�H���g�R���X�g���N�^���`����
CTriangle::CTriangle()
{
	//�R�D�ϐ��ɒl��������
	x0 = -100.0f;
	y0 = 100.0f;
	x1 = 0.0f;
	y1 = -100.0f;
	x2 = 100.0f;
	y2 = 100.0f;
}
//�Q�DRender�����i���\�b�h�j���`����
void CTriangle::Render()
{
	//�R�D�ϐ��̒l���Q�Ƃ���
	glBegin(GL_TRIANGLES);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
//�Q�DCTriangle�N���X�̕ϐ��i�C���X�^���X�j���쐬����
//�R�D���̎��f�t�H���g�R���X�g���N�^�����s�����
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
