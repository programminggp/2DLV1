#include "CObj.h"
#include "CItem.h"
#include "CPlayer.h"
#include "CTaskManager.h"

#define DOOR_RANGEOFMOTION 90 //ドアの可動域
#define DOOR_OPENSPEED 2 //ドアの開く速度
#define ROLLINGSPEED 1.0f //回転する足場の回転速度

#define G (9.8f / 120.0f)//重力加速度//60.0f

//コンストラクタ
//model:モデルのポインタ position:位置 rotation:回転 scale:拡縮 hascollider:コライダの生成の有無(設定がなければ有)
CObj::CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider)
:mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	
	mObjNumber = 1;

	if (mObjNumber == 9){
		mTag = EWATER;
	}
	if (mObjNumber >= 18 && mObjNumber <= 20){
		mTag = ECLEARWATER;
	}
	/*if (mObjNumber == 20){
		mTag = ECLEARWATER;
	}*/

	if (mObjNumber == 101){
		//チェックポイント
		mTag = ECHECKPOINT;
		CCharacter::isRender = false;//描画しない
		//優先度変更
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 102){
		//チェックポイント
		mTag = ECHECKPOINT2;
		CCharacter::isRender = false;//描画しない
		//優先度変更
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 103){
		//チェックポイント
		mTag = ECHECKPOINT3;
		CCharacter::isRender = false;//描画しない
		//優先度変更
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 109){
		//ゴールポイント(1周したと扱われる地点)
		mTag = EGOALPOINT;
		//優先度変更
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 202){
		//ジャンプ台
		mTag = EJUMPER;
	}

	if (hascollider == false){
		//当たり判定を生成しない
		//これにより当たり判定の数を増やすほど処理が重くなることが実証された
		//逆に当たり判定を増やさなければいいので、必要ない当たり判定はどんどんカットしていくよ。
	}
	else{
		CCharacter::Update();
		//モデルの三角形の数分、コライダの配列を作成します
		mpCollider = new CCollider[model->mTriangles.size()];
		for (int i = 0; i < model->mTriangles.size(); i++){
			//コライダを三角形コライダで設定していきます
			mpCollider[i].SetTriangle(this,
				model->mTriangles[i].mV[0],
				model->mTriangles[i].mV[1],
				model->mTriangles[i].mV[2]);
			mpCollider[i].ChangePriority();
		}
	}
}
//デストラクタ
CObj::~CObj(){
	//コライダがあれば削除
	if (mpCollider){
		//delete[] 配列を削除
		delete[] mpCollider;
	}
}

void CObj::Update(){
	if (mObjNumber == 18){
		//ボートを取得しないと表示されないよ！
		if (CPlayer::mpPlayer->mHaveBoat == false){
			mScale.mY = 0.0f;
		}
		//取得すれば表示されるよ！
		else{
			mScale.mY = 35.7f;
			mRotation.mY += 3;
		}
	}

	if (mObjNumber == 21){//仮の番号
		//川を流れるブロック？
		mPosition.mX += 0.4f;
		if (mPosition.mX > 200.0f){
			mPosition.mX = -200.0f;
		}
	}
	if (mObjNumber == 25){//回レ回レ
		mRotation.mX += ROLLINGSPEED;
	}
	if (mObjNumber == 26){//ゆっっっくりY軸回転
		mRotation.mY += 0.01f;
	}

	if (mObjNumber == 31){//仮の番号
		//川を流れるブロック？
		mPosition.mX += 2.5f;
		if (mPosition.mX > 3200.0f){
			mPosition.mX = 0.0f;
		}
	}

	if (mObjNumber == 334){
		mScale.mX += 0.1f;
		mScale.mY += 0.1f;
		mScale.mZ += 0.1f;
	}
	if (mObjNumber == 575){
		mPosition.mX = CPlayer::mpPlayer->mPosition.mX;
		mPosition.mZ = CPlayer::mpPlayer->mPosition.mZ;
		mRotation.mY = CPlayer::mpPlayer->mRotation.mY;
	}

	CCharacter::Update();

	if (mObjNumber == 10){
		if (CItem::mTargetAmount <= 0){
			SetEnabled(false);
		}
	}
	if (mObjNumber == 22){
		if (CPlayer::mpPlayer->mIsGetKey){
			if (mRotation.mY < DOOR_RANGEOFMOTION){
				mRotation.mY += DOOR_OPENSPEED;
				mPosition.mX -= DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
				mPosition.mZ -= DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
			}
		}
		else{
			//ドアが閉まる
			if (mRotation.mY > 0.0f){
				mRotation.mY -= DOOR_OPENSPEED;
				mPosition.mX += DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
				mPosition.mZ += DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
			}
		}
	}
}