#include "CMap.h"

CMap::CMap()
{
	//�n��
	mCollider[0].SetTriangle(this, CVector(200.0f, 0.0f, 200.0f), CVector(200.0f, 0.0f, -200.0f), CVector(-200.0f, 0.0f, 200.0f));

	//�O��
	mCollider[1].SetTriangle(this, CVector(135.0f, 0.0f, 135.0f), CVector(-135.0f, 0.0f, 135.0f), CVector(-110.0f, 110.0f, 110.0f));
	mCollider[2].SetTriangle(this, CVector(110.0f, 110.0f, 110.0f), CVector(135.0f, 0.0f, 135.0f), CVector(-110.0f, 110.0f, 110.0f));

	//�O�V��
	mCollider[3].SetTriangle(this, CVector(110.0f, 110.0f, 110.0f), CVector(-110.0f, 110.0f, 110.0f), CVector(0.0f, 190.0f, 0.0f));


	//���
	mCollider[4].SetTriangle(this, CVector(-135.0f, 0.0f, -135.0f), CVector(135.0f, 0.0f, -135.0f), CVector(110.0f, 110.0f, -110.0f));
	mCollider[5].SetTriangle(this, CVector(-110.0f, 110.0f, -110.0f), CVector(-135.0f, 0.0f, -135.0f), CVector(110.0f, 110.0f, -110.0f));
	//��V��
	mCollider[6].SetTriangle(this, CVector(-110.0f, 110.0f, -110.0f), CVector(110.0f, 110.0f, -110.0f), CVector(0.0f, 190.0f, 0.0f));

	//�n��
	mCollider[7].SetTriangle(this, CVector(-200.0f, 0.0f, 200.0f), CVector(200.0f, 0.0f, -200.0f), CVector(-200.0f, 0.0f, -200.0f));

	//����
	mCollider[8].SetTriangle(this, CVector(135.0f, 0.0f, -135.0f), CVector(135.0f, 0.0f, 135.0f), CVector(110.0f, 110.0f, 110.0f));
	mCollider[9].SetTriangle(this, CVector(110.0f, 110.0f, -110.0f), CVector(135.0f, 0.0f, -135.0f), CVector(110.0f, 110.0f, 110.0f));
	//���V��
	mCollider[10].SetTriangle(this, CVector(110.0f, 110.0f, -110.0f), CVector(110.0f, 110.0f, 110.0f), CVector(0.0f, 190.0f, 0.0f));

	//�E��
	mCollider[11].SetTriangle(this, CVector(-135.0f, 0.0f, 135.0f), CVector(-135.0f, 0.0f, -135.0f), CVector(-110.0f, 110.0f, -110.0f));
	mCollider[12].SetTriangle(this, CVector(-110.0f, 110.0f, 110.0f), CVector(-135.0f, 0.0f, 135.0f), CVector(-110.0f, 110.0f, -110.0f));
	//�E�V��
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
