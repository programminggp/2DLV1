#ifndef CENEMY2_H
#define CENEMY2_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy2 : public CCharacter {
public:
	//�R���X�g���N�^
	CEnemy2();
	//CEnemy(�ʒu, ��], �g�k)
	CEnemy2(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	//���f���f�[�^
	static CModel sModel;
	//�R���C�_
	CCollider mCollider;
	int mHp;	//�q�b�g�|�C���g
};

#endif
