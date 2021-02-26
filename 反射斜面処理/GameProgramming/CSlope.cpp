#include "CSlope.h"
#include "CKey.h"

CSlope::CSlope(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
: CObj(model, position, rotation, scale)
{

}


void CSlope::Update()
{
	if (CKey::Push('J'))
	{
		mRotation.mZ++;
	}
	else if (CKey::Push('L'))
	{
		mRotation.mZ--;
	}
	if (CKey::Push('I'))
	{
		mRotation.mX++;
	}
	else if (CKey::Push('K'))
	{
		mRotation.mX--;
	}
	CCharacter::Update();
}
