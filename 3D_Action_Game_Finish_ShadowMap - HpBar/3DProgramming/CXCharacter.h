#ifndef CXCHARCTER_H
#define CXCHARCTER_H

#include "CModelX.h"
#include "CMatrix44.h"
#include "CTask.h"

//27 コライダクラスの宣言
class CCollider;

class CXCharacter : public CTask {
public:
	//27 キャラクターの識別
	enum ECharTag {
		EPLAYER = 1,
		EENEMY,
	};
	ECharTag mTag;	//キャラクタ識別タグ
	enum EState {
		EIDLE,
		EWALK,
		EATTACK,
		EATTACKR,
		EAVOIDANCEL,
		EAVOIDANCER,
		EDOWN,
	};
	EState mState;

	CModelX *mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize;	//アニメーションの再生フレーム数
	CVector3 mPosition;	//位置
	CVector3 mRotation;	//回転
	CVector3 mScale;
	CMatrix44 mMatrix;	//位置回転行列
	CMatrix44 *mpCombinedMatrix;	//合成行列退避

	//30
	float mVelocityG; //重力速度

	//35
	CVector3 mCameraRotation; //カメラの回転

	bool mHitFlg;

	CVector3 mAdjust;

	CXCharacter()
		: mpCombinedMatrix(0), mVelocityG(0.0f), mHitFlg(true), mState(EIDLE), mScale(1.0f, 1.0f, 1.0f)
	{

	}

	~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}

	//初期化処理
	void Init(CModelX *model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix44 &m, bool addframe);
	//描画処理
	void Render();
	//更新処理
	void Update();
	//27 衝突処理
	virtual bool Collision(CCollider*, CCollider*){
		return false;
	};
	//30 重力処理
	void Gravity();
	//35 カメラ位置の取得
	CVector3 GetCameraPosition();
	CVector3 GetTargetPosition();
	void UpdateAdjust(const CVector3 v);
};

#endif
