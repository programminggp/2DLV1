#ifndef CROAD_H
#define CROAD_H

#include "CCharacter.h"

class CRoad : public CTriangle
{
	CVector mCenter;
	bool mEnabled;
	void SetCenter();
public:
	CRoad();
	CVector GetCenter();
	void SetEnabled(bool enabled);
	bool GetEnabled();
	void operator=(const CTriangle& t);
};

class CRoadManager : public CCharacter
{
	int mFrameCount;
	int mDispCount;
	CRoad* mpRoad;
	std::vector<CRoad*> mRoad;
public:
	CRoadManager();
	~CRoadManager();
	void Init(CModel*);
	void Update();
	void Render();
};

#endif

