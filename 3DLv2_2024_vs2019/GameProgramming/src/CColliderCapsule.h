#ifndef CCOLLIDERCUPSULE_H
#define CCOLLIDERCUPSULE_H
#include "CCollider.h"
//カプセルコライダクラス
class CColliderCapsule : public CCollider
{
public:
	//コンストラクタ（カプセルコライダ）
	//CColliderCapsule(親, 親行列, 頂点1, 頂点2, 直径)
	CColliderCapsule(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	//カプセルコライダの設定
	//Set(親, 親行列, 頂点1, 頂点2, 直径)
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	void Render(); //コライダの描画
	void Update(); //座標の更新
	void ChangePriority(); //優先順位の更新
private:
	CVector mSp; //始点
	CVector mEp; //終点
};
#endif

