#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include "CCollider.h"
/*
�O�p�`�R���C�_�̒�`
*/
class CColliderTriangle : public CCollider
{
public:
	//�D��x�̕ύX
	void ChangePriority();
	CColliderTriangle() {}
	//�R���X�g���N�^�i�O�p�R���C�_�j
	//CColliderTriangle(�e, �e�s��, ���_1, ���_2, ���_3)
	CColliderTriangle(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//�O�p�R���C�_�̐ݒ�
	//Set(�e, �e�s��, ���_1, ���_2, ���_3)
	void Set(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//�`��
	void Render();
};
#endif
