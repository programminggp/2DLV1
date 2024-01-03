//プレイヤークラスのインクルード
#include <math.h>
#include "CPlayer.h"
#include "CApplication.h"
#include "CColliderManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f) //回転速度
#define VELOCITY CVector(0.0f,0.0f,0.5f) //移動速度
#define VELOCITY2 CVector(0.5f,0.0f,0.0f) //移動速度（横)
#define ROTATION_XV CVector(1.0f,0.0f,0.0f) //回転速度
#define MOS_POS_X 400 //マウス座標のX補正
#define MOS_POS_Y 300 //マウス座標のY補正

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sBotan = 0;

int CPlayer::Botan()
{
	return sBotan;
}

int CPlayer::sGate = 0;

int CPlayer::Gate()
{
	return sGate = 0;
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}


//CPlayer(位置、回転、スケール)
CPlayer::CPlayer(const CVector& pos, const CVector& rot, const CVector& scale)
{
	CTransform::Update(pos, rot, scale); //行列の更新
}

void CPlayer::Collision()
{
	//コライダの優先度変更
	mLine1.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//衝突処理を実行
	//CCollisionManager::Instance()->Collision(&mLine1, COLLISIONRANGE);
	//CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	//CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
	CColliderManager::Instance()->Collision(&mLine1);
	CColliderManager::Instance()->Collision(&mLine2);
	CColliderManager::Instance()->Collision(&mLine3);
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
		}
		break;
	
	case CCollider::EBOTAN://ボタンコライダ
	    //相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整ベクトル
			//ボタンと線分の衝突判定
			if (CCollider::CollisionTriangleBotan(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
				sBotan = 1;
			}
		}
		break;
	}
	
}

//更新処理
void CPlayer::Update() {
	if (sBotan > 0)
	{
		sBotan--;
	}
	//Wキーで前進
	if (mInput.Key('W')) {
		//Z軸方向の値を回転させ移動させる
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//Sキーで後退
	if (mInput.Key('S')) {
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//Aキーで左
	if (mInput.Key('A')) {
		//Z軸方向の値を回転させ移動させる
		mPosition = mPosition + VELOCITY2 * mMatrixRotate;
	}
	//Dキーで右
	if (mInput.Key('D')) {
		mPosition = mPosition - VELOCITY2 * mMatrixRotate;
	}
	if (sBotan == 1) {
		if (mInput.Key('F')) {
			sGate++;
		}
	}
	////Sキー入力で下向き
	//if (mInput.Key('S')) {
	//	//X軸の回転値わ減算
	//	mRotation = mRotation - ROTATION_XV;
	//}
	////Wキー入力で上向き
	//if (mInput.Key('W')) {
	//	//X軸の回転値わ加算
	//	mRotation = mRotation + ROTATION_XV;
	//}
	////スペースキー入力で弾発射
	//if (mInput.Key(VK_SPACE)) {
	//	CBullet* bullet = new CBullet();
	//	bullet->Set(0.1f, 1.5f);
	//	bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
	//	bullet->Rotation(mRotation);
	//	bullet->Update();
	//	/*CApplication::TaskManager()->Add(bullet);*/
	//}
	//変換行列の更新
	CTransform::Update();
	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
}