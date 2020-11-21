#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
: mpColliderTriangles(0)
{
}

CColliderMesh::~CColliderMesh()
{
	if (mpColliderTriangles)
	{
		delete[] mpColliderTriangles;
	}
}

//Set(ƒ‚ƒfƒ‹)
void CColliderMesh::Set(CModel *model)
{
	mpColliderTriangles = new CColliderTriangle[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++)
	{
		mpColliderTriangles[i].Set(NULL, NULL
			, model->mTriangles[i].mV[0]
			, model->mTriangles[i].mV[1]
			, model->mTriangles[i].mV[2]);
	}
}
