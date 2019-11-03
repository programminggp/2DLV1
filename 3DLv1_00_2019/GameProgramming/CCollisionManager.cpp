#include "CCollisionManager.h"
#include "CCollider.h"

CCollisionManager CollisionManager;

void CCollisionManager::Collision() {
	CCollider *pos = (CCollider*)mpHead;
	while (pos != mpTail) {
		CCollider *next = (CCollider*)pos->mpNext;
		while (next) {
			pos->mpParent->Collision(pos, next);
			next->mpParent->Collision(next, pos);
			next = (CCollider*)next->mpNext;
		}
		pos = (CCollider*)pos->mpNext;
	}
}