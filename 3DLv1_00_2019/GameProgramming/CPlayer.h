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
	//コライダ
	CCollider mLine[4];//線分コライダ
//	CCollider mCollider;
	//デフォルトコンストラクタ
	CPlayer();
	//更新処理
	void Update();
};

#endif
