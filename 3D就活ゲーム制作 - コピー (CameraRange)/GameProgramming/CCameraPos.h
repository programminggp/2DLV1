#ifndef CCAMERAPOS_H
#define CCAMERAPOS_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CCameraPos :public CCharacter{
private:
	float mZoom_distance;
	float mCameraSpeed;
	//カメラの当たり判定
	CCollider mColCam;
public:
	static CCameraPos*mpCamera;	
	//デフォルトコンストラクタ
	CCameraPos();
	//更新処理
	void Update();	
	//衝突処理
	void Collision(CCollider *mc, CCollider *yc);		
	//コライダの更新
	void TaskCollision();	
};


#endif