#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
#include <list>
/*
モデルデータから三角コライダの生成
*/
class CColliderMesh
{
public:
	CColliderMesh();
	~CColliderMesh();
	//Set(親, 親行列, モデル)
	//モデルから三角コライダの生成
	void Set(CCharacter *parent, CMatrix *matrix, CModel *model);
private:
	//三角コライダのリスト
	std::list<CColliderTriangle*> mpColliders;
};

#endif
