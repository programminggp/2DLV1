#ifndef CCHARACTER_H
#define CCHARACTER_H
//変換行列クラスのインクルード
#include "CTransform.h"
//モデルクラスのインクルード
#include "CModel.h"
//
#include "CTask.h"
//コライダクラスの宣言
class CCollider;

/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter : public CTransform ,public CTask {
public:
	enum ETag
	{
		EZERO,		//初期値
		EPLAYER,	//プレイヤー
		EENEMY,		//敵
		EBULLETPLAYER,	//プレイヤー弾
		EBULLETENEMY,	//敵弾
	};
	enum EState
	{
		ESTATEZERO,
		EALL,
		EIDLE,
		EWALK,
		EATTACK,
		EDEATH,
		EJUMP,
		EDAMAGE, 
	};
	//モデルの設定
	//Model(モデルクラスのポインタ)
	void Model(CModel *m);
	//タグの取得
	ETag Tag();
	EState State();
	const CVector& KnockBack();
	float AttackPower();
	//描画処理
	void Render();
	//デストラクタ
	~CCharacter();
	//コンストラクタ
	CCharacter();
	//コンストラクタ
	//priority：優先度
	CCharacter(int priority);
	//衝突処理
	virtual void Collision(CCollider *m, CCollider *o) {}
protected:
	CModel* mpModel; //モデルのポインタ
	ETag mTag;
	EState mState;
	float mAttackPower;
	CVector mKnockBack;
};

#endif
