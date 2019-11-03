#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"

class CCollisionManager : public CTaskManager {
public:
	void Collision();
};

extern CCollisionManager CollisionManager;

#endif
