#include "CMap.h"

CMap::CMap()
:
//mCollider(this, CVector(-5.0f, 10.0f, 80.0f), CVector(5.0f, 5.0f, 80.0f), CVector(-5.0f, 5.0f, 80.0f))
mpTriangleColider(0)
{
	mCollider.SetTriangle(this, CVector(-5.0f, 10.0f, 80.0f), CVector(5.0f, 5.0f, 80.0f), CVector(-5.0f, 5.0f, 80.0f));
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

CMap::~CMap() {
	if (mpTriangleColider) {
		delete[] mpTriangleColider;
	}
}


void CMap::SetTriangleCollider() {
	if (mpModel) {
		mpTriangleColider = new CCollider[mpModel->mTriangles.size()];
		for (int i = 0; i < mpModel->mTriangles.size(); i++) {
			mpTriangleColider[i].SetTriangle(
				this,
				mpModel->mTriangles[i].mV[0],
				mpModel->mTriangles[i].mV[1],
				mpModel->mTriangles[i].mV[2]);
		}
	}
}
