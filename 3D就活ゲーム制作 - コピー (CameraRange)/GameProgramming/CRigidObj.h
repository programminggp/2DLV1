#ifndef CRIGIDOBJ_H
#define CRIGIDOBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CRigidObj :public CCharacter{
public:
	static CRigidObj*mpRigObj;
	
	//コライダの追加
	CCollider *mpCollider;
	
	//コンストラクタで初期設定
	CRigidObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
	~CRigidObj();
	////デフォルトコンストラクタ
	//CRigidObj();

	//更新
	void Update();

	//プレイヤーの体の当たり判定
	CCollider mColBody;
	CCollider mColBody2nd;

	//衝突処理
	void Collision(CCollider *mc, CCollider *yc);

	//ジャンプ速度の変数
	float mVelocity;
	int mJumpPrio;

	//bool CanMove;//プレイヤーが操作可能か否か(カウントダウン前・ゴール後などは否)

	//コライダの更新
	void TaskCollision();
};


#endif