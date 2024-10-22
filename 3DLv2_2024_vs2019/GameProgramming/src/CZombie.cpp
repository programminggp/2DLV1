#include "CZombie.h"
#define MODEL_PATH "res\\WorldZombie\\world_war_zombie.x"
//追加のアニメーションセット
#define ANIMATION_WALK "res\\WorldZombie\\Zombie_Walk.fbx.x"

CModelX CZombie::sModel;

CZombie::CZombie()
	: mColBody(
		this, 
		nullptr, 
		CVector(0.0f, -70.0f, 0.0f),
		CVector(0.0f, 70.0f, 0.0f), 
		0.5f)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(MODEL_PATH);
		//アニメーションの追加
		sModel.AddAnimationSet(ANIMATION_WALK);
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);
}

CZombie::CZombie(const CVector& pos, const CVector& rot, const CVector& scale)
	: CZombie()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CZombie::Update()
{
	CXCharacter::Update();
	mColBody.Update();
}
