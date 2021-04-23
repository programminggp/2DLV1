#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include "CTriangle.h"
#include "CCollider.h"
#include "CModel.h"
/*
�e�N���X
�O�p�`���΂�
*/
class CBullet : public CCharacter{
public:
	//�O�p�`
	CTriangle mT;
	//���Ɖ��s���̐ݒ�
	//Set�i��,���s�j
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();

	//��������
	int mLife;
	CBullet();

	CCollider mCollider;

	//�Փˏ���
	//Colllision(�R���C�_1, �R���C�_2)
	void Collision(CCollider *m, CCollider *y);

	static CModel mBullet;

	//mBullet.Load("�e�e.obj", "�e�e.mtl");
};

#endif