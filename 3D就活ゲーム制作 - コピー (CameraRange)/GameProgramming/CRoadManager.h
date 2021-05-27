#ifndef CROADMANAGER_H
#define CROADMANAGER_H

#include "CObjFloor.h"

class CRoadManager : public CObjFloor
{
public:
	//CRoadManager(���f���f�[�^�̃|�C���^,�ʒu,��],�g��k��,�X�^�[�g�ʒu,�i�s����)
	CRoadManager(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward);
	//Init(���f���f�[�^�̃|�C���^,�ʒu,��],�g��k��,�X�^�[�g�ʒu,�i�s����)
	void Init(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward);
};

#endif

