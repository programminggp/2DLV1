#include "CObjJumper.h"

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
CObjJumper::CObjJumper(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:CObj(model, position, rotation, scale)
{
	//�W�����v��A��ނɂ���Ĕ�΂��p���[���ω�
	mTag = EJUMPER;
}