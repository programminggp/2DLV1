#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include "CCollider.h"
/*
�����R���C�_�̒�`
*/
class CColliderLine : public CCollider
{
public:
	void ChangePriority();
	CColliderLine(){}
	//�R���X�g���N�^(�����R���C�_)
	//CColliderLine(�e�A�e�s��A���_�P�A���_�Q)
	CColliderLine(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//�����R���C�_�̐ݒ�
	//Set(�e�A�e�s��A���_�P�A���_�Q)
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//�`��
	void Render();
};
#endif