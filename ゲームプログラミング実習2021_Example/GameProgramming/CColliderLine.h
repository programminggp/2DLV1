#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include "CCollider.h"
/*
�����R���C�_�̒�`
*/
class CColliderLine : public CCollider
{
public:
	CColliderLine(){}
	//�R���X�g���N�^�i�����R���C�_�j
	//CColliderLine(�e, �e�s��, ���_1, ���_2)
	CColliderLine(CCharacter *parent, CMatrix *matrix
		, const CVector &v0, const CVector &v1);
	//�����R���C�_�̐ݒ�
	//Set(�e, �e�s��, ���_1, ���_2)
	void Set(CCharacter *parent, CMatrix *matrix
		, const CVector &v0, const CVector &v1);
	//�`��
	void Render();
	//�D��x�̕ύX
	void ChangePriority();

};

#endif
