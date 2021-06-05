//25
#include "CXEnemy.h"
#define _USE_MATH_DEFINES
#include <math.h>

/*
初期化処理
*/
void CXEnemy::Init(CModelX *model) {
	//親の初期化処理
	CXCharacter::Init(model);
	mState = EIDLE;
	//コライダの生成
	//体
	mpColSphereBody = new CSphereCollider(CCollider::EBODY, this, &mpCombinedMatrix[8+1], CVector3(), 0.5f);
	//顔
	mpColSphereHead = new CSphereCollider(CCollider::EHEAD, this, &mpCombinedMatrix[11+1], CVector3(0.0f, 5.f, -3.0f), 0.5f);
	//剣
	mpColSphereSword = new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[21+1], CVector3(-10.0f, 10.0f, 50.0f), 0.3f);
	//30 カプセルコライダ
	new CCapsuleCollider(this, &mpCombinedMatrix[7+1], CVector3(0.0f, -80.0f, 0.0f), CVector3(0.0f, 80.0f, 0.0f), 0.7f);
	//31 索敵
	new CSphereCollider(CCollider::ENONE, this, &mpCombinedMatrix[5+1], CVector3(0.0f, 0.0f, 700.0f), 10.0f);
}

void CXEnemy::Update() {
	mAdjust = CVector3();
//31
	switch (mAnimationIndex) {
	case 7:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(8, false, 30);
			mState = EATTACK;
		}
		break;
	case 8:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(0, true, 60);
			mHitFlg = true;
			mState = EIDLE;
		}
		break;
	case 11:
		if (mAnimationFrame >= mAnimationFrameSize) {
			mEnabled = false;
		}
		break;
	default:
		//プレイヤーを見つけている時
		if (mpPlayer) {
			ChangeAnimation(1, true, 60);
			mState = EWALK;
			//自分からプレイヤーへのベクトルを求める
			CVector3 ep = mPosition - mpPlayer->mPosition;
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
				mRotation.y--;
			}
			else if (dot < 0.0f) {
				mRotation.y++;
			}
			//プレイヤーのポインタを0にします。
			mpPlayer = 0;
			//回る値
			radian = 0.0f;
			//近くに来たら攻撃
			if (ep.length() < 2.4f) {
				ChangeAnimation(7, false, 90);
				mState = EATTACK;
			}
			//34 プレイヤーへ移動
			mPosition = mPosition + CVector3(0.0f, 0.0f, 0.05f) * rot;
		}
		else {
			ChangeAnimation(0, true, 60);
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
#ifdef _DEBUG
	//25 コライダの描画
	//27 削除
	//mpColSphereBody->Render();
	//mpColSphereHead->Render();
	//mpColSphereSword->Render();
#endif
}
//27 衝突処理
bool CXEnemy::Collision(CCollider *m, CCollider *y) {
	//自分のコライダの種類を判定
	switch (m->mTag) {
	case CCollider::ECOLSPHERE://球コライダ
		//相手のコライダの種類判定
		switch (y->mTag) {
		case CCollider::ECOLSPHERE://球コライダ
			//球コライダと球コライダの衝突判定
			if (CCollision::Sphere(m, &((CSphereCollider*)y)->GetWorld())) {
//31
				//プレイヤーのコライダと当たっていれば
				//プレイヤーのポインタ取得
				if (y->mpParent->mTag == EPLAYER) {
					mpPlayer = y->mpParent;
				}
				if (y->mpParent->mTag == EPLAYER	//プレイヤー
					&& y->mColParts == CCollider::ESWORD	//剣
					&& y->mpParent->mState == EATTACK) {	//攻撃中
					if (m->mColParts == CCollider::EBODY	//体
						|| m->mColParts == CCollider::EHEAD) {//頭
						ChangeAnimation(11, false, 30);	//ダウン
						mState = EDOWN;
					}
				}
				if (y->mpParent->mTag == EPLAYER	//プレイヤー
					&& m->mColParts == CCollider::ESWORD	//剣
					&& m->mpParent->mState == EATTACK	//攻撃中
					&& mHitFlg) {
					if (y->mColParts == CCollider::EBODY	//体
						|| y->mColParts == CCollider::EHEAD) {//頭
						//ヒットエフェクト生成
						new CEffectHit3(m->mPosition, CVector3(2.5f, 2.5f, 0.0f), 5, 2);
						mHitFlg = false;
					}
				}
			}
			break;
		}
		break;
	//30
	case CCollider::ECOLCAPSULE://カプセルコライダ
		//相手のコライダの種類判定
		switch (y->mTag) {
		case CCollider::ECOLTRIANGLE://三角形コライダ
			CVector3 adjust;
			//カプセルコライダと三角形コライダの衝突判定
			if (CCollision::CapsuleTriangle(m, y, &adjust)) {
				UpdateAdjust(adjust);
//				mPosition = mPosition + adjust;
				//30 地面か判断
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
