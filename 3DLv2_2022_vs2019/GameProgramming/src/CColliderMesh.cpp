#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
: mpColliderTriangles(nullptr)
{
}

CColliderMesh::~CColliderMesh()
{
	if (mpColliderTriangles)
	{	//三角コライダ配列の削除
		delete[] mpColliderTriangles;
	}
}

//Set(親, 親行列, モデル)
//モデルから三角コライダの生成
void CColliderMesh::Set(CCharacter *parent, CMatrix *matrix, CModel *model)
{	//モデルの三角ポリゴンで三角コライダの配列作成
	mpColliderTriangles = new CColliderTriangle[model->Triangles().size()];
#ifdef _DEBUG
	CVector max, min;
	CColliderTriangle coltri;
	coltri.Set(parent, matrix
		, model->Triangles()[0].V0()
		, model->Triangles()[0].V1()
		, model->Triangles()[0].V2());
	max = coltri.WorldGreater();
	min = coltri.WorldLess();
#endif
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//三角コライダの設定
		mpColliderTriangles[i].Set(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2());
		//mpColliderTriangles[i].ChangePriority();
#ifdef _DEBUG
		max = max.Greater(mpColliderTriangles[i].WorldGreater());
		min = min.Less(mpColliderTriangles[i].WorldLess());
#endif
	}
#ifdef _DEBUG
	printf("MAX:%10f %10f %10f\n", max.X(), max.Y(), max.Z());
	printf("MIN:%10f %10f %10f\n", min.X(), min.Y(), min.Z());
#endif
}
