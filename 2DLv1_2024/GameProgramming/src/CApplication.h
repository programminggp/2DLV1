#pragma once
#include "glut.h"
//
//�N���X�̐錾
//
class CApplication;
class CRect;

//
//�N���X�̒�`
//
//�l�p�`�N���X�̒�`
class CRect
{
public:
	//���\�b�h�̐錾
	//�`�揈��
	void Render();
};

//�l�p�`�N���X�̕`�揈���̒�`
void CRect::Render()
{
	//��ʂɎl�p�`��`�悷��
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(400.0f, 0.0f);
	glVertex2f(400.0f, 300.0f);
	glVertex2f(0.0f, 300.0f);
	glEnd();
}


class CApplication
{
public:
	//�ŏ��Ɉ�x�������s���郁�\�b�h
	void Start();
	//�J��Ԃ����s���郁�\�b�h
	void Update();
	//�f�X�g���N�^
	~CApplication();
private:
	//�C���X�^���X�ϐ��̐錾
	CRect* mpRect;
};

void CApplication::Start()
{
	//�C���X�^���X�̐���
	mpRect = new CRect();
}

void CApplication::Update()
{
	//���\�b�h�̌Ăяo��
	mpRect->Render();
}

CApplication::~CApplication()
{
	//�C���X�^���X�̍폜
	delete mpRect;
}
