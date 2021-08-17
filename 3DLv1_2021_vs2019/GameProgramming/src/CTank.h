#ifndef CTANK_H
#define CTANK_H

//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"

/*
主砲クラス
*/
class CTank3 : public CCharacter
{
public:
	CTank3(CCharacter* parent);
	void Update();
//	void Render();
private:
	static CModel mModel;
	CCharacter* mpParent;
	CMatrix mOffset;
};

//class CTank2 : public CTransform
/*
砲塔クラス
*/
class CTank2 : public CCharacter
{
public:
	CTank2(CCharacter* parent);
	void Update();
private:
	static CModel mModel;
	CCharacter* mpParent;
	CMatrix mOffset;
};

/*
戦車クラス
キャラクタクラスを継承
*/
class CTank : public CCharacter {
public:
	//コンストラクタ
	CTank();
	//Tank(位置, 回転, 拡縮)
	CTank(const CVector& position, const CVector& rotation, const CVector& scale);
	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
	CCharacter* Tank();
private:
	//モデルデータ
	static CModel mModel;
	//コライダ
	CCollider mCollider;
	int mHp;	//ヒットポイント
	int mFireCount;
	CTank2 *mpTank2;
};


#endif

