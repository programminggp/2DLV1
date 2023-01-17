#ifndef CXMUTANT_H
#define CXMUTANT_H

#include"CXCharacter.h"
#include"CCollider.h"
#include"CModelX.h"
#include"CColliderCapsule.h"

class CXMutant :public CXCharacter {
public:
	//更新処理
	void Update();
	CXMutant();
	void Init(CModelX* model);
	void TaskCollision();
	void Collision(CCollider* m, CCollider* o);
	int MutantHp; //体力
private:
	CColliderCapsule mColCapBody; //胴体
	CCollider mColSphereArm; //腕
	CCollider mCore; //コア
	CVector mPoint;  
};
#endif