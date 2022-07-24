#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//タスクマネージャのインクルード
#include "CTaskManager.h"
/*
コリジョンマネージャ
コライダのリスト管理
*/
class CCollisionManager : public CTaskManager {
public:
	//衝突処理
	void Collision();
};
//他で使えるように外部参照
extern CCollisionManager CollisionManager;

#endif
