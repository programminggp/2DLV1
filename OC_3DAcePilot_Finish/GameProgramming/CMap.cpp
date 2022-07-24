#include "CMap.h"

CMap::CMap()
{
	//地面
	mCollider[0].SetTriangle(this, CVector(200.0f, 0.0f, 200.0f), CVector(200.0f, 0.0f, -200.0f), CVector(-200.0f, 0.0f, 200.0f));

	//前壁
	mCollider[1].SetTriangle(this, CVector(135.0f, 0.0f, 135.0f), CVector(-135.0f, 0.0f, 135.0f), CVector(-110.0f, 110.0f, 110.0f));
	mCollider[2].SetTriangle(this, CVector(110.0f, 110.0f, 110.0f), CVector(135.0f, 0.0f, 135.0f), CVector(-110.0f, 110.0f, 110.0f));

	//前天井
	mCollider[3].SetTriangle(this, CVector(110.0f, 110.0f, 110.0f), CVector(-110.0f, 110.0f, 110.0f), CVector(0.0f, 190.0f, 0.0f));


	//後壁
	mCollider[4].SetTriangle(this, CVector(-135.0f, 0.0f, -135.0f), CVector(135.0f, 0.0f, -135.0f), CVector(110.0f, 110.0f, -110.0f));
	mCollider[5].SetTriangle(this, CVector(-110.0f, 110.0f, -110.0f), CVector(-135.0f, 0.0f, -135.0f), CVector(110.0f, 110.0f, -110.0f));
	//後天井
	mCollider[6].SetTriangle(this, CVector(-110.0f, 110.0f, -110.0f), CVector(110.0f, 110.0f, -110.0f), CVector(0.0f, 190.0f, 0.0f));

	//地面
	mCollider[7].SetTriangle(this, CVector(-200.0f, 0.0f, 200.0f), CVector(200.0f, 0.0f, -200.0f), CVector(-200.0f, 0.0f, -200.0f));

	//左壁
	mCollider[8].SetTriangle(this, CVector(135.0f, 0.0f, -135.0f), CVector(135.0f, 0.0f, 135.0f), CVector(110.0f, 110.0f, 110.0f));
	mCollider[9].SetTriangle(this, CVector(110.0f, 110.0f, -110.0f), CVector(135.0f, 0.0f, -135.0f), CVector(110.0f, 110.0f, 110.0f));
	//左天井
	mCollider[10].SetTriangle(this, CVector(110.0f, 110.0f, -110.0f), CVector(110.0f, 110.0f, 110.0f), CVector(0.0f, 190.0f, 0.0f));

	//右壁
	mCollider[11].SetTriangle(this, CVector(-135.0f, 0.0f, 135.0f), CVector(-135.0f, 0.0f, -135.0f), CVector(-110.0f, 110.0f, -110.0f));
	mCollider[12].SetTriangle(this, CVector(-110.0f, 110.0f, 110.0f), CVector(-135.0f, 0.0f, 135.0f), CVector(-110.0f, 110.0f, -110.0f));
	//右天井
	mCollider[13].SetTriangle(this, CVector(-110.0f, 110.0f, 110.0f), CVector(-110.0f, 110.0f, -110.0f), CVector(0.0f, 190.0f, 0.0f));

	mScale = CVector(1.0f, 1.0f, 1.0f);
}
/*
CMap::~CMap() {
	//if (mpTriangleColider) {
	//	delete[] mpTriangleColider;
	//}
}


void CMap::SetTriangleCollider() {
	if (mpModel) {
		//mpTriangleColider = new CCollider[mpModel->mTriangles.size()];
		//for (int i = 0; i < mpModel->mTriangles.size(); i++) {
		//	mpTriangleColider[i].SetTriangle(
		//		this,
		//		mpModel->mTriangles[i].mV[0],
		//		mpModel->mTriangles[i].mV[1],
		//		mpModel->mTriangles[i].mV[2]);
		//}
	}
}
*/
