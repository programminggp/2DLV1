#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include "CCollider.h"
/*
三角形コライダの定義
*/
class CColliderTriangle : public CCollider
{
public:
	//優先度の変更
	void ChangePriority();
	CColliderTriangle() {}
	//コンストラクタ（三角コライダ）
	//CColliderTriangle(親, 親行列, 頂点1, 頂点2, 頂点3)
	CColliderTriangle(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//三角コライダの設定
	//Set(親, 親行列, 頂点1, 頂点2, 頂点3)
	void Set(CCharacter3* parent, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//描画
	void Render();
};
#endif
