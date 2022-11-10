#include "CPaladin.h"

CPaladin::CPaladin(CVector pos, CVector rot, CVector scale)
	: mColCapsule(this,nullptr, CVector(0.0f, 170.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

void CPaladin::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColCapsule.Matrix(&mpCombinedMatrix[2]);

}