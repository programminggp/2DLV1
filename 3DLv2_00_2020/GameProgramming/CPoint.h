#ifndef CPOINT_H
#define CPOINT_H
#include "CCollider.h"
#include "CCharacter.h"
/*
ポイントクラス
敵機などの目標にする
*/
class CPoint : public CCharacter {
public:
	//コライダ追加
	CCollider mCollider;
	CPoint();
	//コンストラクタ
	//CPoint(位置, 半径)
	//CPoint(const CVector &pos, float r);
	//設定
	//Set(位置, 半径)
	void Set(const CVector &pos, float r);
};

#endif
