#include "CXEnemy.h"

CXEnemy::CXEnemy()
: mColSphereBody(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f)
, mColSphereHead(this, CVector(0.0f, 5.0f, -3.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f)
, mColSphereSword(this, CVector(-10.0f, 10.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.3f)
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

void CXEnemy::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//çáê¨çsóÒÇÃê›íË
	mColSphereBody.mpCombinedMatrix = &mpCombinedMatrix[8];
	//ì™
	mColSphereHead.mpCombinedMatrix = &mpCombinedMatrix[11];
	//åï
	mColSphereSword.mpCombinedMatrix = &mpCombinedMatrix[21];
}
