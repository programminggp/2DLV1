#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CCollider.h"
#include"CModelX.h"

class CXEnemy :public CXCharacter {
public:
	//�X�V����
	void Update();
	CXEnemy();
	void Init(CModelX* model);
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	//�R���C�_�錾
	CCollider mColSphereBody; //��
	CCollider mColSphereHead; //��
	CCollider mColSphereSword0; //��
	CCollider mColSphereSword1;
	CCollider mColSphereSword2;
};



#endif