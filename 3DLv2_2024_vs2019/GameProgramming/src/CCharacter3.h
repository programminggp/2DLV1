#ifndef CCHARACTER3_H
#define CCHARACTER3_H
//変換行列クラスのインクルード
#include "CTransform.h"
//モデルクラスのインクルード
#include "CModel.h"
#include "CTask.h"
//コライダクラスの宣言
class CCollider;

/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter3 : public CTransform, public CTask {
public:
	enum class ETag
	{
		EZERO,
		EPLAYER,
		EENEMY,
	};
	enum class EState
	{
		EZERO,
		EIDLE,
		EWALK,
		ERUN,
		EATTACK,
		EHIT,
		EDEATH,
		EJUMP,
	};
	//衝突処理
	virtual void Collision(CCollider* m, CCollider* o) {}
	//コンストラクタ
	CCharacter3();
	//コンストラクタ
	CCharacter3(int priority, ETag tag);
	CCharacter3(ETag tag);
	//デストラクタ
	~CCharacter3();
	//モデルの設定
	//Model(モデルクラスのポインタ)
	void Model(CModel* m);
	//描画処理
	void Render();
	void Tag(ETag t)
	{
		mTag = t;
	}
	ETag Tag()
	{
		return mTag;
	}
	EState State()
	{
		return mState;
	}
protected:
	CVector mAdjust;
	bool mGrounded;
	CVector mTargetPosition;
	float mGravity;
	float mVelocityG;
	float mVelocity;

	ETag mTag;
	EState mState;
	CModel* mpModel; //モデルのポインタ
};

#endif

