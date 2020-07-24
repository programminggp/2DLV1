#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include "CTriangle.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
/*
�e�N���X
�O�p�`���΂�
*/
class CBullet : public CCharacter {
public:
	//�O�p�`
	CTriangle mT;
	//22
	//��������
	int mLife;
	//�R���C�_
	CCollider mCollider;
	CBullet();
	//���Ɖ��s���̐ݒ�
	//Set(��, ���s)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);
};

#endif
