#ifndef CENEMY2_H
#define CENEMY2_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy2 : public CCharacter {
public:
	//コンストラクタ
	CEnemy2();
	//CEnemy(位置, 回転, 拡縮)
	CEnemy2(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
private:
	//モデルデータ
	static CModel mModel;
	//コライダ
	CCollider mCollider;
};

#endif
