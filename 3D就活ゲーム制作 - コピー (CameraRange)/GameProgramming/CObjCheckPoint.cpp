#include "CObjCheckPoint.h"

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
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