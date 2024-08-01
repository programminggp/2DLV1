#ifndef CCOLLIDERCUPSULE_H
#define CCOLLIDERCUPSULE_H
#include "CCollider.h"
//�J�v�Z���R���C�_�N���X
class CColliderCapsule : public CCollider
{
public:
	//�R���X�g���N�^�i�J�v�Z���R���C�_�j
	//CColliderCapsule(�e, �e�s��, ���_1, ���_2, ���a)
	CColliderCapsule(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	//�J�v�Z���R���C�_�̐ݒ�
	//Set(�e, �e�s��, ���_1, ���_2, ���a)
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	void Render(); //�R���C�_�̕`��
	void Update(); //���W�̍X�V
	void ChangePriority(); //�D�揇�ʂ̍X�V
private:
	CVector mSp; //�n�_
	CVector mEp; //�I�_
};
#endif

