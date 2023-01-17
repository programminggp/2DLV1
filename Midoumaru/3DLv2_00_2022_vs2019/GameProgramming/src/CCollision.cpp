#include"CCollision.h"
#include"CTransform.h"
#include"CVector.h"
#include"CCharacter.h"


bool CCollision::CollisionAll(CCollider* m, CCollider* o, CVector* adjust) {
	switch (m->Type()) {
	case CCollider::ESPHERE: //自身が球コライダ
		if (o->Type() == CCollider::ETRIANGLE) {
			return CCollider::CollisionTriangleSphere(o, m, adjust);
		}
		if (o->Type() == CCollider::ESPHERE) {
			return CCollider::Collision(o, m);
			//if (o->Tag() == CCollider::EMUTANTARM) {
			//	return CCollider::Collision(o, m);
			//}
			//if (o->Tag() == CCollider::ESWORD) {
			//	return CCollider::Collision(o, m);
			//}
			//if (o->Tag() == CCollider::EPLAYERAMAGIC) {
			//	return CCollider::Collision(o, m);
			//}
			//if (o->Tag() == CCollider::EPLAYERSMAGIC) {
			//	return CCollider::Collision(o, m);
			//}
		}
		break;
	case CCollider::ECAPSULE: //自身がカプセルコライダ
		if (o->Type() == CCollider::ETRIANGLE) {
			return CCollider::CollisionTriangleLine(o, m, adjust);
		}
		if (o->Type() == CCollider::ECAPSULE) {
			return CCollider::CollisionCapsule(m, o, adjust);
		}
		break;
	case CCollider::ETRIANGLE:
		if (o->Type() == CCollider::ELINE) {
			return CCollider::CollisionTriangleLine(m, o, adjust);
		}
		break;
	case CCollider::ELINE:
		if (o->Type() == CCollider::ETRIANGLE) {
			return CCollider::CollisionTriangleLine(o, m, adjust);
		}
		break;
	}
	switch (m->Tag()){
	case CCollider::ECORE:
		if (o->Tag() == CCollider::ESWORD) {
			return CCollider::Collision(o, m);
		}
		if (o->Tag() == CCollider::EMUTANTARM) {
			return CCollider::Collision(o, m);
		}
		if (o->Tag() == CCollider::EPLAYERAMAGIC) {
			return CCollider::Collision(o, m);
		}
		if (o->Tag() == CCollider::EPLAYERSMAGIC) {
			return CCollider::Collision(o, m);
		}
		break;
	}
	return false;
}


