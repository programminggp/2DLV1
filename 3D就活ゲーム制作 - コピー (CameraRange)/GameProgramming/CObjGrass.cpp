#include "CObjGrass.h"

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
CObjGrass::CObjGrass(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:CObj(model, position, rotation, scale)
{
	mTag = EGRASS;//�Ő��c�������Ă��܂��^�C��
}