#ifndef CCOLLIDERCAPSULE_H
#define CCOLLIDERCAPSULE_H
#include "CCollider.h"
/*
�J�v�Z���R���C�_�̒�`
*/
class CColliderCapsule : public CCollider
{
public:
	CColliderCapsule(){}
	//�R���X�g���N�^�i�����R���C�_�j
	//CColliderLine(�e, �e�s��, ���_1, ���_2, ���a)
	CColliderCapsule(CCharacter *parent, CMatrix *matrix
		, const CVector &v0, const CVector &v1, float radius);
	//�����R���C�_�̐ݒ�
	//Set(�e, �e�s��, ���_1, ���_2, ���a)
	void Set(CCharacter *parent, CMatrix *matrix
		, const CVector &v0, const CVector &v1, float radius);
	//�`��
	void Render();
	//�D��x�̕ύX
	void ChangePriority();

};

#endif
