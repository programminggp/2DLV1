#include "CXEnemy.h"

#define MODEL "res\\knight\\knight_low.X"
CModelX CXEnemy::mModel;

CXEnemy::CXEnemy(const CVector& pos, const CVector& rot, CVector& scale)
	: CXEnemy()
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

CXEnemy::CXEnemy()
	: mColCapsBody(this, nullptr, CVector(0.5f, 3.0f, 0.0f), CVector(0.5f, -3.0f, 0.0f), 0.4f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 0.4f)
	, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.3f)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.3f)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.3f)
{
	//タグにプレイヤーを設定します
	mTag = EENEMY;
	if (mModel.Frames().size() == 0)
	{
		mModel.Load(MODEL);
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
		mModel.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
		mModel.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
		mModel.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
		mModel.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
		mModel.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン
	}
	Init(&mModel);
	ChangeAnimation(2, true, 300);
//	mColSphereSword.Tag(CCollider::ETag::ESWORD);
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColCapsBody.Matrix(&mpCombinedMatrix[1]);
	//頭
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//剣
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);

}

void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	switch (o->Type())
	{
	case CCollider::EType::ESPHERE:
		if (o->Parent()->Tag() == EPLAYER
			&& o->Tag() == CCollider::ETag::ESWORD)
		{
			if (m->Collision(m, o))
			{
				//30フレームかけてダウンし、繰り返さない
				ChangeAnimation(11, false, 30);
			}
		}
	}
}
