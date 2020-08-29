#ifndef CMISSILE_H
#define CMISSILE_H

#include "CCharacter.h"
#include "CCollider.h"
/*
�~�T�C���N���X
*/
class CMissile : public CCharacter {
public:
	int mLife;
	CCharacter *mpPoint;

	//�~�T�C���ɃR���C�_
	CCollider mCollider;
	//�R���X�g���N�^
	//CMissile(���f��, �ʒu, ��], �g�k)
	CMissile(CModel *model, CVector position, CVector rotation, CVector scale);
	//
	void Update();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);
};

#endif
