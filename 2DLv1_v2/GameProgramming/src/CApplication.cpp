#include "CApplication.h"
#include <stdio.h> //printf�֐��̃C���N���[�h

//�l�p�`�N���X�̐錾
class CRect;

//�l�p�`�N���X�̒�`
class CRect
{
public:
	void Render(); //Render���\�b�h�̐錾
};


//Render���\�b�h�̒�`
void CRect::Render()
{
	printf("Render CRect\n"); //������̏o��
}


void CApplication::Start()
{
	CRect rect; //CRect�N���X�̃C���X�^���Xrect�̍쐬
	rect.Render(); //rect�C���X�^���X��Render()�����s
}

void CApplication::Update()
{

}
