#ifndef CPLAYER_H
#define CPLAYER_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"

class CPlayer :public CCharacter{
private:
protected:
public:
	static CPlayer*mpPlayer;
	//デフォルトコンストラクタ
	CPlayer();

	//更新
	void Update();

	//プレイヤーの体の当たり判定
	CCollider mColBody;
	//プレイヤーのタイヤの当たり判定
	CCollider mColTire;

	//衝突処理
	void Collision(CCollider *mc, CCollider *yc);

	//ジャンプ速度の変数
	float mVelocityJump;
	//ジャンプ力(ジャンプ初速)の変数
	float mJumpV0;

	//ジャンプを当たり判定よりも早く処理させるもの
	int mJumpPrio;

	//移動速度
	float mMoveSpeed;
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;

	//回転速度
	float mTurnSpeed;

	bool mCanJump;//ジャンプ可能か(≒地面に足が着いてるか)
	int mCanSwim;//水泳可能か

	CSound SoundJump;
	CSound SoundShot;
	CSound SoundItemGet;
	CSound SoundBoost;
	CSound SoundEngine;//一番の難題
	CSound SoundEngine_Turf;//芝生の上では別の音が鳴る仕様
	bool isSoundEngine;
	CSound SoundHorn;
	int mBuzzerCount;//クラクションを鳴らした回数
	CSound SoundCollision;
	CSound SoundCollisionSmall;
	bool isRespawn;
	int mRespawnCount;

	float mStartPoint[3];//{ X,Y,Z }
	float mStartRotation;//Y軸のみ

	bool mIsGetKey;
	bool mHaveBoat;

	bool mFlyingMode;//デバッグ用：自由落下無効

	int mChecks;
	bool isTouchGoal;//ゴール地点に入っているか
	int mGoalTime;
	int mRank;

	bool isBoost;//ブースト中か(加速床で一定時間有効)
	float mBoostMaxSpeed;//ブーストで底上げされる最高速度の数値
	int mBoostTime;//ブースト状態が継続される時間

	bool CanMove;//プレイヤーが操作可能か否か(カウントダウン前・ゴール後などは否)

	//コライダの更新
	void TaskCollision();
};

#endif