#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
#include <list>
#include "CCollisionManager2.h"

/*
モデルデータから三角コライダの生成
*/
class CColliderMesh
{
public:
	void ChangePriority();
	CColliderMesh();
	~CColliderMesh();
	//Set(親、親行列、モデル)
	//モデルから三角コライダの生成
	void Set(CCharacter3* parent, CMatrix* matrix, CModel *model);
private:
	std::list<CColliderTriangle*> mpColliders;
	//三悪コライダの配列作成
	CColliderTriangle* mpColliderTriangles;
//	CTaskManager2 mColliders;
};
#endif
