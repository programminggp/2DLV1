#include "CPaladin.h"
#define PALADIN_MODEL_PATH "res\\paladin\\paladin.x"
//#define PALADIN_MODEL_PATH "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Walk.fbx.x"
//追加のアニメーションセット
#define ANIMATION_IDLE "res\\paladin\\Sword And Shield Idle.x"
#define ANIMATION_ATTACKSP1 "res\\paladin\\SwordAndShieldAttack.x"

CModelX CPaladin::sModel;

CPaladin::CPaladin()
	: mColBody(
		this,
		nullptr,
		CVector(0.0f, -60.0f, 0.0f),
		CVector(0.0f, 50.0f, 0.0f),
		0.5f)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(PALADIN_MODEL_PATH);
		//アニメーションの追加
		sModel.AddAnimationSet(ANIMATION_IDLE);
		sModel.AddAnimationSet(ANIMATION_ATTACKSP1);
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);
	ChangeAnimation(0, true, 221);
	//ChangeAnimation(1, true, 221);
}

CPaladin::CPaladin(const CVector& pos, const CVector& rot, const CVector& scale)
	: CPaladin()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CPaladin::Update()
{
	CXCharacter::Update();
	mColBody.Update();
}
