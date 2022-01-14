#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include"CTriangle.h"
//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
/*
* �e�N���X
* �O�p�`���΂�
*/

class CBullet : public CCharacter{
public:
	//���Ɖ��s��
	//Set(��,���s)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�e�̐�������
	int mLife;
	//�Փˏ���
	//Collision(�R���C�_1,�R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	//�f�t�H���g�R���X�g���N�^
	CBullet();
private:
	//�R���C�_
	CCollider mCollider;
	//�O�p�`
	CTriangle mT;
};
#endif 

