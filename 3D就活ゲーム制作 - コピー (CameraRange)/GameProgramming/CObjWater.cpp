#include "CObjWater.h"

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
CObjWater::CObjWater(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:CObj(model, position, rotation, scale)
{
	mTag = EWATER;//���c�Փ˂͂��Ȃ�
}