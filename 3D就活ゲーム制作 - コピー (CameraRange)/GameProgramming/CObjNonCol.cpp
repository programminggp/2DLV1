#include "CObjNonCol.h"

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k hasshadow:�e�ɂ��e�N�X�`�����f�̗L��
CObjNonCol::CObjNonCol(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale, bool hasshadow)
:CObj(model, position, rotation, scale, false, hasshadow)
{
	//�R���C�_���������߁A��ɃX�e�[�W�̑����ɗ��p�����B
	mTag = ENONE;
}