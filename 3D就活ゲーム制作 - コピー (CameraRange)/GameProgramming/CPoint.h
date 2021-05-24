#ifndef CPOINT_H
#define CPOINT_H
#include "CCollider.h"
#include "CCharacter.h"

/*
ポイントクラス
敵機などの目標にする
*/
class CPoint : public CCharacter{
	CCollider mCollider; //コライダの追加
	CPoint* mpNext;	//次のポイント
public:
	CPoint();
	//CPoint(位置, 半径, 次ポインタ)
	CPoint(const CVector& pos, float r, CPoint* next = nullptr);
	//設定
	//Set(位置, 半径, 次ポインタ)
	void Set(const CVector& pos, float r, CPoint* next = nullptr);
	//次のポイントの取得
	CPoint* GetNextPoint();
#ifdef _DEBUG
	void Render();
#endif
};
#endif