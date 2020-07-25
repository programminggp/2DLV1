#ifndef COBJ_H
#define COBJ_H

#include "CCharacter.h"
#include "CCollider.h"

class CObj : public CCharacter {
public:
	//�R���C�_�̒ǉ�
	CCollider *mpCollider;
	//�R���X�g���N�^�ŏ����ݒ�
	CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	~CObj();
};

#endif
