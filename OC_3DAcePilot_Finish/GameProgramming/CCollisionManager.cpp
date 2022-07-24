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
		if (pos->mPriority < 0)
			break;
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
