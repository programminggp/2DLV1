#ifndef COBJ_H
#define COBJ_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CObj :public CCharacter{
public:
	//コライダの追加
	CCollider *mpCollider;
	//コンストラクタで初期設定
	CObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider = true);
	~CObj();

	int mObjNumber;
	
	////衝突処理
	//void Collision(CCollider *m, CCollider *y);

	void Update();//virtual…再定義可能になる?

	//bool mDeleteFlag;

	////コライダの更新
	//void TaskCollision();

	////ジャンプ速度の変数
	//float mVelocity;
};

//class CObjection :public CObj{
//public:
//	//コライダの更新
//	void TaskCollision();
//};
#endif