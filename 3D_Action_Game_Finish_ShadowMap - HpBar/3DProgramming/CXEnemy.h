#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollision.h"
#include "CBillBoard.h"

class CXEnemy : public CXCharacter {
public:
	CEffectHit mBillBorad;
	//25
	//�R���C�_�̐錾
	CSphereCollider *mpColSphereBody;
	CSphereCollider *mpColSphereHead;
	CSphereCollider *mpColSphereSword;
	//31
	CXCharacter *mpPlayer;	//�v���C���[�|�C���^
	//�����������̉�]�Ɏg�p
	float radian;
	//�R���C�_�̏�����
	CXEnemy()
		: mpColSphereBody(0)
		, mpColSphereHead(0)
		, mpColSphereSword(0)
		//31
		, mpPlayer(0)
		, radian(0.0f)
	{
		mTag = EENEMY;	//27 �^�O�ɓG�ݒ�
	}
	//36
	CXEnemy(CModelX *m, CVector3 pos)
		: CXEnemy() {
		Init(m); //����������
		mPosition = pos; //�ʒu�ݒ�
		//Task�}�l�[�W���ɒǉ�
		CTaskManager::Get()->Add(this);
	}

	~CXEnemy() {
		//�R���C�_�̍폜
		//35 �폜�̍폜
		//if (mpColSphereBody)
		//	delete mpColSphereBody;
		//mpColSphereBody = 0;
		//if (mpColSphereHead)
		//	delete mpColSphereHead;
		//mpColSphereHead = 0;
		//if (mpColSphereSword)
		//	delete mpColSphereSword;
		//mpColSphereSword = 0;
	}

	void Init(CModelX*);
	void Update();
	//27 �Փˏ���
	bool Collision(CCollider *m, CCollider *y);
};

#endif
