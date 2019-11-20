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
	int mHp;
	//コライダ
	CCollider mCollider;
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
