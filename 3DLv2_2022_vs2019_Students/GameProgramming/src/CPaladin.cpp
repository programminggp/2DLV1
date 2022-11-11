#include "CPaladin.h"
#include "CKey.h"

void CPaladin::Update()
{
	if (CKey::Push('W'))
	{
		mPosition = mPosition + mMatrixRotate.VectorZ() * 0.03f;
	}
	if (CKey::Push('D'))
	{
		mRotation.Y(mRotation.Y() - 1.0f);
	}
	if (CKey::Push('A'))
	{
		mRotation.Y(mRotation.Y() + 1.0f);
	}
	CXCharacter::Update();
}

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
	//çáê¨çsóÒÇÃê›íË
	mColCapsule.Matrix(&mpCombinedMatrix[2]);

}