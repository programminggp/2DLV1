#ifndef CENEMY_H
#define CENEMY_H
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
class CEnemy : public CCharacter {
//	float mRx;
public:
	int mHp;
	//コライダ
	CCollider mCollider;
	CCollider mSearch;
//	CCollider mSearch2;
	//?
	//誘導ポイント
	static CPoint *mPoint;
	static int mPointSize;//ポイントの数
	CPoint *mpPoint;//目指すポイント
	int mPointCnt;//ポイントのカウンタ
	//コンストラクタ
	//CEnemy(モデル, 位置, 回転, 拡縮)
	CEnemy(CModel *model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider *m, CCollider *y);

	//void Render() {
	//	CCharacter::Render();
	//	mCollider.Render();
	//}
};

#endif
