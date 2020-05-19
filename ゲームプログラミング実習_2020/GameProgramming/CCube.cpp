#include "CCube.h"


CCube::CCube(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale) {
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	for (int i = 0; i < model->mTriangles.size(); i++) {
		mColTriangle[i].SetTriangle(this,
			CVector(model->mTriangles[i].mV[0].mX, model->mTriangles[i].mV[0].mY, model->mTriangles[i].mV[0].mZ),
			CVector(model->mTriangles[i].mV[1].mX, model->mTriangles[i].mV[1].mY, model->mTriangles[i].mV[1].mZ),
			CVector(model->mTriangles[i].mV[2].mX, model->mTriangles[i].mV[2].mY, model->mTriangles[i].mV[2].mZ));
	}
	//mColTriangle[0].SetTriangle(this, CVector(1.0f, 0.0f, 1.0f), CVector(1.0f, 0.0f, -1.0f), CVector(1.0f, 2.0f, -1.0f));
	//mColTriangle[1].SetTriangle(this, CVector(1.0f, 0.0f, 1.0f), CVector(1.0f, 2.0f, -1.0f), CVector(1.0f, 2.0f, 1.0f));
	//mColTriangle[2].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[3].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[4].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[5].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[6].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[7].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[8].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[9].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[10].SetTriangle(this, CVector(), CVector(), CVector());
	//mColTriangle[11].SetTriangle(this, CVector(), CVector(), CVector());
}

CCube::~CCube() {

}
