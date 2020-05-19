#ifndef CCUBE_H
#define CCUBE_H

#include "CCharacter.h"
//06
#include "CCollider.h"

#include <vector>

class CCube : public CCharacter {
public:
	//コライダの追加
	CCollider mColTriangle[12];
	//コンストラクタで初期設定
	CCube(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	~CCube();

//	void Render() {}
};



#endif
