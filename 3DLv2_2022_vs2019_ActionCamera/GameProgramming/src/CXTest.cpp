#include "CXTest.h"
#include "CActionCamera.h"
#include "CKey.h"

#define MODEL "res\\monster\\monster-animated-character-X.X"

CModelX CXTest::sModel;

CXTest::CXTest()
{
	if (sModel.Frames().size() == 0)
	{
		sModel.Load(MODEL);
		sModel.SeparateAnimationSet(0, 0, 30, "walk");
		sModel.SeparateAnimationSet(0, 0, 120, "walk");
		sModel.SeparateAnimationSet(0, 150, 190, "run");
		sModel.SeparateAnimationSet(0, 150, 210, "run");
		sModel.SeparateAnimationSet(0, 250, 333, "attack-01");
		sModel.SeparateAnimationSet(0, 320, 400, "attack-02");
		sModel.SeparateAnimationSet(0, 390, 418, "death-01");
		sModel.SeparateAnimationSet(0, 478, 500, "growl");
		sModel.SeparateAnimationSet(0, 500, 550, "death-02");
		sModel.SeparateAnimationSet(0, 565, 650, "death-03");
	}
	mScale = CVector(0.1f, 0.1f, 0.1f);
	Init(&sModel);
}

void CXTest::Update()
{
	if (CKey::Push('0'))
	{
		ChangeAnimation(0, true, 60);
	}
	if (CKey::Push('1'))
	{
		ChangeAnimation(1, true, 60);
	}
	if (CKey::Push('2'))
	{
		ChangeAnimation(2, true, 60);
	}
	if (CKey::Push('3'))
	{
		ChangeAnimation(3, true, 60);
	}
	if (CKey::Push('0'))
	{
		ChangeAnimation(0, true, 60);
	}
	if (CKey::Push('4'))
	{
		ChangeAnimation(4, true, 60);
	}
	if (CKey::Push('5'))
	{
		ChangeAnimation(5, true, 60);
	}
	if (CKey::Push('6'))
	{
		ChangeAnimation(6, true, 60);
	}
	if (CKey::Push('7'))
	{
		ChangeAnimation(7, true, 60);
	}
	if (CKey::Push('8'))
	{
		ChangeAnimation(8, true, 60);
	}
	if (CKey::Push('9'))
	{
		ChangeAnimation(9, true, 60);
	}
	if (CKey::Push('A'))
	{
		ChangeAnimation(10, true, 60);
	}



	CXCharacter::Update();
	//ƒJƒƒ‰ˆ—
	CActionCamera::Instance()->Position(mPosition + CVector(0.0f, 3.0f, 0.0f));
}
