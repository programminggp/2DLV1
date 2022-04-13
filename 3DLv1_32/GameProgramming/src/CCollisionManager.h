#ifndef CCOLLISIONMANAGER
#define CCOLLISIONMANAGER

//タスクマネージャのクラスのインクルード
#include "CTaskManager.h"
//衝突処理範囲より離れているコライダは衝突処理しない
#define COLLISIONRANGE 30

/*
コリジョンマネージャクラス
親:CTaskManagerクラス　子:CCollisionManagerクラス
*/
class CCollisionManager : public CTaskManager
{
public:
	//インスタンスの取得
	static CCollisionManager* Get();
	//衝突処理
	void Collision();
	//
	void CCollisionManager::Collision(CCollider* c, int range);
private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;

};
#endif

