#ifndef CCOLLIDERCUPSULE_H
#define CCOLLIDERCUPSULE_H

#include "CColliderLine.h"

class CColliderCapsule : public CColliderLine
{
public:
	//コンストラクタ（カプセルコライダ）
	//CColliderCapsule(親, 親行列, 頂点1, 頂点2, 直径)
	CColliderCapsule(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	//カプセルコライダの設定
	//Set(親, 親行列, 頂点1, 頂点2, 直径)
	void Set(CCharacter3* parent, CMatrix* matrix, const CVector& v0, const CVector& v1, float radius);
	void Render();
	CVector& Sp() { return mSp; }
	CVector& Ep() { return mEp; }
	void Update();
private:
	CVector mSp;
	CVector mEp;
};


#endif
