#include "CObjGrass.h"

//コンストラクタ
//model:モデルのポインタ position:位置 rotation:回転 scale:拡縮
CObjGrass::CObjGrass(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:CObj(model, position, rotation, scale)
{
	mTag = EGRASS;//芝生…減速してしまうタイル
}