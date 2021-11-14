#ifndef CROADMANAGER_H
#define CROADMANAGER_H

#include "CObjFloor.h"

class CRoadManager : public CObjFloor
{
public:
	//CRoadManager(���f���f�[�^�̃|�C���^,�ʒu,��],�g��k��,�X�^�[�g�ʒu,�i�s����,�e�|�C���g�̔��a,�|�C���g�Ԃ̍ŏ��̊Ԋu)
	CRoadManager(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward, const float radius, const float interval=1);
	//Init(���f���f�[�^�̃|�C���^,�ʒu,��],�g��k��,�X�^�[�g�ʒu,�i�s����,�e�|�C���g�̔��a,�|�C���g�Ԃ̍ŏ��̊Ԋu)
	void Init(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward, const float radius, const float interval=1);
};

#endif
