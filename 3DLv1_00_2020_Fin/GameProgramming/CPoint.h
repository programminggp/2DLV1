#ifndef CPOINT_H
#define CPOINT_H
#include "CCollider.h"
#include "CCharacter.h"
/*
�|�C���g�N���X
�G�@�Ȃǂ̖ڕW�ɂ���
*/
class CPoint : public CCharacter {
public:
	//�R���C�_�ǉ�
	CCollider mCollider;
	CPoint();
	//�R���X�g���N�^
	//CPoint(�ʒu, ���a)
	//CPoint(const CVector &pos, float r);
	//�ݒ�
	//Set(�ʒu, ���a)
	void Set(const CVector &pos, float r);
};

#endif
