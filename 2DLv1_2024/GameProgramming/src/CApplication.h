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
class CRect
{
public:
	void Render();
};

void CRect::Render()
{
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
	CRect* mpRect;
};

void CApplication::Start()
{
	mpRect = new CRect();
}

void CApplication::Update()
{
	mpRect->Render();
}

CApplication::~CApplication()
{
	delete mpRect;
}
