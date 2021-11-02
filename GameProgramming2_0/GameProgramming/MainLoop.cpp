#include "glut.h"

/*�Q�D
* �l�p�`�̃v���O����
* CRectangle�v���O�����i�N���X�j���`����
*/
class CRectangle
{
public:
	//�R�D�f�t�H���g�R���X�g���N�^��錾����
	CRectangle();
	//�S�D�����R���X�g���N�^��錾����
	CRectangle(float left, float right, float bottom, float top);
	//�Q�DRender�����i���\�b�h�j��錾����
	void Render();
//�R�Dprivate�A�N�Z�X����
private:
	//�R�D�ϐ���錾����
	float left, right, bottom, top;
//	float mX, mY, mW, mH;
};
//�R�D�f�t�H���g�R���X�g���N�^���`����
CRectangle::CRectangle()
	//�R�D�ϐ��ɒl��������
	: left(-30.0f), right(30.0f), bottom(-30.0f), top(30.0f)
{
}
//�S�D�����R���X�g���N�^���`����
CRectangle::CRectangle(float l, float r, float b, float t)
	: left(l), right(r), bottom(b), top(t)
{}
//�Q�DRender�����i���\�b�h�j���`����
void CRectangle::Render()
{
	//�Q�D�l�p�`�̕`��
	//glBegin(GL_QUADS);
	//glVertex2f(-30.0f, -30.0f);
	//glVertex2f(30.0f, -30.0f);
	//glVertex2f(30.0f, 30.0f);
	//glVertex2f(-30.0f, 30.0f);
	//glEnd();
	//�R�D�ϐ��̒l���Q�Ƃ���
	glBegin(GL_QUADS);
	glVertex2f(left, bottom);
	glVertex2f(right, bottom);
	glVertex2f(right, top);
	glVertex2f(left, top);
	glEnd();
}
//�Q�DCRectangle�N���X�̕ϐ��i�C���X�^���X�j���쐬����
//�R�D���̎��f�t�H���g�R���X�g���N�^���Ăяo��
CRectangle Rectangle;
//�S�D�����R���X�g���N�^���g�����C���X�^���X�̍쐬
CRectangle Rect(30.0f, 90.0f, 30.0f, 90.0f);

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
}
//MailLoop�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void MainLoop() {
	//�P�D�l�p�`�̕`��
	//glBegin(GL_QUADS);
	//glVertex2f(-30.0f, -30.0f);
	//glVertex2f(30.0f, -30.0f);
	//glVertex2f(30.0f, 30.0f);
	//glVertex2f(-30.0f, 30.0f);
	//glEnd();
	//�Q�D�ϐ�Rectangle��Render�������Ăяo��
	Rectangle.Render();
	//�S�D
	Rect.Render();
}
