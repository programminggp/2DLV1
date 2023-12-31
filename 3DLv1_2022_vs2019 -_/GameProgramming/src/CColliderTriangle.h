#ifndef CCOLLIDERTRIANGLE_H
#define CCOLLIDERTRIANGLE_H
#include "CCollider.h"
/*
三角形コライダの定義
*/
class CColliderTriangle : public CCollider
{
public:
	void ChangePriority();
	CColliderTriangle(){}
	//コンストラクタ(三角コライダ)
	//CColliderTriangle(親、親行列、頂点１、頂点２、頂点３)
	CColliderTriangle(CCharacter3* paretpnt, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//三角コライダの設定
	//Set(親、親行列、頂点１、頂点２、頂点３)
	void Set(CCharacter3* paretpnt, CMatrix* matrix
		, const CVector& v0, const CVector& v1, const CVector& v2);
	//描画
	void Render();
	//
	//void Update();
};
#endif