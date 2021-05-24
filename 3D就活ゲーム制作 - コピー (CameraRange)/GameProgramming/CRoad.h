#ifndef CROAD_H
#define CROAD_H

#include "CCharacter.h"
#include "CObjFloor.h"

//#include "CCollider.h"

/*
class CRoadCollider : public CCollider
{
	CVector mNextPosition;
public:
	CVector GetNextPosition();
	void SetNextPosition(const CVector& v);
	void SetSphere(CCharacter* parent, CVector position, CVector rotation, CVector scale, float radius);
};
*/

class CRoad : public CTriangle
{
	CVector mCenter;
	bool mEnabled;
public:
	CRoad();
	CVector GetCenter();
	void SetEnabled(bool enabled);
	bool GetEnabled();
	void SetCenter();
	void operator=(const CTriangle& t);
};

class CRoadManager : public CObjFloor
{
	int mFrameCount;
	int mDispCount;
	CRoad* mpRoad;
	std::vector<CRoad*> mRoad;
	int mColSize;
//	CRoadCollider *mpCollider;
public:
//	CRoadManager();
	CRoadManager(CModel*, const CVector& pos, const CVector& rot, const CVector& scale);
	~CRoadManager();
	void Init(CModel*, const CVector& pos, const CVector& rot, const CVector& scale);
	void Update();
	void Render();
};

#endif

