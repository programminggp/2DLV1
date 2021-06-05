#include <Windows.h>
#include "CXPlayer.h"
#include "CBillBoard.h"
#include "CParticle.h"
#include "CKey.h"
#include "Define.h"
#include "CLight.h"

//カメラの回転速度
#define CAMERA_ROTATION_ADD 2
//プレイヤーのポインタ
CXPlayer *CXPlayer::mpPlayer = 0;

/*
初期化処理
*/
void CXPlayer::Init(CModelX *model) {
	//プレイヤーのポインタ設定
	mpPlayer = this;
	//親の初期化処理
	CXCharacter::Init(model);
	//コライダの生成
	//体
	mColliders.push_back(new CSphereCollider(CCollider::EBODY, this, &mpCombinedMatrix[8+1], CVector3(), 0.5f));
	//顔
	mColliders.push_back(new CSphereCollider(CCollider::EHEAD, this, &mpCombinedMatrix[11 + 1], CVector3(0.0f, 5.f, -3.0f), 0.5f));
	//剣
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[21 + 1], CVector3(-10.0f, 10.0f, 50.0f), 0.3f));
	//*3
	//カプセルコライダ
	mColliders.push_back(new CCapsuleCollider(this, &mpCombinedMatrix[1], CVector3(0.0f, 10.0f, 0.0f), CVector3(0.0f, 160.0f, 0.0f), 0.7f));
}

void CXPlayer::Update() {
	CMatrix44 rot;
	CVector3 slide(0.25f, 0.0f, 0.0f);
	mAdjust = CVector3();
	//モーションにより振り分け
	switch (mState) {
	case EAVOIDANCER://回避右
		mRotation.y += 12;
		mCameraRotation.y -= 12;
		rot.rotationY(mRotation.y + mCameraRotation.y);
		slide = slide * rot;
		//スライド
		mPosition = mPosition - slide;
		if (mAnimationFrame >= mAnimationFrameSize) {
			//待機モーション（0番、繰り返し、60フレーム）
			ChangeAnimation(0, true, 60);
			mAnimationFrameSize = 60;
			mState = EIDLE;
		}
		break;
	case EAVOIDANCEL://回避左
		mRotation.y -= 12;
		mCameraRotation.y += 12;
		rot.rotationY(mRotation.y + mCameraRotation.y);
		slide = slide * rot;
		//スライド
		mPosition = mPosition + slide;
		if (mAnimationFrame >= mAnimationFrameSize) {
			//待機モーション（0番、繰り返し、60フレーム）
			ChangeAnimation(0, true, 60);
			mAnimationFrameSize = 60;
			mState = EIDLE;
		}
		break;
	case EIDLE://待機
	case EWALK://歩く
		//*7
		//Dキーを押すと右へ回転し
		if (CKey::Push('D')) {
			//右へ回転
			mRotation.y -= PLAYER_ROTATION_ADD;
			mRotation.y = (int)mRotation.y % 360;
		}
		//Aキーを押すと左へ回転する
		if (CKey::Push('A')) {
			//左へ回転
			mRotation.y += PLAYER_ROTATION_ADD;
			mRotation.y = (int)mRotation.y % 360;
		}
		//*13
		//ADキー素早く2度押しで回避
		if (CKey::Twice('D')) {
			ChangeAnimation(0, false, 60);
			mAnimationFrame = 0;
			mAnimationFrameSize = 30;
			mState = EAVOIDANCER;
			break;
		}
		if (CKey::Twice('A')) {
			ChangeAnimation(0, false, 60);
			mAnimationFrame = 0;
			mAnimationFrameSize = 30;
			mState = EAVOIDANCEL;
			break;
		}

		//Wキーを押すと、歩くアニメーションに変え
		//向いている方向へ0.1だけ移動する
		if (CKey::Push('W')) {
			//カメラの方向へ向ける
			CMatrix44 rot;
			CVector3 camera = mPosition - GetCameraPosition();
			rot.rotationY(90);
			camera = camera * rot;
			rot.rotationY(mRotation.y);
			float dot = camera.dot(CVector3(0, 0, 1.0f)*rot);
			if (dot > 0) {
				mRotation.y -= 4.0f;
				mCameraRotation.y += 4.0f;
			}
			else if (dot < 0) {
				mRotation.y += 4.0f;
				mCameraRotation.y -= 4.0f;
			}
			rot.rotationY(mRotation.y);

			//*5
			//位置を移動させる
			mPosition = mPosition + CVector3(0, 0, PLAYER_VELOCITY)*rot;
			//歩きモーション（1番、繰り返し、60フレーム）
			ChangeAnimation(1, true, 60);
			//ステータスを歩く
			mState = EWALK;
		}
		else if (CKey::Push('S')) {
			//カメラの方向へ向ける
			CMatrix44 rot;
			CVector3 camera = mPosition - GetCameraPosition();
			rot.rotationY(90);
			camera = camera * rot;
			rot.rotationY(mRotation.y);
			float dot = camera.dot(CVector3(0, 0, 1.0f)*rot);
			if (dot > 0) {
				mRotation.y -= 4.0f;
				mCameraRotation.y += 4.0f;
			}
			else if (dot < 0) {
				mRotation.y += 4.0f;
				mCameraRotation.y -= 4.0f;
			}
			rot.rotationY(mRotation.y);

			//*6
			//位置を移動させる
			mPosition = mPosition + CVector3(0, 0, -PLAYER_VELOCITY)*rot;
			//歩きモーション（1番、繰り返し、60フレーム）
			ChangeAnimation(1, true, 60);
			//ステータスを歩く
			mState = EWALK;
		}
		else {	//歩いてない時は待機
			//待機モーション（0番、繰り返し、60フレーム）
			ChangeAnimation(0, true, 60);
			mState = EIDLE;
		}

		//SPキーを押すと攻撃1
		if (CKey::Once(' ')) {
			//*8
			//攻撃1モーション（3番、繰り返さない、30フレーム）にする
			ChangeAnimation(3, false, PLAYER_ATTACK_SPEED);
			mState = EATTACK;
//			CSoundManager::mSwing.Play();
		}
		break;
	case EATTACK://攻撃1
		if (mAnimationFrame >= mAnimationFrameSize) {
			//攻撃1終わりモーション（4番、繰り返さない、30フレーム）にする
			ChangeAnimation(4, false, PLAYER_ATTACK_SPEED);
			mState = EATTACKR;
		}
		break;
	case EATTACKR://攻撃1終わり
		if (mAnimationFrame >= mAnimationFrameSize) {
			//待機モーション（0番、繰り返し、60フレーム）にする
			ChangeAnimation(0, true, 60);
			mState = EIDLE;
			mHitFlg = true;
		}
		break;
	}
	//*4
	//Jキーでカメラ回転
	if (CKey::Push('J')) {
		mCameraRotation.y += CAMERA_ROTATION_ADD;
	}
	//Lキーでカメラ回転
	if (CKey::Push('L')) {
		mCameraRotation.y -= CAMERA_ROTATION_ADD;
	}

	Gravity(); //重力処理
	CXCharacter::Update();
	//Lightの位置設定
//	CLight::getLight(0)->setPosition(mPosition + CVector3(LIGHT_POS), mPosition);
}

//衝突処理
bool CXPlayer::Collision(CCollider *m, CCollider *y) {
	//自分のコライダの種類を判定
	switch (m->mTag) {
	case CCollider::ECOLSPHERE://球コライダ
		//相手のコライダの種類判定
		switch (y->mTag) {
		case CCollider::ECOLSPHERE://球コライダ
			//球コライダと球コライダの衝突判定
			if (CCollision::Sphere(m, &((CSphereCollider*)y)->GetWorld())) {
				//敵の攻撃が、プレイヤーにヒット
				if (y->mpParent->mTag == EENEMY	//
					&& y->mColParts == CCollider::ESWORD	//剣
					&& y->mpParent->mState == EATTACK) {	//攻撃中
					if (m->mColParts == CCollider::EBODY	//体
						|| m->mColParts == CCollider::EHEAD) {//頭
						if (m->mpParent->mState != EAVOIDANCEL &&
							m->mpParent->mState != EAVOIDANCER) {
							mHpBar.mValue -= ENEMY_ATTACK_POINT;
							if (mHpBar.mValue <= 0.0f) {
								ChangeAnimation(11, false, 60);	//ダウン
								mState = EDOWN;
							}
						}
					}
				}
				//プレイヤーの攻撃が、敵にヒット
				if (y->mpParent->mTag == EENEMY	//
					&& m->mColParts == CCollider::ESWORD	//剣
					&& m->mpParent->mState == EATTACK) {	//攻撃中
//					&& mHitFlg) {
					if (y->mColParts == CCollider::EBODY	//体
						|| y->mColParts == CCollider::EHEAD) {//頭
						new CEffectHit2(m->mPosition, CVector3(2.5f, 2.5f, 0.0f), 6, 2);
						mHitFlg = false;
					}
				}
			}
			break;
		}
		break;
	case CCollider::ECOLCAPSULE://カプセルコライダ
		//相手のコライダの種類判定
		switch (y->mTag) {
		case CCollider::ECOLTRIANGLE://三角形コライダ
			CVector3 adjust;
			//カプセルコライダと三角形コライダの衝突判定
			if (CCollision::CapsuleTriangle(m, y, &adjust)) {
				UpdateAdjust(adjust);
				//地面か判断
				if (y->mColParts == CCollider::EGROUND) {
					//接地したら重力速度0
					mVelocityG = 0.0f;
				}
			}
			break;
		}
		break;
	}
	return false;
}

void CXPlayer::Render() {
	CXCharacter::Render();
	//HPゲージの設定と表示
	mHpBar.SetPosition(mPosition + CVector3(0.0f, 0.7f, 0.0f));
	mHpBar.Render();
}
