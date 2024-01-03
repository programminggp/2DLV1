#include "CCOlliderMesh.h"

CColliderMesh::CColliderMesh()
{
}

CColliderMesh::~CColliderMesh()
{
	//リスト内のコライダを全て削除
	for (auto idx : mpColliders)
	{
		delete idx;
	}
}

//Set(親、親行列、モデル)
//モデルから三角コライダの生成
void CColliderMesh::Set(CCharacter3* parent, CMatrix* matrix, CModel* model)
{
	//モデルから三角ポリゴンで三角コライダの配列作成
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//三角コライダを生成し、リストへ追加
		mpColliders.push_back(
			new CColliderTriangle(parent, matrix
				, model->Triangles()[i].V0()
				, model->Triangles()[i].V1()
				, model->Triangles()[i].V2()));
	}
}
