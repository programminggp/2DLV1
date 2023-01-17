#ifndef CCOLLIDERCAPSULE_H
#define CCOLLIDERCAPSULE_H

#include "CCollider.h"
/*
カプセルコライダの定義
*/
class CColliderCapsule : public CCollider
{
public:
	CColliderCapsule() {}
	//コンストラクタ（線分コライダ）
	//CColliderLine(親, 親行列, 頂点1, 頂点2, 半径)
	CColliderCapsule(CCharacter* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, float radius);
	//線分コライダの設定
	//Set(親, 親行列, 頂点1, 頂点2, 半径)
	void Set(CCharacter* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, float radius);
	//描画
	void Render();
	//優先度の変更
	void ChangePriority();
};

#endif

