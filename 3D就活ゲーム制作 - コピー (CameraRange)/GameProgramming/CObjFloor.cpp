#include "CObjFloor.h"

//コンストラクタ
//model:モデルのポインタ position:位置 rotation:回転 scale:拡縮
CObjFloor::CObjFloor(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:CObj(model, position, rotation, scale)
{
	mTag = ENONE;//初期値と一緒
}