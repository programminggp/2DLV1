#include "CRoad.h"

#define INTERVAL 30

CRoadManager::CRoadManager()
	: mDispCount(0), mFrameCount(0), mpRoad(nullptr)
{
}

CRoadManager::~CRoadManager()
{
	if (mpRoad != nullptr)
	{
		delete[] mpRoad;
		mpRoad = nullptr;
	}
}

void CRoadManager::Init(CModel* pmodel)
{
	mpModel = pmodel;
	if (mpRoad == nullptr)
	{
		mpRoad = new CRoad[pmodel->mTriangles.size()];
		for (int i = 0; i < pmodel->mTriangles.size(); i++)
		{
			mpRoad[i] = pmodel->mTriangles[i];
			mpRoad[i].SetCenter();
		}
	}
}

void CRoadManager::Update()
{
	mFrameCount++;
	mFrameCount %= INTERVAL;
	if (mFrameCount == 0)
	{
		mDispCount++;
		mDispCount %= mpModel->mTriangles.size();
	}
}

void CRoadManager::Render()
{
	CMaterial material;
	for (int i = 0; i < mpModel->mTriangles.size(); i++)
	{
		if (i == mDispCount)
		{
			material.mDiffuse[0] = 1.0f;
			material.mDiffuse[1] = 0.0f;
			material.mDiffuse[2] = 0.0f;
			material.mDiffuse[3] = 1.0f;
		}
		else
		{
			material.mDiffuse[0] =
				material.mDiffuse[1] =
				material.mDiffuse[2] =
				material.mDiffuse[3] = 1.0f;
		}
		material.Enabled();
		mpModel->mTriangles[i].Render();
	}
}

void CRoad::operator=(const CTriangle& t)
{
	mV[0].mX = t.mV[0].mX;
	mV[0].mY = t.mV[0].mY;
	mV[0].mZ = t.mV[0].mZ;
	mV[1].mX = t.mV[1].mX;
	mV[1].mY = t.mV[1].mY;
	mV[1].mZ = t.mV[1].mZ;
	mV[2].mX = t.mV[2].mX;
	mV[2].mY = t.mV[2].mY;
	mV[2].mZ = t.mV[2].mZ;

	mN[0].mX = t.mN[0].mX;
	mN[0].mY = t.mN[0].mY;
	mN[0].mZ = t.mN[0].mZ;
	mN[1].mX = t.mN[1].mX;
	mN[1].mY = t.mN[1].mY;
	mN[1].mZ = t.mN[1].mZ;
	mN[2].mX = t.mN[2].mX;
	mN[2].mY = t.mN[2].mY;
	mN[2].mZ = t.mN[2].mZ;

	mUv[0].mX = t.mUv[0].mX;
	mUv[0].mY = t.mUv[0].mY;
	mUv[0].mZ = t.mUv[0].mZ;
	mUv[1].mX = t.mUv[1].mX;
	mUv[1].mY = t.mUv[1].mY;
	mUv[1].mZ = t.mUv[1].mZ;
	mUv[2].mX = t.mUv[2].mX;
	mUv[2].mY = t.mUv[2].mY;
	mUv[2].mZ = t.mUv[2].mZ;

	mMaterialIdx = t.mMaterialIdx;

}

CRoad::CRoad()
	: mEnabled(true)
{
}

void CRoad::SetCenter()
{
	mCenter.mX = (mV[0].mX + mV[1].mX + mV[2].mX) / 3.0f;
	mCenter.mY = (mV[0].mY + mV[1].mY + mV[2].mY) / 3.0f;
	mCenter.mZ = (mV[0].mZ + mV[1].mZ + mV[2].mZ) / 3.0f;
}

CVector CRoad::GetCenter()
{
	return mCenter;
}
