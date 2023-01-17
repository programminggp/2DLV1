#ifndef CAREAMAGIC_H
#define CAREAMAGIC_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include "CTriangle.h"
//
#include "CCollider.h"
/*
�e�N���X
�O�p�`���΂�
*/
class CAreaMagic : public CCharacter {
public:
	//CAreaMagic();
	CAreaMagic(const CVector& position, const CVector& rotation, const CVector& scale);
	//���Ɖ��s���̐ݒ�
	//Set(��, ���s)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	CCollider mCollider;
	int AMagicLife;   //�͈͖��@��������
	//�O�p�`
	CTriangle mT;
};

#endif
