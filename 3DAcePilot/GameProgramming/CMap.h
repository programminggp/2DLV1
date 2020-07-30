#ifndef CMAP_H
#define CMAP_H

#include "CCharacter.h"
#include "CCollider.h"

class CMap : public CCharacter {
public:
	//Šm”F—p
	CCollider mCollider[14];
	//
//	CCollider *mpTriangleColider;
	//
	CMap();
	/*
	~CMap();
	//
	void SetTriangleCollider();
	*/
};

#endif
