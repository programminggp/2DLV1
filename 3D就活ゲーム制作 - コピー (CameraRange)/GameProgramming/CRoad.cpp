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
	mRoad.clear();
}

void CRoadManager::Init(CModel* pmodel)
{
	mpModel = pmodel;
	if (mpRoad == nullptr)
	{
		int size = pmodel->mTriangles.size();
		mpRoad = new CRoad[size];
		for (int i = 0; i < size; i++)
		{
			mpRoad[i] = pmodel->mTriangles[i];
		}
		int start = 0;
		float min;
		mRoad.push_back(&mpRoad[start]);
		mpRoad[start].SetEnabled(false);
		while (mRoad.size() < size)
		{
			int min_i = 0;
			min = FLT_MAX;
			for (int i = 0; i < size; i++)
			{
				if (start != i)
				{
					if (mpRoad[i].GetEnabled())
					{
						if (min > (mpRoad[start].GetCenter() - mpRoad[i].GetCenter()).Length())
						{
							min = (mpRoad[start].GetCenter() - mpRoad[i].GetCenter()).Length();
							min_i = i;
						}
					}
				}
			}
			mpRoad[min_i].SetEnabled(false);
			mRoad.push_back(&mpRoad[min_i]);
			start = min_i;
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
		mDispCount %= mRoad.size();
	}
}

void CRoadManager::Render()
{
	CMaterial material;
	for (int i = 0; i < mRoad.size(); i++)
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
		mRoad[i]->Render();
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

	SetCenter();

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

void CRoad::SetEnabled(bool enabled)
{
	mEnabled = enabled;
}

bool CRoad::GetEnabled()
{
	return mEnabled;
}
