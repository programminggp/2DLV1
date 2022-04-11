#ifndef CCOLLIDERTRIANGLE
#define CCOLLIDERTRIANGLE
#include "CCollider.h"
/*
�O�p�`�R���C�_�̒�`
*/
class CColliderTriangle : public CCollider{
public:
	CColliderTriangle(){}
	//�R���X�g���N�^(�O�p�R���C�_)
	//CColliderTriangle(�e,�e�s��,���_1,���_2,���_3,)
	CColliderTriangle(CCharacter* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, const CVector& v2);
	//�O�p�R���C�_�̐ݒ�
	//Set(�e,�e�s��,���_1,���_2,���_�R)
	void Set(CCharacter* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, const CVector& v2);

	//�`��
	void Render();
};
#endif //�I��

