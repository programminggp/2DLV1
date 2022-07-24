#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//
#include "CCollider.h"
/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CCharacter {
public:
	static CPlayer *sPlayer;
	//コライダ
	CCollider mLine[4];//線分コライダ
	CCollider mCollider;
	CCollider mSearch;
	CCharacter *mpTarget;
	int mFireMissile;
	int mFireBullet;
	float mVelocity;
	//デフォルトコンストラクタ
	CPlayer();
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider *mc, CCollider *yc);

};

#endif
