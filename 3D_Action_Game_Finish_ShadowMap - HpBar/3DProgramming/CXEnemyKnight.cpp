#include "CXEnemyKnight.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Define.h"

/*
初期化処理
*/
void CXEnemyKnight::Init(CModelX *model) {
	//親の初期化処理
	CXCharacter::Init(model);
	//コライダの生成
	//体
	mColliders.push_back(new CSphereCollider(CCollider::EBODY, this, &mpCombinedMatrix[1], CVector3(0.5f, -1.0f, 0.0f), 1.0f));
	//顔
	mColliders.push_back(new CSphereCollider(CCollider::EHEAD, this, &mpCombinedMatrix[1], CVector3(0.0f, 1.f, 0.0f), 1.5f));
	//剣
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[26], CVector3(0.7f, 3.5f, -0.2f), 0.5f));
	//剣
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[26], CVector3(0.5f, 2.5f, -0.2f), 0.5f));
	//剣
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[26], CVector3(0.3f, 1.5f, -0.2f), 0.5f));
	//カプセルコライダ
	mColliders.push_back(new CCapsuleCollider(this, &mpCombinedMatrix[0], CVector3(0.0f, 0.0f, 0.0f), CVector3(0.0f, 4.5f, 0.0f), 1.7f));

	//*10
	//索敵
	mColliders.push_back(new CSphereCollider(CCollider::ENONE, this, &mpCombinedMatrix[1], CVector3(0.0f, 0.0f, 1.0f), 20.0f));

	//待機状態にする
	ChangeAnimation(2, true, 200);
	mState = EIDLE;
	mScale = CVector3(ENEMYKNIGHT_SCALE, ENEMYKNIGHT_SCALE, ENEMYKNIGHT_SCALE);
}

void CXEnemyKnight::Render() {
	CXCharacter::Render();
//	mHpBar.SetPosition(mPosition + CVector3(0.0f, 4.5f, -1.0f));
	mHpBar.SetPosition(mPosition + CVector3(0.0f, 4.5f, 0.0f));
	mHpBar.Render();
}

void CXEnemyKnight::Update() {
	mAdjust = CVector3();
	switch (mState) {
	case EATTACK:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(8, false, ENEMY_ATTACK_SPEED);
			mHitFlg = true;
			mState = EATTACKR;
		}
		break;
	case EATTACKR:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(2, true, 200);
			mHitFlg = true;
			mState = EIDLE;
		}
		break;
	case EWALK:
	case EIDLE:
		//プレイヤーを見つけている時
		if (mpPlayer) {
			if (mpPlayer->mState == EDOWN) {
				ChangeAnimation(2, true, 200);
				mState = EIDLE;
				break;
			}
			if (mState == EIDLE) {
				ChangeAnimation(1, true, 60);
				mState = EWALK;
			}
			//自分からプレイヤーへのベクトルを求める
			CVector3 ep = mpPlayer->mPosition - mPosition;
			//回転行列を宣言します
			CMatrix44 rot;
			//自分のY軸の回転行列を求める
			rot.rotationY(mRotation.y);
			//X軸だけ長さ1のベクトルを作成する
			CVector3 vx(1.0f, 0.0f, 0.0f);
			//作成したベクトルを自分のY軸回転だけ回転させる
			vx = vx * rot;
			//回転させたベクトルとプレイヤーへのベクトルの内積を求める
			float dot = ep.dot(vx);
			//内積の値によってY軸の回転値を増減する
			if (dot > 0.0f) {
				mRotation.y -= 2;
			}
			else if (dot < 0.0f) {
				mRotation.y += 2;
			}
			//プレイヤーのポインタを0にします。
			mpPlayer = 0;
			//回る値
			radian = 0.0f;
			//近くに来たら攻撃
			if (ep.length() < ENEMY_ATTACK_RANGE) {
				//*11
				//攻撃アニメーション
				ChangeAnimation(7, false, ENEMY_ATTACK_SPEED);
				//ステータスを攻撃中
				mState = EATTACK;
			}
			else {
				//プレイヤーへ移動
				mPosition = mPosition + CVector3(0.0f, 0.0f, -ENEMY_VELOCITY) * rot;
			}
		}
		else {
			ChangeAnimation(2, true, 200);
			mState = EIDLE;
			//回る
			//ラジアンに加算
			radian += 0.02f;
			//2πを超えたら
			if (radian > M_PI*2) {
				//2π減算
				radian -= M_PI*2;
			}
			//sin関数を活用
			mRotation.y += sinf(radian) * 2;
		}
		break;
	}
	Gravity(); //重力処理
	CXCharacter::Update();
}
//衝突処理
bool CXEnemyKnight::Collision(CCollider *m, CCollider *y) {
	//自分のコライダの種類を判定
	switch (m->mTag) {
	case CCollider::ECOLSPHERE://球コライダ
		//相手のコライダの種類判定
		switch (y->mTag) {
		case CCollider::ECOLSPHERE://球コライダ
			//球コライダと球コライダの衝突判定
			if (CCollision::Sphere(m, &((CSphereCollider*)y)->GetWorld())) {
				//プレイヤーのコライダと当たっていれば
				//プレイヤーのポインタ取得
				if (y->mpParent->mTag == EPLAYER) {
					mpPlayer = y->mpParent;
				}
				//プレイヤーの攻撃が、自分に当たったか？
				if (y->mpParent->mTag == EPLAYER	//プレイヤー
					&& y->mColParts == CCollider::ESWORD	//剣
					&& y->mpParent->mAnimationIndex == 3
					/*&& y->mpParent->mHitFlg*/) {	//攻撃中
					if (m->mColParts == CCollider::EBODY	//体
						|| m->mColParts == CCollider::EHEAD) {//頭
						mHpBar.mValue -= PLAYER_ATTACK_POINT;
						if (mHpBar.mValue <= 0.0f) {
							ChangeAnimation(11, false, 60);	//ダウン
							mState = EDOWN;
						}
					}
				}
				//自分の攻撃が、プレイヤーに当たったか？
				if (y->mpParent->mTag == EPLAYER	//プレイヤー
					&& m->mColParts == CCollider::ESWORD	//剣
					&& m->mpParent->mState == EATTACK	//攻撃中
					&& mHitFlg) {
					if (y->mpParent->mState != EAVOIDANCEL &&
						y->mpParent->mState != EAVOIDANCER) {
						if (y->mColParts == CCollider::EBODY	//体
							|| y->mColParts == CCollider::EHEAD) {//頭
							//ヒットエフェクト生成
							new CEffectHit3(m->mPosition, CVector3(2.5f, 2.5f, 0.0f), 5, 2);
							mHitFlg = false;
						}
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
