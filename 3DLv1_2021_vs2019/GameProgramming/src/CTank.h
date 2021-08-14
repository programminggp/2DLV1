#ifndef CTANK_H
#define CTANK_H

//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"


class CTank3 : public CTransform
{
public:
	CTank3(CTransform* parent);
	void Update();
	void Render();
private:
	static CModel mModel;
	CTransform* mpParent;
	CMatrix mOffset;
};

class CTank2 : public CTransform
{
public:
	CTank2(CTransform* parent);
	void Update();
	void Render();
private:
	static CModel mModel;
	CTransform* mpParent;
	CTank3 mTank;
	CMatrix mOffset;
};

/*
エネミークラス
キャラクタクラスを継承
*/
class CTank : public CCharacter {
public:
	//コンストラクタ
	CTank();
	//CEnemy(位置, 回転, 拡縮)
	CTank(const CVector& position, const CVector& rotation, const CVector& scale);
	//更新処理
	void Update();
	void Render();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
	CTransform* Tank();
private:
	//モデルデータ
	static CModel mModel;
	//コライダ
	CCollider mCollider;
	CCharacter* mpPlayer;	//プレイヤーのポインタ
	CCollider mColSearch;	//サーチ用コライダ
	int mHp;	//ヒットポイント
	int mFireCount;
	CVector mPoint;	//目標地点
	CTank2 mTank2;
};


#endif

