#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include "CCollider.h"
/*
�O�p�`�R���C�_�̒�`
*/
class CColliderTriangle : public CCollider
{
public:
	CColliderTriangle() {}
//	CColliderTriangle(bool flg) : CCollider(flg) {}
	//�R���X�g���N�^�i�O�p�R���C�_�j
	//CColliderTriangle(�e, �e�s��, ���_1, ���_2, ���_3)
	CColliderTriangle(CCharacter *parent, CMatrix *matrix
		, const CVector &v0, const CVector &v1, const CVector &v2);
	//�O�p�R���C�_�̐ݒ�
	//SetTriangle(�e, �e�s��, ���_1, ���_2, ���_3)
	void Set(CCharacter *parent, CMatrix *matrix
		, const CVector &v0, const CVector &v1, const CVector &v2);
	//�`��
	void Render();
	//�D��x�̕ύX
	void ChangePriority();
	//���f������R���C�_�̐���
	//Mesh(�e, �e�s��, ���f��)
	static void Mesh(CCharacter* parent, CMatrix* matrix, CModel *model);

	void Update();

	CVector WorldGreater()
	{
		CVector m = CCollider::mV[0];
		m = m.Greater(CCollider::mV[1]);
		m = m.Greater(CCollider::mV[2]);
		return m;
	}

	CVector WorldLess()
	{
		CVector m = CCollider::mV[0];
		m = m.Less(CCollider::mV[1]);
		m = m.Less(CCollider::mV[2]);
		return m;
	}

private:
	//���_
	CVector mV[4];
};

#endif