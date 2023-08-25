#ifndef CCOLLIDERCUPSULE_H
#define CCOLLIDERCUPSULE_H

#include "CColliderLine.h"

class CColliderCapsule : public CColliderLine
{
public:
	//�R���X�g���N�^�i�J�v�Z���R���C�_�j
	//CColliderCapsule(�e, �e�s��, ���_1, ���_2, ���a)
	CColliderCapsule(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	//�J�v�Z���R���C�_�̐ݒ�
	//Set(�e, �e�s��, ���_1, ���_2, ���a)
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	void Render();
	CVector& Sp() { return mSp; }
	CVector& Ep() { return mEp; }
	void Update();
private:
	CVector mSp;
	CVector mEp;
};


#endif
