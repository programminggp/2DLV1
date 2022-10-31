#include "CPaladin.h"

CPaladin::CPaladin(CVector pos, CVector rot, CVector scale)
	: mColCapsule(this,nullptr, CVector(0.0f, 2.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), 0.3f)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

void CPaladin::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//çáê¨çsóÒÇÃê›íË
	mColCapsule.Matrix(&mpCombinedMatrix[42]);

}