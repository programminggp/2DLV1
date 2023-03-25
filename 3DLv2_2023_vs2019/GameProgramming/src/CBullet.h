#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
//�O�p�`�N���X�̃C���N���[�h
#include "CTriangle.h"
#include "CCollider.h"

/*
�e�N���X
�O�p�`���΂�
*/
class CBullet : public CCharacter3 {
public:
	//�Փˏ���
	void Collision();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);

	CBullet();
	//���Ɖ��s���̐ݒ�
	//Set(��, ���s)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();
private:
	CCollider mCollider;
	//��������
	int mLife;
	//�O�p�`
	CTriangle mT;
};

#endif
