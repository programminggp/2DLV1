#ifndef CC5_H
#define CC5_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
//
#include "CPoint.h"

/*
エネミークラス
キャラクタクラスを継承
*/
class CC5 : public CCharacter {
public:
	CPoint *mpPoint;//目指すポイント
	int mHp;
	//コライダ
	CCollider mCollider;
	CCollider mSearch;
	//コンストラクタ
	//CC5(モデル, 位置, 回転, 拡縮)
	CC5(CModel *model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider *m, CCollider *y);

};


#endif
