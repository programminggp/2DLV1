#include"CXMutant.h"
#include"CXCharacter.h"
#include"CMatrix.h"
#include"CVector.h"
#include"CTransform.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"
#include"CColliderCapsule.h"
#include"CXPlayer.h"
#include"CCollision.h"

//int CXMutant::MutantHp = 5;

CXMutant::CXMutant()
	: mColCapBody(this, nullptr, CVector(0.0f, -110.0f, 40.0f), CVector(0.0f, 65.0f, 0.0f), 0.8f)
	, mColSphereArm(this, nullptr, CVector(0.0f, 40.0f, 0.0f), 0.5f)
	, mCore(this, nullptr, CVector(0.0f, 0.0f,10.0f), 0.9f)
	, MutantHp(5)
{
	mTag = EMUTANT;
}

void CXMutant::Init(CModelX* model)
{
	CXCharacter::Init(model);
	mColCapBody.Matrix(&mpCombinedMatrix[14]);//胴体
	mColSphereArm.Matrix(&mpCombinedMatrix[20]);//腕
	mCore.Matrix(&mpCombinedMatrix[14]);//コア
	mColSphereArm.Tag(CCollider::EMUTANTARM);
	mCore.Tag(CCollider::ECORE);
}

void CXMutant::Update()
{
	//左向き(X軸)のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//上向き(Y軸)のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前向き(Z軸)のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//プレイヤーのポインタが0以外の時
	CXPlayer* player = CXPlayer::Get();
	//目標地点までのベクトルを求める
	CVector vp = mPoint - mPosition;
	float dx = vp.Dot(vx);//左ベクトルの内積を求める
	float dy = vp.Dot(vy);//上ベクトル内積を求める
	float margin = 0.1f;
	//左方向へ回転
	if (dx > margin){
		//CXMutant::ChangeAnimation(2, true, 45);
		mRotation = mRotation + CVector(0.0f, 2.0f, 0.0f);//左へ回転
	}
	else if (dx < -margin){
		//CXMutant::ChangeAnimation(2, true, 45);
		mRotation = mRotation + CVector(0.0f, -2.0f, 0.0f);//右に回転
	}
	////上下に回転
	//if (dy > margin)
	//{
	//	mRotation = mRotation + CVector(-2.0f, 0.0f, 0.0f);//上へ回転
	//}
	//else if (dy < -margin)
	//{
	//	mRotation = mRotation + CVector(2.0f, 0.0f, 0.0f);//下に回転
	//}
	//移動する
	mPosition = mPosition + CVector(0.0f, -0.0f, 0.0f) * mMatrixRotate;
	CTransform::Update();//行列更新
	//およそ3秒ごとに目標地点を更新
	int r = rand() % 50;//rand()は整数の乱数を返す
						 //%180は180で割った余りを求める
	if (r == 0)
		//if (mPoint.X() == 0.0f && mPoint.Y() == 0.0f && mPoint.Z() == 0.0f)
	{
		if (player != nullptr){
			mPoint = player->Position();
		}
		else{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

	//CXMutant::ChangeAnimation(3, true, 160);

	if (MutantHp <= 0) {
		CXMutant::ChangeAnimation(4, false, 70);
	}

	CXCharacter::Update();
	CTransform::Update();
}

void CXMutant::Collision(CCollider* m, CCollider* o){
	////自身のコライダタイプの判定
	//switch (m->Type()) {
	//case CCollider::ECAPSULE:
	//	//相手のコライダが三角コライダの時
	//	if (o->Type() == CCollider::ETRIANGLE) {
	//		CVector adjust;//調整用ベクトル
	//		//三角形と線分の衝突判定
	//		if (CCollider::CollisionTriangleLine(o, m, &adjust)){
	//			mPosition = mPosition + adjust;//位置の更新(mPosition + adjust)
	//			CTransform::Update();//行列の更新
	//		}
	//	}
	//	break;
	//case CCollider::ESPHERE:
	//	//コライダのmとyが衝突しているか判定
	//	if (m->Tag() == CCollider::ECORE){
	//		if (o->Tag() == CCollider::ESWORD) {
	//			if (CCollider::Collision(m, o)) {
	//				MutantHp--;
	//			}
	//		}
	//		if (o->Tag()== CCollider::EPLAYERSMAGIC) {
	//			if (CCollider::Collision(m, o)) {
	//				MutantHp -= 2;
	//			}
	//		}
	//		if (o->Tag() == CCollider::EPLAYERAMAGIC) {
	//			if (CCollider::Collision(m, o)) {
	//				MutantHp -= 2;
	//			}
	//		}
	//	}
	//	break;
	//}
		//case CCollider::ESPHERE://球コライダの時
		////コライダのmとyが衝突しているか判定
		//	if (o->Type() == CCollider::ESPHERE && CCollider::Collision(m, o)) {
		//		//衝突している時は無効にする
		//		//削除mEnabled = false;
		//		/*PlayerHp--;
		//		if (PlayerHp <= 0)
		//		{
		//			mEnabled = false;
		//		}*/
		//	}
		//	break;

	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mPosition = mPosition + adjust;
		}
		if (o->Type() == CCollider::ECAPSULE) {
			mPosition = mPosition + adjust;
		}
		if (CXPlayer::BattleSwitch == true) {
			if (o->Tag() == CCollider::ESWORD) {
				MutantHp--;
			}
		}
		if (o->Tag() == CCollider::EPLAYERSMAGIC) {
			MutantHp -= 2;
		}
		if (o->Tag() == CCollider::EPLAYERAMAGIC) {
			MutantHp -= 2;
		}
	}
}

void CXMutant::TaskCollision()
{
	mColCapBody.ChangePriority();
	mColSphereArm.ChangePriority();
	mCore.ChangePriority();
	CCollisionManager::Get()->Collision(&mColCapBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereArm, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCore, COLLISIONRANGE);
}




