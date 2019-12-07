#ifndef CMAP_H
#define CMAP_H

#include "CCharacter.h"
#include "CCollider.h"

class CMap : public CCharacter {
public:
	//Šm”F—p
	CCollider mCollider;
	//
	CCollider *mpTriangleColider;
	//
	CMap();
	~CMap();
	//
	void SetTriangleCollider();
};

#endif
