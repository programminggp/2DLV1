#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H

#include "CModel.h"
#include "CColliderTriangle.h"
/*
モデルデータから三角形コライダの生成
*/
class CColliderMesh
{
public:
	CColliderTriangle *mpColliderTriangles;
	CColliderMesh();
	~CColliderMesh();
	//Set(モデル)
	void Set(CModel *model);
};

#endif
