#include "CCollisionManager.h"
#include "CCollider.h"
#include "CCharacter.h"

void CCollisionManager::Update() {
	CCollider  *m = (CCollider*)mpHead;
	while (m != mpTail) {
		CCollider *y = (CCollider*)m->mpNext;
		while (y) {
			if (m->mpParent) {
				m->mpParent->Collision(m, y);
			}
			if (y->mpParent) {
				y->mpParent->Collision(y, m);
			}
			y = (CCollider*)y->mpNext;
		}
		m = (CCollider*)m->mpNext;
	}

}