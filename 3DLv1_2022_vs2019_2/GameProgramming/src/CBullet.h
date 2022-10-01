#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
//�O�p�`�N���X�̃C���N���[�h
#include "CTriangle.h"

/*
�e�N���X
�O�p�`���΂�
*/
class CBullet : public CCharacter3 {
public:
	CBullet();
	//���Ɖ��s���̐ݒ�
	//Set(��, ���s)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();
private:
	//��������
	int mLife;
	//�O�p�`
	CTriangle mT;
};

#endif
