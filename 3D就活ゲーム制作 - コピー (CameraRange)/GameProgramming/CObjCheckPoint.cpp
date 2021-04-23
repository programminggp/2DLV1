#include "CObjCheckPoint.h"

//コンストラクタ
//model:モデルのポインタ position:位置 rotation:回転 scale:拡縮
CObjCheckPoint::CObjCheckPoint(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale, int checkpoint_number)
:CObj(model, position, rotation, scale)
{
	cpnumber = checkpoint_number;

	if (cpnumber == 1){
		mTag = ECHECKPOINT;
	}
	else if (cpnumber == 2){
		mTag = ECHECKPOINT2;
	}
	else if (cpnumber == 3){
		mTag = ECHECKPOINT3;
	}
	else if (cpnumber == 9){
		mTag = EGOALPOINT;
	}
}