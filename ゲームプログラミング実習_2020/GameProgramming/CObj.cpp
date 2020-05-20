#include "CObj.h"


CObj::CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
: mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	mpCollider = new CCollider[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++) {
		mpCollider[i].SetTriangle(this,
			CVector(model->mTriangles[i].mV[0].mX, model->mTriangles[i].mV[0].mY, model->mTriangles[i].mV[0].mZ),
			CVector(model->mTriangles[i].mV[1].mX, model->mTriangles[i].mV[1].mY, model->mTriangles[i].mV[1].mZ),
			CVector(model->mTriangles[i].mV[2].mX, model->mTriangles[i].mV[2].mY, model->mTriangles[i].mV[2].mZ));
	}
}

CObj::~CObj() {
	if (mpCollider) {
		delete[] mpCollider;
	}
}
