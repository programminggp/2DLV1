#include "CCOlliderMesh.h"

CColliderMesh::CColliderMesh()
	:mpColliderTriangles(nullptr)
{
}

CColliderMesh::~CColliderMesh()
{
	//if (mpColliderTriangles != nullptr)
	//{    //三角コライダ配列の削除
	//	delete[] mpColliderTriangles;
	//}
	for (auto idx : mpColliders)
	{
		delete idx;
	}
}

//Set(親、親行列、モデル)
//モデルから三角コライダの生成
void CColliderMesh::Set(CCharacter3* parent, CMatrix* matrix, CModel* model)
{   //モデルから三角ポリゴンで三角コライダの配列作成
	//mpColliderTriangles = new
	//	CColliderTriangle[model->Triangles().size()];
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{   //三角コライダの設定
		mpColliders.push_back(new CColliderTriangle(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2()));
//		mpColliderTriangles[i].ChangePriority();
	}
}