#ifndef CROAD_H
#define CROAD_H

#include "CCharacter.h"
#include "CObjFloor.h"

class CRoadManager : public CObjFloor
{
public:
	CRoadManager(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward);
	~CRoadManager();
	void Init(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward);
};

#endif

