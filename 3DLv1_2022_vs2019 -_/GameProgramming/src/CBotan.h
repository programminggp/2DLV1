#ifndef CBOTAN_H
#define CBOTAN_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CBotan : public CCharacter3 {
public:
	void Collision();
	//衝突処理
	//Collision(コライダ１、コライダ２)
	void Collision(CCollider* m, CCollider* o);
	//コンストラクタ
	//CEnemy(モデル、位置、回転、拡縮)
	CBotan(CModel* model, const CVector& position,
		const CVector& ratation, const CVector& scale);
	//更新処理
	void Update();
private:
	//コライダ
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif
