#ifndef CROAD_H
#define CROAD_H

#include "CCharacter.h"

class CRoad : public CTriangle
{
	CVector mCenter;
	bool mEnabled;
public:
	CRoad();
	void SetCenter();
	CVector GetCenter();
	void operator=(const CTriangle& t);
};

class CRoadManager : public CCharacter
{
	int mFrameCount;
	int mDispCount;
	CRoad* mpRoad;
public:
	CRoadManager();
	~CRoadManager();
	void Init(CModel*);
	void Update();
	void Render();
};

#endif

