#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CColliderTriangle.h"

class CXPlayer : public CXCharacter
{
	static CCharacter* spInstance;
	static CModelX mModel;
	float mJumpV;
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
	CColliderLine mColLine;

public:
	CXPlayer();
	CXPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	//void Init(CModelX* model);

	void Update();

	void TaskCollision();

	void Collision(CCollider* m, CCollider* o);
};

#endif