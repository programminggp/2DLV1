#ifndef CXMUTANT_H
#define CXMUTANT_H

#include"CXCharacter.h"
#include"CCollider.h"
#include"CModelX.h"
#include"CColliderCapsule.h"

class CXMutant :public CXCharacter {
public:
	//�X�V����
	void Update();
	CXMutant();
	void Init(CModelX* model);
	void TaskCollision();
	void Collision(CCollider* m, CCollider* o);
	int MutantHp; //�̗�
private:
	CColliderCapsule mColCapBody; //����
	CCollider mColSphereArm; //�r
	CCollider mCore; //�R�A
	CVector mPoint;  
};
#endif