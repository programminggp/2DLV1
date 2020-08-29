#ifndef CAIRBASE_H
#define CAIRBASE_H

#include "CCharacter.h"
#include "CCollider.h"
/*
�q���n�N���X
*/
class CAirBase : public CCharacter {
public:
	//�_���[�W
	int mDamage;

	//�ǐ����ɃR���C�_
	CCollider mCollider;
	//�R���X�g���N�^
	//CAirBase(���f��, �ʒu, ��], �g�k)
	CAirBase(CModel *model, CVector position, CVector rotation, CVector scale);
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);
};


#endif
