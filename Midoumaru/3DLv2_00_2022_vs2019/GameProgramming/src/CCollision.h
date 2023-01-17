#ifndef CCOLLISION_H
#define CCOLLISION_H
#include"CCollider.h"
#include"CXCharacter.h"
#include"CTransform.h"
#include"CVector.h"

class CCollision : public CXCharacter {
public:
    static bool CollisionAll(CCollider* m, CCollider* o, CVector* adjust);
};

#endif
