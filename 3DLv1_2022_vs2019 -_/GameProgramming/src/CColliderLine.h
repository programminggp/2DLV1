#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include "CCollider.h"
/*
線分コライダの定義
*/
class CColliderLine : public CCollider
{
public:
	void ChangePriority();
	CColliderLine(){}
	//コンストラクタ(線分コライダ)
	//CColliderLine(親、親行列、頂点１、頂点２)
	CColliderLine(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//線分コライダの設定
	//Set(親、親行列、頂点１、頂点２)
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1);
	//描画
	void Render();
};
#endif