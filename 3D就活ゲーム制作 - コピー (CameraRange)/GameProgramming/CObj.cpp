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
			//if (mObjNumber == 111){
			//	//加速床の当たり判定だけ上に移動させる
			//	model->mTriangles[i].mV[0] = model->mTriangles[i].mV[0] + CVector(0.0f, 5.0f, 0.0f);
			//	model->mTriangles[i].mV[1] = model->mTriangles[i].mV[1] + CVector(0.0f, 5.0f, 0.0f);
			//	model->mTriangles[i].mV[2] = model->mTriangles[i].mV[2] + CVector(0.0f, 5.0f, 0.0f);
			//}
			mpCollider[i].ChangePriority();
		}
	}

	

	//mVelocity = 0.0f;

	//mEnabled = false;
}
//デストラクタ
CObj::~CObj(){
	//コライダがあれば削除
	if (mpCollider){
		//delete[] 配列を削除
		delete[] mpCollider;
	}
}

//void CObj::Collision(CCollider *m, CCollider *y){
//	//if (mObjNumber == 2001){
//	//	//自身のコライダタイプの判定
//	//	switch (m->mType){
//	//	case CCollider::ETRIANGLE:
//	//		//相手のコライダが三角コライダの時
//	//		if (y->mType == CCollider::ETRIANGLE){
//	//			//////自分のコライダが何かの時
//	//			////if (m->mTag == CCollider::EBODY){					
//	//			////}
//	//			////芝生通過中の処理
//	//			//if (y->mpParent->mTag == CCharacter::EGRASS){
//	//			//	//CVector aiueo;//仮のベクトル
//	//			//	//if (CCollider::CollisionTriangleLine(y, m, &aiueo)){
//	//			//	//	mVelocity = 0;
//	//			//	//}
//	//			//}
//	//			//else{
//	//			//	mVelocity = 0;
//	//			//}
//	//			mVelocity = 0;
//	//		}
//	//	}
//	//}
//	//mVelocity = 0;//実行されてない
//	//	//自身のコライダタイプの判定
//	//	switch (mc->mType){
//	//	case CCollider::ESPHERE://球コライダ
//	//		//相手のコライダが三角コライダの時
//	//		if (yc->mType == CCollider::ETRIANGLE){
//	//			////水泳可能な時は水場(水の上)を通過できる
//	//			//if (yc->mTag == EWATER && mCanSwim){
//	//			//}
//	//			//else{
//	//			//}
//	//			////チェックポイント関連の処理
//	//			//if (CCollider::Collision(mc, yc)){
//	//			//	if (yc->mpParent->mTag == CCharacter::ECHECKPOINT){//中間地点1
//	//			//		if (mChecks == 0){
//	//			//			//各中間地点を通過しないと1周したとみなされない
//	//			//			mChecks = 1;
//	//			//		}
//	//			//	}
//	//			//	if (yc->mpParent->mTag == CCharacter::ECHECKPOINT2){//中間地点2
//	//			//		if (mChecks == 1){
//	//			//			//各中間地点を通過しないと1周したとみなされない
//	//			//			mChecks = 2;
//	//			//		}
//	//			//	}
//	//			//	if (yc->mpParent->mTag == CCharacter::ECHECKPOINT3){//中間地点3
//	//			//		if (mChecks == 2){
//	//			//			//各中間地点を通過しないと1周したとみなされない
//	//			//			mChecks = 3;
//	//			//		}
//	//			//	}
//	//			//}
//	//			//自分のコライダが本体の時
//	//			if (mc->mTag == CCollider::EBODY){
//	//				//芝生通過中の処理
//	//				if (yc->mpParent->mTag == CCharacter::EGRASS){
//	//					CVector aiueo;//仮のベクトル
//	//					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
//	//						//ブースト効果の方が優先される
//	//						if (isBoost == false){
//	//							//printf("speed down…\n");
//	//							//一定速度までスピード低下
//	//							if (mCarSpeed > 3.0f){
//	//								if (mCarSpeed > 3.3f){
//	//									mCarSpeed -= 0.3f;
//	//								}
//	//								else{
//	//									mCarSpeed = 3.0f;
//	//								}
//	//							}
//	//						}
//	//						/*if (mTurnSpeed <= 0.0f&&mTurnSpeed>-0.5f){
//	//						mTurnSpeed = -0.5f;
//	//						}
//	//						if (mTurnSpeed > 0.0f){
//	//						mTurnSpeed -= 0.11f;
//	//						}
//	//						mTurnSpeed -= 0.04f;*/
//	//					}
//	//				}
//	//				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT){//中間地点1
//	//					if (mChecks == 0){
//	//						//各中間地点を通過しないと1周したとみなされない
//	//						CVector aiu;//数合わせのためだけのベクトル
//	//						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
//	//							mChecks = 1;
//	//						}
//	//					}
//	//				}
//	//				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT2){//中間地点2
//	//					if (mChecks == 1){
//	//						//各中間地点を通過しないと1周したとみなされない
//	//						CVector aiu;//数合わせのためだけのベクトル
//	//						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
//	//							mChecks = 2;
//	//							//mChecks = 0;
//	//						}
//	//					}
//	//				}
//	//				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT3){//中間地点3
//	//					if (mChecks == 2){
//	//						//各中間地点を通過しないと1周したとみなされない
//	//						CVector aiu;//数合わせのためだけのベクトル
//	//						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
//	//							mChecks = 3;
//	//						}
//	//					}
//	//				}
//	//				////加速床に乗った時の処理
//	//				//if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
//	//				//	CVector aiueo;//とりまベクトル
//	//				//	if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
//	//				//		//mCarSpeed += 10.0f;
//	//				//		isBoost = true;
//	//				//		mBoostTime = 45;
//	//				//		printf("SPEED UP!\n");
//	//				//	}
//	//				//}
//	//				if (yc->mpParent->mTag == CCharacter::EWATER){
//	//					//通過可能、ステージ1の水
//	//				}
//	//				else if (yc->mpParent->mTag == CCharacter::ECLEARWATER){
//	//					//通過可能、ステージ2の水
//	//				}
//	//				else if (yc->mpParent->mTag == CCharacter::ECHECKPOINT
//	//					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
//	//					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
//	//					|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
//	//					//処理は行われるが、これらのパネルは通過可能
//	//				}
//	//				else{
//	//					CVector adjust;//調整用ベクトル
//	//					//		//三角形と球の衝突判定
//	//					//		CCollider::CollisionTriangleSphere(yc, mc, &adjust);
//	//					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
//	//						//位置の更新
//	//						mPosition = mPosition - adjust * -1;
//	//						//行列の更新
//	//						CCharacter::Update();
//	//						if (yc->mpParent->mTag == CCharacter::EWALL){
//	//							//衝突したのが壁だった場合は壁には引っかからず落下
//	//							//壁にぶつかると衝突音がし、車が減速する
//	//							//速い時に衝突で減速、遅い時の衝突は特に変化なし
//	//							if (mCarSpeed > 4.5f){
//	//								mCarSpeed = 2.0f;
//	//								//mCarSpeed /= 2.0f;
//	//								//	SoundCollision.Play();
//	//								//激突時、エフェクト発生
//	//								new CEffect(mPosition + CVector(0.0f, 35.0f, 0.0f), 50.0f, 50.0f, TextureExp, 4, 4, 1, 0);
//	//								//new CEffect(mPosition + CVector(0.0f, 390.0f/2, 0.0f), 390.0f, 390.0f, TextureExp, 4, 4, 111);
//	//								printf("ｺﾞﾝｯ");
//	//							}
//	//							else if (mCarSpeed > 3.0f){
//	//								mCarSpeed = 2.0f;
//	//								//	SoundCollisionSmall.Play();
//	//								//軽くぶつけた時もエフェクト発生
//	//								new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 17.0f, 17.0f, TextureHit, 3, 8, 1, 1);
//	//								printf("ｺﾞｽｯ");
//	//							}
//	//							else{
//	//								//壁にこすりながらの移動時、速度が遅くなる
//	//								if (mCarSpeed > 2.0f){
//	//									mCarSpeed = 2.0f;
//	//									/*new CEffect(mPosition + CVector(0.0f, 20.0f, 0.0f), 68.0f + 12.0f, 17.0f + 3.0f, TextureHit, 1, 1, 1, 1);
//	//									new CEffect(mPosition + CVector(0.0f, 60.0f, 0.0f), 68.0f + 12.0f, 17.0f + 3.0f, TextureHit, 1, 1, 1, 0);*/
//	//								}
//	//							}
//	//							//mCarSpeed = -mCarSpeed * 1.0;
//	//							//mVelocityJump = 2.0f;
//	//						}
//	//						else{
//	//							mVelocityJump = 0;
//	//							mCanJump = true;
//	//							/*if (mRotation.mX < yc->mpParent->mRotation.mX){
//	//							mRotation.mX++;
//	//							}
//	//							else if (mRotation.mX > yc->mpParent->mRotation.mX){
//	//							mRotation.mX--;
//	//							}*/
//	//							int rotateofycmx = yc->mpParent->mRotation.mX;
//	//							rotateofycmx %= 360; //-360度から360度までの数値に変換
//	//							//-235=125 300=-60 -180度未満か、180度以上の角度は
//	//							if (rotateofycmx < -180){
//	//								rotateofycmx += 360;
//	//							}
//	//							else if (rotateofycmx >= 180){
//	//								rotateofycmx -= 360;
//	//							}
//	//							mRotation.mX = rotateofycmx;
//	//							//if (mRotation.mX < yc->mpParent->mRotation.mX){
//	//							//	mRotation.mX = yc->mpParent->mRotation.mX;
//	//							//}
//	//							//else if (mRotation.mX > yc->mpParent->mRotation.mX){
//	//							//	mRotation.mX = yc->mpParent->mRotation.mX;
//	//							//}
//	//							//mRotation = yc->mpParent->mRotation;
//	//						}
//	//					}
//	//				}
//	//			}
//	//			//自分のコライダが判定の時
//	//			if (mc->mTag == CCollider::ESEARCH){
//	//				//加速床に乗った時の処理
//	//				if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
//	//					CVector aiueo;//とりまベクトル
//	//					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
//	//						//mCarSpeed += 10.0f;
//	//						if (isBoost == false){
//	//							printf("SPEED UP!\n");
//	//							//SoundBoost.Play();
//	//						}
//	//						isBoost = true;
//	//						mBoostTime = 45;
//	//					}
//	//				}
//	//			}
//	//			/*if(yc->mpParent->mTag == CCharacter::ESPRING){
//	//			mJumpV0 = 2.3f;
//	//			}*/
//	//			/*if (CItem::mpItem->mItemNumber == 2){
//	//			mJumpV0 = 2.3f;
//	//			}*/
//	//		}
//	//		if (yc->mType == CCollider::ESPHERE){
//	//			if (CCollider::Collision(mc, yc)){
//	//				//
//	//				if (mc->mTag == CCollider::EBODY){
//	//					if (yc->mpParent->mTag == CCharacter::EPLAYER){
//	//						CVector adjust;//調整用ベクトル
//	//						////		//球同士の衝突判定
//	//						if (CCollider::Collision(mc, yc, &adjust)){
//	//							//位置の更新
//	//							mPosition = mPosition - adjust * -1;
//	//							//行列の更新
//	//							CCharacter::Update();
//	//							//printf("X:%f Y:%f Z:%f",mPosition.mX,mPosition.mY,mPosition.mZ);
//	//							//printf("敵の衝突処理");
//	//						}
//	//					}
//	//					if (yc->mpParent->mTag == CCharacter::EENEMY
//	//						&& yc->mTag == CCollider::EBODY){
//	//						if (mc == yc){
//	//							return;
//	//						}
//	//						CVector adjust;//調整用ベクトル
//	//						////		//球同士の衝突判定
//	//						if (CCollider::Collision(mc, yc, &adjust)){
//	//							//位置の更新
//	//							mPosition = mPosition - adjust * -1;
//	//							//行列の更新
//	//							CCharacter::Update();
//	//							//printf("X:%f Y:%f Z:%f",mPosition.mX,mPosition.mY,mPosition.mZ);
//	//						}
//	//					}
//	//				}
//	//				if (mc->mTag == CCollider::ESEARCH){
//	//					//ポインタからポインタに向けて移動する
//	//					if (yc->mpParent->mTag == CCharacter::EPOINT){
//	//						CVector adjust;//調整用ベクトル
//	//						//		//球同士の衝突判定
//	//						if (CCollider::Collision(mc, yc, &adjust)){
//	//							//衝突したポインタと目指しているポインタが同じ時
//	//							if (yc->mpParent == mpPoint){
//	//								//mPointCnt++;//次のポイントにする
//	//								////最後だったら最初にする
//	//								//mPointCnt %= mPointSize;
//	//								//mpPoint = &mPoint[mPointCnt];
//	//								int r = (mc->mRadius + yc->mRadius) * 0.8f;
//	//								int gap = (rand() % (r * 2) - r);
//	//								//敵AIのLvにより分散値も変化
//	//								if (CSceneTitle::mDifficulty == 1){
//	//									r = (mc->mRadius + yc->mRadius) * 0.8f;
//	//									gap = (rand() % (r * 2) - r);
//	//								}
//	//								else if (CSceneTitle::mDifficulty == 2){
//	//									r = (mc->mRadius + yc->mRadius) * 0.4f;
//	//									gap = (rand() % (r * 2) - r);
//	//								}
//	//								else if (CSceneTitle::mDifficulty == 3){
//	//									r = (mc->mRadius + yc->mRadius) * 0.2f;
//	//									gap = (rand() % (r * 2) - r);
//	//								}
//	//								//次のポイントのポインタを設定
//	//								if (mpPoint == mPoint){
//	//									mVPoint = mPoint2->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint2;
//	//								}
//	//								else if (mpPoint == mPoint2){
//	//									mVPoint = mPoint3->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint3;
//	//								}
//	//								else if (mpPoint == mPoint3){
//	//									mVPoint = mPoint4->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint4;
//	//								}
//	//								else if (mpPoint == mPoint4){
//	//									mVPoint = mPoint5->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint5;
//	//								}
//	//								else if (mpPoint == mPoint5){
//	//									mVPoint = mPoint6->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint6;
//	//								}
//	//								else if (mpPoint == mPoint6){
//	//									//難易度Normal以上ではさらに細かくポイントが設定されている
//	//									if (CSceneTitle::mDifficulty == 2 || CSceneTitle::mDifficulty == 3){
//	//										mVPoint = mPoint7->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//										mpPoint = mPoint7;
//	//									}
//	//									else{
//	//										mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//										mpPoint = mPoint;
//	//									}
//	//								}
//	//								//敵AIがHARD以上での挙動
//	//								else if (mpPoint == mPoint7){
//	//									mVPoint = mPoint8->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint8;
//	//								}
//	//								else if (mpPoint == mPoint8){
//	//									mVPoint = mPoint9->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint9;
//	//								}
//	//								else if (mpPoint == mPoint9){
//	//									mVPoint = mPoint10->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint10;
//	//								}
//	//								else if (mpPoint == mPoint10){
//	//									mVPoint = mPoint11->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint11;
//	//								}
//	//								else if (mpPoint == mPoint11){
//	//									mVPoint = mPoint12->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint12;
//	//								}
//	//								else if (mpPoint == mPoint12){
//	//									mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint;
//	//								}
//	//								//printf("mpPoint…X:%.1f Y:%.1f Z:%.1f\n", mpPoint->mPosition.mX, mpPoint->mPosition.mY, mpPoint->mPosition.mZ);
//	//							}
//	//						}
//	//					}
//	//					//switch (yc->mpParent->mTag){
//	//					//case EPOINT://ポイントの時
//	//					//	//衝突したポインタと目指しているポインタが同じ時
//	//					//	if (yc->mpParent == mpPoint){
//	//					//		mPointCnt++;//次のポイントにする
//	//					//		//最後だったら最初にする
//	//					//		mPointCnt %= mPointSize;
//	//					//		//次のポイントのポインタを設定
//	//					//		mpPoint = &mPoint[mPointCnt];
//	//					//		printf("a");
//	//					//	}
//	//					//	break;
//	//					//default:
//	//					//	;
//	//					//}
//	//				}
//	//			}
//	//		}
//	//		break;
//	//	}
//	//}
//
//	/*if (mObjNumber != 9){
//		if (CCollider::Collision(m, y)){
//			if (y->mpParent->mTag == CCharacter::EPLAYER){
//				mEnabled = false;
//			}
//		}
//	}*/
//	/*if (y->mpParent->mTag == CCharacter::EBULLET){
//		if (CCollider::Collision(m, y)){
//			if (y->mpParent->mTag == CCharacter::EBULLET){
//				mEnabled = false;
//				
//			}
//		}
//	}*/
//	/*if (CCollider::Collision(m, y)){
//		if (y->mpParent->mTag == CCharacter::EBULLET){
//			mEnabled = false;
//
//		}
//	}*/
//	//if (mObjNumber == 13){//仮
//	//	if (CCollider::Collision(m, y)){
//	//		if (y->mpParent->mTag == CCharacter::EPLAYER){
//	//			mEnabled = false;
//	//		}
//	//	}
//	//}	
//}

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
		//当たり判定は必要ない
	//	mPosition.mY = CPlayer::mpPlayer->mPosition.mY;
	}

	CCharacter::Update();

	//うまく消せない
	/*if (mObjNumber == 13){
		if (mDeleteFlag){
			mEnabled = false;
		}
	}*/

	if (mObjNumber == 10){
		if (CItem::mTargetAmount <= 0){
			SetEnabled(false);
		}
	}
	if (mObjNumber == 22){
		if (CPlayer::mpPlayer->mIsGetKey){
			//ドアが開く
			//mEnabled = false;
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


	//if (mObjNumber == 2001){	
	//	mPosition = CVector(0.0f, mVelocity * 2.0f, 0.0f) * //mMatrixScale * 
	//		CMatrix().RotateZ(0) *
	//		CMatrix().RotateX(0) *
	//		CMatrix().RotateY(0)
	//		*mMatrixTranslate;//できてる？
	//	CCharacter::Update();
	//	//コースアウト時
	//	if (mPosition.mY < -150.0f){
	//		//落下の勢いを0にする
	//		mVelocity = 0.0f;
	//		mPosition.mY = 31.0f;
	//	}
	//	CCharacter::Update();
	//	//重力の影響を受ける
	//	mVelocity -= G;
	//}
}

//void CObjection::TaskCollision()
//{
//	/*mColBody.ChangePriority();
//	mColTire.ChangePriority();
//	CollisionManager.Collision(&mColBody);
//	CollisionManager.Collision(&mColTire);*/
//	//mpCollider.ChangePriority();
//	//CollisionManager.Collision(&mpCollider);
//}