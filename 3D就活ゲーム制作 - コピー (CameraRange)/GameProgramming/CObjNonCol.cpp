#include "CObjNonCol.h"

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
CObjNonCol::CObjNonCol(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:CObj(model, position, rotation, scale, false)
{
	//�R���C�_�����A�X�e�[�W�̏�����ɁB
	mTag = ENONE;
}