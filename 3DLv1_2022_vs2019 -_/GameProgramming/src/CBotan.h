#ifndef CBOTAN_H
#define CBOTAN_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CCollider.h"
/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CBotan : public CCharacter3 {
public:
	void Collision();
	//�Փˏ���
	//Collision(�R���C�_�P�A�R���C�_�Q)
	void Collision(CCollider* m, CCollider* o);
	//�R���X�g���N�^
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CBotan(CModel* model, const CVector& position,
		const CVector& ratation, const CVector& scale);
	//�X�V����
	void Update();
private:
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif
