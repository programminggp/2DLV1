#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"

/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy : public CCharacter {
public:
	int mHp;				//HP
	CCollider mCollider;	//衝突判定用コライダ
	CCollider mSearch;		//索敵用コライダ
	CVector *mpTarget;		//目指すターゲット
	CVector mPoint;			//目指すポイント
	int mPointCnt;			//ポイントのカウンタ
	int mFireBullet;		//発射間隔
	float mVelocity;		//飛行速度

	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider *m, CCollider *y);
};

#endif
