#ifndef CPOINT_H
#define CPOINT_H
#include "CCollider.h"
#include "CCharacter.h"

/*
�|�C���g�N���X
�G�@�Ȃǂ̖ڕW�ɂ���
*/
class CPoint : public CCharacter{
	CCollider mCollider; //�R���C�_�̒ǉ�
	CPoint* mpNext;	//���̃|�C���g
public:
	CPoint();
	//CPoint(�ʒu, ���a, ���|�C���^)
	CPoint(const CVector& pos, float r, CPoint* next = nullptr);
	//�ݒ�
	//Set(�ʒu, ���a, ���|�C���^)
	void Set(const CVector &pos, float r, CPoint* next = nullptr);
	//���̃|�C���g�̎擾
	CPoint* GetNextPoint();
};

#endif