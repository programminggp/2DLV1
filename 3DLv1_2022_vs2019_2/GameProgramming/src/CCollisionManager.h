#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

//衝突処理範囲より離れているコライダは衝突処理しない
#define COLLISIONRANGE 30

class CCollisionManager : public CTaskManager
{
public:
	//衝突処理
	//Collision(コライダ, 範囲)
	//コライダの優先度+範囲～優先度-範囲までのコライダと衝突判定を実行する
	void Collision(CCollider* c, int range);
	//衝突処理
	void Collision();
	//インスタンスの取得
	static CCollisionManager* Instance();
private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
};

#endif
