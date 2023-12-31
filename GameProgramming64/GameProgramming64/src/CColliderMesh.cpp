#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
{
}

CColliderMesh::~CColliderMesh()
{
	//三角コライダの削除
	for (auto col : mpColliders)
	{
		delete col;
	}
}

//Set(親, 親行列, モデル)
//モデルから三角コライダの生成
void CColliderMesh::Set(CCharacter *parent, CMatrix *matrix, CModel *model)
{	
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//三角コライダの生成
		mpColliders.push_back(new CColliderTriangle(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2()));
	}
}
