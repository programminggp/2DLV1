#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTransform {
public:
	//コンストラクタ
	//CCollider(親, 親行列, 位置, 半径)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//親ポインタの取得
	CCharacter3* Parent();
	//描画
	void Render();
protected:
	CCharacter3* mpParent;//親
	CMatrix* mpMatrix;//親行列
	float mRadius;	//半径
};
#endif
