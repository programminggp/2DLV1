#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CCollider.h"
#include"CModelX.h"

class CXEnemy :public CXCharacter {
public:
	//更新処理
	void Update();
	CXEnemy();
	void Init(CModelX* model);
	//衝突処理
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	//コライダ宣言
	CCollider mColSphereBody; //体
	CCollider mColSphereHead; //頭
	CCollider mColSphereSword0; //剣
	CCollider mColSphereSword1;
	CCollider mColSphereSword2;
};



#endif