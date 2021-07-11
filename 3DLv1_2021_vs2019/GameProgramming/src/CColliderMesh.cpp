#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
: mpColliderTriangles(0)
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
	mpColliderTriangles = new CColliderTriangle[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++)
	{	//三角コライダの設定
		mpColliderTriangles[i].Set(parent, matrix
			, model->mTriangles[i].mV[0]
			, model->mTriangles[i].mV[1]
			, model->mTriangles[i].mV[2]);
		mpColliderTriangles[i].ChangePriority();
	}
}
