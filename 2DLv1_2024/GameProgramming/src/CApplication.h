#pragma once
//
//�C���N���[�h
//
#include <stdio.h>
#include "glut.h"

//
//�N���X�̐錾
//

//CApplication�N���X�̐錾
class CApplication;
//CRect�N���X�̐錾
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
private:
	//�ϐ��̐錾
	float mX;
	float mY;
};

//�l�p�`�N���X�̕`�揈���̒�`
void CRect::Render()
{
	//�ϐ��̑��
	mX = 200.0f;
	mY = 150.0f;
	//��ʂɎl�p�`��`�悷��
	glBegin(GL_QUADS);
	glVertex2f(mX, mY);
	glVertex2f(mX + 400.0f, mY);
	glVertex2f(mX + 400.0f, mY + 300.0f);
	glVertex2f(mX, mY + 300.0f);
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
	//printf("Start\n");
	//�C���X�^���X�̐���
	mpRect = new CRect();
}

void CApplication::Update()
{
	//printf("Update\n");
	//���\�b�h�̌Ăяo��
	mpRect->Render();
}

//CApplication�̏I�����Ɏ��s
CApplication::~CApplication()
{
	//�C���X�^���X�̍폜
	delete mpRect;
}
