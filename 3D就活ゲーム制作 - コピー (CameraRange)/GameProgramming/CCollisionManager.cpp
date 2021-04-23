#include "CCollisionManager.h"
//コライダクラスのインクルード
#include "CCollider.h"
//他で使用できるように外部変数で作成
CCollisionManager CollisionManager;

//衝突処理
void CCollisionManager::Collision() {
	//現在位置を先頭にする
	CCollider *pos = (CCollider*)mpHead->mpNext;
	//最後まできたら終了する
//?	while (pos != mpTail) {
	while (pos) {
			//現在位置の次を求める
		CCollider *next = (CCollider*)pos->mpNext;
		//次が0になったら終了
		while (next) {
			//親の衝突処理を呼び出す
			//自分の衝突処理
			pos->mpParent->Collision(pos, next);
			//相手の衝突処理
			next->mpParent->Collision(next, pos);
			//次を求める
			next = (CCollider*)next->mpNext;
		}
		//現在位置を次にする
		pos = (CCollider*)pos->mpNext;
	}
}

//Collision(コライダ）
//コライダとの衝突処理を実行する
void CCollisionManager::Collision(CCollider *collider)
{
	int sPri = collider->mPriority + 900; //開始位置（大）
	int ePri = collider->mPriority - 900; //終了位置（小）
	//現在位置を先頭にする
	CCollider *pos = (CCollider*)mpHead->mpNext;
	//開始位置まできたら終了する
	while (pos && pos->mPriority > sPri) {
		//現在位置を次にする
		pos = (CCollider*)pos->mpNext;
	}
	if (pos) {
		//終了位置まで繰り返し
		while (pos && pos->mPriority >= ePri) {
			//親の衝突処理を呼び出す
			collider->mpParent->Collision(collider, pos);
			//次を求める
			pos = (CCollider*)pos->mpNext;
		}
	}
	//優先度0とは衝突判定させる
	while (pos && pos->mPriority) {
		//現在位置を次にする
		pos = (CCollider*)pos->mpNext;
	}
	if (pos) {
		//終了位置まで繰り返し
		while (pos && pos->mPriority <= 0) {
			//親の衝突処理を呼び出す
			collider->mpParent->Collision(collider, pos);
			//次を求める
			pos = (CCollider*)pos->mpNext;
		}
	}
}


