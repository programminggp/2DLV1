#ifndef CENEMY_H
#define CENEMY_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"
#include "CSound.h"
#include "CPoint.h"

class CEnemy :public CCharacter{
public:
	static CEnemy*mpEnemy;
	//デフォルトコンストラクタ
	CEnemy();

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

	//移動速度
	float mMoveSpeed;
	float mADMoveX;
	float mWSMoveZ;
	float mCarSpeed;
	//敵AIの強さによるスピード差
	float mCPULevelSpeed;

	//回転速度
	float mTurnSpeed;

	bool mCanJump;//ジャンプ可能か(≒地面に足が着いてるか)

	CSound SoundBoost;
	CSound SoundEngine;//一番の難題
	bool isSoundEngine;
	CSound SoundCollision;
	CSound SoundCollisionSmall;
	CSound SoundRespawn;
	CSound SoundRespawn2;
	int mRespawnCount;

	float mStartPoint[3];//{ X,Y,Z }

	int mChecks;

	bool isBoost;//ブースト中か(加速床で一定時間有効)
	float mBoostMaxSpeed;//ブーストで底上げされる最高速度の数値
	int mBoostTime;//ブースト状態が継続される時間

	bool CanMove;//プレイヤーが操作可能か否か(カウントダウン前・ゴール後などは否)

	static int RenderType;//ゲーム画面の描画とミニマップの描画を分ける変数

	//コライダの更新
	void TaskCollision();

	//誘導ポイント//中心、全エネミー共通のポイント
	static CPoint *mPoint;
	static CPoint *mPoint2;
	static CPoint *mPoint3;
	static CPoint *mPoint4;
	static CPoint *mPoint5;
	static CPoint *mPoint6;
	static CPoint *mPoint7;
	static CPoint *mPoint8;
	static CPoint *mPoint9;
	static CPoint *mPoint10;
	static CPoint *mPoint11;
	static CPoint *mPoint12;
	static CPoint *mPoint13;
	static CPoint *mPoint14;
	static CPoint *mPoint15;
	static CPoint *mPoint16;
	static CPoint *mPoint17;
	static CPoint *mPoint18;
	static CPoint *mPoint19;
	static CPoint *mPoint20;
	static CPoint *mPoint21;
	static CPoint *mPoint22;
	static CPoint *mPoint23;
	//
	static CPoint *mPoint24;
	static CPoint *mPoint25;
	static CPoint *mPoint26;
	static CPoint *mPoint27;
	static CPoint *mPoint28;
	static CPoint *mPoint29;
	static CPoint *mPoint30;
	static CPoint *mPoint31;
	static CPoint *mPoint32;
	static CPoint *mPoint33;
	static CPoint *mPoint34;
	static CPoint *mPoint35;
	static CPoint *mPoint36;
	static CPoint *mPoint37;
	static CPoint *mPoint38;
	static CPoint *mPoint39;
	static CPoint *mPoint40;
	static CPoint *mPoint41;
	static CPoint *mPoint42;
	static CPoint *mPoint43;
	static CPoint *mPoint44;
	static CPoint *mPoint45;
	static CPoint *mPoint46;
	static CPoint *mPoint47;
	static int mPointSize;//ポイントの数
	CPoint *mpPoint;//目指すポイント
	int mPointCnt;//ポイントのカウンタ
	//次のポイントまでに出す最高速度
	float mMaxSpeed_PtoP;

	//コライダ
	CCollider mSearch;

	CVector mVPoint;

	int mEnemyLap;
	bool isTouchGoal;//ゴール地点に入っているか
	bool isEnemyGoaled;
	int mGoalTime;
	int mRank;

	//ポイントへのベクトルを求める
	//CVector dir = mpPoint->mPosition - mPosition;
	CVector dir;
	//左方向へのベクトルを求める
	CVector left;
};


#endif