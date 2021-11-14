#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//タスクマネージャのインクルード
#include "CTaskManager.h"
class CCollider;

/*
コリジョンマネージャ
コライダのリスト管理
*/
class CCollisionManager : public CTaskManager {
public:
	//衝突処理
	void Collision();

	void Collision(CCollider *collider);
};
//他で使えるように外部参照する
extern CCollisionManager CollisionManager;

#endif
