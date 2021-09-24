#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword;	//��
public:

	CXPlayer();

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	void Update();
};

#endif
