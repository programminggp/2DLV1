#ifndef CCAMERARANGE_H
#define CCAMERARANGE_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CCameraRange :public CCharacter{
private:
	//カメラの当たり判定
	CCollider mColRange;
public:
	static CCameraRange*mpCameraRange;
	//デフォルトコンストラクタ
	CCameraRange();

	//更新
	void Update();	

	//コライダの更新
	void TaskCollision();	
};


#endif